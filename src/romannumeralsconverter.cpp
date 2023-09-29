#include "romannumeralsconverter.h"


/* Le mappe non possono essere constexpr, quindi occorre dichiararle static
const e definirle fuori dalla classe */

const std::map<const size_t, const std::string> RomanNumeralsConverter::m_ThouToRom_Map =
{
  {1, "M"}, {2, "MM"}, {3, "MMM"}
};

const std::map<const size_t, const std::string> RomanNumeralsConverter::m_HundToRom_Map =
{
  {1, "C"}, {2, "CC"}, {3, "CCC"}, {4, "CD"}, {5, "D"}, {6, "DC"}, {7, "DCC"}, {8, "DCCC"}, {9, "CM"}
};

const std::map<const size_t, const std::string> RomanNumeralsConverter::m_TensToRom_Map =
{
  {1, "X"}, {2, "XX"}, {3, "XXX"}, {4, "XL"}, {5, "L"}, {6, "LX"}, {7, "LXX"}, {8, "LXXX"}, {9, "XC"}
};

const std::map<const size_t, const std::string> RomanNumeralsConverter::m_UnitToRom_Map =
{
  {1, "I"}, {2, "II"}, {3, "III"}, {4, "IV"}, {5, "V"}, {6, "VI"}, {7, "VII"}, {8, "VIII"}, {9, "IX"}
};

const std::map<const std::string, const size_t> RomanNumeralsConverter::m_RomToDec_Map =
{
  {"I", 1},    {"II", 2},    {"III", 3},   {"IV", 4},   {"V", 5},   {"VI", 6},   {"VII", 7},   {"VIII", 8},   {"IX", 9},
  {"X", 10},   {"XX", 20},   {"XXX", 30},  {"XL", 40},  {"L", 50},  {"LX", 60},  {"LXX", 70},  {"LXXX", 80},  {"XC", 90},
  {"C", 100},  {"CC", 200},  {"CCC", 300}, {"CD", 400}, {"D", 500}, {"DC", 600}, {"DCC", 700}, {"DCCC", 800}, {"CM", 900},
  {"M", 1000}, {"MM", 2000}, {"MMM", 3000}
};


/**
 * @brief Convert a decimal number to its roman equivalent
 *
 * @param DecimalNumeral The size_t decimal value to be converted
 * @return std::string
 **/
std::string RomanNumeralsConverter::ConvertDecimalToRoman(size_t DecimalNumeral) const
{
  std::string Result;

  if (DecimalNumeral == 0 || DecimalNumeral > 3999)
  {
    /* Number not supported */
#ifndef NDEBUG
    std::cerr << "\nError: number not supported\n";
#endif // NDEBUG
  }
  else
  {
    constexpr size_t Size = static_cast<size_t>(PowersOfTen::HOW_MANY);
    size_t DecimalPlaces[Size];

    for (size_t i = Size; i > 0; --i)
    {
      /* Split "DecimalNumeral" into individual decimal places and store into
      "DecimalPlaces". Most significant digit (thousands) is at index 0. */

      DecimalPlaces[i - 1] = DecimalNumeral % 10;
      DecimalNumeral /= 10;
    }

    /* Read the individual decimal places and convert them to strings. The
    following constants are for easier reading. */

    constexpr size_t ThouIndex = static_cast<size_t>(PowersOfTen::THOUSANDS);
    constexpr size_t HundIndex = static_cast<size_t>(PowersOfTen::HUNDREDS);
    constexpr size_t TensIndex = static_cast<size_t>(PowersOfTen::TENS);
    constexpr size_t UnitIndex = static_cast<size_t>(PowersOfTen::UNITS);

    /* Incrementally build the string */

    if (DecimalPlaces[ThouIndex] != 0)
    {
      // Result += m_ThouToRom_Map[DecimalPlaces[ThouIndex]]; // L'operatore indicizzazione potrebbe modificare la mappa, pertanto è in contrasto con il modificatore "const" della funzione
      Result += m_ThouToRom_Map.find(DecimalPlaces[ThouIndex])->second; // Occorre invece utilizzare il metodo "find".
    }
    else {;} // Empty place: nothing to convert

    if (DecimalPlaces[HundIndex] != 0)
    {
      Result += m_HundToRom_Map.find(DecimalPlaces[HundIndex])->second;
    }
    else {;} // Empty place: nothing to convert

    if (DecimalPlaces[TensIndex] != 0)
    {
      Result += m_TensToRom_Map.find(DecimalPlaces[TensIndex])->second;
    }
    else {;} // Empty place: nothing to convert

    if (DecimalPlaces[UnitIndex] != 0)
    {
      Result += m_UnitToRom_Map.find(DecimalPlaces[UnitIndex])->second;
    }
    else {;} // Empty place: nothing to convert
  }

  return Result;
}


/**
 * @brief Convert a roman numeral to its decimal equivalent
 *
 * @param RomanNumeral The std::string to be converted
 * @return size_t
 **/
size_t RomanNumeralsConverter::ConvertRomanToDecimal(const std::string& RomanNumeral) const
{
  size_t      Result = 0;
  std::string AllowedLetters("CDILMVX");

  std::string tempRomanNumeral = RomanNumeral;

  for (auto& Char : tempRomanNumeral)
  {
    Char = static_cast<char>(std::toupper(static_cast<char>(Char)));
  }

  if (tempRomanNumeral.find_first_not_of(AllowedLetters) != std::string::npos)
  {
    /* Illegal letter detected */
  #ifndef NDEBUG
    // throw std::runtime_error("\nIllegal letter\n"); // Debug
    std::cerr << "\n\"" << tempRomanNumeral << "\": illegal letter detected\n";
  #endif // NDEBUG

    Result = 0;
  }
  else
  {
    /* All letters in string have been recognised. Proceed */

    PowersOfTen PreviousPower = PowersOfTen::THOUSANDS;
    PowersOfTen  CurrentPower = PowersOfTen::THOUSANDS;
    bool hasJustStarted       = true;
    char PreviousLetter       = '\0';
    std::string TempStr; // Used to convert a group of letters representing thousands, hundreds, tens or units

    auto Iter = tempRomanNumeral.cbegin();

    /* Analyse the whole string, and try to recognise the groups of letters that
    sequentially make up the thousands, hundreds, tens and units. If no errors
    are detected, store the individual groups into "TempStr", convert "TempStr"
    to a decimal number, repeat for all powers of 10 and accumulate to get the
    final result. */

    while(Iter != tempRomanNumeral.cend())
    {
      /* Identify the power of ten the character belongs to */

      if (*Iter == 'M' && PreviousLetter != 'C')
      {
        CurrentPower = PowersOfTen::THOUSANDS;
      }
      else if (   (*Iter == 'M' && PreviousLetter == 'C')
               || (*Iter == 'C' && PreviousLetter != 'X')
               || (*Iter == 'D') )
      {
        CurrentPower = PowersOfTen::HUNDREDS;
      }
      else if (   (*Iter == 'C' && PreviousLetter == 'X')
               || (*Iter == 'X' && PreviousLetter != 'I')
               || (*Iter == 'L') )
      {
        CurrentPower = PowersOfTen::TENS;
      }
      else
      {
        CurrentPower = PowersOfTen::UNITS;
      }

      /* Split up the original string into substrings representing thousands, hundreds,
      etc. Store the substring into "TempStr", to be later converted into a size_t */

      if ( hasJustStarted )
      {
        /* The process has just started: store the first read letter and advance */

        hasJustStarted = false;
        PreviousPower = CurrentPower;
        TempStr.push_back(*Iter);
      }
      else if ( CurrentPower > PreviousPower )
      {
        /* Power of ten has decreased: convert the substring, clear it and continue */
        /* REMINDER: in "PowersOfTen" enum, thousands are lowest and units are highest. */

        auto Found = m_RomToDec_Map.find(TempStr);

        if (Found != m_RomToDec_Map.cend())
        {
          Result += Found->second;
          TempStr.clear();
          TempStr.push_back(*Iter);
        }
        else
        {
#ifndef NDEBUG
          // throw std::runtime_error("\nNot found in map");
          std::cerr << "\n\"" << TempStr << "\": error computing powers of ten (CurrentPower > PreviousPower)";
#endif // NDEBUG

          Result = 0;
          break;
        }
      }
      else if (CurrentPower == PreviousPower)
      {
        /* Same power of ten. Continue building the substring */

        TempStr.push_back(*Iter);
      }
      else /* CurrentPower < PreviousPower */
      {
        /* Powers of ten must be sequential from thousands to units */

#ifndef NDEBUG
        // throw std::runtime_error("\nErrore potenza");
        std::cerr << "\n\"" << TempStr << "\": error computing powers of ten (CurrentPower < PreviousPower)";
#endif // NDEBUG

        Result = 0;
        break;
      }

      /* If end of string has been reached, convert the substring immediately */

      if ( (Iter + 1) == tempRomanNumeral.cend() )
      {
        auto Found = m_RomToDec_Map.find(TempStr);

        if (Found != m_RomToDec_Map.cend())
        {
          Result += Found->second;
        }
        else
        {
#ifndef NDEBUG
          // throw std::runtime_error("\nNot found in map");
          std::cerr << "\n\"" << TempStr << "\": not found in map";
#endif // NDEBUG

          Result = 0;
          break;
        }
      }
      else {/* Continue analysing the string */}

      PreviousLetter = *Iter;
      PreviousPower  = CurrentPower;

      ++Iter;
    }
  }

  return Result;
}

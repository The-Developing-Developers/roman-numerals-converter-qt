#include "romannumeralsconverter.h"

RomanNumeralsConverter::RomanNumeralsConverter(QObject *parent)
    : QObject{parent}
{

}

/* Le mappe non possono essere constexpr, quindi occorre dichiararle static
const e definirle fuori dalla classe */

const QMap<const size_t, QString> RomanNumeralsConverter::m_ThouToRom_Map =
{
  {1, "M"}, {2, "MM"}, {3, "MMM"}
};

const QMap<const size_t, QString> RomanNumeralsConverter::m_HundToRom_Map =
{
  {1, "C"}, {2, "CC"}, {3, "CCC"}, {4, "CD"}, {5, "D"}, {6, "DC"}, {7, "DCC"}, {8, "DCCC"}, {9, "CM"}
};

const QMap<const size_t, QString> RomanNumeralsConverter::m_TensToRom_Map =
{
  {1, "X"}, {2, "XX"}, {3, "XXX"}, {4, "XL"}, {5, "L"}, {6, "LX"}, {7, "LXX"}, {8, "LXXX"}, {9, "XC"}
};

const QMap<const size_t, QString> RomanNumeralsConverter::m_UnitToRom_Map =
{
  {1, "I"}, {2, "II"}, {3, "III"}, {4, "IV"}, {5, "V"}, {6, "VI"}, {7, "VII"}, {8, "VIII"}, {9, "IX"}
};

const QMap<const QString, size_t> RomanNumeralsConverter::m_RomToDec_Map =
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
 * @return QString
 **/
QString RomanNumeralsConverter::ConvertDecimalToRoman(size_t DecimalNumeral) const
{
  QString Result;

  if (DecimalNumeral == 0 || DecimalNumeral > 3999)
  {
    /* Number not supported */
    qDebug() << "\nError: number not supported\n";
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
      Result += m_ThouToRom_Map.find(DecimalPlaces[ThouIndex]).value(); // Occorre invece utilizzare il metodo "find".
    }
    else {;} // Empty place: nothing to convert

    if (DecimalPlaces[HundIndex] != 0)
    {
      Result += m_HundToRom_Map.find(DecimalPlaces[HundIndex]).value();
    }
    else {;} // Empty place: nothing to convert

    if (DecimalPlaces[TensIndex] != 0)
    {
      Result += m_TensToRom_Map.find(DecimalPlaces[TensIndex]).value();
    }
    else {;} // Empty place: nothing to convert

    if (DecimalPlaces[UnitIndex] != 0)
    {
      Result += m_UnitToRom_Map.find(DecimalPlaces[UnitIndex]).value();
    }
    else {;} // Empty place: nothing to convert
  }

  return Result;
}


/**
 * @brief Convert a roman numeral to its decimal equivalent
 *
 * @param RomanNumeral The QString to be converted
 * @return size_t
 **/
size_t RomanNumeralsConverter::ConvertRomanToDecimal(const QString& RomanNumeral) const
{
  size_t      Result = 0;
  QString AllowedLetters("CDILMVX");

  QString tempRomanNumeral = RomanNumeral.toUpper();

  if (tempRomanNumeral.toStdString().find_first_not_of(AllowedLetters.toStdString()) != std::string::npos)
  {
    /* Illegal letter detected */
    qDebug() << "\n\"" << tempRomanNumeral << "\": illegal letter detected\n";

    Result = 0;
  }
  else
  {
    /* All letters in string have been recognised. Proceed */

    PowersOfTen PreviousPower = PowersOfTen::THOUSANDS;
    PowersOfTen  CurrentPower = PowersOfTen::THOUSANDS;
    bool hasJustStarted       = true;
    QChar PreviousLetter       = '\0';
    QString TempStr; // Used to convert a group of letters representing thousands, hundreds, tens or units

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
          Result += Found.value();
          TempStr.clear();
          TempStr.push_back(*Iter);
        }
        else
        {
          qDebug() << "\n\"" << TempStr << "\": error computing powers of ten (CurrentPower > PreviousPower)";

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

        qDebug() << "\n\"" << TempStr << "\": error computing powers of ten (CurrentPower < PreviousPower)";

        Result = 0;
        break;
      }

      /* If end of string has been reached, convert the substring immediately */

      if ( (Iter + 1) == tempRomanNumeral.cend() )
      {
        auto Found = m_RomToDec_Map.find(TempStr);

        if (Found != m_RomToDec_Map.cend())
        {
          Result += Found.value();
        }
        else
        {
          qDebug() << "\n\"" << TempStr << "\": not found in map";

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

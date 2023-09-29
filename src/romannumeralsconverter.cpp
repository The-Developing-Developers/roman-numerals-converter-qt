#include "romannumeralsconverter.h"

/* I vettori in C++17 non possono essere constexpr, quindi occorre dichiararli static const e
definirli fuori dalla classe. */

const QVector<QPair<const size_t, const QString>> RomanNumeralsConverter::m_DecToRom_Map
{
  {1,    "I"}, { 2,    "II"}, { 3,    "III"}, { 4,   "IV"}, { 5,   "V"}, { 6,   "VI"}, { 7,   "VII"}, { 8,   "VIII"}, { 9,   "IX"},
  {10,   "X"}, { 20,   "XX"}, { 30,   "XXX"}, { 40,  "XL"}, { 50,  "L"}, { 60,  "LX"}, { 70,  "LXX"}, { 80,  "LXXX"}, { 90,  "XC"},
  {100,  "C"}, { 200,  "CC"}, { 300,  "CCC"}, { 400, "CD"}, { 500, "D"}, { 600, "DC"}, { 700, "DCC"}, { 800, "DCCC"}, { 900, "CM"},
  {1000, "M"}, { 2000, "MM"}, { 3000, "MMM"}
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

  if ( DecimalNumeral == LowerLimitForConversion || DecimalNumeral >= UpperLimitForConversion )
  {
    /* Number not supported */
    qDebug() << "\nError: number not supported\n";
    return Result;
  }
  else { /* All OK: proceed */ }

  constexpr size_t Size = static_cast<size_t>(PowersOfTen::HOW_MANY);
  size_t DecimalPlaces[Size];

  for (size_t i = 0; i != Size; ++i)
  {
    /* Split "DecimalNumeral" into individual decimal places and store into "DecimalPlaces". Least
    significant digit (units) is at index 0. For example, number 2497 is stored as 7942. */

    DecimalPlaces[i] = DecimalNumeral % 10;
    DecimalNumeral /= 10;
  }

  /* The following constants are for easier reading. */

  constexpr size_t ThouIndex = static_cast<size_t>(PowersOfTen::THOUSANDS);
  constexpr size_t HundIndex = static_cast<size_t>(PowersOfTen::HUNDREDS);
  constexpr size_t TensIndex = static_cast<size_t>(PowersOfTen::TENS);
  constexpr size_t UnitIndex = static_cast<size_t>(PowersOfTen::UNITS);

  /* Incrementally build the final string by reading the individual decimal places, converting them
  to roman substrings, and concatenating them. */

  if (DecimalPlaces[ThouIndex] != 0)
  {
    Result += GetSubstrFromNumber_Pvt(DecimalPlaces, ThouIndex);
  }
  else { /* Empty place: nothing to convert */ }

  if (DecimalPlaces[HundIndex] != 0)
  {
    Result += GetSubstrFromNumber_Pvt(DecimalPlaces, HundIndex);
  }
  else { /* Empty place: nothing to convert */ }

  if (DecimalPlaces[TensIndex] != 0)
  {
    Result += GetSubstrFromNumber_Pvt(DecimalPlaces, TensIndex);
  }
  else { /* Empty place: nothing to convert */ }

  if (DecimalPlaces[UnitIndex] != 0)
  {
    Result += GetSubstrFromNumber_Pvt(DecimalPlaces, UnitIndex);
  }
  else { /* Empty place: nothing to convert */ }


  return Result;
}


/**
 * @brief Convert a roman numeral to its decimal equivalent
 *
 * @param RomanNumeralCopy A copy of the QString to be converted. A copy is needed to allow ignoring
 * case in original string, which cannot be modified.
 * @return Converted number, base-10
 **/
size_t RomanNumeralsConverter::ConvertRomanToDecimal(QString RomanNumeralCopy) const
{
        size_t  Result = 0;
  const QString AllowedLetters("CDILMVX");
  auto const    NotFound = std::string::npos;

  RomanNumeralCopy = RomanNumeralCopy.toUpper();

  if (RomanNumeralCopy.toStdString().find_first_not_of(AllowedLetters.toStdString()) != NotFound)
  {
    /* Illegal letter detected */
    qDebug() << "\n\"" << RomanNumeralCopy << "\": illegal letter detected\n";

    return Result;
  }
  else { /* OK: continue */ }

  /* All letters in string "RomanNumeralCopy" have been recognised. Proceed */

  PowersOfTen PreviousPower  = PowersOfTen::THOUSANDS; // Used to determine whether a substring needs to be converted to decimal
  PowersOfTen CurrentPower   = PowersOfTen::THOUSANDS; // Used to determine whether a substring needs to be converted to decimal
  bool        isFirstLetter  = true; // Used because the first letter of "RomanNumeralCopy" needs a different treatment
  QChar       PreviousLetter = '\0';
  QString     TempSubStr; // Used to convert a group of letters representing thousands, hundreds, tens or units

  auto StrIter = RomanNumeralCopy.cbegin();

  /* Analyse the whole "RomanNumeralCopy" string one char at a time, and try to recognise the groups
  of letters that sequentially make up the thousands, hundreds, tens and units. If no errors are
  detected, store the individual chars into "TempSubStr", convert "TempSubStr" to a decimal number,
  repeat for all powers of 10 and accumulate to get the final result. */

  while( StrIter != RomanNumeralCopy.cend() )
  {
    /* Identify the power of ten the analysed character belongs to */

    if (*StrIter == 'M' && PreviousLetter != 'C')
    {
      CurrentPower = PowersOfTen::THOUSANDS;
    }
    else if (    (*StrIter == 'M' && PreviousLetter == 'C')
              || (*StrIter == 'C' && PreviousLetter != 'X')
              || (*StrIter == 'D') )
    {
      CurrentPower = PowersOfTen::HUNDREDS;
    }
    else if (    (*StrIter == 'C' && PreviousLetter == 'X')
              || (*StrIter == 'X' && PreviousLetter != 'I')
              || (*StrIter == 'L') )
    {
      CurrentPower = PowersOfTen::TENS;
    }
    else
    {
      CurrentPower = PowersOfTen::UNITS;
    }

    /* Split up the original string into substrings representing thousands, hundreds, etc. Store the
    substring into "TempSubStr", to be later converted into a size_t */

    if ( isFirstLetter )
    {
      /* The process has just started: store the first read letter and advance. This case is
      accessed only once, at the beginning of the conversion. It needs to be treated differently
      from the others because a starting point for the whole conversion is required, or else the
      "Final Check" (see below) would fail. */

      isFirstLetter = false;
      TempSubStr.push_back(*StrIter);
    }
    else if ( CurrentPower < PreviousPower )
    {
      /* Power of ten has decreased: convert the substring, clear it and continue */

      size_t ValidationResult = ValidateTempStr_Pvt(TempSubStr);

      if ( ValidationResult )
      {
        Result += ValidationResult;
        TempSubStr.clear();
        TempSubStr.push_back(*StrIter);
      }
      else
      {
        qDebug() << "\n\"" << TempSubStr << "\": error computing powers of ten (CurrentPower > PreviousPower)";

        Result = 0;
        break; // while(StrIter != RomanNumeralCopy.cend()) // Stop whole process
      }
    }
    else if (CurrentPower == PreviousPower)
    {
      /* Same power of ten. Continue building the substring */

      TempSubStr.push_back(*StrIter);
    }
    else /* CurrentPower > PreviousPower */
    {
      /* Powers of ten must be sequential from thousands to units */

      qDebug() << "\n\"" << TempSubStr << "\": error computing powers of ten (CurrentPower < PreviousPower)";

      Result = 0;
      break; // while(StrIter != RomanNumeralCopy.cend()) // Stop whole process
    }

    /* Final Check: if end of string has been reached, convert the substring immediately. */

    if ( (StrIter + 1) == RomanNumeralCopy.cend() )
    {
      size_t ValidationResult = ValidateTempStr_Pvt(TempSubStr);

      if ( ValidationResult )
      {
        Result += ValidationResult;
        break;
      }
      else
      {
        qDebug() << "\n\"" << TempSubStr << "\": not found in map";

        Result = 0;
      }
    }
    else { /* Continue analysing the string */ }

    PreviousLetter = *StrIter;
    PreviousPower  =  CurrentPower;

    ++StrIter;
  }


  return Result;
}


/**
 * @brief Validate the temporary substring when converting from roman to
 * decimal. If validation is unsuccessful, returns zero.
 *
 * @param TempStr The substring to be validated
 * @return size_t
 **/
size_t RomanNumeralsConverter::ValidateTempStr_Pvt(const QString& TempStr) const
{
  size_t Result = (size_t)0;

  for ( const auto& Pair : m_DecToRom_Map )
  {
    if ( Pair.second == TempStr )
    {
      Result = Pair.first;
      break;
    }
    else
    {;} // Continue searching
  }

  return Result;
}


/**
 * @brief Converts a single digit to its equivalent roman representation, taking into account the
 * digit's decimal place.
 *
 * @param DecimalPlaces Array containing the original decimal number split into individual digits
 * @param Index The index used to traverse the array
 * @return QString
 **/
QString RomanNumeralsConverter::GetSubstrFromNumber_Pvt(size_t* DecimalPlaces, size_t Index) const
{
  QString Result;
  size_t  Multiplier;

  switch ( Index )
  {
    case static_cast<size_t>(PowersOfTen::THOUSANDS):
      Multiplier = (size_t)1000;
      break;

    case static_cast<size_t>(PowersOfTen::HUNDREDS):
      Multiplier = (size_t)100;
      break;

    case static_cast<size_t>(PowersOfTen::TENS):
      Multiplier = (size_t)10;
      break;

    case static_cast<size_t>(PowersOfTen::UNITS):
      Multiplier = (size_t)1;
      break;

    default:
      throw std::runtime_error("PowersOfTen: unsupported enumerative");
      break;
  }

  for ( const auto& Pair : m_DecToRom_Map )
  {
    if ( Pair.first == DecimalPlaces[Index] * Multiplier )
    {
      Result = Pair.second;
      break;
    }
    else
    {;} // Continue searching in the map
  }

  return Result;
}

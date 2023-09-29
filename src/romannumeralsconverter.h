/**
 * @file Roman_Numerals_Converter.hpp
 *
 * @brief Converts from decimal to roman numeral and vice-versa.
 **/

#ifndef ROMANNUMERALSCONVERTER_H
#define ROMANNUMERALSCONVERTER_H

#ifndef NDEBUG
  #include <iostream>
#endif // NDEBUG

#include <string>
#include <map>
#include <QObject>


/**
 * @brief Converts a decimal number (a size_t) to a roman numeral (an std::string) and
 * vice-versa.
 * 
 * Instantiate this class and use its methods.
 *
 * The converter only supports numbers from 1 up to 3999.
 **/
class RomanNumeralsConverter : public QObject
{
  Q_OBJECT

private:

  /**
   * @brief Used to properly identify individual decimal places both during
   * Roman-to-Decimal and Decimal-to-Roman conversion
   **/
  enum class PowersOfTen
  {
    THOUSANDS,
    HUNDREDS,
    TENS,
    UNITS,

    HOW_MANY
  };

  /* Map individual decimal places to their roman equivalent. Used to build
  the output string in the decimal-to-roman converter. */

  static const std::map<const size_t, const std::string> m_ThouToRom_Map;
  static const std::map<const size_t, const std::string> m_HundToRom_Map;
  static const std::map<const size_t, const std::string> m_TensToRom_Map;
  static const std::map<const size_t, const std::string> m_UnitToRom_Map;

  /* Map individual roman numberals to their decimal values equivalent. Used
  to generate the output number in the roman-to-decimal converter. */

  static const std::map<const std::string, const size_t> m_RomToDec_Map;

public:
  explicit RomanNumeralsConverter(QObject *parent = nullptr);
  ~RomanNumeralsConverter(void) = default;

  std::string ConvertDecimalToRoman(size_t) const;
  size_t      ConvertRomanToDecimal(const std::string&) const;

};

#endif // ROMANNUMERALSCONVERTER_H

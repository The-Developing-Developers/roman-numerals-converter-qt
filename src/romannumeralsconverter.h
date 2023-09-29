/**
 * @file Roman_Numerals_Converter.hpp
 *
 * @brief Converts from decimal to roman numeral and vice-versa.
 **/

#ifndef ROMANNUMERALSCONVERTER_H
#define ROMANNUMERALSCONVERTER_H

#include <QString>
#include <QMap>
#include <QObject>
#include <QtDebug>


/**
 * @brief Converts a decimal number (a size_t) to a roman numeral (an QString) and
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

  static const QMap<const size_t, QString> m_ThouToRom_Map;
  static const QMap<const size_t, QString> m_HundToRom_Map;
  static const QMap<const size_t, QString> m_TensToRom_Map;
  static const QMap<const size_t, QString> m_UnitToRom_Map;

  /* Map individual roman numberals to their decimal values equivalent. Used
  to generate the output number in the roman-to-decimal converter. */

  static const QMap<const QString, size_t> m_RomToDec_Map;

public:
  explicit RomanNumeralsConverter(QObject *parent = nullptr);
  ~RomanNumeralsConverter(void) = default;

  QString ConvertDecimalToRoman(size_t) const;
  size_t  ConvertRomanToDecimal(const QString&) const;

};

#endif // ROMANNUMERALSCONVERTER_H

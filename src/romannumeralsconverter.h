/**
 * @file romannumeralsconverter.h
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
 * @brief Converts a decimal number (a size_t) to a roman numeral (an QString) and vice-versa.
 * \n Instantiate this class and use its methods.
 * \n The converter only supports numbers from 1 up to 3999.
 **/
class RomanNumeralsConverter
{
private:

  /**
   * @brief Used to properly identify individual decimal places both during Roman-to-Decimal and
   * Decimal-to-Roman conversion
   **/
  enum class PowersOfTen
  {
    UNITS,
    TENS,
    HUNDREDS,
    THOUSANDS,

    HOW_MANY
  };

  static constexpr size_t LowerLimitForConversion = (size_t)0;
  static constexpr size_t UpperLimitForConversion = (size_t)4000;

  static const QVector<QPair<const size_t, const QString>> m_DecToRom_Map;

  size_t  ValidateTempStr_Pvt    (const QString&)  const;
  QString GetSubstrFromNumber_Pvt(size_t*, size_t) const;

public:

  explicit RomanNumeralsConverter(void) = default;
          ~RomanNumeralsConverter(void) = default;

  QString ConvertDecimalToRoman(size_t)  const;
  size_t  ConvertRomanToDecimal(QString) const;

};

#endif // ROMANNUMERALSCONVERTER_H

#include "Keys.hpp"
#include "Delimiter.hpp"
#include "StreamGuard.hpp"

std::istream & vorobieva::operator>>(std::istream & in, ComplexKey && key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = DelimiterChar;
  using delStr = DelimiterString;
  double real = 0;
  double imag = 0;
  in >> delStr{ "#c(" } >> real >> imag >> del{ ')' };
  if (in)
  {
    key.smth = {real, imag};
  }
  return in;
}

std::istream & vorobieva::operator>>(std::istream & in, BinaryKey && key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  StreamGuard fmtguard(in);
  using del = DelimiterChar;
  in >> del{ '0' } >> del{ 'b' };
  key.smth = 0;
  in >> key.smth;
  if (in && (key.smth != 0) && (key.smth != 1))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & vorobieva::operator>>(std::istream & in, StringKey && key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterChar;
  in >> del{ '"' };
  std::getline(in, key.smth, '\"');
  return in;
}
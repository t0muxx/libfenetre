#include <windows.h>

namespace utils {

wchar_t *cstr_to_wstr(const char *c) {
  size_t written;
  const size_t cSize = strlen(c) + 1;
  wchar_t *wc = new wchar_t[cSize];
  mbstowcs_s(&written, wc, cSize, c, cSize);

  return wc;
}

} // namespace utils

#include "errors.h"

namespace errors {
void error_exit(LPSTR function_name) {
  LPVOID message_buf = 0;
  LPVOID display_buf = 0;
  DWORD error_code = GetLastError();

  FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                     FORMAT_MESSAGE_IGNORE_INSERTS,
                 NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                 (LPSTR)message_buf, 0, NULL);

  fprintf(stderr, "%s failed with error code : %lu: %s\n", function_name,
          error_code, (LPSTR)message_buf);

  ExitProcess(error_code);
}
} // namespace errors
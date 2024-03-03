#include "errors.h"

void errors::error_exit(LPSTR function_name) {
  LPVOID message_buf = 0;
  LPVOID display_buf = 0;
  DWORD error_code = GetLastError();

  FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                     FORMAT_MESSAGE_IGNORE_INSERTS,
                 NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                 (LPSTR)message_buf, 0, NULL);

  fprintf(stderr, "err: %s failed with error code : %lu: %s\n", function_name,
          error_code, (LPSTR)message_buf);

  ExitProcess(error_code);
}

DWORD errors::error_print(std::string function_name) {
  LPVOID message_buf = 0;
  LPVOID display_buf = 0;
  DWORD error_code = GetLastError();

  FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                     FORMAT_MESSAGE_IGNORE_INSERTS,
                 NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                 (LPSTR)message_buf, 0, NULL);

  fprintf(stderr, "err: %s failed with error code : %lu: %s\n",
          function_name.c_str(), error_code, (LPSTR)message_buf);

  return (error_code);
}

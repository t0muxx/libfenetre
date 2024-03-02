#include "peb.h"

namespace process {

PPEB getPEB() { return (PPEB)__readgsqword(0x60); }

} // namespace process
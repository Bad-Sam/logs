#include "logs.h"

__declspec(dllimport) void __stdcall ExitProcess(u32);

s32 _fltused;

void mainCRTStartup()
{
  const char* logs_file_name = "logs.txt";
  
  // Open outputs
  logs_open_console_output();
  logs_open_file_output(logs_file_name);

  u32 bits = 0x3C000000;
  for (u32 bit_pos = 24; bit_pos > 15; bit_pos--)
  {
    bits |= (1 << bit_pos);
    f32 value = *(f32*)&bits;

    // Format logs
    logs_append_hex(bits);
    logs_append_literal(" (");
    logs_append_u32(bits);
    logs_append_literal(") as a f32 is ");
    logs_append_f32(value);
    logs_append_char('\n');

    // When deemed ready, write buffered logs to enabled outputs
    logs_flush();
  }

  // Write to specific outputs
  logs_disable_output(LOGS_OUTPUT_CONSOLE);
  logs_append_literal("========== Logging session end ==========\n\n");
  logs_flush();
  
  logs_enable_output(LOGS_OUTPUT_CONSOLE);
  logs_disable_output(LOGS_OUTPUT_FILE);
  logs_append_literal("\nLogs written to file ");
  logs_append_cstr(logs_file_name);

  // Close outputs, implicitly flushing logs buffer to enable outputs
  logs_close_file_output();
  logs_close_console_output();

  ExitProcess(0);
}

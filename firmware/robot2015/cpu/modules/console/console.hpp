#pragma once

#include "robot.hpp"
#include <memory>
#include "commands.hpp"

/**
 * enable scrolling vi sequence
 */
const std::string ENABLE_SCROLL_SEQ = "\033[r";

/**
 * clear screen vi sequence
 */
const std::string CLEAR_SCREEN_SEQ = "\033[2J";

/**
 * Manages serial-over-USB communication with the PC
 */
class Console
{

public:
  /**
   * max buffer length. Default 252 (three lines)
   */
  static const uint8_t BUFFER_LENGTH = 252;

  /**
   * new line character. Default '\r'
   */
  static const char NEW_LINE_CHAR = 13;  //ASCII CR (\r) (0x0D)

  /**
   * backspace flag char. (What char does the console send when the backspace key
   * is pressed?). Default DEL
   */
  static const char BACKSPACE_FLAG_CHAR = 127; //ASCII DEL (0x7F)

  /**
   * backspace reply char. (What char causes screen to delete the last
   * character?). Default '\b'
   */
  static const char BACKSPACE_REPLY_CHAR = 8;   //ASCII BK (\b) (0x08)

  /**
   * when the console backspaces, what does the last character become. Default ' '
   */
  static const char BACKSPACE_REPLACE_CHAR = 32;

  /**
   * default ETX (0x3)
   */
  static const char BREAK_CHAR = 3;

  /**
   * define the sequence for arrow key flags
   */
  static const char ARROW_KEY_SEQUENCE_ONE = 27;
  static const char ARROW_KEY_SEQUENCE_TWO = 91;
  static const char ARROW_UP_KEY = 65;
  static const char ARROW_DOWN_KEY = 66;

  static const char CMD_END_CHAR = ';';

  /**
   * receice buffer full error message
   */
  static const std::string RX_BUFFER_FULL_MSG;

  /**
   * break message
   */
  static const std::string COMMAND_BREAK_MSG;

  /**
  * console header string.
  */
  static std::string CONSOLE_HEADER;
  static std::string CONSOLE_USER;
  static std::string CONSOLE_HOSTNAME;

  /**
   * Serial (over USB) baud rate. Default 9600. Screen default 9600
   */
  static uint16_t baudrate;

  /**
   * Console initialization routine. Attaches interrupt handlers and clears the
   * buffers.
   */
  static void Init(void);

  /**
   * console communications check. should be called in the main loop.
   */
  static void ConComCheck(void);

  /**
   * flushes stdout. Should be called after every putc or printf block.
   */
  static void Flush(void);

  /**
   * requests the main loop break
   */
  static void RequestSystemStop(void);

  /**
   * returns if the main loop should break
   */
  static bool IsSystemStopRequested(void);

private:
  // Constructor is only used in init branch of Instance()
  Console();

  static std::shared_ptr<Console>& Instance();

  void ClearRXBuffer();

  void ClearTXBuffer();

  void RXCallback();

  void TXCallback();

  static std::shared_ptr<Console> instance;

  /**
   * serial connection
   */
  Serial pc;

  /**
   * receive buffer
   */
  char rxBuffer[BUFFER_LENGTH];

  /**
   * transmission buffer
   */
  char txBuffer[BUFFER_LENGTH];

  /**
   * is a system stop requested
   */
  bool sysStopReq = false;

  /**
   * flags for arrow key sequences. Arroy keys aren't in ASCII so we have to
   * process the the three key sequence
   */
  bool flagOne = false;
  bool flagTwo = false;

  /**
   * receive buffer index
   */
  uint8_t rxIndex = 0;

  /**
   * transmission buffer index
   */
  uint8_t txIndex = 0;
};
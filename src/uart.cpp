#include "uart.h"

size_t UART::available()
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    return this->serial->available();
#elif defined(BOARD_BW16)
    return Serial1.available();
#else
    return Serial.available();
#endif
}

void UART::begin(uint32_t baudrate)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W)
    this->serial = new SerialPIO(0, 1);
    this->serial->begin(baudrate);
#elif defined(BOARD_VGM)
    this->serial = new SerialPIO(this->tx_pin, this->rx_pin);
    this->serial->begin(baudrate);
#elif defined(BOARD_BW16)
    Serial1.begin(baudrate);
#else
    Serial.begin(baudrate);
#endif
}

void UART::clear_buffer()
{
    while (this->available() > 0)
    {
        this->read();
    }
}

void UART::flush()
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    this->serial->flush();
#elif defined(BOARD_BW16)
    Serial1.flush();
#else
    Serial.flush();
#endif
}

void UART::print(String str)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    this->serial->print(str);
#elif defined(BOARD_BW16)
    Serial1.print(str);
#else
    Serial.print(str);
#endif
}

void UART::printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    this->serial->printf(format, args);
#elif defined(BOARD_BW16)
    // not supported yet
#else
    Serial.printf(format, args);
#endif
    va_end(args);
}

void UART::println(String str)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    this->serial->println(str);
#elif defined(BOARD_BW16)
    Serial1.println(str);
#else
    Serial.println(str);
#endif
}

uint8_t UART::read()
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    return this->serial->read();
#elif defined(BOARD_BW16)
    return Serial1.read();
#else
    return Serial.read();
#endif
}

uint8_t UART::readBytes(uint8_t *buffer, size_t size)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    return this->serial->readBytes(buffer, size);
#elif defined(BOARD_BW16)
    return Serial1.readBytes(buffer, size);
#else
    return Serial.readBytes(buffer, size);
#endif
}

String UART::readStringUntilString(String terminator)
{
    String receivedData = "";
    unsigned long lastDataTime = millis();

    while (true)
    {
        // If no new line is received in the last 5 seconds, exit the loop
        if (millis() - lastDataTime >= 5000)
        {
            break;
        }

        // Read a line from serial input
        String line = this->readSerialLine();
        if (line.length() > 0)
        {
            receivedData += line;
            lastDataTime = millis();

            // Check if the terminator exists in the accumulated data
            int termIndex = receivedData.indexOf(terminator);
            if (termIndex != -1)
            {
                // Remove the terminator and any subsequent data
                receivedData = receivedData.substring(0, termIndex);
                break;
            }
        }
        delay(1);
    }

    receivedData.trim();
    return receivedData;
}

String UART::readSerialLine()
{
    String receivedData = "";

#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    receivedData = this->serial->readStringUntil('\n');
#elif defined(BOARD_BW16)
    while (Serial1.available() > 0)
    {
        char incomingChar = Serial1.read();
        if (incomingChar == '\n')
        {
            break;
        }
        receivedData += incomingChar;
        delay(1); // Minimal delay to allow buffer to fill
    }
#else
    while (Serial.available() > 0)
    {
        char incomingChar = Serial.read();
        if (incomingChar == '\n')
        {
            break;
        }
        receivedData += incomingChar;
        delay(1); // Minimal delay to allow buffer to fill
    }
#endif
    receivedData.trim();
    return receivedData;
}

#ifdef BOARD_VGM
void UART::set_pins(uint8_t tx_pin, uint8_t rx_pin)
{
    this->tx_pin = tx_pin;
    this->rx_pin = rx_pin;
}
#endif

void UART::set_timeout(uint32_t timeout)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    this->serial->setTimeout(timeout);
#elif defined(BOARD_BW16)
    Serial1.setTimeout(timeout);
#else
    Serial.setTimeout(timeout);
#endif
}

void UART::write(const uint8_t *buffer, size_t size)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    this->serial->write(buffer, size);
#elif defined(BOARD_BW16)
    Serial1.write(buffer, size);
#else
    Serial.write(buffer, size);
#endif
}
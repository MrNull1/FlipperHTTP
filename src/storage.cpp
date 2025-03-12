#include "storage.h"

bool file_begin()
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    if (!LittleFS.begin())
    {
        if (LittleFS.format())
        {
            if (!LittleFS.begin())
            {
                return false;
            }
        }
        return false;
    }
    return true;
#elif defined(BOARD_BW16)
    // skip for now
    return true;
#else
    if (!SPIFFS.begin(true))
    {
        return false;
    }
    return true;
#endif
}

void file_deserialize(JsonDocument &doc, const char *filename)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    File file = LittleFS.open(filename, "r");
#elif !defined(BOARD_BW16)
    File file = SPIFFS.open(filename, FILE_READ);
#endif
#ifndef BOARD_BW16
    deserializeJson(doc, file);
    file.close();
#else
    // skip for now
#endif
}

String file_read(const char *filename)
{
    String fileContent = "";
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    File file = LittleFS.open(filename, "r");
#elif !defined(BOARD_BW16)
    File file = SPIFFS.open(filename, FILE_READ);
#endif
#ifndef BOARD_BW16
    if (file)
    {
        // Read the entire file content
        fileContent = file.readString();
        file.close();
    }
#else
    // skip for now
#endif
    return fileContent;
}

void file_serialize(JsonDocument &doc, const char *filename)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    File file = LittleFS.open(filename, "w");
#elif !defined(BOARD_BW16)
    File file = SPIFFS.open(filename, FILE_WRITE);
#endif
#ifndef BOARD_BW16
    if (file)
    {
        serializeJson(doc, file);
        file.close();
    }
#else
    // skip for now
#endif
}

bool file_write(const char *filename, const char *data)
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    File file = LittleFS.open(filename, "w");
#elif !defined(BOARD_BW16)
    File file = SPIFFS.open(filename, FILE_WRITE);
#endif
#ifndef BOARD_BW16
    if (file)
    {
        file.print(data);
        file.close();
        return true;
    }
#else
    // skip for now
#endif
    return false;
}

size_t free_heap()
{
#if defined(BOARD_PICO_W) || defined(BOARD_PICO_2W) || defined(BOARD_VGM)
    return rp2040.getFreeHeap();
#elif defined(BOARD_BW16)
    return os_get_free_heap_size_arduino();
#else
    return ESP.getFreeHeap();
#endif
}
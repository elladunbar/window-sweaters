#pragma once
#include "extern.h"
#include "ApplicationServices/ApplicationServices.h"

#define DELAY_ASYNC_EXEC_ON_MAIN_THREAD(delay, code) {\
  dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^{\
    usleep(delay);\
    dispatch_async(dispatch_get_main_queue(), ^{\
      code\
    });\
  });\
}

static inline void debug(const char* message, ...) {
#ifdef DEBUG
  va_list va;
  va_start(va, message);
  vprintf(message, va);
  va_end(va);
#endif
}

static inline void error(const char* message, ...) {
  va_list va;
  va_start(va, message);
  vfprintf(stderr, message, va);
  va_end(va);
  exit(EXIT_FAILURE);
}

static inline  CFArrayRef cfarray_of_cfnumbers(void* values, size_t size, int count, CFNumberType type) {
  CFNumberRef temp[count];

  for (int i = 0; i < count; ++i) {
    temp[i] = CFNumberCreate(NULL, type, ((char *)values) + (size * i));
  }

  CFArrayRef result = CFArrayCreate(NULL,
                                    (const void **)temp,
                                    count,
                                    &kCFTypeArrayCallBacks);

  for (int i = 0; i < count; ++i) CFRelease(temp[i]);

  return result;
}

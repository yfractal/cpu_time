#include <ruby.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>

static inline double cpu_time()
{
#if defined(_WIN32)
    FILETIME  createTime;
    FILETIME  exitTime;
    FILETIME  kernelTime;
    FILETIME  userTime;

    ULARGE_INTEGER kernelTimeInt;
    ULARGE_INTEGER userTimeInt;

    GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime);

    kernelTimeInt.LowPart = kernelTime.dwLowDateTime;
    kernelTimeInt.HighPart = kernelTime.dwHighDateTime;
    userTimeInt.LowPart = userTime.dwLowDateTime;
    userTimeInt.HighPart = userTime.dwHighDateTime;

    return (double)(kernelTimeInt.QuadPart + userTimeInt.QuadPart);
#elif !defined(CLOCK_PROCESS_CPUTIME_ID)
    #include <sys/resource.h>
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_stime.tv_sec + usage.ru_utime.tv_sec + ((usage.ru_stime.tv_usec + usage.ru_utime.tv_usec) / 1000000.0);
#else
    struct timespec clock;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &clock);
    return clock.tv_sec + (clock.tv_nsec / 1000000000.0);
#endif
}

static VALUE
rb_cpu_time()
{
    double time = cpu_time();

    return rb_float_new(time);
}

void
Init_cpu_time(void)
{
    VALUE class = rb_define_class("CPUTimeTimer", rb_cObject);
    rb_define_singleton_method(class, "cpu_time", rb_cpu_time, 0);
}

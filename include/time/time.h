/* Copyright (c) 2017 Arrow Electronics, Inc.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Apache License 2.0
 * which accompanies this distribution, and is available at
 * http://apache.org/licenses/LICENSE-2.0
 * Contributors: Arrow Electronics, Inc.
 */

#ifndef ARROW_TIME_TIME_H_
#define ARROW_TIME_TIME_H_

#if defined(__cplusplus)
extern "C" {
#endif


#include <config.h>
#if !defined(__XCC__)
# if defined (__STRICT_ANSI__)
#  undef __STRICT_ANSI__
#  include <time.h>
#  define __STRICT_ANSI__
# else
#  include <time.h>
#  include <sys/time.h>
# endif
#else
# if defined(__XCC__)
#  include <qcom_time.h>
#  if defined(time)
#    undef time
#  endif
struct timezone { int zone; };
time_t time(time_t *timer);
int gettimeofday(struct timeval *tv, struct timezone *tz);
# endif
#endif

#if defined (_ARIS_)
#if defined(_TIMEVAL_DEFINED)
#include <nxd_bsd.h>
#else
# include <sys/time.h>
#endif
int stime(time_t *timer);
#endif

int msleep(int m_sec);
void get_time(char *ts);
time_t build_time();
#if !defined(TARGET_NUCLEO_F401RE)
void set_time(time_t t);
#endif


#if ( defined(_TIMEVAL_DEFINED) && !defined(__BSD_VISIBLE) ) || defined(__NO_STD__) || defined(ETH_MODE) || defined(__senseability__)

#define timerclear(tvp)     ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timerisset(tvp)     ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp)                 \
        (((tvp)->tv_sec == (uvp)->tv_sec) ?             \
                ((tvp)->tv_usec cmp (uvp)->tv_usec) :           \
                ((tvp)->tv_sec cmp (uvp)->tv_sec))
#define timeradd(tvp, uvp, vvp)                     \
        do {                                \
            (vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;      \
            (vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;   \
            if ((vvp)->tv_usec >= 1000000) {            \
                (vvp)->tv_sec++;                \
                (vvp)->tv_usec -= 1000000;          \
            }                           \
        } while (0)
#define timersub(tvp, uvp, vvp)                     \
        do {                                \
            (vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;      \
            (vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;   \
            if ((int)(vvp)->tv_usec < 0) {               \
                (vvp)->tv_sec--;                \
                (vvp)->tv_usec += 1000000;          \
            }                           \
        } while (0)

#endif

#if defined(__cplusplus)
}
#endif

#endif // ARROW_TIME_TIME_H_

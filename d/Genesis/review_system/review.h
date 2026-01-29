/*
 * This file is to be included by all the files concerened 
 * with reviews.
 */

#define PATH "/d/Debug/debugwiz/"

/*
 * This include is used to define GLOBAL_READ - all players with
 * global read.  These are presumed to be reviewers.
 */

#ifdef TINTIN_AND_MRPR_OUT_TO_GET_THE_REVIEWERS_BUT_COULD_HAVE_PUT_THE_DEFINE_BELOW_IN_CONFIG_SYS_LOCAL_AND_NO_ONE_WOULD_EVEN_KNOW_THEY_HAD_CHANGED_IT
#include "/config/sys/local.h"
#endif

#ifndef GLOBAL_READ
#define GLOBAL_READ (m_indexes("/secure/master"->query_global_read()))
#endif

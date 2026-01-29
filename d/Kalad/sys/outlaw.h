/*
   /d/Kalad/sys/outlaw.h
   
   Macros for recognizing, adding and removing outlaws in Kalad.
   
   Fysix@Genesis, Nov 1997
 */
#ifndef _KALAD_OUTLAW_DEFS
#define _KALAD_OUTLAW_DEFS

#define OUTLAW_FILE "/d/Kalad/obj/outlaw"

#define IS_OUTLAW(x)    OUTLAW_FILE->query_outlaw(x)
#define ADD_OUTLAW(x)   OUTLAW_FILE->add_outlaw(x)
#define UNOUTLAW(x)     OUTLAW_FILE->remove_outlaw(x)
#define OUTLAWS         OUTLAW_FILE->query_outlaws()

#endif

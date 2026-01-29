#ifndef TEMPLE_DEF
#define TEMPLE_DEF

#include "../local.h"

#define TEMPLE      (NERAKA + "temple/")
//#define TEMPLE      (NERAKA + "temple_v2/")

#ifdef WHITE
#undef WHITE
#endif

#ifdef BLACK
#undef BLACK
#endif

#ifdef GREEN
#undef GREEN
#endif

#ifdef BLUE
#undef BLUE
#endif

#ifdef RED
#undef RED
#endif

#define LVLTWO      TEMPLE + "lvl2/"
#define LVLTHREE    TEMPLE + "lvl3/"
#define LVLFOUR     TEMPLE + "lvl4/"
#define LVLFIVE     TEMPLE + "lvl5/"
#define DUNGONE     TEMPLE + "dung1/"
#define DUNGTWO     TEMPLE + "dung2/"
#define DUNGTHREE   TEMPLE + "dung3/"
#define WHITE       TEMPLE + "white/"
#define BLACK       TEMPLE + "black/"
#define GREEN       TEMPLE + "green/"
#define BLUE        TEMPLE + "blue/"
#define RED         TEMPLE + "red/"

#define DOOR        TEMPLE + "doors/"
#define KEY         TEMPLE + "keys/"

#define T_LEADER        1
#define T_INQUISITOR    2
#define T_MENTOR        3
#define T_LIBRARIAN     4
#define T_HERBMASTER    5

#define T_HIGH_PRIEST   6
#define T_PRIEST        7
#define T_INITIATE      8

#define T_PILGRIM       9

#define T_GENERAL       10
#define T_HIGH_OFFICER  11
#define T_OFFICER       12
#define T_SOLDIER       13
#define T_RECRUIT       14

#define T_WIZARD        15

#define T_TEAMLEADER    1
#define T_TEAMMEMBER    2

#endif

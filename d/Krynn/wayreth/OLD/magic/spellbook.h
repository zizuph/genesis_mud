#ifndef _SPELLBOOK_H_
#define _SPELLBOOK_H_

#define HEADER   "     ______________________________  ______________________________\n" + \
                 "  __/                              \\/                              \\__\n"

#define SUB_HEADER    " ||:|                              |:  Description:                |:||\n"
#define BLANK    " ||:|                              |:                              |:||\n"

#define BLANK_L  " ||:|                              "

#define BLANK_R  "|:                              |:||\n"

#define BOTTOM   " ||:|_____________________________ |: _____________________________|:||\n" + \
	         " ||/______________________________\\|:/______________________________\\||\n" + \
	         " |_______________________________  `'  _______________________________|\n" + \
	         "                                 `----'\n\n"

#define CMD                     ("/cmd/std/command_driver")
#define ACTOR(x, y, z)          CMD->actor(x, y, z)
#define TARGET(x, y)            CMD->target(x, y)
#define TARGETBB(x, y)          CMD->targetbb(x, y)
#define ALL(x)                  CMD->all(x)
#define ALLBB(x)                CMD->allbb(x)
#define ALL2ACT(x, y, z)        CMD->all2act(x, y, z)
#define ALL2ACTBB(x, y, z)      CMD->all2actbb(x, y, z)
#define GENERAL(x, y)           general(x, y)
#define GENERALBB(x, y)         generalbb(x, y)
#define TASK_EASY		TASK_SIMPLE + 150

#endif _SPELLBOOK_H_




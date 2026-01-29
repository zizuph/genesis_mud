/*
 *
 *  /d/Gondor/common/lib/clock.h
 * 
 *  NOTE: Use of this file is depreciated.
 *  Please include /d/Gondor/sys/clock.h instead.
 *
 *	Ring Quest stage definitions
 *
 *	RQ_GANDALF_IN_BAGEND,		3018,  Apr 12th.
 *	RQ_OSGILIATH_ATTACK,		3018,  Jun 20th.
 *	RQ_LEFT_HOBBITON,		3018,  Sep 23rd.
 *	RQ_ARRIVED_IN_RIVENDELL,	3018,  Oct 20th.
 *	RQ_LEFT_RIVENDELL,		3018,  Dec 25th.
 *	RQ_ARRIVED_IN_LOTHLORIEN,	3019,  Jan 16th.
 *	RQ_LEFT_LOTHLORIEN,		3019,  Feb 16th.
 *	RQ_LEFT_HENNETH_ANNUN,		3019,  Mar  8th.
 *	RQ_ENTERED_MORDOR,		3019,  Mar 15th.
 *	RQ_QUEST_ENDED,			3019,  Mar 25th.
 */
#ifndef GONDOR_RING_QUEST_DEFS
#define GONDOR_RING_QUEST_DEFS
#define RQ_GANDALF_IN_BAGEND	  1
#define RQ_OSGILIATH_ATTACK       5
#define RQ_LEFT_HOBBITON	 10
#define RQ_ARRIVED_IN_RIVENDELL	 18
#define RQ_LEFT_RIVENDELL	 20
#define RQ_ARRIVED_IN_LOTHLORIEN 28
#define RQ_LEFT_LOTHLORIEN	 30
#define RQ_LEFT_HENNETH_ANNUN	 40
#define RQ_ENTERED_MORDOR	 50
#define RQ_QUEST_ENDED		100
#define RQ_QUEST_FULFILLED     1000

#define RQ_STAGE_WAR		 RQ_LEFT_HENNETH_ANNUN
#define RQ_OSGILIATH_BROKEN      RQ_OSGILIATH_ATTACK
#define RQ_OSGILIATH_FIXED       RQ_QUEST_ENDED
#endif


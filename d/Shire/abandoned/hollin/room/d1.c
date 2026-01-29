/*
 * File: /d/Shire/hollin/room/d1.c
 */

#include "defs.h"
inherit HOLLIN_BASE;
#define HOLLIN_DIR "/d/Shire/hollin/"
#define HOLLIN_ROOM HOLLIN_DIR +"room/"
create_hollin_room()
{
	set_extraline("The road looks like it's rarely used, overgrown "+
	  "by small bushes here and there.\n");

	add_exit(HOLLIN_ROOM + "d2", "southeast");
	//add_exit(HOLLIN_DIR + "ruins1", "northwest");

}

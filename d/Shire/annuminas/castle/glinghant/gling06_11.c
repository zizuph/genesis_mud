
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit GLINGHANT_BASE_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";

void create_glinghant_room() {}


/*
 * cavern vars and routines
 */
int alarm_id;

// We use 'create_Room' instead of 'create_shire_room' because
// this is an indoors room
public void create_room()
{
    set_long("@@intro@@" + "@@my_long@@");
//    add_my_desc("You stand at the top of a great marble stairway, " +
//			"descending into the great hall of the Glinghant.\n");
    add_prop(ROOM_I_LIGHT, 1);    
	add_exit(GLINGHANT_BASE_ROOM + "gling02_01", "northwest");
	add_exit(GLINGHANT_BASE_ROOM + "gling02_02", "north");
	add_exit(GLINGHANT_BASE_ROOM + "gling02_03", "northeast");
}

string intro()
{
    return "You stand in the knee deep pool just before " +
		"the statue. ";
}
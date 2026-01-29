
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit GLINGHANT_BASE_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";

/*
 * cavern vars and routines
 */
int alarm_id;

// We use 'create_Room' instead of 'create_shire_room' because
// this is an indoors room
public void create_glinghant_room()
{
    set_long("@@intro@@" + " @@my_long@@");
//    add_my_desc("You stand at the top of a great marble stairway, " +
//			"descending into the great hall of the Glinghant.\n");
    add_prop(ROOM_I_LIGHT, 1);    
	add_exit(CASTLE_GLINGHANT_DIR + "gling02_01", "west");
	add_exit(CASTLE_GLINGHANT_DIR + "gling02_03", "east");
	add_exit(CASTLE_GLINGHANT_DIR + "gling03_02", "northwest");
	add_exit(CASTLE_GLINGHANT_DIR + "gling03_03", "north");
	add_exit(CASTLE_GLINGHANT_DIR + "gling03_04", "northeast");
	add_exit(CASTLE_GLINGHANT_DIR + "gling01_01", "southeast");

}

string intro()
{
    return "You stand in the southwestern corner, the water has " +
    	"receded here.";
}
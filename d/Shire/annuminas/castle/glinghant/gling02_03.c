
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
    set_long("@@intro@@" + " @@my_long@@");
    add_prop(ROOM_I_LIGHT, 1);    
	add_exit(CASTLE_GLINGHANT_DIR + "gling02_02", "west");
	add_exit(CASTLE_GLINGHANT_DIR + "gling02_04", "east");
	add_exit(CASTLE_GLINGHANT_DIR + "gling01_01", "south");
	add_exit(CASTLE_GLINGHANT_DIR + "gling03_04", "north");
	add_exit(CASTLE_GLINGHANT_DIR + "gling03_03", "northwest");
	add_exit(CASTLE_GLINGHANT_DIR + "gling03_05", "northeast");

}

string intro()
{
    return "You're standing at the bottom of the marble staircase, " +
    	"just to the south.";
}
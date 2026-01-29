
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit GLINGHANT_BASE_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";


public void create_glinghant_room()
{
    set_long("@@intro@@" + "@@my_long@@");
//    add_my_desc("\n");
    add_prop(ROOM_I_LIGHT, 1);    
	add_exit(CASTLE_GLINGHANT_DIR + "gling02_02", "northwest");
	add_exit(CASTLE_GLINGHANT_DIR + "gling02_03", "north");
	add_exit(CASTLE_GLINGHANT_DIR + "gling02_04", "northeast");
}

string intro()
{
    return "You stand at the top of a great marble stairway, " +
		"descending into the great hall of the Glinghant. ";
}
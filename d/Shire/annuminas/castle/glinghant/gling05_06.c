
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
public void create_room()
{
    set_long("@@long_intro@@" + "@@my_long@@");
  //  add_my_desc("");
    add_prop(ROOM_I_LIGHT, 1);    
	add_exit(GLINGHANT_BASE_ROOM + "gling06_01", "northwest");
	add_exit(GLINGHANT_BASE_ROOM + "gling06_02", "north");
	add_exit(GLINGHANT_BASE_ROOM + "gling06_03", "northeast");
	add_exit(GLINGHANT_BASE_ROOM + "gling05_05", "west");
	add_exit(GLINGHANT_BASE_ROOM + "gling05_07", "east");
	add_exit(GLINGHANT_BASE_ROOM + "gling04_06", "south");
	add_exit(GLINGHANT_BASE_ROOM + "gling04_05", "southwest");
	add_exit(GLINGHANT_BASE_ROOM + "gling04_07", "southeast");


}

string
long_intro() 
{
	return "You're standing knee deep within the mirror pool, just before " +
		"the statue. ";
}



int
query_vinecreeper()
{
	if (present(CASTLE_GLINGHANT_NPC + "_vinecreature_",TO))
	{
		return 1;
	}
	return 0;
}
/*

 Inside of the caravan wagon,

 by Udana, 03/06

*/


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <composite.h>

inherit CARAVAN + "wagon_base.c";

inherit "/d/Terel/std/room_tell.c";

int create_inside(object wagon, int direction)
{
	int tmp = ::create_inside(wagon, direction);
	 /* Orhton, dwarf improving armours with fur */
	clone_here(NPC + "fur_man")->move(TO);
	return tmp;
}
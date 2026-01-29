/*
 * ASH.c
 * 
 * This object is only placed in a room after a player/npc has been
 * killed with the spell 'Telberin's Fire and Ice'
 *
 * by Alaron
 */

#include "../telberin.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit "/std/object";

string dead_race;

void
create_object()
{
    set_name("ash");
    set_adj("dark");
    set_short("pile of dark ash");
    
    set_long("It is a pile of dark ash. Faintly outlined in the pile "+
	     "of charred ember you can make out what might be the powdered "+
             "remains of a @@drace@@ skull.\n");
    
    add_prop(OBJ_M_NO_GET,"@@pickup@@");
    add_prop(OBJ_I_VOLUME,3);
    add_prop(OBJ_I_WEIGHT,1);
}

string
drace()
{
    if (dead_race == "dwarf")
	return "dwarven";
    else if (dead_race == "elf")
	return "elven";
    else if (dead_race == "human")
	return "human";
    else if (dead_race == "gnome")
	return "gnomish";
    else if (dead_race == "goblin")
	return "goblin";
    else return dead_race;
}

void
set_dead_race(string x)
{
    dead_race = x;
}

string
pickup()
{
    set_alarm(1.0,0.0,"remove_me");
    return "You attempt to pick up the ashes but they drift out of "+
	"your hand into the wind.\n";
}

void
remove_me()
{
    tell_room(environment(this_object()),
	      "The ashes disappear into the air.\n");
    remove_object();
}

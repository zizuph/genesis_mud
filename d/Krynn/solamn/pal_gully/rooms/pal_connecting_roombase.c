/* 
 * The base indoor room for road to the caves past the moors
 * west of Palanthas.
 * Modified from Mortis 03.2015 by Mirandus
 */
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include CLOCKH

/* Inherit the Ansalon room */
inherit R_FILE
inherit RDIR + "connecting_tells.c";

#define CREATE "create_pal_connecting_room"
#define RESET  "reset_pal_connecting_room"

/*
 * This function is called from the main Krynn room. It checks
 * whether or not the room should be reset.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
	return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);

    add_item(({"skirmishes", "fighting", "skirmish"}), "Dewar dwarves "
    +"seem to be chasing after Aghar dwarves in an "
    +"attempt to kill them.  The Aghar are fighting back as best they "
    +"can but seem to more be trying to escape than "
    +"actually hurt anyone.\n");
    add_item(({"scuff marks", "skid marks", "marks",
	"spots", "spot"}), "Spots on the "
    +"ground that have been left by falling dwarves in "
    +"their attempt to either escape or kill the other.\n");
    add_item(({"blood", "blood stains", "stains","bloodstains",
	"bloostain"}), "Stains from blood "
    +"lie on the ground in places where unfortunate "
    +"dwarves were not able to escape.\n");
	add_item(({"road", "roads", "floor", "ground", "dirt", "dust","path"}),
	"The road is made of compacted dirt. Less a road and more a path, it "
	+"leads toward a cavern and a mine in the distance. There are scuff "
	+"marks and stains on the ground.\n");
	add_item(({"dewar", "dewar dwarf", "dewar dwarves"}), "Off in the "
	+"distance you see a Dewar dwarf. The Dewar were cast out "
    +"due to their insanity. Now forced to live in places no other "
    +"dwarf would live.\n");
	add_item(({"dwarves", "dwarfs"}), "There are Aghar and Dewar dwarves "
	+"in the distance. Every once and a while they run past.\n");
	add_item(({"aghar", "aghar dwarf", "aghar dwarves"}), "Off in the "
	+"distance you see dopey looking dwarves running very fast often "
	+"holding petrified rats. They are the Aghar who are forced to live "
	+"in places no other dwarf would live\n");
    
    set_tell_time(90);
    add_tell("@@get_tells@@" + "\n");
    
    add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_S_MAP_FILE, "pal_gully.txt");
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}

int
smell_air(string str)
{
    
    notify_fail("Smell what?\n");
    if (str != "air" && str != "the air" && str != "area" 
    && str != "the area" && str != "garbage"   && str != "refuse")
    return 0;
    
    else
    say(QCTNAME(this_player()) +
    " smells the area around them subtly. You notice them cringe slightly.");
    write("You smell the air around you. The strong scent of fresh blood "
	+"fills your nostrils causing you to cringe slightly.\n");
    return 1;
}


public void
init()
{
    ::init();
    add_action(smell_air, "smell");
}
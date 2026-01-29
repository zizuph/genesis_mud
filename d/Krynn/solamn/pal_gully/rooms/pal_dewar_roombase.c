/* 
 * The base indoor room for dewar dwarves in caves past the moors
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
inherit RDIR + "dcave_tells.c";

#define CREATE "create_pal_dewar_room"
#define RESET  "reset_pal_dewar_room"

string smell_air(string str);

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

    add_item(({"walls", "wall", "the walls", "the wall"}),"Smooth and "
    +"well carved. Oil lanterns are attached to the walls to "
    +"provide light throughout the cavern system.\n");
    add_item(({"lanterns","oil lantern","lantern", "oil lanterns",
	    "light", "lights", "lamps", "lamp"}),
    "Small but well made, these oil lanterns are attached to the wall "
    +"to provide light throughout the cavern. They are fed by an "
    +"intricate piping system so that they never go out.\n");
    add_item(({"pipe system","system","intricate system", "oil"}),
    "Attached to the walls through the system, these pipes carry "
    +"liquid oil to the oil lanterns attached to the walls. In this way "
    +"the dwarves only need to fill one oil drum in order to "
    +"keep the entire area lit. Or, it can be used "
    +"to blow the whole place up.\n");
	add_item(({"ceiling", "ceilings", "vaulted ceiling", 
    "vaulted ceilings"}), "High arched ceilings allow "
    +"for ample space to move about "
    +"in this cavern system. They are well carved and intricate.\n");
    add_item(({"floor", "floors","rock"}), "The floors of the cavern are smooth "
    +"and covered in a fine layer of rock dust. Blood stains are "
    +"visible as are footprints from the inhabitants of this system.\n");
	add_item(({"dust", "layer of dust", "fine layer of dust", "fine dust"}),
	"A fine layer of dust has settled over the entire floor. Blood stains "
	+"and foot prints are visible in the dust\n");
	add_item(({"foot print", "foot prints", "print", "prints","footprints",
	"footprint"}), "Footprints "
	+"from the inhabitants of this cavern system are visible in the dust.\n");
	add_item(({"blood","stains","bloodstains", "blood stains", "blood pools",
	"blood pools", "stains"}),
	"Crimson blood stains in the rock are impossible to miss. They hint at "
	+"something much more nefarious and evil about these caverns.\n");
	
	
	
    
    set_tell_time(90);
    add_tell("@@get_tells@@" + "\n");
    
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
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
    && str != "the area" && str != "blood"   && str != "rocks")
    return 0;
    
    else
    say(QCTNAME(this_player()) +
    " smells the area around them before wrinkling their nose with "
	+"displeasure.");
    write("You smell the air and are overwhelmed with the acridness "
	+"of all the blood in the air. You wrinkle your nose in displeasure.\n");
    return 1;
}


public void
init()
{
    ::init();
    add_action(smell_air, "smell");
}

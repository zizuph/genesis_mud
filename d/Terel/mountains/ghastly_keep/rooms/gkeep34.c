/* /d/Terel/mountain/ghastly_keep/gkeep34.c
 *
 * One of the rooms in the Ghastly Keep.
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth
 *  30/04-17                   Fixed a bug with the treasure spawing   Znagsnuf
 *  04/05-17                   Remove the clone_unque to the dragon    Znagsnuf 
 */

#include "defs.h";
#include <money.h>

inherit GKEEP_STD_ROOM;

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    update_longdesc();

    set_short("Behind the dragon's lair");
    set_long("Spooky doesn't quite cover it and eerie is an understatement. "
    	    + "The scent of death is laden into those gusts that push "
    	    + "impetuously against the sentinel stone. The crumbling cracked "
    	    + "rocks are layered on top of each other, caked with mosses "
    	    + "and dried up blood. You can only imagine the bloodshed "
    	    + "that has been going on in this room and soaked into the moss "
    	    + "covered floor these past centuries.\n");

    add_item( ({ "scent", "stone" } ), "The scent of death is laden into "
           + "those gusts that push impetuously against the sentinel stone.\n");

    add_item( ({ "rocks", "moss" } ), "Crumbled cracked rocks are layered "
          + "on top of each other, caked with moss and dried up blood.\n");

    add_item( ({ "cracked", "layer" } ), "Crumbled cracked rocks, are layered "
          + "on top of each other, caked with moss and dried up blood.\n");

    add_item( ({ "floor", "bloodshed" } ), "The blood has been soaked into "
              + "the moss covered floor.\n");

    add_item( ({ "moss", "green moss", "green mosses", "mosses" }), "Green moss "
               + " covers these rocks.\n");

    add_item( ({ "bloods", "dried blood", "blood" }), "Blood, dark as crimson, "
               + "is spread everywhere.\n");
 
    add_exit(GKEEP + "gkeep32", "northwest");

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    update_longdesc();
}

/*
 * Function name: add_treasure()
 * Description  : Resets the room
 */
void
add_treasure()
{  
    MONEY_MAKE(random(10),"platinum")->move(TO);
    MONEY_MAKE(random(50),"gold")->move(TO);
}
/*
 * Component shop room
 *
 * by Arman 
 */


#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include "component_list.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

inherit TOWERROOM;

#define NPC "/d/Krynn/wayreth/npc/"

object gTrainer;

void
reset_tower_room()
{
   if (!gTrainer)
    {
        gTrainer = clone_object(NPC + "herbalist");
        gTrainer->move(TO);
    }
   return;
}

void
create_tower_room()
{
    set_short("Component shop");
    set_long("This is the component shop located in the Tower " +
        "of High Sorcery. Here, Magi can purchase herbs necessary " +
        "for spell-casting. \n");

    AI(({"wall","walls"}), "The walls of this component shop " +
        "are kept clean. It seems that all the components are " +
        "kept behind the counter.\n");
    AI("counter","The counter is a marble white, made of a " +
        "finely polished substance.\n");
    AI("ceiling","The ceiling is plain, with no distinguishing " +
        "features.\n");
    AI("floor","The floor is of little interest. The only thing " +
        "noteworthy is its cleanliness.\n");

   reset_tower_room();

    add_exit(WTOWER + "lobby", "north", 0);

}


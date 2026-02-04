/*
 * Revised:
 *  Jan 2021 - Lucius: Moved Dark One npc into mansion directory.
 */
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player
#define TO             this_object

object ob;

void
reset_room()
{
    
    if (ob && !ob->id("corpse"))
	return;
    ob=clone_object(MANSION+"mon/darkone.c");
    ob->move_living("M", TO());
}

void
create_room()
{
    set_short("Battlefield");
    set_long(BS("You have arrived at the scene of Confrontation. The very "
    + "presence of the Dark One blackens the sky, but LightBringer burns "
    + "with a holy brilliance that pushes back even the darkness of the One. "
    + "The charred ground smokes and writhes underneath your feet, and the "
    + "silence of death itself reigns over the ruined earth.\n"));

    add_exit(MANSION +"battlefield_1","south",0,1);
    reset_room();
}


/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
inherit "/d/Avenir/inherit/sair_wall";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Center");
    set_long("A hall of stone, carved magnificently from the living "+
	"rock of this place. Four columns support the hall, made into "+
	"the images of serpents. The ceiling forms a vault, which has "+
	"been engraved with a demonic face. In the center of the hall "+
	"is a fire pit that heats and lights the area, but with only a "+
	"faint flickering glow.\n");

    add_item(({"fire pit", "fire", "pit"}),
	"It is lit with coal. It is very hot, but provides little light.\n");
    add_item(({"face", "demonic face", "ceiling"}),
	"Engraved upon the ceiling is a horrible visage, a nightmare " +
	"made in stone. It must be an entity worshipped by the beings " +
	"that carved this hall. The face looks like that of an animal, " +
	"perhaps a goat. Its mouth gapes open, displaying hook-like " +
	"teeth. Its eyes only slits. Its head crowned by many strange " +
	"and differing horns, some twisted, others spiral or straight. " +
	"From the face are six small talon-like claws, that circle it. " +
	"Out from the talons reach four bat-like wings. Light from " +
	"the fire below it seems almost to bring it to life.\n");
    add_item(({"wall", "walls"}),
    "The walls of this hall have been carved with exquisite skill "+
    "from the living stone.\n");

	
    IN; LIGHT;

    set_sair_dest(({L2+"add/t36", L4+"center", L2+"center"}));  
    add_sair_wall();   


    add_exit(L1 + "s5", "south");
    add_exit(L1 + "n1", "north");
    add_exit(L1 + "e1", "east");
    add_exit(L1 + "w1", "west");

    add_npc(MON + "lizard", 1);
    add_npc(MON + "dark_elf", 3);
}


public void
init()
{
    ::init();
    sair_init();  
}


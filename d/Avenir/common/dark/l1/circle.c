/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Circle");
    set_long("This large cavern has been cut carefully from the " +
	     "stone. The ceiling forms a polished dome, the floor " +
	     "is also polished, being inset with a large circle. " +
	     "In the center of the circle is a small dais, made from " +
	     "some black stone. Black iron torch-holders are set into the " +
	     "stone about the circle.\n");

    add_item("crystal", "It is beautiful rock crystal, it forms many "+
			 "strange shapes and shines a variety of hues.\n");
	add_item(({"circle", "floor"}),
			 "A large circle has been inset in the floor "+
			 "using a contrasting pale stone.\n");
	add_item("ceiling", "It is domed and polished to a high sheen.\n");
	add_item(({"dais", "small dais", "altar"}), 
			 "It is a small dais a few hands-high. It was probably an altar of some sort.\n");
	add_item(({"torch holders", "torch holders"}), 
			 "They are made of iron, and blackened with soot. "+
			 "They appear to have held torches at one time.\n");

    IN; LIGHT;

    add_exit(L1 + "se4c", "southwest");
	
	add_npc(MON + "maivia", 1);
	add_npc(MON + "dark_elf", 2);
}

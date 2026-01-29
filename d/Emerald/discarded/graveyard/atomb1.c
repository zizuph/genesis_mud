/*
 * ATOMB1.c
 * 
 * Tomb inside the graveyard in Emerald. Players reach this 
 * dark, spooky spot by typing 'crawl through opening' outside the
 * tomb where there's an opening because the door is old and falling
 * off.
 *
 * by Alaron July 30, 1996
 */

#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Dark Tomb");
    set_long("   The darkness pushes in upon the tomb, completely "+
	     "blotting out any and all light. The cold, stagnant air "+
	     "in the tomb sends a chill up your spine. The frigid stone "+
	     "walls are covered with moisture, mildew and cobwebs "+
	     "hanging from the corners so dense they look like thick "+
	     "white blankets. In the corner of the dark chamber lies "+
	     "an enormous stone coffin, its sides decorated with "+
	     "detailed carvings of snakes and scorpions from top to "+
	     "bottom. Scanning the room left to right you suddenly "+
	     "notice something overhead that you had almost missed...\n"+
	     "   There, hanging from the ceiling by rotting iron chains and "+
	     "hooks are seven skeletons. Each of the skeletons, "+
	     "apparent victims of some perverse ritualistic murder, have a "+
	     "silver dagger embedded in their spines; their eyeless "+
	     "sockets examine the floor beneath "+
	     "in a dejected pose. Worms and snakes "+
	     "crawl in and out of the spaces between their bones. Massive "+
	     "nets of gray cobweb hook from their spines to the corner wall "+
	     "where hundreds of thick, black spiders scurry about.\n"+
	     "   There is an ancient, broken door leaning against a small "+
	     "opening in the southern wall. There is a small amount of "+
	     "dim light filtering through.\n");

    add_prop(ROOM_I_INSIDE, 1);
    DARK;

    add_item( ({"door",  "opening", "ancient door", "broken door",
		"south wall", "southern wall", "dim light", "light"}),
	     "   The ancient, broken door leaning against the opening "+
	     "in the south wall has long since fallen off of its "+
	     "rusted iron hinges. Now it does nothing more than "+
	     "lean precariously on the outside of the tomb, covering "+
	     "enough of the opening to prevent the light from "+
	     "spilling into the chamber.\n");
    add_item( ({"sides", "walls"}),
	     "   The thick stone sides of the coffin are completely covered "+
	     "by carved decorations of writhing snakes and stinging "+
	     "scorpions.\n");

    add_item( ({"coffin", "stone coffin", "enormous coffin",
		"enormous stone coffin"}),
	     "The huge stone coffin is probably taller than the "+
	     "tallest elf alive, and wider than some of the strongest "+
	     "dwarves that ever lived. You can't help but wonder what "+
	     "manner of creature would be large enough to occupy a "+
	     "casket such as this. Even more, you wonder what manner of "+
	     "creature brought about the death of something this size.\n");

    add_item( ({"cobwebs", "walls", "stone walls", "cobweb", "spiders",
		"worms"}),
	     "Cobwebs fill the entire tomb with their mirky gray and white "+
	     "presence, attaching themselves everywhere, blanketing the "+
	     "entire room. Thick, black spiders scurry across the webs "+
	     "and go about their business while wet, slimy worms wriggle their "+
	     "way across the floors and out of little cracks in the walls "+
	     "avoiding the cobwebs.\n");

    add_item( ({"skeletons", "skeleton", "hanging skeletons", "dead people",
		"ceiling", "up", "far wall"}),
	     "Hanging from a section of the joining piece between the "+
	     "ceiling and the far wall are seven large skeletons. They "+
	     "are very, very tall and incredibly thick-boned. Their "+
	     "skulls are larger than any you've seen and the bones in "+
	     "their fingers come to a long, sharp point. Each of the "+
	     "hanging skeletons contains a silver dagger buried halfway "+
	     "into the spinal column through the front of the ribcage. "+
	     "Thick cobwebs hang loosely from their backs and attach "+
	     "to the far wall, providing playgrounds for scurrying black "+
	     "spiders. Thick, wet worms squirm in and out of the spaces "+
	     "between the bones of the skeletons, almost making it appear "+
	     "as though the skeletons had flesh - moving flesh!\n");

    add_exit(GRAVEYARD_DIR + "graveyard7", "south");
    reset_euid();
    clone_object(GRAVEYARD_DIR + "obj/atome")->move(this_object(),1);
}


init()
{
    ::init();
    add_action("mask_exa","exa");
    add_action("mask_exa","examine");
    add_action("mask_exa","look");
    add_action("mask_exa","l");
}

int
mask_exa(string str)
{
    if (!random(8))
    {
	reset_euid();
	write("While looking about the tomb you step through a large "+
	      "cobweb. Its covered with spiders!!\n");
	say(QCTNAME(this_player())+" steps through a large cobweb "+
	    "while looking about the tomb. Its covered with "+
	    "spiders!!\n");
	clone_object(GRAVEYARD_DIR+"obj/spider_ob")->move(this_player(),1);
    }
    return 0;
}

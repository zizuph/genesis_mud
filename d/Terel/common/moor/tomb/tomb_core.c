// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc
/* from the imagination of Lord Sorgum ;)  */

#include "/d/Terel/include/Terel.h"
inherit MOOR_DIR +"tomb/tomb_base";
#include "../local.h"


int 
test_exit()
{
    object zombie = present("zombie", TO);
    
	if (zombie)
	{
        if (random(3) == 0)
		{
            write("The "+ zombie->short() +" prevents you from going in "+
                "that direction.\n");
			say(QCTNAME(zombie) + " stops " + QTNAME(TP) +" from leaving.\n", 
                ({ TP, zombie }));
            return 1;
		}
	else return 0;
	}
	
	return 0;
}


void
create_room()
{
	::create_room();
	
    add_npc(MOBDIR +"dweller3", 2);
    add_npc(MOBDIR +"hound", 2);
	
    set_short("Tomb core");
    set_long(
    "Spread out before you " +
	"is a vast fungus-encrusted shore lighted by a belching column of " +
	"sickly green flame and washed by a wide oily river flowing forth " +
	"from a frightful abyss. The viscous vegetation glitters green " +
	"in the chaotic glare. You hear the insidious lapping of the " +
	"grimy water against the shore.\n"
    );

    add_item(({"column", "flame", "green flame", "abyss"}), 
    "The sickly green flaming column sprouts volcanically from " +
    "depths which are profound and inconceivable. The flames coat the " +
	"stone walls with venomous verdigris.\n"
    );

    add_item(({"slime", "grime", "water", "river", "verdigris"}),
	"The water is beyond disgusting. It is oily and grimy with an "+
    "unsettling viscosity the color of verdigris.\n"
    );
	
    add_item(({"shore", "fungus", "vegetation"}), 
	"The shore is composed of viscous looking vegetation cast in an " +
	"eerie green light by the leprous fire.  Titanic toadstools darkly " +
	"discolored by the slimy water grow among the the vegatation and " +
	"other fungus.\n"
    );

 
    add_exit("under_tomb02", "south", test_exit); // to tomb dweller area
    add_exit("grime_river", "north", test_exit);   // to Benton 
}

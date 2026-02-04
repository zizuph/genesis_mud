inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

void
create_room()
{
    set_short("Tomb core");
    set_long(
        "The damp stone passage grows broader.  Spread out before you " +
	"is a vast fungus-encrusted shore lighted by a belching column of " +
	"sickly green flame and washed by a wide oily river flowing forth " +
	"from a frightful abyss.  The viscous vegetation glitters green " +
	"in the chaotic glare.  You hear the insidious lapping of the " +
	"sunless grimy water against the shore.\n"
    );

    add_item(({"column", "flame", "green flame"}), 
        "The sickly green flaming column sprouts volcanically from " +
        "depths which are profound and inconceivable.  The flames coat the " +
	"stone walls with venomous verdigris.\n"
        );

    add_item(({"shore", "fungus", "vegetation"}), 
	"The shore is composed of viscous looking vegetation cast in an " +
	"eerie green light by the leprous fire.  Titanic toadstools darkly " +
	"discolored by the slimy water grow among the the vegatation and " +
	"other fungus.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TOMBDIR + "under_tomb02", "south", 0);
    add_exit(TOMBDIR + "grime_river", "north", 0);    
}

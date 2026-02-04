inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("cottage graveyard");
    set_long(
	"The crest of the hill is bleak and windswept.  Under a giant elm " +
	"tree black gravestones stick up through the snow like the decayed " +
	"fingernails of a gigantic corpse.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_item(({"tree", "trees", "elm", "elm tree"}), 
       "The grotesque vine-encumbered tree silently waves its knotted " +
       "branches far aloft.\n"
    );

    add_item(({"grave", "graves", "gravestone", "tombstone"}), (
       "The black gravestones are very smooth and bear no markings.\n"));

    add_exit(TOMBDIR + "cottage_kitchen", "in", 0);
    /*    add_exit(TOMBDIR + "graveyard_forest", "east", 0);*/
}



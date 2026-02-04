inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("cottage garden");
    set_long(
	"Here next to the sloppy garden are the remains of a flower garden. " +
        "There are various dead plants and old rose bushes lying around, as " +
        "well as lots of weeds.\n");
 
    add_prop(ROOM_I_INSIDE, 0);

    seteuid(getuid(TO));

    clone_object(TOMBDIR + "flower_pot")->move(TO);

    add_exit(TOMBDIR + "cottage_garden", "west", 0);
}



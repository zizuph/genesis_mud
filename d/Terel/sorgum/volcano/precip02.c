inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("on precipice.");
    set_long(BSN(
	"You pray to keep awake lest sleep lose your hold and send " +
        "you down the dizzy miles of air to the crags and sharp rocks " +
	"of the accursed valley."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "precip01", "east", 0);
}

weapon_disarm()
{
     write(BSN(
       "The very terrible outline of something noxiously thin, " +
       "thorned, tailed and bat-winged draws your sword out "));
}
       

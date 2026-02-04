/*
 * A void room for the transformed mystic disciple
 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BSN(xx)        break_string(xx+"\n", 70)
#define NF(xx)         notify_fail(xx)
#define TP             this_player()
#define TO             this_object()

create_room()
{
    set_short("Your body enters the mystic void");
    set_long(BSN(
	"Your body enters the mystic void while your soul is using another body."
    ));
    add_prop(ROOM_I_INSIDE, 0);
}

/* highpass */

#include <filter_funs.h>
#include "climb.h"
#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("small cave");
    set_long(BS("Another cave room. This one is very small and not "+
	"particularly interesting. It is so small that you can "+
	"hardly turn here.\n"));


    add_exit(MISTY_DIR+"r2", "up");

}

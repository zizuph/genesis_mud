inherit "/std/room";
#include <stdproperties.h>
#include "../dark.h"

#define   OGRES    8
object    ogres = allocate(OGRES);

void reset_room()
{
    int   i;

    cleanup_loot();

    for(i=0;i < OGRES; i++)
    {
	if(!ogres[i] && random(3))
	{
	    ogres[i] = clone_object(MON + "ogre");
	    ogres[i]->equip_me();
	    ogres[i]->move_living("xx", this_object());
	}
    }
}

void
create_room()
{
    set_short("rough-cut tunnel");
    set_long("The rough-cut tunnel turns here, heading to"
	+" the north and southwest.  There are two small chambers to"
	+" the east and west.\n");

    add_exit(L5 + "s8","north",0);
    add_exit(L5 + "s6","southwest",0);
    add_exit(L5 + "s18","west",0);
    add_exit(L5 + "s19","east",0);
    add_prop(ROOM_I_LIGHT,0);
    IN

    add_item(({"wall","walls"}), "The walls are constructed from hard "
      +"rock, smooth in places, but rough and unhewn in others.\n");
    add_item(({"floor","ground"}), "The floor is made from smooth undressed "
      +"stone, the very material that the tunnels were carved from.\n");
    add_item(({"ceiling","roof"}), "The ceiling is high overhead, and is made "
      +"from the same sort of rock as the rest of the tunnel.\n");
    add_cmd_item(({"air","the air"}), ({"smell","sniff"}), "The air is "
      +"dry and musty, as if some creature had died here long, long ago.\n");

    reset_room();
}

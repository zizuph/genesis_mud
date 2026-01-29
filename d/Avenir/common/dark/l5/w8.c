// File name:    /d/Avenir/common/dark/l5/w8.c
// creator(s):   Farlong
// last update:  Cirion, May 1996 - added Ogres, cleaned up the area.
// purpose:      Tunnels in Level 5 of the Utterdark, containing Ogres and
//               other nasties.
// note:         
// bug(s):       
// to-do:        
// revision:     
inherit "/std/room";
#include <stdproperties.h>
#include "../dark.h"

#define   OGRES    onum
int       onum  =  random(10);
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
    set_short("smooth stone passage");
    set_long("This smooth-cut stone passage looks like it was"
	+" made with a purpose.  It extends for as far as you can see"
	+" without side passages or other exits.\n");

    add_exit(L5 + "w7","west",0);
    add_exit(L5 + "w9","east",0);
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

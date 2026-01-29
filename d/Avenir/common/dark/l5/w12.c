// File name:    /d/Avenir/common/dark/l5/w12.c
// creator(s):   Farlong
// last update:  Cirion, May 1996 - added Ogres, cleaned up the area.
// purpose:      Tunnels in Level 5 of the Utterdark, containing Ogres and
//               other nasties.
// note:         
// bug(s):       
// to-do:        
// revision:     
inherit "/std/room";
#include "../dark.h"
#include <stdproperties.h>

#define OGRES  onum

int onum = 3 + random(4), rnum;
object ogres = allocate(OGRES);

void 
reset_room()
{
    int i;

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
      +" made with a purpose.  It follows an arc to the southeast and"
      +" northeast without side passages or other exits. The air is strong"
      +" the stench of ogres.\n");

    add_exit(L5 + "w13","southeast",0);
    add_exit(L5 + "w11","northeast",0);
    add_prop(ROOM_I_LIGHT,0);
    IN

    reset_room();
}

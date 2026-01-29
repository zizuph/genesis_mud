inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    set_short("In a secret passageway in the House of Paullus");
    set_long("You now find yourself in a larger room that the "+
    "passageway. The walls are made of stone, but it feels "+
    "strangely hot and stuffy down here. Dust covers the "+
    "room.\n");
    
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    
    add_exit(NOBLE(paullus/hole2),"up",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/drash));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}


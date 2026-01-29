
//	Modified by: Toby, 971007 (fixed typo)


inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    set_short("The Kabal Museum of Art");
    set_long("You are greeted by a cool breeze as you step into "+
    "this large, vaulted ceiling building. The walls are made of "+
    "white stone, and there are windows along the walls letting "+
    "beams of sun shine down. " +
    //"This room is rather plain, except "+
    //"for a large glass case in the corner of the room. "+
    "This vast museum stretches "+
    "further to the east.\n");
   
    add_item("walls","The walls are clean and made of white stone.\n");
    add_item("ceiling","The ceiling is vaulted and soars high into the "+
    "sky.\n");
    add_item("windows","The windows let light into the building.\n");
    add_item("tables","On the tables you see many strange and "+
    "interesting artifacts.\n");
    add_item("stands","On the stands you see many strange and "+
    "interesting artifacts.\n");

    INSIDE;

//     clone_object(NOBLE(obj/case6))->move(TO);

    add_exit(NOBLE(museum1),"east",0,-1,0);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/historian));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

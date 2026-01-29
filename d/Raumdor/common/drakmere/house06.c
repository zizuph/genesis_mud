#include "defs.h"
inherit HOUSE_ROOM;
/* By Sarr */

object man;
object woman;
object child;

void reset_room();


void
create_room()
{
    ::create_room();
    
    set_short("Inside a house in Drakmere");
    set_long("You are in a small wooden house. There stands a "+
    "fire pit in the center of the room, while beds line the "+
    "west wall. Some chests are stacked in the north side "+
    "of the wall, while a warm fur rug covers the otherwise cold "+
    "hard wooden floor. Food plates and food scraps are piled in "+
    "one corner of the room.\n");
    add_item("beds","They look nice and warm.\n");
    add_item(({"pit","fire pit"}),"It burns dimly, lighting the room and "+
    "keeping the inhabitants warm, and, judging from the large "+
    "iron pot in the fire, providing warm food.\n");
    add_item(({"iron pot","pot"}),"You smell something good cooking.\n");
    add_item("chests","Clothes and other valuables are contained in "+
    "the chests.\n");
    add_item("rug","Its a large, warm fur rug. You feel like rolling "+
    "around naked in it.\n");
    reset_room();
    add_exit(DRAKMERE_DIR + "road31","north","@@house");
}

int
house()
{
    write("You step back ouside into the streets of Drakmere.\n");
    return 0;
}

void
reset_room()
{
    if(!man)
    {
        man = clone_object(DRAKMERE_NPC_DIR + "m_citizen");

        man->move_living("xxx",TO);
    }
    if(!woman)
    {
        woman = clone_object(DRAKMERE_NPC_DIR + "f_citizen");

        woman->move_living("xxx",TO);
    }
    if(!child)
    {
       child = clone_object(DRAKMERE_NPC_DIR + "child");

       child->move_living("xxx",TO);
    }
}

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
    set_long("You are now within a modest wooden dwelling. "+
    "There are a couple of beds that line the west wall, a "+
    "small fireplace on the north wall, a few chests and "+
    "drawers on the east wall, while a large, warm and cozy "+
    "looking rug covers the floor. There is a table with "+
    "a couple chairs surrounding it standing here.\n");
    add_item("beds","They look nice and warm.\n");
    add_item("fireplace","It burns dimly, lighting the room and "+
    "keeping the inhabitants warm, and, judging from the large "+
    "iron pot in the fire, providing warm food.\n");
    add_item(({"iron pot","pot"}),"You smell something good cooking.\n");
    add_item("chests","Clothes and other valuables are contained in "+
    "the chests.\n");
    add_item("drawers","Looks like where the inhabitants store some "+
    "of their stuff.\n");
    add_item("rug","Its a large, warm fur rug. You feel like rolling "+
    "around naked in it.\n");
    add_item("table","A small wooden table, with some food bowls and "+
    "other utensiles on it.\n");
    add_item("chairs","Made of solid oak.\n");
    add_exit(DRAKMERE_DIR + "road04","east","@@house");
    reset_room();
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


int
house()
{
    write("You step back ouside into the streets of Drakmere.\n");
    return 0;
}

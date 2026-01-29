inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("In the Lord's room of the House of Aemilius");
    INSIDE;
    set_long("You now find yourself in a large, and luxurious "+
      "room. The walls around you are made of polished, oak "+
      "wood that gleam with a dull shine. The ceiling is high and "+
      "vaulted, and a large mirror is placed on it, overlooking "+
      "the massive bed just before you. There are windows along "+
      "the back, overlooking the city. The floor is covered with "+
      "many rich animal furs. There are stuffed animal heads along "+
      "the walls, including a few grotesque goblin heads. There "+
      "are many chests along the wall, and a dresser and wardrobe "+
      "off to the other side. Paintings and tapestries adorn the "+
      "walls.\n");

    add_item("walls","They are made of hard oak.\n");
    add_item("mirror","@@mirror@@");
    add_item("windows","You can see the noble district stretch "+
      "out before you.\n");
    add_item("furs","They are soft and furry.\n");
    add_item("heads","You see the heads of moose, tigers, lions, "+
      "bears, wolves, and even a few goblins.\n");
    add_item("chests","The are locked chests made of oak and steel.\n");
    add_item("wardrobe","A full selection of fine furs and coats.\n");
    add_item("dresser","The dresser is made of black oak, and "+
      "there are little combes, brushes and other grooming objects on "+
      "it.\n");
    add_item("paintings","They are mostly of deserts.\n");
    add_item("tapestries","They are intricate woven symbols and "+
      "designs.\n");

    add_exit(NOBLE(aemilius/m16),"west",0,-1,-1);
    reset_room();
}

string
mirror()
{
    if(TP->query_prop(LIVE_I_UNDEAD))
	return "Odd, you don't see your reflection.\n";
    return "You see yourself smiling up.\n";
}


void
reset_room()
{
    if(!ob)
    {
	ob = clone_object(NOBLE(npc/aemilius));
	ob->arm_me();
	ob->move_living("xxx",TO);
    }
}


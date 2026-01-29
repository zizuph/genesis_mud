#include "/d/Ansalon/goodlund/nethosak/city/obj/door.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
inherit MITHAS_IN;

object beholder;

void
reset_mithas_room()
{
   if(!objectp(beholder))
   {
      beholder = clone_object(MNPC + "beholder");
      beholder->move(this_object());
   }
}

void
create_mithas_room()
{
    object door;
    set_short("Cellar of an old house");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest75","up",0);

    add_prop(ROOM_I_LIGHT,0);
    door = clone_object(MOBJ + "woodendoor2");

    add_item(({"stones","walls", "wall"}),
      "The walls looks very old, in the northern part "+
      "of the wall, you notice a small hole that might "+
      "lead to another section of this cellar.\n");

    add_item(({"rubbel","furniture"}),
      "This garbage is useless, most of it is rotten "+
      "and completely useless.\n");
 
    add_item(({"planks"}),
      "The planks look old, but quite steady.\n");
 
    add_item(({"moss"}),
      "There's only a few moss spots on the walls and floor.\n");
 
    add_cmd_item(({"hole"}),({"crawl", "enter"}),
      "@@enter_hole");

    door = clone_object(MOBJ + "woodendoor2");
    door->move(this_object());
    reset_mithas_room();
}

string
long_descr()
{ 
    return
    "You are standing in the cellar of an old house. The "+
    "walls here are made out of stones, and the roof above "+
    "you consist of wooden planks and thin stones. In one "+
    "of the corners of the room, old rubble and something that "+
    "used "+
    "to be furniture has been shoved aside. This entire "+
    "room is covered in a ghastly gloom, and the humidity "+
    "here makes it a decent environment for moss and "+
    "bugs.\n";
}

int
enter_hole()
{
    if(objectp(beholder) && E(beholder) == TO)
    {
        write("The beholder moves in front of you to block the entrance. " +
          "You can't enter the hole.\n");
        return 1;
    }
    TP->move_living("crawls into a small hole in the wall",MROOM + "lair",0,0);
    return 1;
}

#include "../default.h"
inherit PORT_ROOM;

#define SAILOR PORT + "npc/sailor"
object ob1;
object ob2;

void
create_port_room()
{
    set_short("Guard room");
    set_long("You've entered a small guard room.\n"+
      "This is where the guards play cards, or just sit back and relax. The "+
      "otherwise bare room contains a round wooden table and several small "+
      "chairs. A symbol of a dark sun dominates the far wall.\n");
    add_item(({"round wooden table","round table","wooden table","table"}),
      "A large table set upon rickety wooden legs that sits in the center "+
      "back area of the room, directly in front of the symbol. Several "+
      "playing cards are scattered on top of the table.\n");
    add_item(({"playing cards","cards","card"}),"A typical deck of "+
      "playing cards. They look worn and faded, apparently from continual "+
      "usage.\n");
    add_item(({"small chairs","chairs","chair"}),"Short, uncomfortable "+
      "seats for the guards. It seems they were deliberately built that "+
      "way so the guards wouldn't get too comfortable.\n");
    add_item(({"symbol of a dark sun","symbol","dark sun","sun","far wall","wall"}),
      "The side of the room opposite you is dominated by a painting of "+
      "a sun as black as the stygion depths of the Abyss. The image lends "+
      "an air of foreboding to the room.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/ba2", "south");

    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(SAILOR);
	ob1 -> move_living("xxx",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(SAILOR);
	ob2 -> move_living("xxx",TO);
	ob1 -> team_join(ob2);
    }
}


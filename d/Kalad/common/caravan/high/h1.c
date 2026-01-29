#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Bedroom");
    set_long("A small bedroom.\n"+
      "At the far end of this room is a large comfortable-looking bed, beside "+
      "it are two lamps, which are providing a dim light. The floor is "+
      "bare, just plain wooden planks. The walls however are decorated with "+
      "several portraits. A short hallway leads back west.\n");

    add_item("bed", "A nice cozy bed covered with a quilted blanket "+
      "and soft, cottony pillows.\n");

    add_item(({ "quilted blanket", "blanket" }), "Amusing patterns of small "+
      "animals have been sewn onto it.\n");

    add_item(({ "pillows", "pillow" }), "The pillows look extremely soft!\n");

    add_item(({ "two lamps", "lamps", "lamp" }), "They are currently lit and "+
      "are providing a cheery warmth to the room.\n");

    add_item(({ "floor", "wooden planks", "planks", "plank" }), "The ground is "+
      "bare of any covering.\n");

    add_item(({ "walls", "wall" }), "The sides of the room are bare wood, "+
      "like the floor, however several portraits are hanging from them.\n");

    add_item(({ "portraits", "portrait" }), "They depict several different "+
      "people, a man, a woman, and a small child. They're probably the "+
      "family that resides in this home.\n");

    add_item(({ "short hallway", "hallway" }), "It leads to the west into "+
      "another room.\n");

    add_exit(CVAN + "high/house", "west");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "mother");
	ob1->move_living("M", TO);
    }

    if (!ob2)
    {
	ob2 = clone_object(NPC + "child");
	ob2->move_living("M", TO);
	ob1->team_join(ob2);
    }
}

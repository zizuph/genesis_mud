#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Kitchen");
    set_long("You enter the room to the sounds of pots and pans clanking.\n"+
      "This room is cluttered with all kinds of kitchen utensils, most of "+
      "which are hanging all over the walls. On the far side of the room "+
      "lies a gigantic oven and another thing that looks like a grill. "+
      "The floor here looks rather greasy.\n");

    add_item(({ "pots", "pans", "utensils" }),
      "They are all swinging wildly in the air, it takes a lot of your "+
      "concentration just to avoid getting hit.\n");

    add_item(({ "walls" }),
      "The walls are splattered with grease.\n");

    add_item(({ "oven" }),
      "A huge contraption made of iron. You feel intense heat radiating from "+
      "it. You notice a large pipe running from the oven up into the "+
      "ceiling where it disappears.\n");

    add_item(({ "grill" }),
      "A stained metal grill. Someone seems to have left it on while there "+
      "was still cooking oil on it, probably the cause of all the grease "+
      "stains in the room.\n");

    add_item(({ "floor" }),
      "The floor here in the kitchen is greasy and dirty, unlike the rest "+
      "of the Company building, which is squeaky clean.\n");

    clone_object(CVAN + "door/kdoor1")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tccook");
	ob1->move_living("M", TO);
    }
}

void
init()
{
    ::init();
    write("You are assaulted by the smell of burned grease!\n");
}

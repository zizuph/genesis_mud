#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(0);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Raised Dais");
    set_long("You are atop the large dais at the very end of this "+
      "enormous hall. The grand red carpet ends here, covering the surface "+
      "of the platform. Two enormous statues of golden lions flank the "+
      "impressive throne in the center back of the dais. Marbled steps lead "+
      "down to the east.\n");

    add_item(({ "carpet" }), "A lavishly decorated carpet, intricate symbols "+
      "of strange animals have been sewn upon its surface, adding to its "+
      "priceless beauty. You almost feel bad that you are standing upon it!\n");

    add_item(({ "statues", "lions" }), "Life-size statues of powerfully built "+
      "mountain lions. Examining them further you realize that the lions "+
      "are built entirely out of pure gold, not simply gold-covered. "+
      "Obviously this pair of statues must be worth a king's ransom!\n");

    add_item(({ "steps" }), "Carved marble stairs that lead slowly down to "+
      "the east.\n");

    add_cmd_item(({ "east", "wall" }), "enter", "@@enter");
    add_cmd_item("wall", "enter", "@@enter");

    add_exit(CVAN + "company/s81", "east", "@@block");

    clone_object(OBJ + "throne")->move(TO);
    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "bhgmaster");
	ob1->move_living("M", TO);
    }
}

int
block()
{
    write("As you take a step down from the dais, you slam into an invisible "+
      "wall and are forced back up.\n");
    return 1;
}

string
enter()
{
    write("You feel slight resistance as you pass through the invisible barrier.\n");
    set_dircmd("wall");
    TP->move_living("into nothingness", CVAN + "company/s81");
    return "You feel the resistance fade away.\n";
}

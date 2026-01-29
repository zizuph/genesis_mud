inherit CVAN_ROOM;

#include "default.h"

object ob1;

void
create_cvan_room()
{
    set_short("Within the Shrine to Solara, the Sun Goddess");
    set_long("\nYou are within the small, one-story stone structure "+
      "dedicated to the Sun Goddess, Solara. The interior is scarcely "+
      "decorated. The walls, floor and ceiling are but bare marble. "+
      "Dominating this solitary room is the symbol of the sun which "+
      "is mounted upon a golden stand. It is accessable via several "+
      "marble steps leading to the west. The entrance meanwhile, lies "+
      "just to the east.\n\nA palpable sense of peace and serenity "+
      "seems to emanate from every corner of the Shrine.\n\n");

    add_item(({ "interior", "shrine", "Shrine" }),
      "\nWhat do you want to look at? The walls? The floor? Perhaps the "+
      "ceiling?\n\n");
    add_item(({ "walls", "wall", "marble walls", "stone walls" }),
      "\nConstructed of marble, they gleam faintly, reflecting even the "+
      "dimmest of lights.\n\n");
    add_item(({ "floor", "stone floor", "marble floor" }),
      "\nBuilt from luxurious white marble, it is the very epitome of "+
      "cleanliness. For not a bit of dirt marrs its smooth surface.\n\n");
    add_item(({ "sun symbol", "symbol", "symbol of the sun" }),
      "\nIt is fashioned from pure gold and sculpted into the likeness of"+
      "the sun. The Symbol appears to gather in light and reflects it "+
      "back at twice the original intensity.\n\n");
    add_item(({ "golden stand", "stand" }),
      "\nThe Symbol of the Sun is resting upon it. At the stand's base "+
      "the faithful of Solara drop items as contributions in an effort "+
      "to gain her favour.\n\n");
    add_item(({ "stone steps", "steps", "marble steps" }),
      "\nTiered marble steps that force anyone just entering to raise "+
      "their gaze and behold the Symbol of the Sun Goddess, Solara.\n\n");
    add_item(({ "entrance" }),
      "\nThe front of the Shrine, it leads out onto Wall Street.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "\nAs you prepare to attack, a force beyond "+
      "your scope of power stays your hand. You realize that the very "+
      "sacredness of this shrine prevents harmful actions.\n\n");
    add_prop(ROOM_I_LIGHT, 2);

    set_hear_bell(1);

    add_exit(CVAN + "wall/s2", "east", 0);

    ob1 = clone_object(NPC + "s_priestess")->move(TO);
}

void
init()
{
    ::init();

    add_action("do_pray", "pray");
}

int
do_pray(string str)
{
    if(!str || str != "solara")
    {
	notify_fail("\nIt is blasphemy to pray to any but Solara "+
	  "within her Shrine!\n\n");

	return 0;
    }

    write("\nYou clasp your hands together and bow your head in a "+
      "silent prayer to the Sun Goddess, Solara. May she grant you "+
      "her favour.\n\n");
    say(QCTNAME(TP) + " clasps " + TP->query_possessive() + " hands "+
      "together in a silent prayer to the Sun Goddess, Solara.\n");

    set_alarm(3.0, 0.0, "do_smile");

    return 1;
}

void
do_smile()
{
    this_player()->command("smile cont");

    return;
}


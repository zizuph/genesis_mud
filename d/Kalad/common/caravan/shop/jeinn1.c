#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Room within the Journey's End Inn");
    set_long("This room is small, but comfortable. Several couches are "+
      "placed in strategic areas around the room, insuring numerous places "+
      "of rest for those that may need it.\n");

    add_item(({"couches", "couch"}), "There are quite a few of them in this "+
      "room, all look extremely comfortable to your road-weary eyes.\n");
    add_item(({"floor"}), "The floor beneath you is composed of strong, "+
      "shiny hardwood planks.\n");
    add_item(({"strong hardwood planks", "shiny hardwood planks", "strong planks", "shiny planks", "hardwood planks", "planks", "plank"}),
      "The floor is composed of them.\n");

    add_exit(CVAN + "shop/jeinn", "down", "@@msg", -1);
    add_exit(CVAN + "shop/jeinn2", "east");

    clone_object(OBJ + "mirror")->move(TO);
    clone_object(OBJ + "charity_box")->move(TO);
}

int
sit_down(string str)
{
    if(!str || str != "down")
    {
	notify_fail("Sit where, down?\n");
	return 0;
    }

    write("You sit down on a couch with an audible PLOP.\n");
    say(QCTNAME(TP) + " sits down on a couch with an audible PLOP.\n");
    set_alarm(3.0, 0.0, "resting");
    return 1;
}

void
resting()
{
    write("You feel relaxed and refreshed from resting on the couch.\n");
    say(QCTNAME(TP) + " looks relaxed and refreshed from resting on the couch.\n");
}

msg()
{
    TP->catch_msg("Sounds of drinking and merriment greet you like an old "+
      "friend.\n");
    return 0;
}

void
init()
{
    ::init();
    AA(sit_down, sit);
}

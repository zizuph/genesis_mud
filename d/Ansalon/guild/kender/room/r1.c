#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KEN_OUT;

void
reset_kendermore_room()
{
    return;
}

create_kendermore_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"giant oak tree","oak tree","tree"}),
      "A great oak tree rises up before you, its huge limbs " +
      "stretching out above you, filled with a thick and " +
      "lush canopy of green. You think you can hear giggles " +
      "and laughter from within the leaves.\n");

    add_item(({"huge roots","roots","root"}),
      "Huge roots claw into the ground here like great " +
      "burrowing worms. Between two of them is a small opening " +
      "to the north.\n");
    add_item(({"ancient evergreen forest","ancient forest",
	"forest","evergreen forest"}),
      "You stand in the middle of an ancient evergreen forest.\n");

    add_item(({"small opening","opening"}),
      "Between two huge roots to the north is a small opening, " +
      "so small that only little people would be able to fit in.\n");

    add_exit(KROOM + "train_room", "northeast", 0);
    add_exit(KROOM + "joinroom","northwest",0);
    add_exit(KROOM + "r2","north","@@enter_tree");
    add_exit("/d/Ansalon/balifor/flotsam_forest/room/traild","southwest",0);

    reset_kendermore_room();
}

int
enter_tree()
{
    if(TP->query_race() == "elf" || TP->query_race() == "human" ||
       TP->query_race_name() == "minotaur" || TP->query_race_name() == "ogre")
    {
	write("You are too big to fit through the " +
	  "opening.\n");
	say(QCTNAME(TP) + " tries to crawl through the opening, " +
	  "but is too big.\n");
	return 1;
    }
    write("You scramble through the opening into the tree...\n");
    say(QCTNAME(TP) + " scrambles through the opening into the tree.\n");
    return 0;
}

string
short_descr()
{
    return "Before a giant oak tree in the middle of an ancient forest";
}

string
long_descr()
{
    return "You stand at the base of a giant oak tree in " +
    "an ancient evergreen forest. Huge " +
    "roots from the oak claw into the ground around you. Between two " +
    "particularly big roots to your north is an opening into the " +
    "center of the tree. A new looking path leads around the oak " +
    "to your northeast.\n";
}

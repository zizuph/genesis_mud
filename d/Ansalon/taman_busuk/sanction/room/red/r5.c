#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("on a path halfway up the side of a volcano in Sanction");
    set_long("@@long_descr");

    add_item(({"wide path","path"}),
      "You stand on a wide path, created and maintained by numerous " +
      "slaves taken by the dragonarmies. The path leads up to the " +
      "large temple on the edge of the volcano.\n");
    add_item(({"sanction","city","city of sanction"}),
      "Looking down from the side of a volcano, you can make out the " +
      "city of Sanction quite clearly. It is a city that is slowly " +
      "being carried into oblivion by the lava streams that flow " +
      "through it, lava streams that illuminate the city with a hellish " +
      "red light, making the city seem like it better belongs in the " +
      "lower levels of the Abyss.\n");
    add_item(({"looming temple","temple","structure",
	"malevolent structure","dragons head","head"}),
      "Looming before you is a structure shaped in the form of a " +
      "giant dragons head. It is the temple of Luerkhisis, and " +
      "is the center of the Queen of Darkness's power on Krynn.\n");

    add_exit(SRED + "r4","southwest",0);
    add_exit(SRED + "r6","northeast",0);
}


string
long_descr()
{
    return tod_short_descr()+ "You stand on a path halfway up " +
    "the side of an active volcano, one of the Lords of Doom " +
    "that borders on the city of Sanction. " +
    "From this height, the city can be made out quite clearly, " +
    "but it is the looming temple further up that captures your " +
    "attention... a malevolent structure created in the image of " +
    "an evil dragons head. The path leads southwest towards the " +
    "base of the base of the volcano, and northeast up to the " +
    "temple before you.\n";
}

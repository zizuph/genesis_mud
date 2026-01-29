#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("before a great structure shaped in the form of a " +
      "dragons head, the temple of Luerkhisis");
    set_long("@@long_descr");

    add_item(({"wide path","path"}),
      "You stand on a wide path, created and maintained by numerous " +
      "slaves taken by the dragonarmies. The path ends here at the " +
      "base of the temple, while it continues down the side " +
      "of the volcano to your southwest.\n");
    add_item(({"malevolent structure","structure","dragons head",
	"head","temple","temple of luerkhisis"}),
      "Looming before you is the temple of Luerkhisis, the center of " +
      "the Queen of Darkness's power on Krynn. To your northeast " +
      "you can enter the temple through what looks like the maw " +
      "of the dragons head.\n");
    add_item(({"wide doors","doors","maw"}),
      "The wide doors to the temple are positioned where the great " +
      "maw of the dragon would be. The doors are open.\n");

    add_exit(SRED + "r5","southwest",0);
    add_exit(LUERK + "r1","northeast","@@enter_temple");
}

int
enter_temple()
{
    write("You enter the temple of Luerkhisis...\n\n");
    return 0;
}

string
long_descr()
{
    return tod_short_descr()+ "You stand before a malevolent structure " +
    "shaped in the form of a giant dragons head. This is the " +
    "temple of Luerkhisis, the center of the Queen of " +
    "Darkness's power on Krynn. You can enter through its " +
    "wide doors to your northeast. To your southwest, a path " +
    "continues down the volcano you stand on.\n";
}

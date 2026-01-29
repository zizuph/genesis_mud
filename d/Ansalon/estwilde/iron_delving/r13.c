#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_OUT;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"cobbled path","path"}),
      "A cobbled path, crafted by dwarves, heads off to the " +
      "west towards the middle of Iron Delving.\n");
    add_item(({"hall of warriors","hall","building",
	"stone building","large stone building","house"}),
      "To your east is the Hall of Warriors, the " +
      "house where dwarven warriors of the clan relax " +
      "and discuss matters when they are not beating up " +
      "giants and goblins.\n");
    add_item(({"iron delving","community"}),
      "You stand in the dwarven community of Iron Delving " +
      "situated in the middle of the plains of Estwilde.\n");

    add_exit(IRON + "r11","west",0);
    add_exit(GUILD_NEIDAR_ROOM_PATH + "start","east","@@enter_hall");

    reset_dwarf_room();
}

int
enter_hall()
{
    if(TP->test_bit("Ansalon",3,3) && TP->test_bit("Ansalon",3,4))
    {
	write("You are in disgrace! You cannot enter the Hall " +
	  "of Warriors.\n");
	return 1;
    }

    if( !TP->query_guild_member("Dwarven Warriors of the Neidar Clan") &&
        !TP->query_guild_member("Shieldbearers of Iron Delving") )
    {
	write("You are not a member of the Clan, so cannot " +
	  "enter the Hall of Warriors.\n");
	return 1;
    }

    write("You enter the Hall of Warriors.\n");
    return 0;
}

string
short_descr()
{
    return "Before the Hall of Warriors in Iron Delving";
}

string
long_descr()
{
    return "You are standing on a cobbled " +
    "path before the Hall of Warriors, a large stone " +
    "building that houses the warriors of the dwarven " +
    "community of Iron Delving. The path leads " +
    "off to the west, while the entrance to the hall is " +
    "to your east.\n";
}

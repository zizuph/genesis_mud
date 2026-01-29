#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;

#define RESCUED_MERCHANT "_i_rescued_the_sanction_merchant"
#define GIVEN_QUEST "_given_ansalon_merchant_quest"

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_short("Inside a warehouse on the docks of Kalaman");
    set_long("@@long_descr");

    add_item(({"empty crates","crates"}),
      BSN("Empty wooden crates are the only things being stored within the warehouse. " +
	"You find nothing interesting about them."));
    add_item("warehouse","@@long_descr");
    add_item(({"stairway","stairs","wooden stairway"}),
      BSN("A wooden stairway at the back of the warehouse leads up to an office " +
	"above."));
    add_item("office",
      BSN("An office of some sort can be reached by going up the stairway."));

    add_exit(KROOM + "road2","north",0);
    add_exit(KROOM + "office","up","@@no_go");


}

int
no_go()
{
    if(TP->query_prop(GIVEN_QUEST) || TP->query_prop(RESCUED_MERCHANT))
    {
	write("You knock on the door, which swiftly opens and allows you entrance.\n");
	say(QCTNAME(TP)+ " knocks on the door to the upper room. It opens, "+
	  "allowing " +HIM(TP)+ " entrance.\n");
	return 0;
    }
    write("You try to go up, but notice the door to the upper room has "+
      "been closed. Knocking produces no response.\n");
    return 1;
}

string
read_note()
{
    write("The note pinned on the door says:\n" +
      "     Gone to get more crystals. Will be back soon!\n     T'nahcrem.\n");
    return "";
}

string
long_descr()
{
    string str;

    str = "You stand within a warehouse that stands on the edge of the docks of " +
    "Kalaman. A few empty crates are the only things that are being store here, as " +
    "most goods have been either stored within the walls of the city, or quickly shipped " +
    "off to Palanthas, due to the ever increasing risk of an attack on the city by the " +
    "dragonarmies. A wooden stairway at the back of the room leads up to an office " +
    "above the warehouse.";

    return BSN(str);
}



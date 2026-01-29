
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

inherit SANCINROOM;
inherit "/d/Ansalon/lib/pub";

object ob, barkeeper = 0;

void
reset_sanction_room()
{
    if (!objectp(barkeeper))
    {
	barkeeper = clone_object(SNPC + "barkeep2");
	set_barkeeper(barkeeper);
	barkeeper->move(TO,1);
    }

}

void
create_sanction_room()
{
    set_short("bottom floor of an inn in Sanction");

    set_long("You stand in a quiet inn on the eastern " +
      "edge of the city of Sanction. It is refreshingly " +
      "cool in this room, as the roof here is two floors " +
      "above you. A stairway near the western wall rises " +
      "railed-in balcony, an officers club for members of the "+
      "dragonarmy. A menu has been posted near the door.\n");

    add_item("roof","The high roof makes this inn " +
      "surprisingly cool for a city surrounded by active volcanoes.\n");
    add_item(({"stairway","wall","western wall"}),
      "A stairway on the western wall rises up to a balcony " +
      "reserved for dragonarmy officers.\n");
    add_item("rail","A rail surrounds the balcony above you.\n");
    add_item(({"balcony","railed-in balcony","club","officers club"}),
      "Hmm. The balcony above looks like it has been set up " +
      "with quite opulent furnishings.\n");
    add_item("menu","A menu has been posted near the door. " +
      "You can read it if you want.\n");

    add_cmd_item("menu","read","@@read_pricelist");

    add_exit(SCITY + "street17","east",0);
    add_exit(SCITY + "balcony","up","@@go_up");
    add_exit(SCITY + "feast_entry","down",0);

    add_drink_object(({"soup","soups", "chilled soup", "chilled soups"}),
      SOBJ + "soup",48);
    add_drink_object(({"platter","platters", "seafood platter", "seafood platters"}),
      SOBJ + "platter", 144);

    reset_room();
}

int
go_up()
{
    if(this_player()->query_dragonarmy_promotions() < 3)
    {
	write("Only Dragonarmy High Officers are allowed access to the upper " +
		"balcony.\n");
	return 1;
    }
    return 0;
}

string
read_pricelist()
{
    return "\n+-----------------------+\n" +
    "| Pricelist :           |\n" +
    "|                       |\n" +
    "| Chilled soup     4 sc |\n" +
    "| Seafood platter  1 gc |\n" +
    "+-----------------------+\n";
}


/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
    ::init();
    init_pub();
}


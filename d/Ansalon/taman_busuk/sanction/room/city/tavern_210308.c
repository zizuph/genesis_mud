
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

inherit SANCINROOM;
inherit "/d/Ansalon/lib/pub";

object ob,rough,merc,barkeeper = 0;

void
reset_sanction_room()
{
    if(!objectp(merc))
    {
	merc = clone_object(SNPC + "mercenary");
	merc->set_color("red");
	merc->quiet_arm_me();
	merc->move(TO,1);
	tell_room(TO, "A "+merc->short()+" enters and eyes everyone.\n");
    }

    if (!objectp(barkeeper))
    {
	barkeeper = clone_object(SNPC+ "barkeep1");
	set_barkeeper(barkeeper);
	barkeeper->move(TO,1);
	tell_room(TO, "The "+barkeeper->short()+
		" enters saying: Sorry to keep you waiting.\n");
    }

    if(!objectp(rough))
    {
	rough = clone_object(SNPC + "roughneck");
	rough->arm_me();
	rough->move(TO,1);
	tell_room(TO, "A "+rough->short()+" enters and sits at the bar.\n");
    }

}

void
create_sanction_room()
{
    set_short("a tavern in the slum district of Sanction");

    set_long("This is a tavern situated in the center of the Queen " +
      "of Darkness' empire, the city of Sanction. Not surprisingly, " +
      "it is quite often frequented by many rowdy and immoral soldiers, " +
      "making this place probably as dangerous as any battlefield " +
      "you have ever walked upon. A menu hangs in a frame on the wall here.\n");

    add_item(({"soldiers","immoral soldiers","rowdy soldiers"}),
      "It would probably be best to keep your eyes on your brew. " +
      "Staring at drunken soldiers will just cause you grief.\n");
    add_item(({"wall","menu"}),
      "A menu has been tacked to a wall here.\n");

    add_cmd_item("menu","read","@@read_pricelist");

    add_exit(SCITY + "slum4","west",0);

    add_drink_object(({"tobacco","tobac","blackroot tobacco",
	"blackroot tobac"}),
      SOBJ + "tobacco", 12);
    add_drink_object(({"beer","small beer"}),
      SOBJ + "beer", 14);
    add_drink_object(({"draught","draught of doom"}),
      SOBJ + "draught_of_doom", 120);

    reset_room();
}

string
read_pricelist()
{
    return "\n+-----------------------+\n" +
    "| Pricelist :           |\n" +
    "|                       |\n" +
    "| Beer            14 cc |\n" +
    "| Draught of Doom 10 sc |\n" +
    "|                       |\n"+
    "| Blackroot tobac  1 sc |\n"+
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


/*
	*Food room for the orcs guild
	*Altrus, May 2005
*/
#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID ({"pricelist","sign","menu"})
#define FOOD_DIR "/d/Shire/guild/orc_guild/obj/"

static object orc_seller;

void create_room()
{
	set_short("A well-lit side chamber");
	set_long("The torches on the cave walls are much larger here than the ones in the passage. Carcasses hang from hooks on the walls, dripping blood on the floor. Whever there is not meat hanging, shelves line the walls. A number of crudely fashioned tables are placed in the middle of the chamber, with equally ill-made benches next to them. This looks like the place where the orcs around here come for meals when they can get them. A sign is hanging from one of the shelves.\n");

	add_item(({"bench","benches","table","tables", "crudely fashioned tables", "ill-made benches", "crudely fashioned table", "ill-made bench"}), "The tables and benches looks like they have seen better days. They have been severely mistreated and defaced. Even so, they are still functional for sitting and eating.\n");
	add_item(({"carcass", "carcasses", "meat"}), "Not all of the carcasses are identifiable. Most appear to be of the four-legged variety, probably horses judging from the size. However, a few, though already torn apart, may have been two-legged. Blood from the carcasses drips on the floor, although no one seems to mind.\n");
	add_item(({"hooks", "hook", "iron hook", "iron hooks"}), "The hooks holding up the meat are iron, rusty, and stick out about two feet from the wall.\n");
	add_item(({"shelves"}), "The shelves are used for holding various food and drink stores. Probably shouldn't take them without paying though; things might get bloody and painful.\n");
	add_item(({"stores"}), "Just read the sign. No need to go messing up the shelves to find what you want.\n");
	add_item(({"blood"}), "The blood dripping from the carcasses pools wherever there is a low point in the floor.\n");
	add_item(({"cave"}), "There is not doubt that this part of the cave has been cut and dug out by tools; the walls are too square to be natural.\n");
	add_item(({"walls"}), "The walls, while crudely fashioned, are more or less squared to the floor, at least up to head heighth. There are several small torches hanging on the wall from sconces.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic. There is blood all over.\n");
	add_item(({"torches", "large torches", "larger torches"}), "The torches are made of tar soaked fabric or skins wrapped onto the end of sticks, mounted on sconces. These ones seem to light the area better than the small ones in the passage.\n");
	add_item(({"sconces"}), "The sconces hanging from the walls are made from metal, probably iron. They are rusted and bent, in serious need of replacing.\n");
	add_item(({"sticks", "small sticks"}), "The sticks being used as torches to provide some light for the cave.\n");
	add_item(({"fabric", "skins"}), "The fabric or skin or whatever it is that's wrapped around the torches is soaked in some kind of oil or tar.\n");
	add_item(({"oil", "tar", "substance"}), "The oily or tarry substance on the torches makes them easier to light.\n");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine, but was dug and fashioned for use as the warren you see now.\n");
	
	add_item(PRICELIST_ID, "The sign is meant to be read.\n");
   
	add_prop(ROOM_I_INSIDE,1);
	add_prop(ROOM_I_NO_CLEANUP, 1);
	add_prop(ROOM_I_NO_ATTACK, 1);
	add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
	
	add_exit("/d/Shire/guild/orc_guild/rooms/entry2","east");
	configure_shire_inn();
	reset_shire_room();
}

string pricelist_desc()
{
	return 
	" =========================================\n"+	
	"| water  . . . . . . . . . . . . . 20 cc |\n"+
	"| strange brew . . . . . . . . . . 50 cc |\n"+
	"| ############ . .all out! so don't ask! |\n"+
	"| orc liquor . . . . . . . . . . .300 cc |\n"+
	"|                                        |\n"+
	"| bread . . . . . . . . . . . . . .50 cc |\n"+
	"| dried meat . . . . . . . . . .  100 cc |\n"+
	"| ######## . . no longer available due to|\n"+
	"| a decline in the number of executions. |\n"+
	"| entrails . . . . . . . . . . . .400 cc |\n"+
	"| horse haunch . . . . . . . . . .650 cc |\n"+
	"|========================================|\n";
}

void reset_shire_room() 
{
	if(!orc_seller) 
		orc_seller = clone_object("/d/Shire/guild/orc_guild/orc_seller");
	if(!present(orc_seller)) 
		orc_seller->move(this_object());
}

void
init() 
{
  ::init();
  add_action("do_read", "read", 0);
  init_shire_inn();
}

int
do_read(string str)
{
  if (!str) return 0;
  if (member_array(str, PRICELIST_ID) == -1) return 0;
  write(pricelist_desc());
  return 1;
}

int
do_order(string str) 
{

  if (!orc_seller || !present(orc_seller)) 
  {
    notify_fail("There is no one here to buy anything from.\n");
    return 0;
  }
  return ::do_order(str);
}

mixed *get_order(string item_name)
{
	    object order;
	    int price;
	    
	    setuid();
	    seteuid(getuid());	
	    switch (item_name)
	    {
		case "water":
		case "waters":
		case "glass of water":
		case "glasses of water":
		case "0":
			order = clone_object(FOOD_DIR + "dirty_water");
			price = 20;
			break;
		case "brew":
		case "brews":
		case "strange brew":
		case "strange brews":
		case "1":
			order = clone_object(FOOD_DIR + "strange_brew");
			price = 50;
			break;
		case "liquor":
		case "liquors":
		case "orc liquor":
		case "orc liquors":
		case "2":
			order = clone_object(FOOD_DIR + "orc_liquor");
			price = 300;
			break;
		case "bread":
		case "breads":
		case "3":
			order = clone_object(FOOD_DIR + "moldy_bread");
			price = 50;
			break;
		case "meat":
		case "meats":
		case "dried meat":
		case "dried meats":
		case "4":
			order = clone_object(FOOD_DIR + "dried_meat");
			price = 110;
			break;
		case "entrails":
		case "5":
			order = clone_object(FOOD_DIR + "entrails");
			price = 400;
			break;
		case "haunch":
		case "haunches":
		case "horse haunch":
		case "horse haunches":
		case "6":
			order = clone_object(FOOD_DIR + "horse_haunch");
			price = 650;
			break;
		default: 
			write("That's not on the menu.\n");
			return 0;
	    }
	    return (({order}) + ({price}));
}

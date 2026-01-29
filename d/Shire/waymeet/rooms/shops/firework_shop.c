/* 
 * A fireworks shop for Waymeet
 *  (plus a little exit up to my workroom)
 * Raymundo, Feb 2020
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "/d/Genesis/delivery/delivery.h"
#include "/d/Shire/defs.h"
#include "/d/Shire/waymeet/defs.h"
#define PRICELIST_ID ({"pricelist","list","sign", "prices"})

static object innkeeper;

int
wiz_check()
{
	if(!TP->query_wiz_level())
	{
		write("There is no obvious exit up.\n");
		return 1;
	}
	if(TP->query_met_name() == "Raymundo")
	{
		write("\nGreetings, Master! Welcome home!\n\n");
		return 0;
	}
	write("\nWelcome, fellow wizard!\n\n");
	return 0;
}

void
create_room()
{

   configure_shire_inn();
   set_short("In the Fireworks Shop");
   set_long("You are standing in the fireworks shop. You see various "
		+ "fireworks and firecrackers all over the walls next to a very "
		+ "large portrait. There is a counter here with a pricelist on "
		+ "top of it. In the corner, you see a box full of firework-"
		+ "making supplies.\n");
	add_item("box", "The box contains papers, and powders, and glues--"
		+ "all of the things you'd need to make fireworks.\n");
	add_cmd_item( ({"firework", "fireworks", "firecracker", "firecrackers"}),
		"make", "You lack the training to make your own fireworks! Just "
		+ "purchase them.\n");

	add_item( ({"portrait", "painting"}), "The painting extends from the "
		+ "floor to the ceiling. It depicts a white-bearded grey-robed "
		+ "wizard carrying a pack of fireworks. He is surrounded by a "
		+ "mob of hobbit children, all of whom are laughing and cheering. "
		+ "Behind the wizard, you notice the garishly orange building you "
		+ "currently occupy.\n");
	add_item( ({"firework", "fireworks", "firecracker", "firecrackers"}), 
		"There are fireworks behind the counter for purchase. There are "
		+ "also many firecrackers on the walls, serving as decorations.\n");
	add_item( ({"wall", "walls"}), "As is the case outside, the walls are "
		+ "painted orange. Very very bright orange. There are firecrackers "
		+ "all over the wall, serving as decorations, as well as a very "
		+ "large portrait.\n");
	add_item( "ceiling", "The ceiling is the bottom of the roof. It "
		+ "keeps the rain out.\n");
	add_item("floor", "The floor is made of wood. It has some scratches "
		+ "and scuff marks on it.\n");
	add_item( ({"scratch", "scratches", "mark", "marks", "scuffs", "scuff mark", "scuff marks"}),
		"The scratches and scuffs appear to be from customers' boots. "
		+ "Judging by the ammount of scuffs, you can infer the shop gets a lot "
		+ "of business.\n");
	add_item( ({"storey", "second storey"}), "Weird. You don't notice a "
		+ "second storey from the inside either. What's with the stairs?\n");
	add_item("counter", "The counter looks like a few boards that have been "
		+ "nailed together to make a more-or-less level surface. There is a "
		+ "sign on it.\n");
	remove_item("spittoon");
   add_item(PRICELIST_ID, "@@pricelist_desc");
   add_item( ({"fine print", "print"}), "@@read_fineprint@@");
   add_cmd_item( ({"print", "fine print"}), "read", "@@read_fineprint@@");
   
   add_prop(ROOM_I_INSIDE,1);
//	innkeeper = clone_object(WAYM_NPC_DIR + "majorian");
	//innkeeper->move(TO);
   
	add_exit(WAYM_STREET_DIR + "street_10", "out");
	add_exit(WAYM_STREET_DIR + "street_10", "east", 0,0,1);
	add_exit("/w/raymundo/workroom", "up", wiz_check, 0,1);
   reset_shire_room();

}

//so you can read the pricelist.
string
pricelist_desc()
{
  return("\n"
	+ "+-------------------------------------------------------------+\n"
    + "| We have the following fireworks for sale:                   |\n"
	+ "+=============================================================+\n"
	+ "| 1. a long tubular firework                                  |\n"
	+ "| 2. a short squat firecracker                                |\n"
	+ "| 3. a yellow flower-shaped firecracker                       |\n"
	+ "| 4. a rainbow-tipped arrow-shaped firecracker                |\n"
	+ "| 5. a red tube on a stick                                    |\n"
	+ "| 6. a brown paper-bear firework                              |\n"
	+ "| 7. a black box-shaped firework                              |\n"
	+ "+=============================================================+\n"
	+ "| All fireworks can be purchased for five platinum coins      |\n"
	+ "+-------------------------------------------------------------+\n"
	+ "You see some fine print at the bottom of the sign.\n");
}

string
read_fineprint()
{
	return("For simplicity's sake, please purchase by number. \nFor example, "
		+ "<buy 1>, <buy 2>, etc.\nThank you.\n");
}
void
reset_shire_room() 
{
	if(!innkeeper)
	{
		innkeeper = clone_object(WAYM_NPC_DIR + "majorian");
	}
 if(!present(innkeeper));
 {
	innkeeper->move(TO);
 }

}

void
init() 
{
    ::init();
    add_action("do_read", "read", 0);
	add_action("dont_order", "order");
	add_action("do_order", "purchase");
	add_action("do_light", "light");
    init_shire_inn();
}

int
do_light()
{
	write("It's not a good idea to light anything around this many "
		+ "fireworks. You could die!\n");
		return 1;
}
//I don't like the order verb for this room, so i redefined it.
int
dont_order()
{
	write("The shopekeeper says: This is not an inn. Just buy things, don't "
		+ "order them.\n");
	return 1;
}

int
do_read(string str)
{
  if (!str) return 0;
  if (member_array(str, PRICELIST_ID) == -1) return 0;
  write(pricelist_desc());
  return 1;
}

//When you buy your scroll.
int
do_order(string str) 
{

  if (!innkeeper || !present(innkeeper)) 
  {
    notify_fail("There is no one here to buy anything from.\n"+
                "The propreitor has been killed!\n");
    return 0;
  }
  
 
  
  return ::do_order(str);
}

mixed *
get_order(string str)
{
  object order;
  int price;

  switch (str) 
  {
	case "1":
	case "number 1":
	case "#1":
	case "firework":
	case "firecracker":
	
        order = clone_object(WAYM_FIREWORKS_DIR + "firework");
		break;
		
	case "2":
	case "number 2":
	case "#2":
		order = clone_object(WAYM_FIREWORKS_DIR + "firework2");
		break;
		
	case "3":
	case "number 3":
	case "#3":
		order = clone_object(WAYM_FIREWORKS_DIR + "firework3");
		break;
		
	case "4":
	case "number 4":
	case "#4":
		order = clone_object(WAYM_FIREWORKS_DIR + "firework4");
		break;
		
	case "5":
	case "number 5":
	case "#5":
		order = clone_object(WAYM_FIREWORKS_DIR + "firework5");
		break;
		
	case "6":
	case "number 6":
	case "#6":
		order=clone_object(WAYM_FIREWORKS_DIR + "firework6");
		break;
		
	case "7":
	case "number 7":
	case "#7":
		order = clone_object(WAYM_FIREWORKS_DIR + "firework7");
	    break;
  }
	price = (1728*5);
  return (({order}) + ({price}));
}


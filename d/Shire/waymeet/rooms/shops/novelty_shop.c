/*
 * A novelty shop for Waymeet
 *
 * Raymundo, Feb 2020
 * Cotillion - 2020-09-29
 * - Fixed type confusion
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "/d/Genesis/delivery/delivery.h"
#include "/d/Shire/defs.h"
#include "/d/Shire/waymeet/defs.h"
#define PRICELIST_ID ({"pricelist","list","sign", "prices"})
#define SPIN "_i_can_spin_the_wheel"

static object innkeeper;
void wheel();
void
create_room()
{

   configure_shire_inn();
   set_short("In the Novelty Shop");
   set_long("This shop is novel, to say the least. It's unlike any other shop "
	+ "you've ever been in. The walls are painted orange and pink and purple "
	+ "and green, almost at random. Otherwise, the walls are completely bare, "
	+ "with no product displayed whatsover, the only exception being a sign.\n");

	add_item( ({"wall", "walls"}), "The walls are garishly painted. That's a lot "
		+ "of colours that don't quite seem to go together!\n");
	add_item( ({"product", "products"}), "You have no idea what this shop sells "
		+ "because nothing is displayed.\n");

	remove_item("spittoon");
   add_item(PRICELIST_ID, "@@pricelist_desc");


   add_prop(ROOM_I_INSIDE,1);
//	innkeeper = clone_object(WAYM_NPC_DIR + "majorian");
	//innkeeper->move(TO);

	add_exit(WAYM_STREET_DIR + "street_9", "out");
	add_exit(WAYM_STREET_DIR + "street_9", "east", 0,0,1);
	wheel();
   reset_shire_room();

}

//so you can read the pricelist.
string
pricelist_desc()
{
  return("\n"
	+ "+-------------------------------------------------------------+\n"
    + "|                                                             |\n"
	+ "|       Pay the Fee, Insert the Token, Spin the Wheel         |\n"
	+ "|                                                             |\n"
	+ "+-------------------------------------------------------------+\n\n");
}


void
reset_shire_room()
{
	if(!innkeeper)
	{
		innkeeper = clone_object(WAYM_NPC_DIR + "dippity");
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
	add_action("dont_order", "buy");
	add_action("do_order", "pay");

    init_shire_inn();
}


//I don't like the order verb for this room, so i redefined it.
int
dont_order()
{
	write("The shopekeeper says: Just pay the fee.\n");
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

void
inn_hook_cant_pay(int price)
{
    write("\nYou haven't got enough money to buy a token! "
        + "Looks like you can't spin that wheel after all!\n");
    TP->remove_prop(SPIN);
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

  if(TP->query_prop(SPIN))
  {
	  notify_fail("You already paid your fee. Go ahead and spin the wheel.\n");
	  return 0;
  }

  if(str == "fee" | str == "the fee")
  {
	  write("You pay the fee and can now spin the wheel!\n");
  return ::do_order(str);
  }

  else
  {
	  notify_fail("Pay what? The fee?\n");
	  return 0;
  }
}

mixed *
get_order(string str)
{
    string order;
    int price;
    int x = 0;
    switch (x)
    {
    case 0:
        TP->add_prop(SPIN, 1);
        order = WAYM_OBJ_DIR + "token";
        break;
    }

    price = (1728);
    return (({order}) + ({price}));
}

void
wheel()
{
	object n_wheel;
	n_wheel = clone_object(WAYM_OBJ_DIR + "novel_wheel");
	n_wheel->move(TO);
}

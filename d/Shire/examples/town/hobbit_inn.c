#include "../local.h"
#include HOBBIT_FILE

inherit TOWN_BASE;
inherit INN_LIB;

object innkeeper, hobbit;

void
create_town_room()
{
    set_short("Brandywine Inn");
    set_long("This is the local inn, known as the Brandywine Inn. "+
      "Here the locals get hosed on Brandywine and good old "+
      "Molson Canadian.  On the counter you notice a menu.\n");

    add_item("locals","They all seem to be passed out at the moment.\n");
    add_item("menu","Maybe you could read it?\n");

    add_exit(EXAMPLE_ROAD + "road2","out","@@exit_block@@");
    configure_shire_inn();
    reset_shire_room();
}

//  We want to stop players from running out of the inn with drinks
int
exit_block()
{
    if (present("bottle",TP))
    {
	TP->catch_msg("You can't leave the inn with that liqour.\n");
	return 1;
    }
    return 0;
}

void
init() 
{
    ::init();  // Always do this, it makes sure all the other inits work
    init_shire_inn();
    add_action("do_read","read");
}

void
reset_shire_room()
{
    if (!innkeeper)
    {
	innkeeper = clone_object(EXAMPLE_NPC + "hobbitmaker_hobbit");
	innkeeper->move(TO);
    }
    if (!hobbit)
    {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(MILITA);
	hobbit->set_power(150);
	hobbit->move(TO);
    }
}

int
do_read(string str)
{
    TP->catch_msg("The Brandywine inn sells thses items:\n\n"+
      "1) A bottle of Molson Canadian .....  60 cc.\n"+
      "2) A bottle of Brandywine  ......... 120 cc.\n"+
      "\n\n\n");
    return 1;
}

int
do_order(string str)
{
    if (!present(innkeeper,TO)) // No innkeeper no service
    {
	NF("But the innkeeper isn't here at the moment.\n");
	return 0;
    }
    return ::do_order(str);
}


//  Since we inherited the std/inn we must define the orders that
//  a player can get.  We do this by defining the below function.

mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());  // Fix the uid
    switch(item_name)
    {
    case "Molson Canadian": case "1": case "beer": case "molson canadian":
	order = clone_object(EXAMPLE_OBJ + "molson");
	price = 60;
	break;
    case "Brandywine": case "2": case "brandywine":
	order = clone_object(EXAMPLE_OBJ + "brandywine");
	price = 120;
	break;
    }

    return (({order}) + ({price}));
}

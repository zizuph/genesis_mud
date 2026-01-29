/*
 * craft/houses/a-05.c
 * 
 * By Skippern 20(c)01
 * 
 * A tailoring shop in Dol Amorth
 */
#include "../../defs.h"

inherit "/d/Gondor/common/lib/shop";

#include <macros.h>

/* Global variables */
public int          i, j, nr;
public string       a;
public object       o, pl = this_player();

/* Prototypes */
private nomask int         order(string arg);
private nomask int         help(string arg);

void
create_shop()
{
    set_short("inside a tailor's shop");
    set_long("You are inside a tailor shop.\n");

    set_store_room(DOL_OTHER + "store/a-05");
    set_keeper_file(DOL_NPC + "keeper/a-05");
    set_shop_name("Tailors of Dol Amroth");
    set_hated_race( ({ "goblin" }) );
    set_suspected_race( ({ "gnome" }) );
    set_favoured_race( ({ "elf" }) );

    clone_object(DOL_OBJ + "doors/a-05-door")->move(this_object());
}

void
init()
{
    ::init();
    ::init_shop();
    //    add_action(order, "order");
    //    add_action(help, "help");
}

string
exa_poster()
{
    return "Welcome to Tailors of Dol Amroth!\n"+
	"You can try these instructions:\n"+
	"     buy pants for gold and get copper back\n"+
	"     buy pants for gold coins\n"+
	"     sell hat for copper coins\n"+
	"     sell all - will sell all your clother,\n"+
	"                exept for those you wear\n"+
	"     sell hat, sell second hat, sell hat 2, sell two hats\n"+
	"                also works. You may want to change the verb\n"+
	"                <buy> or <value> too.\n"+
	//        " For new clothes you can <order>. Type <help order> for \n"+
	//        " more help on the team. To list used clothes just type\n"+
	//        " <list>. <list pants> also works.\n\n";
	"To list used clothes just type <list>. <list pants> also works.\n\n";
}

private nomask int
order(string arg)
{
    string mesg;

    /* until the this code is testet thurugly, this is optional */
    return 0;

    notify_fail("Order what?\n");

    if (!arg)
  	return 0;

    write("The shop is currently out of order. Eh?\n");
    return 1;
}

private nomask int
help(string arg)
{
    if (arg != "order" && arg != "here")
        return 0;

    write(read_file(DOL_BASE + "txt/order.help"));
    return 1;
}

mixed
shop_hook_filter_sell(object ob)
{
    if (!function_exists("set_looseness",ob))
        return "The shopkeeper says: I do not want your " + ob->short() + 
	    "!\nThe shopkeeper says: I do not trade in anything but " +
            "clothes!\n";
    else
        return 0;
}

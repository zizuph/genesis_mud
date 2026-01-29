/* -*- Mode: C -*-
 *
 * trade/houses/p-10.c
 *
 * Skippern 20(c)01
 *
 * The bank of Dol Amroth.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";
inherit "/lib/bank";

#define FEE      5

/* Prototypes */
string read_plaque();

void
create_inside()
{
    set_short("inside a bank");
    set_long("This is inside a large and strong building, actually this is " +
	     "the bank of Dol Amroth, the strongest building save the " +
	     "fortress. A poster hangs on the far wall.\n");

    add_item( ({ "plaque", "poster", "instructions" }),
	&read_plaque());
    add_cmd_item( ({ "plaque", "poster", "instructions" }), "read",
        &read_plaque());

    config_default_trade();
    set_bank_fee(FEE);
    config_trade_data();

    clone_object("/d/Genesis/obj/deposit")->move(this_object());
    clone_object(DOL_OBJ + "doors/p-10-door.c")->move(this_object());
}

string
read_plaque()
{
    return "The poster reads:\n" +
        "/~~~~~~~~~~~~~~~~~~~~~~~~~~/\n"+
        "| <>                   <> |\n"+
        "|   Welcome to the bank   |\n"+
        "|    of Dol Amroth. We    |\n"+
        "|    allow all valid      |\n"+
        "|    services to the      |\n"+
        "|    affordable fee of    |\n"+
        "|    "+FEE+"%.                  |\n"+
        "|         -Management     |\n"+
        "| <>                   <> |\n"+
        "\\__________________________\\\n\n";
}

void
init()
{
    ::init();
    bank_init();
}

void
enter_inv(object ob, object from)
{
    object task;
    string *places, tmp;
    int i;

    ::enter_inv(ob, from);

    if (task = present("I_do_quest_token.c", ob))
    {
	if (task->query_task() == DOL_Q_M_EXPLORE_TOWN)
	{
  	    tmp = task->query_visit();
	    places = explode(tmp, "::");
	    for (i = 0; i < sizeof(places); i++)
	    {
		if (places[i] == "bank") return;
	    }
	    places += ({ "bank" });
	    tmp = implode(places, "::");
	    task->set_visit(tmp);
	    task->set_part(task->query_part()+1);
	}
    }
}

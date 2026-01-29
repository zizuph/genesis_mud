#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit SANCINROOM;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

object ob;
int feast_status = 0;

void
reset_sanction_room()
{
    return;
}


void
create_sanction_room()
{
    config_default_trade();
    set_short("Below the Resting Blade Inn, before the entry to a feasthall");
    set_long("You are standing in the foyer underneath the Resting Blade " +
        "Inn.@@feast_status@@\n");

    add_item(({"foyer"}),
      "You stand in the foyer of The Resting Blade Inn. A feasthall is to your north.\n");

    add_exit(SCITY + "inn","up",0);
    add_exit(SCITY + "feasthall","north","@@query_entry");

    reset_sanction_room();
}

int
query_entry()
{
   if(feast_status)
   {
      write("You walk into the feasthall to your north...\n");
      return 0;
   }
   else
      write("The feasthall is closed until someone hires it!\n");
      return 1;
}


string
feast_status()
{
    ob = TP;

    if(feast_status)
	return " To your north is a feasthall, which seems to be prepared for " +
         "some sort of celebration. You could enter there if you wish.";
    else return " To your north is a feasthall, that currently is closed. " +
         "For a mere 20 gold you can <hire feasthall>.";
}

void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action("rent","hire");
}

void
reset_feasthall()
{
    feast_status = 0;
}

int
rent(string str)
{
    NF("Hire what?\n");
    if(str == "feasthall")
    {

	if (!present("gold coin",TP))
	{
	    write("You'll need gold coins to hire out the feasthall!\n");
	    return 1;
	}
	if (!MONEY_MOVE(20,"gold",TP,0))
	{
	    write("You pay 20 gold coins to hire out the feasthall!\n");
            set_alarm(7200.0, 0.0, "reset_feasthall");
            feast_status = 1;

	    return 1;
	}
        notify_fail("You need 20 gold to hire the feasthall!\n");
	return 0;
    }
    return 0;
}


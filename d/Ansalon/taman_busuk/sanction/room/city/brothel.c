#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit SANCINROOM;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define QUERY_THIEF ob->query_guild_style_occ() == "thief" || ob->query_guild_style_lay() == "thief" || ob->query_race_name() == "kender"

object ob;

void
reset_sanction_room()
{
    return;
}


void
create_sanction_room()
{
    config_default_trade();
    set_short("The Naked Sylph, a shadowy brothel in Sanction");
    set_long("You are standing in the foyer of the Naked Sylph, a "+
      "brothel in the city of Sanction. It is rather warm in here, " +
      "most likely due to the lack of ventilation and the naturally " +
      "hot weather in this city due to the surrounding volcanoes. "+
      "Dark red drapes hang from the ceiling to the floor all around "+
      "you, making it impossible to tell how large this room is. To "+
      "your east a staircase rises to the next floor, while a desk " +
      "with an old matron behind it has been placed before the " +
      "staircase.@@thief_sign@@\n");

    add_item(({"foyer","naked sylph","brothel"}),
      "You stand in the foyer of the Naked Sylph. It is rather " +
      "dark and shadowy here.\n");
    add_item(({"dark red drapes","red drapes","drapes"}),
      "Dark red drapes hang from the ceiling all around you, " +
      "making it impossible to determine the size or shape of " +
      "this room. They sway slightly, as if a soft breeze " +
      "blows through them.\n");
    add_item("ceiling","High above you is the ceiling. Very little " +
      "can be determined about it, as many drapes hanging " +
      "from it obscure your view of it.\n");
    add_item("staircase","A large staircase ascends to the " +
      "next floor of the brothel.\n");
    add_item("desk","Before the staircase stands a heavy-looking " +
      "desk. On it rests a sign that you can read.\n");
    add_item("sign","A sign with words on it rests on the " +
      "desk.\n");
    add_item(({"old matron","matron"}),
      "An old lady sits stiffly behind the desk here. A thick mask of " +
      "makeup does little to hide the leathery face that " +
      "scowls back at you as you observe her.\n");
    add_item(({"strange mark","mark"}), "@@see_mark");

    add_exit(SCITY + "slum3","west",0);
    add_exit("","east","@@no_go");
    add_invis_exit(SCITY + "brothel_north","north","@@query_thief");

    add_cmd_item("sign","read","@@read_sign");

    reset_sanction_room();
}

string
see_mark()
{
    ob = TP;

    if(QUERY_THIEF)
	return "A thief sygil of passage! You believe you can go north " +
	"from here into the local thief guilds territory.\n";
    else
	return "Look at what?\n";
}

int
query_thief()
{
    ob = TP;

    if(QUERY_THIEF)
    {
	write("You swiftly duck behind the dark red drape...\n\n");
	return 0;
    }
    write("You try and duck behind the dark " +
      "red drape, but the old matron catches you, informing you " +
      "rather caustically that if you are not here for the girls, " +
      "you can leave.\n");
    say(QCTNAME(TP)+ " starts playing with the drapes, and is " +
      "suddenly verbally abused by the old matron at the desk.\n");
    return 1;
}

string
read_sign()
{
    return "\n"+
    "               The Naked Sylph\n"+
    "               @=============@\n"+
    "          To spend the night with one of\n"+
    "          our many beautiful and skilled\n"+
    "          ladies-of-the-night, waking up\n"+
    "          in their loving arms next time\n"+
    "          you decide to travel these realms,\n"+
    "          simply 'hire prostitute'.\n"+
    "          The cost is a mere one gold coin.\n\n\n";
}

int
no_go()
{
    write("The staircase may only be used by patrons " +
      "coming down from the rooms above.\n");
    return 1;
}

string
thief_sign()
{
    ob = TP;

    if(QUERY_THIEF)
	return " You notice a drape to the north has a strange mark on it.";
    else return "";
}

void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action("rent","hire");
}

int
rent(string str)
{
    NF("Rent what?\n");
    if(str == "prostitute")
    {
	if(TP->query_gender() == 1) /*If player is female*/
	{
	    write("The old matron says: My girls aren't that " +
	      "way inclined lassy! Still, if you want to make yourself " +
	      "a gold coin...\nThe old matron grins wickedly.\n");
	    say("The old matron says to "+ QTNAME(TP)+ ": My girls aren't that "+
	      "way inclined lassy! Still, if you want to make yourself " +
	      "a gold coin...\nThe old matron grins wickedly.\n");
	    return 1;
	}
	if (!present("gold coin",TP))
	{
	    write("The old matron snaps: I only take gold! If you want " +
	      "a piece of my girls, you'll have to go find some!\n");
	    say("The old matron snaps at " +QTNAME(TP)+ ": I " +
	      "only take gold! If you want a piece of my girls, " +
	      "you'll have to go find some!\n");
	    return 1;
	}
	if (!MONEY_MOVE(1,"gold",TP,0))
	{
	    write("You pay 1 gold coin for a night of pleasures. You " +
	      "shall awaken next time you return to these realms in the " +
	      "arms of a lady-of-the-night.\n");
	    TP->set_temp_start_location(SCITY + "upper_brothel");
	    return 1;
	}
	return 0;
    }
    return 0;
}


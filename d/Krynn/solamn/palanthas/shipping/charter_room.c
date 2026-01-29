/*Join room for mariners */

#pragma strict_types
#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <money.h>
#include "/d/Ansalon/guild/mariner/guild.h"

inherit SHIP_BASE;
inherit "/d/Ansalon/common/cheater";

#define SHIP1 "/d/Krynn/std/boats/example_boat"
#define SHIP2 "/d/Krynn/std/boats/example_medium_boat"
#define SHIP3 "/d/Krynn/std/boats/example_large_boat"

#define SHIP_TYPE ({ SHIP1, SHIP2, SHIP3 })

void
create_palan_room()
{
    set_short("office of the harbourmaster");
    set_long("@@long_descr");

    add_item(({"harbourmaster","master","desk"}),
       "The harbourmaster sits behind a desk here, looking rather " +
       "flustered.\n");
    add_item(({"office"}),
       "This is the office of the harbourmaster of Palanthas.\n");
    add_item(({"sign","wall"}),
       "A sign is attached to the wall here. You can read it if you want.\n");

    add_cmd_item("sign","read","@@read_sign");

    EXIT(SHIP + "p01", "out", 0, 0);

}

string
long_descr()
{
    return "You stand within the office of the harbourmaster of Palanthas. " +
       "Captains from across the continent and beyond dock here with the tide, " +
       "making the harbourmaster's job incredibly busy! A sign " +
       "has been attached to the wall here which you can read.\n";
}

int
read_sign()
{
    write("The sign contains a number of personal messages, and reads:\n\n" +
          "      Current personal <charter>s out of Palanthas Harbour:\n\n" +
          "      Fishing boat    ---    200 gold coins\n\n" +
          "      Merchant ship   ---    800 gold coins\n" +
          "                      ---    crewed by a professional mariner\n\n" +
          "      Warship         ---    2000 gold coins\n" +
          "                      ---    crewed by a master sea captain\n\n\n" +
          "                    ForSale\n" +
          "                 GnomishSpyglass\n" +
          "              PerfectForTheIntrepid\n" +
          "              explorerWhoHasItAll!\n" +
          "                   2GoldCoins\n\n\n" +
          "      Note: Mariners wanted! For those interested in a \n" +
          "      career on the high seas, make your way to Kalaman's\n" +
          "      harbourmaster and enlist!\n");

    return 1;
}

int
chartership(string str)
{
    string * ship_list, ship_file;
    int ship_type, cost;

    if(!str)
    {
       notify_fail("Charter what?\n");
       return 0;
    }

    if((str != "fishing boat") && (str != "merchant ship") && (str != "warship"))
    {
       notify_fail("That type of charter isn't an option.\n");
       return 0;
    }

    if((str == "fishing boat"))
    {
       ship_type = 0;
       ship_file = SHIP1;
       cost = 28800; // 200 gold
    }

    if((str == "merchant ship"))
    {
       ship_type = 1;
       ship_file = SHIP2;
       cost = 115200; // 800 gold
    }

    if((str == "warship"))
    {
       ship_type = 2;
       ship_file = SHIP3;
       cost = 288000; // 2000 gold
    }

    if(!MONEY_ADD(TP, -cost))
    {
       notify_fail("You cannot afford to pay the charter price.\n");
       return 0;
    }

    write("You charter a ship to sail the seas of Ansalon! It is " +
          "docked outside the harbourmaster's office, its captain waiting your " +
          "orders.\n");
    say(QCTNAME(TP)+ " charters a ship to sail the seas of Ansalon!\n");

    setuid();
    seteuid(getuid());

    object boat_in, ship, captain, owner;
   
    owner = this_player();
    ship = clone_object(ship_file);
    ship->move("/d/Krynn/solamn/palanthas/shipping/p01");
    ship->config_boat_inside();
    boat_in = ship->query_boat_in();

    captain = clone_object("/d/Ansalon/goodlund/bloodsea/living/chartered_capt1");

    boat_in->set_owner(captain);

    captain->move_living("into his ship", boat_in);
    captain->set_captain_lvl(ship_type);
    captain->arm_me();
    captain->equip_me();
    captain->set_owner(owner);   

    clone_object("/d/Calia/sea/objects/fish_net")->move(boat_in);

    return 1;

}

int
buyglass(string str)
{
    object glass, who;
    NF("Buy what did you say? spyglass?\n");
    if(!str || (str != "spyglass"))
	return 0;

    if (check_cheater(TP, TO))
        return 1;
    if(str = "spyglass")
    {
	NF("The harbourmaster says: You cannot pay the price.\n");
	if(!MONEY_ADD(TP, -288))
	    return 0;

	write("You pay the harbourmaster and he passes you a battered " +
          "gnomish spyglass.\n");
	say(QCTNAME(TP) + " buys a gnomish spyglass from the harbourmaster.\n");

	who = TP;
	glass = clone_object("/d/Ansalon/goodlund/bloodsea/obj/spyglass");
        if (glass->move(who) != 0)
        {
    	  write("Noticing that you are too burdened to carry the spyglass, the " +
    	    "harbourmaster places it on the ground before you.\n");
    	  say("The harbourmaster places the spyglass on the ground before " 
            + QCTNAME(TP) + ".\n");
    	  glass->move(environment(who));
         }
 
	return 1;
    }
    return 1;
}

void
init()
{
    ::init();
    add_action(chartership, "charter");
    add_action(buyglass, "buy");
}

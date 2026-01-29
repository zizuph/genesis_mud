/* pigeons.c->vin38.c, made by Nick modified by percy. */
/* modified slightly by Teth, Dec 4, 1996 */

#include "../local.h"
#include <macros.h>
#include <money.h>

inherit IN_BASE;

void
create_vin_room()
{
    set_short("In the dove hut");
    set_long("This hut is filled with doves! The stench of this " +
        "room is awful! It is amazing that anyone can reside " +
        "in this place, but considering that the service is " +
        "deemed necessary, the Knights of Vingaard Keep allow " +
        "it to remain open.\n");
    AI("doves","There are doves of many types of breeds " +
        "and colours present, all cooing and creating a mess.\n");
    ACI(({"doves","dove"}),"get","Any dove you attempt to " +
        "get flies out of reach just at the last moment!\n");
    AI("sign","The sign reads:\n\nMessenger doves! 99 copper " +
        "coins each!\n\n");
    ACI("sign","read","The sign reads:\n\nMessenger doves! 99 " +
        "copper coins each!\n\n");
    
    AE(VROOM + "es3", "east", 0);

    reset_room();
}

void
reset_vin_room()
{
    if (!P("grook", TO))
      clone_object(VNPC + "grook")->move_living("xx", TO);
}

init()
{
    ::init();
    ADA("buy");
}

buy(str)
{
    int playeralign;

    object pig,who;
    NF("Buy what did you say?\n");
    if (!str || (str != "dove"))
	return 0;

    NF("There is unfortunately no one here to sell you a dove.\n");
    if (!P("pig_gnome", TO))
	return 0;

    NF("Grook says: IWon'tSellToPeopleLikeYouWhoAreEvilAndMeanAndNasty!\n");
    playeralign = TP->query_alignment();
    if (playeralign < 0)
        {
        if (!TP->query_prop(I_WAS_EVIL))
        TP->add_prop(I_WAS_EVIL, 1);
        }
    NF("Grook says: IWon'tSellToPeopleLikeYouWhoAreEvilAndMeanAndNasty!\n");
    if (TP->query_prop(I_WAS_EVIL))
        return 0;

    NF("Grook says: You cannot pay the price.\n");
    if (!MONEY_ADD(TP, -99))
	return 0;

    write("You pay the gnome, and he utters a soft whistle. A " +
        "dove lands on his left shoulder, and he hands the dove " +
        "to you.\n");
    say(QCTNAME(TP) + " receives a dove from the gnome.\n");

    who = TP;
    pig = clone_object(VNPC + "dove");
    pig->set_owner(who);
    pig->move(who);
    return 1;
}

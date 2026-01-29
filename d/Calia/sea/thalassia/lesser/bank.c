
/* 	Bank in the Lesser Zone of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar
                16-02-08    Added Bank ID                   Mercade

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";
inherit "/lib/bank";
#define NUM 4

object bank_teller;
object *guard = allocate(NUM);

void
make_monster(int i)
{
    guard[i] = clone_object("/d/Calia/sea/creatures/tin_triton");
    guard[i]->equip_me();
    guard[i]->move(TO);
    tell_room(TO, QCTNAME(guard[i]) + " arrives.\n");
}

void
fix_bank_teller()
{
    bank_teller = clone_object(SEA_CREATURES + "bank_teller");
    bank_teller->move(TO);
    tell_room(TO, QCTNAME(bank_teller) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < NUM; i++)
        if (!guard[i])
            set_alarm(0.5, 0.0, &make_monster(i));

    if (!bank_teller) 
        fix_bank_teller();
}

void
create_water_room()
{
    object bank;

    set_short("Thalassian bank");
    set_long("This is a rectangular room carved right out of the marble "+
        "wall surrounding this section of the city. A plaque hangs by "+
        "the well-protected bank deposit located here. There is a "+
        "doorway heading back out to the west.\n");

    add_item("plaque", "@@standard_bank_sign");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");
    add_item("strongroom","It is a small fort-like hut. "+
        "It has a small opening protected with a waterproof cage "+
        "and a large sign. Behind the opening there is a small "+
        "wizened gnome.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_swim_exit(THALL+"lesser29","west",0,1);

    config_default_trade();
    set_bank_fee(22);
    config_trade_data();

    bank = clone_object("/d/Genesis/obj/deposit");
    bank->set_bank_id(1402, "Thalassia");
    bank->move(TO, 1);

    set_alarm(1.0, 0.0, "reset_room");
}

/* Called when player pays some money */
void
bank_hook_pay(string text)
{
    TP->catch_msg("You pay "+ text +" to "+QTNAME(bank_teller) + ".\n");
}


/* Called when a change text is supposed to be written */
void
bank_hook_change(string text)
{
    TP->catch_msg(QCTNAME(bank_teller)+ " gives you " + text + " back.\n");
}


/*
 * This function writes what the other players sees.
 */
void
bank_hook_other_see(int test)
{
    if (!test)
	say(QCTNAME(bank_teller) + " changes some of " + QTNAME(TP) + 
            "'s money.\n");
    else
	say(QCTNAME(TP) + " seems to calculate something.\n");
}

/*
 * Function name: bank_hook_already_minimized
 * Description:   Write this when your coins already are minimized
 */
void
bank_hook_already_minimized()
{
    bank_teller->command("say Your coins are already minimized, " + 
        TP->query_nonmet_name());
}

/*
 * Function name: bank_hook_no_idea
 * Description:   When there is no idea to minimize since it will all be
 *   		  eaten up by the tax
 */
void
bank_hook_no_idea()
{
    bank_teller->command("say There is no point in minimizing " +
        "your coins now, " + TP->query_nonmet_name());
}


/*
 * Function name: bank_hook_minimized
 * Description:   Player minimized his coins
 */
void
bank_hook_minimized(string pay_text, string got_text)
{
    TP->catch_msg(QCTNAME(bank_teller) + " minimized your coins.\n");
    say(QCTNAME(bank_teller) + " minimized " + QTNAME(TP) + "'s coins.\n");
}

int
check_bank_teller()
{

    if (bank_teller && present(bank_teller,TO))
        return 1;
    else
        return 0; 
}

/* Called for action to change some coins */
int
change(string str)
{
    if (!check_bank_teller())
    {
        NF("The banker is not here!\n");
        return 0;
    }
    else return ::change(str);
}


/* Called for minimize action */
int
minimize(string str)
{
    if (!check_bank_teller())
    {
        NF("The banker is not here!\n");
        return 0;
    }
    else return ::minimize(str);
}

public int
clean_up()
{
    int i;

    for (i=0; i < NUM; i++)
        if (guard[i])
            return 1;

    remove_object();
}

void
init()
{
    ::init();
    bank_init();
}

/*
 * File:     maiko.c
 * Created:  Cirion
 * Purpose:  elderly monk that sells food in the dining hall
 *           of the monks.
 * Cloned:   /d/Earthsea/monk/room/dining 
 * Modification Log:
 *
 */
#include "defs.h"
#include <money.h>
#include <formulas.h>

inherit MONK_NPC + "npc";
inherit "/lib/trade";
inherit "/lib/pub";

#define MAX_PURCHASED 20
#define DRINK_PRICES ({ 11, 71, 189 })

// from 'man values'
#define M_FOOD_VALUE(amount) (5 + (amount * amount / 600))

// function prototypes
void setup_food();
void setup_drinks();

void
create_monk ()
{
    set_name ("maiko");
    set_race_name ("human");
    set_short ("elderly wrinkled human");
    set_long ("This bald monk stands tall with an air of ease and "
        + "grace that defies his many years. He now "
        + "serves out his remaining years as the steward of the "
        + "dining hall, taking orders for food and drink.\n");

    init_monk ();

    // give him some copper coins
    equip_monk (({ 19 + random (12) }));


    set_act_time(30);
    add_act("control");
    add_act("inspired");
    add_act("mdedicate");
    add_act("mrelax");


    // setup functions for him to see food and drink
    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(({ 2000, 700, 50, 4 }));
    set_money_give_reduce(({ 1, 1, 1, 1 })); 

    setup_drinks ();
    setup_food ();
}

void
setup_drinks ()
{
    int    rand_val;

    rand_val = random(50, (time() / 3600)); // random addition changes every hour

    add_drink("water", "water", "fresh", 90, 0, 10,
        "glass of water", "glasses of water",
        "It is simply water, sparkling fresh and clear.\n",0);

    add_drink("wine", "wine", "red", 70, 40, F_VALUE_ALCO(40) + rand_val,
        "glass of red wine", "glasses of red wine",
        "The sparkling rosy tint of this wine comes from "
      + "the ripened grapes that were harvested from the "
      + "vinyards near the monestary.\n", 0);

    add_drink("mead", "mead", "foul smelling",10, 70, F_VALUE_ALCO(70) + rand_val,
        "mug of thick mead", "mugs of thick mead",
        "Foul smelling vapors rise from this thick, dark brown "
      + "liquid. You feel dizzy even inhaling the fumes.\n",0);
}

void
setup_food ()
{
    int    rand_val;

    rand_val = random(20, (time() / 3600)); // random addition changes every hour

    add_food( ({ "bread", "loaf" }), ({ "bread", "loaf" }),
        ({ "warm", "hot" }),
        100, // food amount
        M_FOOD_VALUE(100) + rand_val, // cc
        "loaf of bread", "loaves of bread",
        "It is a piping hot loaf of freshly-made bread.\n");

    add_food( ({ "soup", "bowl", "broth" }), ({ "broth", "soup", "bowl" }),
        ({ "warm", "hot", "vegetable" }),
        193, // food amount
        M_FOOD_VALUE(193) + rand_val, // cc
        "bowl of hot vegetable broth", "bowls of hot vegetable broth",
        "It is a large, thick leaf formed cleverly into a bowl, "
            + "which is filled with warm, rich-smelling vegetable broth.\n");

}

int
list_prices (string str)
{
    int timer = 0, i;
    mixed data;
    string name, cost, prefix;

    data = query_drinks ();

    if (pointerp (data) && sizeof (data) > 0)
    {
        for (i=0; i<sizeof (data); i++)
        {
            if (!i)
                monk_say ("For drinks I can sell you the following:", timer++);

            name = data[i][5];
            cost = LANG_WNUM (data[i][4]);

            if (i == (sizeof (data) - 1)) // last iteration
                monk_say ("And " + LANG_ADDART (name) + " for " + cost + " coppers.", timer++);
            else
                monk_say (capitalize (LANG_ADDART (name)) + " for " + cost + " coppers....", timer++);

        }
    }


    data = query_food ();

    if (pointerp (data) && sizeof (data) > 0)
    {
        for (i=0; i<sizeof (data); i++)
        {
            if (!i)
                monk_say ("For food I can sell you the following:", timer++);

            name = data[i][4];
            cost = LANG_WNUM (data[i][3]);

            if (i == (sizeof (data) - 1)) // last iteration
                monk_say ("And " + LANG_ADDART (name) + " for " + cost + " coppers.", timer++);
            else
                monk_say (capitalize (LANG_ADDART (name)) + " for " + cost + " coppers....", timer++);

        }
    }


    return 1;
}

void
init_living ()
{
    ::init_living ();

    // initialize the pub-specific commands
    init_pub ();
    add_action(list_prices, "list");
}


void
move_to_table (object ob, object where)
{
    ob->move (where, 1);
}

/*
 * Function name: pay_hook_player_buys
 * Description:   A hook to redefine if you want own message when player
 *                gets his/hers order.
 * Arguments:     ob - The object player ordered
 *                price - The price the player payed for the object
 */
void
pub_hook_player_buys (object ob, int price)
{
    object table;

    write("You pay " + price + " coppers for " + ob->short() + ".\n");
    say(QCTNAME(this_player()) + " orders " + ob->short() + ".\n");

    table = present ("dining_table", environment (TO));

    /* place the purchase on the table for the player. */
    if (objectp(table))
    {
        tell_room (environment(TO), QCTNAME (TO) + " places " + LANG_THESHORT (ob)
            + " on " + LANG_THESHORT (table) + ".\n");

        /* sadly, we need to use an alarm to move the purchase    */
        /* to the table, since the code for moving the stuff      */
        /* directly to the player is *after* the hook is called   */
        /* in the order () function in /lib/pub                   */
        set_alarm (0.0, 0.0, &move_to_table (ob, table));
    }
}


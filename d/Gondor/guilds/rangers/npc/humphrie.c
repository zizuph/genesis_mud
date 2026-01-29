/*
 *  /d/Gondor/guilds/rangers/npc/humphrie.c
 *
 *  Innkeeper of the North Hideout Mess Hall.
 *
 *  Modified directly from: innkeeper.c
 *
 *  Coded by Elessar.
 *
 *  Modification log:
 *  15-Jul-2001, Alto    changed filename to humphrie.c and revised
 *      to fit new ranger themes.
 *
 */
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "npc_ranger.c";

#define CO_NO    2

string ask_dwarfblood();

public void
introduce(object player)
{
    command("hail " + OB_NAME(player));
    command("present me");
}

public void
create_ranger() 
{
    set_name("humphrie");
    add_name(({ "cook", "inn keeper", "head cook" }));
    set_race_name("human");
    set_adj("fat");
    add_adj("friendly");
    set_long("The mess hall cook, Humphrie, is a human ranger with a "
        + "friendly face. He seldom takes a break, but runs between the "
        + "kitchen and the common room serving the hungry men and women "
        + "stationed in the northern hideout. He tries to keep the glasses "
        + "as shiny as possible, and the meals hot and delicious.\n");
    set_title("the Head Cook of the Rangers of the North");
    set_gender(G_MALE);
    default_config_npc(42);
    set_base_stat(SS_INT, 55);
    set_skill(SS_WEP_KNIFE, 30);
    set_skill(SS_DEFENCE,   30);
    set_skill(SS_TRADING,   55);
    set_alignment(600 + random(200));
    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("Welcome to the Mess Hall! Don't be making mess, you hear?");
    add_chat("My name is Humphrie.");
    add_chat("Are you hungry? We have some tender pheasant.");
    add_chat("Perhaps you want to buy my excellent ale?");
    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");
    set_default_answer("say That is not on the menu. Please take another " +
        "look at the menu.");
    add_ask(({ "ale", "golden ale" }), "say It's an excellent golden ale.", 1);
    add_ask(({ "beer", "prime beer"}), 
        "say A nice cold beer, you won't be disappointed. It's been " +
        "brewed in Bree.", 1);
    add_ask(({ "wine", "red wine"}),
        "say A chilly red wine, very nice bouquet from Merrydown.", 1);
    add_ask(({ "rum", "rum toddy"}), 
        "say Boiled water in rum with sugar. Drink it while it's hot.", 1);
    add_ask(({ "whiskey", "dry whiskey"}), 
        "say The dry whiskey won't disappoint you. It has matured " +
        "for 12 years.", 1);
    add_ask(({ "dwarfblood"}), &ask_dwarfblood());
    add_ask("porridge", "say A good breakfast porridge.", 1);
    add_ask(({ "stew", "vegetable stew"}),
        "say If you like vegetables, this is the meal for you.", 1);
    add_ask(({ "beans", "bacon", "bacon and beans" }),
        "say If you don't get satiated by one meal then buy another one.", 1);
    add_ask(({ "pheasant", "fried pheasant" }),
        "say A very good meal, the tender pheasant melts in your mouth.", 1);
    add_ask(({ "stag", "steak", "stag steak" }),
        "say This is a real dinner. Eating it all will give you " +
        "great stamina.", 1);

    set_company_no(CO_NO);
}

string
ask_dwarfblood()
{
    command("smile");
    command("say Let's see, 2 parts coffee, 2 parts redwine and 1 part");
    command("say of a secret dwarven spirit.");
    command("say Heated until it almost boils then served.");
    command("say Makes you warm in a cold winter evening.");
    return "";
}

/* solamnian prestige */
public int
query_knight_prestige()
{
    return (-5);
}


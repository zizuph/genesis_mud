/*
 * /d/Gondor/common/dwarf_guild/npc/keeper.c
 *
 * The shopkeeper of the shop in the dwarven race guild
 *
 * /Mercade, 7 January 1994
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */

inherit "/d/Gondor/common/dwarf_guild/npc/remember";
inherit "/lib/shop";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define STORE_ROOM        (DWARF_DIR + "store")
#define SAVE_FILE         (DWARVEN_RACE_GUILD_NPCS + "shopkeeper_save")
#define MY_NAME           "thror"
#define SHORT_MONEY_TYPES ({ "cc", "sc", "gc", "pc" })
#define NUM               (sizeof(SHORT_MONEY_TYPES))
#define BASE              60
#define COMPUTE_STAT      (((BASE * 4) / 3) + random(BASE / 2) + 1)
#define COMPUTE_SKILL     max(COMPUTE_STAT, 100)
#define SHORT(o)          check_call((string)o->short())
#define CLONE_OBJECT(s)   clone_object(s)->move(this_object(), 1)

void
create_monster() 
{
    set_name(MY_NAME);
    add_name( ({ "owner", "shopkeeper", "keeper" }) );
    set_living_name(MY_NAME);
    set_race_name("dwarf");

    set_adj("proud");
    add_adj("rough-bearded");

    set_long(BSN("You are looking at a rough-bearded dwarf. He is the " +
        "keeper of the shop in the " + DWARVEN_RACE_GUILD_NAME + ". Dispite " +
        "of his rough apprearance he is a friendly dwarf and he is willing " +
        "to trade with you."));

    set_title("son of Borin, keeper of the shop of the " +
        DWARVEN_RACE_GUILD_NAME);

    set_gender(G_MALE);

    set_base_stat(SS_STR, COMPUTE_STAT);
    set_base_stat(SS_DEX, COMPUTE_STAT);
    set_base_stat(SS_CON, COMPUTE_STAT);
    set_base_stat(SS_WIS, COMPUTE_STAT);
    set_base_stat(SS_INT, COMPUTE_STAT);
    set_base_stat(SS_DIS, COMPUTE_STAT);

    REFRESH;  /* hp, mana, fatigue  */
    FIX_EUID; /* set the euid right */

    set_alignment(500);

    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_WEP_AXE,      COMPUTE_SKILL);
    set_skill(SS_PARRY,        COMPUTE_SKILL);
    set_skill(SS_DEFENCE,      COMPUTE_SKILL);
    set_skill(SS_AWARENESS,    COMPUTE_SKILL);
    set_skill(SS_UNARM_COMBAT, COMPUTE_SKILL);

    set_mm_in(" arrives.");
    set_mm_out(" walks away.");

    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE_ROOM);

    set_npc_save_file(SAVE_FILE);
    create_remember();
}

void
arm_shopkeeper()
{
    object ob;

    fix_souls();

    CLONE_OBJECT(DWARVEN_RACE_GUILD_WEAPONS + "k_axe");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "k_cloak");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "k_sweater");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "k_pants");

    ob = clone_object(DWARVEN_RACE_GUILD_ARMOURS + "npc_belt");
    ob->move(this_object(), 1);
    ob->set_owner_name(MY_NAME);

    command("wear all");

    ob = clone_object(DWARVEN_RACE_GUILD_OBJECTS + "wallet");
    ob->move(this_object(), 1);

    MONEY_MAKE_GC(random(10))->move(ob, 1);
    MONEY_MAKE_SC(random(20))->move(ob, 1);
    MONEY_MAKE_CC(random(30))->move(ob, 1);
}

void
init_living()
{
    ::init_living();

    init_shop();
}

void
attacked_by(object attacker)
{
    command("wield all");

    ::attacked_by(attacker);
}

int
shop_hook_sell_no_match(string str)
{
    npc_say("You do not have any " + str + " to sell, " + player_name(TP) + ".");
    notify_fail("");
    return 1;
}

int
shop_hook_sold_nothing()
{
    npc_say("You have nothing to sell, " + player_name(TP) + ".");
    notify_fail("");
    return 1;
}

void
shop_hook_sell_no_value(object ob)
{
    npc_say("That " + CAP(LANG_THESHORT(ob)) + " is worthless, " +
        player_name(TP) + ".");
    notify_fail("");
}

void
shop_hook_sell_worn_or_wielded(object ob)
{
    npc_say("You cannot sell " + LANG_THESHORT(ob) + " for you did not " +
        "tell me you wanted to sell worn or wielded objects, " +
        player_name(TP) + ". Add an exclamation mark for that.");
    notify_fail("");
}

void
shop_hook_sell_filled_container(object ob)
{
    npc_say("You cannot sell " + LANG_THESHORT(ob) + " for you did not " +
        "tell me you wanted to sell filled containers, " +
        player_name(TP) + ". Add an exclamation mark for that.");
    notify_fail("");
}

void
shop_hook_sell_no_sell(object ob, string str)
{
    if (stringp(str))
    {
        /* lets hope this looks nice, otherwise use NF(str) */
        npc_say(str);
    }
    else
    {
        npc_say("I cannot buy " + LANG_THESHORT(ob) + ", " +
            player_name(TP) + ".");
    }
    notify_fail("");
}

void
shop_hook_sell_object_stuck(object ob, int err)
{
    npc_say("It seems you are stuck with " + LANG_THESHORT(ob) +
        ", " + player_name(TP) + ".");
    notify_fail("");
}

void
shop_hook_sell_get_money(string str)
{
    write(query_The_name(TP) + " gives you " + str + ".\n");
}

void
shop_hook_buy_no_match(string str)
{
    npc_say("I have no " + str + " to sell you, " + player_name(TP) + ".");
    notify_fail("");
}

void
shop_hook_buy_no_buy(object ob, string str)
{
    if (stringp(str))
    {
        /* If this is ugly, use NF(str) */
        npc_say(str);
    }
    else
    {
        npc_say("How stupid of me, " + player_name(TP) + ". Unfortunately " +
            LANG_THESHORT(ob) + " is not for sale.");
    }

    ob->remove_object();
    notify_fail("");
}

void
shop_hook_cant_carry(object ob, int err)
{
    npc_say("You cannot carry " + LANG_THESHORT(ob) + ", " +
        player_name(TP) + ". I shall put it on the floor for you.");
    notify_fail("");
}

void
shop_hook_buy_magic_money(object ob)
{
    command("quiver at " + CAP(TP->query_real_name()));
    npc_say("What, " + player_name(TP) + "! Pay me in silver or gold if " +
        "you want to deal with me. Come back with real money if you want " +
        LANG_THESHORT(ob) + ".");
    command("curse at " + CAP(TP->query_real_name()));
}

void
shop_hook_buy_pay_money(string str, string change)
{
    write("You give " + str + " to " + query_the_name(TP) + ".\n");

    if (strlen(change))
    {
        write(CAP(PRONOUN(TO)) + " gives you " + change + " back.\n");
    }
}

void
shop_hook_value_not_interesting(object ob)
{
    npc_say(CAP(LANG_THESHORT(ob)) + " does not interest me, " +
        player_name(TP) + ".");
    notify_fail("");
}

void
shop_hook_value_held(object ob, string text)
{
    npc_say("For your " + LANG_THESHORT(ob) + ", " + player_name(TP) +
        ", I could offer you " + text + ".");
}

void
shop_hook_value_store(object ob, string text)
{
    npc_say("For " + LANG_THESHORT(ob) + " you would have to pay me " +
        text + ", " + player_name(TP) + ".");
}

void
shop_hook_value_asking(string str)
{
    say(QCTNAME(TP) + " asks " + QTNAME(TO) + " about some values.");
}

int
shop_hook_value_no_match(string str)
{
    npc_say("We hold no '" + str + "' in stock, " + player_name(TP) +
        ". I am sorry for you.");
    notify_fail("");
}

void
shop_hook_list_empty_store(string str)
{
    npc_say("Unfortunately I am currently sold out, " +
        player_name(TP) + ".");
    notify_fail("");
}

int
shop_hook_list_no_match(string str)
{
    npc_say("We have no '" + str + "' in stock, " + player_name(TP) +
        ". I am sorry for you.");
    notify_fail("");
}

string
neat_text(int *arr)
{
    int i;
    string temp = "";

    if (sizeof(arr) != NUM) /* invalid array */
    {
        return "";
    }

    for (i = (NUM - 1); i >= 0; i--)
    {
        if (arr[i] > 0)
        {
            temp += sprintf("%2d %2s ", arr[i], SHORT_MONEY_TYPES[i]);
        }
        else
        {
            temp += "      ";
        }
    }

    return temp;
}

void
shop_hook_list_object(object ob, int price)
{
    string message = neat_text(split_values(price));

    if (!strlen(message))
    {
        message = "That item wouldn't cost you much.\n";
    }

    write(sprintf("%-35s %20s\n", CAP(LANG_ASHORT(ob)), message));
}

/*
 * The shop defines the sign.. The implementation in /lib/shop is therefore
 * blocked.
 */
int
do_read(string str)
{
    return 0;
}

/*
 * We are friendly for other domains... Solamnian knights may not kill him!
 */
int
query_knight_prestige()
{
    return -5;
}

/*
 * /d/Gondor/common/dwarf_guild/npc/smith.c
 *
 * Copyright (C) Mercade @ Genesis - January 17 1994
 *
 * This smith is the smith in the Dwarven race guild. He will craft any
 * axe you like and he is also capable of reparing an axe if needed. And
 * maybe he will repair other weapons also... I am not sure yet. Give him
 * your belt and he will brand it for you.
 *
 * Apart from repairing weapons, this smith is also capable of crafting
 * axes for you. Those axes are rather configurable, which I like very
 * much! Pickaxes can be sold from stock. The last axe a player orders
 * will be remembered. This to allow people to quickly re-order their
 * prefered axes. The favourite axe is remembered 30 days. In order to
 * maintain your weapons, you can buy a whetstone from Borin too.
 */

inherit "/d/Gondor/common/dwarf_guild/npc/remember";

#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "../axe.h"
#include "../dwarf.h"

#define SAVE_FILE            (DWARVEN_RACE_GUILD_NPCS + "smith_save")
#define PICKAXE              (DWARVEN_RACE_GUILD_WEAPONS + "pick_axe")
#define WARAXE               (DWARVEN_RACE_GUILD_WEAPONS + "axe")
#define WHETSTONE            (DWARVEN_RACE_GUILD_OBJECTS + "whetstone")
#define MY_NAME              "borin"
#define BASE                 80
#define COMPUTE_STAT         (((BASE * 3) / 4) + random(BASE / 2) + 1)
#define COMPUTE_SKILL        max(COMPUTE_STAT, 100)
#define CLONE_OBJECT(s)      clone_object(s)->move(this_object())
#define BRAND_PRICE_PER_CHAR  5 /* in silver coins per char */
#define MY_BRAND             (DWARVEN_RACE_GUILD_PREFIX + "smith_made")
#define REPAIR_IMPOSSIBLE    0
#define REPAIR_PARTIALLY     1
#define REPAIR_FULLY         2
#define REPAIR_NOT_NEEDED    3
#define CLIENT               player_name(client)
#define CHECK_CLIENT         if (!check_client()) return
#define TARGET               OB_NAME(target)
#define LAST_AXE_VARIABLE    "last_axe"
#define TIME_TO_REMEMBER     2592000 /* 30 days */
#define TIME_PROP            "_time_prop"
#define AXE_TYPE_WARAXE      "waraxe"
#define AXE_TYPE_PICKAXE     "pickaxe"
#define AXE_TYPE_WHETSTONE   "whetstone"
#define AXE_LOG              "smith_axe"

#define BUSY_NOTHING 1
#define BUSY_BELT    2
#define BUSY_REPAIR  3
#define BUSY_ORDER   4

/* Global variable, will be saved.
 */
mapping last_axe = ([ ]); /* for every player the last bought axe is stored */

/* Global variables, will not be saved.
 */
static int     busy = 0;  /* the busy status             */
static object  client;    /* the client                  */
static object  target;    /* the object being processed  */
static mapping axes = AXES_DEFINITION;
static string  axe_type;  /* the type of the axe ordered */
static mapping props;     /* the selectable properties   */
static int     new_dull;  /* the new dull for the weapon */
static int     new_corr;  /* the new corr for the weapon */
static int     price;     /* the price to pay in silver  */

/* Prototype.
 */
void update_last_axe();

void
create_monster()
{
    set_name(MY_NAME);
    add_name( ({ "smith", "blacksmith" }) );
    set_living_name(MY_NAME);
    set_race_name("dwarf");

    set_adj("strong");
    add_adj("rough-bearded");

    set_long(BSN("This rough-bearded dwarf is the blacksmith of the " +
        DWARVEN_RACE_GUILD_NAME + ". If you pay him, he will craft any " +
        "axe for you or repair a weapon that is in need."));

    set_title("son of Fror, blacksmith in the " + DWARVEN_RACE_GUILD_NAME);
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
    set_skill(SS_WEP_CLUB,     BASE);
    set_skill(SS_WEP_POLEARM,  BASE);
    set_skill(SS_WEP_AXE,      BASE);
    set_skill(SS_PARRY,        COMPUTE_SKILL);
    set_skill(SS_DEFENCE,      COMPUTE_SKILL);
    set_skill(SS_AWARENESS,    COMPUTE_SKILL);
    set_skill(SS_UNARM_COMBAT, COMPUTE_SKILL);
    set_skill(SS_2H_COMBAT,    COMPUTE_SKILL);

    set_npc_save_file(SAVE_FILE);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_S_WIZINFO,
        BSN("If needed, you can call the function \"reset_smith\" in the " +
        "smith to completelty reset him and make him available for new " +
        "clients."));

    create_remember( ({ LAST_AXE_VARIABLE }) );
    last_axe = query_npc_variable(LAST_AXE_VARIABLE);
    if (!mappingp(last_axe))
    {
        last_axe = ([ ]);
    }

    /* Only update this information on monday. */
    if (ctime(time())[0..2] == "Mon")
    {
        update_last_axe();
    }
}

void
arm_smith()
{
    object ob;

    fix_souls();

    set_mm_in("arrives.");
    set_mm_out("walks away.");

    CLONE_OBJECT(DWARVEN_RACE_GUILD_WEAPONS + "s_hammer");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_WEAPONS + "s_poker");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "s_apron");

    ob = clone_object(DWARVEN_RACE_GUILD_ARMOURS + "npc_belt");
    ob->move(this_object(), 1);
    ob->set_owner_name(MY_NAME);

    command("wield all");
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

    add_action("do_decline", "decline");
    add_action("do_order",   "order");
    add_action("do_order",   "buy");
    add_action("do_pay",     "pay");
    add_action("do_select",  "select");
}

varargs void
drop_object(object obj, object player)
{
    if ((!objectp(obj)) ||
        (ENV(obj) != TO))
    {
        return;
    }

    if (objectp(player) &&
        (ENV(player) == ENV(TO)))
    {
        npc_say("You cannot handle the " + obj->short() + ", " +
            player_name(player) + ". I shall drop it here.");
    }
    else
    {
        command("shout Hey! What about that " + obj->short() + "?");
    }

    command("drop " + OB_NAME(obj));

    if (ENV(obj) == TO)
    {
        obj->move(ENV(TO), 1); /* will always move! */
    }
}

void
available()
{
    drop_object(target);

    busy     = 0;
    client   = 0;
    target   = 0;
    axe_type = 0;
    props    = 0;
    price    = 0;
    axe_type = 0;
}

void
occupy(object obj, object player, int busy_type)
{
    busy   = busy_type;
    client = player;
    target = obj;
}

/*
 * This is an emergency function to reset the smith completely.
 */
void
reset_smith()
{
    mixed alarms = get_all_alarms();
    int   index;

    npc_say("GRRUUHH!!  BLEECH!!  WHREEEEH!!");
    command("puke all"); /* GRIN */

    if ((objectp(target)) &&
        (ENV(target) == TO))
    {
        target->move(ENV(TO), 1);
        LTELL_ROOM(ENV(TO), TO, "In a sudden attack of epilepsy, ",
            " drops the " + target->short() + ".", TO);
    }

    available();

    /* remove all pending alarms. */
    for (index = 0; index < sizeof(alarms); index++)
    {
        remove_alarm(alarms[index][0]);
    }
}

void
client_leaves()
{
    command("shout Leaving so soon, " + CLIENT + "?");
    command("shrug");

    drop_object(target, client);
    available();
}

int
check_client()
{
    if ((!objectp(client)) ||
        (ENV(client) != ENV(TO)))
    {
        drop_object(target, client);
        available();
        return 0;
    }

    return 1;
}

void
return_done()
{
    if ((!objectp(client)) ||
        (ENV(client) != ENV(TO)))
    {
        command("shrug");
        drop_object(target);
    }

    npc_say("Here you are, " + CLIENT + ".");
    command("give " + TARGET + " to " + client->query_real_name());
    drop_object(target, client);

    available();
}

void
brand_belt()
{
    string name = client->query_real_name();

    CHECK_CLIENT;

    if (strlen(target->query_owner_name()))
    {
        npc_say("That belt already has a name branded into it, I do not " +
            "want to add a second name to it, " + CLIENT + ".");
        set_alarm(2.0, 0.0, "return_done");
        return;
    }

    if (!query_met_player(name))
    {
        npc_say("You have not introduced yourself before, " + CLIENT + ".");
        set_alarm(2.0, 0.0, "return_done");
        return;
    }

    npc_say("Oke, " + CLIENT + ", I can brand your name into that belt. " +
        "Your name is " + strlen(name) + " characters long, means that it " +
        "will cost you " + (strlen(name) * BRAND_PRICE_PER_CHAR) +
        " silver coins. Just <pay> me and I will brand your name into it.");
}

void
brand_belt_paid()
{
    CHECK_CLIENT;

    if (!MONEY_ADD(client,
        -(strlen(client->query_real_name()) * BRAND_PRICE_PER_CHAR * 12)))
    {
        command("hmph");
        npc_say("You cannot afford to pay me, " + CLIENT + ". Maybe you " +
            "should have chosen a shorter name.");
        command("giggle mischieviously");
        set_alarm(4.0, 0.0, "return_done");
        return;
    }

    set_this_player(client);

    WRITE("You pay " + TO->query_the_name(client) + " his fee.");
    say(QCTNAME(client) + " pays " + QTNAME(TO) + " his fee.\n");

    command("thank " + CAP(client->query_real_name()));
    npc_say("I shall start on it at once, " +
        ((client->query_gender() == G_MALE) ? "Sir" :
        ((client->query_gender() == G_FEMALE) ? "Ma'am" : "mirky blob")) +
        ".");

    TELL_ROOM(ENV(TO), TO, " puts a few branding-irons into the fire " +
        "to let them become red-hot.", TO);
    npc_say("It won't take long, " + CLIENT + ". You can wait here.");

    set_alarm( 6.0, 0.0, "brand_halfway");
    set_alarm(12.0, 0.0, "return_done");
}

void
brand_halfway()
{
    LTELL_ROOM(ENV(TO), TO, "Then ", " takes the branding-irons out of " +
        "the fire one by one and brands some letters into the belt. You " +
        "smell the scent of burning leather.", TO);

    target->set_owner_name(client->query_real_name());
}

int
get_possible_repair(int current, int repair, int new)
{
    if (current == repair) 
    {
        return REPAIR_NOT_NEEDED;
    }
    else if (current == new)
    {
        return REPAIR_FULLY;
    }
    else if (repair == new)
    {
        return REPAIR_IMPOSSIBLE;
    }

    return REPAIR_PARTIALLY;
}

void
repair_weapon()
{
    int dull        = target->query_dull();
    int corr        = target->query_corroded();
    int repair_dull = target->query_repair_dull();
    int repair_corr = target->query_repair_corr();
    int can_repair_dull;
    int can_repair_corr;
    int initial_value;
    int current_value;
    string str;
    string weapon = target->short();

    CHECK_CLIENT;

    npc_say("Let me take a look at that " + weapon + " of yours, " + CLIENT +
        ".");
    command("inspect " + TARGET);

    if (target->query_prop(OBJ_I_BROKEN))
    {
        command("ack");
        npc_say("Your " + weapon + " is broken! I cannot fix it.");
        set_alarm(4.0, 0.0, "return_done");
        return;
    }

    if ((dull == repair_dull) &&
            (corr == repair_corr))
    {
        if ((dull + corr) == 0)
        {
            npc_say("Your " + weapon + " is in excellent condition, " +
                CLIENT + ". Just like if it was crafted only recently.");
        }
        else
        {
            npc_say("Your " + weapon + " has been repaired before, " + CLIENT +
                ". However, it is still in excellent condition now. There " +
                "is nothing that needs to done about it.");
        }

        if (target->id(MY_BRAND))
        {
            npc_say("Obviously, one should expect weapons that were crafted " +
                "or repaired by me to be in an excellent condition!");
        }

        command("polish " + TARGET);
        set_alarm(4.0, 0.0, "return_done");
        return;
    }

    new_dull = dull;
    while (!F_LEGAL_WEAPON_REPAIR_DULL(new_dull, dull))
    {
        new_dull--;
    }

    new_corr = corr;
    while (!F_LEGAL_WEAPON_REPAIR_CORR(new_corr, corr))
    {
        new_corr--;
    }

    can_repair_dull = get_possible_repair(dull, repair_dull, new_dull);
    can_repair_corr = get_possible_repair(corr, repair_corr, new_corr);

    switch(((can_repair_dull * 4) + can_repair_corr))
    {
    case 0:
    case 3:
    case 12:
    case 15:
        npc_say("There is nothing I can do with your " + weapon + ", " + 
            CLIENT + ".");
        set_alarm(4.0, 0.0, "return_done");
        return;
        break;
    case 1:
        str = "Your " + weapon + " cannot be repaired, though I can polish " +
            "it a little, " + CLIENT + ".";
        break;
    case 2:
        str = "Your " + weapon + " cannot be repaired, though I can give it " +
            "back its original shine, " + CLIENT + ".";
        break;
    case 4:
        str = "I cannot remove the rust from your " + weapon + ", " + CLIENT +
            ", though I can repair it a little."; 
        break;
    case 5:
        str = "I can polish your " + weapon + ", " + CLIENT + " and I can " +
            "repair it a little.";
        break;
    case 6:
        str = "I can only repair your " + weapon + " a little, " + CLIENT +
            ", though I can give it back its original shine.";
        break;
    case 7:
        str = "Let me repair your " + weapon + " for you, " + CLIENT + ".";
        break;
    case 8:
        str = "I cannot remove the rust from your " + weapon + ", " + CLIENT +
            ", but I can repair it completely.";
        break;
    case 9:
        str = "I can polish your " + weapon + " some and I can repair it " +
            "completely, " + CLIENT + ".";
        break;
    case 10:
    case 11:
    case 14:
        str = "I can make your " + weapon + " as new again, " + CLIENT + ".";
        break;
    case 13:
        str = "Let me polish your " + weapon + " a little, " + CLIENT + ".";
        break;
    default:
        str = "This should not have happened. Please make a bug-report.";
        break;
    }

    current_value = target->query_value();

    if (target->query_prop(OBJ_I_BROKEN))
    {
        target->remove_prop(OBJ_I_BROKEN);
        initial_value = target->query_value();
        target->add_prop(OBJ_I_BROKEN, 1);
    }
    else
    {
        initial_value = current_value;
    }

    price = ((current_value *
        F_WEAPON_VALUE_REDUCE(dull - new_dull,    corr - new_corr)) /
        F_WEAPON_VALUE_REDUCE(dull - repair_dull, corr - repair_corr));
    price -= initial_value;

    /*
     * You pay the increase in value + 50%
     * price + 50% / 12 (silver) == price / 8
     */
    price = ((price <= 8) ? 1 : (price / 8));

    npc_say(str);
    npc_say("For " + price + " silvers I shall repair your " + weapon +
        " as good as possible, " + CLIENT + ". Just <pay> me and I will " +
        "get to work on it.");
}

void
repair_weapon_paid()
{
    CHECK_CLIENT;

    if (!MONEY_ADD(client, -(price * 12)))
    {
        command("hmph");
        npc_say("You cannot afford to pay me, " + CLIENT + ". I cannot " +
            "repair your " + target->short() + ".");
        set_alarm(4.0, 0.0, "return_done");
        return;
    }

    set_this_player(client);

    WRITE("You pay " + TO->query_the_name(client) + " his fee.");
    say(QCTNAME(client) + " pays " + QTNAME(TO) + " his fee.\n");

    command("thank " + CAP(client->query_real_name()));
    npc_say("I shall start on it at once, " +
        ((client->query_gender() == G_MALE) ? "Sir" :
        ((client->query_gender() == G_FEMALE) ? "Ma'am" : "mirky blob")) +
        ".");

    TELL_ROOM(ENV(TO), TO, " holds the " + target->short() + " in the fire " +
        "for a moment and starts to work on it.", TO);
    npc_say("It won't take long, " + CLIENT + ". Wait here.");

    set_alarm( 8.0, 0.0, "repair_weapon_halfway");
    set_alarm(12.0, 0.0, "return_done");
}

void
repair_weapon_halfway()
{
    LTELL_ROOM(ENV(TO), TO, "Suddenly ", (" puts the " + target->short() +
        " in a bucket of icy water. Some clouds of steam block your vision " +
        "for a moment. He then starts to polish the weapon with a soft " +
        "cloth."), TO);

    target->add_name(MY_BRAND);
    target->set_repair_dull(new_dull);
    target->set_repair_corr(new_corr);
    target->remove_prop(OBJ_I_BROKEN);
}

void
order_pickaxe_paid()
{
    CHECK_CLIENT;

    FIX_EUID;

    target = clone_object(PICKAXE);
    target->move(TO, 1);
    target->add_name(TARGET);
    price = ((target->query_prop(OBJ_I_VALUE) / 12) + 1);

    if (!MONEY_ADD(client, -(price * 12)))
    {
        command("hmph");
        npc_say("You cannot afford to pay me, " + CLIENT + ". I cannot " +
            "sell you a pickaxe.");
        target->remove_object();
        available();
        return;
    }

    set_this_player(client);

    WRITE("You pay " + TO->query_the_name(client) + " the price.");
    say(QCTNAME(client) + " pays " + QTNAME(TO) + " the price.\n");

    command("thank " + CAP(client->query_real_name()));
    return_done();
}

void
order_waraxe_paid()
{
    CHECK_CLIENT;

    FIX_EUID;

    target = clone_object(WARAXE);
    target->move(TO, 1);
    target->add_name(TARGET);
    target->set_properties(props);

    price = target->query_prop(OBJ_I_VALUE);

    if(!MONEY_ADD(client, -price))
    {
        command("hmph");
        npc_say("You cannot afford to pay me the " + (price / 12) +
            " silvers, " + CLIENT + ". I cannot sell you a waraxe. Maybe " +
            "you should select an axe of less quality. However, I counsel " +
            "you to save some more money!");
        target->remove_object();
        available();
        return;
    }

#ifdef AXE_LOG
    log_file(AXE_LOG, sprintf("%-24s %-12s %-1s\n", ctime(time()),
        CAP(client->query_real_name()), implode(m_values(props), " ")));
#endif

    last_axe[client->query_real_name()] = ([ TIME_PROP : time() ]) + props;
    set_npc_variable(LAST_AXE_VARIABLE, last_axe);
    save_npc();

    set_this_player(client);

    WRITE("You pay " + TO->query_the_name(client) + " the price.");
    say(QCTNAME(client) + " pays " + QTNAME(TO) + " the price.");

    npc_say("Congratulations, " + CLIENT +
        ", you have bought yourself a quality weapon, a " + CAP(MY_NAME) +
        " original. Take good care of it. If the blade gets dull after " +
        "having lain in too many orc necks, you can always come back to " +
        "have it sharpened.");
    npc_say("If you want to buy another " + target->short() + ", all you " +
        "have to type is <order last waraxe> for I will remember what my " +
        "dear customers order.");
    command("thank " + CAP(client->query_real_name()));
    return_done();
}

void
order_whetstone_paid()
{
    CHECK_CLIENT;

    FIX_EUID;

    target = clone_object(WHETSTONE);
    target->move(TO, 1);
    target->add_name(TARGET);
    target->add_prop(OBJ_I_VALUE, price);

    if (!MONEY_ADD(client, -price))
    {
        command("hmph");
        npc_say("You cannot afford to pay me, " + CLIENT + ". I cannot " +
            "sell you a grindstone now.");
        target->remove_object();
        available();
        return;
    }

    set_this_player(client);

    WRITE("You pay " + TO->query_the_name(client) + " the price.");
    say(QCTNAME(client) + " pays " + QTNAME(TO) + " the price.\n");

    command("thank " + CAP(client->query_real_name()));
    return_done();
}

void
cannot_process()
{
    CHECK_CLIENT;

    npc_say("I do not know what to do with your " + target->short() + ", " +
        CLIENT + ". I shall return it to you.");

    return_done();
}


void
return_busy(object obj, object player)
{
    if (!objectp(player) ||
        (ENV(player) != ENV(TO)))
    {
        command("shrug");
        drop_object(obj);
        return;
    }

    /*
     * If the smith isn't busy after all he will help the player.
     */
    if ((!busy) && (objectp(player)))
    {
        obj->move(player, 1);
        obj->move(TO, 1);
    }

    npc_say("Sorry, " + player_name(player) + ", but I am already busy with " +
        ((client == player) ? "you": CLIENT) + ".");
    command("give " + OB_NAME(obj) + " to " + player->query_real_name());
    drop_object(obj, player);
}

int
do_decline(string str)
{
    if (TP != client)
    {
        npc_say("I have not made you an offer, " + player_name(TP) + ". " +
            "There is nothing for you to decline.");
        return 1;
    }

    npc_say("Oke, " + CLIENT + ". I regret it, but it is a free world.");

    if (objectp(target))
    {
        npc_say("You shall receive your property back.");
        set_alarm(4.0, 0.0, "return_done");
    }
    else
    {
        available();
    }

    return 1;
}

int
axe_price()
{
    int    i;
    int    to_pay = price;
    string *args = m_indices(axes);

    for (i = 0; i < sizeof(args); i++)
    {
        to_pay += axes[args[i]][INDEX_PRICES][member_array(props[args[i]],
            axes[args[i]][INDEX_TYPES])];
    }

    return to_pay;
}

int
do_order(string str)
{
    object tp = TP;
    object axe;

    if (objectp(client))
    {
        NFN0("I am already busy with " +
            ((client == tp) ? "you" : CLIENT) + ".\n");
    }

    switch(str)
    {
    case "pickaxe" :
    case "pick-axe":
    case "pick axe":
        catch(axe = clone_object(PICKAXE));
        if (!objectp(axe))
        {
            npc_say("Unfortunately I do not have any pickaxes in stock. " +
                "However, this should not have happened. Please make a " +
                "bugreport.");
            return 1;
        }

        /* Will fail if the value of the axe = 0. Which it never should. */
        npc_say("Pickaxes I have in stock. They will cost you " +
            ((axe->query_prop(OBJ_I_VALUE) / 12) + 1) +
            " silvers. Just <pay> me and you can take one with you. If you " +
            "do not want to buy the axe, just <decline>.");

        axe->remove_object();
        axe_type = AXE_TYPE_PICKAXE;
        occupy(0, tp, BUSY_ORDER);
        return 1;

    case "waraxe" :
    case "war-axe":
    case "war axe":
        catch(axe = clone_object(WARAXE));
        if (!objectp(axe))
        {
            npc_say("Unfortunately I lack some of the necessary supplies " +
                "necessary to craft axes. Please make a bugreport.");
            return 1;
        }

        price = (axe->query_prop(OBJ_I_VALUE) / 12);
        npc_say("Sure, I can craft you a waraxe. You shall have to tell " +
            "me what kind of axe you want. Use the command <select> to " +
            "do that. Do \"select\" without arguments for more " +
            "information. Once you have selected all properties, you can " +
            "<pay> me. The base price is " + price +
            " silvers. Do <decline> at any point to stop ordering.");

        axe->remove_object();
        axe_type = AXE_TYPE_WARAXE;
        props = DEFAULT_AXE_PROPERTIES;
        occupy(0, tp, BUSY_ORDER);
        return 1;

    case "last waraxe" :
    case "last war-axe":
    case "last war axe":
        catch(axe = clone_object(WARAXE));
        if (!objectp(axe))
        {
            npc_say("Unfortunately I lack some of the necessary supplies " +
                "necessary to craft axes. Please make a bugreport.");
            return 1;
        }

        if (!m_sizeof(last_axe[tp->query_real_name()]))
        {
            command("apologize to " + CAP(tp->query_real_name()));
            npc_say("I am very sorry, " + player_name(tp) +
                ", but I forgot the last axe you ordered if you did order " +
                "here before. My memory does not last longer than 30 days.");
            return do_order("war-axe");
        }

        axe_type = AXE_TYPE_WARAXE;
        props = ([ ]) + last_axe[tp->query_real_name()];
        props = m_delete(props, TIME_PROP);
        price = (axe->query_prop(OBJ_I_VALUE) / 12);
        axe->remove_object();

        npc_say("Naturally I do remember what kind of axe you last ordered, " +
            player_name(tp) + ". You can <pay> me now or <decline> if you " +
            "do not want it after all. The price would be " + axe_price() +
            " silvers. Obviously, you can use <select> to check the " +
            "properties or select different ones.");

        occupy(0, tp, BUSY_ORDER);
        return 1;

    case "whetstone"  :
    case "whet-stone" :
    case "whet stone" :
    case "grindstone" :
    case "grind-stone":
    case "grind stone":
        catch(axe = clone_object(WHETSTONE));
        if (!objectp(axe))
        {
            npc_say("Geez... I am out of whetstones. How strange. Please " +
                "make a bugreport about this.");
            return 1;
        }

        price = axe->query_prop(OBJ_I_VALUE);
        /* Will fail if the value of the axe = 0. Which it never should. */
        npc_say("Whetstones I have in stock. They will cost you " +
            ((axe->query_prop(OBJ_I_VALUE) / 12) + 1) +
            " silvers. Just <pay> me and you can take one with you. If you " +
            "do not want to buy the stone, just <decline>.");

        axe->remove_object();
        axe_type = AXE_TYPE_WHETSTONE;
        occupy(0, tp, BUSY_ORDER);
        return 1;
    }

    npc_say("To order an axe, just <order type>. The possible types of axes " +
        "that I can craft you are \"war-axe\" and \"pickaxe\". If you have " +
        "recently bought a war-axe here, you can ask for the \"last " +
        "war-axe\" too and I also have whetstones for sale.");
    return 1;
}

void
write_waraxe_setting_options(string option)
{
    /* Have to do ({ }) + in order to get rid of pointer manipulation.
     */
    string *possible = ({ }) + axes[option][INDEX_TYPES];
    int     index;

    for (index = 0; index < sizeof(possible); index++)
    {
        possible[index] = sprintf("%-10s  %3d",
            possible[index], axes[option][INDEX_PRICES][index]);
    }

    WRITE("Description on \"" + option + "\":");
    WRITE(axes[option][INDEX_DESCRIPTION]);

    WRITE("Possible options with their relative price in silver coins " +
        "behind them:");
    write(sprintf("%-74#s\n", implode(possible, "\n")));

    npc_say("Currently, " + CLIENT + ", the \"" + option + "\" is set to \"" +
        props[option] + "\". In order to change it, do <select property " +
        "option>. (Example: select " + option + " " +
        ONE_OF_LIST(axes[option][INDEX_TYPES]) +
        ") When done selecting, you can <pay> me.");
}

void
select_waraxe_option(string option, string setting)
{
    if (member_array(setting, axes[option][INDEX_TYPES]) == -1)
    {
        WRITE("The value \"" + setting + "\" is not a valid value for " +
            "the property \"" + option + "\". Please do <select " +
            option + "> to get a list of all possible values.");
        return;
    }

    props[option] = setting;
    WRITE("Very well. You select \"" + setting + "\" as value for the " +
        "property \"" + option + "\".");
    return;
}

void
select_overview()
{
    int    i;
    string *args = m_indices(axes);

    npc_say("With the command <select>, " + CLIENT + ", you can tell me " +
        "exactly which kind of axe you want. There are several properties " +
        "to select. Do <select property> for a description of the property " +
        "and the possible values. (Example: select " + ONE_OF_LIST(args) +
        ")");

    for (i = 0; i < sizeof(args); i++)
    {
        args[i] = sprintf("%-15s  %-10s", args[i], props[args[i]]);
    }

    WRITE("The properties are with their current values are:\n");
    write(sprintf("%-74#s\n", implode(args, "\n")));
    WRITE("In the current configuration, the price would be " + axe_price() +
        " silver coins. You can <pay> me if you are done selecting or do " +
        "<decline> to decline the offer.");
}

int
do_select(string str)
{
    string *args;

    CHECK_CLIENT 0;

    if (this_player() != client)
    {
        NFN0("I am busy with " + CLIENT +
            ". You shall have to wait for your turn, " +
            player_name(this_player()) + ".");
    }

    if (axe_type != AXE_TYPE_WARAXE)
    {
        NFN0("You can only select properties when ordering for a war-axe, " +
            CLIENT + ". The other things I can sell you here cannot be " +
            "crafted to your specific requests.");
    }

    if (!strlen(str))
    {
        select_overview();
        return 1;
    }

    args = explode(lower_case(str), " ");

    /* Selected an illegal property.
     */
    if (member_array(args[0], m_indices(axes)) == -1)
    {
        npc_say("You have chosen a non-existent property (" + args[0] +
            ") for the axe, " + CLIENT +
            ". Use \"select\" without arguments to see all possible " +
            "properties.");

        return 1;
    }

    switch(sizeof(args))
    {
    /* Only the property name, inform about the possible settings.
     */
    case 1:
        write_waraxe_setting_options(args[0]);
        return 1;

    case 2:
        select_waraxe_option(args[0], args[1]);
        return 1;

    default:
        npc_say("Incorrect number of arguments, " + CLIENT +
            ". You should do \"select [property [setting]]\".");
        return 1;
    }

    npc_say("This is not possible! Please make a bugreport about this. " +
        "(end of \"do_select()\")");
    return 1;
}

int
do_pay(string str)
{
    object *oblist = PARSE_THIS(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Whom do you want to pay?");
    }

    if (sizeof(oblist) != 1)
    {
        NFN0("You can only pay one person at a time.");
    }

    if (oblist[0] != TO)
    {
        NFN0("To pay " + oblist[0]->query_the_name(TP) + ", just give " +
            OBJECTIVE(oblist[0]) + " some money.");
    }

    if (client != TP)
    {
        npc_say("I am not serving you at the moment, " + player_name(TP) +
            ". There is no need for you to pay me anything.");
        return 1;
    }

    write("You search in your pocket for money to pay " +
        TO->query_the_name(TP) + ".\n");

    if (busy == BUSY_BELT)
    {
        set_alarm(4.0, 0.0, "brand_belt_paid");
        return 1;
    }

    if (busy == BUSY_REPAIR)
    {
        set_alarm(4.0, 0.0, "repair_weapon_paid");
        return 1;
    }

    if (busy == BUSY_ORDER)
    {
        set_alarm(4.0, 0.0, ("order_" + axe_type + "_paid"));
        return 1;
    }

    /* should never end up here. */
    npc_say("There is no reason for you to pay me, " + CLIENT +
        ". You can keep your hard earned money!");
    available();
    return 1;
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from))
    {
        return;
    }

    /* He does not want coins. I'm too lazy to <give> them back. */
    if (function_exists("create_heap", obj) == "/std/coins")
    {
        set_alarm(1.0, 0.0, "npc_say", ("In order to give me my fee, just " +
            "<pay> me. I shall return you those coins, " + player_name(from) +
            "."));
        obj->move(from, 1);
        return;
    }

    if (obj->query_lock())
    {
        set_alarm(1.0, 0.0, "npc_say", ("That " + obj->short() +
            " is protected. I cannot do anything with it. Here, you " +
            "have it back already."));
        obj->move(from, 1);
        return;
    }

    if (busy)
    {
        set_alarmv(2.0, 0.0, "return_busy", ({ obj, from }) );
        return;
    }

    if (obj->id(DWARVEN_RACE_GUILD_BELT_ID))
    {
        occupy(obj, from, BUSY_BELT);
        set_alarm(4.0, 0.0, "brand_belt");
        return;
    }

    if (function_exists("create_object", obj) == "/std/weapon")
    {
        occupy(obj, from, BUSY_REPAIR);
        set_alarm(4.0, 0.0, "repair_weapon");
        return;
    }

    occupy(obj, from, BUSY_NOTHING);
    set_alarm(4.0, 0.0, "cannot_process");
}

void
update_last_axe()
{
    int    index;
    string *players;

    players = m_indices(last_axe);

    for(index = 0; index < sizeof(players); index++)
    {
        if ((last_axe[players[index]][TIME_PROP] + TIME_TO_REMEMBER) < time())
        {
            last_axe = m_delete(last_axe, players[index]);
        }
    }

    set_npc_variable(LAST_AXE_VARIABLE, last_axe);
    save_npc();
}

object
query_client()
{
    return client;
}

/*
 * We are friendly to other domains. Solamnian Knights should not kill him.
 */
int
query_knight_prestige()
{
    return -5;
}

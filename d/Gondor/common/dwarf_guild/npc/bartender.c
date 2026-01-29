/*
 * /d/Gondor/common/dwarf_guild/npc/bartender.c
 *
 * The bartender in the pub in the dwarven race guild
 *
 * /Mercade, 7 January 1994
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */

inherit "/d/Gondor/common/dwarf_guild/npc/remember";

#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/logkill.c"
#include "../dwarf.h"

#define SAVE_FILE         (DWARVEN_RACE_GUILD_NPCS + "bartender_save")
#define MY_NAME           "alion"
#define BASE              60
#define COMPUTE_STAT      (((BASE * 4) / 3) + random(BASE / 2) + 1)
#define COMPUTE_SKILL     max(COMPUTE_STAT, 100)
#define CLONE_OBJECT(s)   clone_object(s)->move(this_object(), 1)
#define TARGET(o)         ("drink_" + OB_NUM(o))

#define LEAVE_MESSAGES                       \
    ({ "Catch you later, #!",                \
       "Come back soon, big spender!",       \
       "Drop by any time, #!",               \
       "You bring joy to my humble pub, #!", \
       "Good hunting, #!",                   \
       "Have a nice day!",                   \
    })

/*
 * Global variables
 */
static int    no_shout = 0;
static string *leave_messages = LEAVE_MESSAGES;
static mixed  served_drinks;
/*
 * This variable hold all drinks that the bartender will serve. It is
 * composed in and set from the pub. For more details on the format of the
 * drinks see the pub.
 */
#define INDEX_DRINKS_PARSE 1
#define INDEX_DRINKS_FILE  2

void
create_monster() 
{
    set_name(MY_NAME);
    add_name( ({ "bartender", "keeper" }) );
    set_living_name(MY_NAME);
    set_race_name("dwarf");

    set_adj("long-bearded");
    add_adj("jovial");

    set_long(BSN("You are looking at a long-bearded dwarf. He is the " +
        "bartender of the pub in the " + DWARVEN_RACE_GUILD_NAME + ". If " +
        "you order a drink, he is more than willing to serve you."));

    set_title("son of Oin, bartender in the " + DWARVEN_RACE_GUILD_NAME);

    set_gender(G_MALE);

    set_base_stat(SS_STR, COMPUTE_STAT);
    set_base_stat(SS_DEX, COMPUTE_STAT);
    set_base_stat(SS_CON, COMPUTE_STAT);
    set_base_stat(SS_WIS, COMPUTE_STAT);
    set_base_stat(SS_INT, COMPUTE_STAT);
    set_base_stat(SS_DIS, COMPUTE_STAT);

    REFRESH;  /* hp, mana, fatigue  */
    FIX_EUID; /* set the euid right */

    set_alignment(400);

    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_WEP_AXE,      BASE);
    set_skill(SS_PARRY,        COMPUTE_SKILL);
    set_skill(SS_DEFENCE,      COMPUTE_SKILL);
    set_skill(SS_AWARENESS,    COMPUTE_SKILL);
    set_skill(SS_UNARM_COMBAT, COMPUTE_SKILL);

    set_npc_save_file(SAVE_FILE);
    create_remember();
}

void
init_living()
{
    ::init_living();

    add_action("do_buy", "buy");
    add_action("do_buy", "order");
}

void
arm_barkeeper()
{
    object ob;

    fix_souls();

    CLONE_OBJECT(DWARVEN_RACE_GUILD_WEAPONS + "k_axe");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "k_cloak");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "k_sweater");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "k_pants");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "b_apron");

    ob = clone_object(DWARVEN_RACE_GUILD_ARMOURS + "npc_belt");
    ob->move(this_object(), 1);
    ob->set_owner_name(MY_NAME);

    command("wear all");

    ob = clone_object(DWARVEN_RACE_GUILD_OBJECTS + "wallet");
    ob->move(this_object());

    MONEY_MAKE_GC(random(10))->move(ob, 1);
    MONEY_MAKE_SC(random(20))->move(ob, 1);
    MONEY_MAKE_CC(random(30))->move(ob, 1);
}

void
attacked_by(object attacker)
{
    command("wield all");

    ::attacked_by(attacker);
}

int
do_buy(string str)
{
    object  tp = TP;
    int     i;
    object  drink;
    string *words;
    string  drink_id;
    int     size;

    if (!strlen(str))
    {
        npc_say("What do you want to " + query_verb() + ", " +
            player_name(tp) + "?");
        return 1;
    }

    if (!sizeof(served_drinks))
    {
        npc_say("We are currently sold out, " + player_name(tp) + ". I am " +
            "very sorry, but I cannot serve you now. Please make a " +
            "bugreport about this.");
        return 1;
    }

    words = explode(str, " ");
    if (sizeof(words) > 1)
    {
        size = LANG_NUMW(words[0]);
    }

    if (size > 1)
    {
        SAY(" orders some drinks.");
        str = implode(words[1..], " ");
    }
    else
    {
        SAY(" orders a drink.");
        size = 1;
    }

    for (i = 0; i < sizeof(served_drinks); i++)
    {
        if (parse_command(str, tp, served_drinks[i][INDEX_DRINKS_PARSE]))
        {
            break;
        }
    }

    if (i == sizeof(served_drinks))
    {
        npc_say("Unfortunately I do not serve " + str + ", " +
            player_name(tp) + ", but I will be happy to serve you something " +
            "else if you please.");
        return 1;
    }

    catch(drink = clone_object(DWARVEN_RACE_GUILD_OBJECTS +
        served_drinks[i][INDEX_DRINKS_FILE]));

    if (!objectp(drink))
    {
        npc_say("I am terribly sorry, " + player_name(tp) + ", but I am " +
            "out of " + str + " right now. Please make a bugreport about " +
            "it so I can replenish my stock.");
        return 1;
    }

    drink->set_heap_size(size);
    if (!MONEY_ADD(tp,
        -(size * F_VALUE_ALCO((int)drink->query_alco_amount()))))
    {
        command("hmph");
        npc_say("You cannot afford to buy " + ((size == 1) ? "" : "all ") +
            drink->short() + ", " + player_name(tp) + ".");
        drink->remove_object();
        return 1;
    }

    drink_id = TARGET(drink);
    drink->add_name(drink_id);
    drink->add_pname(drink_id);
    drink->move(TO, 1);
    command("give all " + drink_id + " to " + tp->query_real_name());

    if (present(drink_id, TO))
    {
        npc_say("You are too loaded to carry " +
            ((size == 1) ? "the drink" : "all drinks") + ", " +
            player_name(tp) + ". I shall put " +
            ((size == 1) ? "it" : "them") + " down for you to take.");
        command("drop all " + drink_id);
        return 1;
    }

    npc_say("Here you are, " + player_name(tp) + ".");
    return 1;
}

/*
 * This function should be called from the pub with the mapping of drinks
 * that will be served here.
 */
void
set_drinks(mixed drinks)
{
    served_drinks = drinks;
}

/*
 * If a living leaves the pub, we are notified.
 */
void
player_leaves(object player)
{
    if (no_shout)
    {
        return;
    }

    if (!CAN_SEE(TO, player) || !CAN_SEE_IN_ROOM(TO))
        return;
    set_alarm(0.5, 0.0, "command", ("shout " +
        implode(explode(ONE_OF_LIST(leave_messages), "#"),
        player_name(player))));

    no_shout = 1;
    set_alarm(5.0, 0.0, "remove_no_shout");
}

void
remove_no_shout()
{
    no_shout = 0;
}

/*
 * We are friendly for other domains, Solamnian knights may not kill him!
 */
int
query_knight_prestige()
{
    return -5;
}

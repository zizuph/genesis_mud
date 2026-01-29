/*
 * Based Raven's Smith from the mud Sex & Violence, 2001
 * Removed forging abilities
 * Finwe, October 2007
 */

inherit "/lib/trade";
#include <exec.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

/*
 * === global variables ==================================================
 * =============================================================== *** ===
 */

#define ARMOUR_PATH        ("/std/armour")
#define WEAPON_PATH        ("/std/weapon")

#define REPAIR_COST(item)  (item->query_prop(OBJ_I_VALUE) / 20)
#define POLISH_COST(item)  (item->query_prop(OBJ_I_VALUE) / 20)
#define MEND_COST(item)    ((item->check_armour() ?           \
                            F_VALUE_ARMOUR(item->query_ac()) :\
                            F_VALUE_WEAPON(item->query_pen(), \
                            item->query_hit())) * 2)
#define OBTAIN_COST(item)  (item->query_prop(OBJ_I_VALUE) *  4)

#define MODULE_ARMOUR      (   0)
#define MODULE_WEAPON      (   1)
#define MORE(x)            this_player()->more(read_file(x, 2))


/*
 * === support routines ==================================================
 * =============================================================== *** ===
 */

/*
 * Function name : appeal
 * Description   : the appeal of the module to the player, this hook helps
 *                 in smithy behaviour creating, for example if your smith
 *                 hates dwarves then this hook can return "filthy dwarf"
 *                 if the player is dwarf, or if the smith is funny he can
 *                 call each hobbit "furball"
 * Arguments     : object  - player object
 * Returns       : string  - appeal string
 */

string
appeal(object player)
{
    string  *member = explode(player->query_nonmet_name(), " ");

    return implode(member - ({"a", "an"}), " ");
}

/*
 * Function name : hook_smithy_answer_dark_room
 * Description   : refuse to deal with player when the room is dark
 * Arguments     : void    - no arguments
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_answer_dark_room()
{
    command("say Uhmm, you wouldn't by any chance have a torch handy?");
    command("say It's too dark for me to do business.");
    return 1;
}

/*
 * Function name : hook_smithy_answer_invisible
 * Description   : refuse to deal with player when can't see him
 * Arguments     : void    - no arguments
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_answer_invisible()
{
    command("say Uhmm, where are you hiding? I can't see you!");
    command("peer suspiciously");
    return 1;
}

/*
 * Function name : hook_smithy_repair_faulty_syntax
 * Description   : called when player tries to repair with bad syntax
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_repair_faulty_syntax(string letter)
{
    notify_fail(CAP(query_verb()) + " what?\n");
    return 0;
}

/*
 * Function name : hook_smithy_repair_faulty_object
 * Description   : called when player tries to repair not weapon or armour
 * Arguments     : object  - the object player tries to repair
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_repair_faulty_object(object item)
{
    command("say " + CAP(LANG_THESHORT(item)) + " is not an armour, it"  +
            " isn't a weapon either, how should I repair this?");
    command("smile merrily");
    return 1;
}

/*
 * Function name : hook_smithy_repair_cannot_repair
 * Description   : called when object cannot be repaired any firther
 * Arguments     : object  - the object
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_repair_cannot_repair(object item)
{
    string  verb = (item->check_weapon() ? "sharpened" : "repaired");

    command("say " + CAP(LANG_THESHORT(item)) + " cannot be " + verb +
            " any further!");
    return 1;
}

/*
 * Function name : hook_smithy_repair_cannot_afford
 * Description   : called when player cannot afford the repairing
 * Arguments     : object  - the object player tries to repair
 *                 int     - the cost of repairing
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_repair_cannot_afford(object item, int cost)
{
    command("say You cannot afford to have " + LANG_THESHORT(item) +
            " sharpened!");
    command("gesture");
    return 1;
}

/*
 * Function name : hook_smithy_repair_notify_repair
 * Description   : notify the player about the repair
 * Arguments     : object  - the repaired object
 *                 int*    - array of coins player payed
 *                 int*    - array of coins player got back
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_repair_notify_repair(object item, int* charge, int* change)
{
    string  verb = (item->check_weapon() ? " sharpens " : " repairs "),
            name = LANG_THESHORT(item);

    TP->catch_msg("You give " + name + " to " + QTNAME(TO) + ".\n");
    say(QCTNAME(TP)+" gives " + name + " to " + QTNAME(TO) + ".\n");
    tell_room(ENV(TO), QCTNAME(TO) + verb + name + ".\n");
    TP->catch_msg(QCTNAME(TO) + " gives you " + name + ".\n");
    say(QCTNAME(TO)+" gives " + name + " to " + QTNAME(TP) + ".\n");

    TP->catch_msg("You pay " + QTNAME(TO) + " " + text(charge) + ".\n");
    if (strlen(text(change))) write("You get "+text(change)+" back.\n");
}

/*
 * Function name : hook_smithy_polish_faulty_syntax
 * Description   : called when player tries to polish with bad syntax
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_polish_faulty_syntax(string letter)
{
    notify_fail(CAP(query_verb()) + " what?\n");
    return 0;
}

/*
 * Function name : hook_smithy_polish_faulty_object
 * Description   : called when player tries to polish not weapon or armour
 * Arguments     : object  - the object player tries to polish
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_polish_faulty_object(object item)
{
    command("say " + CAP(LANG_THESHORT(item)) + " is not a weapon, how"  +
            " should I polish it?");
    command("smile merrily");
    return 1;
}

/*
 * Function name : hook_smithy_polish_cannot_polish
 * Description   : called when object cannot be polished any firther
 * Arguments     : object  - the object
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_polish_cannot_polish(object item)
{
    command("say " + CAP(LANG_THESHORT(item)) + " cannot be polished" +
            " any further!");
    return 1;
}

/*
 * Function name : hook_smithy_polish_cannot_afford
 * Description   : called when player cannot afford the polishing
 * Arguments     : object  - the object player tries to polish
 *                 int     - the cost of polishing
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_polish_cannot_afford(object item, int cost)
{
    command("say You cannot afford to have " + LANG_THESHORT(item) +
            " polished!S.");
    command("gesture");
    return 1;
}

/*
 * Function name : hook_smithy_polish_notify_polish
 * Description   : notify the player about the polish
 * Arguments     : object  - the polished object
 *                 int*    - array of coins player payed
 *                 int*    - array of coins player got back
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_polish_notify_polish(object item, int* charge, int* change)
{
    string  name = LANG_THESHORT(item);

    TP->catch_msg("You give " + name + " to " + QTNAME(TO) + ".\n");
    say(QCTNAME(TP)+" gives " + name + " to " + QTNAME(TO) + ".\n");
    tell_room(ENV(TO),   QCTNAME(TO) + " polishes " + name + ".\n");
    TP->catch_msg(QCTNAME(TO) + " gives you " + name + ".\n");
    say(QCTNAME(TO)+" gives " + name + " to " + QTNAME(TP) + ".\n");

    TP->catch_msg("You pay " + QTNAME(TO) + " " + text(charge) + ".\n");
    if (strlen(text(change))) write("You get "+text(change)+" back.\n");
}

/*
 * === main routines =====================================================
 * =============================================================== *** ===
 */

/*
 * Function name : action_smithy_repair
 * Description   : handles attempts to repair weapon or armour
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 1 for success or 0 for failure
 */

int
action_smithy_repair(string text)
{
    mixed   item;
    int     cost, *coin, repair_left, *charge, *change;

    if (!text || !sizeof(item = (FIND_STR_IN_OBJECT(text, TP))))
       return hook_smithy_repair_faulty_syntax(text);

    item = item[0];

    say(QCTNAME(TP) + " asks " + QTNAME(TO) + " to repair " +
        TP->query_possessive() + " " + item->query_short() + ".\n");
    TP->catch_msg("You ask " + QTNAME(TO) + " to repair your " +
        item->query_short() + ".\n");

    if (!CAN_SEE_IN_ROOM(TO))       return hook_smithy_answer_dark_room();
    if (!CAN_SEE(TO, TP))           return hook_smithy_answer_invisible();

//    if (query_smithy_design(TP)) remove_smithy_design(TP);

//    if (query_smithy_design() || query_smithy_crafts())
//       return hook_smithy_select_notify_busy();

    if (!item->check_weapon() && !item->check_armour())
       return hook_smithy_repair_faulty_object(item);

    if (item->check_weapon())
       repair_left = item->query_dull() - item->query_repair_dull();
    else
       repair_left = item->query_condition() - item->query_repair();

    if (!repair_left)
       return hook_smithy_repair_cannot_repair(item);

    cost = REPAIR_COST(item);

    if (sizeof(coin = pay(cost, TP, 0, 0, 0, 0, 1)) == 1)
       return hook_smithy_repair_cannot_afford(item, cost);

    if (item->check_weapon())
       item->set_repair_dull(item->query_dull());
    else
       item->set_repair(item->query_condition());

    charge = coin[0..(SIZEOF_MONEY_TYPES - 1)];
    change = coin[SIZEOF_MONEY_TYPES..(2*SIZEOF_MONEY_TYPES - 1)];

    hook_smithy_repair_notify_repair(item, charge, change);

    return 1;
}

/*
 * Function name : action_smithy_polish
 * Description   : handles attempts to polish weapon
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 1 for success or 0 for failure
 */

int
action_smithy_polish(string text)
{
    mixed   item;
    int     cost, *coin, *charge, *change;

    if (!text || !sizeof(item = (FIND_STR_IN_OBJECT(text, TP))))
       return hook_smithy_polish_faulty_syntax(text);

    item = item[0];

    say(QCTNAME(TP) + " asks " + QTNAME(TO) + " to polish " +
        TP->query_possessive() + " " + item->query_short() + ".\n");
    TP->catch_msg("You ask " + QTNAME(TO) + " to polish your " +
        item->query_short() + ".\n");

    if (!CAN_SEE_IN_ROOM(TO))       return hook_smithy_answer_dark_room();
    if (!CAN_SEE(TO, TP))           return hook_smithy_answer_invisible();

//    if (query_smithy_design(TP)) remove_smithy_design(TP);
//
//    if (query_smithy_design() || query_smithy_crafts())
//       return hook_smithy_select_notify_busy();

    if (!item->check_weapon())
       return hook_smithy_polish_faulty_object(item);

    if (!item->query_corroded())
       return hook_smithy_polish_cannot_polish(item);

    cost = POLISH_COST(item);

    if (sizeof(coin = pay(cost, TP, 0, 0, 0, 0, 1)) == 1)
       return hook_smithy_polish_cannot_afford(item, cost);

    item->set_repair_corr(item->query_corroded());

    charge = coin[0..(SIZEOF_MONEY_TYPES - 1)];
    change = coin[SIZEOF_MONEY_TYPES..(2*SIZEOF_MONEY_TYPES - 1)];

    hook_smithy_polish_notify_polish(item, charge, change);

    return 1;
}

int
action_smithy_help(string str)
{
    string s;
    object tp = this_player();

    seteuid(getuid());

    tp->catch_msg("This is what I wil do for you:\n" +
        "\trepair <armour/weapon> to repair worn down armours or sharpen " +
            "dull weapons, or\n" +
        "\tpolish <weapon> to repair corroded weapons.\n");
    
    return 1;
}


/*
 * Function name : init_smithy
 * Description   : adds smithy actions to the environment
 * Arguments     : void    - no arguments
 * Returns       : void    - nothing is returned
 */
void
init_smithy()
{
    add_action(action_smithy_repair, "repair");
    add_action(action_smithy_repair, "sharpen");
    add_action(action_smithy_polish, "polish");
    add_action(action_smithy_help, "help");
}

string
help_text()
{
    return "Use <help smithy> for more information.\n";
}
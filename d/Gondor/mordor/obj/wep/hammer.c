/*
 * /d/Gondor/mordor/obj/wep/hammer.c
 *
 * This is a hammer. I will allow you to use it on several objects that you
 * find in your environment. If it is an armour or a weapon you might break
 * it and a the lock on a door may be smashed allowing you to open it without
 * a key. Obviously, you can also try to kill someone with it.
 *
 * /Mercade, 23 October 1993
 *
 * Revision history:
 */

inherit "/std/weapon";

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <formulas.h>
#include <tasks.h>

#define WEAPON_HIT 15
#define WEAPON_PEN 30
#define MINIMUM_FATIGUE_TO_HAMMER        15
#define FATIGUE_REDUCTION_TO_HAMMER      10
#define MINIMUM_FATIGUE_TO_SMASH_LOCK    55
#define FATIGUE_REDUCTION_TO_SMASH_LOCK  50

/*
 * The fatigue to add is dependant on your constitution.
 */
#define FATIGUE_REDUCTION_HIT_ENEMY(p) (p->query_stat(SS_CON) / 10)
/*
 * The damage you will inflict is dependant on your strength.
 */
#define HP_REDUCTION_ON_ENEMY(p)       (p->query_stat(SS_STR) / 2)

void
create_weapon()
{
    set_name("hammer");
    add_name("club");

    set_adj("orc");
    set_adj("orcish");
    set_adj("black");
    set_adj("strong");

    set_short("black orc hammer");
    set_pshort("black orc hammers");
    set_long(BSN("It is a strong hammer, made by orcs. This hammer serves " +
        "many purposes. The orc use it for construction, but you can also " +
        "use it for demolition and you can always test its strength " +
        "against the head of an enemy."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 13000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }) );
    add_prop(OBJ_I_RES_IDENTIFY, 25);
    add_prop(MAGIC_AM_ID_INFO, ({
	BSN("It is a very strong hammer."), 1,
	BSN("With the hammer you can break weapons and armour."), 20,
	BSN("The hammer might be used to smash locks."), 40 }) );

    FIX_EUID;
}

/*
 * To add the smash command to the player.
 */
void
init()
{
    ::init();

    add_action("do_smash", "bash");
    add_action("do_smash", "smash");
    add_action("do_smash", "break");
    add_action("do_smash", "hammer");
    add_action("do_smash", "demolish");
}

/*
 * A command parser. I have taken this from the standard soul and slightly
 * modified it for my needs.
 */
object
get_victim(string str)
{
    object *oblist, *tmplist;
    int    i;

    if (!parse_command(str, environment(this_player()), "%l", oblist))
        return 0;
 
    oblist = NORMAL_ACCESS(oblist, 0, 0);

    if (!sizeof(oblist))
        return 0;

    tmplist = ({});
    for (i = 0; i < sizeof(oblist); i++)
    {
        if (objectp(oblist[i]) && living(oblist[i]) &&
                (this_player() != oblist[i]) &&
                CAN_SEE(this_player(), oblist[i]))
            tmplist = tmplist + ({ oblist[i] });
    }

    return (sizeof(tmplist) ? tmplist[0] : 0 );
}

/*
 * This parser will get the door-object to the door that you want to bash, if
 * that is what you want. This has to be done for a player cannot see the
 * door itself.
 */
object
get_door(string str)
{
    object *inv = all_inventory(ENV(TP));
    int i;

    for (i = 0; i < sizeof(inv); i ++)
    {
        if ((function_exists("create_object", inv[i]) == "/std/door") &&
            (member_array(str, inv[i]->query_door_name()) > -1))
        {
            return inv[i];
        }
    }

    return 0;
}

/*
 * The smash command itself. It can take several forms.
 */
int
do_smash(string str)
{
    object tp = TP;
    object victim;
    string qvb = query_verb();

    if (!CAN_SEE_IN_ROOM(tp))
    {
        NFN0("It is too dark to see.");
    }

    if (!strlen(str))
    {
        NFN0(CAP(qvb) + "what?");
    }

    if (!query_wielded())
    {
        NFN0("You will need to wield this " + TO->short() + " to be able " +
            "to use it.");
    }

    /*
     * If I am correct doors will not be found using the parse_command
     * function, so I will have to check on them manually.
     */
    if (!objectp(victim))
    {
        if (!objectp(victim = get_door(str)))
        {
            NFN0(CAP(qvb) + " what?");
        }

        if (!(victim->query_locked()))
        {
            WRITE("The " + str + " is not locked.");
            return 1;
        }

        if (victim->query_no_pick())
        {
            WRITE("After close examination of the " + str + " you realize " +
                "that there is no way to open it by hammering at it with " +
                "your hammer.");
            return 1;
        }

        if (tp->query_fatigue() < MINIMUM_FATIGUE_TO_SMASH_LOCK)
        {
            WRITE("You are not fit enough to " + qvb + " the " + str + ".");
            return 1;
        }

        tp->add_fatigue(FATIGUE_REDUCTION_TO_SMASH_LOCK);

        if (tp->resolve_task( (TASK_DIFFICULT +
                (victim->query_pick() > 100 ? 100 : victim->query_pick())),
            ({ SKILL_WEIGHT, 50, TS_STR,
               SS_OPEN_LOCK,
               SS_WEP_CLUB,
               SS_APPR_OBJ }) ) > 0)
        {
            WRITE("You swing you hammer and smash the lock on the " + str +
                ". You can now open the " + str + ".");
            SAY(" swings " + POSSESSIVE(tp) + " hammer and smashes the " +
                "lock on the " + str + ".");
            victim->set_locked(0);
            (victim->query_other_door())->set_locked(0);
            tell_room(victim->query_other_room(),
                BSN("From behind the " + str + " you hear a noise as if " +
                "someone is trying to smash the lock on it using a hammer."));

            return 1;
        }

        WRITE("Banging at the " + str + " with your hammer does not open " +
            "it. The lock does not give in.");
        SAY(" swings " + POSSESSIVE(tp) + " hammer but fails to smash the " +
            "lock on the " + str + ".");
        tell_room(victim->query_other_room(),
            BSN("From behind the " + str + " you hear a noise as if someone " +
            "is trying to smash the lock on it using a hammer."));

        return 1;
    }

    if (ENV(victim) == tp)
    {
        NFN0("You cannot " + qvb + " something you carry.");
    }

    if (tp->query_fatigue() < MINIMUM_FATIGUE_TO_HAMMER)
    {
        NFN0("You are not fit enought to " + qvb + " anything.");
    }

    /* If you wanna break an armour/weapon, that is your decision. */
    if ((victim->check_armour()) || (victim->check_weapon()))
    {
        if (victim->query_prop(OBJ_I_BROKEN))
        {
            NFN0("The " + check_call(victim->short()) + " is already broken.");
        }

        tp->add_fatigue(FATIGUE_REDUCTION_TO_HAMMER);
        victim->add_prop(OBJ_I_BROKEN, 1);
        write(BSN("You start hammering the " + check_call(victim->short()) +
            " in order to " + (qvb == "hammer" ? "break" : qvb) + " it. " +
            "When you stop, the " + check_call(victim->short()) + " is " +
            "broken."));
        SAY(" starts hammering the " + check_call(victim->short()) + " in " +
            "order to smash it. When " + PRONOUN(tp) + " stops, the " +
            check_call(victim->short()) + "is broken.");
        return 1;
    }

    if (victim == tp->query_attack())
    {
        NFN0("You are already fighting " + victim->query_the_name(tp) + ".");
    }

    if (living(victim))
    {
        if ((!(tp->query_npc())) && (tp->query_met(victim)) &&
            (tp->query_prop(LIVE_O_LAST_KILL) != victim))
        {
	    tp->LCATCH_MSG("Attack ", "?!? Please confirm by trying again.",
                victim);
            tp->add_prop(LIVE_O_LAST_KILL, victim);
            return 1;
        }

        if ((!F_DARE_ATTACK(tp, victim)) &&
            (member_array(victim, tp->query_enemy(-1)) == -1))
        {
            write("Umm... no, You do not have enough self-discipline to " +
                "dare!\n");
            return 1;
        }

        tp->reveal_me();
        write(BSN("You swing your " + TO->short() + " towards " +
            victim->query_the_name(tp) + " in order to smash his head."));
        victim->CATCH_MSG(" swings " + POSSESSIVE(tp) + " " + TO->short() +
            " towards you in order to smash your head.", tp);
        /* I admit this tell_room is ugly, but I am lazy today. */
        tell_room(ENV(TP), QCTNAME(tp) + " swings " + POSSESSIVE(tp) +
            TO->short() + " towards " + QTNAME(victim) + " in order to " +
            " smash " + POSSESSIVE(victim) + "head.\n" , ({ tp, victim }) );

        tp->add_fatigue(-(FATIGUE_REDUCTION_HIT_ENEMY(tp)));
        victim->heal_hp(-(HP_REDUCTION_ON_ENEMY(tp)));

        if (victim->query_hp() <= 0)
        {
            victim->do_die(tp);
            return 1;
        }

        tp->command("kill " + str);
        return 1;
    }

    NFN0("There is no use in trying to " + qvb + " the " +
        check_call(victim->short()) + ".");
}

/*
 * Recovery code.
 */
string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}

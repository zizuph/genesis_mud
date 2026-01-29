/* Stralle @ Genesis 000921
 *
 * A shadow that can mask the did_hit() in a weapon to make it
 * poisoned. Used for the kapaks special attack.
 */

#pragma strict_types

inherit "/std/shadow";

#include <ss_types.h>
#include <poison_types.h>
#include <macros.h>

#define QSW     (query_shadow_who())

int gPoisons = 3; /* Initially three poisons */

void
set_num_poison(int arg)
{
    gPoisons = arg;
}

int
query_num_poisons()
{
    return gPoisons;
}

public varargs string
long(string str, object for_obj)
{
    //return QSW->check_call(QSW->query_long()) + (gPoisons ? "\nYou notice " +
    return QSW->check_call(QSW->long()) + (gPoisons ? "\nYou notice " +
        "some form of liquid coating the blade.\n" : "") +
        (str ? "" : QSW->wep_condition_desc());
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
    int dam)
{
    object ob, wielder;
    int ret = QSW->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    /* Only if we make a true hit, do we have the ability to poison */
    if (!dam || phurt < 0)
        return ret;

    if (!gPoisons)
    {
        /* If no poisons left, we remove the shadow */
        set_alarm(0.0, 0.0, &remove_shadow());
        return ret;
    }
    
    if (!random(3))
    {
        setuid();
        seteuid(getuid());

        wielder = QSW->query_wielded(QSW);

        /* Generate messages to all parties */
        wielder->catch_msg("As you hurt " + QTNAME(enemy) + " with your " +
            (wielder->query_combat_object())->cb_attack_desc(aid) +
            ", " + enemy->query_possessive() + " face becomes paler.\n");
        enemy->catch_msg("As " + QTNAME(wielder) + " hurts you" +
            " with " + wielder->query_possessive() + " " +
            (wielder->query_combat_object())->cb_attack_desc(aid) +
            " you feel something coursing through your veins.\n");
        enemy->tell_watcher("As " + QTNAME(wielder) + " hurts " +
            QTNAME(enemy) + " with " + wielder->query_possessive() +
            " " + (wielder->query_combat_object())->cb_attack_desc(aid) +
            ", " + enemy->query_possessive() + " face becomes paler.\n",
            enemy, ({ wielder }));

        /* Clone a standard poison into the enemy */
        ob = clone_object("/std/poison_effect");
        ob->set_interval(random(5) + 15);
        ob->set_time(random(20) + 50);
        ob->set_damage( ({ POISON_HP, 40 + random(30),
            POISON_STAT, SS_CON }) );
        ob->set_poison_type("draconian");
        ob->set_strength(random(10) + 15);
        ob->set_silent(1);
        if (ob->move(enemy))
            ob->move(enemy, 1);
        ob->start_poison();
    
        /* Reduce the number of poisons on this weapon */
        gPoisons--;

        return 1;
    }

    return ret;
}

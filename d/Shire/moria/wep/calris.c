/*
 * calris.c
 *
 * Calris is sindarin for 'Light Cleaver', it is a +30 giant flaming
 * sword (2handed) of black eog. Weighs 18 lbs = 9 kgs. It is on fire
 * only if held by the Balrog, and when the demon is on fire. It delivers
 * heat criticals.
 * ------------------------------------------------------------------------
 * 
 * 2020-12-26 - Cotillion
 * - Fixed hit messages not being displayed for non flame hits.
 */

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <formulas.h>

inherit "/std/weapon";

//inherit BASE_WEAPON;

//CONSTRUCT_WEAPON
void create_weapon()
{
    set_name("sword");
    add_name("calris");
    add_name("cleaver");
    set_adj(({"giant", "light", "black", "eog", "balrog's"}));

    set_short("@@my_short@@");

    set_long("This is Light Cleaver (sindarin \"Calris\"), a @@my_short@@. "
      + "It is heavy, and you surely must wield it two-handed, though the "
      + "huge Balrog uses it single handed. It seems to be made of "
      + "black eog.\n");

    set_hit(60);
    set_pen(57);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_wf(TO);

    add_prop(OBJ_I_VOLUME, 12200);
    add_prop(OBJ_I_WEIGHT, 26600); /* 26.6 kg */
    add_prop(OBJ_I_VALUE,  3 * F_VALUE_WEAPON(40, 40));

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 90}));
    add_prop(MAGIC_AM_ID_INFO, ({"This sword glows with an fiery-red aura "+
        "of magic.\n", 20, "Forged in darkness and named Calris, the "+
        "Light Cleaver.\n", 50}));
    add_prop(OBJ_M_NO_BUY, 1);
    set_hands(W_ANYH);
}

init()
{
    ::init();
    add_action("do_wield", "wield");
}

int
do_wield()
{
    TO->query_hands();
    return 0;
}

int
query_hands()
{
    if (!TP || TP->query_race_name() != "balrog")
        return wep_hands = W_BOTH;
    else
        return wep_hands = W_ANYH;
}


int
query_usable(object who)
{
    return STR(who) > 60;
}

int
query_aflame()
{
    return living(wielder) && wielder->query_race_name() == "balrog";
}


int
query_hit()
{
    if (query_aflame())
        return 100;
    else
        return 60;
}

int
query_pen()
{
    if (query_aflame())
        return 100;
    else
        return 57;
}

string
my_short()
{
    if (query_aflame())
        return "giant flaming sword";
    else
        return "giant black sword";
}

int
wield(object to)
{
    if (!query_usable(TP))
    {
        write("You are not strong enough to wield this weapon.\n");
        say(QCTNAME(TP)+ " tries to wield " + QSHORT(TO) + " but is too weak.\n");
        return -1;
    }

    wielded_in_hand = query_hands();
    write("You manage to wield Calris "+
      (wielded_in_hand == W_BOTH ? "two-handed.\n" : "single-handed.\n"));
    say(QCTNAME(TP)+" wields a " + QSHORT(TO) + ".\n");
    return 1;
}

void
flame_damage(object target, string hdesc, int base_pen)
{
    if (!objectp(target) || !objectp(wielder))
        return;

    int resist = target->query_magic_res(MAGIC_I_RES_FIRE);
    int pen = base_pen * (100 - resist) / 100 + 10;

    target->hit_me(pen, MAGIC_DT, wielder, -1);

    if (hdesc == "legs") {
        hdesc = "leg";
    }

    target->tell_watcher(LANG_POSS(QCTNAME(target)) + " " + hdesc + 
        " is enveloped within a burst of fire from the Balrog's "+ TO->short() +"!\n");

    target->catch_tell("The Balrog's " +  TO->short() + " slashes your " + hdesc + "." +
        " Your " + hdesc + " is enveloped in a burst of unholy fire!\n");

    if (HP(target) <= 0) {
        target->do_die(wielder);
    }
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    mixed *res;
    int resist, pen;

    int ret = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (!query_aflame() || HP(enemy) <= 0)
        return ret;

    /* Run delayed to provide correct order of messages. */
    set_alarm(0.0, 0.0, &flame_damage(enemy, hdesc, phit));
    return ret;
}



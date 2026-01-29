/*
 * Sword used by Kirk, gang leader of the Brix in the
 * aesthetics quarter of Palanthas.  Second chance for
 * dulling (slightly higher than in normal did_hit) on
 * weapons parried by this one in did_parry().
 *
 * Mortis 09.2006
 *
 * Update:
 * Made this sword mildly magical. Increased chance that it would dull a
 * parried weapon from a fraction of a percent to around two thirds.
 * Increased parry bonus from 2 to 10 since the weakest imbue is already 12.
 * This sword was intended to be a cool weapon-breaker, not a power killing
 * sword, but it has to be strong enough to make it somewhat worthwhile to
 * wield. These changes are in line with my original intentions, plus the
 * wielder (Kirk) is very challenging to kill, especially with his 2014
 * upgrades.
 *
 * Mortis 09.2014
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include "../../local.h"
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>

int mypar = 10; // +10 to parry

// Prototypes
void wield_msg(object mwield);
void unwield_msg(object munwield);

create_weapon()
{
    set_name("tynesword");
    add_name(({"sword"}));
    set_adj("v-hilted");
    add_adj(({"v", "hilted"}));
    set_short("v-hilted tynesword");
    set_long("With a straight, folded-steel blade this tynesword is short "
    + "enough in length to be classed a shortsword.  Thin notches cut into "
    + "its back edge have been blackened with resin, and from its cross "
    + "guard hilt extend two long, thin blades like an upright 'V'.  "
    + "Balanced perfectly by an iron pommel in the shape of a visored "
    + "plate helm, this tynesword seems custom designed for parrying "
    + "blows, catching weapons, and breaking them.\n");

    set_hit(42);
    set_pen(37);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    set_wf(TO);

    set_likely_dull(15);  // Incr. chance to dull due to teeth breaking.
    set_likely_break(12); // Incr. chance to break due to function & design.
    
    set_keep(1);

    add_prop(OBJ_M_NO_SELL, "The shopkeeper cannot afford to buy " +
      "magical weapons.  You will have to find another market.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({22, "abjuration"}));
    add_prop(MAGIC_AM_ID_INFO, ({"You gather that the tynesword has been "
    + "enhanced with protective magic to better guide it in parrying blows. "
    + "That guidance also allows it to hit more easily.\n", 20,
      "\nA hidden Arcane Mark reveals it was enchanted by the Rogue Wizard "
    + "Resesthon.\n", 40}));
    add_prop(OBJ_S_WIZINFO, "The Rogue Wizard Resesthen enchanted this "
    + "weapon to aid a shadowy blade fighter with a weapon breaking style. "
    + "Overall, when successfully parrying, it has a two thirds chance to "
    + "damage the parried weapon.\n");
    
    add_prop(OBJ_I_WEIGHT, 1800 + random(601));
    add_prop(OBJ_I_VOLUME, 1700 + random(501));
    add_prop(OBJ_I_VALUE,  1100 + random(251));
}

mixed
wield(object what)
{
    if (TP->query_npc())
    {
        return 0;
    }

    TP->set_skill_extra(SS_PARRY, (TP->query_skill_extra(SS_PARRY) + mypar));

    set_alarm(1.0, 0.0, &wield_msg(wielder));

    return 0;
}

mixed
unwield(object what)
{
    if (TP->query_npc())
    {
        return 0;
    }

    TP->set_skill_extra(SS_PARRY, (TP->query_skill_extra(SS_PARRY) - mypar));

    set_alarm(1.0, 0.0, &unwield_msg(wielder));

    return 0;
}

void
wield_msg(object mwield)
{
    if (TP->query_npc() || !mwield)
    {
        return;
    }

    mwield->catch_msg("You feel more confident in your ability to "
    + "block and parry wielding the tynesword.\n");
    say(QCTNAME(mwield) + " grasps " + HIS(mwield) + " tynesword "
    + "confident in " + HIS(mwield) + " defenses.\n", mwield);
}

void
unwield_msg(object munwield)
{
    if (TP->query_npc() || !munwield)
    {
        return;
    }

    munwield->catch_msg("You no longer feel as confident in your ability to "
    + "block and parry without the tynesword.\n");
    say(QCTNAME(munwield) + " releases " + HIS(munwield) + " grip on "
    + HIS(munwield) + " tynesword appearing less well defended now.\n",
    munwield);
}

/*
 * Function name: did_parry
 * Description:   Tells us that this weapon was used to parry an attack. It
 *                can be used to wear down a weapon. Note that this method
 *                is called before the combat messages are printed out.
 * Arguments:     att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 */
public varargs void
did_parry(object att, int aid, int dt)
{
    int par_hits, par_wep_pen, par_likely_dull, wep0dt, wep1dt;
    object *att_wep = att->query_weapon(-1), parried_wep;

    if (!sizeof(att_wep))
    {
        return;  // Makes sure nothing happens if nothing is wielded.
    }

    wep0dt = att_wep[0]->query_dt();
    if (wep0dt == W_BLUDGEON)
    {
        return;     // Blunt weapons/Unarmed are not vulnerable to tyneswords.
    }

    if (sizeof(att_wep) == 1)
    {
        parried_wep = att_wep[0];
    }

    /* This narrows down which weapon of the attacker got parried.  It
     * basically just eliminates bludgeoning weapons if multiple weapons
     * are wielded.  Then it designates the weapon to be affected. */
    if (sizeof(att_wep) == 2)
    {
        wep0dt = att_wep[0]->query_dt();
        wep1dt = att_wep[1]->query_dt();

        if (wep0dt == W_BLUDGEON && wep1dt == W_BLUDGEON)
        {
            return;
        }

        if (wep0dt == W_BLUDGEON)
        {
            parried_wep = att_wep[1];
        }

        if (wep1dt == W_BLUDGEON)
        {
            parried_wep = att_wep[0];
        }

        if (!objectp(parried_wep))
        {
            if (random(2) == 1)
            {
                parried_wep = att_wep[1];
            }
            else
            {
                parried_wep = att_wep[0];
            }
        }
    }

    if (!objectp(parried_wep))
    {
        return;     //Again checks to make sure a valid weapon has been parried.
    }

    par_hits        = parried_wep->query_weapon_hits();
    par_wep_pen     = parried_wep->query_pen();
    par_likely_dull = parried_wep->query_likely_dull() + 2;

    /* This is the chance of the parried weapon being dulled as a result of
     * being parried. It is the normal hit's chance + 75%. */
    if (F_WEAPON_CONDITION_DULL(par_hits, par_wep_pen, par_likely_dull) ||
        random(100) < 75)
    {
        string parhow        = one_of_list(({"a notch", "the v-bladed hilt"})),
               par_wep_short = parried_wep->short();

        if (parried_wep->query_prop(OBJ_I_IS_MAGIC_WEAPON) == 1 &&
            random(4) != 1)
        { return; }

        att->catch_msg("Your " + par_wep_short + " creaks dangerously as it "
        + "is caught in " + parhow + " of the tynesword!\n");
        wielder->catch_msg("You catch " + QTNAME(att) + "'s " + par_wep_short
        + " in " + parhow + " of your tynesword!\n");
        tell_room(E(att), QCTNAME(att) + "'s " + par_wep_short + " creaks "
        + "dangerously as it is caught in " + parhow + " of " + QTNAME(wielder)
        + "'s tynesword!\n", ({att, wielder}));

        parried_wep->set_weapon_hits(0);
        parried_wep->set_dull(parried_wep->query_dull() + 1);
    }

}

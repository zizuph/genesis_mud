/* 
 * Fist spikes used by lowly Brix gangers behind
 * Jems court in the Aesthetics quarter of Palanthas.
 *
 * Based on the coding concept behind Shiva's flaming
 * gloves found on Lyden in Tyr.
 *
 * On a successful hit with either hand that does more
 * than 20 points of damage, the spikes will inflict
 * bonus impalation damage.
 *
 * Cannot be worn with shields.
 *
 * Mortis 05.2006
 *
 * These did nominal damage for giving up shields and wielded weapons.
 * Increased random and factored special damage. Switched to wrist slot
 * and allowed weapons to be wielded. Intention was to block shields, and
 * I originally used code that blocked shields and weapons. Now I'm better. :)
 *
 * Mortis 09.2014
 *
 * These have been reviewed by AoB and returned to blocking weapons
 * due to thematic discrepancies, the spikes affected the damage of
 * bludgeon weapons.
 *
 * Carnak 02.2016
 *
 * Ported over to use unarmed_enhancers.
 *
 * Ckrik 11.2021
 */

inherit "/std/unarmed_enhancer";
inherit "/lib/keep";

#include "../../local.h"
#include <files.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <macros.h>

#define SPIKES_SHADOW (MONKS + "arms/brixx_fist_spikes_sh")

void
create_unarmed_enhancer()
{
    seteuid(getuid());

    set_name("spikes");
    set_pname("spikes");

    set_adj("fist");
    add_adj("pair of");

    set_short("pair of fist spikes");
    set_pshort("pairs of fist spikes");

    set_default_enhancer(36, 35, W_BLUDGEON | W_IMPALE, 3, A_HANDS | A_WRISTS, 0, this_object());
    set_am(({1, -2, 1}));

    set_long("Worn on the middle two fingers of each hand with a palm bar "
    + "for secure grasping, this pair of contoured iron knuckles stretches "
    + "across the knuckles with four thick nail-like spikes creating a "
    + "punching surface capable of inflicting nasty, piercing damage.\n");

    add_prop(OBJ_I_VALUE,  168);
    add_prop(OBJ_I_WEIGHT, 650);
    add_prop(OBJ_I_VOLUME, 525);
}

/* Called when the spikes are worn, this function
 * adds a shadow that takes care of some of the spikes'
 * functionality.
 */
mixed
wear(object obj)
{
    if (TP->query_npc() == 1)
    { return 0; }

    int t1, t2, t3;
    object sh, tool1, tool2, tool3;

    tool1 = TP->query_tool(W_BOTH);
    tool2 = TP->query_tool(W_RIGHT);
    tool3 = TP->query_tool(W_LEFT);

    t1 = tool1->query_at();
    t2 = tool2->query_at();
    t3 = tool3->query_at();

    if (TP->query_tool(W_BOTH) || TP->query_tool(W_RIGHT) ||
        TP->query_tool(W_LEFT))
    {
        return "You are unable to wear the fist spikes as your hands "+
        "are otherwise occupied.\n";
    }
    
    if (t1 == A_SHIELD || t2 == A_SHIELD || t3 == A_SHIELD)
    { return "You cannot employ the fist spikes while wearing a shield.\n"; }

    if ((sh = clone_object(SPIKES_SHADOW)) && sh->shadow_me(TP))
    {
        sh->set_spikes_ob(TO);
    }

    else
    {
        sh->remove_shadow();
    }

    return 0;
}    

/* Called when the spikes are removed, this function
 * removes the spikes shadow.
 */
int
remove(object obj)
{
    if (TP->query_npc() == 1)
    {
        return 0;
    }

    TP->remove_spikes_shadow();
    return 0;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object wearer;
    string with, where, how, what, owhat, impaley;

    if (!(wearer = query_worn()))
    {
        return 0;
    }

    if (phurt < 0)
    {
        return 0;
    }

    // Give an attack description.
    with = (aid == W_RIGHT ? "right hand" : "left hand");

    where = " the " + hdesc + " of ";

    switch (dam)
    {
    case -3..2:
        how = "";
        what = "barely connect with";
        owhat = "barely connects with";
        break;
    case 3..7:
        how = "";
        what = "connect with";
        owhat = "connects with";
        break;
    case 8..14:
        how = "";
        what = "thuddingly connect with";
        owhat = "thuddingly connects with";
        break;
    case 15..25:
        how = "";
        what = "pummel";
        owhat = "pummels";
        break;
    case 26..37:
        how = "";
        what = "smackingly pummel";
        owhat = "smackingly pummels";
        break;
    case 38..59:
        how = "";
        what = "knuckle-smash";
        owhat = "knuckle-smashes";
        break;
    case 60..95:
        how = " ruthlessly";
        what = "knuckle-smash";
        owhat = "knuckle-smashes";
//            where = " ";
        break;
    default:
        how = " brutally";
        what = "massacre";
        owhat = "massacres";
//            where = " ";
    }

    switch (phurt)
    {
    case 1..9:
        impaley = "piercing the skin beneath";
        break;
    case 10..19:
        impaley = "impaling the flesh beneath";
        break;
    case 20..34:
        impaley = "impaling deeply into the flesh beneath";
        break;
    default:
        impaley = "impaling all the way into the flesh beneath";
        break;
    }

    wearer->catch_tell("You " + what + where + enemy->query_the_name(wearer)
        + how + " with your " + with + ", your fist spikes "
        + impaley + ".\n");
        // Original used enemy->query_the_name(wearer)
    enemy->catch_tell(wearer->query_The_name(enemy) + " " + owhat + 
        " your " + hdesc + how + " with " + wearer->query_possessive() + " " + with + ", "
        + wearer->query_possessive() + " fist spikes " + impaley + ".\n");
    wearer->tell_watcher(QCTNAME(wearer) + " " + owhat + where + QTNAME(enemy)
        + how + ", " + wearer->query_possessive() + " fist spikes " + impaley + ".\n", enemy);
    return 1;
}

string
query_recover()
{
    return ::query_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    ::init_recover(arg);
}

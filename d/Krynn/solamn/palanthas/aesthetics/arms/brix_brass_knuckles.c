/* 
 * Brass knuckles used by lowly Brix gangers behind
 * Jems court in the Aesthetics quarter of Palanthas.
 *
 * Based on the coding concept behind Shiva's flaming
 * gloves found on Lyden in Tyr.
 *
 * On a successful hit with either hand that does more
 * than 25 points of damage, the knuckles will inflict
 * bonus bludgeoning damage.
 *
 * Cannot be worn with shields.  Cannot hold or wield
 * while wearing knuckles.
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
 * due to thematic discrepancies, the knuckles affected the damage of
 * bludgeon weapons.
 *
 * Carnak 02.2016
 *
 * Ported over to use unarmed_enhancers.
 *
 * Ckrik 11.2021
 *
 */

inherit "/std/unarmed_enhancer";
inherit "/lib/keep";

#include "../../local.h"
#include <files.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <macros.h>

#define KNUCKLES_SHADOW (MONKS + "arms/brixx_brass_knuckles_sh")

void
create_unarmed_enhancer()
{
    seteuid(getuid());

    set_name("knuckles");
    set_pname("knuckles");

    set_adj("brass");
    add_adj("pair of");

    set_short("pair of brass knuckles");
    set_pshort("pairs of brass knuckles");

    set_default_enhancer(36, 35, W_BLUDGEON, 3, A_HANDS | A_WRISTS, 0, this_object());
    set_am(({1, -2, 1}));

    set_long("Worn on the middle two fingers of each hand with a palm bar "
        + "for secure grasping, this pair of contoured brass knuckles stretches "
        + "across the knuckles creating a punching surface capable of inflicting "
        + "nasty damage.\n");

    add_prop(OBJ_I_VALUE,  144);
    add_prop(OBJ_I_WEIGHT, 550);
    add_prop(OBJ_I_VOLUME, 400);
}

/* Called when the knuckles are worn, this function
 * adds a shadow that takes care of some of the knuckles'
 * functionality.
 */
mixed
wear(object obj)
{
    if (TP->query_npc() == 1)
    {
        return 0;
    }

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
        return "You are unable to wear the brass knuckles as your "+
        "hands are otherwise occupied.\n";
    }
    
    if (t1 == A_SHIELD || t2 == A_SHIELD || t3 == A_SHIELD)
    { return "You cannot employ the brass knuckles while wearing a shield.\n"; }

    if ((sh = clone_object(KNUCKLES_SHADOW)) && sh->shadow_me(TP))
    {
        sh->set_knuckles_ob(TO);
    }

    else
    {
        sh->remove_shadow();
    }

    return 0;
}    

/* Called when the knuckles are removed, this function
 * removes the knuckles shadow.
 */
int
remove(object obj)
{
    if (TP->query_npc() == 1)
    {
        return 0;
    }

    TP->remove_knuckles_shadow();
    return 0;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object wearer;
    string with, where, how, what, owhat, bludge;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

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
    case 1..10:
        bludge = "bruising the flesh beneath";
        break;
    case 11..20:
        bludge = "shaking the bone beneath";
        break;
    case 21..35:
        bludge = "cracking the bone beneath";
        break;
    default:
        bludge = "cracking bone and rupturing flesh";
        break;
    }

    wearer->catch_tell("You " + what + where + enemy->query_the_name(wearer)
        + how + " with your " + with + ", your brass knuckles "
        + bludge + ".\n");
    // Original used enemy->query_the_name(wearer)
    enemy->catch_tell(wearer->query_The_name(enemy) + " " + owhat + 
        " your " + hdesc + how + " with " + wearer->query_possesive() + " " + with + ", "
        + wearer->query_possesive() + " brass knuckles " + bludge + ".\n");

    wearer->tell_watcher(QCTNAME(wearer) + " " + owhat + where + QTNAME(enemy)
        + how + ", " + wearer->query_possesive() + " brass knuckles " + bludge + ".\n", enemy);
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

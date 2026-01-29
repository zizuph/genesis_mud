/*
 * /d/Gondor/common/wep/lockpicks.c
 *
 * Skill enhancing/bestowing lock picks courtesy of Xeros of GondorMud.
 * They are worked up in conjunction with the by now famous stealth_armour,
 * stealth_cloak and shadow plant.
 *
 * Wielding the lockpicks will give you some extra skill in the are of
 * lockpicking. You will benefit more if you already have more skill.
 * Thanks again to Olorin. 1 Nov 1993
 *
 * Coded by Xeros of GondorMud
 *
 * Revision history:
 * /Mercade, 23 November 1993, Added dynamic function for extra skill
 */
#pragma strict_types
    
inherit "/std/weapon";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <ss_types.h>

/*
 * Global variable.
 */
int added_skill;

void
create_weapon()
{
    set_name("picks");
    add_name("set");
    set_pname("lockpicks");
    add_pname("sets");
    set_adj("lock");
    add_adj("small");
    set_short("set of small lock picks");
    set_long(BSN("These tiny lock picks are all connected by a common hilt "+
        "so that they vaguely resemble a knife when all pushed together, "+
        "but you feel confident that they are virtually useless as weapons, "+
        "their strength lies rather in opening locks."));

    set_default_weapon(5, 5, W_KNIFE, W_IMPALE, W_BOTH, 0);
    set_wf(TO);

    add_prop(OBJ_I_VALUE, 150);
    add_prop(OBJ_I_WEIGHT, 575 + random(125));
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(MAGIC_AM_MAGIC, ({ 45, "enchantment" }) );
    add_prop(OBJ_I_RES_IDENTIFY, 10);
    add_prop(MAGIC_AM_ID_INFO, ({
        "These lock picks radiate magic of the enchantment sort.\n", 1,
        "They bestow a small measure of lock picking skill upon the user.\n", 45 }) );
}

public int
wield(object wep)
{
    added_skill = (10 + ((TP->query_skill(SS_OPEN_LOCK)) / 4));
    if ((TP->query_skill(SS_OPEN_LOCK) + added_skill) > 100)
    {
        added_skill = (100 - (TP->query_skill(SS_OPEN_LOCK)));
    }

    TP->set_skill_extra(SS_OPEN_LOCK,
        (TP->query_extra_skill(SS_OPEN_LOCK) + added_skill));
    WRITE("You wield the " + short() + ". Your hands feel nimbler, more " +
        "skilled while gripping the picks.");
    SAY(" grips the handle of a set of lock picks in " + POSSESSIVE(TP) +
        " hands.");
    return 1;
}

public int
unwield(object wep)
{
    TP->set_skill_extra(SS_OPEN_LOCK,
        (TP->query_skill_extra(SS_OPEN_LOCK) - added_skill));
    WRITE("You unwield the " + short() + ". Your hands feel less nimble and " +
        "skilled at picking locks.");
    SAY(" releases " + POSSESSIVE(TP) + " grip on the set of lock picks.");
    return 1;
}


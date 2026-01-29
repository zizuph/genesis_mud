/*
 * Fire arrow used by /d/Krynn/turbidus_ocean/living/pirate_marksman.c
 * Based on code developed by Navarre for the old elven archers.
 * 
 * Arman Kharas, January 2021.
 */

#include </stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/arrow";
inherit "/lib/keep";
inherit "/d/Genesis/specials/resist";

public void
create_arrow()
{
    set_adj("tarred");
    add_adj("black-feathered");
    set_projectile_id("fiery_black_feathered_arrow");
    set_hit(40);
    set_pen(58);
    set_keep(1);
    
    add_item(({"feathers", "raven feathers"}), 
        "These black raven feathers are incredible " +
        "smooth, allowing the wind to pass over them " +
        "without hindrance.\n");
    add_item(({"shaft", "ash shaft"}), 
        "The shaft is made of ash making this arrow " +
        "very well balanced.\n");
    add_item(({"black tar substance","tar","tar substance",
        "substance"}),
        "A strange alchemical tar has been coated all over the " +
        "the head of the arrow.\n");

    add_prop(MAGIC_AM_ID_INFO, 
        ({ "This arrow has been coated in a gnomish alchemical " +
        "solution that was supposed to be effective in re-growing " +
        "hair, but has proven to be a very flamable. Applied " +
        "to arrows results in them exploding on impact doing " +
        "fire damage.\n", 60}));        
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));    
    add_prop(OBJ_S_WIZINFO, 
        "This arrow has a very high pen due to natural piercing " +
        "damage but also because of alchemical fire damage on the target. " +
        "fire resistance or vulnerability impacts the damage output of " +
        "the arrow based on the function in /d/Genesis/specials/resist.c " +
        "spell_resist_modify_value(int value, int resist).\n" +
        "They are carried by ~/turbidus_ocean/living/pirate_marksman.c\n");
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow has" : "These arrows have") + 
        " fins made from the finest raven feathers, fletched " +
        "to an ash shaft ending at a sharp steel arrowhead coated " +
        "in a strange black tar substance.\n";
}

public varargs
void
projectile_hit_target(object archer, int aid, string hdesc, int phurt,
    object enemy, int dt, int phit, int dam, int hid)
{
    string you_burnt, they_burnt;
    int resistance = enemy->query_magic_res(MAGIC_I_RES_FIRE);

    // Damage is modified by the following formulas based on
    // target vulnerability or resistance to MAGIC_I_RES_FIRE
    //
    //    if (random(100) < (resistance * 80 / 100)), dam = 0;
    //
    //    dam = (dam * (100 - max(min(resistance, 100), -50))) / 100;

    dam = spell_resist_modify_value(dam, resistance);
        
    switch(dam)
    {
        case 0:
            you_burnt = "You are unaffected by the fire.\n";
            they_burnt = " seems unaffected by the fire.\n";
            break;
        case 1..200:
            you_burnt = "You feel burnt by the fire.\n";
            they_burnt = " seems burnt by the fire.\n";
            break;
        case 201..350:
            you_burnt = "You are badly hurt by the fire.\n";
            they_burnt = " seems badly hurt by the fire.\n";
            break;
        default:
            you_burnt = "You are engulfed in flames.\n";
            they_burnt = " is engulfed in flames.\n";
    }
            
    tell_room(environment(enemy), "The tarred black-feathered arrow " +
        "explodes as it hits " + QTNAME(enemy)+".\n", enemy);
    tell_room(environment(enemy), QCTNAME(enemy)+they_burnt, enemy);
    enemy->catch_tell("The tarred black-feathered arrow explodes " +
        "as it hits you.\n");
    enemy->catch_tell(you_burnt);

    ::projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt, phit, dam, hid);
}

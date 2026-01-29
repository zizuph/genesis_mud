/*
 * /d/Raumdor/common/arm/skullplate.c
 *
 * (Based on an idea by Sarr (17.Feb.97))
 *
 * When this breastplate is hit, it have a 30% chance to cast a 
 * cone of cold back at the attacker.
 *              
 * Nerull  - 5/5-09
 *
 * 2010/08/06 Last update
 * 2011/08/04 Lavellan - Fixed do_proc runtime (hopefully), and typos
 * 2017-09-07 Malus: Fix messages to account for visibility 
 * 2020-12-30 Cotillion: Fixed the plate doing damage on misses
 *                       and various other code mistakes.
 */ 

inherit "/d/Raumdor/std/armour.c";
inherit "/d/Genesis/specials/resist.c";

#pragma strict_types
#include "/d/Raumdor/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>

/*
 * Function name: create_armour
 * Description  : Constructor to configure the armour when its created.
 */
void
create_armour()
{
    ::create_armour();
    set_name("skullplate");
    set_short("gleaming black skullplate");
    add_name("breastplate");
    set_adj("black");
    add_adj("gleaming");

    set_long("Despair positively radiates from this ghastly piece of" 
        + " armour. The design of the blackened metal is that of an" 
        + " enormous skull, its maw gaping open to cover the abdominal" 
        + " region. Hollow eye sockets are positioned upon the left" 
        + " and right breast of the armour, and are filled with dense" 
        + " metallic scales to protect what lies beneath. Within the open" 
        + " mouth of the hideous visage, a cluster of glittering black" 
        + " gemstones has been set and is held in place by blackened" 
        + " platinum prongs.\n");

    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    
    add_prop(MAGIC_AM_ID_INFO, ({
        "This breastplate is enchanted by cold magic.\n", 10,
        "When struck, the skullplate will sometimes spout a cone of " 
        + "cold back at the attacker.\n", 50}));        

    add_prop(OBJ_S_WIZINFO,"This is a magical armour. It has a special, " 
        + "that when struck, there is a 30% chance it will spout " 
        + "out a cone of cold and do half of the damage it took as the " 
        + "hit at the attacker. If the attacker is resistant to cold "
        + "magic, the damage may be avoided entirely.\n");

    set_ac(50);

    set_at(A_BODY);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
    add_prop(OBJ_I_VOLUME, 3623);
    add_prop(OBJ_I_WEIGHT,  F_WEIGHT_DEFAULT_ARMOUR(query_ac(), A_BODY));
    
    setuid();
    seteuid(getuid());
}

void 
cone_attack(object att, int dam)
{
    if (!query_worn() || !objectp(att))
        return;

    /* No distance attacks */
    if (environment(att) != environment(query_worn()))
        return;

    // Cap possible damage to something reasonable
    dam = min(dam, F_PENMOD(40, 100));

    // Resistances.
    int resistance = combine_resistances(att, ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_COLD }) );
    int cone = F_NEW_DAMAGE(dam / 2, random(100), resistance);

    if (wearer->can_see_in_room())
    {
        wearer->catch_msg("As " + QTPNAME(att) + " blow is " +
            "partially absorbed by your "+ short() +
            ", a cone of cold spouts from the center of its " +
            "hideous mouth and engulfs " + QTNAME(att) +
            (cone ? " with frigid frost" : ", but it has no effect") +
            "!\n");
    }

    if (att->can_see_in_room())
    {
        if (CAN_SEE(att, wearer))
        {
            att->catch_msg("As your blow is partially absorbed by " +
                QTPNAME(wearer) + " " + short() + ", a cone of cold " +
                "spouts from the center of its hideous mouth and " + 
                "engulfs you" +
                (cone ? " with frigid frost" : ", but you resist it") +
                "!\n");
        }
        else
        {
            att->catch_msg("As your blow is partially absorbed by " +
                QTPNAME(wearer) + " armour, a cone of cold "
                + "spouts out and engulfs you" +
                (cone ? " with frigid frost" : ", but you resist it") +
                "!\n");
        }
    } else if (cone) {
        att->catch_msg("You are struck by a frigid blast!\n");
    }

    wearer->tell_watcher("As " + QTPNAME(wearer) + 
        " armour partially absorbs " + QTPNAME(att) +
        " attack, a cone of cold suddenly spout forth and engulfs " +
        QTNAME(att) + (cone ? " with frigid frost" : ", but it has no effect") +
        "!\n", att);

    if (cone)
    {
        mixed hit = att->hit_me(cone, MAGIC_DT, wearer, -1);

        // Here we log the damage.    
        log_file("skullplate_dam", "" 
            + wearer->query_name() + " (" + wearer->query_average_stat() 
            + ") PEN " + cone + " DMG: " + hit[3] + " on " + att->query_name() 
            + " (" + att->query_average_stat() + ") at "
            + extract(ctime(time()))+".\n", 0);

        if (att->query_hp() <= 0)
        {
            att->do_die(wearer);
        }
    } 
}

int last_attack;
/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    int res = ::got_hit(hid,ph,att,dt,dam);

    /* Lets not attack on misses */
    if (dam <= 0)
        return res;

    /* At most every 5 seconds */
    if ((last_attack + 5) > time())
        return res;

    /* 30% chance */
    if (random(100) >= 30)
        return res;

    last_attack = time();
    set_alarm(0.0, 0.0, &cone_attack(att, dam));
}



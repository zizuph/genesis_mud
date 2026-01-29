/*
 * File : elven_blade.c
 * Elven blade, Sarist's family sword. Quest reward.
 * 
 * Blizzard, 03/03/2003
 * Cotillion -2004-10-13
 * - Fixed ::did_hit
 * Cotillion 2015-02-14:    LIVE_I_QUICKNESS 65 -> 50
 * Cotillion 2020-05-24
 * - The above nerf was only added as a comment, fixed
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit "/lib/keep";

create_weapon()
{
    set_name("sword");
    add_name(({"_sarist_sword_reward_", "longsword" })); 
    set_short("azure rune-etched longsword");
    set_adj( ({ "azure", "runed-etched" }) );
    set_long("This long and slender sword is an elegant weapon, clearly of " +
        "elven craft. Its hilt and pommel are made of silver, the blade of " +
        "finely forged, strange azure metal is perfectly balanced, what " +
        "affords quick recovery in combat. There are etched runes on the " +
        "surface of this weapon that glow brightly indicating it has " +
        "undergone some form of enchantment, but no identifying marks " +
        "can be recognized.\n");
   
    add_item("runes",
        "The long azure blade is decorated with runes, that seem to " +
        "glow brightly, shedding light on the surroundings.\n");
       
    set_default_weapon(49, 46, W_SWORD, W_SLASH | W_IMPALE, W_LEFT);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_LIGHT, 2);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This is Sarist's family sword. The quest " +
        "reward, given to player after saving the elf scout. The sword " +
        "refuses to be wielded by evil people. It was made of some strange " +
        "azur metal and thanks to elven magic it has increased hit and " +
        "pen, sometimes dealing extra damge to evil aligned enemies. " +
        "It also grants the player quickness of 50.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"The sword has been enchanted by elven magic.\n", 10,
        "The magic, used for enchanting this blade, prevents it to be " +
        "wielded by evil people.\n", 20,
        "The sword has been made of strange azure metal and thus it is " +
        "very light, but also extremely lethal.\n", 30 }) );
        
    add_prop(OBJ_I_VOLUME, 1800);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,38) + 1000);
   
    set_wf(TO);
    set_likely_dull(1);
    set_likely_break(1);
    set_keep(1);
}

public mixed
wield(object wep)
{
    if ( TP->query_alignment() < 100 )
    {
        say(QCTNAME(TP) + " tries to wield " + POSSESSIVE(TP) + " " + short() + 
            ", but the weapon flashes brighty and resists " + OBJECTIVE(TP) + 
            ". \n");
        
        TP->heal_hp(-(TP->query_hp() / 4));
        
        return "You grasp the hilt of the " + short() + ", but after a " +
            "moment it flashes brightly, burning your hand.\n" +
            "Gritting your teeth, you unwield the " + short() + ".\n";
    }
    
    write("You grasp the hilt of the " + short() + " firmly.\n");
    say(QCTNAME(TP) + " grasps the hilt of " + POSSESSIVE(TP) + " " +
        short() + " firmly.\n");
    
    wielder = TP;

    wielder->add_prop(LIVE_I_QUICKNESS,
        wielder->query_prop(LIVE_I_QUICKNESS) + 50);
    wielder->query_combat_object()->cb_update_speed();
                        
    return 1;
}
 
public int
unwield(object what)
{
    query_wielded()->add_prop(LIVE_I_QUICKNESS, query_wielded()->query_prop(LIVE_I_QUICKNESS) - 50);
    query_wielded()->query_combat_object()->cb_update_speed();
    return 0;        
}
 
public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
        int dam)
{
    
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    if ( enemy->query_alignment() < 10 )
    {   
        if ( !random(5) )
        {
            wielder->catch_msg("The runes on the " + short() + 
                " flash brightly.\n");
            
            if ( phurt > 1 )
            {
                enemy->hit_me(dam/2, W_SLASH, wielder, -1, -1);

                if ( enemy->query_hp() <= 0 )
                {
                    enemy->do_die(wielder);
                }
            }
        }
        
        return 0;
    }
    
    return 0;
}

int
set_dull(int du)
{
    return 0;
}
                

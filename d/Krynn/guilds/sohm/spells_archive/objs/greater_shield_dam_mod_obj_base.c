/*
 * Custom Damage Modification Messages for Greater Magic Shield
 *
 * Created by Arman 2016
 */
 
#pragma strict_types
#include <macros.h>
inherit "/d/Genesis/specials/std/dam_mod_obj_base";
                   
/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    ::create_effect();
    set_name("_greater_magic_shield_dam_mod_obj");
    add_name( ({"greater magic shield dam mod obj" }) );
    set_short("hidden magic shield damage modifer object");    
    set_long("A WoHS greater magic shield damage modifier object. One should not be able to see "+
           "it in their inventory.\n");
    setuid();
    seteuid(getuid());
}
public void
attack_modified(object player, object attacker, int attack_id)
{
    if (!objectp(attacker) || !objectp(player))
    {
        return;
    }
    
    if (query_dam_mod_absorb())
    {
        // absorbs damage
        player->catch_msg("The shimmering shield of magical force " +
            "absorbs the attack from " + QTNAME(attacker)
            + ", deflecting the blow.\n");
        attacker->catch_msg("A shimmering shield of magical force surrounding " + 
           QTNAME(player) + " absorbs your attack, deflecting the blow.\n");
        player->tell_watcher("The shimmering shield of magical force surrounding " +
            QTNAME(player) +  " absorbs the attack from " + QTNAME(attacker)
            + ", deflecting the blow.\n", ({ player, attacker }));
    }
    else
    {
        ::attack_modified(player, attacker, attack_id);
    }        
}
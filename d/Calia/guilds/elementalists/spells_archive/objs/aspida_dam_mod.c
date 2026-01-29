/*
 * Custom Damage Modification Messages for Stoneskin (Aspida)
 *
 * Created by Jaacar, December 2017
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
    set_name("_aspida_dam_mod_obj");
    add_name( ({"aspida dam mod obj" }) );
    set_short("hidden aspida damage modifer object");    
    set_long("An aspida damage modifier object. One should not be able to see "+
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
        player->catch_msg("The attack from " + QTNAME(attacker)
            + " strikes you, but your diamond-like skin absorbs "
            + "and deadens the blow.\n");
        attacker->catch_msg("Your attack on " + QTNAME(player)
            + " deadens as it strikes " + player->query_possessive()
            + " diamond-textured body and it does not seem to hurt "
            + player->query_objective() + " as much as you think it "
            + "should.\n");
        player->tell_watcher(QCTNAME(attacker) + " strikes " + QTNAME(player)
            + ", but the blow deadens on contact and doesn't appear to "
            + "hurt as much as it should have.\n", ({ player, attacker }));
    }
    else
    {
        ::attack_modified(player, attacker, attack_id);
    }        
}

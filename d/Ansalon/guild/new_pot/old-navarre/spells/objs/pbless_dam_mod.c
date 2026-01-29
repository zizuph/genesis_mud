/*
 * Custom Damage Modification Messages for Pbless
 *
 * Created by Navarre, May 2013
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
    set_name("_base_pbless_dam_mod_obj");
    add_name( ({"base pbless dam mod obj" }) );
    set_short("hidden pbless damage modifer object");    
    set_long("A pbless damage modifier object. One should not be able to see "+
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
        player->catch_msg("The attack from " + 
                          attacker->query_the_name(player) + " hits you, " +
                          "but your blessing by Takhisis weakens the " +
                          "blow.\n");

        attacker->catch_msg("Your attack on " +
                            player->query_the_name(attacker) +
                            " is weakened by an unseen force.\n");
            
        player->tell_watcher(QCTNAME(attacker) + " strikes " +
                             QTNAME(player) + ", but the blow appears to " +
                             "have less effect than it should have had.\n",
                             ({ player, attacker }));
    }
    else
    {
        ::attack_modified(player, attacker, attack_id);
    }        
}

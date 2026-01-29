/*
 * Knights of Solamnia Damage Absorbtion
 * 
 * Knights of the Crown and Rose Order get damage absorbtion when
 * they are mounted on their warhorse.
 * 
 * Created by Petros, December 2013
 *
 * 2018-11-11: This has now been increased to 10 caid.
 */
 
#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../../guild.h"

inherit "/d/Genesis/specials/std/dam_mod_obj_base";
inherit KNIGHT_UTILITY;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_knight_mounted_absorb_object_");
    add_name( ({ "knight_mounted_absorb_obj" }) );
    set_short("hidden knight mounted absorbtion object");    
    set_long("This damage absorbtion object is for certain Knights of Solamnia."
    + " You shouldn't see this.\n");

    setuid();
    seteuid(getuid());

    set_dam_mod_combat_aid(10);
}

/*
 * Function:    is_knight_mounted_absorb_object
 * Description: Indicates whether this is the Knight Mounted Absorb
 *              Object. Used in filters during remove_object
 */
public int
is_knight_mounted_absorb_object()
{
    return 1;
}

/*
 * Function     : query_dam_mod_valid
 * Description  : Validation function to see whether this damage modifier 
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 *                dt        - int, damage type
 * Returns      : 0/1 - invalid/valid
 */
public int
query_dam_mod_valid(object player, object attacker, int attack_id, int dt)
{
    object  steed;
    mixed   leading;
    
    leading = filter(filter(player->query_following_steeds(), 
              &->is_solamnian_steed()), 
              &operator(==)(environment(player)) @ environment);
    
    if (pointerp(leading) && sizeof(leading) && leading[0]->query_auto_mount())
        leading[0]->unlead_and_mount(0);
    
    if (query_mounted_solamnian_steed(player))
        return 1;

    return 0;
}
    
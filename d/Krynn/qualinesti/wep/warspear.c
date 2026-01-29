/*
 * File : warspear.c
 * A weapon used by elves in Qualinesti.
 *
 * Blizzard, 02/2003
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "../local.h"

create_weapon()
{
   set_name(({ "warspear", "spear", "war-spear" }));
   set_short("leaf-headed elven war-spear");
   set_adj( ({ "leaf-headed", "elven", "war" }) );
   set_long("This magnificant spear has a three foot long shaft of pale " +
       "white wood as hard as steel. Its razor-sharp head is leaf-shaped, " +
       "and could cut a hair lengthwise. It is used by grasping the " +
       "center of the shaft with one hand, and the butt with the other, " +
       "giving excellent maneuverability and accuracy. This is a favourite " +
       "of the elven hunters.\n");
   set_default_weapon(39, 38, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);
   set_wf(TO);
   add_prop(OBJ_I_VOLUME, 1800);
   add_prop(OBJ_I_WEIGHT, 5000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(39,34) + 1000);
   set_keep(1);
   
}

int 
wield_check(object ob)
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(47);
        set_pen(46);
        query_wielded()->update_weapon(TO);
        
        return 1;
    }
}

mixed
wield(object ob)
{
    if ( !interactive(TP) )
    {
        set_alarm(1.0, 0.0, &wield_check(TO));
        return 1;
    }
}

int
unwield(object what)
{
    set_hit(39);
    set_pen(38);
    query_wielded()->update_weapon(TO);
    
    return 0;
}

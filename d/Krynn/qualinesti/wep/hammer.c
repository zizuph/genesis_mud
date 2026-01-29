/*
 * File : hammer.c
 * Kragh's warhammer.
 *
 * Blizzard,    05/2003
 * Carnak,      06/2017 - Added W_CLUB to the code so the wt and dt are 
 *                        correctly added.
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "../local.h"

create_weapon()
{
   set_name(({"hammer", "club", "warhammer", "war-hammer"}));
   set_short("red iron war-hammer");
   set_adj( ({"red", "iron", "war" }) );
   set_long("This heavy warhammer has a broad striking head that can easily " +
       "beat down the target. It is made of a strange, blood-red metal, " +
       "which shimmers with an oily sheen. The weapon is a good example " +
       "of dwarven craft quality.\n");
   set_default_weapon(31, 35, W_CLUB, W_BLUDGEON, W_ANYH);
   set_wt(W_CLUB);
   set_wf(TO);
   add_prop(OBJ_I_VOLUME, 5000);
   add_prop(OBJ_I_WEIGHT, 7000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(31,35) + random(300));
}

int 
wield_check(object ob)
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(41);
        set_pen(45);
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
    set_hit(31);
    set_pen(35);
    query_wielded()->update_weapon(TO);
    
    return 0;
}

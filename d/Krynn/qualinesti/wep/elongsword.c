/*
 * File : elongsword.c
 * Qualinesti; longsword for elves in the camp.
 *
 * Blizzard, 02/2003
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
   set_name(({"longsword", "sword"}));
   set_short("shiny elven longsword");
   set_adj( ({"shiny", "elven", "slender" }) );
   set_long("This is a fine elven sword, long and slender. A typical " +
            "elven weapon with a slim blade and a hilt, carefully " +
            "ornamented with metal carvings.\n");
   set_default_weapon(35, 32, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
   set_wf(TO);
   add_prop(OBJ_I_VOLUME, 1800);
   add_prop(OBJ_I_WEIGHT, 5000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,32) + random(300));
}

int 
wield_check(object ob)
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(45);
        set_pen(42);
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
    set_hit(35);
    set_pen(32);
    query_wielded()->update_weapon(TO);
    
    return 0;
}


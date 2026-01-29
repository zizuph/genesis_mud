/*
 * File : shortsword.c
 * Qualinesti; shortsword for elves in the camp.
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
   set_name(({"shortsword", "sword"}));
   set_short("fine shiny shortsword");
   set_adj( ({"shiny", "short", "elven"}) );
   set_long("This needle-pointed razor-sharp blade is about two feet " +
       "long and is made of some shiny material. A typical elven weapon " +
       "with a hilt carefully ornamented with metal carvings.\n");
   set_default_weapon(27, 26, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
   set_wf(TO);
   add_prop(OBJ_I_VOLUME, 1400);
   add_prop(OBJ_I_WEIGHT, 1800);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(27, 26) + 400);
}

int 
wield_check(object ob)
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(37);
        set_pen(36);
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
    set_hit(27);
    set_pen(26);
    query_wielded()->update_weapon(TO);
    
    return 0;
}

/*
 * File : edagger.c
 * Qualinesti; standard dagger for elves in the camp.
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
   set_name(({"knife", "dagger"}));
   set_short("long elven dagger");
   set_adj( ({"long", "elven", "thin" }) );
    add_adj("metal");  /* it is, isn't it? -Gorboth */
   set_long("This elven dagger has a long, thin blade and is quite sharp. " +
       "Considering its light weight it could be easily used in conjunction " +
       "with a sword.\n");
   set_default_weapon(16, 15, W_SLASH | W_IMPALE, W_ANYH);
   set_wt(W_KNIFE);
   set_wf(TO);
   add_prop(OBJ_I_VOLUME, 800);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,19) + random(70));
}

int 
wield_check(object ob)
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(31);
        set_pen(30);
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
    set_hit(16);
    set_pen(15);
    query_wielded()->update_weapon(TO);
    
    return 0;
}

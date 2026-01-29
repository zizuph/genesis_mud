/*
 * File : dagger.c
 * Qualthas' dagger.
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
    set_short("long gleaming dagger");
    set_adj( ({"long", "elven", "thin" }) );
    set_long("This long, straight dagger glitters with an bluish hue. It is " +
        "made of best quality steel and thus it is very sharp. " +
        "Considering its light weight it could be easily used in conjunction " +
        "with a sword.\n");
    set_default_weapon(20, 22, W_SLASH | W_IMPALE, W_ANYH);
    set_wt(W_KNIFE);
    set_wf(TO);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,19) + random(170));
}

int 
wield_check(object ob)
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(30);
        set_pen(32);
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
    set_hit(20);
    set_pen(22);
    query_wielded()->update_weapon(TO);
    
    return 0;
}
    
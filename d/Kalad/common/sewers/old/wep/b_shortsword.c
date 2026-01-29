/*     Created by:      Sir Toby, 97-07-30
 *     Purpose:		Equip thieves and lizards in sewers.
 *     Modified:        
 */


#pragma strict_types

inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include <formulas.h>

#define HIT (21+random(5))
#define PEN (16+random(6))

void
create_weapon()
{
::create_weapon();
    set_name("sword");
    add_name("shortsword");

    set_short("black shortsword");
    set_long("This is a fincrafted black metal shortsword. " +
	     "It is so deep black that light is not " +
	     "reflected at all. The pommel is as black " +
	     "as the blade of this fine piece of weapon.\n");

    set_adj("black");
    set_adj("metal");
   
    add_cmd_item( ({"sword","shortsword"}),({"touch","feel"}),
        "The shortsword is cold and smooth.\n");


    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_PIERCE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN) + random(10));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(HIT,W_SWORD) + random(35));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/4);


}
/*     Created by:      Sir Toby, 97-07-31
 *     Purpose:		Equip thieves and lizards in sewers.
 *     Modified:        
 */


#pragma strict_types

inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include <formulas.h>

#define HIT (29+random(3))
#define PEN (33+random(3))

void
create_weapon()
{
::create_weapon();
    set_name("mace");
    set_pname("maces");
    add_name("club");
    add_pname("clubs");

    set_short("black mace");
    set_long("This is a fincrafted black metal mace. " +
	     "It is so deep black that light is not " +
	     "reflected at all. The handle is as black " +
	     "as the blade of this fine piece of weapon.\n");

    set_adj("black");
    set_adj("metal");
   
    add_cmd_item( ({"mace","black mace"}),({"touch","feel"}),
        "The mace is cold to the touch.\n");


    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN) + random(10));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(HIT,W_CLUB) + random(35));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/4);


}


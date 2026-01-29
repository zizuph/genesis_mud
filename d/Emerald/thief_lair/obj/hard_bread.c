/* Roast venison, which can be purchased (its rather expensive) from
   the bandits at /thief_lair/cave9.
   Code (c) 1999 to Damian Horton (BKA Casimir)
*/

inherit "/std/food";

#include <stdproperties.h>

create_food()
{
    set_name("bread");
    add_name("loaf");
    set_adj("hard");
    add_adj("rye");
    set_short("loaf of bread");
    set_long("A loaf of hard, dry bread, made of barley flour. Not the "+
	     "most appetizing of fare, but nontheless nourshing.\n");

    set_amount(1300); 
    add_prop(OBJ_I_WEIGHT, 1300);  
    add_prop(OBJ_I_VOLUME, 1100);
}






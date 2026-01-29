/* 
 * /d/Kalad/common/wild/pass/arm/dragon_scale.c
 * Purpose    : A shield of dragon scale, it has an ac 40, since you must defeat the very powerful dragon to get it
 * Located    : On the Deep Dragon
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
/* has 40 in ac since its a reward for killing the dragon */
create_armour()
{
    ::create_armour();
    set_name("scale");
    set_adj("maroon");
    add_adj("dragon");
    set_pname("scales");
    set_short("maroon dragon scale");
    set_pshort("maroon dragon scales");
    set_long("A large triangular-shaped dragon scale. From the large "+
      "size of the scale, it appears to have once been located on a dragon's "+
      "chest. Its dark red hue reminds one of the most valueable of rubies.\n");
    set_ac(40);
    set_at(A_SHIELD);
    add_prop(OBJ_I_VALUE,1728);
    add_prop(OBJ_I_WEIGHT,7500);
    add_prop(OBJ_I_VOLUME,7500);
}

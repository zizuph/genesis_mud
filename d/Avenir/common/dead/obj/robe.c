// Glowing robe held by the banshee on the marshes
//     -I.

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name(({"robes","robe","gossamer"}));
  set_short("white gossamer robe");
  add_adj(({"white", "gossamer","shining","glowing","silk"}));
  set_long ("This robe of white gossamer silk is translucent and "
       +"fragile. It seems to give off a bright glow, lighting "
       +"the area around you and feeling warm to the touch.\n");
  set_ac (3);
  set_am(({ -1, 0, 1}));
  set_at (A_ROBE);

  add_prop(OBJ_I_WEIGHT, 30);
  add_prop(OBJ_I_VALUE, 8900);
  add_prop(MAGIC_AM_MAGIC,({8,"enchantment"}));
  add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
  add_prop(OBJ_I_LIGHT,2);

  add_prop(MAGIC_AM_ID_INFO,({
     "The "+short()+" seems to be somewhat magical.\n",1,
     "It was made by the great sorceress Aurunith.\n",10,
     "The gossamer fabric it was woven with is made from fine "
        +"strands of the herb Mittikna, making it glow.\n",20}));

  add_prop(OBJ_S_WIZINFO,"This cloak is a lightsource, with "
        +"a light value of 2. It is possessed by the banshee "
        +"on the dead marshes.\n");
}

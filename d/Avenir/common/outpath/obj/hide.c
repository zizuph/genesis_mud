/* Armour for the quarl in the newbie area
 *  Cirion  050396
 */
#pragma strict_types

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void create_armour()
{
  string   myadj = ({ "heavy", "thick", "smelly", "large",
                      "disgusting" })[random(5)];

  set_name("hide");
  set_adj(({"thick","smelly", myadj}));
  set_short(myadj + " hide");
  set_long("It is the large hide of some animal, untreated "
      +"and worn over the shoulders and arms. It seems that "
      +"it would offer decent protection against blows.\n");
  set_default_armour(A_TORSO | A_L_ARM | A_R_ARM, 10,
         ({ -1, 0, 1 }));

  add_prop(OBJ_I_WEIGHT, 3197);
  add_prop(OBJ_I_VOLUME, 5000);
  add_prop(OBJ_I_VALUE, 200);
}

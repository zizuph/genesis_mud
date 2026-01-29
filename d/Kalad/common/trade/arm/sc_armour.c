inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("full suit of adamantite armour");
   add_name("suit");
   add_name("adamantite armour");
   add_name("armour");
   set_long("A complete suit of impervious adamantite armour, consisting of "+
      "interlocking helmet, platemail, gauntlets and greaves. In stark contrast "+
      "to the blinding brilliance of the metal is the rose-red hue of a "+
      "red hawk, the symbol of the sheriff-captain of Kabal.\n");
   set_ac(25);
   set_at(A_HEAD | A_BODY | A_ARMS | A_LEGS);
   add_prop(OBJ_I_VALUE,2400); /* Its a full suit after all! */
   add_prop(OBJ_I_WEIGHT,50000);
   add_prop(OBJ_I_VOLUME,50000);
}

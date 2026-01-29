inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

create_armour()
{
   ::create_armour();
   set_name("mail");
   set_short("light mail");
   set_long("This suit of mail resembles chainmail in appearance, but "
      +"weighs next to nothing. The weight, though, is not an "
      +"accurate measure of the protection of this fine suit of "
      +"armor. There is not a weak link in the entire suit, and "
      +"the metal almost seems too strong to be normal.\n");
   set_adj("light");
   set_default_armour(26, A_BODY | A_ARMS, 0, 0);
}

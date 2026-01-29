
// Standard boots for guards in the Bazaar area.
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("boots");
  set_short("pair of red leather boots");
  add_adj(({"red", "leather"}));
  set_long ("This is a pair of high boots made from red dyed leather. "+
            "They are well broken in and feel quite comfortable.\n");
  set_ac (12);
  set_am(({ 0, 2, -1}));
/* removed A_LEGS so codpiece can be worn
  set_at (A_LEGS | A_FEET);
*/
   set_at (A_FEET);
}

/* created by Aridor, 09/15/94 */

inherit "/std/armour";

#include <wa_types.h>
#include <ss_types.h>

void
create_armour()
{
   set_name("boots");
   set_adj("steel");
   set_short("pair of steel boots");
   set_pshort("pairs of steel boots");
   set_long("These are heavy steel boots. It looks like they " +
      "have been used to stomp goblins recently.\n");
   set_at(A_FEET);
   set_ac(20);
}


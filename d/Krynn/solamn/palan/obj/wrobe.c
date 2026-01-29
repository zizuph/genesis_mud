/* created by Aridor, 09/04/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("robe");
    set_adj("white");
    set_short("white robe");
    set_long("This is the white robe of the order of the clerics of " +
      "Paladine. The collar closes tight around the neck " +
      "and the robe falls down to the floor with a small belt " +
      "around the waist, much like a dress.\n");
    set_ac(10);
    set_at(A_ROBE);
}

/* created by Aridor, 09/04/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("dress");
    set_adj("fancy");
    set_short("fancy dress");
    set_long("This is a wide fancy dress fashioned among the ladies " +
      "of Palanthas. The collar closes tight around the neck " +
      "and the dress falls down to the floor with a small belt " +
      "around the waist.\n");
    set_ac(4);
    set_at(A_ROBE);
}

/* seashell necklace
 * Created by Damaris 01/2001
 */
#pragma strict_types
#include "arm.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
inherit "/std/arm";

void create_armour()
{
    set_name("necklace");
    set_adj(({"mulicoloured", "seashell",}));
    set_short("multicoloured seashell necklace");
    set_pshort("multicoloured seashell necklaces"); /* Sets plural name. */
    set_long("This necklace has many small multicoloured seashells "+
      "that have been strung on a gold chain.\n");

    set_ac(50);
    add_prop(OBJ_I_VALUE, 100);
    set_at(A_NECK);
    set_am( ({-1,3,-2 }) );
    set_af(this_object());
}

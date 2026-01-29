/* 
 * Sandals for the Union of the Warriors
 * of Shadow. Cirion 031696
 */
#pragma strict_types
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>


public void
create_armour()
{
    set_name("sandals");
    add_name("pair");
    add_name("sandal");
    set_pname("pairs");
    set_short("pair of leather sandals");
    set_adj(({"leather","soft"}));
    add_adj("union");
    add_adj("unworn");

    set_long("These sandals are light and comfortable. "+
	"They are suitable for lounging around indoors.\n");

    add_prop(OBJ_I_VOLUME,  107);
    add_prop(OBJ_I_WEIGHT,  164);
    add_prop(OBJ_I_VALUE,    46);

    set_at(A_FEET);
    set_ac(2);
}

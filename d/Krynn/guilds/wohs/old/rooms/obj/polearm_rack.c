/* Karath
 * a polearm rack for holding staves in Wayreth
 *
 */

inherit "/std/container";
inherit "/lib/keep";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <macros.h>

public void
create_container()
{
    set_name("rack");
    add_adj( ({"mahogany", "weapon", "staff", "polearm"}) );
    set_short("@@short_fun");
    set_long("This rack is affixed to the wall of the tower. "+
	"It has small circular holes in the bottom, and leather "+
	"straps at the top for holding staves and other polearms "+
	"steady.\n");
    add_prop(CONT_I_RIGID,          0);
    add_prop(CONT_I_WEIGHT,     20000);
    add_prop(CONT_I_VOLUME,     20000);
    add_prop(CONT_I_MAX_WEIGHT, 85000);
    add_prop(CONT_I_MAX_VOLUME, 85000);

    add_prop(OBJ_M_NO_GET,"The rack is built into the wall of the tower.\n");
    add_prop(CONT_M_NO_INS, VBFC_ME("check_insert"));
}

public mixed
check_insert()
{
    int i;
    object *arr;

    for (i = 0; i < 10; i++)
    {
        if (!objectp(calling_object(-i)))
            break;
        if (calling_object(-i) == TO)
        {
            arr = ({calling_object(-(i+1))});
	    if(arr[0]->query_wt() == W_POLEARM)
		return 0;
	    else return "The rack is meant for polearms only.\n";
        }
    }
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "mahogany staff rack";
    return "empty mahogany staff rack";
}

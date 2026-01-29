/* Karath
 * a knife scabbard holder for holding knives in Wayreth
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
    set_name("sheathes");
    add_adj( ({"row", "polished", "leather", "knife", "dagger"}) );
    set_short("@@short_fun");
    set_long("A very interesting looking item, this is a very wide belt "+
	"of leather with a number of sheathes on it. It it tacked firmly "+
	"into the wall and is used for storage of knifes and daggers. The "+
	"leather is polished to a supple, well-worn, shine.\n");
    add_prop(CONT_I_RIGID,          0);
    add_prop(CONT_I_WEIGHT,     20000);
    add_prop(CONT_I_VOLUME,     20000);
    add_prop(CONT_I_MAX_WEIGHT, 85000);
    add_prop(CONT_I_MAX_VOLUME, 85000);

    add_prop(OBJ_M_NO_GET,"The sheathes are firmly tacked to the wall "+
	"of the tower.\n");
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
	    if(arr[0]->query_wt() == W_KNIFE)
		return 0;
	    else return "The sheathes are only big enough to hold knives.\n";
        }
    }
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "row of leather knife sheathes";
    return "row of empty leather knife sheathes";
}

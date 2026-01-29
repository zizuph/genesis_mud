/* Punisher harness */
// converted to /lib/wearable_item by Lilith 09 Jul 1998
// converted to use item_expiration, code cleanup--Lilith, May 2022

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_object()
{
    config_wearable_item(A_TORSO, 1, 15, this_object());

    set_name("harness");
    add_name(({"armour", "leather"}));
    set_short("black leather harness");
    add_adj(({"leather", "harness", "black" }));
    add_pname(({"clothes", "clothing"}));
    set_long ("This harness is composed of straps of leather "+
        "intricately woven together. It looks like its function "+
        "is mostly for vanity or intimidation purposes, "+
        "as it wouldn't be much protection in a fight. "+
        "  It can be worn under most armours.\n");
		
    add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
    add_prop(OBJ_I_WEIGHT, 1000);   /* weight 1 kilo */
    add_prop(OBJ_I_VALUE, 144);
	
	if (IS_CLONE)
      set_item_expiration();  	  
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

/*
 * Function name: leave_env
 * Description:   The clothing is moved from the inventory.
 * Arguments:     from - Where from  to - Destination.
 */
void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}


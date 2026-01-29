/* belly chain for the bazaar and future mecantile pale
 * d/Avenir/common/bazaar/Obj/worn/belly_chain.c
 *
 * Lilith May 2022: added item_expiration functionality
 */


inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define HIS  this_player()->query_possessive()

int times; /* How many times we can recover */
int  query_times()       {    return times;   }

void
create_object()
{
    config_wearable_item(A_HIPS, 1, 1, this_object());

    if (times) times++;
    else       times = 1;

    set_name("belly chain");
    add_name(({"chain", "cinctura"}));
    add_pname("cinturas");
    add_pname(({"clothes", "clothing"}));
    set_adj("black");
    set_short("black belly chain");
    set_long("Thin braided chains of black anodized steel wrap "+
        "around " +
        "your waist and hips. Suspended from the chains is a " +
        "diamond-shaped hematite teardrop that catches the light. " +
        "The black teardrop shaped gem swings lazily back and forth " +
        "with your every move. \n");

    add_prop(OBJ_I_VOLUME, 2000);   /* volume 2 litres */
    add_prop(OBJ_I_WEIGHT, 1000);   /* weight of slippers 1 kilo */
    add_prop(OBJ_I_VALUE, 50);
	
	set_keep(1);
	
    if (IS_CLONE)
        set_item_expiration();  

}

mixed 
wear()
{     
    write("You wrap the "+ short() +" around your hips.\n");
    say(QCTNAME(this_player()) +" wears "+ HIS +" " + short() +
        " seductively around "+ HIS +" hips.\n");
    return 1;
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
    return MASTER + ":"+ query_item_expiration_recover();
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


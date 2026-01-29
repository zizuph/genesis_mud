/* 
 * A pair of pants for the Union of the Warriors
 * of Shadow. Cirion 031696
 *       Updated by Lilith 17 Jun 2001
 *
 * * Lucius May 2009: Small cleanups
 * * Lucius Oct 2009: Changed 'union' name to an adjective.
 * * Lucius May 2016: Changed from an armour to a clothing
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";
inherit "/lib/wearable_item";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

public void
create_object(void)
{
    set_keep(1);
    config_wearable_item(A_WAIST, 1, 15, this_object());

    set_name(({"pair","pants","pant"}));
    add_pname(({"pairs", "pairs of pants"}));
    set_pshort("pairs of pale grey pants");
    set_adj(({"pale","grey","union"}));
    add_adj("unworn");

    set_long("These pants are pale grey, the colour of stone. "+
      "Made of fine sybarun wool, they fit snugly at the "+
      "waist and lower legs, but flare a bit around the "+
      "thighs and knees to allow for unconstricted "+
      "movement during combat.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE,  300);  

    if (IS_CLONE)
      set_item_expiration(); 
}

public varargs string
short(object for_ob)
{
    if (query_worn())
	return "pair of pale grey pants that blouse at the knees";
    else     
	return "pair of pale grey pants";
}

public mixed 
wear(object ob)
{
    if (TP != ENV(TO))
	return 0;

    write("You fasten the pale grey pants at your "+
	"waist and blouse them over your knees.\n");
    say(QCTNAME(TP)+" fastens the pale grey pants around "+
	HIS(TP)+" waist and blouses them at the knees.\n");

    return 1;
}

public void
leave_env(object dest, object old)
{
    wearable_item_leave_env(dest, old);    
    ::leave_env(dest, old);
}



public void
appraise_object(int num)
{
    ::appraise_object(num);

}

public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);

}


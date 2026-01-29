/*
 *  file name:   lskirt.c
 *  creator:     Zielia
 *  last update:
 *  purpose:
 *  note(s):
 *  bug(s):
 *  to-do:
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

#include "zigg.h"

inherit "/std/object";

inherit "/lib/keep";
inherit "/lib/wearable_item";

public void
create_object(void)
{
    config_wearable_item(A_HIPS, 5, 10, TO);

    set_name(({"skirt", "garment", "stat::item"}));
    add_pname(({"clothes", "clothing"}));
    set_adj(({"leather", "scaled", "short", "black", "scaled-leather", 
    	"sybarun", "ziggurat"}));
    set_short("short scaled-leather skirt");
    set_long("Layers of scalloped, black, leather panels form the scales of "+
	"this skirt. Too short to be considered any kind of armour, it "+
	"offers the barest modicum of decency, just reaching the top of "+
	"the thighs when worn.\n");

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 500);
	
	if (IS_CLONE)
      set_item_expiration();  	

}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
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

/*
 *  file name:   blindfold.c
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

private static string color, material;

varargs public void
config_bf(string c, string m)
{
    if (!c)
    {
	c = one_of_list(({"red", "black", "blue", "green", "orange",
		"yellow", "purple"}));
    }

    if (!m)
    {
	m  = one_of_list(({"leather", "satin", "silk", "suede",}));
    }

    remove_adj(color);
    color = c;
    add_adj(color);

    remove_adj(material);
    material = m;
    add_adj(material);

    set_short(color +" "+ material +" blindfold");
    set_long("This soft "+ color +" "+ material +" blindfold is gentle "+
	"yet most effective in cutting off a person's sight. "+
	"It is contoured to fit the face and has "+ material +" cords "+
	"to secure it over the eyes. Soft "+ color +" fur lining helps "+
	"block out the light while providing sensual comfort.\n");
}

public void
create_object(void)
{
    config_wearable_item(A_EYES, 2, 1, TO);

    set_name(({"blindfold", "mask", "basket::item"}));
    set_adj(({"soft", "contoured", "fur-lined", "sybarun", "ziggurat"}));

    config_bf(color, material);
	set_keep(1);

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 200);
	
	if (IS_CLONE)
      set_item_expiration();  
}

public int
wear(object ob)
{
    if (TP != environment(TO))
        return 0;

    write("You position the "+ short() +" into place over your eyes, "+
	"and slowly tie it behind your head, the soft fur and "+ material +
	" drawing closer and tighter to your skin, making you blind to the "+
	"world around you even as your other senses seem to heighten.\n");

    say(QCTNAME(TP)+" positions the "+ short() +" over "+ HIS(TP) +
	" eyes and ties it in the back, effectively cutting off "+ HIS(TP) +
	" sight.\n");

    ALTER_PROP(wearer, LIVE_I_BLIND, 10);

    return 1;
}

public int
remove(object ob)
{

    write("You remove the "+ short() +" and blink rapidly as you adjust "+
      "to being able to see once again.\n");

    say(QCTNAME(TP)+" removes "+ HIS(TP) +" "+ short() +", blinking "+
	HIS(TP) +" eyes rapidly as "+ HIS(TP) +" sight adjusts to normal.\n");

    ALTER_PROP(wearer, LIVE_I_BLIND, -10);

    return 1;
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
    return MASTER + ":" + query_item_expiration_recover() +
        "#!"+ color +"!"+ material +"!#";
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    sscanf(arg, "%s#!%s!%s!#%s", arg,
        color, material, arg);
    config_bf(color, material);

}

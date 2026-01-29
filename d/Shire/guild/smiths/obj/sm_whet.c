/*
 *           Whetstone for the Smiths Guild
 *              By Morinir of the Shire
 *     much code taken from the whetstone coded by
 *         Mercade for the Rockfriends guild
 */

#pragma save_binary;

inherit "/std/object";

#include "/d/Shire/guild/smiths/smiths.h"
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>

#define CHECK_WEAPON "check_weapon"
#define STD_WEAPON   "/std/weapon"

void
create_object() {
    set_name(({ "rock" , "whetstone" , "smiths_whetstone" , "stone" }));
    set_adj("small");
    set_adj("grey");
    set_short("small grey rock");
    set_long("A small stone that has been found useful by a smith as a"+
      " whetstone. This stone would have no value to anyone but a smith.\n");

    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,10);
}

init() {
    ::init();
    add_action("sharpen","sharpen");
}

int
sharpen(string str) {
    object obj;
    object *to_sharpen;
    int repair,dull;
    string occu_guild,laym_guild;

    notify_fail("Sharpen what?\n");
    if (!strlen(str))
    {
	return 0;
    }

    if ((!parse_command(str, TP, "[the] %i", to_sharpen)) ||
      (!sizeof(to_sharpen = NORMAL_ACCESS(to_sharpen, 0, 0))))
    {
	return 0;
    }

    if (sizeof(to_sharpen) != 1)
    {
	write("Please select only one weapon to sharpen.\n");
	return 1;
    }
    else
    {
	obj = to_sharpen[0];
    }

    if (function_exists(CHECK_WEAPON, obj) != STD_WEAPON)
    {
	write("You can only sharpen weapons.\n");
	return 1;
    }

    if (!(obj->query_dt() & (W_IMPALE | W_SLASH)))
    {
	NF("Your " + obj->short() + " doesn't have any sharp edges,"+
	  " and thus cannot be sharpened.\n");
	return 0;
    }

    repair = obj->query_repair_dull();
    dull   = obj->query_dull();
    switch(dull - repair)
    {
    case 0:
	NF("There is no reason to sharpen your " + obj->short() +
	  ", since it is already as sharp as it can be.\n");

	return 0;
    case 1..2:
	break;

    default:
	NF("The " + obj->short() + " is too dull to sharpen with this"+
	  " stone.\n");
	return 0;
    }

    /*
       if (!F_LEGAL_WEAPON_REPAIR_DULL(repair, dull))
       {
	   NF("You cannot sharpen the "+obj->short()+" again without"+
	      " damaging the blade.\n");
    return 0;
       }
    */

    occu_guild=TP->query_guild_name_occ();
    laym_guild=TP->query_guild_name_craft();

    if ((occu_guild!=GUILD_NAME) && (laym_guild!=GUILD_NAME)) {
	write("It is too hard to handle the small whetstone.\n");
	return 1;
    }

    obj->set_repair_dull(++repair);

    write("You start sharpening your "+obj->short()+" with your "+short()+
      ". Soon the "+obj->short()+" is again as sharp as a razor.\n");
    say(QCTNAME(TP)+" starts sharpening the "+obj->short()+" with the "+
      short()+".\n");
    return 1;
}

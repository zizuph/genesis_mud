/*
 * Hammerhands whetstone
 * TAPAKAH, 10/2005
 * Based on smiths' whetstone
 */

#pragma save_binary;
#pragma strict_types;

inherit "/std/object";

#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"

#define CHECK_WEAPON "check_weapon"
#define STD_WEAPON   "/std/weapon"
#define SMITHS_NAME "The Smiths Guild"

int sharpen(string str);

void
create_object() {

  set_name(({ "rock" , "whetstone" , "smiths_whetstone" , "stone","hammerhand_whetstone" }));
  set_adj("small");
  set_adj("sandy");
  set_short("small sandy rock");
  set_long("A small stone that has been found useful by a smith as a "+
	   "whetstone. This stone would have no value to anyone but a smith."+
	   "\n");
  
  add_prop(OBJ_I_VALUE,50);
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
  string guild;
  
  notify_fail("Sharpen what?\n");
  if (!strlen(str))
    return 0;

  if ((!parse_command(str, TP, "[the] %i", to_sharpen)) ||
      (!sizeof(to_sharpen = NORMAL_ACCESS(to_sharpen, 0, 0))))
    return 0;
  if (sizeof(to_sharpen) != 1) {
    write("Please select only one weapon to sharpen.\n");
    return 1;
  }
  else
    obj = to_sharpen[0];
  if (function_exists(CHECK_WEAPON, obj) != STD_WEAPON) {
    write("You can only sharpen weapons.\n");
    return 1;
  }

  if (!(obj->query_dt() & (W_IMPALE | W_SLASH))) {
    write("Your " + obj->short() + " doesn't have any sharp edges,"+
	  " and thus cannot be sharpened.\n");
    return 1;
  }

  repair = obj->query_repair_dull();
  dull   = obj->query_dull();
  switch(dull - repair) {
  case 0:
    NF0("There is no reason to sharpen your " + obj->short() +
       ", since it is already as sharp as it can be.\n");    
  case 1..2:
    break;
    
  default:
    write("The " + obj->short() + " is too dull to sharpen with this"+
	  " stone.\n");
    return 1;
  }

  guild = TP->query_guild_name_craft();
  if(!TP->query_prop(HH_MEMBER) ||
     guild != SMITHS_NAME) {
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

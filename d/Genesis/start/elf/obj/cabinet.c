#include "../stddefs.h"
#include <stdproperties.h>

#pragma save_binary

inherit "/std/door";
inherit STRINGLIB;
inherit MISCLIB;

#define NAMES ({"cabinet door", "cabinet"})

#define INSIDE SHOREDIR + "wardrobe"

#define CAB_LONG \
  "It is a old, wooden cabinet fastened to the wall. The cabinet has a "+\
  "single door, and in the door is a small keyhole. Painted below the "+\
  "keyhole is a small picture of a priest. " + \
  "(Hmm... that has to be a cabinet minister.)\n"

#define CAB_OPEN_LONG \
  "The cabinet is open, and when you look inside, it seems very roomy. " +\
  "In fact, it looks like there is an entire room inside it.\n"

#define CAB_CLOSED_LONG \
  "The cabinet is closed.\n"

#define PICTURE_ITEM ({"picture", "minister", "priest"})
#define PICTURE_DESC "It is picture of a man of the cloth.\n"

#define KNOCK_DESC "Nothing happens. Nice idea, though.\n"

#define GET_FAIL_MSG \
  "It is inseparable from the wall.\n"

create_door()
{
  set_door_name(NAMES);
  set_name(NAMES);
  set_adj(({"wooden"}));

  set_long("@@mylong@@");
  add_item(PICTURE_ITEM, WRAP(PICTURE_DESC));
  add_cmd_item(NAMES, "cabinet", WRAP(KNOCK_DESC));

  add_prop(OBJ_I_WEIGHT,  50000);
  add_prop(OBJ_I_VOLUME, 500000);
  add_prop(DOOR_I_HEIGHT, 100);
  add_prop(OBJ_M_NO_GET, GET_FAIL_MSG);

  set_door_id("cabinet door");
  set_other_room(INSIDE);
  set_pass_command(({"enter", "go"}));
  set_fail_pass("The cabinet is closed.\n");
  set_open(0);

  set_locked(1);
  set_lock_name("cabinet lock");
  set_lock_command("lock");
  set_lock_mess(({"locks the cabinet.\n", 0 }));
  set_fail_lock(({"The cabinet is already locked.\n",
		  "The cabinet is open.\n"}));
  set_unlock_command("unlock");
  set_unlock_mess(({"unlocks the cabinet\n", 0 }));
  set_fail_unlock("The cabinet is already unlocked.\n");
  
  set_key(CARAVAN_KEY_VALUE);
  set_no_pick();

  load_object(INSIDE);
  /*
   * Here are some sillyness, just to make the door a separate object
   * again, not something submerged in the room description.
   */

  unset_no_show();
  set_no_show_composite(0);
  set_door_desc("@@mylong@@");
  set_open_desc("");
  set_closed_desc("");

  enable_reset();
}

reset_door()
{
  set_locked(1);
  load_object(INSIDE);
}

void set_door_id(string id) 		
{ 
  door_id = id; 
}

int pass_door(string arg)
{
  string str;

  if (!arg) {
    notify_fail(capitalize(query_verb()) + " what?");
    return 0;
  }
  if (!id(arg) &&
      !(sscanf(arg, "through %s", str) && id(str)))
    return 0;

  return ::pass_door(arg);
}

string mylong() 
{
  if (query_open())
    return WRAP(CAB_LONG + CAB_OPEN_LONG);
  else
    return WRAP(CAB_LONG + CAB_CLOSED_LONG);
}

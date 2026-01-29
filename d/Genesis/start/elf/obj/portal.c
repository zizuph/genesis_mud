#include <stdproperties.h>
#include "../stddefs.h"

#pragma save_binary

inherit OBJECT;
inherit STRINGLIB;

string destination;

#define LONG \
  "It is a huge, silver portal, through which another place can dimly be " +\
  "seen.\n"

#define PLACE_ITEM ({"place", "another place", "through portal", "other side"})
#define PLACE_DESC \
  "Whatever lies on the other side is hidden from you, as its image is too "+\
  "blurred to interpret.\n"

#define GET_FAIL_MSG \
  "It is attached to the ground by mystical forces.\n"

create_object() {
  set_name("portal");
  set_adj(({"huge", "silver"}));

  set_long(WRAP(LONG));

  add_item(PLACE_ITEM, WRAP(PLACE_DESC));
  add_cmd_item("portal",         "enter", "@@transport@@");
  add_cmd_item("portal",         "go",    "@@transport@@");
  add_cmd_item("through portal", "go",    "@@transport@@");

  add_prop(OBJ_M_NO_GET, GET_FAIL_MSG);
}


void set_destination(string str) { destination = str; }


string transport()
{
  if (this_player()->move_living("through the portal", destination))
    return "The magic of the portal fails you.\n";
  else
    return ("You feel a faint residual chill from your passage " + 
	    "through the portal.\n");
}
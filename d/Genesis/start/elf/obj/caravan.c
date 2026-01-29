#include <stdproperties.h>
#include "../stddefs.h"

#pragma save_binary

inherit OBJECT;
inherit STRINGLIB;
inherit MISCLIB;

#define INSIDE SHOREDIR + "inside"

#define LONG \
"It is an old, horse-drawn caravan, such as gypsies and other " + \
  "vagabonds use. However, there is no horse harnessed to it, " + \
  "and the curtains in the windows are drawn.\n" + \
  "It is painted blue-green with pictures of mermaids frolicking " + \
  "below the ocean waves. By the quality of the paintings you can " + \
  "see that the artist was quite attached to the subject.\n" + \
  "The door is ajar, so there is no difficulty to enter.\n" 

#define MERMAID_ITEM ({"mermaid", "mermaids"})
#define MERMAID_DESC "The painted mermaids have an almost lifelike quality.\n"

#define WINDOW_ITEM ({"window", "curtains"})
#define WINDOW_DESC "The pale blue curtains are drawn, and you cannot look in.\n"

#define PAINTINGS_ITEM ({"paintings"})
#define PAINTINGS_DESC "They are beautifully made.\n"

#define DOOR_ITEM ({"door"})
#define DOOR_DESC "Hmm... Looks like someone has stolen the lock from this door.\n"

create_object() 
{
  set_name("caravan");
  set_adj(({"old"}));
  
  set_long(WRAP(LONG));
  
  add_item(PAINTINGS_ITEM, PAINTINGS_DESC);
  add_item(     DOOR_ITEM,      DOOR_DESC);
  add_item(  MERMAID_ITEM,   MERMAID_DESC);
  add_item(   WINDOW_ITEM,    WINDOW_DESC);
  
  add_prop(OBJ_I_WEIGHT,  2000000);
  add_prop(OBJ_I_VOLUME, 32000000);
}

init() 
{
  add_action("do_enter", "enter");
}

do_enter(str) 
{
  if (id(str) || member_array(str, DOOR_ITEM) > -1) {
    load_object(INSIDE);
    
    this_player()->move_living("into the caravan", INSIDE);
    return 1;
  } 

  notify_fail(query_verb() + " what?\n");
  return 0;
}
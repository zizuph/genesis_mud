inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../ctower.h"
#include <macros.h>
#include <stdproperties.h>

void
create_ctower_room()
{
  set_short("Study");
 
  set_long( "This is one of the private studies "+
      "for those that need to digest what they have learned in "+
      "a peaceful, solitary setting.  There is a desk with a chair, "+
      "a fireplace, and an overstuffed chair with an end table.  The "+
      "overall effect is cozy and quite studious.  You consider"+
      " sitting down and relaxing awhile.\n@@passage_desc@@" );
 
  add_item(({"desk"}),  "The desk has some writing "+
      "materials but is otherwise empty.\n" );
 
  add_item(({"end table", "table"}),  "The table "+
      "is here to facilitate reading in the overstuffed chair.\n" );
 
  add_item(({"chair", "overstuffed chair"}),  "The chair at "+
      "the desk looks functional while the overstuffed chair looks "+
      "downright comfortable and inviting.\n" );
 
  add_item(({"fireplace"}),  "The fireplace only earns the "+
      "title of fireplace by the heat emanating from it and the standard "+
      "shape and design.  Instead of wood however, is a "+
      "formation of glowing red crystals and "+
      "you notice an interesting design, a prism by the "+
      "looks of it, on the mantel.\n" );
 
  add_item(({"prism"}), "The prism is a multicolored "+
      "crystal that glows softly.\n");
 
  add_item(({"crystals", "crystal"}),  "The crystals "+
      "are generating both the heat and the light for the room.\n" );
 
  add_exit(CTOWER_ROOM + "hall2", "south");

}

string passage_desc()
{
  return (member_array("passage", query_exit_cmds()) >= 0 ?
      "The fireplace has been pushed aside, revealing a " +
      "hidden passage.\n" : "");
}
   
void close_fireplace()
{
  tell_room(this_object(), "The fireplace quietly moves back into " +
      "place.\n");
  remove_exit("passage");
}

int
push(string str)
{
  string action;

  if (str != "prism" && str != "the prism")
  {
    return 0;
  }
 
  if (member_array("passage", query_exit_cmds()) >= 0)
  {
    action = " does something to the fireplace.\n";
    write("You push the prism.\n");
    close_fireplace();
  }
  else
  {
    action = " does something to the fireplace which quietly moves "+
        "aside, revealing a hidden passage";
    write("You push the prism and the fireplace quietly moves "+
        "aside, revealing a hidden passage.\n");
    add_exit(CTOWER_ROOM + "sroom2", "passage");
  }
 
  say(QCTNAME(this_player()) + action + ".\n");
  return 1;
}
 
int
sit_in(string str)
{
  if (str != "in chair" && str != "in overstuffed chair")
  {   
    return 0;
  }

  write("You decide that the overstuffed chair looks much "+
      "more comfortable and sit down it it.  You feel relaxed "+
      "and perfectly at ease here.\n");
  say(QCTNAME(this_player()) + " sits down in the overstuffed chair.\n");
  return 1;
}

int pull(string str)
{
  if (str == "prism" || str == "the prism")
  {
    write("You try to pull the prism, but nothing happens.\n");
    return 1;
  }

  return 0;
}

void init()
{
  ::init();

  add_action(push, "push");
  add_action(push, "press");
  add_action(push, "move");
  add_action(pull, "pull");
  add_action(sit_in, "sit");
}

void reset_room()
{
  object room;

  if (member_array("passage", query_exit_cmds()) < 0)
  {
    return;
  }

  if (member_array("passage", query_exit_cmds()) >= 0 &&
      (!(room = find_object(CTOWER_ROOM + "sroom2")) ||
      !sizeof(filter(all_inventory(room), interactive))))
  {
    close_fireplace();
  }
}
   

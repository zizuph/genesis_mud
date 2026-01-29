#pragma strict_types
#pragma no_inherit
#pragma no_clone

inherit "/d/Kalad/room_std";

#include "defs.h"
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

#define FOUND_CRACK "_kalad_thanar_raid_crack"

public void
create_room()
{
   set_short("Chasm ledge");
   set_long(
      "This is a small ledge jutting out of the chasm wall, surrounded by " +
      "sheer rock to one side and impenetrable emptiness to the other.\n"
   );
   add_item(
      ({ "wall", "chasm wall", "cracks", "crack" }),
      "The chasm wall seems to be lined with cracks large enough to " +
      "support a climber from the base of the ledge up to the top, though " +
      "they seem to stop at the bottom of the ledge, making it impossible " +
      "to climb further.\n"
   );
   add_item("lever", "@@lever_desc");
   add_exit(PASS+"w21", "up", 0, 5);
   add_prop(OBJ_S_SEARCH_FUN, "search_cracks");
}

public string
search_cracks(object player, string str)
{
   if(player->query_prop(FOUND_CRACK))
   {
      return "You search the cracks and realize that the lever is still there.\n";
   }

   if(player->resolve_task(TASK_DIFFICULT, ({ SS_AWARENESS, SS_FR_TRAP })) <= 0)
   {
      player->add_prop(FOUND_CRACK, 1);
      return "As you search among the cracks, you notice a lever hidden deep " +
         "within the chasm wall.\n";
   }

   return 0;
}

public string
lever_desc()
{
   if(this_player()->query_prop(FOUND_CRACK))
      return "It looks like you could pull it.\n";

   return "You find no lever.\n";
}

public int
push(string str)
{
   if(!this_player()->query_prop(FOUND_CRACK))
      return 0;

   if(str != "lever")
      return notify_fail("Push what?\n");

   return notify_fail("You push the lever but nothing seems to happen.\n");
}

public int
pull(string str)
{
   if(!this_player()->query_prop(FOUND_CRACK))
      return 0;

   if(str != "lever")
      return notify_fail("Pull what?\n");

   write("You pull the lever and suddenly feel yourself being swept " +
      "down through a hole.\n");
   say(QCTNAME(this_player()) + " starts feeling around the " +
      "chasm wall and suddenly disappears!\n");

   this_player()->move_living("M", ROOM+"cave", 1, 0);
   return 1;
}

public void
init()
{
   ::init();
   add_action(pull, "pull");
   add_action(push, "push");
}

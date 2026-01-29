inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <chapel.h>
#include "/d/Emerald/sys/paths.h"

void
create_room()
{
   set_short("Chapel rectory");
   set_long("   A plush carpet absorbs your footsteps as you enter the " +
      "rectory of the chapel. The walls are dark wood panels, adding to " +
      "the somberness of the room. A stained-glass window almost " +
      "completely covers one wall. This room is sparse except for a long " +
      "table set against the wall by the chapel entrance.\n\n");
   
   add_item(({"door", "doors"}), "The chapel doors are made of a " +
      "highly polished wood. The door handles appear to be crafted  " +
      "from pure crystal.\n");
   add_item(({"window", "glass", "stained glass"}), "The stained glass window "+
      "is brilliantly coloured and depicts a scene of the flora and fauna of the area. The "+
      "window is so large it almost completely covers the wall.\n");
   add_item(({"wall","walls"}),"The walls are made of dark wooden panels.\n");
   add_item("table","This is a long table. On the table is a book and many bowls of rice. Perhaps you can look at the book.\n");
   add_item(({"bowl","bowels"}),"You can see many crystal bowls filled with rice.\n");
   add_item("book","You see that this is a guest list book. But unfortunately the signatures are not much more than a few scrawls and are unreadable.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(CHAPEL_DIR + "outside", "south", "@@go_outside@@");
   add_exit(CHAPEL_DIR + "chapel", "north");
   add_exit(CHAPEL_DIR + "jewelers", "west");
   add_exit(CHAPEL_DIR + "shop", "east");
}

void
leave_inv(object ob, object to)
{
   object bowl;
   
   ::leave_inv(ob, to);
   if (!ob || !living(ob))
      return;
   if (ob->query_prop(IS_BRIDE) || ob->query_prop(IS_GROOM) ||
         ob->query_prop(JUST_MARRIED))
   return;
   if (!to || MASTER_OB(to) == CHAPEL_DIR + "outside") {
      bowl = present("wedding_bowl", ob);
      if (bowl) {
         bowl->remove_object();
         ob->catch_msg("As you leave the chapel, the rice " +
            "bowl dissipates.\n");
       }
   }
   if (!to || MASTER_OB(to) == CHAPEL_DIR + "chapel") {
      bowl = present("wedding_bowl", ob);
      if (bowl)
         return;
      bowl = clone_object(CHAPEL_DIR + "obj/bowl");
      if (bowl->move(ob))
         bowl->remove_object();
      else
        ob->catch_msg("You are given a bowl of rice ...\n\n");
   }
}

int
go_outside()
{
   write("As you step up to the doors, they magically open.\n");
   write("After you have passed, they silently close.\n");
   return 0;
}

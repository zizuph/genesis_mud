inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define START  "/d/Terel/mecien/valley/ledge"
#define VALLEY "/d/Terel/mecien/valley/"
#define TP this_player()


object guardian;

protect(object who){
   if(present("protector_ring", who)) set_alarm(3.0, -1.0, "evil", who);
}

evil(object who){
   guardian->command("roar");
   who->catch_msg("An image of a winged lion appears roaring in your mind.\n");
   set_alarm(2.0, -1.0, "hot_ring", who);
}

hot_ring(object who){
  who->catch_msg("Your ancient gold ring suddenly grows very hot!\n");
}


public void
reset_room()
{
   if (guardian) return;
   guardian = clone_object(VALLEY + "guardian");
   guardian->move(this_object());
   
}

public int
do_enter(string str)
{
   notify_fail("Enter what?\n");
   if (str != "mist") return 0;
   
   if(present(guardian)){
      if(TP->query_alignment() < 0) map(users(), protect);
   }
   this_player()->move_living("into the mist", START);
   return 1;
}

public void
init()
{
   ::init();
   add_action(do_enter, "enter");
}

public void
create_room()
{
   set_short("Entrance");
   set_long("Mists and shadows abound everywhere. The air is still, " +
      "haunted by by looming ice mountains to the south. Nothing " +
      "can be seen through the mists, yet they weave patterns, " +
      "like souls from beyond, beckoning their weary welcome to " +
      "those that would join them.\n");
   
   add_exit("/d/Terel/mecien/mountains/tunnel3", "south", 0);
   
   add_item(({"mist","cloud"}), "The mist seems to call you.\n");
   
   reset_room();
}

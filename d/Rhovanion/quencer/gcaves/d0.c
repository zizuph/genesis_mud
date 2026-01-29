/* goblin caves */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"


create_room()
{
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_INSIDE, 1);

    set_short("goblin prison");
    set_long("This room is dark and it smells bad. Somehow you can guess "+
             "that this is the place where goblins keep their prisoners. "+
             "To the west is door that leads back to the tunnels. Maybe "+
             "you should leave immediately if you don't want to stay "+
             "here forever. There is a big noise coming from north and "+
             "prison continues to the east.\n");

  add_item("door", "This is the other side of the secret door. Goblins "+
                   "haven't even tried to hide it from this side. So you "+
                   "can simply push it to get through.\n");
  add_item(({"wall","walls"}),BS("These walls seems to be natural. But "+
              "then again you have seen so many strange things in these "+
              "caves that you are not sure with anything you see or feel.\n"));

  add_exit(CAVE_DIR+"d1", "north");
  add_exit(CAVE_DIR+"d2", "east");
}

init()
{
    ::init();
    add_action("push_something", "push");
}

push_something(something)
{
  if(something=="door")
  {
    TP->catch_msg("You open the door and pass quickly; the wall swings "+
                  "back, closing the small opening.\n");
    say(QCTNAME(TP)+" opens the door and disappears inside. The wall swings "+
        "back closing the small opening.\n");
          tell_room(CAVE_DIR+"t17",QCTNAME(TP)+" enters the room through "+
                                           "a secret door.\n");
    TP->move_living("M",CAVE_DIR+"t17");
          return 1;
   }
 return 0;
}

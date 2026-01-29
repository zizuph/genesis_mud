/* goblin caves */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define CAVE_DIR              MISTY_DIR + "gcaves/"
#define PASSWD_TO_THIS_PLACE  "_passwd_to_this_place"


create_room()
{
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_INSIDE, 1);

    set_short("treasure chamber");
    set_long("This is treasure chamber of goblin lord. It is very quiet "+
             "here and very odd thing is "+
             "that there is no treasure here. You would bet your life "+
             "that goblin lord has some treasure somewhere. Maybe it "+
             "is somewhere else.\n");

  add_item(({"wall","walls"}),BS("These walls seems to be natural. But "+
              "then again you have seen so many strange things in these "+
              "caves that you are not sure with anythink you see or feel.\n"));

   add_exit(CAVE_DIR+"d10", "west");
}

init()
{
    ::init();
    add_action("shout_name", "shout");
}

int
shout_name(string something)
{
  if(something == (TP->query_prop(PASSWD_TO_THIS_PLACE)))
  {
    TP->catch_msg("You take deep breath and shout: "+something+
                  "\nStrangely all sound is absorbed by eastern "+
                  "wall.\nAfter the sound wall absorbs you too!\n");
    say(QCTNAME(TP)+" takes deep breath and shouts something. You can't "+
        "tell what it was because the eastern wall absorbs the sound.\n"+
        "Ooops!!! The wall absorbs "+QTNAME(TP)+" too!\n");
    tell_room(CAVE_DIR+"d12","The western wall starts to emit something. "+
                             "Suddenly "+QTNAME(TP)+" is standing here.\n");
    TP->move_living("M",CAVE_DIR+"d12", 1);
    return 1;
   }
  TP->catch_msg("You take deep breath and shout: "+something+"\n"+
                "Strangely all sound is absorbed by eastern wall.\n");
  say(QCTNAME(TP)+" takes a deep breath and shouts something. You can't "+
      "tell what it was because eastern wall absorbs all sound.\n");
  return 1;
}

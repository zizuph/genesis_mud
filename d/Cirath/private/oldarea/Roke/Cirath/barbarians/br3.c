inherit "/std/room";

#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"

void create_room()
{
  set_short("Road in Barbarian Camp");
  set_long(break_string("You're on a sand road close to the middle of "+
           "the camp. You can see many tents around you and a large "+
           "house to your south. The house is for the elders who work "+
           "there. A large entrance (propably because the barbarians are "+
           "large) to the south leads into the building. West there is a "+
           "crossroad.\n",60));

  add_item((("tents")),"The tents are quite big./n");
  add_item((("tent")),"There's a lot of them you know...\n");
  add_item((("dust")),"The wind is whirling it up from the ground.\n");
  add_item((("sand")),"Of course it's sand in a desert, what did you think?\n");
  add_item(({"path","paths"}),"They are well-travelled...\n");
  add_item((("camp")),"You're standing in it...The mighty Barbarian Camp!\n");
  add_item("entrance","There is no...\n");
  add_item("crossroad","It's west of you, in the middle of the camp.\n");
  add_item("house","The house is large and made of stone.\n");

  add_exit(BARBARIANS+"br4","east");
  add_exit(BARBARIANS+"bcr","west");
  add_exit(BARBARIANS+"be1","south");
}


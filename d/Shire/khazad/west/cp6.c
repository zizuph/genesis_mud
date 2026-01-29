
inherit "/d/Shire/khazad/moria_room_drip";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Cavern road\n"+
     "There are two obvious exits: west, east");
  set_long("Large stalactites crowd the cavern ceiling, occasionaly "+
     "dripping water in places. Stalagmites likewise cover the floor "+
     "except for a wide, flat road raised on a bed of dirt and rock "+
     "cutting its way through the center of the cavern. Wet moss, "+
     "covering a great portion of the walls, glistens in the light. "+
     "The cavern turns here and continues off to the northeast. "+
     "The cavern road runs off to the west and stops to the east "+
     "before a long, jagged cleft in the eastern wall.\n"+
     "There are two obvious exits: west, east.\n");

  add_item(({ "eastern wall", "opening", "cleft" }),
     "It narrows as it runs up the side of the eastern wall. "+
     "The opening at the base of the cleft is large enough to enter "+
     "into. Moss grows heavily in the cleft and partially covers the "+
     "opening at its base.\n");
  add_item(({ "stalactites", "stalactite" }),
     "From this distance its hard to tell their exact size. Most "+
     "seem fairly large and have water streaking down their sides "+
     "from time to time.\n");
  add_item(({ "stalagmites", "stalagmite" }),
     "Some are small stumps while others tower above you. Traces "+
     "of water can be seen on most.\n");
  add_item("stumps", "@@stumps");
  add_item("ravine",
     "While fairly shallow it offers a clear path through the "+
     "stalagmites.\n");
  add_item(({ "ceiling", "roof" }),
     "It's nearly covered with stalactites.\n");
  add_item(({ "water", "drops" }),
     "Occasionally you see a small drop of water fall from above.\n");
  add_item(({ "floor", "ground" }),
     "It's covered with stalagmites except for the path of the "+
     "cavern road. In some places the ground is slick from the "+
     "water.\n");
  add_item(({ "road", "path", "cavern road", "flat road" }),
     "It's elevated a few feet above the cavern floor by a bed of "+
     "rock and dirt. It appears to be in good condition for "+
     "travelling on.\n");
  add_item(({ "wet moss", "moss" }),
     "Covering the cavern walls, it has a translucent greenish appearance "+
     "and glistens in the light.\n");
  add_item(({ "walls", "wall" }),
     "They slope outwards from the ceiling down and have moss hanging "+
     "from them.\n");
  add_exit("/d/Shire/khazad/west/cp5","west",0,1);
  add_exit("/d/Shire/khazad/west/wd1","east",0,1);
  add_exit("/d/Shire/khazad/west/ravine1","northeast","@@check_prop@@");
  set_noshow_obvious(1);
}

int
check_prop()
{
   if(!TP->query_prop("_i_have_examined_stumps"))
   {
    write("There is no obvious exit northeast.\n");
    return 1;
    }
}

string
stumps()
{
   TP->add_prop("_i_have_examined_stumps",1);
   write("As you move to the side of the road for a better view of the smaller "+
     "stalagmites you notice a shallow ravine running to the northeast "+
     "behind the larger stalagmites.\n");
    return "";  //String functions always return a string var.
}


public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if(!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/ravine1")
  {
    ob->catch_msg("You carefully climb out of the slick ravine.\n");
    TP->remove_prop("_i_have_examined_stumps");
  }
  else if (file_name(from) == "/d/Shire/khazad/west/wd1")
    ob->catch_msg("Moving the wet moss aside you leave the dark "+
      "cleft.\n");
}

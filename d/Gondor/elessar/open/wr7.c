inherit "/d/Gondor/elessar/lib/field";
#include "/sys/macros.h"
#include "/sys/ss_types.h"

create_room()
{
  areadesc = "dark, gloomy forest";
  areatype = 8;
  area = "southwestern";
  areaname = "Anorien";
  land = "Gondor";
  grass = "dark green grass among the trees";
  extraline = "You are inside the Druedain Forest, a gloomy place with "+
  "tall trees. This is said to be where the Druedain live, a strange tribe "+
  "of wild men still living in the stone-age. The Rohirrim have not been "+
  "particularly friendly to the Druedain, so you'd better beware. The road "+
  "continues east and west. There seems to be a track of some kind "+
  "going south through the forest here.";
  add_exit("/d/Gondor/anorien/road/wr8","west",0);
  add_exit("/d/Gondor/anorien/road/wr6","east",0);
  add_item("forest","@@exa_forest");
  add_item("track","@@exa_track");
  make_the_room();
}

init() {
  ::init();
  add_action("try_south","s");
  add_action("try_south","south");
}

try_south() {
  if (this_player()->query_skill(107) > 5) {
    write("You find the beginning of an old track, which you follow south.\n");
    say(QCTNAME(this_player())+" disappears south in the forest.\n",this_player());
    this_player()->move_living("south","/d/Gondor/anorien/druedain/oldroad1");
    this_player()->init_command("look");
    return 1;
    }
  write("You don't dare to enter the Druedain Forest, being so unskilled in\n"+
"tracking and location sense. You might get lost!\n");
  return 1;
}

exa_forest() {
  if (this_player()->query_skill(107) > 5) return "Looking at the forest, your skilled eyes suddenly discover an old\n"+
"track leading through the forest south of here!\n";
  return "You study the forest to see if you can catch a glimpse of one\n"+
    "of the legendary Druedain, but see nothing. The grey trees of\n"+
    "the Druedain Forest reveals nothing of interest to you.\n";
}

exa_track() {
if (this_player()->query_skill(107) > 5) return "There's an old, hidden track running south through the forest!\n"+
    "Maybe you can find something interesting if you follow it?\n";
  return "The only track you see, is the old West Road which you are standing on.\n";
}


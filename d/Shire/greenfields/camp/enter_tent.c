inherit "/d/Shire/greenfields/camp/camp";
#include <macros.h>
#include "/d/Shire/common/defs.h"

string tent_name;


init()
{
  ::init();
  add_action("enter_tent","enter");
}


void set_tent_name(string str)
{
  tent_name = str;
}


int enter_tent(string str)
{
  notify_fail("Enter what?\n");
  if(!str) return 0;
  if(str != "tent") return 0;
  if(TP->query_race_name() != "orc" && present("_orcmaker_orc") 
    && CAN_SEE(find_object("_orcmaker_orc"),this_player()))
  {
    write("The orc blocks the way into the tent.\n");
    say(QCTNAME(this_player())+" is stopped from entering the tent "+
      "by the orc.\n");
    return 1;
  }
/*
  write("You step through the unguarded flap and into the tent.\n");
  say(QCTNAME(this_player())+" enters the tent.\n");
*/
  set_dircmd(str);
  (GREEN_DIR + "camp/" + tent_name)->load_me();
  this_player()->move_living("into the tent through the unguarded flap",
    GREEN_DIR + "camp/" + tent_name);
  return 1;
}

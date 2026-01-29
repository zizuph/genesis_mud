/*
 * Base file for Bree Orc entering tents
 * Based on the Greenfields orc camp tent file
 * By Finwe, July 2000
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit CAMP_BASE;

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
  (CAMP_DIR + tent_name)->load_me();
  this_player()->move_living("into the tent through the unguarded flap",
    CAMP_DIR + tent_name);
  return 1;
}

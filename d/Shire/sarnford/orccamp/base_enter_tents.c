/*
 * Base file for Bree Orc entering tents
 * Based on the Greenfields orc camp tent file
 * By Finwe, July 2000
 *
 * 2000/08/10 Last update
 * 2011/07/25 Lavellan - Improved entry message.
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
  if(TP->query_race_name() != "orc" && present("_warning_orc") 
    && CAN_SEE(find_object("_warning_orc"),this_player()))

//      if(present("orc"))
    {
	write("An orc prevents you fron entering the tent.\n");
    say(QCTNAME(this_player())+" tries to enter the tent but is " +
        "blocked by an orc.\n");
	return 1;
    }
/*
  write("You step through the unguarded flap and into the tent.\n");
  say(QCTNAME(this_player())+" enters the tent.\n");
*/
  set_dircmd(str);
  (CAMP_DIR + tent_name)->load_me();
//  this_player()->move_living("enters the tent through the unguarded flap",
  this_player()->move_living("into the tent through the unguarded flap",
    CAMP_DIR + tent_name);
  return 1;
}

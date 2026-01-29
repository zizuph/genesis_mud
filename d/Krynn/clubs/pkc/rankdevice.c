/*  created by Aridor  12/07/93 
    This is the club ranking device.
    It displays the ranking list of the clubmembers according to
    their logintimes and alignment. (see clubmaster.c for the 
    calculations.)
*/

inherit  "/std/object";


#include "clubdefs.h"
#include <macros.h>
#include <stdproperties.h>
#define MORE_OBJ "/std/board/board_more"

create_object()
{
  add_name("poster");
  set_name("surface");
  add_name("board");
  add_name("display");
  add_name("ranking device");
  set_adj("strange");
  set_adj("plain");
  set_long("@@my_long");
  set_short("plain surface on the wall");
  add_item(({"device","box"}),
	   "It's a small black box of unknown origin, but " +
	   "you have the feeling the device records your activities. " + 
	   "Whenever you are logged in, this device is very happy about " +
	   "it. If you don't log in for too long, you may find " +
	   "yourself expelled from the club.\n");

  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_I_WEIGHT, 10000);
  add_prop(OBJ_I_VOLUME, 50000);
  add_prop(OBJ_M_NO_GET, "The plain surface is securely fastened to the wall.\n");
  
}


my_long()
{
  string str = (CLUBMASTER)->get_ranking_list_display();
  str = BS("This plain surface looks much like a poster but it has some very special abilities. " +
	    "At the bottom you can see a small device. On the poster " +
	    "you can read the following lines:",SL) + str + "\n* means Supporter is currently active.\n";
  clone_object(MORE_OBJ)->more(str);
  return "";
}



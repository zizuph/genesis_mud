/* This object maintains the sponsor tree of the knights.
 * Eventually it'll be updated automatically.
 *
 * Aridor 09/95
 */

inherit "/std/object";

#include "../local.h"
#define STDMORE "/obj/more"

void
create_object()
{
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_name("sponsor tree");
    set_name("tapestry");
    set_no_show_composite(1);
    set_short("tapestry");
    set_long("There are tapestries hanging on every wall, each one " +
	     "an elaborate tree of names worked in gold threads. To " +
	     "learn more about the tapestries, try <read tapestry>.\n");
}

void
init()
{
   ADA("read");
   ::init();
}


int
read(string str)
{
   NF("Read what?\n");
   if (!str)
      return 0;
   
   switch(str)
   {
      case "aaron":
      case "bebop":
      case "blake":
      case "cindy":
      case "dordon":      
      case "faline":
      case "grumph":
      case "gwen":
      case "lunie":
      case "pangu":
      case "rae":
      case "trojan":
      case "tapestry":
      case "tree":
      
	clone_object(STDMORE)->more(read_file(MUSEUM_TREE + str));
	//cat(TREE + str);
      break;
      default:
      NF("You can't read that.\n");
      return 0;
   }
   
   return 1;         
}


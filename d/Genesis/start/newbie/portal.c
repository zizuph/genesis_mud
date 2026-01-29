/*
 * Newbie one-way portal
 * TAPAKAH, 07/2005
 */

#pragma no_shadow
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include "newbie.h"

#define TP  this_player()
#define ENV environment(this_player())

#define LOG_PORTAL "NEWBIE_PORTAL"
#define SPARKLE "/d/Sparkle/area/city/rooms/streets/center_f"

void create_object();
string enter_desc();
void init();
int enter_portal(string str);

void
create_object()
{
  set_name("portal");
  set_adj("shimmering");
  set_short("shimmering portal");
  set_long("An oval shimmering portal hovers in the room. Looking through it "+
	   "you can see vague contours of an ancient church and of a tall "+
	   "marble tower. You also notice people running around minding their "+
	   "businesses without any sense of being watched.\n"+"@@enter_desc@@");

  add_prop(OBJ_I_VALUE,0);
  add_prop(OBJ_I_WEIGHT,20000);
  add_prop(OBJ_I_VOLUME,50000);
  add_prop(OBJ_I_NO_GET,1);
}

string
enter_desc() {

  if(SD_IS_NEWBIE(TP)) {
    return "You feel you can enter it safely.\n";
  }
  else {
    return "You feel you're too big to enter the portal.\n";
  }
}

void
init() {

  ::init();

  add_action(enter_portal,"enter");
}

int
enter_portal(string str) {

  if(str)
    if(str != "portal") {
      notify_fail("Enter what?\n");
      return 0;
    }
  if(SD_IS_NEWBIE(TP)) {
    write("You close your eyes as you enter the shimmering portal.\n"+
	  "As you open them again, you find yourself on a bustling town\n"+
	  "square of Sparkle.\n");
    tell_room(ENV,QCTNAME(TP) + " enters the shimmering portal.\n",TP);
    log_file(LOG_PORTAL, ctime(time()) + " " + TP->query_name() + " from " + file_name(ENV) + "\n");
    TP->move_living("M",SPARKLE);
    write("\nThe portal closes behind you and you can't see any trace of it.\n");
    tell_room(ENV,"A portal opens in the air and " + QNAME(TP) + " steps out of it.\n"+
	      "The portal closes behind " + TP->query_objective() +
          " and you can't see any trace of it.\n",TP);
  }
  else 
    write("You are too big to enter the portal.\n");
  
  return 1;
}

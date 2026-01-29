/*
 * Portal to Faerie from Solace
 * Based on the newbie portal by Tapakah.
 * -- Finwe, November 2005
 */

#pragma no_shadow
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

#define STAT_LIMIT 43 /* apprentice */
#define IS_NEWBIE(x)  ((x)->query_average_stat() < STAT_LIMIT)
#define LOG_PORTAL "/d/Sparkle/area/faerie/logs/portals"
#define GLADE "/d/Sparkle/area/faerie/rooms/forest/glade"
//#define ENV environment(this_player())

void create_object();
string enter_desc();
void init();
int enter_portal(string str);

void
create_object()
{
  set_name("portal");
  set_adj("shimmering");
  set_short("large shimmering portal");
  set_long("A large, shimmering portal. It hangs in the center of the room. Vague shapes of trees surrounding a road can be seen in it. " + "@@enter_desc@@");

  add_prop(OBJ_I_VALUE,0);
  add_prop(OBJ_I_WEIGHT,20000);
  add_prop(OBJ_I_VOLUME,50000);
  add_prop(OBJ_I_NO_GET,1);
}

string
enter_desc() {

  if(IS_NEWBIE(TP)) {
    return "You feel you can safely enter it.\n";
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
enter_portal(string str) 
{

    if(str)
        if(str != "portal") 
        {
            notify_fail("Enter what?\n");
            return 0;
        }
    
    if(IS_NEWBIE(TP)) 
    {
        write("You step into the " + short() + " and suddenly everything " +
            "goes black. A cold feeling washes over you. Within a few " +
            "moments, you realize you're somewhere else.\n\n");
        tell_room(ENV(TP),QCTNAME(TP) + " enters the " + short() + ".\n",TP);
        write_file(LOG_PORTAL,ctime(time()) + " " + TP->query_name() + 
            " from Solace to forest glade\n");
        TP->move_living("M",GLADE);
        write("\nThe " + short() + " wavers then becomes still.\n");
        tell_room(ENV(TP),"The " + short() + "suddenly wavers and " + 
            QCTNAME(TP) + " steps out of it.\n",TP);
    }
    else 
        write("You are too big to enter the portal.\n");
  
  return 1;
}

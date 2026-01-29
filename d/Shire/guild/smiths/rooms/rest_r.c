/*
     The resting room for the smiths guild
     smiths may start here
*/

#pragma save_binary;

inherit "/d/Shire/room";
inherit "/lib/guild_support";

#include "/d/Shire/skills.h"
//#include "/d/Shire/sys/defs.h"
#include <wa_types.h>

/*
 * Sets flag in players from calling dragons into ME.
 * Disabled by request of Admin, June 2001
#include "/d/Gondor/common/lib/gs_include.c"
*/
#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>

#define SLEEPING "_live_i_sleep"


void
create_room() {
   set_short("Resting room in the Blacksmiths Guild");
   set_long("Except for a single candle on a table this room is " +
        "dark and mostly quiet. Real beds and the shape of the " +
        "room is round after the manners of hobbits to make " +
        "everyone feel safe here. The room is used by smiths " +
        "who may rest here if they wish. If you wish this to " +
        "be your starting place, you may <start here>.\n");

   add_item("beds","They are nice soft beds with thick mattresses.\n");
   add_item("candle","It is a white candle made from beeswax.\n");
   add_item("table","This nice table is made from solid oak. It has nice"+
      " carvings and is most likely of dwarvish origin.\n");

   add_exit(SMITHSDIR_ROOMS+"improve","southwest","@@test_exit@@");
   add_exit(SMITHSDIR_ROOMS+"discus","southeast","@@test_start@@");

   add_prop(ROOM_I_INSIDE,1);

    // safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

}

init() {
   ::init();
   add_action("catch_cmd","",1);
   add_action("start","start");
   add_action("sleep","sleep");
   add_action("wake","wake");
}

int
start(string str) {
   if (str!="here")
      write("Start where?\n");
   else {
      write("Okay, from now on you will start here.\n");
      TP->set_default_start_location(file_name(TO));
   }
   return 1;
}

int
sleep() {
   if (TP->query_prop(SLEEPING)) {
      write("You are already fast asleap.\n");
      return 1;
   }
   write("You decide to take a nap.\n");
   say(QCTNAME(TP)+" decides to take a nap.\n");
   TP->add_prop(SLEEPING,1);
   return 1;
}

int
wake() {
   if (TP->query_prop(SLEEPING)) {
      write("You wake up.\n");
      say(QCTNAME(TP)+" suddenly wakes up.\n");
      TP->remove_prop(SLEEPING);
      return 1;
   }
   write("But you are not sleeping!\n");
   return 1;
}

int
catch_cmd() {
   if (TP->query_prop(SLEEPING)) {
      write("You are too tired to do anything.\n");
      return 1;
   }
   return 0;   
}

int
test_exit() 
{
    seteuid(getuid());
    if (!IS_MEMBER(TP) && !TP->query_wiz_level()) 
    {
        write("Only smiths are allowed to go there.\n");
        return 1;
    }
    return 0;
}

/* Fix bug where non members were able to start here after 
 * leaving guild.
 */

int test_start() 
{
    seteuid(getuid());
    if (!IS_MEMBER(TP)) 
    {
        TP->set_default_start_location(TP->query_def_start());
        return 0;
    }
    return 0;
}

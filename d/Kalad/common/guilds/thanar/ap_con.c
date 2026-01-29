/* 
 * /d/Kalad/common/guilds/thanar/ap_con.c
 * Purpose    : This file does the speak functions for the Thanar ghost.
 * Located    : <called into being by the player>
 * Created By : Sarr 
 * Modified By: Rico 26.Mar.97; general clean up of code, basically 
 */ 

inherit "/std/object";

#include "/d/Kalad/defs.h"

#define THANAR_TALK   "_thanar_talk"
#define LOG_FILE      "apparition"

object thanar;   /* the apparition of Thanar */

void
set_thanar(object ob)
{
   thanar = ob;
}

void
create_object()
{
   set_name("controller");
   set_long("controller.");

   set_no_show();

   add_prop(OBJ_M_NO_DROP, 1);
}

void
init()
{
   ::init();

   add_action("do_speak", "thsay");
}

int
do_speak(string str)
{
   notify_fail("\nMake the " + thanar->short() + " say what?\n\n");

   if(!str)
      return 0;

   tell_room(E(thanar), "\nThe " + thanar->short() + 
      " thunders: " + str + "\n\n");

   /* added a log-file to see if they make the apparition talk
      nonsense or use it as intended - for roleplaying          */
   log_file(LOG_FILE, extract(ctime(time()), 4, 15) + " " +
      capitalize(this_player()->query_real_name()) + " said: "+
      str + "\n");

    return 1;
}


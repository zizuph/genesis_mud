/* Kirk of Port City - Library base room
**
** History:
** Date        Coder       Action
**----------   ----------- ------------------------------------------
** 4/10/98     Zima        Created - support for library book reading
**
*/
inherit  "/d/Khalakhor/std/room";
#include "/sys/ss_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
string*  pclist=({});    // list of parse_command patterns 
string*  fnlist=({});    // file names corresponding to patterns
int      min_read_skill; // minimum skill required for read;
int      guild_only;     // guild member only?
 
//
// create_khalakhor_room
//
void create_khalakhor_room() {
   set_short("Library base room");
   set_long("   This is the library base room");
   INSIDE;
}
 
//
// set_book_list - set the list of titles and corresp. parse_command patterns
//
void init_library(string* pcl, string* fnl, int min, int gm_only) {
   pclist         = pcl;
   fnlist         = fnl;
   min_read_skill = min;
   guild_only     = gm_only;
}
 
//
// allowed_to_read - is this player allowed to read here?
//
int allowed_to_read(object tp) {
   //limit to guild members of certain levels
   //TO BE COMPLETED LATER
   return 1;
}
 
//
// do_read - allows player to read a book, if he can
//
int do_read(string parms) {
   string fname="?";
   int    i=0;
 
   // check if player specifies something on the shelf
   notify_fail("Read what? titles?\n");
   if (!(stringp(parms))) return 0;
   while ((i<sizeof(pclist)) && (fname=="?")) {
      if (parse_command(lower_case(parms),({(all_inventory(TP))}),pclist[i]))
         fname=fnlist[i];
      else
         i++;
   }
   if (fname=="?")
      write("Read what? titles?\n");
   else if (TP->query_skill(SS_LANGUAGE) <= min_read_skill)
      write("You are unable to understand the cryptic writing.\n");
   else if (!allowed_to_read(TP))
      write("The enchanted writings blur your vision when you attempt to "+
            "read them.\n");
   else
      TP->more(read_file(SR_SCRIPT+fname+".txt"));
   return 1;
}
 
//
// init - add the read command
//
void init() {
   ::init();
   add_action(&do_read(),"read");
}

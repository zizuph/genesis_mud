/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#define NO_WHERE 0
#define IDLE     0
object chariot_room;
int chariot_signaled;
object pole;
 
void signal_chariot() { return; }
void logerr(string P) { return; }
/*
** CHECK_WAITING: called by chariot room at end of trip to see if more
**                people are now waiting for the chariot
*/
void check_waiting() {
   int location;
   int chstatus;
   location=(chariot_room->query_location());
   chstatus=(chariot_room->query_status());
   if ((location!=NO_WHERE)||(chstatus!=IDLE)) {
      logerr("depot.inc(check_waiting): called when not idle");
      return;
   }
   if ((pole->query_raised())&&(!(chariot_signaled))) signal_chariot();
}
 
void create_room() {
   set_short("Test");
   set_long("A test room");
}

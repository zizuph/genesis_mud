/* Kirk of Port City - Sanctuary
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/5/97      Zima        Created
** 7/20/98     Zima        Added support for lying prostrate
**
*/
/* inherits/includes */
#include "defs.h"
inherit  ROOM+"ksanct";
inherit  SR_ROOM+"kneelrm";
 
object cathair;
 
/* room definition */
void create_khalakhor_room() {
   set_short("Sanctuary of the kirk");
   set_long(
      "   You are on the north end of the sanctuary, at the entrance of the "+
      "great apse of the kirk which houses the towering statue of "+
      "the angel. The divine guardian gazes out over the sanctuary in a "+
      "protective stare, a motionless sentry which seems so life-like "+
      "that you expect it to step out of the apse on top of you. The "+
      "high altar of the kirk is just to the south, light from the "+
      "stained glass windows and the candles of the chandeliers "+
      "illuminating it and the entire sanctuary. A large rounded arch "+
      "borders the face of the apse, where an inscription is written "+
      "with large letters.\n");
 
   setup_ksanct();
 
   add_item(({"apse","arch"}),
      "The apse is an extension on the north end of the sanctuary. It "+
      "is constructued in the form of a large domed cylinder cut in "+
      "half. A large rounded arch borders the face of the apse, an "+
      "inscription sculpted along its top. Murals and symbols are painted "+
      "on its rounded walls in vibrant colors, between pillars which rise "+
      "up around its circumference to support its half-domed ceiling. You "+
      "could get a better look if you walked up into it to the north.\n");
   add_item(({"murals","symbols"}),
      "Painted on the walls of the apse, you could see them in more "+
      "detail if you stepped up into the apse to the north.\n");
   add_item("pillars",
      "They are set along the circumference of the apse.\n");
   add_item(({"angel","statue"}),
      "The statue stands inside the apse to the north, gazing out over "+
      "the sanctuary. You could get more detail if you stepped up into "+
      "the apse itself to the north.\n");
   add_item("inscription",
      "It is sculpted along the round top of the arch over the entrance "+
      "to the apse.\n");
   add_cmd_item("inscription","read",
   "MAIGHAL THE ARCHANGEL THE HIGH SERVANT OF ARDAUGH.\n");
 
   add_exit("kapse",   "north",  "@@check_kneeling");
   add_exit("ksanct5", "south",  "@@check_kneeling");
   add_exit("ksanct9", "east", "@@check_kneeling");
   add_exit("ksanct7", "west", "@@check_kneeling");
   cathair=clone_object(OBJ+"cathair");
   cathair->move(this_object());
   kneel_before = "the cathair";
}

//
// init - add prostrate command
//
void init()
{
   ::init();
   add_action(&kneel(),"prostrate");
   add_action(&kneel(),"lie");
}

/*
**  ARGOS  - Temple of Dephonia, Entrance foyer
**
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/95    Created
**
*/
 
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
   set_short("Foyer of the Temple of Dephonia");
   set_long(break_string(
      "You hesitantly enter the foyer of the Temple of Dephonia, a " +
      "diamond-shaped chamber of black marble filled with a forboding " +
      "aura of evil. A statue of the goddess herself, towering high " +
      "above your head, sits atop a pedestal of intricately engraved " +
      "inlaid silver, a sight away from which you fear to draw your " +
      "eyes. To the south an arched entrance leads further into " +
      "the temple, while a pair of tall silver doors stands open to " +
      "the north leading onto the portico.\n",70));
 
    add_prop(ROOM_I_INSIDE,1);
    add_item("statue", break_string(
       "Towering high above your head, this is a statue of Dephonia the " +
       "goddess of the Light of Darkness. She is portrayed as a beautiful "
       + "young woman " +
       "with an inviting yet mysteriously evil smile.  She has very " +
       "long hair, crowned with what seems to be a serpent, and is " +
       "wearing a long flowing tunic. Crafted at the foot of the " +
       "statue is a perched raven, its eyes seeming to stare right " +
       "through you.\n",70));
    add_item("raven", "It is part of the statue.\n");
 
    add_item("pedestal", break_string(
       "A large diamond-shaped block of black marble, embellished " +
       "with inlaid silver intricately engraved with mysterious " +
       "runes.  There is an inscription on the pedestal.\n",70));
    add_item("inscription", "It is carved into the pedestal.\n");
    add_cmd_item("inscription","read", "PRAISED BE THE LIGHT OF DARKNESS.\n");
    add_item("runes", break_string(
       "They are engraved into the silver of the pedestal. " +
       "You do not understand them.\n",70));
 
    add_item(({"arch","entrance"}), break_string(
       "An arched doorway, inlaid with silver, leads south " +
       "further into the temple.\n",70));
 
    add_item("doors", break_string(
       "Tall silver doors, twice your heighth, each engraved with a " +
       "raven spreading his wings, as if to ward off any intruders.\n",70));
    add_cmd_item("doors",({"close","shut"}), "The doors can not be shut.\n");
 
    add_exit(ROOM_DIR+"portico","north", 0);
    add_exit(ROOM_DIR+"corr11","south",0);  /* change 0 to @@log_visit */
}
 
int log_visit() {
      object ob=this_player();
      log_file("deph_enter",(ob->query_name())+" visited at "+
               ctime(time())+".\n");
      return 0;
}

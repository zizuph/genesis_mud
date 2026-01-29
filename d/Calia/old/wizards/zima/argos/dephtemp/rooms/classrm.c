/*
**  Temple of Dephonia - Class room for childern and Novice Priests
**
** The inscription on the sash is the Second prayer needed by some players
**     to finish the vision quest.
** The plaque gives the greek letters in order so that the player can
**     know the order to read the quest tomes (they are titled "Alpha
**     tome", "Beta tome", etc.
** The Beta (second) tome of the Vision Quest is found on the podium
**     here.
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
#include <ss_types.h>
#include "defs.h"
#include "vqscenes.h";
#define SceneNum   2
#define LANG_LEVEL 10
int tome_here=1; /* tome is present when loaded */
 
void return_object(int ObjNum) {
   tome_here=1;
}
 
create_room() {
   set_short("The Lecture Chamber of the Temple of Dephonia");
   set_long(
      "You walk into a well-lighted rectangular chamber which runs " +
      "from the northeast to the southwest. Small mats are scattered " +
      "on the floor while a podium stands near the short southwestern " +
      "wall. A large tapestry hangs on the rear wall, while a large " +
      "plaque is placed near the doorway to the chamber which leads " +
      "east into the corridor.\n");
 
    add_prop(ROOM_I_INSIDE,1);
 
    add_item("mats",break_string(
       "Woven of dried reeds, these mats are scattered across the " +
       "floor of the chamber, upon which eager listeners sit as "   +
       "the wisdom of the Order is imparted to them.\n",70));
    add_item("podium","@@exa_podium");
    add_item("tome","@@exa_tome");
    add_cmd_item("tome","read","@@read_tome");
    add_item("tome from podium","What?\n");
    add_cmd_item("tome from podium",({"take","get"}),"@@take_tome");
    add_cmd_item("tome","take","Take tome from what?\n");
    add_cmd_item("tome","get", "Get tome from what?\n");
    add_item("tapestry",
       "This rather old weaving of wool and silk portrays "+
       vq_scene[SceneNum]+". There is an inscription sewn into a long "+
       "sash which is draped from the top of the tapestry.\n");
    add_item("sash",break_string(
       "A long sash of red silk, it is embroidered with an " +
       "inscription.\n",70));
    add_item("inscription",
       "It is sewn into the sash. Perhaps you can read it.\n");
    add_cmd_item("inscription","read", /* translate to greek later */
       "The inscription reads: "+vq_prayer[SceneNum]+".\n");
    add_item("plaque",break_string(
       "The plaque is covered in strange symbols which seem to be " +
       "letters of the alphabet. You wonder if you can read them.\n",70));
 
    add_cmd_item("plaque","read","@@read_plaque");
 
    add_exit(ROOM_DIR+"corr11","east",0);
}
 
int read_plaque() {
    if (this_player()->query_skill(SS_LANGUAGE) < LANG_LEVEL)
       write("You don't understand the ancient writing.\n") ;
    else
       write(break_string("The plaque lists in order the letters of the " +
       "ancient alphabet " +
       "used in the ancient writings in this area. The letters are titled: " +
       "Alpha, Beta, Gamma, Delta, Epsilon, Zeta, Eta, Theta, Iota, Kappa, " +
       "Lambda, Mu, Nu, Xi, Omicron, Pi, Rho, Sigma, Tau, Upsilon, Phi, "    +
       "Chi, Psi, Omega.\n",70));
   return 1;
}
 
string exa_podium() {
   string desc= ("The podium is carved of dark mohagany and carved with " +
                "intricate details. You wonder at the mysteries which "  +
                "have been spoken by those who have stood behind this "  +
                "symbol of wisdom.");
   if (tome_here) desc=desc+" You notice a tome laying on top.\n";
   else           desc=desc+".\n";
   return desc;
}
 
string exa_tome() {
   if (tome_here)
       return "It is laying on top of the podium in plain view.\n";
    else
       return "You find no tome here.\n";
}
 
string read_tome() {
   if (tome_here)
       return "You must take it from the podium to read it.\n";
    else
       return "You find no tome here.\n";
}
 
int take_tome() {
   object tome=0;
   object Thisroom=0;
   if (tome_here) {
      tome=clone_object(OBJ_DIR+"tomeb"); /* Beta tome */
      Thisroom=environment(this_player());
      tome->move(this_player());
      write("You take the tome from the podium.\n");
      tell_room(Thisroom, QCNAME(this_player())+
                " takes the tome from the podium.\n",this_player());
      tome_here=0; /* tome gone now */
      }
   else
      write("You find no tome here.\n");
   return 1;
}

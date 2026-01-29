/* This function included in rooms where there is a statue which is
** NOT part of the toe quest. When player does "rub toe on statue",
** gets a message of "wrong statue". Created because of players
** getting confused and not watching messages properly.
**
** History:
** Date      Coder     Action
** -------- ---------- -------------------------------
** 11/15/95 Zima       Created
*/
#include <macros.h>
 
int rub(string Parms) {
   string *Parm;
 
   if (!(Parms)) { write("Rub what?\n"); return 1; }
   Parm=explode(Parms," ");
 
   if ((member_array("toe",Parm)>-1) && (member_array("statue",Parm)>-1)) {
      write("You rub the toe on the statue but nothing seems to happen.\n");
      write("You notice that this statue seems to have never been rubbed "+
            "before. Perhaps it is not a custom to rub this statue?\n");
      return 1;
   }
   write("Rub what?\n");
   return 1;
}
 
void init() {
   ::init();
   add_action("rub","rub");
}

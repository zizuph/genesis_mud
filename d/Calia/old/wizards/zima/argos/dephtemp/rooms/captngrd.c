/*
**  Temple of Dephonia, Office of the Captain of the Guard
**
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/94    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "vqscenes.h"
#define SCENE_NUM 8
 
object priest=0;
 
void
reset_room()
{
    if (priest) return;
    priest=clone_object(NPC_DIR+"captngrd");
    priest->equip_me();
    priest->move(THIS);
    tell_room(THIS, QCNAME(priest)+" rises from his desk.\n");
}
 
create_room() {
   set_short("Chamber in the Temple of Dephonia");
   set_long(
      "You enter a spartanly furnished rectangular chamber which " +
      "serves as the office of the Captain of the Guard. There is " +
      "a simple but heavy desk which sits in the middle of the room, " +
      "accompanied by a highbacked chair. The only decor is a large " +
      "banner which hangs on the northeastern wall behind the desk, "+
      "and a tapestry on the southeastern. The doorway to the west "+
      "leads back into the corridor.\n");
 
    add_prop(ROOM_I_INSIDE,1);
 
    add_item("desk",
      "It is a short unornate desk made of black pine, nothing " +
      "to capture your attention. There is a note on top of " +
      "the desk.\n");
    add_item("note",
       "It is a note bearing the seal of the Hierophant. Perhaps " +
       "you can read it.\n");
    add_cmd_item("note","read",
       "It says: Leave the temple doors open, we are expecting " +
       "visitors, but arm everyone but the children, and keep " +
       "a special watch.\n");
    add_item("chair",
       "Like the desk, the accompanying chair is simply made of " +
       "black pine with no cushions. It doesn't look very "+
       "comfortable.\n");
    add_item("tapestry",
       "Hanging on the southeastern wall, this ancient tapestry is " +
       "threaded with silk to portray "+vq_scene[SCENE_NUM]+". "+
       "An inscription is " +
       "threaded along the lower edge of the tapestry.\n");
   add_item("inscription",
      "It is threaded on the tapestry. Perhaps you can read it.\n");
   add_cmd_item("inscription","read",
      "It reads: "+vq_prayer[SCENE_NUM]+".\n");
   add_item("banner", break_string(
       "The banner is made of red silk and is embellished with " +
       "a large round shield, emblazoned with a raven encircled " +
       "by a wreath of hemlock, placed over two crossed spears.\n",70));
 
   add_item("doorway","It leads out of the chamber to the west.\n");
 
   add_exit(ROOM_DIR+"corr18","west",0);
   set_alarm(1.0,0.0,"reset_room");
}
 
int CorrectParms(string ParmStr) {
   string *Parm;
   int    i;
   int    FoundPerm=0;
   int    OK=0;
 
   if (!ParmStr) return 0;
   Parm=explode(ParmStr," ");
   for (i=0; i<sizeof(Parm); i++)
      if (Parm[i]=="permission")
         FoundPerm=1;
      else if ((FoundPerm)&&(priest->id(Parm[i])))
         OK=1;
   return OK;
}
 
int request(string ParmStr) {
   object TPlay=this_player();
   object TRoom=this_object();
   object Pass=present(CAPTNSEAL,TPlay);
   string *Parm;
 
   if ((priest)&&(present(priest,TRoom)))
      if ((ParmStr) && (CorrectParms(ParmStr)))
         if (!Pass) {
            Pass = clone_object(OBJ_DIR+"cptnseal");
            write("You cleverly make up a reason why you should be given "+
                  "free passage through the temple and make a convincing "+
                  "case to the Captain of the Guard.\n"+
                  "The Captain of the Guard eyes you suspiciously then "+
                  "hands you a " +
                  "small seal.\n");
            tell_room(TRoom,QCNAME(TPlay)+" tells a convincing tale to the "+
                  "Captain of the Guard.\n" +
                  "The Captain of the Guard eyes " + QTNAME(TPlay) +
                  " suspiciously and hands over a small seal.\n",
                  TPlay);
            Pass->move(TPlay);
            priest->command(
                  "say Mind your business, stranger. I shall be watching.");
            }
         else /* already has pass */
            priest->command("say You already have a pass, fool!");
      else /* invalid or missing parms */
         write("Request what from whom?\n");
   else /* priest not here so ignore command */
      write("What?\n");
   return 1;
}
 
void init() {
   ::init();
   add_action("request","request");
}

/* Kirk of Port City - Apse
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/5/97      Zima        Created
** 5/30/98     Zima        Glorify code added; kneelrm inherited
*/
/* inherits/includes */
#include "defs.h"
inherit  "/d/Khalakhor/std/room";
inherit  SR_ROOM+"kneelrm";
#include <macros.h>
#include <stdproperties.h>
 
object   statue;
int      responding=0; // are we responding?
 
/* room definition */
void create_khalakhor_room() {
   set_short("Apse of the kirk");
   set_long(
      "   You are at standing at the feet of the towering "+
      "statue of the angel which looks out over the sanctuary, in the "+
      "large apse on at the north end. The apse is made like half of a "+
      "domed cylinder, its round wall divided into sections by four "+
      "pillars which rise from the floor to the bottom of the dome. "+
      "Murals are painted on each section of the wall, with one on the "+
      "surface of the half-dome ceiling itself. You can step out of the "+
      "apse into the sanctuary to the south.\n");
   INSIDE;
   add_prop(SR_K1SECURE,1); // secure area
   add_item("sanctuary",
      "It spreads out before you to the south.\n");
   add_item("apse",
      "You are standing in it. It is made constructed in the shape of a "+
      "tall domed cylinder cut in half, appended to the sanctuary's "+
      "north end. It houses the great statue and its circular wall, "+
      "supported by three great pillars, is painted with murals.\n");
   add_item(({"dome","half-dome","ceiling"}),
      "The ceiling of the apse is a half dome, supported by the pillars, "+
      "and painted with a mural. It barely rounds over the head of the "+
      "statue.\n");
   add_item("mural","Which one? the first, second, third or fourth?\n");
   add_item(({"wall","sections"}),
      "The wall of the apse circles around to the north in a semicircle, "+
      "divided into three sections by the pillars. Murals are painted "+
      "on each section, the first, second and third sections.\n");
   add_item("pillars",
      "Four marble pillars rise along the edge of the curved wall, two "+
      "at the face of the apse to the west and east, and two proportioned "+
      "in the center of the wall to the northeast and northwest, dividing "+
      "the wall into its three sections.\n");
   add_item("murals",
      "There are four murals, one painted on each of the three sections "+
      "of the wall and the other on the ceiling. You can look at the murals "+
      "individually, the first through the fourth.\n");
   add_item(({"northwest mural","first mural"}),
      "The mural on the northwest section of the apse portrays the angel "+
      "standing before an elf in a simple brown robe with a white knotted "+
      "rope belt who holds his hand over a book which the angel is "+
      "presenting to him as if taking an oath.\n");
   add_item(({"north mural","second mural"}),
      "The mural on the north section portrays a group of three manachs "+
      "dressed in black robes with white knotted rope belts, the angel "+
      "embracing the group with his large arms from behind them, his wings "+
      "held out protectingly. There is one elven, one human and one dwarven "+
      "manach in the group.\n");
   add_item(({"northeast mural","third mural"}),
      "The mural on the northeast section portrays the angel descending "+
      "from the sky, the toes of one foot on the ground, an angry scowl "+
      "on his face, and his hand held out with his fingers in a claw-like "+
      "manner. Behind him there are three injured manachs on the ground "+
      "crouched in fear, while before him are a group of oncoming "+
      "rampaging goblins, each of which seems to be choking to death "+
      "while in full run, their eyes bulging.\n");
   add_item(({"ceiling mural","mural on ceiling","fourth mural"}),
      "The mural painted on the half-dome ceiling portrays the angel "+
      "sitting on a simple throne, surrounded by heavenly clouds, as "+
      "if he is looking down on his subjects from the sky.\n");
 
   add_exit("ksanct8","south","@@check_kneeling");
   statue=clone_object(SR_OBJ+"kstatue");
   statue->move(TO);
   kneel_before=(statue->short());
}
 
//
// resp_glorify - the response to a correct glorification
//
void
resp_glorify(object tp, object pend, object censor, object cloud, int step)
{
   string sshort=(statue->short()),msg;
 
   if (!(objectp(tp)||objectp(pend)||(ENV(tp)!=TO)||(!kneeling(tp)))) step=0;
 
   switch (step)
      {
      case 1: msg="A gentle breeze rises and begins to whip the "+
                  "clouds of incense about.";                        break;
      case 2: msg="The wind strengthens and the clouds of incense "+
                  "begin to vortex around the "+ sshort+"!";         break;
      case 3: msg="The vortexing cloud of incense is sucked into "+
                  "the floor!";
                  censor->update_desc(1); // extinguish censor
                  cloud->remove_object(); // suck up cloud of incense
                  break;
      case 4: msg="The "+sshort+" seems to come to life!";           break;
      case 5: msg="The Archangel proclaims: Your praises are "+
                  "heard aspirant!";                                 break;
      case 6: msg="The Archangel proclaims: May you always praise "+
                  "Ardaugh and the High Servant!";
                  pend->set_level(3);                                break;
      case 7: msg="The "+sshort+" seems to return to normal.";       break;
      default:msg="The wind ceases and all becomes quiet again.";
              censor->update_desc(3);  //lit
              censor->do_smoke();      //restart smoking
              responding=0;
      }
   tell_room(TO,msg+"\n");
   if (responding)
      set_alarm(7.0,0.0,&resp_glorify(tp,pend,censor,cloud,(step+1)));
}
 
//
// wrong - respond to glorify when something is wrong
//
void wrong(int rc, object tp)
{
   string m;
   switch(rc)
      {
      case 1: m="He who has not glorified the servants of the Servant "+
                "is not heard.";
              break;
      case 2: m="Your praises I have heard, aspirant! Seek the election "+
                "of Ardaugh!";
              break;
      case 3: m="The prayers of praise do not rise before me!"; break;
      case 4: m="Place the prayers of praise before me!";       break;
      case 5: m="The prayers which rise are not pleasing unto me!"; break;
      case 6: m="Humble thyself before me!"; break;
      case 7: m="Thy words are foreign unto me!"; break;
      default:m="Thy praises are lost in a tear in the fabric of space!";
      }
   responding=0;
   tp->catch_msg("You hear a voice in your mind saying:\n"+m+"\n");
}
 
//
// glorify - step in the entrance quest
//
int glorify(string cmd)
{
   object pend   = present(SHAM_PENDANT,TP), // player must have pendant
          censor = present(SR_CENSOR,TO),    // censor must be here
          cloud  = present(SR_INC_CLOUD,TO); // cloud must be here
   int    itype=0, level=-1, rc;             // incense type, aspirant lvl
 
   if (objectp(censor)) itype=(censor->query_inc_type());
   if (objectp(pend))
      level=(pend->query_level());
   else
      return 0; // don't respond to glorifies from non-aspirants
   if (responding) { write("Patience!\n"); return 1; }
   if (!stringp(cmd)) { write("Glorify what?\n"); return 1; }
 
   cmd=lower_case(cmd);
   write("You glorify "+cmd+".\n");
   tell_room(TO,QCTNAME(TP)+" glorifies "+cmd+".\n",TP);
 
   if      (level<2)                     rc=1; // not ready yet
   else if (level>2)                     rc=2; // already done
   else if (!objectp(cloud))             rc=3; // censor not smoking
   else if (!objectp(censor))            rc=4; // censor not on floor
   else if (itype != SR_INC_ASHEN)       rc=5; // wrong incense
   else if (!kneeling(TP))               rc=6; // not kneeling
   else if (cmd != "maighal the archangel the high servant of ardaugh") rc=7;
   else                                  rc=0; // all is OK
 
   if (rc)
      set_alarm(7.0,0.0,&wrong(rc,TP));
   else
      set_alarm(7.0,0.0,&resp_glorify(TP,pend,censor,cloud,1));
   responding=1;
   return 1;
}
 
void init()
{
   ::init();
   add_action(&glorify(),"glorify");
}

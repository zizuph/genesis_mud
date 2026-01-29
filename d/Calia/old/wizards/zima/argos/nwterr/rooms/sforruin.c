/* Satyr Forest, a Newbie area
**
** This is where a newbie can solve the Satyr Quest. All he has to do is
** find the broken leg of the statue here (search underbrush in sfor12.c)
** and give it to the priestly satyr.
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/18/95   Zima          Created
**/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define SATYR_DOM "Calia"
#define SATYR_GROUP 2
#define SATYR_BIT 1
#define SATYR_XP 700
 
object satyr;
void reset_room() {
    if (satyr) return;
    satyr=clone_object(NPC_DIR+"psatyr");
    satyr->equip_me();
    satyr->move(THIS);
    tell_room(THIS, QCNAME(satyr)+" trots into the ruins.\n");
}
 
/* room definition */
void create_room() {
   set_short("Inside a crumbling shrine in a dense forest");
   set_long(
       "You are standing inside the ruins of a forgotten shrine in a "+
       "dense forest, "+
       "a set of twelve crumbling marble pillars set in a circle. A "+
       "statue stands on top of a pedestal in the center of the shrine, "+
       "obviously the object of devotion of this ancient structure. "+
       "Oddly the only invasion of the encroaching woods are the strangling "+
       "vines which wrap around the aging pillars.\n");
 
   add_item(({"ruins","shrine"}),
      "It is made up of a group of twelve crumbling marble pillars "+
      "which encircle the a statue standing on the pedestal. There "+
      "is no roof set on the pillars, and the sunlight beams down "+
      "onto the sacred object the which the ruins house.\n");
   add_item("pillars",
      "Twelve short columns of marble, only a little taller than "+
      "yourself, cracked and crumbling from what must have been "+
      "centuries of abandonment in the forest. Clinging vines grow "+
      "all around the pillars, as if trying to choke this small "+
      "bit of forgotten civilization in the wilderness.\n");
   add_item("vines",
      "Dark green vines with heart-shaped leaves grow wrapped around "+
      "the decaying pillars, as if they intend to choke the life from "+
      "the marble.\n");
   add_item("pedestal",
      "It is a short circular column of white marble, seemingly untouched "+
      "by the forest, though weathered by years of sun and rain. A statue "+
      "stands on top of it.\n");
   add_item("statue",
      "It is a sculpture of a satyr, a mysterious creature with the body "+
      "of a goat and the upper body of a human. It holds a large bowl "+
      "above its head with its human hands, and is reared up on its "+
      "rear goat legs. You notice one of its front legs is broken off, "
      +
      "the only blemish on an otherwise well-kept artwork of devotion.\n");
   add_item("forest",
      "The trees grow all around the edges of the ruins, allowing you "+
      "only one way out to the northwest.\n");
 
 
   /* exits */
   add_exit(ROOM_DIR+"sfor10","northwest",0);
   set_alarm(7.0,0.0,"reset_room");
}
 
int CorrectParm(string StringParm) {
   /* returns 0 if giving leg to satyr, 0 otherwise */
   string *Parm;
   int i;
   int OK=0;
   int legfound=0;
 
   if (!(StringParm)) return 0;
   Parm=explode(StringParm," ");
   for (i=0; i<sizeof(Parm); i++)
      if (lower_case(Parm[i])=="leg")
         legfound=1;
      else if ((lower_case(Parm[i])=="satyr")&&(legfound))
         OK=1;
   return OK;
}
 
int give(string ParmStr) {
   object TPlay=this_player();
   object TRoom=this_object();
   object Leg=present("_satyr_quest_leg",TPlay);
 
   if ((satyr)&&(Leg)&&(present(satyr,TRoom))&&(CorrectParm(ParmStr))) {
      write("You give the marble goat leg to the regal caped satyr.\n");
      tell_room(TRoom,QCNAME(TPlay)+" gives something to the "+
                      QCNAME(satyr)+".\n",TPlay);
      Leg->remove_object();
      if (TPlay->test_bit(SATYR_DOM, SATYR_GROUP, SATYR_BIT)) {
         write("The regal caped satyr glares angrily at you and throws "+
               "the leg into the forest!\n");
         tell_room(TRoom,QCTNAME(satyr)+" glares angrily at "+QCNAME(TPlay)+
                   " and throws the leg into the forest!\n",TPlay);
         }
      else {
         satyr->command("emote jumps happily in the air and cackles.");
         satyr->command("emote goes down on his front legs and bows deeply.");
         satyr->command("emote smiles happily.");
         write("You feel a little more experienced.\n");
         TPlay->set_bit(SATYR_GROUP, SATYR_BIT);
         TPlay->add_exp(SATYR_XP);
         log_file("satyr_quest", TPlay->query_name() +
                  " solved the Satyr Quest."+
                  " EXP="+SATYR_XP+".\n");
      }
      return 1;
   }
   return 0;
}
 
void init() {
   ::init();
   add_action("give","give");
}
void jump_for_joy() {
   if ((satyr)&&(present(satyr,this_object()))) {
      satyr->command("emote jumps for joy!");
      satyr->command("emote holds its hands out in a begging manner.");
      satyr->command("emote bows down on its front legs.");
   }
}
 
void enter_inv(object Entrant, object From) {
   object leg=present("_satyr_quest_leg",Entrant);
   ::enter_inv(Entrant,From);
 
   if ((leg)&&(satyr)) set_alarm(2.0,0.0,"jump_for_joy");
}

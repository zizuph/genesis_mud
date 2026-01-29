

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "defs.h"
#include "combat.h"

#define NUM             sizeof(query_money_types(-1))
#define CLOSED          0       /* 1 = closed,   0 = open.  */

int closed;
object meditate;

void set_up_skills();

void
create_room()
{ 
   
   set_short("Pirates Training Room");
   set_long(
      "This is the training room of the Pirates. Here you can "+
      "<learn> new skills, <improve> skills you already know, "+
      "and <meditate>. A large lava flow enters from the "+
      "southeast, runs along the east wall, and then exits "+
      "to the northeast. The room is extremely hot.\n");
   add_item(({"wall","walls"}),
      "The walls and ground are hot to the touch. It might "+
      "have something to do with the lava by the east wall.\n");
   add_item(({"lava","lava flow","east wall"}),
      "The lava is red-hot molten rock "+
      "flowing along the east wall. There is not much "+
      "lava here, but there is enough to make this room "+
      "extreamly hot and steamy.\n");
   add_item(({"gound","floor"}),
      "The gound is hot and covered with steam. The only "+
      "portion of the ground you can see clearly is the "+
      "glowing lava flow on the east wall.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_TYPE, ROOM_NORMAL);
   add_exit(THIS_DIR+"boardroom","west",0);
   
   create_skill_raise();
   set_up_skills();
   
}

void
leave_inv(object ob, mixed to)
{
   ::leave_inv(ob, to);
   gs_leave_inv(ob, to);
   
}


void
init()
{
   ::init();
   init_skill_raise();
   init_guild_support();
   
}

void
set_up_skills()
{
   string me, ot;
   
   me = "insult enemies into submission"; ot = me;
   sk_add_train(SS_INSULT,({ me, ot }), "insult", 85, 100 );
   me = "gut Knights and Calians with a knife"; ot = me;
   sk_add_train(SS_WEP_KNIFE,  ({ me, ot }),    0, 0, 80);
   me = "convince merchants that you get a better deal"; ot = me;
   sk_add_train(SS_TRADING,    ({ me, ot }),       0, 0, 80);
   me = "defend yourself"; ot = me;
   sk_add_train(SS_DEFENCE,({me,ot}),0, 0, 60);
   me = "stab your friends in the back"; ot = me;
   sk_add_train(SS_BACKSTAB,({me,ot}),0,0, 90);
   me = "open locks without a key"; ot = me;
   sk_add_train(SS_OPEN_LOCK, ({ me, ot }),    0, 0, 75 );
   me = "hide when you feel like it"; ot = me;
   sk_add_train(SS_HIDE, ({ me, ot }),     0, 0, 85 );
   me = "become more aware of your enemies and surroundings"; ot = me;
   sk_add_train(SS_AWARENESS,({ me, ot }), 0 , 0, 90);
}

void
gs_hook_start_meditate()
{
   write("You fall to your knees and pray to your lord and "+
      "master.\n");
   tell_room(ENV(TP),QCTNAME(TP)+" falls to "+
      TP->query_possessive()+" knees in "+
      "reverence to Lord Diablo.\n",TP);
}

void
gs_hook_rise()
{
   write("You rise from your worship of El Diablo.\n");
   tell_room(ENV(TP),QCTNAME(TP)+" rises from "+
      TP->query_possessive()+" worship of El Diablo.\n",TP);
}

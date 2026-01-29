/* humanoid npc coded by Elizabeth Cook/Mouse, January 1997 */

inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "/std/act/chat";
inherit "/std/act/action";
#include "../../mouse.h"  

void create_monster()  {
     set_name("leah");
     set_living_name("mouse:leah");
     set_race_name("human");
     set_short("tanner's daughter");
     set_long("Leah is Matteus' daughter, who minds the shop. She is "+
          "a small, pretty girl. She is rather shy and soft-spoken for one "+
          "who must deal so much with the public, yet her sweet nature "+
          "more than compensates for it. She has a ready smile and warm "+
          "greeting for everyone who enters the shop.\n");
     set_stats(({20,25,25,25,20,25}));
     set_skill(SS_UNARM_COMBAT,20);
     set_skill(SS_DEFENCE,10);
     set_skill(SS_AWARENESS,25);
     set_gender(G_FEMALE);
     set_alignment(ALIGN_BLESSED);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(CONT_I_WEIGHT, 32000);
     add_prop(CONT_I_HEIGHT, 120);

     set_act_time(30);
     add_act("emote smiles shyly.\n");
     add_act("emote says softly:  Greetings. Let me know if I may assist "+
          "you.\n");
     add_act("emote quietly hums a church hymn.\n");

     set_chat_time(25);
     add_chat("'Tis a beautiful day, is it not?\n"); 
}

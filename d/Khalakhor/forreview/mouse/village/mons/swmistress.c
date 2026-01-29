/* humanoid npc coded by Elizabeth Cook/Mouse, March 1997 */

inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "/std/act/chat";
inherit "/std/act/action";
#include "../../mouse.h"  

void create_monster()  {
     set_name("seamstress");
     add_name("mistress");
     set_living_name("mouse: seamstress");
     set_race_name("human");
     set_short("mistress seamstress");
     set_long("The mistress seamstress is an expert at her craft. Her "+
           "adept fingers fly through their tasks with amazing speed and "+
           "grace. Somehow she is capable of concentrating on her own "+
           "work, while overseeing the endeavors of her assistants "+
           "as well.\n");
     set_stats(({20,30,25,25,25,30}));
     set_skill(SS_UNARM_COMBAT,20);
     set_skill(SS_DEFENCE,30);
     set_skill(SS_AWARENESS,25);
     set_gender(G_FEMALE);
     set_alignment(ALIGN_SYMPATHETIC);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(LIVE_I_NEVERKNOWN,1);
     add_prop(CONT_I_WEIGHT, 60000);
     add_prop(CONT_I_HEIGHT, 180);

     set_act_time(30);
     add_act("emote makes another stitch in the fabric.\n");
     add_act("emote carefully examines the emerging pattern of the "+
           "needlework.\n");
     add_act("emote checks the progress of her assistants.\n");
     add_act("emote tells the girl cutting the pattern:  Don't waste "+
           "any of that material! It was quite expensive and it might "+
           "well be a long time before the elves send us any more of "+
           "that quality!\n");

     set_chat_time(25);
     add_chat("Parties at the manor mean more work for us.\n"); 
     
}

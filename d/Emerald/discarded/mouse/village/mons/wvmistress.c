/* humanoid npc coded by Elizabeth Cook/Mouse, March 1997 */

inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "/std/act/chat";
inherit "/std/act/action";
inherit "/std/act/asking";
inherit "/std/act/trigaction";
#include "../../mouse.h"

void create_monster()  {
     set_name("weaver");
     add_name("mistress");
     set_living_name("mouse: weaver");
     set_race_name("human");
     set_short("mistress weaver");
     set_long("The mistress weaver is an expert at her craft. Her adept "+
         "fingers fly through their tasks with amazing speed and grace."+
         "The mistress' quick eyes and small, hawkish features remind "+
         "you of a bird.\n");
     set_gender(G_FEMALE);
     set_alignment(ALIGN_SYMPATHETIC);
     set_stats(({20,30,25,25,25,30}));
     set_skill(SS_UNARM_COMBAT,20);
     set_skill(SS_DEFENCE,30);
     set_skill(SS_AWARENESS,25);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(LIVE_I_NEVERKNOWN,1);
     add_prop(CONT_I_WEIGHT, 60000);
     add_prop(CONT_I_HEIGHT, 180);

     set_act_time(30);
     add_act("emote adeptly passes the shuttle through the warp threads.\n");
     add_act("emote carefully selects the next color of yarn for the "+
           "pattern she is working on.\n");
     add_act("emote checks the progress of her assistants.\n");
     add_act("emote looks up at you and inquires:  What may I do for "+
           "you? We are very busy right now, I fear.\n");

     set_chat_time(25);
     add_chat("Be careful there, girl! If you hold it too taut, "+
           "you'll break the thread.\n"); 

     set_default_answer("The mistress looks at you confusedly.\n");
     
     add_ask("help","The mistress replies:  I could use some help. "+
           "If you are serious, you may ask me for a task.\n");
     add_ask("task","The mistress says:  I and my assistants are too "+
           "busy with our work here. I need someone to gather the herbs "+
           "we use to make the dyes. If you are willing to do this, I "+
           "will reward you richly. Ask for a color, and I will decide "+
           "which color we need most.\n"); 
}

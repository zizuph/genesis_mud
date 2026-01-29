/* humanoid npc coded by Elizabeth Cook/Mouse, January 1997 */

inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "/std/act/chat";
inherit "/std/act/action";


void create_monster()  {
     set_name("drunkard");
     set_living_name("mouse:drunkard");
     set_race_name("human");
     add_adj(({"stumbling","drooling"}));
     set_short("stumbling, drooling human");
     set_long("This woozy man is the town drunkard. He looks and smells "+
          "as if hasn't bathed in a decade. Judging by his filthy clothing, "+
          "it appears he hasn't changed his clothing since his last bath, "+
          "either. He is grinning and drooling on himself, and can barely "+
          "hold his eyes open. He is babbling to himself incoherently. "+
          "Despite his less than agreeable appearance, he is completely "+
          "harmless.\n");
     set_stats(({20,30,25,25,25,30}));
     set_skill(SS_UNARM_COMBAT,10);
     set_skill(SS_DEFENCE,10);
     set_gender(G_MALE);
     set_alignment(ALIGN_NICE);
     add_prop(LIVE_I_NEVERKNOWN,1);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(CONT_I_WEIGHT, 60000);
     add_prop(CONT_I_HEIGHT, 190);

     set_act_time(20);
     add_act("emote grins stupidly.\n");
     add_act("emote drools on himself.\n");
     add_act("emote hugs a tree to prevent himself from falling over.\n");
     add_act("emote tries to dance a jig and falls down.\n");
     add_act("emote hiccups loudly.\n");

     set_chat_time(15);
     add_chat("Tie the dawk of the hairsh, ish good shtuf!\n");
     add_chat("May mayad gesh wife when ay comsh nith home every drunkth, "+
          "so ay don'th drinth on Tooshdaysh.\n");
    
}

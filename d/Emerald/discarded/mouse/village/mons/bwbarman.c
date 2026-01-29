/* humanoid npc coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "std/act/chat";
inherit "std/act/action";
#include "../../mouse.h"   

void create_monster()  {
     set_name("bartender");
     set_living_name("mouse:bartender");
     set_race_name("human");
     add_adj(({"burly","jolly"}));
     set_short("burly, jolly bartender");
     set_long("This large, jovial human has been running the "+
          "Briarwood Inn for years. His good-naturedness makes him "+
          "well liked amongst his patrons. His easy-going demeanor "+
          "should not be mistaken as a sign of weakness, however.\n");
     set_stats(({60,50,55,55,60,50}));
     set_skill(SS_UNARM_COMBAT,50);
     set_skill(SS_DEFENCE,50);
     set_skill(SS_AWARENESS,50);
     set_gender(G_MALE);
     set_alignment(ALIGN_GOOD);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(CONT_I_WEIGHT, 100000);
     add_prop(CONT_I_HEIGHT, 200);
     add_prop(LIVE_I_NEVERKNOWN,1);  

     set_act_time(10);
     add_act("emote grins widely.\n");
     add_act("emote polishes a glass with a soft white cloth.\n");
     add_act("emote holds a gleaming glass up toward the light to check "+
          "for any spots.\n"); 
     add_act("emote looks at you and asks in a chuckling voice:  What's "+
          "your poison?\n");
     add_act("emote shouts:  Alice! Quit dawdling, girl!\n");

     set_chat_time(5);
     add_chat("Nothing can shock me, I've heard it all, trust me.\n");
     add_chat("Nothing happens in Festiwycke I don't hear about it "+
          "sooner or later. I know more secrets than the priest.\n");

}



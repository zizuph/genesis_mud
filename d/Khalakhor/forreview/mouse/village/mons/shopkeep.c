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
     set_name("shopkeeper");
     set_living_name("mouse:shopkeeper");
     set_race_name("human");
     set_short("shopkeeper");
     set_long("This well-dressed, rotund man is the owner of the "+
          "General Trade. He was fortunate to gain trading rights with "+
          "the elves, which has made him quite a tidy sum. He will be "+
          "more than glad to help you part with some of your coin, "+
          "though he is known to drive a hard bargain when required to "+
          "part with coin of his own.\n");
     set_stats(({25,20,25,25,25,30}));
     set_skill(SS_UNARM_COMBAT,20);
     set_skill(SS_DEFENCE,20);
     set_skill(SS_AWARENESS,25);
     set_gender(G_MALE);
     set_alignment(ALIGN_NASTY);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(LIVE_I_NEVERKNOWN,1);
     add_prop(CONT_I_WEIGHT, 80000);
     add_prop(CONT_I_HEIGHT, 180);

     set_act_time(30);
     add_act("emote smiles greedily.\n");
     add_act("emote pats his large belly with great satisfaction.\n");
     add_act("emote carefully examines an object he has recently "+
          "unpacked from a crate.\n");

     set_chat_time(25);
     add_chat("I trade only in the best goods!\n");
     add_chat("Shall we strike a deal?\n");
     add_chat("Nothing sounds better than the jingle of coins in one's "+
          "pocket!\n"); 
}

/* humanoid npc coded by Elizabeth Cook/Mouse, February 1997 */

inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "/std/act/action";
#include "../../mouse.h"

void create_monster()  {
     set_name("alice");
     set_living_name("mouse:alice");
     add_name("girl");
     set_race_name("human");
     set_short("girl clearing tables");
     set_long("This is Alice, a young, slightly built girl who earns "+
          "her keep by clearing tables and washing dishes. Her hair is "+
          "falling loose from its braid and streams of perspiration "+
          "have begun to stream down her tiny face. She works laboriously "+
          "for one of such a young age.\n");
     set_stats(({10,10,15,15,10,10}));
     set_skill(SS_UNARM_COMBAT,10);
     set_skill(SS_AWARENESS,10);
     set_gender(G_FEMALE);
     set_alignment(ALIGN_BLESSED);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(CONT_I_WEIGHT, 30000);
     add_prop(CONT_I_HEIGHT, 100);

     set_act_time(30);
     add_act("emote wipes a loose strand of hair from her eyes.\n");
     add_act("emote removes dirty glasses from a table and wipes "+
          "down the tabletop.\n");
     add_act("emote sighs deeply.\n");

  
}

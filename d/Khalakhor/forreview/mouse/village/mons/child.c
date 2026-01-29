/* humanoid npc coded by Elizabeth Cook/Mouse, November 1996 */

inherit "std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "std/act/chat";
inherit "std/act/action";
#include "../../mouse.h"  

string* desc1 = (({
     "red-haired","blond-haired","black-haired","tall","short","whiney",
     "obnoxious","well-behaved","buck-toothed","snot-nosed"}));

string* desc2 = (({
     "blue-eyed","brown-eyed","skinny","fat","dirty","loud-mouthed","sullen",
     "cheerful","grubby"}));

void create_monster()  {
     string adj1,adj2;
     adj1 = desc1[random(10)];
     adj2 = desc2[random(9)];
     set_name("child");
     set_race_name("human");
     set_gender(random(1));
     set_short(adj1+", "+adj2+" child");
     set_long("This "+adj1+" child is playing in the ditch beside the road.\n");
     set_stats(({20,20,15,15,20,15}));
     set_skill(SS_UNARM_COMBAT,15);  
     set_alignment(ALIGN_NEUTRAL);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(LIVE_I_NEVERKNOWN,1);
     add_prop(CONT_I_WEIGHT, 30000);
     add_prop(CONT_I_HEIGHT, 100);
}



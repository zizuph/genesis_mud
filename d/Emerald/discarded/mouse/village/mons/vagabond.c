/* humanoid npc coded by Elizabeth Cook/Mouse, March 1997 */

inherit "std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "std/act/chat";
inherit "std/act/action";
#include "../../mouse.h" 

string* desc1 = (({
     "stinking","rotten-toothed","grinning","limping","desperate-looking",
     "slack-jawed","tired","sullen","impoverished","starving"}));

string* desc2 = (({
     "ragged","filthy","scrawny","greasy","dirty","unkempt","half-crazed",
     "shiftless","grubby"}));

void create_monster()  {
     string adj1,adj2;
     adj1 = desc1[random(10)];
     adj2 = desc2[random(9)];
     set_name("vagabond");
     add_adj(({adj1,adj2}));
     set_race_name("human");
     set_gender(random(1));
     set_short(adj1+", "+adj2+" human");
     set_long("This "+adj1+" vagabond has sought safety in numbers "+
          "here in this encampment that is off the beaten track.\n");
     set_stats(({20,25,20,20,25,20}));
     set_skill(SS_UNARM_COMBAT,20);
     set_skill(SS_DEFENCE,20);
     set_skill(SS_AWARENESS,20);
     set_alignment(ALIGN_NASTY);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
     add_prop(CONT_I_WEIGHT, 60000);
     add_prop(CONT_I_HEIGHT, 180);
}



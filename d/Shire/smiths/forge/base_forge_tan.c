   /* Tobin, the Shop keeper at Smiths Guild */

inherit "/sys/global/money";
inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"

#define NECKLACE SMITHSDIR_OBJ+"npc_neck"

void
create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({FORGE_TANNER_NAME,"seller", "smiths_guild_keeper"}));
   set_title(FORGE_TANNER_TITLE);
   set_race_name(FORGE_TANNER_RACE);
   set_adj(({FORGE_TANNER_ADJ1,FORGE_TANNER_ADJ2}));
   set_long("This is the seller of Smiths' items\n");

             /* STR  DEX CON INT WIS DIS */
   set_stats(({ 90, 50, 100, 50, 70, 90 })); 

   add_ask(({"buy","steel bar","steel bars"}),QCTNAME(TO)+" says to you: "+
      " That was lucky, I have just bought a large amount of steel bars. You"+
      " can <pay>"+
      STEEL_COST+" copper coins for a steel bar.\n");
   add_ask(({"pole","wooden pole","wooden poles"}),QCTNAME(TO)+
      " says to you: "+
      " That was lucky, I have all the wooden poles you want. You"+
      " can <pay>"+
      WOOD_COST+" copper coins for a wooden pole.\n");

   set_alignment(250);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_DEFENCE,80);
   command("wield all");
}
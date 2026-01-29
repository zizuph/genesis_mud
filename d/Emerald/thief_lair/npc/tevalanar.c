/* Tevalanar, the half-elven leader of the bandits in the Blackwall
   mountains.

   Code (c) 1999 Damian Horton. BKA Casimir.
*/

#pragma strict_types
#pragma save_binary 

#include <wa_types.h>                        
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit THIEF_LAIR_DIR + "/npc/leader.c";
inherit THIEF_LAIR_DIR + "/npc/intro.c";

void
create_bandit()
{
    set_name("tevalanar");
    set_title(", Bandit Leader");
    set_race_name("half-elf");
    set_adj("haughty");
    add_adj("stern-faced");
    set_long("Given his finelly chiselled features, and the air of "+
	"quiet grace and superiority that attends him, one could easily "+
	"mistake him for an elf were it not for a lair of fine, blonde "+
	"stubble which grows on his cheeks. Inspite of its soft features, "+
	"his countenance is a mask of grim determination. You have every "+
	"reason to expect that he is very competant and therefore dangerous, "+
	"individual.\n"); 
    add_prop(CONT_I_HEIGHT, 166);
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_VOLUME, 165000);
   
    set_stats(({110, 125, 115, 115, 95, 120}));
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_BLIND_COMBAT, 62);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 85);
    set_skill(SS_UNARM_COMBAT,65);
    set_skill(SS_AWARENESS, 68);
    set_alignment(-600);
    set_exp_factor(150); //nasty specials, part of a very dangerous group

    set_act_time(6);
    add_act("emote assesses you with an unflinching eye.");
  
    set_cact_time(10);
    add_cact("emote shakes his head in disbelief.");
    add_cact("say Well, at least we will have some new weapons.");
    add_cact("say You will not survive to report our location to the "+
	     "elvish patrols.");

     //		THIEF_LAIR_DIR + "arm/leather_undercoat" ?!
    add_equipment(({THIEF_LAIR_DIR + "wep/elvish_longsword",
		      THIEF_LAIR_DIR + "arm/chainmail_overcoat",
		      THIEF_LAIR_DIR + "arm/quilt_leggings"}));
    ::create_bandit_leader();    
}
 
/* sets unarmed combat off, giving more sword attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}
 





/* created by, when:   who knows?? */

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include "../local.h"

inherit M_FILE

void
create_krynn_monster()
{
    set_name("farmer");
    set_short("nervous farmer");
    set_long("This farmer is busy harvesting his wheat. " +
	     "His face has lines of stress not usually " +
	     "so prominant in someone of his age. " +
	     "His clothes have seen long years of use " +
	     "and are patched in places.\n");
    set_race_name("human");
    set_adj("nervous");
    
    set_skill(SS_DEFENCE, 10);
    set_skill(SS_WEP_SWORD, 10);
    default_config_mobile(21);
    set_knight_prestige(-1);
    
    set_act_time(1);
    add_act("emote watches you out of the corner of his eye.");
    add_act(({"emote looks around nervously.",
	      "emote stares at you suspiciously.",
	      "say I don't want any trouble."}));
    add_act(({"say There are strange rumours about...",
	      "say People have been disappearing in the night.",
	      "say I don't trust strangers now...You should leave."}));
    add_act(({"say Good luck on your way.",
	      "emote goes back to his work, ignoring you."}));
    add_act("emote pretends not to notice you.");
    
    
    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP + "scythe")->move(TO);
    command("wield weapon");
}

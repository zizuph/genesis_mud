
/* SW guard... */

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include "/d/Rhovanion/common/rhun/sw/s_s/sw_ent_quest.h"

create_monster() {
	set_race_name("human");
	set_adj("elderly");
	set_short("An elderly human");
	set_name("man");
	add_name("spellweaver_guard");
	add_name("_SW_guild_guard_");
	
	set_alignment(-301);
	set_gender(0);
	set_long("This elderly man is standing here as if guarding something, "+
	    "though you know not what.\n");
	add_prop(CONT_I_WEIGHT, 65*1000);
	add_prop(CONT_I_VOLUME, 65*1000);
	add_prop(CONT_I_HEIGHT, 150);
	add_prop(NPC_M_NO_ACCEPT_GIVE,0);
	set_stats(({60,50,40,70,70,50}));
	set_hp(query_max_hp());
	
	
	set_skill(SS_UNARM_COMBAT, 25);
	set_skill(SS_DEFENCE, 19);
	
	set_chat_time(5);
	add_chat("Hello.");
	add_chat("Bring me a piece of evidence.");
	
	set_act_time(4);
	add_act("smile softly");
	add_act("nod thoughtfully");
	add_act("emote quickly makes a strange sign in midair.");
	
}


enter_inv(object obj, object from)
{
    if (!from) return;
    ::enter_inv(obj,from);
    if(obj==present("_sw_ent_quest_cloth_scrap"))
    {
        command("say Thank you.  You have done well.");
	command("say Approach the wall, and complete your quest.");
	command("point north");
	TP->add_prop(I_DID_NOT_KILL_GUILD_GUARD,1);
    }
    else
    {
        command("say I don't need this.  You may have it back.");
		write("The elderly human returns it to you.\n");
        obj->move(from);
        return 1;
    }
}

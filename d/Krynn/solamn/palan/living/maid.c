/* created by Aridor, 09/10/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "cblouse")->move(TO);
    clone_object(OBJ + "skirt")->move(TO);
    clone_object(OBJ + "sandals")->move(TO);
    command("wear all");
    MONEY_MAKE_SC(random(5))->move(TO);
}

void
create_citizen()
{
    set_name("adria");
    add_name("maid");
    set_race_name("elf");
    set_introduce(", housemaid to Lord Amothus Palanthus");
    set_gender(1);
    set_adj("merry");
    add_adj("talkative");
    set_long("@@my_long@@She seems to have her free day today, strolling " +
	     "around the city.\n");
    default_config_npc(random(10) + 30);
    add_prop("_live_m_attack_thief","call_guards");
    set_act_time(0);
    add_act("say I just bought this pretty blouse. Do you like it?"); 
    add_act("emote fluffs her hair.");
    add_act(({"say Stay away from the Shoikan grove.", "emote shivers."}));
    add_act(({"say A lovely day, isn't it?",
		"emote looks expectantly at you."}));
    add_act("emote shakes a stone from her sandal.");
    add_act("say I heard there are draconians in the Plains of Solamnia.");   
    add_act("say The Knights of Solamnia will protect Palanthas.");
    add_act(({"say Surely Palanthas is the most beautiful city in all the " +
		"world.", "emote smiles blissfully."}));
    add_act("say Lord Amothus Palanthus assured me that the Blue Army "+
	    "will never get beyond Westgate Pass.");
    
    add_ask(({"grove", "shoikan"}),
	    "say It is a cursed place that craves flesh.", 1); 
    add_ask(({"plains", "solamnia"}),
	    "say Why, I thought everyone knew that the Plains of Solamnia " +
	    "are southeast of Palanthas!", 1);   
    add_ask(({"draconians", "army", "blue army"}),
	    "say The Highlord Kitiara and her blue dragon Skie have an " +
	    "army in the plains.", 1); 
    set_random_move(30);
    set_restrain_path(TDIR);
}

void
call_guards(object thief, object victim, object what)
{
    command("say Help! Thieves! Robbers! HELP!");
    command("panic");
    call_the_guards(thief->query_real_name(),"xxx");
}

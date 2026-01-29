/* created by Aridor, 09/15/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>
#include <ss_types.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "robe")->move(TO);
    clone_object(OBJ + "shoes")->move(TO);
    clone_object(OBJ + "wshirt")->move(TO);
    clone_object(OBJ + "trousers")->move(TO);
    command("wear all");
    MONEY_MAKE_CC(random(55))->move(TO);
}

void
create_citizen()
{
    set_name("edgar");
    add_name("minstrel");
    set_race_name("human");
    set_introduce("Allen Poe, Travelling Minstrel");
    set_gender(0);
    set_adj("young");
    add_adj("musical");
    set_long("@@my_long@@He is hoping for a good audience here in " +
	     "Palanthas.\n");
    default_config_npc(random(30) + 40);
    set_skill(SS_DEFENCE, 60);
    set_all_hitloc_unarmed(10);
    add_prop("_live_m_attack_thief", 1);
    set_act_time(0);
    add_act("say There are draconians in the Plains of Solamnia. I've seen " +
	    "them on my journey here.");
    add_act("say The Knights of Solamnia are standing at Westgate Pass.");
    add_act(({"say Palanthas is the most beautiful city I have ever seen."}));
    add_ask(({"plains", "solamnia"}),
	    "say Why, I thought everyone knew that the Plains of Solamnia " +
	    "are southeast of Palanthas!", 1);   
    add_ask(({"draconians", "army", "blue army"}),
	    "say The Highlord Kitiara and her blue dragon Skie have invaded " +
	    "the Plains of Solamnia. They're trying to split Solamnia and" +
	    "disable the supply lines from here to Vingaard Keep.", 1); 
    set_random_move(100);
    set_restrain_path(TDIR);

}


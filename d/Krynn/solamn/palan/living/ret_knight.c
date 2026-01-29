/* created by Aridor, 09/10/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>
#include <ss_types.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "sol_armour")->move(TO);
    clone_object(OBJ + "sol_boots")->move(TO);
    clone_object(OBJ + "sol_sword")->move(TO);
    command("wear all");
    MONEY_MAKE_SC(random(5))->move(TO);
}

void
create_citizen()
{
    set_name("arthur");
    add_name("knight");
    set_race_name("human");
    set_introduce("Crownguard, Knight of the Rose, Retired");
    set_gender(0);
    set_adj("old");
    add_adj("stout");
    set_long("@@my_long@@He is enjoying his days in the beautiful city " +
	     "of Palanthas.\n");
    set_extra_long("He is wearing the moustache of a Knight of Solamnia.\n");
    default_config_npc(random(30) + 110);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE, 60);
    set_all_hitloc_unarmed(10);
    add_prop("_live_m_attack_thief", 1);
    set_act_time(50);
    add_act(({"say Stay away from the Shoikan grove.",
		"say That place is cursed." }));
    add_act("say I heard there are draconians in the Plains of Solamnia.");   
    add_act("say The Knights of Solamnia will protect Palanthas.");
    add_act(({"say Palanthas is the most beautiful city I have ever seen."}));
    add_act(({"say Lord Amothus Palanthus told me the other day that the " +
		"Blue Army will never get beyond Westgate Pass.",
		"say Ha, I wouldn't count on that!"}));
    
    add_ask(({"club","knight club","knights club","knights' club"}),
	    "say Certainly I know where you can find it. From the plaza you " +
	    "need to go east along Paladine Street, then turn into Knights' " +
	    "Avenue. It's right there.",1);
    add_ask(({"grove", "shoikan"}),
	    "say The evil has taken hold there, it's like a thorn in the " +
	    "side of Palanthas.", 1); 
    add_ask(({"plains", "solamnia"}),
	    "say Why, I thought everyone knew that the Plains of Solamnia " +
	    "are southeast of Palanthas!", 1);   
    add_ask(({"draconians", "army", "blue army"}),
	    "say The Highlord Kitiara and her blue dragon Skie have invaded " +
	    "the Plains of Solamnia. They're trying to split Solamnia and " +
	    "disable the supply lines from here to Vingaard Keep.", 1); 
    add_ask(({"derek"}),"say Well, Derek, that's my son! He's a knight now " +
	    "and continues the proud tradition of the family.\n");
}

attacked_by(object who)
{
    ::attacked_by(who);
    command("wield all");
}








// Bazaar Armourer (/d/Avenir/common/outpost/mon/armourer.c)
// creator(s):     Lilith, Apr 2022
// purpose:        cloned to /outpost/armorer.c
// note:           repairs armours twin of Phinia in the Bazaar Armory
// revisions:
      
#pragma strict_types

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";
inherit "/d/Avenir/inherit/sigil";
inherit "/d/Avenir/common/outpost/mon/call_for_help";

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

// Like haste, but better
void add_attacks()
{
    query_combat_object()->cb_set_attackuse(150);
}

string no_jobs()
{
    command("say I don't have any tasks right now, but I know "+
        "if you go to the Bazaar, the librarian, the blacksmith, "+
        "and even Jadestone might have something for you to do.");
}
	
public void 
create_monster(void)
{
    if (!IS_CLONE)
	return;

    ::create_monster();
	
    setuid();
    seteuid(getuid());

    set_name("phedra");
    set_living_name("phedra");
    set_title("icu I'orar, Master Armourer of Fort Sybarus");
    set_syb_house("i'orar");	
    set_race_name("dwarf");
    set_adj("commanding");

    set_long("@@my_long@@");

    set_gender(G_FEMALE);
    set_alignment(0);
    set_appearance_offset(-30);
	
    set_all_attack_unarmed(60,60);
    set_all_hitloc_unarmed(60); 
    default_config_npc(random(20) + 105);
	
    set_skill(SS_DEFENCE,      85);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_WEP_AXE,      80);
	set_skill(SS_WEP_CLUB,     80);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS,    70);
    set_skill(SS_SPELLCRAFT, 70);  // reduce caster damage
    set_skill(SS_FORM_ABJURATION, 70);  // reduce caster damage
    set_skill(SS_AWARENESS, 70);   // reduce theiving of imbues
    set_skill(SS_ACROBAT, 70);     // reduce melee damage

    MAKE_SYBARITE; 
	
	add_prop(LIVE_I_SEE_DARK,  1); // So she can conduct business 
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);
	
    set_act_time(25);
    add_act("sigh softly");
    add_act("smile respect elf");
    add_act("emote moulds some leather padding into a chainmail shirt.");
    add_act("emote pounds a dent out of a helmet.");
    add_act("emote measures a dwarf and fits him with fresh armour.");
    add_act("emote rolls her shoulders to relieve some tension.");
	
    set_default_answer("say There are questions I cannot or will "+
       "not answer. I'm sure you understand.", 1);

    add_ask(({"phinia", "twin" }), 
        "say Phinia is the Master Armourer at the Bazaar. She is also "+
        "my twin sister. Most dwarves are born as twins and triplets, "+
        "you know.", 1);
		
    add_ask(({"coal"}),
        "say We've got plenty coal here, but the smith in the Bazaar "+
        "always needs more.", 1);		
		
    add_ask(({"fights", "trouble", "gaol", "defenders", "guards"}),
        "say The defenders here are serious about their work. "+
        "If you start a fight at Fort Sybarus, they will toss "+
        "you into the gaol and leave you to rot there.", 1);
		
    add_ask(({"grouth", "old banker", "manager", "old manager"}),
        "say The old manager, Grouth, retired and his son has "+
        "taken over the job.", 1);
		
    add_ask(({"amblo", "old gnome", "merchant", "bank"}),
        "say Amblo the merchant and the old manager, Grouth, "+
        "started a bank. Grouth retired but last I heard "+
        "Amblo was still doing Nitikas' Will down in the "+
        "underdark.", 1);

    add_ask("[about] [the] 'ogre' / 'ogres' [problem]", 
	    "say We've got an ogre problem. "+
        "Darn things feed on rats and breed just like them. When "+
        "they run out of stuff to eat they up rise through the Underdark "+
		"like turds in a chamberpot.", 1);		
		
    set_alarm(0.1, 0.0, add_attacks);	

}


int query_not_attack_me(object who, int aid)
{
    mixed comm;
    who->catch_msg(QCTNAME(this_object()) +" steps out of harm's way, "+
    "causing you to miss. How frustrating!\n");       
    comm = (({"emote grumbles.",
    "say Who do you think you are, attacking me in my own shop?",
    "emote is seems to channel a dark aura.",
    "say to "+ OB_NAME(who) +" If you don't stop this I won't "+
    "do any more repairs for you.",
    "say to "+ OB_NAME(who) +" You aren't very bright, are you?",
    "say to "+ OB_NAME(who) +" Perhaps if you pick on someone your "+
    "own size, you would win a fight.",
    "say to "+ OB_NAME(who) +" This will take you all day.",
    "emote makes evading attacks look easy.",
    "emote seems to be enjoying the workout.",
    "say to "+ OB_NAME(who) +" Leave now!",
    }));        
        
    command(one_of_list(comm));
    return 1;
}

public string 
query_exp_title(void)
{
    return "sybarite";
}

public string
my_long(void)
{
    string str = "She is a commanding female dwarf.\n";

    if (TP->query_met(query_real_name()))
    {
	str = query_name() +" is a commanding dwarf, presenting "+
	"herself as:\n"+ query_name();
	if (strlen(query_title()))
	    str += " "+ query_title() +",";
	str += " "+ query_exp_title() +", female dwarf.\n";
    }

    str += "She is a slender, paler version of a surface dwarf.\n"+
    "She has smooth and creamy nut-brown skin.\n"+	 
    "Her short chestnut brown hair falls "+
    "in waves about her face and neck.\n"+
    "She has a tidy red-gold chin curtain beard.\n"+
    "She has a fuzzy red-gold set of whiskers.\n"+
    "Her shoulders and arms are muscular, and her square,\n"+
    "short-nailed hands have callouses.\n"+
    "She has wise, dark eyes that regard you with some impatience.\n"+
    "She is wearing a thick leather apron, a thin chainmail shirt, "+
    "a set of leather chaps, a pair of suede trousers, and steel boots.\n";
    return str;
}


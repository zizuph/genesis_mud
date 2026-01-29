// file name: /d/Avenir/common/dead/mon/bogl_on_duty.c
// creator(s): Lilith June 2021
// last update:
// purpose: BOGLer working with corpses.
// note:   
// bug(s):
// to-do:

#pragma strict_types

inherit "/std/monster";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#define BOBJ "/d/Avenir/common/bazaar/Obj/"
#define ZOBJ "/d/Avenir/common/city/zigg/obj/"

void
equip_me()
{
	
    seteuid(getuid());

    clone_object(ZOBJ+"soap")->move(TO,1);
    clone_object(BOBJ+"worn/loincloth")->move(TO, 1);
    clone_object(BOBJ+"worn/pshirt")->move(TO, 1);
	clone_object(OBJ+"rushlight")->move(TO, 1);
	if (random(10) <1)
	    clone_object(OBJ+"death_mask")->move(TO);
    command("wear all");	
}
string horns = one_of_list(({"silver-tipped","copper-tipped","polished",
               "dyed green","dyed pink","dyed purple","dyed blue",
			   "sanded flat","painted with stripes","inset with pearls",
			   "inset with pyrite","inset with garnets","inset with quartz",
			   "inset with onyx"}));	
string eyes = one_of_list(({"honest", "child-like", "kind", "merry",
               "wide", "small", "measuring", "intelligent", "wise",
               "interested", "playful", "amused", "contented",
               "hungry", "thoughtful"}));
			   
string 
my_long()
{
	string str;
    str = CAP(HE(TO)) +" is a "+query_adj()	+" "+ query_gender_string() 
	    + " goblin who seems to be "
	    + query_exp_title() +" in size.\n";
    str += CAP(HE(TO)) +" is a proud member of B.O.G.L.\n" 
		+ CAP(HIS(TO)) +" arms are long and "+ HIS(TO) +" back is strong.\n"
        + CAP(HE(TO)) +" appears to be remarkably mild-mannered for a goblin.\n"
		+ CAP(HE(TO)) +" seems to take pride in "+ HIS(TO) +" horns, "
		+"which are "+horns+".\n"
		+ CAP(HIS(TO)) +" eyes are dark and "+ eyes+ ".\n"
		+ CAP(HIS(TO)) +" skin is light brown and surprisingly clean for a goblin.\n";
    return str;
}	
	
public void
create_monster(void)
{

    string str = one_of_list(({
	"smiling", "simple", "happy", "content", "diligent",
	"sensitive", "tired", "muscular", "ugly", "one-eyed",
	"notch-eared", "slow", "kind", "hard-working", "dimpled",
	"patient", "snaggle-toothed", "big-eyed",
	"tiny", "sweaty", "aromatic", "focused"}));

    set_adj(str);
    add_name("bogl", "_Avenir_BOGL_goblin");
    set_race_name("goblin"); 
	  set_gender(G_MALE);
    set_short(str +" male goblin");
    set_pshort(str + " goblins");
    set_long(my_long);
	// stat ave 60 to 80
    default_config_npc(random(60) + 20);
    //Thick skinned little sucker. Full body AC is 25-35.
    set_all_hitloc_unarmed(25 +(random(10))); 
	add_prop(MAGIC_I_RES_MAGIC, 20); //~30% magic_dt immunity (like AC)
	
	set_skill(SS_AWARENESS,    50); // challenge imbue theives
    set_skill(SS_DEFENCE,      50); // reduce melee damage 	
    set_skill(SS_ACROBAT,      50); // reduce melee damage
	set_skill(SS_UNARM_COMBAT, 50);	 
    set_skill(SS_BLIND_COMBAT, 50); 
	set_skill(SS_SPELLCRAFT,   50); // reduce caster damage
	set_skill(SS_FORM_ABJURATION,50); // reduce caster damage

	set_act_time(20);
	add_act("emote hefts a corpse up out of the water and hands it off "+
	    "to another goblin.");
	add_act("emote picks something up out of the water and tucks it into "+
	    "the clothing of a corpse.");
	add_act("nod .");
    set_chat_time(60 + random(30));
	add_chat("It like my job.");
	add_chat("I hope he lived a good life so Mascarvin grants him rebirth.");
	add_chat("When's the next pahloor raid gonna be?");
	add_chat("I heard the son of a High Lord died on the Holm. They "
	    +"recovered his body so we will be interring it soon.");
    add_chat("We have a good life. We must be pleasing the gods.");
	add_chat("We serve Mascarvin and the Hegemon.");
	add_chat("I don't understand much but I don't need to.");
	add_chat("The undead are always moving.");
	add_chat("I saw a spectral guardian the other day. Had to clean my "
	   +"loicloth because I soiled myself.");
	add_chat("The quiet here is calming.");
	add_chat("Remember to put rubbish in the west chute and corpses "
	   +"in the east one. Don't mix it up this time!");
	add_chat("Be careful not to fall down the hole.");
	set_default_answer(VBFC_ME("what_me"));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_HAS_MONEY, 600);

}

string
what_me()
{
	switch(random(7))
	{
		case 0:
			command("say Slow down. I don't understand you.");
			break;
		case 1:
			command("say I don't know these things you ask about.");
			break;
		case 2:
			command("emote shrugs.");
			break;
		case 3:
			command("say Please stop asking me questions, you are scaring me.");
			break;
		case 4:
			command("emote looks anxiously around.");
			break;
		case 5:
			command("say Ask someone else, please.");
			break;
		case 6:
			command("emote pretends not to hear.");
			break;
	}
	return "";
}

// file name: /d/Avenir/common/dead/mon/bogl.c
// creator(s): Lilith June 2021
// last update: Lilith, Sept 2021: added gems but forgot to include gem.h
//              Lilith, Feb 2022: remove magic res now the combat system 
//                 is auto-calcing it based on AC. 
// purpose: goblin for the BOGL encampment
// note:   
// bug(s):
// to-do:

#pragma strict_types

inherit "/std/monster";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#include "/d/Genesis/gems/gem.h"
#define BOBJ "/d/Avenir/common/bazaar/Obj/"
#define ZOBJ "/d/Avenir/common/city/zigg/obj/"
void
equip_me()
{
	object gem;
	
    seteuid(getuid());
	
	// Everyone gets soap. Goblins aren't known for being clean or 
	// smelling good, but these are sybarite goblins...
    clone_object(ZOBJ+"soap")->move(TO,1);
	
	if (TO->query_gender() == G_FEMALE)
	{
	    clone_object(BOBJ+"worn/trouser")->move(TO, 1);
        clone_object(BOBJ+"worn/blouse")->move(TO, 1);
	    clone_object(ZOBJ+"glotion")->move(TO, 1);
	}	
	else
	{
        clone_object(BOBJ+"worn/loincloth")->move(TO, 1);
        clone_object(BOBJ+"worn/pshirt")->move(TO, 1);
	}
	
	// They like their sea food. Keeps down the goblin body odor, too.
    switch(random(10))
    {
		case 0:
	        clone_object(ZOBJ+"glotion")->move(TO, 1);
			break;
		case 1:
		    clone_object(BOBJ+"food/fish")->move(TO, 1);
			break;
        case 2:
            clone_object(BOBJ+"food/mollusk")->move(TO, 1);
		    clone_object(BOBJ+"food/hearty_bread")->move(TO, 1);
			break;
	    case 3:
	       clone_object(BOBJ+"food/eel")->move(TO, 1);
	       break;
	    case 4:
	       clone_object(BOBJ+"food/net_fish")->move(TO, 1);
	       break;
	    case 5:
	       clone_object(BOBJ+"food/hearty_bread")->move(TO, 1);
	       break;
	    case 6:
	       clone_object(BOBJ+"misc/net")->move(TO, 1);	   
	       break;
	    case 7:	      
		   clone_object(BOBJ+"wield/scratcher")->move(TO, 1);
	       break;
	    case 8:
		   gem = RANDOM_GEM_BY_RARITY(GEM_ALL);
           gem->move(TO,1);
	       break;
	    default:
	       clone_object(BOBJ+"misc/net")->move(TO, 1);   
    }	
    command("wear all");	
}

// In sybarus, goblin body-art is decorating their horns.
string horns = one_of_list(({"silver-tipped","copper-tipped","polished",
               "dyed green","dyed pink","dyed purple","dyed blue",
			   "tied with ribbons","sanded flat","painted with stripes",
			   "inset with pyrite","inset with garnets","inset with "+
               "pearls","inset with quartz","inset with onyx"}));
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
        + CAP(HE(TO)) +" appears to be remarkably even-tempered for a goblin.\n"
		+ CAP(HE(TO)) +" seems to take pride in "+ HIS(TO) +" horns, "
		+"which are "+horns+".\n"
		+ CAP(HE(TO)) +" has a smile on "+HIS(TO)+" face, showing clean fangs.\n"
		+ CAP(HIS(TO)) +" eyes are dark and "+ eyes+ ".\n"
		+ CAP(HIS(TO)) +" skin is light brown and surprisingly clean for a goblin.\n";
    return str;
}	
	
public void
create_monster(void)
{

    string str = one_of_list(({
	"smiling", "cheerful", "merry", "happy", "content",
	"sensitive", "tired", "muscular", "ugly", "one-eyed",
	"notch-eared", "dapper", "kind", "hard-working", "dimpled",
	"chipper", "laughing", "giggling", "snaggle-toothed", "big-eyed",
	"hard-working", "sweaty", "aromatic", "dusty"}));

    set_adj(str);
    add_name("bogl", "_Avenir_BOGL_goblin");
    set_race_name("goblin"); 
		if (random(5)>1)
	  set_gender(G_MALE);
    else
	  set_gender(G_FEMALE);
    set_short(str +" "+ query_gender_string() +" goblin");
    set_pshort(str + " goblins");
    set_long(my_long);
	// stat ave 40 to 80
    default_config_npc(random(40) + 40);
    //Thick skinned little sucker. Full body AC is 25-35.
    set_all_hitloc_unarmed(25 +(random(10))); 
	
	set_skill(SS_AWARENESS,    50); // challenge imbue theives
    set_skill(SS_DEFENCE,      50); // reduce melee damage 	
    set_skill(SS_ACROBAT,      50); // reduce melee damage
	set_skill(SS_UNARM_COMBAT, 50);	 
    set_skill(SS_BLIND_COMBAT, 50); 
	set_skill(SS_SPELLCRAFT,   50); // reduce caster damage
	set_skill(SS_FORM_ABJURATION,50); // reduce caster damage

	set_act_time(60);
	add_act("soapbubble");
	add_act("soapwash");
	add_act("rub lotion");
	add_act("eat food");
	add_act("itch back");
	add_act("emote hums a little melody.");
	add_act("emote sweeps the floor.");
	add_act("emote picks a bone up off the ground.");
	add_act("emote picks wax out of its ear.");
	add_act("emote puts some fresh herbs down on a mat");
	add_act("emote fillets a fish.");
	add_act("emote picks its teeth with a fish bone");
	add_act("sigh content");
	add_act("boggle");
	add_act("nod under");
    set_chat_time(60 + random(30));
	add_chat("It like my job.");
	add_chat("I like it here.");
	add_chat("I need to take the ferry back to the bazaar for supplies "
        +"soon. Do you need something?");
	add_chat("I'm hungry for some fish.");
	add_chat("I feel peaceful when I am fishing.");
	add_chat("This is a good home.");
	add_chat("Few people know we are here.");
	add_chat("I like to carry things and clean things.");
	add_chat("The ghosts and apparitions and other undead here in the marshes "
	    +"did something bad when they were living. That's why they don't "
		+"look like themselves. Did you know that?");
	add_chat("The undead down in the catacombs served the gods well, "
	    +"unlike the ones on the moors.");
	add_chat("We serve Mascarvin and the Hegemon.");
	add_chat("I don't understand much but I don't need to.");
	add_chat("The dwarves guarding the Fort are very vigilant.");
	add_chat("We need to pick up the next load of bodies. Someone check "
	   +"for strangers in the marsh.");
	add_chat("I like the quiet here. It helps me stay calm.");
	add_chat("It's time to sweep up again...");
	add_chat("Remember to put rubbish in the west chute and corpses "
	   +"in the east one. Don't mix it up this time!");
	add_chat("Be careful not to fall down the hole.");
	set_default_answer(VBFC_ME("what_me"));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 40 +(random(70)));
	add_prop(CONT_I_WEIGHT, 40000 +(random(40000)));
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

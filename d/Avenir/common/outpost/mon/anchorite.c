// Anchorite Priest at the Shrine
// creator(s):  Lilith May 2022
// purpose:		Stands at the entrance to the shrine
// revisions:	

inherit "/d/Avenir/inherit/monster";
// This allows her to introduce to players
inherit "/d/Avenir/inherit/intro";
// This has the house sigil subloc, etc
inherit "/d/Avenir/inherit/sigil";
// This allows her to answer questions about the gods, etc.
inherit "/d/Avenir/common/gods/god_asks";
// This will summon the punishers to take away attackers
inherit "/d/Avenir/common/outpost/mon/call_for_help";

#include "/d/Avenir/common/outpost/outpost.h"
#include <language.h>
#include <ss_types.h>

string
my_long()
{
    string  str;

    str =  "She is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += "She is a sybarite elf with distinctive milky white skin "+
           "that has never been exposed to sunlight.\n"+
	       "She appears to be a priest or cleric of some sort.\n"+
           "She has jet black eyes with a dreamy quality to them.\n"+
		   "She wears a shimmering veil over her hair and shoulders.\n"+
		   "She is wearing a grey silk tunic, a pair of flowing grey "+
           "trousers, and grey leather slippers.\n";
    return str;
}

string
no_jobs()
{
    command("say I have nothing for you at this time?");
    return "";
} // no_jobs()


void create_monster()
{
    if(!IS_CLONE)
       return;
   
    ::create_monster();

    set_name("kaenati");
    set_living_name("kaenati");
    add_name(({"cleric", "priest", "anchorite"}));
	set_title("icu Cha'uri, the Dedicated Oblate of Salilus and "+
        "Faithful Anchorite of the Hours");
	set_syb_house("cha'uri");
    set_race_name("elf");
    set_gender(G_FEMALE);
    set_adj("serious");
    set_adj("veiled");
    set_long(my_long);

    set_stats(({ 90, 90, 90, 90, 90, 90 }));
        
    set_alignment(0);
 
    set_skill(SS_DEFENSE,      80);
	set_skill(SS_WEP_POLEARM,  80);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS,    70);
	add_prop(LIVE_I_SEE_DARK,  1); 
    add_prop(CONT_I_HEIGHT,    200);
    add_prop(CONT_I_WEIGHT,    50000);
	
	
    set_act_time(60);
    add_act("emote paces briefly." );
    add_act("emote adjusts her veil to flow more smoothly down her back.");
	add_act("emote hums musically to herself.");
    add_act("emote folds her hands together.");
    add_act("emote whispers to herself and makes an upward gesture with "+
        "one of her fingers.");	
    add_act("emote looks out over the courtyard for a long moment.");
    add_act("smile polite");
    add_act("hmm");
    add_act("emote murmurs something that sounds like 'Let not the Other "+
        "see your innermost self, nor reveal unto him the divine "+
        "mysteries.'");
    
    set_chat_time(45);
    add_chat("There is little advantage in pleasing ourselves "+ 
        "if we please not the Gods.");
    add_chat("Beloved Patron, of my essence I give to you. "+
        "For you are enough to me, and I can do nothing "+
        "less that is not full worship of you. ");
    add_chat("No Sybarite doubts that he exists, nor does he doubt the "+
        "existence of the Gods." );
    add_chat("Our great and glorious destiny is to live as the Gods Will.");
    add_chat("Contemplate. Furious activity is no substitute for "+
        "understanding.");
    add_chat("Talk, turmoil and desire exist outside the veil. "+
        "Inside the veil is silence, calm, and peace.");
	
    set_default_answer("say You will have to find the answer to that "+
        "question another way. I mostly answer questions about the "+
        "gods.", 1);
		
    add_ask(({"task", "quest", "quests", "help" }), no_jobs, 1);

    add_ask("[about] 'oblate' [of] [salilus]",
        "say I have dedicated myself to the service of Salilus. "+
        "I am His oblate.", 1);

    add_ask("[about] 'anchorite' / 'anchorites' [of] [the] [hours]",
        "say Anchorites are clerics. We spend an hour each day in seclusion, "+
        "meditation, and prayer. This strengthens our connection to "+
        "the Gods, that we might perform wonders in their names.", 1);		
		
    add_ask("[about] [going] [to] / [into] [the] 'temple' / 'shrine'",
        "say The portal is still spinning. We are only allowed to "+
        "enter the shrine when it stops.", 1);
		
    add_ask(({"[about] [why] [is] [the] 'portal' / 'doorway' [spinning]"}),
        "say Salilus is the god of openings. He opens the way and he "+
        "closes it, too. When you see a doorway spining, it means "+
        "he has closed the way to where it leads. Be patient. "+
        "I'm sure the way into the shrine will re-open one day soon.", 1);

    add_ask(({"[about] [the] 'trefoil' [banner]"}), 
       "say The trefoil is the symbol of Sybarus, taken from the way the "+
       "Forbidden City was built: three enclaves, one for each High "+
       "Lord, and the intersection where they meet.", 1);

    add_ask(({"fights", "trouble", "gaol", "defenders", "guards"}),
        "say The defenders here are serious about their work. "+
        "If you start a fight at Fort Sybarus, they will toss "+
        "you into the gaol and leave you to rot there.", 1);
				
    add_ask("[about] [going] [to] [the] 'gaol'",
        "say Well now... There's no tolerance for fighting here, amongst "+
        "the guards or anyone else. If you start a brawl, you're going to "+
        "be hauled off to the gaol at the bottom of the north tower.", 1);

    add_ask("[about] [fighting] / [killing] / [brawling] / [brawl]",
        "If you start a fight here, we're going to assume you're an "+
        "enemy of Sybarus. You're going to end up in the gaol and that's "+
        "a very unpleasant place to be, if you ask me.", 1);		
  
	add_ask("[about] [who] [is] [your] 'patron' / 'god'", 
        "say My patron is Salilus, Lord of the First Hour.", 1); 
		
	add_ask("[what] / [about] [is] [a] 'gnorf' / 'gnorfling'", 
	    "say Gnorflings are surprisingly good-natured halflings, the "+
        "product of gnomes and dwarves interbreeding. Generally they "+
        "are considered to be a bit simple-minded, but every once "+
        "in a while one comes along who is shockingly smart.",1);
	
    add_ask("[about] [a] 'window' / 'windows' [to] [lean] [out] [of]", 
	    "say Windows, hmm?  Well the best view of Fort Sybarus is from "+
        "the third floor window of the south tower, near Dato the "+
        "barber.", 1);
		
    add_ask("[about] 'dato' / 'barber'", 
	    "say There's a barber up in the south tower. He's very popular "+
        "with the soldiers here, so you might have to wait. "+
		"Dato will have your facial hair beautifully styled "+
        "for a reasonable price.", 1); 
		
    add_ask("[about] [where] [is] [the] 'facial' 'hair' [stylist]", 
	    "say Dato the Barber is up in the south tower, near the big window."+
		"", 1);
		
    add_ask("[about] 'fort' [sybarus]",
	    "say Fort Sybarus was built to protect Sybarus from invasion.", 1);	
		
    add_ask("[about] 'mustache' / 'mustaches' / 'beard' / 'beards'",
        "say Don't the dwarves around here have splendid beards and "+
        "moustaches?  Dato the barber does wonderful work. Seeing it "+
        "almost makes me which elven-kind could grow facial hair.", 1); 
		
    add_ask("[about] / [where] [is] 'seaside' [town] [located]",
        "say Seaside is one of those secrets we've tried to keep from "+
        "outsiders, so forgive me if I don't give the location "+
        "away.", 1);	
	
	add_god_asks();	
}

// what's a good value for these guys?
int query_knight_prestige()
{
    return -100;
}

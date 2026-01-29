// Dwarven manager for the outpost
// creator(s):   Kazz   May 1995
// purpose:		run's the outpost.  Receiver for deliveries (Krynn)
//			    and will hand out quests.
// note:		lives in tower_office.c which is also a delivery office.
// bug(s):
// to-do:		* create more unique gear for this guy
// revisions:	Denis, May'96: Changed the location of intro.c
//			    Denis, Jul'96: Removed the usage of trig_new for intro.
//              Lilith, Apr 2022: updated asks.

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/sigil";
inherit "/d/Avenir/common/gods/god_asks";

#include "/d/Avenir/common/outpost/outpost.h"
#include <language.h>
#include <money.h>
#include </sys/ss_types.h>

string my_long();

void create_monster()
{
    if(!IS_CLONE)
       return;

    set_name("lyrouth");
    add_name(({"manager", "gnorfling", "lorent", "dwarf", "gnome"}));
	set_title("icu Hu'garen, Manager of Fort Sybarus and Head Banker");
	set_syb_house("hu'garen");
    set_race_name( "gnorf" );
    set_gender(G_MALE);
    set_adj( "muscular" );
    set_adj( "clever" );
    set_long(my_long);

    set_stats(({ 90, 90, 90, 90, 90, 90 }));
        
    set_alignment(0);
 
    set_skill( SS_DEFENSE, 80 );
    set_skill( SS_WEP_AXE, 80 );
	set_skill( SS_WEP_CLUB, 80 );
    set_skill( SS_BLIND_COMBAT, 60 );
    set_skill( SS_AWARENESS, 70 );
	add_prop(LIVE_I_SEE_DARK, 1); // So he can conduct business 

    set_act_time(17);
    add_act("emote paces briefly." );
    add_act("emote thoughtfully scratches his neatly-trimmed "+
        "red beard styled in ringlets.");
	add_act("emote tallies something up in a book.");
    add_act("emote flips a silver coin back and forth across "+
        "his knuckles.");
    add_act("emote chews briefly on his flowing flame red "+
        "handlebar mustache.");	
    add_act("emote squints his jewel-like green eyes at the ceiling.");
    add_act("smile polite");
    add_act("hmm");
    
    set_chat_time(10);
    add_chat("My favourite island is the Holm. I narrowly escaped being "+
        "killed there. It was thrilling!");
    add_chat("What can I do for you?" );
    add_chat("Packages, packages, packages." );
    add_chat("Amblo's gold made a lot possible.");
    add_chat("Mind your manners and stay out of fights or you're "+
        "going to end up in the gaol.");
    add_chat("That old Amblo was right. It takes money to make money.");
    add_chat("Things seem to be running smoothly, thankfully." );
	add_chat("Grouth ran things well for nearly a century. It was easy "+
        "to take on the role when he retired.");
    add_chat("Keeping all these dwarves fed takes expertise.");
	add_chat("I've a friendly word of advice for you: avoid fighting "+
        "while at Fort Sybarus.");
    
    set_cact_time(5+random(5));
    add_cact("emote says: You'll die.");
    add_cact("emote bellows in rage.");
    add_cact("emote shifts position to get a better hit." );
    add_cact("emote growls at you.");
    add_cact("emote growls: Fool, you'd better leave while you can." );

    set_default_answer("say No offence, but... it's probably not "+
        "something you should be inquiring with me about...", 1);
		
    add_ask( ({"task", "quest", "quests", "help", 
        "package", "packages" }), "@@no_jobs", 1);

    add_ask(({ "bank", "deposit", "money", "gold" }), 
        "@@bank_stuff", 1);

    add_ask(({"fights", "trouble", "gaol", "defenders", "guards"}),
        "say The defenders here are serious about their work. "+
        "If you start a fight at Fort Sybarus, they will toss "+
        "you into the gaol and leave you to rot there.", 1);
 
    add_ask(({"grouth", "father", "old banker", "manager"}),
        "say The old manager, Grouth, was my father. He retired and I've "+
        "taken over the job. How can I help you?", 1);

   add_ask("[about] [going] [to] [the] 'holm'",
        "say The Hegemon honored me with the opportunity to Hunt on the  "+
        "Holm. I almost died a few times fighting infidels, but I held my "+
        "own and returned with a panther's pelt, even.", 1);
		
    add_ask("[about] [going] [to] [the] 'gaol'",
        "say Well now... There's no tolerance for fighting here, amongst "+
        "the guards or anyone else. If you start a brawl, you're going to "+
        "be haulded off to the gaol at the bottom of the north tower.", 1);

    add_ask("[about] [fighting] / [killing] / [brawling] / [brawl]",
        "If you start a fight here, we're going to assume you're an "+
        "enemy of Sybarus. You're going to end up in the gaol and that's "+
        "a very unpleasant place to be, if you ask me.", 1);		
  
	add_ask("[about] [who] [is] / [was] [your] 'mother'", 
        "say My mother is Lyrisant, and yes, "+
	    "if my father, Grouth, is a dwarf, then she is a gnome.", 1); 
		
	add_ask("[what] / [about] [is] [a] 'gnorf' / 'gnorfling'", 
	    "say I bet you didn't think "+
        "dwarves and gnomes were compatible, but I'm proof they are!",1);
	
    add_ask("[about] [a] 'window' / 'windows' [to] [lean] [out] [of]", 
	    "say The windows here are small. "+
        "If you want a really good view of the fort, there's a big "+
        "window just one level down that you can lean out of.", 1);
		
    add_ask("[about] 'amblo' / 'amblos' [gold]", 
	    "say He's a friend of the family--explores "+
        "the Underdark with this pony and buys and sells goods. "+
		"I'm holding his gold for him nice and safe, just like yours. "+
        "Last I heard he was gathering info on the ogres.", 1); 
		
    add_ask("[about] [the] 'ogre' / 'ogres' [problem]", 
	    "say We've got an ogre problem. "+
        "Darn things feed on rats and breed just like them. When "+
        "they run out of stuff to eat they up rise through the Underdark "+
		"like turds in a chamberpot.", 1);
		
    add_ask("[about] [the] [managing] 'fort' [sybarus]",
	    "say Fort Sybarus was built to protect Sybarus from invasion. "+ 
        "I am in charge of keeping it supplied and keeping the accounts "+
        "in order.", 1);	
		
    add_ask("[about] [your]	'role' / 'job' / 'manager' / 'banker'/ 'duties'",
        "say I manage the non-military side of things here at the fort. "+
        "I help keep the defenders fed and armed -- and paid!", 1); 
		
    add_ask("[about] / [where] [is] 'seaside' [town] [located]",
        "say Seaside is one of those secrets we've tried to keep from "+
        "outsiders, so forgive me if I don't give the location "+
        "away.", 1);
	add_god_asks();	
}

string
my_long()
{
    string  str;

    str =  "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += "Not quite a dwarf and not quite a gnome, this fellow "+
	       "is a bit of both, known as a gnorf or gnorfling.\n"+
	       "He looks like he's quite important in these parts.\n"+
           "He appears to control the fort and its commerce.\n"+ 
           "He has a neatly-trimmed red beard styled in ringlets.\n"+ 
		   "He has a flowing flame red handlebar mustache.\n"+
           "He has jewel-like green eyes that follow your every move.\n"+
		   "He carries a steel war hammer in a sheathe at his side.\n"+
		   "He is wearing a green leather vest with brass buttons, a "+
           "long-sleeved white shirt, and pair of brown velvet trousers.\n";
    return str;
}

void equip_me()
{
    MONEY_MAKE_CC(22 + random(20))->move(this_object());
    MONEY_MAKE_SC(3 + random(15))->move(this_object());
} // equip_me()

string
bank_stuff()
{
    command("say That crazy gnome Amblo asked my father to hold on "+
        "to his money chest for him...seeing as he's down "+
        "Deep most of the time.");
    command("say Dad figured he'd keep myself honest and make "+
        "some money off of it.");
    command("say Do you need change?");
    return "";
} // bank_stuff


string
no_jobs()
{
    command( "say Maybe you have a package for me?" );
    command("say Or perhaps you could make a delivery for me?");
    return "";
} // no_jobs()


// what's a good value for these guys?
int query_knight_prestige()
{
    return -100;
}

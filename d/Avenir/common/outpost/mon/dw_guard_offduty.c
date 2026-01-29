// copy of dw_guard.c with some mods for "off-duty"
// Dwarven guard for the outpost gate
// creator(s):   Kazz   Jan 1995
// purpose:      dwarven guards (initially for the outpost)
// note:         These guards can be generic Avenir guards.  
//		 add_gate_talk() or set_fort_wander() are called for outpost.
// updates:      Lilith Oct 1998: code upgrade, cosmetic improvements.
//               Lilth Apr 2022: updates for mustaches and beards.
//                added chats and asks.

inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/death_crier";
inherit "/d/Avenir/common/outpost/mon/call_for_help";

#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/guilds.h"

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>

string *Sadj1 = ({ "angry","menacing","brutal","fierce","calm",
                   "flustered","efficient","trustworthy","jovial", 
                   "mean","anti-social","friendly","ill-tempered",
                   "sad","gruff","gentle","pensive","dutiful",
                   "proud", "rumpled", "faithful", "zealous",
                   "fanatical","serene","impressive","imposing"});
string *Sadj2 = ({ "deep-chested","long-armed","bandaged","limping",
                   "cold-eyed","muscular","sweaty","full-bearded",
                   "round-eyed","wild-eyed","sturdy","stocky","squat",
                   "one-eared","scar-faced","one-eyed","bearded", 
                   "ugly","swarthy","blue-eyed","long-haired","pale",
                   "short-legged","long-nosed","dark"}); 
string *Seyes = ({ "dark-brown","angry blue","dark green","leaf green",
                   "intense gray","thrilling black","serene blue",
                   "sparkling black","blue-black","coal-black",
                   "steel-gray","gray-green","nut-brown","pale gray",
                   "amber-yellow", "red-brown"});
string *Shair = ({ "gray-streaked","silver-streaked","ebony black",
                   "fiery-red","silky dark","silky black","jet black",
                   "orange","mahogany brown","deep red",
                   "light brown","chestnut brown","blue-black",
                   "golden brown","chocolate brown", "yellow" });
string *Sfhair = ({"well-groomed", "medium-length", "long", 
                   "very long", "waist-length","bushy",
                   "thick", "full", "flowing", "tidy",
                   "fabulous", "majestic", "magnificent"});
string *Stache = ({"walrus mustache", "handlebar mustache", 
                   "braided mustache", "horseshoe mustache" });
string *Sbrd = ({ "beard that is curly", "beard that is wavy", 
                 "beard that is wiry", "beard styled with ringlets",
                 "beard plaited into twin braids", "wizard beard",
                 "beard plaited into many braids", "pointed beard",
                 "beard that is free-flowing", "forked beard", 
                 "beard that is tied near the chin", 
                 "beard that tied near the end",
                 "beard that is forked and waxed into points" });				   
				   
				   
int alarm_id;
string eyes, hair, adj1, adj2, fhair, fhair2, mstache, brd;

string query_eyes()          {    return eyes;      }
void set_eyes(string str)    {    eyes = str;       }
string query_hair()          {    return hair;      }
void set_hair(string str)    {    hair = str;       }
string query_fhair()         {    return fhair;     }
void set_fhair(string str)   {    fhair = str;      }
string query_stache()        {    return mstache;   }
void set_stache(string str)  {    mstache = str;    }
string query_fhair2()        {    return fhair2;    }
void set_fhair2(string str)  {    fhair2 = str;     }
string query_brd()           {    return brd;       }
void set_brd(string str)     {    brd = str;        }

void equip_me();
void set_helper();
string my_long();
string ask_sober();
string ask_voloda();

/* Make each dwarf guard unique */
void
shape_me()
{
    set_adj(one_of_list(Sadj1));
    add_adj(one_of_list(Sadj2));
    set_eyes(one_of_list(Seyes));
    set_hair(one_of_list(Shair));
	set_fhair(one_of_list(Sfhair));
	set_fhair2(one_of_list(Sfhair));	
	set_stache(one_of_list(Stache));
    set_brd(one_of_list(Sbrd));
}

/* Create the dwarven guard */
void
create_monster()
{
    /* if I'm not a clone, do not proceed */
    if (!IS_CLONE)
        return;
    
    /* You're all individuals! */
    shape_me();
    set_name("defender");
    add_name("avenir_dwarf_id");
    add_name(({"guard", "faithful", "peacekeeper" }));
    set_pname("guards");
    add_pname("dwarves");
    set_race_name("dwarf");
    add_adj("off-duty");

    set_gender(G_MALE);
    set_alignment(0);

    set_long(my_long);

    set_stats(({ 60+random(60), 45+random(40), 90+random(30),
                 30+random(50), 30+random(50), 100+random(50) }));
        
    set_stat_extra(5, 100);
    set_skill(SS_WEP_SWORD, 60 + random (30));
    set_skill(SS_DEFENCE,   60 + random (30));
    set_skill(SS_PARRY,     60 + random (30));
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_WEP_AXE,   60 + random (30) );
    set_skill(SS_WEP_CLUB,  60 + random (30) );	
    set_skill(SS_WEP_POLEARM,  60 + random (30) );
    set_skill(SS_BLIND_COMBAT, 50 );
    set_scar(random(20));

    set_monster_home(OUTPOST + "fort2");

    // all guards will help each other.
    set_helper();

    add_prop(OBJ_M_HAS_MONEY, random(20) + 90);
    add_prop(LIVE_I_SEE_DARK, 1);

    /* Add_acts and the asks relating to them */
    set_act_time(3 + random(9));
    set_default_answer("@@default_ans");	
	add_ask("[for] [a] 'job' / 'help' / 'task' / 'quest'", 
		"say If I need help, I will ask you for it.", 1);
	add_ask("[open] [the] 'gate'", 
	    "say Just knock on it. If the guards up top "+
		"like the looks of you, they'll open it for you.", 1);
    add_ask("[about] [the] 'fort' [sybarus]",
	    "say Fort Sybarus was built soon after Salilus opened the "+
        "way into the Great Cavern and the life-saving light of the "+
        "Source. It exists to protect Sybarus from Outlanders and "+
		"invaders.", 1);	
    add_ask("[about] / [where] [is] 'seaside' [town] [located]",
        "say Seaside is one of those secrets we've tried to keep from "+
        "Outlanders, so forgive me if I don't give the location "+
        "away.", 1);
    add_ask("[about] [the] [armour] 'colour' / 'colours'", 
	    "say We come from different houses and those houses are associ"+
        "ated with different High Lords. Green is for the Lord High "+
        "Inquisitor, red is for the Lord High Executioner, and "+
        "purple is for the Lord High Commissioner.", 1);
		
    add_ask("[about] [the] [burning] 'pool' / 'pools'",
        "say They're pools of oil that we use for light so we can see "+
        "all the way to the other side of the abyss. And they do have a "+
        "secondary function of deterring invaders.", 1);		
    add_ask("[about] [the] 'invaders'",
        "say We've got invaders trying to get past the gates all the time. "+
        "Sometimes it's Outlanders but mostly its dark elves or the "+
        "occasional deep ogre.", 1);
    add_ask("[about] [the] [dark] / [deep] 'elves' / 'ogre' / 'ogres'",
        "say We've got invaders trying to get past the gates all the time. "+
        "Sometimes it's Outlanders but mostly its dark elves or the "+
        "occasional deep ogre.", 1);		
    add_act("say The people of Sybarus sleep peacefully in their beds "+
	    "because we stand ready to defend them.");
    add_act("say Discipline is the soul of our defence.");
    add_act("say We live in a world that has walls and those walls "+
        "are guarded by dwarves with weapons at the ready.");
	
	add_act("say If a dwarf hasn't discovered something that he is "+
        "willing to die for, he isn't fit to live.");
	add_ask(({"[what] [are] [you] [willing [to] 'die' [for]"}), 
		"say I am willing to die for Sybarus, should the Gods "+
        "require it. What are YOU willing to die for?", 1);
	
    add_act("say Cowardly outlanders and infidels die manytimes "+
        "before their deaths; we Defenders of Sybarus taste "+
        "death but once -- and then we are gathered to Mascarvin's "+
        "bosom for a well-earned rest.");
	add_ask("[about] [the] [goddess] 'mascarvin' [bosom]", 
	    "say Those who die in the God's good graces are gathered "+
		"up by Mascarvin and nurtured until our rebirth.", 1);	
		
    add_act("say I should get to the Shrine soon, and make an "+
        "offering to Salilus and Sair.", 1);	
    add_ask("[about] 'shrine'", 
        "say The shrine is in the east part of Fort Sybarus, near "+
        "the forge complex.", 1);
    add_ask("[about] 'salilus'",
	    "say He is the god of the First Hour. He is the one who made "+
		"the opening for the first of us to make our way into the "+
        "Great Cavern. Fort Sybarus was built in that opening.", 1);
    add_ask("[about] 'sair'",
        "say Sair is the goddess of the First Hour. By Her Will, our "+
        "walls remain strong and intact.", 1);
		
    add_act("say When my stint is over and I get my pay, I'm "+
        "headed for the meadery to drink my fill!");
    add_ask(({"[about] [the] 'mead' / 'meadery'"}),
        "say Oh the Seaside Meadery and Alehouse offers the best "+
        "mead. You really should try it!", 1);		
		
	add_act("say Would you look at that! I've got a chip in my "+
        "armour! Time to go see Voloda.");
	add_ask("[who] [is] 'voloda'",            "@@ask_voloda@@");
	add_ask("[about] 'voloda' / 'painter' / 'paint'",    
        "@@ask_voloda@@");
    add_ask("[about] [where] [is] [the] [gear] 'painter' / 'voloda'",
    	"@@ask_voloda@@");
	add_ask("[about] 'fix' / 'fixing' 'chip' / 'chips'",
        "@@ask_voloda@@");
		
    add_act("say Is your sweetheart meeting you at the fountain "+
        "in Seaside at the 12th Hour too?");
    add_ask("[about] [the] 'fountain' [in] [seaside]",
        "say There is a green with a fountain in the center, a water-"+
        "clock really, down in Seaside. It is a lovely place, "+
        "Seaside is.", 1);		
		
    add_act("emote grumbles: Any dwarf worth his beard serves at "+
        "Fort Sybarus when summoned. It is my pleasure and my "+
        "privilege to serve. But requiring sobriety the whole time? "+
        "That's just cruel.");
    add_ask("[about] 'sobriety'",      "@@ask_sober@@");		
    add_ask("[about] [being] 'sober'", "@@ask_sober@@");		
    add_ask("[about] '448'",           "@@ask_sober@@");		
    add_ask("[about] 'alcohol'",       "@@ask_sober@@");
	
    add_act("emote looks really grumpy for a long moment");	
    add_ask("[about] [why] [are] [you] [so] 'grumpy'", "@@ask_sober@@");		
		
    add_act("say Aye, looking forward to getting home to the missus "+
        "and my wee ones. And my barrel of mead.");       
    add_act("say The food at the dining hall would taste better "+
        "with beer or mead to wash it down with, you know what "+
        "I mean?");
    add_act("emote makes a few practice swings with his weapon.");
    add_act("emote drops to the ground and does a few pushups, "+
        "then bounces back to his feet.");
    add_act("emote freezes suddenly, his whole body taking a "+
        "listening posture.");
    
    add_ask("[about] [where] [can] [i] [get] [a] 'beard' / 'mustache'",
        "say Oh there is a barber named Dato down in Seaside town. "+
        "He did the braid for my beard. Do you like it?", 1);	
    add_act("emote fiddles with his beard.");
    add_act("emote twirls his mustache.");
    add_act("emote coughs into his beard.");	
    add_act("emote sneezes and then wipes off his mustache and beard.");
	
    set_cact_time(3);
    add_cact("emote grumbles: You will die." );
    add_cact("emote says: The Source gives me strength you can't imagine.");
    add_cact("emote says: I will enjoy presenting your heart to the Shadow Elves!" );
    add_cact("emote growls at you.");
    add_cact("emote growls: You better leave while you can." );

	
    
} // create_monster()

string
my_long()
{
    string  str, poss;
    poss = TO->query_possessive(); 

    str =  "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += "He is a typical specimen of male sybarite dwarves, "+
           "being paler of coloring and less bellicose than his "+
           "surface-dwelling brethren.\n"+
           "He appears to be a guard, charged with holding this "+
           "fort.\n"+ 
           capitalize(TO->query_pronoun()) +" has "+ query_eyes()+ 
           " eyes that follow your every move.\n"+
		   "He is obviously off-duty, because instead of wearing "+
           "his beard in a battle-braid, he has a "+ query_fhair() 
		   +" "+ query_hair() +" "+ query_brd() +".\n"+
		   "He has a "+ query_fhair2() +" "+ query_hair() +
		   " "+ query_stache() +".\n";

    return str;
}

void
equip_me ()
{
    int which_weapon; // 66-33 split favouring hammers
    
    which_weapon = random(3);
    if (which_weapon > 1)
        add_weapon(OBJ +"dw_rhammer");
    else
        add_weapon(OBJ + "dw_raxe");
    
    add_armour(OBJ + "dw_rchain");
    /* full hitp, mana, fatigue */
    refresh_living();

} // equip_me()

void
set_fort_wander()
{
    set_restrain_path( OUTPOST + "fort" );
    set_monster_home( OUTPOST + "fort1" );  
    set_random_move( 10+random(25) );
} // set_fort_wander()


// all these guards will help in a fight
void set_helper()
{
    string *actions = ({"shout Guards! Help me!",
		        "shout Hold strong! I'm coming!",
		            "say You will die for this!"});

    set_helper_friends( ({"guard", "helper", "sybarite"}) );	
    set_helper_actions( actions );
} // set_helper()

string ask_voloda()
{
    command("say Voloda is a talented painter. She uses gemstone "+
        "dust and minerals to make durable paints for our gear "+
        "so we can keep them in perfect shape.");		
	return "";
} // ask_voloda
	
string ask_sober()
{
	command("rolleyes");
	command("say A long time ago, back in 448, some dwarves "+
        "stationed at Fort Sybarus had too much to drink and "+
		"some dark elf filth tricked them into helping him "+
        "attack the Academy of Defense.");
    command("emote looks embarassed.");
    command("say It was a huge mess, as I'm sure you can imagine, "+
        "and ever since, we're not allowed a drop of alcohol "+
        "consumption while stationed at Fort Sybarus, on penalty "+
        "of death.");
    command("say It's like having to give up mother's milk!");
    command("say But the alternative was banishment of dwarven-"+
        "kind from Sybarus--and we didn't want to die out like "+
        "the hobbits did. So... we go without for a couple of "+
        "Wei.");
   command("shrug sheepish");
	return "";
} // ask_sober

/*
 * Function name: default_ans
 * Description  : Gives the default answer to asked questions
 * Returns      : ""
 */
string 
default_ans()
{
    switch(random(5))
    {
    case 0:
        command("emote appears to be focussed on something.");
        break;
    case 1:
        command("say Ask someone else...");
        break;
    case 2:
        command("emote glances aside as if looking for help.");
        break;
    case 3:
        command("emote looks irritated.");
        command("say That knowledge is above my pay grade.");
        break;
    case 4:
        command("emote frown.");
        command("say Your accent is too thick for me to understand.");
        break;
    }
    return "";
} // default_ans

/*
 * check_meet enables the npc to greet players it
 * comes into contact with.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i = random(10);
    alarm_id = 0;

    if (!present(tp, environment(TO)))
        return;

    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        if (i == 2)
            command("bow deep "+ tp->query_real_name());
        if (i == 4)
            command("say to "+ tp->query_real_name() +" I am "+
                "honoured by your presence!");
        if (i == 6)
            command("say to "+ tp->query_real_name() +" I can "+
                "assure you that everything is under control.");
        return;
    }
    if (IS_INFIDEL(tp))
    {        
        if (i < 6)
        {
            command("emote squints at you.");
            command("shout Infidel!");
            command("kill "+ tp->query_real_nme());
        }
        return;
    }    
    if (IS_DANCER(tp))
    {
        if (i == 0)
            command("whistle admir "+ tp->query_real_name());
        if (i == 6)
            command("bow gallant to "+ tp->query_real_name());
            return;
    }       
    else
    {
        if (i == 5)
            command("say to "+ tp->query_real_name() + " "+
               "Be you friend or foe?");
            command("say to "+ tp->query_real_name() + " "+
               "If friend, welcome. If foe, leave.");
        if (i == 9)
            command("say to "+ tp->query_real_name() + " "+
               "All are welcome who respect the peace.");
            return;
    }
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        if (alarm_id)
            return;
        alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
    }
}  

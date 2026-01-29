/* 08 Sept 2003 - Palmer fixed double adjective bug i.e. no more 'hapy happy female hobbit'  */

#pragma strict_types
#pragma save_binary

inherit "/d/Shire/hobbitmaker/team";
inherit "/std/act/attack";
inherit "/d/Shire/hobbitmaker/names";

#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/lib/goodkill.h"
#include "tobacco.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>

#define NUM_TYPES 8  /* Number of types of Hobbitmaker hobbits */
#define HOBBIT_WEP  HOBBITMAKER_DIR + "wep/"
#define HOBBIT_ARM  HOBBITMAKER_DIR + "arm/"
#define HOBBIT_OBJ  HOBBITMAKER_DIR + "obj/"

// Allowable types of hobbits to be set with set_type when cloning
// MILITA and SHIRRIFFE types are always male MAIDEN type is always female
//   All other types are randomly set to female or male
#define CHILD      0
#define TWEENS     1
#define FARMER     2
#define CITIZEN    3
#define ELDER      4
#define MILITA     5
#define SHIRRIFFE  6
#define MAIDEN     7

// Arrays storing weapons and armours according to 'type'
#define TWEENS_WEP ({"cknife","h_dagger","h_knife"})
#define FARMER_WEP ({"pitchfork","shovel"})
#define ELDER_WEP  ({"h_staff"})
#define GUARD_WEP   ({"h_spear","hickclub","rapier","sgauche","shortsword"})
#define CITIZEN_WEP ({"cknife","h_club","h_dagger","h_flail",\
         "h_knife","h_pole","h_staff","hickclub","rapier"})
#define POOR_ARM ({"h_cloak","h_robe","h_shirt","h_tunic","hat","pants"})
#define AVG_ARM  ({"h_robe","h_tunic","hat","leggings","lshirt","pants",\
        "scloak"})
#define GOOD_ARM ({"coat","lshirt","pants","scloak","leggings"})

// Array storing miscellaneous items found on hobbits

// Function prototypes
void get_soul();
nomask void disable_all_noise();
nomask void disable_noise();
nomask void disable_cnoise();
nomask public void set_hobbit_type();
nomask public void set_hobbit_stats(int level);
nomask public void set_hobbit_skills();
string hobbit_chats();
string hobbit_cchats();
string hobbit_acts();
string hobbit_cacts();
void introduce_hobbit(string who);
void arm_hobbit();
string get_adjective();

// Global Vars
int npc_power, ran_num, npc_type;
string family_name;
string adj1="";

void create_hobbit() {}

nomask void
create_shire_monster()
{
    if (!IS_CLONE)
	return;
    ran_num = 1 + random(10);
    npc_type = -1;

    set_name("hobbit");
    add_name("_hobbitmaker_hobbit");
    set_long("@@hobbit_long@@");
    set_title("");
    set_race_name("hobbit");
    set_adj(({get_adjective(), get_adjective()}));
    set_stats(({ 50, 50, 50, 50, 50, 50 }));
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_HEIGHT,   500);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_S_WIZINFO,"This hobbit was created using the Hobbitmaker.  "+
      "To learn more about the Hobbitmaker, ask a Shire wiz, or RTFSC. "+
      "\nIgneous.\n");

    this_object()->add_subloc("_hobbit_feet",this_object());

    set_chat_time(5+random(5));
    add_chat("@@hobbit_chats@@");
    set_act_time(5+random(5));
    add_act("@@hobbit_acts@@");
    set_cchat_time(7);
    add_cchat("@@hobbit_cchats@@");
    set_cact_time(5);
    add_cact("@@hobbit_acts@@");
    create_hobbit();
    set_alarm(0.2,0.0,get_soul);
}

void
get_soul()
{
    setuid(); seteuid(getuid());
    add_cmdsoul("/d/Shire/hobbit/hobbit_soul");
    update_hooks();
}


//  All hobbits will have a family name even if you don't set it *grin*
nomask public void
set_title(string title)
{
    if (!family_name)
	family_name = get_family_name();
    if (!title || title == "")
	::set_title(family_name);
    else
	::set_title(family_name + ", " + title);
}

nomask public string
query_family_name()
{
    return family_name;
}

nomask public void
set_family_name(string name)
{
    string *arr = explode(query_title(), ",");

    family_name = CAP(name);
    arr[0] = family_name;
    if (sizeof(arr) ==  1)
	::set_title(arr[0]);
    else
	::set_title(implode(arr, ","));
}

nomask public int
query_hobbit_type()
{
    return npc_type;
}

public string
get_adjective()
{
    string *adjectives, adj;

    adjectives = ({"sandy-haired","proud","merry","smiling","aging", "bouncy",
      "nimble","cheerful","blue-eyed","curly-haired","chatty","small","good-natured",
      "friendly","sharp-eyed","green-eyed","hungry","jolly","sleepy","short",
      "chatty","mischievous","brown-eyed","round-faced","ruddy-faced","happy",
      "tired","agile","jolly","energetic","cheerful","nimble","inquisitive","jovial",
      "tricky", "sneaky"});

    if (!query_gender()) // add gender based adjectives
	adjectives += ({"drunken","silly","boisterous","sturdy","fat","chubby",
	  "strong","slim","eager"});
    else
	adjectives += ({"slender","sweet","gentle","crass","dainty","kindly",
	  "chatty","talkative","plump","passive"});
    adj = adjectives[random(sizeof(adjectives))];
    // Make sure we don't have first and second adj duplicated
    while (adj == adj1)
    {
        adj = adjectives[random(sizeof(adjectives))];
    }
    adj1 = adj;
    return adj;
}

public string
hobbit_long()
{
    string str;

    str = (TP->query_met(TO) ? TO->query_met_name() : "The "+TO->query_nonmet_name());

    switch(npc_type)
    {
    case -1:
	str += " isn't really a hobbit...  Some silly wizard "+
	"seems to have forgotten to set this hobbit right.\nPlease make "+
	"a bug report about this.\n";
	break;
    case CHILD:
	str += " looks up at you with the staring eyes of a child.\n";
	break;
    case TWEENS:
	str += " looks like "+HE_SHE(TO)+" is barely in "+HIS_HER(TO)+" tweens.\n";
	break;
    case FARMER:
	str += " has the sturdy looks of a hobbit which farms the lands.\n";
	break;
    case CITIZEN:
	str += " is a typical hobbit citizen of the Shire.\n";
	break;
    case ELDER:
	str += " has the look of wisdom in "+HIS_HER(TO)+" eyes, a wisdom which "+
	"is only learned through age.\n";
	break;
    case MILITA:
	str += " is a member of the local hobbit milita, responsible for the "+
	"well being of the local citizens.\n";
	break;
    case SHIRRIFFE:
	str += " is one of the Shires shirriffes.  "+CAP(HE_SHE(TO))+" is the "+
	"responsible for keeping law and order in this part of the Shire.\n";
	break;
    case MAIDEN:
	str += " is a typical hobbit citizen of the Shire.\n";
	break;
    }
    return str;
}

public string
show_subloc(string subloc, object on, object for_who)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != "_hobbit_feet")
        return ::show_subloc(subloc, on, for_who);
    if (on != for_who)
    {
	return CAP(HE_SHE(TO)) + " has extremely "+
	"furry feet.\n";
    }
    return "";
}

public void
add_introduced(string name)
{
    set_alarm(2.0,0.0,&introduce_hobbit(name));
}

void
introduce_hobbit(string who)
{
    object obj;

    if (query_attack())
    {
	if (query_attack()->query_real_name() == lower_case(who))
	    command("say I wouldn't introduce myself to a murdering "+
	      query_attack()->query_race_name()+" like you!");
	else
	    command("say I'm busying defending myself from "+
	      query_attack()->query_nonmet_name()+" at the moment... "+
	      "Perhaps you can help me drive the hobbit murderer off?");
	return;
    }
    if (interactive(obj = present(who, environment())))
    {
	command("say Hullo there, my name is "+query_name()+" "+CAP(family_name)+".");
	switch (random(4))
	{
	case 0:
	    command("say Nice to meet you "+obj->query_name());
	    break;
	case 1:
	    command("greet "+who);
	    break;
	case 2:
	    command("say How do you do, kind "+obj->query_race_name());
	    break;
	case 3:
	    command("say Have we met before?");
	    break;
	}
    }
}

nomask void
disable_all_noise()
{
    disable_noise();
    disable_cnoise();
}

nomask void
disable_noise()
{
    clear_chat();
    set_chat_time(10000);
    clear_act();
    set_act_time(10000);
}

nomask void
disable_cnoise()
{
    clear_cchat();
    set_cchat_time(10000);
    clear_cact();
    set_cact_time(10000);
}

nomask public void
set_power(int level)
{
    if(level > 200)
    {
	level = 200;
    }

    set_hobbit_stats(level);
}

nomask public void
set_hobbit_stats(int level)
{
    int   *npc_stats,
    initial_stat,
    is;

    initial_stat = level / 2;

    npc_stats = allocate(6);

    npc_stats[0] = initial_stat - (ran_num * 3);   // STR
    npc_stats[1] = initial_stat + (ran_num * 5);   // DEX
    npc_stats[2] = initial_stat - (ran_num * 2);   // CON
    npc_stats[3] = initial_stat - ran_num;         // INT
    npc_stats[4] = initial_stat + ran_num;         // WIS
    npc_stats[5] = initial_stat + ran_num;         // DIS

    for (is = 0; is < 6; is++)
    {
	if (npc_stats[is] < 10)
	    npc_stats[is] = 10;
    }

    set_stats(npc_stats);
    set_alarm(0.5,0.0,&set_hobbit_skills());
    REFRESH;
}


nomask public void
set_hobbit_skills()
{
    int     ran_num2,
    npc_stat_avg = query_average_stat(),
    mod_skills,
    com_skill,
    spe_skill,
    gen_skill;

    ran_num2 = random(6) + 5;

    set_alignment(250 + 2 * npc_stat_avg);

    if(npc_stat_avg > 50)
    {
	mod_skills = npc_stat_avg/3 + 100;
    }
    else
    {
	mod_skills = npc_stat_avg * 2;
    }

    com_skill = mod_skills * 50 / 100;
    spe_skill = mod_skills * 45 / 100;
    gen_skill = mod_skills * 55 / 100;

    if(spe_skill > 70)
	spe_skill = 70;
    else if(spe_skill < 5)
	spe_skill = 5;
    if (npc_type == 5 || npc_type == 6) // Fighting hobbits like militia
	spe_skill += 15;

    if(com_skill > 60)
	com_skill = 60;
    else if(com_skill < 5)
	com_skill = 5;
    if (npc_type == 5 || npc_type == 6) // Fighting hobbits like militia
	com_skill += 15;

    if(gen_skill > 80)
	gen_skill = 80;
    else if(gen_skill < 10)
	gen_skill = 10;

    set_skill(SS_WEP_SWORD,spe_skill + random(5));
    set_skill(SS_WEP_KNIFE,spe_skill + random(5));
    set_skill(SS_WEP_POLEARM,spe_skill + random(5));
    set_skill(SS_WEP_CLUB,spe_skill - 20);
    set_skill(SS_WEP_AXE,spe_skill - 10);
    set_skill(SS_WEP_MISSILE,spe_skill + random(10) + 10);
    set_skill(SS_PARRY,com_skill + random(5));
    set_skill(SS_DEFENCE,com_skill + random(5));
    set_skill(SS_SNEAK,gen_skill + random(5));
    set_skill(SS_HIDE,gen_skill + random(5));
    set_skill(SS_AWARENESS,gen_skill + random(5));
    set_skill(SS_HERBALISM,gen_skill + random(10));
    set_skill(SS_ACROBAT,gen_skill + random(5));
    arm_hobbit();
}

void
arm_hobbit()
{
    string *filenames = ({});
    int arm_num;
    setuid(); seteuid(getuid());

    if (npc_type > 0)  //  Hobbit children have no money or pipe-weed
    {
	MAKE_MONEY;
	clone_tobacco();
    }
    switch(npc_type)
    {
    case CHILD:
	return;
    case TWEENS:
	filenames += ({HOBBIT_WEP + ONE_OF_LIST(TWEENS_WEP)});
	break;
    case FARMER:
	filenames += ({HOBBIT_ARM + ONE_OF_LIST(AVG_ARM)});
	filenames += ({HOBBIT_WEP + ONE_OF_LIST(FARMER_WEP)});
	break;
    case MAIDEN:
    case CITIZEN:
	if (random(3))
	    filenames += ({HOBBIT_ARM + ONE_OF_LIST(POOR_ARM)});
	else
	    filenames += ({HOBBIT_ARM + ONE_OF_LIST(AVG_ARM)});
	filenames += ({HOBBIT_WEP + ONE_OF_LIST(CITIZEN_WEP)});
	break;
    case ELDER:
	filenames += ({HOBBIT_ARM + ONE_OF_LIST(POOR_ARM)});
	filenames += ({HOBBIT_WEP + ONE_OF_LIST(ELDER_WEP)});
	break;
    case MILITA:
	filenames += ({HOBBIT_ARM + ONE_OF_LIST(GOOD_ARM)});
	filenames += ({HOBBIT_WEP + ONE_OF_LIST(GUARD_WEP)});
	break;
    case SHIRRIFFE:
	filenames += ({HOBBIT_ARM + ONE_OF_LIST(GOOD_ARM)});
	filenames += ({HOBBIT_WEP + ONE_OF_LIST(GUARD_WEP)});
	break;
    }
    if (sizeof(filenames))
	add_equipment(filenames);

    //  Normal citizens don't go around not wielding weapons
    if (npc_type != MILITA && npc_type != FARMER && npc_type != SHIRRIFFE)
	command("unwield all");
}

nomask public void
set_type(int some_num)
{
    if(some_num < 0 || some_num > NUM_TYPES)
	some_num = 0;

    npc_type = some_num;

    set_hobbit_type();
}

nomask public void
set_hobbit_type()
{
    set_gender(random(2));  //  Could be male or female
    switch(npc_type)
    {
    case CHILD:
	add_name("child");
	break;
    case TWEENS:
	add_name("tween");
	break;
    case FARMER:
	add_name("farmer");
	break;
    case CITIZEN:
	add_name("citizen");
	break;
    case ELDER:
	add_name("elder");
	break;
    case MILITA:

	add_name("milita");
	set_gender(0);  // Hobbit milita were typically male
	break;
    case SHIRRIFFE:
	add_name("shirriffe");
	set_gender(0); //  Hobbit Shirriffes were typically male
	break;
    case MAIDEN:
	add_name("maiden");
	set_gender(1); //  This is a female hobbit
	break;
    }
    if (!query_gender())
	set_name(get_male_name());
    else
	set_name(get_female_name());

    set_adj(({get_adjective(),get_adjective()}));
}

string
hobbit_chats()
{
    if (query_attack())
	return hobbit_cchats();

    switch(npc_type)
    {
    case -1:
	return "I'm buggy, please make a bug report about me.";
    case CHILD:
	switch(random(4))
	{
	case 0:
	    return "I love playing games!";
	case 1:
	    return "I am scared of orcs!";
	case 2:
	    return "Have you seen my mommy?";
	case 3:
	    return "Today is my birthday!";
	}
	break;
    case TWEENS:
	switch (random(5))
	{
	case 0:
	    return "I love hearing stories!";
	case 1:
	    return "I am scared of orcs.";
	case 2:
	    return "One day I plan on going adventuring.";
	case 3:
	    return "I don't remember seeing you around here before, "+
	    "you must be a stranger to these parts.";
	case 4:
	    return "My uncle says he saw a walking tree outside the " +
	    "Shire, but I don't believe him.";
	}
	break;
    case FARMER:
	switch (random(8))
	{
	case 0:
	    return "Working the fields is hard, but I am harder.";
	case 1:
	    return "No good children....They are always taking strawberries "+
	    "from my garden!";
	case 2:
	    return "I raise cattle and reap the harvest of the land.";
	case 3:
	    return "Lovely day isn't it?";
	case 4:
	    return "I hope it rains soon. My fields need to be watered.";
	case 5:
	    return "Last year was not a good year for my crops.";
	case 6:
	    return "I worked all day and boy, am I tired.";
	case 7:
	    return "Those pesky birds keep destroying my crops!";
	}
	break;
    case CITIZEN:
	switch (random(12))
	{
	case 0:
	    return "How are you today?";
	case 1:
	    return "I bet you've seen some strange things while "+
	    "adventuring....";
	case 2:
	    return "A lot of strange people have been passing through "+
	    "here lately. I wonder why?";
	case 3:
	    return "Nothing beats "+(present("tobacco",ENV(TO)) ?
	      present("tobacco",ENV(TO))->query_flavour() :
	      "longbottom leaf")+" tobacco!";
	case 4:
	    return "There seems to be a storm brewing in the east...";
	case 5:
	    return "The party last night was wonderful! I have never "+
	    "eaten so much in my life.";
	case 6:
	    return "Where do your adventures take you today?";
	case 7:
	    return "The Shire is full of wonderful places to visit.";
	case 8:
	    return "Southfarthing grows the best pipeweed.";
	case 9:
	    return "Can you believe the bad weather we've been having?";
	case 10:
	    return "The best things in life are pipeweed and a " +
	    "good hot meal.";
	case 11:
	    return "I'd rather be home having a hot meal and a cold beer " +
	    "than standing here waiting for my sister.";
	}
	break;
    case ELDER:
	switch (random(5))
	{
	case 0:
	    return "I have seen many adventurers pass through "+
	    "here in my day.";
	case 1:
	    return "I'd have to say "+(present("tobacco",ENV(TO)) ?
	      present("tobacco",ENV(TO))->query_flavour() :
	      "longbottom leaf")+" tobacco, is the finest the Shire "+
	    "has ever produced.";
	case 2:
	    return "That "+(family_name == "took" ? CAP(get_family_name()) :
	      "Took")+ " family is a strange one.";
	case 3:
	    return "Have you ever been to Bree..strange happenings go on "+
	    "there";
	case 4:
	    return "Those Tooks are a strange breed.";
	}
	break;
    case MILITA:
    case SHIRRIFFE:
	switch (random(6))
	{
	case 0:
	    return "The Shire has been filled with troublemakers as of late.";
	case 1:
	    return "The orcs seem to get closer and closer to the town "+
	    "everyday....";
	case 2:
	    return "These latest reports worry me.";
	case 3:
	    return "Beware of orcs stranger.";
	case 4:
	    return "If you travel, beware of bandits.";
	case 5:
	    return "They say strange things are afoot in the Shire.";
	}
	break;
    case MAIDEN:
	switch (random(4))
	{
	case 0:
	    return "Now where did "+CAP(get_male_name())+" go?  It's time "+
	    "for him to come home for dinner.";
	case 1:
	    return "Hullo there, how are you doing today?";
	case 2:
	    return "Do you have any stories about your adventures "+
	    "to tell me?";
	case 3:
	    return "I can't wait till the next party is thrown...will "+
	    "be hard to outdo that last one!";
	}
	break;
    }
    return "Hurry up and make some chats for me you lazy wizard!";
}

string
hobbit_acts()
{
    if (query_attack())
	return hobbit_cacts();

    switch(npc_type)
    {
    case -1:
	return "emote is buggy.";
    case CHILD:
	switch(random(7))
	{
	case 0:
	    return "yawn";
	    break;
	case 1:
	    return "sniff";
	case 2:
	    return "sigh tired";
	case 3:
	    return "dance all";
	case 4:
	    return "emote scratches " + HIS_HER(TO) + " feet.";
	case 5:
	    return "tickle all";
	case 6:
	    return "smile mischeviously";
	}
	break;
    case TWEENS:
	switch(random(5))
	{
	case 0:
	    return "sing";
	case 1:
	    return "dance all";
	case 2:
	    return "emote looks around for someone to play with.";
	case 3:
	    return "smile foolish";
	case 4:
	    return "emote scratches " + HIS_HER(TO) + " feet.";
	}
	break;
    case FARMER:
	switch(random(7))
	{
	case 0:
	    return "emote tends "+ HIS_HER(TO) +" fields "+
	    (sizeof(query_weapon(-1)) ? "with "+ HIS_HER(TO) +" "+
	      query_weapon(-1)[0]->short() : "") + ".";
	case 1:
	    return "smile tired";
	case 2:
	    return "stretch";
	case 3:
	    return "peer frant";
	case 4:
	    return "emote scratches " + HIS_HER(TO) + " feet.";
	case 5:
	    return "sigh tired";
	case 6:
	    return "emote examines the sky for a change in weather.";

	}
	break;
    case CITIZEN: case MAIDEN:
	switch(random(6))
	{
	case 0:
	    return "emote rubs "+HIS_HER(TO)+" tummy.";
	case 1:
	    return "twiddle";
	case 2:
	    return "smile cheerful";
	case 3:
	    return "emote "+(sizeof(query_armour(-1)) ? "straightens "+
	      HIS_HER(TO)+" "+ query_armour(-1)[0]->short() +"." :
	      "fixes "+HIS_HER(TO)+" hair.");
	case 4:
	    return "grin sheepishly";
	case 5:
	    return "emote scratches " + HIS_HER(TO) + " feet.";
	}
	break;
    case ELDER:
	switch(random(5))
	{
	case 0:
	    return "emote "+(present("tobacco",TO) ? "stuffs some "+
	      present("tobacco",TO)->short()+" into "+HIS_HER(TO)+" pipe "+
	      "and starts to smoke it." : "fidgets in "+HIS_HER(TO)+
	      " pockets looking for some tobacco.");
	case 1:
	    return "emote eyes light up as "+HE_SHE(TO)+" smiles at you.";
	case 2:
	    return "stretch";
	case 3:
	    return "emote starts to ramble on about when "+HE_SHE(TO)+
	    " was your age and the adventures that "+HE_SHE(TO)+" had.";
	case 4:
	    return "emote scratches " + HIS_HER(TO) + " feet.";
	}
	break;
    case MILITA:
	switch(random(6))
	{
	case 0:
	    return "emote "+(sizeof(query_weapon(-1)) ? "polishes "+HIS_HER(TO)+
	      " "+query_weapon(-1)[0]->short()+"." : "stands at "+HIS_HER(TO)+
	      " post.");
	case 1:
	    return "emote "+(sizeof(query_armour(-1)) ? "attends to "+
	      HIS_HER(TO)+" "+query_armour(-1)[0]->short()+" with pride "+
	      "and skill." : " searches "+HIS_HER(TO)+" pockets for some "+
	      "pipe-weed.");
	case 2:
	    return "twiddle";
	case 3:
	    return "peer suspiciously";
	case 4:
	    return "emote scratches " + HIS_HER(TO) + " feet.";
	case 5:
	    return "emote examines you carefully.";
	}
	break;
    case SHIRRIFFE:
	switch(random(5))
	{
	case 0:
	    return "emote "+(sizeof(query_weapon(-1)) ? "polishes "+HIS_HER(TO)+
	      " "+query_weapon(-1)[0]->short()+"." : "stands at "+HIS_HER(TO)+
	      " post.");
	case 1:
	    return "emote "+(sizeof(query_armour(-1)) ? "attends to "+
	      HIS_HER(TO)+" "+query_armour(-1)[0]->short()+" with pride "+
	      "and skill." : " searches "+HIS_HER(TO)+" pockets for some "+
	      "pipe-weed.");
	case 2:
	    return "emote looks you over carefully.";
	case 3:
	    return "emote stretches "+HIS_HER(TO)+" tired legs.";
	case 4:
	    return "emote scratches " + HIS_HER(TO) + " feet.";
	}
	break;
    }
    return "emote tells you to make "+HIM_HER(TO)+" some acts.";
}


string
hobbit_cchats()
{
    if (!query_attack())
	return hobbit_chats();

    switch(npc_type)
    {
    case -1:
	return "I'm buggy for some reason, please make a bug report about this.";
    case CHILD:
	switch(random(4))
	{
	case 0:
	    return "Help! Help!";
	case 1:
	    return "Leave me alone you big meanie!";
	case 2:
	    return "Mommy!!!  I want my mommy!!!";
	case 3:
	    return "I want my mommy!!";
	}
	break;
    case TWEENS:
	switch(random(6))
	{
	case 0:
	    return "Leave me alone you bully!";
	case 1:
	    return "Ouch that hurt!";
	case 2:
	    return "Please leave me alone "+query_attack()->query_nonmet_name()+
	    ", I have done nothing to you!";
	case 3:
	    return "What have I done to you to deserve this?";
	case 4:
	    return "You aren't fighting fairly!";
	case 5:
	    return "This isn't a fair fight!";
	}
	break;
    case FARMER:
	switch(random(3))
	{
	case 0:
	    return "I am going to have to teach you a lesson with my "+
	    (!sizeof(query_weapon(-1)) ? ("bare hands") :
	      query_weapon(-1)[0]->short())+", my dear "+
	    query_attack()->query_nonmet_name()+"!";
	case 1:
	    return "Cease this senseless violence at one!";
	case 2:
	    return "Please be sensible "+query_attack()->query_nonmet_name()+".";
	}
	break;
    case CITIZEN:
	switch(random(7))
	{
	case 0:
	    return "I am poor and don't have a coin, please leave me alone.";
	case 1:
	    return "Please don't kill me "+query_attack()->query_nonmet_name()+
	    ".  I have a "+(query_gender() ? ("husband") : "wife")+
	    " and four children!";
	case 2:
	    return "Where are the guards?";
	case 3:
	    return "Help! Help! The Shire is under attack!";
	case 4:
	    return "Just wait until the guards come!";
	case 5:
	    return "Stop! Stop!";
	case 6:
	    return "This isn't a fair fight!";

	}
	break;
    case ELDER:
	switch(random(6))
	{
	case 0:
	    return "I hope Gandalf will cast you into the void one day!";
	case 1:
	    return "I am old, please leave me be, foul "+
	    query_attack()->query_nonmet_name()+".";
	case 2:
	    return "Please cease this senseless act!";
	case 3:
	    return "Help!! Help!! I'm being repressed!";
	case 4:
	    return "Didn't your mother teach you better manner than this?";
	case 5:
	    return "Stop this at once, or I shall have to get meaner!";

	}
	break;
    case MILITA:
	switch(random(5))
	{
	case 0:
	    return "You are under arrest, foul "+query_attack()->query_race_name()+
	    "!  Please come quietly!";
	case 1:
	    return "You will answer for your crimes!";
	case 2:
	    return "Lay down your "+(!sizeof(query_attack()->query_weapon(-1))
	      ? ("arms") : (query_attack()->query_weapon(-1)[0]->short()))+
	    " and come quietly!";
	case 3:
	    return "You will pay for this!";
	case 4:
	    return "Take that, you son of a flea-bitten orc!";
	}
	break;
    case SHIRRIFFE:
	switch(random(5))
	{
	case 0:
	    return "Lay down your "+(!sizeof(query_attack()->query_weapon(-1))
	      ? ("arms") : (query_attack()->query_weapon(-1)[0]->short()))+
	    " and come quietly!";
	case 1:
	    return "You are under arrest "+query_attack()->query_nonmet_name()+
	    " for attacking defenseless hobbits!";
	case 2:
	    return "My dear "+query_attack()->query_nonmet_name()+", I am "+
	    "going to have to teach you a lesson or two with my "+
	    (!sizeof(query_weapon(-1)) ? ("bare fists") :
	      query_weapon(-1)[0]->short())+"!";
	case 3:
	    return "I'm a Shirriffe of the Shire, I order you to cease this "+
	    "attack at once!";
	case 4:
	    return "Take that, you son of a flea-bitten orc!";
	}
	break;
    case MAIDEN:
	switch(random(5))
	{
	case 0:
	    return "Why are you attacking me "+query_attack()->query_nonmet_name()+
	    "? I've done nothing to you!";
	case 1:
	    return "Please spare me "+query_attack()->query_nonmet_name()+"!  "+
	    "I don't want my children to grow up without a mother!";
	case 2:
	    return "Please end this senseless act, now!";
	case 3:
	    return "Where is the Shirriffe when you need him?";
	case 4:
	    return "My boyfriend will beat you up if you don't stop now!";
	}
	break;
    }
    return "Hurry up and make some combat chats for me!";
}

string
hobbit_cacts()
{

    if (!query_attack())
	return hobbit_acts();

    switch(npc_type)
    {
    case -1:
	return "is buggy.";
    case CHILD:
	switch(random(4))
	{
	case 0:
	    return "sob";
	case 1:
	    return "cry";
	case 2:
	    return "whine";
	case 3:
	    return "scream";
	}
	break;
    case TWEENS:
	switch(random(4))
	{
	case 0:
	    return "shout For all the "+family_name +
	    (extract(family_name, -1) == "s" ? "" : "s" )+" in the Shire!";
	case 1:
	    return "sigh";
	case 2:
	    return "shout Call the milita, I'm being attacked by an evil "+
	    query_attack()->query_nonmet_name()+"!!";
	case 3:
	    return "emote tries to run away.";
	}
	break;
    case FARMER:
	switch(random(3))
	{
	case 0:
	    return "slap "+query_attack()->query_real_name();
	case 1:
	    return "shout For the Shire!";
	case 2:
	    return "grumble";
	}
	break;
    case CITIZEN: case MAIDEN:
	switch(random(4))
	{
	case 0:
	    return "shout For all of the "+family_name+
	    (extract(family_name, -1) == "s" ? "" : "s" )+" in the Shire!";
	case 1:
	    return "emote pleads for "+HIS_HER(TO)+" life.";
	case 2:
	    return "grumble";
	case 3:
	    return "shout Help!  Murderer!!  Guards!!! Guards!!!";
	}
	break;
    case ELDER:
	switch(random(4))
	{
	case 0:
	    return "shout Help!! Help!! This no good "+
	    query_attack()->query_nonmet_name()+" is trying to kill me!!";
	case 1:
	    return "emote screams in horror!";
	case 2:
	    return "emote begs to be spared.";
	case 3:
	    return "emote pleads for "+HIS_HER(TO)+" life.";
	}
	break;
    case MILITA:
	switch(random(4))
	{
	case 0:
	    return "shout For the Shire!";
	case 1:
	    return "shout Over here!!  That "+query_attack()->query_race_name()+
	    " that has been killing hobbits is fighting me!";
	case 2:
	    return (!sizeof(query_weapon(-1)) ? ("grumble") :"emote tightens "+
	      HIS_HER(TO)+" grip on "+HIS_HER(TO)+" "+
	      query_weapon(-1)[0]->short()+".");
	case 3:
	    return "emote calls for help.";
	}
	break;
    case SHIRRIFFE:
	switch(random(4))
	{
	case 0:
	    return "shout For the Shire!!";
	case 1:
	    return (!sizeof(query_weapon(-1)) ? ("grumble") :"emote tightens "+
	      HIS_HER(TO)+" grip on "+HIS_HER(TO)+" "+
	      query_weapon(-1)[0]->short()+".");
	case 2:
	    return "emote attacks with renewed vigour.";
	case 3:
	    return "shout You will pay for your crimes "+
	    query_attack()->query_nonmet_name()+"!";
	}
	break;
    }
    return "emote asks you to make some combat acts for "+HIM_HER(TO)+".";
}


int
special_attack(object enemy)
{
    int     npc_dex =  query_stat(SS_DEX)/4;
    int     npc_miss = query_skill(SS_WEP_MISSILE)/4;
    int     npc_str =  query_skill(SS_STR)/3;
    mixed   *hitresult;
    string  *how = allocate(2), wep;

    if (npc_type == CHILD || npc_type == -1)
	return 0;
    if (npc_type != MILITA && npc_type != SHIRRIFFE) // Milita attack differently
    {
	if (random(8))
	    return 0;

	hitresult = enemy->hit_me(F_PENMOD(npc_dex+npc_miss, query_skill(SS_WEP_MISSILE)),
	  W_BLUDGEON, TO, -1);

	switch (hitresult[0])
	{
	case -1:
	    how[0] = "You hear the stone whistle harmlessly by you.";
	    how[1] = "The stone whistles harmlessly by "+QTNAME(enemy)+".";
	    break;
	case 0:
	    how[0] = "The stone hits you without harm.";
	    how[1] = "The stone hits "+QTNAME(enemy)+" without harm.";
	    break;
	case 1..10:
	    how[0] = "The stone hits you lightly.";
	    how[1] = "The stone hits "+QTNAME(enemy)+" lightly.";
	    break;
	case 11..20:
	    how[0] = "The stone hits you with a solid thump.";
	    how[1] = "The stone hits "+QTNAME(enemy)+" with a solid thump.";
	    break;
	case 21..35:
	    how[0] = "The stone hits you hard, leaving a small bruise.";
	    how[1] = "The stone hits "+QTNAME(enemy)+" hard.";
	    break;
	default:
	    how[0] = "The stone pummels you, leaving a deep, painful bruise!";
	    how[1] = "The stone pummels "+QTNAME(enemy)+", leaving what looks "+
	    "to be a rather painful bruise.";
	    break;
	}

	// Send no messages to the npc
	if (enemy->query_hp() <= 0)
	{
	    enemy->catch_msg(QCTNAME(TO)+ " throws a stone at your head, hitting "+
	      "it so hard that the blow knocks you senseless!\n");
	    TO->tell_watcher(QCTNAME(TO)+ " throws a stone at "+QTNAME(enemy)+"'s "+
	      "head, the blow knocks "+QTNAME(enemy)+" senseless!\n",enemy);
	    enemy->do_die(TO);
	    return 1;
	}
	if (enemy->query_wiz_level())
	    enemy->catch_msg(hitresult[3] + " damage was done.\n");
	enemy->catch_msg(QCTNAME(TO)+" throws a stone at your "+hitresult[1]+
	  "!\n" + how[0] + "\n");
	TO->tell_watcher(QCTNAME(TO)+" throws a stone at "+QTNAME(enemy)+"'s "+
	  hitresult[1] + "!\n" + how[1] + "\n",enemy);
	if (hitresult[1] == "head")
	    enemy->add_attack_delay(5 + random(6) , 1);
	return 1;
    }
    if (random(5))
	return 0;
    if (!sizeof(query_weapon(-1)))
	return 0;

    wep = query_weapon(-1)[0]->short();

    hitresult = enemy->hit_me(F_PENMOD(npc_dex + npc_str +
	query_weapon(-1)[0]->query_pen(), 65), W_IMPALE, TO, -1);

    switch (hitresult[0])
    {
    case -1:
	how[0] = QCTNAME(TO)+"'s "+wep+" missed you completely.";
	how[1] = QCTNAME(TO)+"'s "+wep+" misses "+QTNAME(enemy)+" completely.";
	break;
    case 0:
	how[0] = QCTNAME(TO)+" swings "+HIS_HER(TO)+" "+wep+" dangerously "+
	"close to your "+hitresult[1]+".";
	how[1] = QCTNAME(TO)+" swings "+HIS_HER(TO)+" "+wep+" dangerously "+
	" close to "+QTNAME(enemy)+"'s "+hitresult[1]+".\n" ;
	break;
    case 1..10:
	how[0] = QCTNAME(TO)+"'s "+wep+" barely scratches your "+hitresult[1]+".";
	how[1] = QCTNAME(TO)+"'s "+wep+" barely scratches "+QTNAME(enemy)+
	"'s "+hitresult[1]+".";
	break;
    case 11..20:
	how[0] = QCTNAME(TO)+"'s "+wep+" barely pierces your "+hitresult[1]+".";
	how[1] = QCTNAME(TO)+"'s "+wep+" barely pierces "+QTNAME(enemy)+"'s "+
	hitresult[1]+".";
	break;
    case 21..35:
	how[0] = QCTNAME(TO)+" pierces your "+hitresult[1]+" deeply with "+
	HIS_HER(TO)+" "+wep+".";
	how[1] = QCTNAME(TO)+" pierces "+QTNAME(enemy)+"'s "+hitresult[1]+
	" deeply with "+HIS_HER(TO)+" "+wep+".";
	break;
    default:
	how[0] = QCTNAME(TO)+" rips open a bleeding wound in your "+hitresult[1]+
	" with "+HIS_HER(TO)+" "+wep+".";
	how[1] = QCTNAME(TO)+" rips open a bleeding wound in "+QTNAME(enemy)+
	"'s "+hitresult[1]+" with "+HIS_HER(TO)+" "+wep+".";
	break;
    }

    // Send no messages to the npc
    if (enemy->query_hp() <= 0)
    {
	enemy->catch_msg(QCTNAME(TO)+ " lunges towards you with "+HIS_HER(TO)+
	  " "+wep+" leaving you mortaly wounded.\n");
	TO->tell_watcher(QCTNAME(TO)+ " lunges towards "+QTNAME(enemy)+" "+
	  "with "+HIS_HER(TO)+" "+wep+", mortaly wounding "+QTNAME(enemy)+"!\n",
	  enemy);
	enemy->do_die(TO);
	return 1;
    }
    if (enemy->query_wiz_level())
	enemy->catch_msg(hitresult[3] + " damage was done.\n");
    enemy->catch_msg(QCTNAME(TO)+" lunges towards your "+hitresult[1]+
      " with "+HIS_HER(TO)+" "+wep+"!\n" + how[0] + "\n");
    TO->tell_watcher(QCTNAME(TO)+" lunges towards "+QTNAME(enemy)+"'s "+
      hitresult[1] + " with "+HIS_HER(TO)+" "+wep+"!\n" + how[1] + "\n",enemy);
    return 1;
}

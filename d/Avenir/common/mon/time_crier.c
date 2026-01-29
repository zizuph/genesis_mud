// Town Crier   /d/Avenir/common/mon/time_crier.c
// creator(s):  Lilith  Jan 99
// last update: 
// purpose:     Various routines Patrolling different areas.
// note:	Criers are under supervision of the Commissioner.
// bug(s):
// to-do:

#pragma strict_types

inherit "/d/Avenir/inherit/spy_npc";
inherit "/d/Avenir/inherit/avenir_time";

#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/guilds.h"

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>

/* Use these to determine movement routines, if any, in the
 * set_walk and init_where_i_walk functions
 */
#define TEST         0
#define NONE         1
#define W_BAZAAR     2
#define W_ENTRY      3
#define W_OUTPOST    4
#define W_TRIBUNAL   5
#define W_VILL_STR   6

string *Sadj1 = ({"courteous","polite","cordial","gracious","avid",
                  "keen","fervent","dedicated","solicitious",
                  "dignified","solemn","droll","dashing","intrepid",
                  "prudent","dauntless"});
string *Seyes = ({"dark-brown","pale blue","jade green","leaf green",
                  "dove gray","captivating black","serene blue",
                  "grave black","blue-black","cinnamon brown",
                  "entrancing gray","gray-green", "blue-green"});
string *Shair = ({"gray-streaked","caramel-coloured","ebony black",
                  "fiery-red","silky dark","silky black","curly dark",
                  "pale corn-silk","wavy brown","mahogany brown",
                  "light brown","chestnut brown","blue-black",
                  "deep auburn","chocolate brown" });

int walk;

string eyes, hair, adj1, swho;
string my_long();

string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
string query_swho()   {    return swho;      }

int    query_walk()   {    return walk;      }

void   set_eyes(string str)   {    eyes = str;      }
void   set_hair(string str)   {    hair = str;      }
void   set_swho(string str)   {    swho = str;      }

void   init_where_i_walk();
void   test_environs();

/* set_walk controls if and where the monster walks, using 
 * the numbers defined above. If you don't set it, the 
 * init_where_i_walk will default to 0= NONE (stay where cloned)
 */
void set_walk(int i)     {    walk = i;      }

/*
 *  The various routes the npcs walk, depending on location.
 *  Add new ones below. Always use seq_addfirst("crying" .. );
 *  as shown below, since the seq_new function called by the 
 *  init_where_i_walk is always "crying".
 */
int
bazaar_route()
{   // BAZAAR: assumes str11.c as starting point
    seq_reset();        
    seq_addfirst ("crying",
       ({ "smile polite", "s", "ask guard How is the knee?",5,
          "e", 5, "e", "n", 5, "emote stares up at the Source.", 
          "n", "e", "e", 2, "bow respect guard", "s", "s", 2,
          "w", "w", "n", "n", "w", 4, "laugh at nygel",
          "w", "s", 2, "@@bazaar_route@@"}) );
    return 0;
}

int 
entry_route()
{
    /* Assumes /d/Avenir/common/city/entry/courtyard.c as start */
    seq_reset();
    seq_addfirst("crying",
       ({ "smile polite", "whisper defender How is the knee?", 5,
          "w", 5, "emote stares up at the Source.", 5, "sit bench", 
          2, "stretch", 2, "stand", "w", 5, "emote leans against "+
          "the dark stone wall.", 5, "e", 2, "e", "bow respect all", 
          3, "blue", "greet overseer", 2, "whisper overseer love "+
          "your hair", 5, "w", 2, "@@entry_route@@"}) ); 
    return 0;
}

int
tribunal_route()
{   // TRIBUNAL
    return 0;
}

int
outpost_route()
{   // Outpost
    return 0;
}


int 
v_street_route()
{
    // Village
    return 0;
}

/*
 *   Test where I am located, so I know the route I must walk.
 */
void
test_environs()
{
    string str;    
    str = file_name(environment(this_object()));

    if (str == "/d/Avenir/common/outpost/")
    {
        set_walk(W_OUTPOST);
        init_where_i_walk();
        return;
    }
    if (str == "/d/Avenir/common/city/entry/courtyard")
    {
        set_walk(W_ENTRY);
        init_where_i_walk();
        return;
    }
    if (str == "/d/Avenir/common/bazaar/extr/")
    {
        set_walk(W_BAZAAR);
        init_where_i_walk();
        return;
    }
    if (str == "/d/Avenir/common/bazaar/admin/")
    {
        set_walk(W_TRIBUNAL);
        init_where_i_walk();
        return;
    }
    if (str == "/d/Avenir/common/village/street/")
    {
        set_walk(W_VILL_STR); 
        init_where_i_walk();
        return;
    }
    else
    {
        set_walk(NONE);       
        init_where_i_walk();
    }   
}

/*
 *  The int set_walk() determines the course of walking.
 *  If it is not set when this function is called, the 
 *  course will be determined by test_environs() and then
 *  the npc sent on his or her way by calling the seq_new.
 */
void 
init_where_i_walk()
{
    int    i;
    string str;

    i = query_walk();



    switch(i)
    {
        case  0:  test_environs();        break;
        case  1:  /* stay where cloned */ break;    
        case  2:  bazaar_route();         break;
        case  3:  entry_route();          break;
        case  4:  outpost_route();        break;
        case  5:  tribunal_route();       break;      
        case  6:  v_street_route();       break;      
        default: break;
    }
    if (i > 1)
        seq_new ("crying", 1); // never stop
}


/*
 *  This gets the time from the avenir_time object and returns the
 *  get_time_text string.
 */
string 
tell_time()
{
    command("shout It is currently the "+ get_time_text() +".");
    return "";
}

/*
 * We are masking this function from the avenir_time.c
 * It notifies us of the change of hours once every hour.
 */
public void
avenir_time_callout(int av_year,int av_week_of_year,int av_dow,int av_hour)
{
    /* This will tell the time every hour */  
    command("shout It is currently the "+ get_time_text() +".");
}

/* 
 * set_morph sets the various attributes of the 
 * npc, making it unique several different ways.
 */
void
set_morph()
{
    int i;

    i = random(4);
    if (i > 2)
        set_race_name("half-elf");
    else
        set_race_name("human");       

    set_adj(Sadj1[random(sizeof(Sadj1))]);
    set_eyes(Seyes[random(sizeof(Seyes))]);
    set_hair(Shair[random(sizeof(Shair))]);
    set_gender(random(2));
}

/* Create the npc */
void
create_monster()
{
    /* If I'm not a clone, do not proceed */
    if (!IS_CLONE)
        return;

    /* initialize spy npc functions */
    ::create_monster();

    /* Synchronize clock */
    start_avtime();

    /* You're all individuals! */
    set_morph();

    set_name("crier");
    add_adj("officious");
    set_long(my_long);
    add_name(({"timekeeper","official","sybarite","faithful",
        "town crier", "time crier"}));
    set_alignment(0);

    set_knight_prestige(-1);   

    MAKE_SYBARITE; 
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_skill(SS_DEFENCE, random(20) + 40);
    set_skill(SS_WEP_POLEARM, random(20) + 40);
    set_skill(SS_AWARENESS, random(40)+ 40);
    set_skill(SS_WEP_KNIFE, random(20) + 40);
    set_skill(SS_BLIND_COMBAT, random(20)+ 40);
    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(15);
    set_appearance_offset(-10); // always good-looking

    default_config_npc(random(60) + 60);

    set_chat_time(3);
      add_chat("If you want to know the time, just ask.");
      add_chat("There is no greater joy than pleasing the Gods.");
      add_chat("Its been a fairly uneventful day, praise the Gods.");

    set_act_time(2);
      add_act("sigh slow");
      add_act("emote smiles engagingly.");
      add_act("emote appears to be observing you with studied nonchalance.");
      add_act("emote checks to make sure that "+ POSSESS(TO) +" tunic "+
          "is smooth and unwrinkled.");
      add_act(VBFC_ME("tell_time"));

    set_cact_time(7);
      add_cact("glare enemy");
      add_cact("say I serve the Commissioner. I will be avenged.");
      add_cact("say Your corpse will be goblin-feed!");

    set_default_answer(VBFC_ME("what_me"));
      add_ask(({"time", "tell time", "what is the time", "what time is it"}),
        VBFC_ME("tell_time"));
      add_ask(({"what has occurred", "what has occured"}),
        VBFC_ME("ask_about_encountered"), 1);
      add_spy_ask();
}

string
my_long()
{
    string  str, sHis, sHe;
    sHis =TO->query_possessive(); 
    sHe  =TO->query_pronoun();
    str =  capitalize(sHe) +" is "+ 
           LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += capitalize(sHe)  +" is a town crier.\n"+
           capitalize(sHis)  +" job is to announce "+
           "the Hour and other important events in Sybarus.\n"+
           capitalize(sHis) +" skin has that pale, translucent "+
           "quality characteristic of most sybarites.\n"+
           capitalize(sHis) +" shoulder-length, "+ query_hair() +
           " hair is held at "+ sHis +" nape by a gold trefoil clasp.\n"+
           capitalize(sHe)  +" has observant "+ query_eyes() +" eyes.\n";
    return str;
}

/*
 * equip_me is called in the npc when it is cloned by the 
 * placer module.
 */
void 
equip_me()
{
    object shirt, pants, cloak, dagger;

    seteuid(geteuid(this_object()));

    cloak = clone_object(BAZAAR + "Obj/worn/mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    shirt = clone_object(BAZAAR + "Obj/worn/menshirts");
    shirt->create_tailored();
    shirt->move(TO, 1);

    pants = clone_object(BAZAAR + "Obj/worn/menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    dagger = clone_object(COM +"obj/knife");
    dagger->move(TO);
    
    command("wear all");
    command("wield all");

    /* Full health, mana, etc */
    refresh_living();

    /* Npc should be cloned to room now, 
     * let's initialize its walk route.
     */
    set_alarm(5.0, 0.0, &test_environs()); 
}

string
give_task()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks around suspiciously");
        command("say The air speaks, yet not in the voice of a "+
            "God.");
        command("say You are the spawn of a coward and a thief!");
        return "";
    }
    if (IS_SYBARITE(TP))
    {
        command("say to "+ TP->query_real_name() + 
            " I require no assistance.");
        return "";
    }
    if (IS_INFIDEL(TP))   
    {
        command("say What are you doing here, you infidel scum?");
        command("shout GUARDS!");
        return "";
    }
}

string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks warily about.");        
        return "";
    }
    switch(random(4))
    {
        case 0:
            command("say I am only permitted to answer questions "+
                "relating to my position as Town Crier.");
            break;
        case 1:
            command("say Harassing a town crier is a crime, you know.");
            break;
        case 2:
            command("say If you want to know the time, ask. If you "+
               "want to know what has occurred today, ask. Just do "+
               "not trouble me about anything else.");
            break;
        case 3:
            command("say I do not know.");
            break;
    }
    return "";    
}

void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(6);
    alarm_id = 0;

    if (!present(tp, environment(TO)))
        return;

    if (IS_INFIDEL(TP))
    {
        command("to "+ tp->query_real_name() +
            "I see the mark of Plalgus upon you, infidel!");
        return;
    }
    if (IS_SYBARITE(tp))
    {
        command("say to "+ tp->query_real_name() +
            " May you please the Gods in all you do.");
        return;
    }
    else
    {    
        if (i > 3)
        {
            command("say to "+ tp->query_real_name() +
                " Hail and well-met, Outlander.");
            return;
        }
        command("bow . all");
        return;
    }
}

string 
query_exp_title()
{
    return "sybarite";
}

string 
race_sound()
{
    return "asserts";
}

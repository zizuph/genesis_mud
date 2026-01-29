//-*-C++-*-
// file name:    Female Albi  /d/Avenir/common/dark/mon/albus_f.c
// creator(s):   Casca, 11/26/99
// purpose:      Populate the underdark
// note:         
// bug(s):       
// to-do:        

inherit "/d/Avenir/inherit/monster.c";
#include "/d/Avenir/common/common.h"
#include </sys/ss_types.h>

#define FIXEUID   setuid(); seteuid(getuid())

string *randadjl;
string *randadjs;
string albus_long();

void
create_monster()
{
    if(!IS_CLONE)
       return;

    randadjl = ({"ugly", "large", "gangly", "red-eyed",
                 "short", "stumpy", "long-haired", "slender", 
                 "bald", "short-legged", "white-haired",
                 "long-nosed","pink-skinned"});

    randadjs = ({"pregnant", "quiet", "bruised", "smiling", "calm", 
                 "unhappy", "jovial", "sad", "downcast"});

    ::create_monster();

    set_name("albus");
    add_name("avenir_albus_id");
    set_race_name("albus");
    set_gender(G_FEMALE);
    set_adj(randadjs[random(sizeof(randadjs))]);
    add_adj(randadjl[random(sizeof(randadjl))]);

    set_long(albus_long);

    set_stats(({ 40+random(10), 45+random(10), 50+random(20),
                 20+random(10), 20+random(10), 50+random(20) }));
 

    set_skill(SS_DEFENCE, 40 + random (30));
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_BLIND_COMBAT, 80 );
    set_skill(SS_UNARM_COMBAT, 50 );

    if (TO->query_adj() == "pregnant")
    {
        add_leftover("/d/Avenir/inherit/leftover", "fetus",1, "", 0,0);
        set_alignment(800);       /*To punish good people who kill her. */
        set_knight_prestige(-2);
        set_m_in("waddles");
        add_act("emote rubs her huge belly.");
        add_act("emote wraps her arms about her swollen belly.");
        add_cact("say Please no hurt my baby!");
        add_cact("emote covers her swollen belly with her arms.");
        add_ask(({"baby", "pregnant"}),
            "say I'm so happy to make a baby, The Odd one say that each "+
            "little one makes us stronger.", 1);
    }

    NEVERKNOWN;

        set_act_time(6 + random (6));
    add_act("smiles shyly");
    add_act("emote stirs the contents of a pot over a fire.");
    add_act("sigh .");
    add_act("yawn");
    add_act("stretch");
    add_act("drop baby");
    add_act("get baby");
    add_act("@@stock_fire@@");
    add_act("emote rocks back and forth.");
    add_act("peer curiously goblin");
    add_act("emote stares into the fire.");
    add_act("point human");
    add_act("whisper avenir_albus_id Whos the ugly one?");
    add_act("say Why you here?");
    add_act("say Go away.");

        set_cact_time(9 + random (20));
    add_cact("whimper");
    add_cact("spit enemy");
    add_cact("scream");
    add_cact("cry");
    add_cact("glare angr enemy"); 
    add_cact("say The Odd one will destroy you!");

    add_ask(({"odd-one","Odd_one","oddone","Oddone","odd one","Odd one",
        "leader","massive red-eyed albus", "massive albus"}),
        "say He is our leader, he make us able to fight back against "+
        "the large ones.", 1);
    add_ask(({"cavern", "home"}),
        "say The Odd one find this place for us and make it our home "+
        "he teach us how to live better.", 1);
    add_ask(({"trash","tunnel","junk"}),
        "say Our leader tell us to put all the trash away from "+
        "our home. But its to dangerous to go very far away.", 1);
    add_ask(({"miners","trolls","foreman","foremen","shadow-elves"}),
        "say We use things they no longer want, good tools for "+
        "for breaking rocks and food they dont need.", 1);

    if (random(3))
        clone_object("/d/Avenir/common/dark/mon/baby")->move(TO, 1);
}

string
albus_long()
{
    string  str;

    /* Adding the adjectives to the long */
    str =  capitalize(this_object()->query_pronoun()) +" is "+ 
           LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += "She looks something like a female goblin, but her skin is a very pale "+
           "white tinged with a hint of pink.\n"+
           "She is much more fragile looking than her male counterparts, but "+
           "a force to be reckoned with when defending her young.\n";
    return str;
}

public void
stock_fire()
{
    object *all;
    int i;

    all = all_inventory(environment(this_object()));
    for (i=0; i<sizeof(all); i++) 
    {
        if (all[i]->query_prop(OBJ_I_HAS_FIRE)) 
           continue;
        if (function_exists("create_torch", all[i])) 
        {
            all[i]->reset_torch();
            command("emote stocks the campfire.");
            command("light all");
            return;
        }
    }
}

public void
add_introduced(string name)
{
    command("shrug uncar");
}


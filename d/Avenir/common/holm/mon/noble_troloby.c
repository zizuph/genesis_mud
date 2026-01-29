/* file name:        /d/Avenir/common/holm/t_camp/noble_troloby.c
 *  creator(s):      (Rangorn , Feb 97)
 *  revisions:
 *  purpose:         
 *  note:             
 *  bug(s):
 *  to-do:
 */                                                                            
inherit "/std/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/helper";

#include "../holm.h"
#include <ss_types.h>

#define FIXEUID     setuid(); seteuid(getuid())

/* Prototypes.
*/
string troloby();
string hunt();
string nemur();
string scar_ask();
string give_quest();
string no_reward();
string my_long();
/*
 * Function name: create_monster()
 */
void create_monster()
{
    set_name("jen'Zanur");
    set_race_name("troloby");
    add_name(({"jenzanur", "jen'zanur"}));
    set_gender(G_NEUTER);
    set_adj("vigorous");
    set_adj("proud");
    set_long(my_long);   
    set_stats( ({100,120,100,110,110,110}) );
  
    set_alignment(0);
  
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENSE, 60);
    set_skill(SS_PARRY, 70 + random(20));
    set_skill(SS_WEP_POLEARM, 70 + random(20));
    set_skill(SS_BLIND_COMBAT, 40);

    set_act_time(5);
    add_act("emote looks down on you with proud fiery-red eyes.");
    add_act("emote glares at you almost as if assessing you.");
    add_act("smirk");
    add_act("think something serious.");
    add_act("emote looks up at the Source and mumbles something.");
  
    set_cact_time(6);
    add_cact("emote sneers at you");
    add_cact("emote says: So the shadow-elves have sent you to kill me.");
    add_cact("emote says: So you are willing to wager the ultimate prize.");
  
    add_ask( ({"help", "quest", "task"}) , give_quest,1);
    add_ask( ({"troloby","trolobys"}), troloby,1);
    add_ask( ({"reward"}), no_reward,1);
    add_ask( ({"scar", "cheek"}), scar_ask, 1);
    add_ask( ({"hunt"}), hunt,1);
    add_ask( ({"nemur","wizard", "master"}), nemur,1);    
//    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    FIXEUID;
}           

string
my_long()
{
    return "This is a vigorous proud troloby.\n"+
           "Despite its giant stature, the features of its count"+
           "enance are human, and so perfect they would seem to "+
           "be chiseled from marble by a great sculptor.\n"+
           "You can see blood pulsating beneath the badly-healed, "+
           "hideous scar which ruins the perfection of its right cheek.\n"+
           "Its skin is so pale a pink it is almost white.\n"+
           "Its eyes are proud and fiery-red.\n";

}

void equip_me()
{
    clone_object(HOLM_OBJ + "nt_wep")->move(this_object());
    clone_object(HOLM_OBJ + "nt_armour")->move(this_object());
    clone_object(HOLM_OBJ + "nt_helm")->move(this_object());
    command("wear all");
    command("wield all");
} 

string give_quest()
{
    command("smirk");
    command("say Don't insult me! You can't help me.");
    return "";
}  

string no_reward()
{
    command("say What do you want to be rewarded for?");
    command("say Not getting yourself killed yet?");
    return "sigh";
}                                    

string scar_ask()
{
    command("say It is a gift from Nemur, a reminder of my place.");
    command("emote smiles meaningfully at you.");
    return "";
}

string troloby()
{
    command("hmm");
    command("say We are creatures of Nemur, his attempts at creation.");
    command("say Most of us are bred here, some are permitted to leave "+
          "in service to the Shadow-elves.");
    return "sigh .";
}

string hunt()
{
    command("say So you have come to the Holm for the Hunt?");
    command("say Be careful, or I'll give you one.");
    return "grin wick";
}

string nemur()
{
    command("say He is the Master of the troloby encampment.");
    command("say He is a powerful wizard who considers himself so " + 
           "superior that he is all but a God.");
    command("say One might think it was heresy, but he lives, so "+
           "his Patron is indeed powerful.");
    command("say Nemur's genius is matched only by his insanity.");
    return "spit";
}


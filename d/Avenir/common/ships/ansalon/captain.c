// -*-C++-*-
// name: Captain /d/Avenir/common/ships/ansalon/captain.c
// creator(s):   
// last update:  
// purpose:      Ship Captain for the Odalisque
// note:         
// bug(s):
// to-do:
// revision:     

#include "/d/Avenir/common/ships/ship.h"
#include "/sys/cmdparse.h"
#define ETO      environment(this_object())
#define ATICKET  ANSA_DIR + "ticket"
#define APRICE   12

#pragma save_binary

inherit "/d/Genesis/ship/captain";
inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";

private void call_demon();
private void equip_me();
private int no_demon = 0;
private object demon;

void
create_monster()
{
    if (!IS_CLONE)
      return;
    set_name("tibalsek");
    add_name("captain");
    set_title("Adriel ini Hu'garen, Captain of the Odalisque");
    set_living_name("tibalsek");
    set_race_name("gnome");
    set_adj(({"wiry", "sun-bronzed"}));
    set_long("@@my_long");
    set_stats(({ 80, 60, 90, 80, 60, 70 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_WEP_SWORD,75);
    set_skill(SS_DEFENCE,75);
    set_skill(SS_PARRY,75);
    set_skill(SS_AWARENESS,50);
    set_appearance_offset(-10); // always 'handsome' 
    set_alignment(-100+random(200));

    add_prop(LIVE_I_SEE_DARK, 80);
    add_prop(OBJ_I_RES_MAGIC, 50);
    add_prop(OBJ_I_RES_FIRE, 50);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
    set_act_time(10);   
      add_act("grumble");
      add_act("smile");
      add_act("grimace");
      add_act("emote props himself against the rudder and contemplates "+
          "the lateen sails.");
      add_act("emote looks worriedly out to sea.");
      add_act("emote shades his eyes with his hand.");
      add_act("emote licks his sunburned lips.");
      add_act("chuckle");

    set_chat_time(5);
      add_chat("Travelling by sea is a solitary journey of the spirit.");
      add_chat("Another year or two of this and I'll have earned enough "+
          "rank to raise myself to icu in House Hu'garen.");
      add_chat("The Blue Dragonarmy has control of Balifor, now. "+
          "They make it difficult to earn an honest living from the "+
          "sea.");      
      add_chat("I've heard the Highlord of the Blue Dragonarmy is a "+
          "woman named Kitiara.");
      add_chat("Bloody draconians keep harassing me, looking for "+
          "someone called Everman or some such. Their command of "+
          "Common Tongue is barbaric!"); 
      add_chat("I've heard that there are wondrous things on the Holm. "+
          "When I retire, perhaps I will have earned the privilege "+
          "of Hunting there.");
  
    set_cchat_time(3);
      add_cchat("T'would be wise to cease this nonsense before it "+
          "is too late.");
      add_cchat("Death is deliverance from the nightmare of living.");
      add_cchat("Lost! All is lost!");
      add_cchat("Infidel!");
      add_cchat("All are slaughtered when faced with this spiritual alliance.");
      add_cchat("I give you Amyras Soultaker!");

    set_cact_time(2);
      add_cact("wield all");
      add_cact("cackle madly");
      add_cact("smile insane");

    set_default_answer(VBFC_ME("what_me"));
      add_ask(({"concubine","Concubine","SS Concubine",
          "about the concubine","about the Concubine",
          "about concubine", "shipwreck", "wreck"}), 
          VBFC_ME("answer_ship") );
      add_ask(({"knights", "Knights", "Knighthood", "knighthood"}),
          VBFC_ME("knight_ask"));
      add_ask(({"god", "gods", "Gods", "Will of the Gods", "will"}),
          VBFC_ME("gods_ask"));
      add_ask(({"where","where to","from", "destination", "sail",
          "sailing", "travel", "ship", "odalisque", "Odalisque"}),
          "say The Odalisque sails between the Rift of Sybarus "+
          "and Port Balifor in Ansalon",1);
      add_ask(({"flotsam", "Flotsam", "balifor", "Balifor"}),
          "say I'm no land-lubber. I stick to what I know: the "+
          "deck of this ship." ,1);
      add_ask(({"Sybarus", "sybarus", "rift", "Rift"}),
          "say Sybarus is the city of Faithful, who dwell in the "+
          "shadow of the Source", 1);
      add_ask(({"good", "Good", "evil", "Evil", "right", "Right",
          "wrong", "Wrong", "good and evil", "right and wrong",
          "morality"}), VBFC_ME("good_ask"));
      add_ask(({"holm", "Holm", "Park", "park"}),
          "say Ah the Holm! It is the ultimate hunting ground. It is "+
          "a place where chaos reigns, and anything can happen!",1);
      add_ask(({"house", "houses", "House", "Hu'garen", "hu'garen", "hugaren"}),
          "say My House is Hu'garen. My family allied itself with Hu'garen"+
          " four generations ago. I am hoping to raise myself and my "+
          "children to icu before I retire.", 1);
      add_ask(({"hunt", "Hunt", "hunting", "Hunting"}),
          "say It is a form of recreation for the Shadow Elves, and a "+
          "rare privilege for the rest of us. I've heard that to "+
          "Hunt is to know that one is truly alive.", 1);
      add_ask(({"rank", "Rank", "ranking"}),
          "say Rank is a complicated thing, yet it is everything to "+
          "we Syarites. The Houses are all ranked according to their "+
          "power and influence, and within the houses are three "+
          "ranks: ini, icu, and dei.", 1);
      add_ask("ini",
          "say Ah, rank within Sybarus is complicated. To be 'ini' "+
          "is to be at the lower or newer level within one's House. "+
          "Ini are blood-sworn to a House. They are recently adopted "+
          "or initiated, or simply have not distinguished themselves "+
          "to the point where they have earned icu rank. ", 1);
      add_ask("icu", 
          "say A sybarite with icu rank is a member of a family that "+
          "has served a House for generations. The common-tongue "+
          "translation for 'icu' is 'blood-loyal'. It is the highest "+
          "rank that non-elves may reach in a House.", 1);
      add_ask("dei", 
          "say To be dei is to be a true member of the Family which "+
          "rules the House. The common-tongue translation for 'dei' "+
          "is something like 'blood-born'. Only elves can be dei.", 1);
      add_ask(({"draconian", "draconians", "kitiara", "Kitiara", 
          "Everman", "everman"}),
          "say I don't know much at all about that. Kitiara com"+
          "mands the draconians of the Blue Army. They're out to "+
          "destroy the Knights, and find the Everman, whoever that "+
          "unfortunate soul may be.", 1);
      add_ask(({"union", "Union", "Shadow Warriors", "shadow warriors"}),
          "say They are the guardians of Sybarus, with the mandate of "+
          "the Hegemon.", 1);
      add_ask(({"drow", "Drow"}), "say I've heard of them. Very dark "+
          "people with white hair. They live below, like Sybarites do.",
          1);
      add_ask(({"dancer", "dancers", "dancers of the veil", "veil dancers",
          "qalita", "Dancers"}), "say Ah the Dancers! Aren't they "+
          "delightful! You can find Qalita down at the pub in Sybarus.",1);
      add_ask(({"pub", "pub in sybarus", "Icy Bod's"}), "say The pub is "+
          "called Icky Bod's. I've not been there in too long.",1);
      add_ask(({"Hizarbin", "hizarbin", "Jazur", "jazur", "Nantur", 
          "nantur"}), 
          "say Names of Power should not be spoken lest you would wish "+
          "the one so named to appear as though summoned.", 1);            

    set_ticket(ATICKET);
    set_price(APRICE);

    seteuid(getuid());
    equip_me();
}    


string
my_long()
{
    string  str;

    str = "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    if (TP->query_met(query_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) 
            + " "+ query_race_name() +", presenting himself as:\n" 
            + query_name();
        if (strlen(query_title()))
            str += " "+ query_title() +",";
        str += " "+ query_exp_title() +", male "+ query_race_name() +".\n";
    }

     str += "He is a gnome of Sybarus, a merchantile captain with much "+
         "experience running the DragonArmy blockade at Port Balifor. "+
         "His once pale skin has been sun-bronzed "+
         "and toughened by years of exposure to the elements.\n"+
         "His long, dark hair is copper-streaked and tied back with "+
         "a ribband.\nHis eyes are the colour of amber.\n";
    return str;
}

string
what_me()
{
    switch(random(6))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say I don't know. I stick to what I know do know:"+
                " the deck of this ship.");
            break;
        case 2:
            command("emote struggles to answer, but does not seem able "+
                "to get the words out.");
            break;
        case 3:
            command("say Would that I could, but I cannot say.");
            break;
        case 4:
            command("emote raises his eyebrows and blinks several "+
                "times in a row.");
            break;
        case 5:
            command("say Oddly enough, I don't know anything about that.");
            break;
    }
    return "";    
}

string 
answer_ship()
{
    command("say Aye, the fair ship Concubine. She was the first "+
        "to sail the Rift. It was an ill-fated venture.");
    command("say Staek, Captain of the Melancholy, is the only one "+
        "to have survived. He's the one to talk to if you have "+
        "questions. You can find him on the run between Sparkle "+
        "and the Rift.");
    return "";
}

string
gods_ask()
{
    command("say My patron God is Hizarbin, who governs the waters.");
    command("say I have taken Nantur as patroness as well, for she "+
        "rewards those who gather knowledge in Her name.");
    return "";
}

string
good_ask()
{
    command("smile thoughtfully");
    command("say I've given that subject much thought during those "+
        "long sun-accursed days at sea.");
    command("say What are good and evil, but a matter of perspective?"+
        " Neither are absolutes--they are but interpretations of a "+
        "moral code.");
    command("say If my moral code differs from yours, you look at me "+
        "and think that I am either good or evil in relation to it.");
    command("say It is irrelevant. What matters is Right and Wrong. "+
        "Doing the Will of the Gods is Right and all else is Wrong. ");
    command("say It is not your place to say that something I do by "+
        "the Will of the Gods is good or evil.");
    command("say The childish, immature morality of Outlanders does "+
        "not apply to Gods! Do you hear me? Morality does not apply "+
        "to Gods!");
    return "";
}


string 
knight_ask()
{
    command("spit");
    command("say A misguided group of fools, they are, serving a weak "+
        "god. So self-righteous and pompous, these Knightlings, "+
        "insisting so stridently upon their 'goodness', yet "+
        "distrusted even so by the people of their land.");
    command("say Bah! Good and Evil matter not to me. It is Right and "+
          "Wrong that matter. Doing the Will of the Gods is Right "+
          "and all else is Wrong. Mark my words if you venture into "+
          "Sybarus.");
    return "";
}

void
equip_me()
{
    clone_object(SPAR_DIR + "rapier")->move(TO, 1);
    clone_object(SPAR_DIR + "shirt")->move(TO, 1);
    command("wear all");
    command("wield all");
}


private void
call_demon()
{
    object me = this_object();
  
    if (no_demon >= 3) 
    {
        command("shout Amyras! I am yours! Take my soul!");
        return;
    }

    if (query_hp() < query_max_hp()/2 && !objectp(demon) && no_demon <= 3)
    {
        tell_room(ETO, QCTNAME(me) + "'s body arches grotesquely and "+
	    "flames appear to burst from his chest!\n");
        demon = clone_object(SPAR_DIR + "amyras");
        demon->move_living("M", ETO);
        tell_room(ETO, "The flames coalesce into a humanoid figure!\n");
        demon->command("shout You dare attack my Servant!");
        demon->set_follow("tibalsek");
        demon->help_staek(me);
        no_demon++;
    }
}

int
special_attack(object victim)
{
    if(random(2)) return 0; /* normal attack */

    switch (random(2))
    {
        case 0:
            call_demon();
            break;
        case 1:
           tell_room(ETO, QCTNAME(TO) +
	       " appears to draw strength from an unseen source.\n");
           heal_hp(200+random(70));
           break;
    }
    return 1;
}

void 
give_back(object what, object from)
{
    if(!command("give "+what->query_name()+" to "+from->query_real_name()))
       command("drop "+what->query_name());
}

void enter_inv(object what, object from)
{
    ::enter_inv(what, from);

    if(!living(from))
      return;

    set_alarm(1.0, 0.0, &give_back(what, from));
}

void
init_living()
{
    ::init_living();
 
    if (ticket)
        add_action("buy", "buy");
}

string race_sound()
{
  return "rumbles";
}


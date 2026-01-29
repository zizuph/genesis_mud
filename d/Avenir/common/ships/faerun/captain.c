// -*-C++-*-
// name: Captain /d/Avenir/common/ships/faerun/captain.c
// creator(s):   
// last update:  Lucius 2008: Converted to Faerun line.
// purpose:      Ship Captain for the Luminous
// note:         
// bug(s):
// to-do:
// revision:     
#pragma strict_types

#include <macros.h>
#include <cmdparse.h>
#include "../ship.h"

#define ETO      environment(this_object())
#define FTICKET  (FRUN_DIR + "ticket")
#define FPRICE   24

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Genesis/ship/captain";

private string
my_long(void)
{
    string str = "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +
	" "+ query_race_name()+".\n";

    if (TP->query_met(query_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) 
            + " "+ query_race_name() +", presenting himself as:\n" 
            + query_name();
        if (strlen(query_title()))
            str += " "+ query_title() +",";
        str += " "+ query_exp_title() +", male "+ query_race_name() +".\n";
    }

     str += "He is a gnome of Sybarus, a merry merchantile captain "+
         "with several years' sailing experience.\nHis once-pale "+
         "skin has been browned and toughened by years of exposure "+
         "to the elements.\nHis curly red hair is tied at his neck "+
         "with a ribband.\nHis eyes are the colour of chocolate.\n";

    return str;
}

public void
equip_me(void)
{
    clone_object(SPAR_DIR + "rapier")->move(TO, 1);
    clone_object(SPAR_DIR + "shirt")->move(TO, 1);
    command("wear all");
    command("wield all");
}

public void
create_captain(void)
{
    if (!IS_CLONE)
      return;
    
    setuid();
    seteuid(getuid());

    set_name("ubrus");
    add_name(({"captain", "nika"}));
    set_title("Nika icu Ra'let, Captain of the Luminous");
    set_living_name("ubrus");
    set_race_name("gnome");
    set_adj(({"barrel-chested", "hearty"}));
    set_long(my_long);
    default_config_npc(200);
    set_skill(SS_SWIM, 100);
    set_skill(SS_WEP_SWORD,75);
    set_skill(SS_DEFENCE,75);
    set_skill(SS_PARRY,75);
    set_skill(SS_AWARENESS,80);
    set_skill(SS_UNARM_COMBAT, 90);
    set_appearance_offset(-10); // always 'handsome' 
    set_alignment(0);

    add_prop(LIVE_I_SEE_DARK, 80);
    add_prop(OBJ_I_RES_MAGIC, 50);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
    set_act_time(6);   
      add_act("emote laughs until his belly shakes.");
      add_act("smile .");
      add_act("chuckle merr");
      add_act("emote scratches himself.");
      add_act("emote looks eagerly out to sea.");
      add_act("emote shades his eyes with his hand.");
      add_act("emote licks his sunburned lips.");
      add_act("chuckle");

    set_chat_time(5);
      add_chat("The Luminous is no longer welcome in Emerald.");
      add_chat("I've found a new port at someplace called Faerun.");
      add_chat("I've gotten used to sailing on this sea, navigating by "+
          "the stars.");
      add_chat("At first I found the huge open spaces discomforting.");
      add_chat("I've come to like your sky and your sun, but I miss the "+
          "pulse of the Source, and the cavern's embrace.");
      add_chat("You're not likely to find a better, safer ship than the "+
          "Luminous.");
      add_chat("Bakona runs the best pub I've seen yet.");
      add_chat("I've heard that there are wondrous things on the Holm. "+
          "When I retire, perhaps I will have earned the privilege "+
          "of Hunting there.");
  
    set_cchat_time(3);
      add_cchat("T'would be wise to cease this nonsense before it "+
          "is too late.");
      add_cchat("Death is deliverance from the nightmare of living.");
      add_cchat("Lost! All is lost!");
      add_cchat("Infidel!");

    set_cact_time(2);
      add_cact("wield all");
      add_cact("cackle wild");
      add_cact("smile eager");

    set_default_answer(VBFC_ME("what_me"));
      add_ask(({"concubine","Concubine","SS Concubine",
          "about the concubine","about the Concubine",
          "about concubine", "shipwreck", "wreck"}), 
          VBFC_ME("answer_ship") );
      add_ask(({"knights", "Knights", "Knighthood", "knighthood"}),
          VBFC_ME("knight_ask"));
      add_ask(({"calia", "calian", "calians"}),
          "say Aren't they the ones who fall all over themselves trying "+
          "to move behind each other?", 1);
      add_ask("bakona", "say A wonderful woman. She runs the pub at the "+
          "Sybarus Port. If you pay her a visit, give her my best.", 1);
      add_ask(({"god", "gods", "Gods", "Will of the Gods", "will"}),
          VBFC_ME("gods_ask"));
      add_ask(({"where","where to","from", "destination", "sail",
          "sailing", "travel", "ship", "luminous", "Luminous"}),
          "say The Luminous sails between the Rift of Sybarus "+
          "and Faerun.",1);
      add_ask(({"palanthas", "palanthus"}),
          "say I sail there. That's all I know." ,1);
      add_ask(({"Sybarus", "sybarus", "rift", "Rift"}),
          "say Sybarus is the city of Faithful, who dwell in the "+
          "shadow of the Source", 1);
      add_ask(({"good", "Good", "evil", "Evil", "right", "Right",
          "wrong", "Wrong", "good and evil", "right and wrong",
          "morality"}), VBFC_ME("good_ask"));
      add_ask(({"holm", "Holm", "Park", "park"}),
          "say Ah the Holm! It is the ultimate hunting ground. It is "+
          "a place where chaos reigns, and anything can happen!",1);
      add_ask(({"house", "houses", "House", "Ra'let", "ra'let", "ralet"}),
          "say My House is Ra'let. My family has been under its auspices "+
          "for seven generations.", 1);
      add_ask(({"hunt", "Hunt", "hunting", "Hunting"}),
          "say It is a form of recreation for the Shadow Elves, and a "+
          "rare priviledge for the rest of us. I've heard that to "+
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
          "people with white hair. They live below, as we Sybarites do.",
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

    set_price(FPRICE);
    set_ticket(FTICKET);
    set_newbie_stats(25);

    equip_me();
}    

public string
what_me(void)
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

public string 
answer_ship(void)
{
    command("say Aye, the fair ship Concubine. She was the first "+
        "to sail the Rift. It was an ill-fated venture.");
    command("say Staek, Captain of the Melancholy, is the only one "+
        "to have survived. He's the one to talk to if you have "+
        "questions. You can find him on the run between Sparkle "+
        "and the Rift.");
    return "";
}

public string
gods_ask(void)
{
    command("say My patron God is Hizarbin, who governs the waters.");
    command("say It is Hizarbin's Will that I sail these waters, or "+
        "I would be home, fishing the Sybarus Sea.");
    return "";
}

public string
good_ask(void)
{
    command("grin merr");
    command("say Tibalsek and I were talking about that just the other "+
        "day.");
    command("say What are good and evil, but a matter of perspective?"+
        " Neither are absolutes--they are but interpretations of a "+
        "moral code.");
    command("say If my moral code differs from yours, you may "+
        "think that I am either good or evil in relation to it.");
    command("say It is unimportant. What matters is Right and Wrong. "+
        "Doing the Will of the Gods is Right and all else is Wrong. ");
    command("say It is our great and glorious destiny, to live as the "+
        "Gods' will.");
    return "";
}

public string 
knight_ask(void)
{
    command("laugh merr");
    command("say A curious group, indeed. A bit pompous for my taste, "+
          "and inclined to name those who disagree with them 'evil'.");
    command("say They're not a bad sort, really. Just misguided.");
    command("say They don't understand that doing the Will of the Gods "+
          "is Right and all else is Wrong.");
    return "";
}

private void 
give_back(object what, object from)
{
    if (!command("$give "+ OB_NAME(what) +" to "+ OB_NAME(from)))
	command("drop "+ OB_NAME(what));
}

public void
enter_inv(object what, object from)
{
    ::enter_inv(what, from);

    if (!living(from))
      return;

    set_alarm(1.0, 0.0, &give_back(what, from));
}

public string
race_sound(void)	{ return "heartily booms"; }


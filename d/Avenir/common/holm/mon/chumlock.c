/*
========= ========= ========= ========= ========= ========= ========= =========|
 */
#include "../holm.h"
#include <ss_types.h>

inherit "/d/Avenir/inherit/monster";

void
create_monster()
{
    set_name("chumloch");
    set_title("the Faithful");
    add_name(({"man", "old man", "chumlock"}));
    set_adj("ancient");
    set_race_name("human");
    set_gender(G_MALE);
    set_long("This fellow is bent with age and the heavy burden of a "+
        "lifetime of service.\nHis face is kindly and careworn.\n"+
        "His filmy dark eyes are shadowed with fear and pain."+
        "\n");
    set_stats(({60,60,60,40,40,50}));
 
    set_alignment(0);

    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(20, 11);
 
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_ELEMENT_LIFE, 100);

    set_default_answer(VBFC_ME("what_me"));

    add_prop(NPC_I_NO_LOOKS,1);

    add_chat(13);
    add_chat("Master has quite a temper. Last time I displeased "+
        "him he cursed me.");
    add_chat("The curse wasn't lifted for weeks. I nearly starved "+
        "to death, but I dared not go to the apothecary for aid. He "+
        "promised that, should I attempt to escape my punishment, he "+
        "would trap my soul in the Portal of Salilus, and I would know "+
        "eternal unrest.");
    add_chat("Another mess to mop up in the altar room...well at least "+
        "the screaming has stopped.");
    add_chat("I wonder how my pot of stew is doing?");
    add_chat("I wonder if one of Master's students would make himself "+
        "useful and bring me some more venison?");
    
    set_act_time(10);
    add_act(({"say Master wants things just so.",
        "emote smiles dutifully."}));
    add_act(({"say I've never need into the City. I'd like to go -- "+
        "just once -- before I die.", "sigh dream"}));
    add_act("emote rubs his belly and smacks his lips together.");
    add_act("emote hums tunelessly to himself.");
    add_act("emote mops his forehead with his sleeve.");
    add_act(({"emote scratches himself under the arm.", "emote gives "+
        "off a musty, unwashed smell."}));
    add_act("emote sweeps the floor with his broom.");
    add_act(({"emote complains: Master wants his room tidied once a day, "+
        "but he's got that magical ward on his door, and only He can "+
        "dispell it.", "emote complains: Every day he gives me grief "+
        "about his unmade bed, and he's deaf to any excuses!"}));

    add_ask(({"help", "task", "job", "errand", "quest"}), 
        VBFC_ME("give_job"), 1);
    add_ask(({"curse"}), 
        "say Never am I so wretched as when my Master has cursed "+
        "me. 'Tis a terrible price to pay for his displeasure. Why, "+
        "sometimes it seems he'll never lift the curse! "+
        "Stay far away from him, lest you find yourself in "+
        "similar straights." , 1);
    add_ask(({"lift curse"}), "say Oh dear! I can't do that! You'll "+
        "have to throw yourself on the Master's mercy, or see some"+
        "one in the apothecary for help.", 1);
    add_ask(({"magic", "magick",}), 
        "say Merciful Mascarvin! I don't touch the stuff! Nearly burned "+
        "my hand off cleaning the Master's worktable, I did!", 1);
    add_ask(({"master", "beast", "teacher", "learn"}), 
        "say Alas, my master is a man of "+
        "surpassing cruelty and talent. He has been rewarded by "+
        "Salilus Himself for his services, and sometimes instructs "+
        "others in the ways of magick.", 1);
    add_ask(({"key", "keys", "rack", "chest"}),
        "say I've several keys. Master likes things kept locked up. "+
        "Dangerous things should be locked up, don't you think?", 1);

    seteuid(getuid(TO));
}

void
add_introduced(string name)
{
    command("introduce myself to " + name);
    if (random(3))
    {
        command("say Is the Master expecting you?");
        command("emote hints: If not, you'd best be going before he "+
           "finds you're here. Tabris-Zeffar alone knows what Master "+
           "would do to you, and I shouldn't like to be around "+
           "when he does it!");  
    }
}

string
what_me()
{
    switch(random(4))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say I mop floors and make beds. That is all I know.");
            break;
        case 2:
            command("emote struggles to answer, but does not seem able "+
                "to get the words out.");
            break;
        case 3:
            command("say Would that I could, but I cannot say.");
            break;
    }
    return "";    
}


string
give_job()
{
         command("smile " + TP->query_name());
         command("say I've nothing for you to do right now, but that "+
            "doesn't mean I won't later.");
         return "";
}


// file name:     /d/Avenir/union/npc/alcintaron.c
// creator(s):    Lilith
// purpose:       Quest
// note:          Cloned by /d/Avenir/union/room/altar_room
//                Clones the key for the Akram Dagger Quest
/*
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code.
 *
 */
#pragma strict_types
#include "../defs.h"

inherit (NPC + "npc");
inherit "/d/Avenir/inherit/defeat";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


public void 
create_monster()
{
    set_name("alcintaron");
    set_living_name("alcintaron");
    set_race_name("elf");
    set_adj("tenebrous");
    set_title("former Weaponsmith of the Union and Recondite "+
	"Spectre of Darkness");
    set_long("The being before you has shape and yet is "+
	"without shape, a mere collection of shadows and "+
	"the spark of self summoned from Jazur's divine "+
	"embrace. The face and hands are veiled in shadows "+
	"that shift and flow before your eyes. The only "+
	"truly distinctive characteristic is a towering "+
	"height, and yet you know somehow that this person "+
	"is a male of elven extraction.\n");

    set_base_stat(SS_OCCUP, 400);
    set_stats(({ 200, 200, 255, 225, 226, 150 }));

    set_gender(G_MALE);
    set_alignment(0);

    set_union_npc();
    TO->set_union_sphere(SPH_WEAPONRY);

    set_skill(SS_LANGUAGE,     100);
    set_skill(SS_ACROBAT,      100);
    set_skill(SS_AWARENESS,     95);
    set_skill(SS_DEFENCE,       95);
    set_skill(SS_SWAY,         150);
    set_skill(SS_FLING,        100);
    set_skill(SS_SLASH,        150);

    add_prop(LIVE_I_SEE_INVIS, 1 + random(4));
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_UNDEAD, 100);

    add_prop(CONT_I_HEIGHT, 272);
    add_prop(CONT_I_WEIGHT, 56000);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_act_time(35);
    add_act("emote narrows his eyes.");
    add_act("emote draws the shadows close about him.");
    add_act("emote murmurs something about a dagger.");
    add_act("gaze intently");
    add_act("dignity");
    add_act("usay With blood-offerings have I been summoned from the "+
      "Shadows, to serve the Will of Jazur if you are worthy.");
    add_act("usay Is it not magnificient?");

    set_default_answer(VBFC_ME("answer_none"));
    add_ask(({"[who] / [what] [are] 'you'"}), 
      "say I am one whose life encompassed the Union's beginning, at "+
      "Akram's side. I am the former Weaponsmith of the Union and "+
      "Recondite Spectre of Darkness", 1);
    add_ask(({"[what] [is] [your] 'name'"}), 
      "say Names have power. If you would know my name you must show "+
      "the proper respect.", 1);
    add_ask(({"'introduce' / 'intro' [yourself]"}), 
      "say Names have power. If you would know my name you must show "+
      "the proper respect.", 1);
    add_ask(({"alcintaron"}), 
      "say That is the name by which I was called when I was enfleshed.", 1);
    add_ask(({"akram"}),
      "say In a time long past I was Akram's weaponsmith. I forged his "+
      "dagger in the way revealed to me by Jazur in a vision.", 1);
    add_ask(({"[being] 'weaponsmith' / 'smith'"}),
      "say It was with joy that I practiced my art. When I was not craft"+
      "ing exquisite tools of death, I created monuments to She whom "+
      "we all serve.", 1);
    add_ask(({"altar", "orb"}),
      "It is my finest work. It take great pride in it, for I collaborated "+
      "with Jazur herself in its creation.", 1);
    add_ask(({"mosaic", "mosaics"}), "Yes, it is my work, as well.", 1);
    add_ask(({"[for] 'help' / 'assist' / 'assistance' / 'task'"}), 
      "say There is little I need, resting here in Jazur's embrace. "+
      "Yet... I might be of assistance to you, if you have the key.", 1);
    add_ask(({"key", "keys"}), 
      "say The keys are many: spheres are keys, daggers are keys, "+
      "words are keys, and answers are keys. The key is, to find the "+
      "correct question.", 1);
    add_ask(({"sphere", "spheres"}), 
      "say What is more perfect than a sphere, which holds the key to "+
      "our existence even after death?", 1); 
    add_ask(({"'die' / 'death' / 'dying' / 'rebirth' / "+
	" 'reincarnation' / 'summoning'"}), 
      "say The cycle of death and rebirth ends when we become One. We "+
      "die and are reincarnated as Jazur wills. And when we no longer "+
      "wish reincarnation, we join the Shadows and the Flame, to await "+
      "our summoning in times of need.", 1);
    add_ask(({"'shadows' [and] 'flame'"}), "point orb", 1);
    add_ask(({"word", "words"}), 
      "say A word is a thought given a form that others might understand. "+
      "Some words are quite modest, yet others have great power.", 1);
    add_ask(({"'word' [of] 'power'"}), 
      "say A word of power, when spoken, can make the ground tremble. "+
      "It can summon a spirit to your bidding. It can even kill the "+
      "one who pronounces it.", 1);
    add_ask(({"past", "before"}), 
      "say What came before is never truly lost, for what Was becomes "+
      "what Is, and the Is is always now.", 1);
    add_ask(({"hmm"}), "say Hmm indeed.", 1);
    add_ask(({"amon"}), 
      "say An innocuous word, of itself. It means: in strength.", 1);
    add_ask(({"dowd"}), 
      "say It is the name of another who serves Jazur, as we "+
      "all do.", 1);
    add_ask(({"plantilsi", "Plantilsi"}),
      "say Such is a word of power. It is the equivalent of "+
      "Calling a Name three times, a summoning that cannot "+
      "be ignored.", 1);
    add_ask(({"'follow' / 'join' / 'team' [with] [me]"}),
      "say This form you see cannot travel far from this place. "+
      "I regretfully decline your offer.", 1);
    add_ask(({"[how] [to] [forge] [akram's] 'dagger' / 'daggers'"}), 
      VBFC_ME("answer_dagger"));
    add_ask(({"'vision' [from] [jazur] [how] [to] "+
	"[forge] [akram's] [dagger]"}), VBFC_ME("answer_vision"));
    add_ask(({"'serve' / 'will' [of] [jazur]"}), VBFC_ME("answer_dagger"));
}

public void 
leave()
{
    command("emote returns to the shadows within the orb.");
    remove_object();
}

public string
answer_none()
{
    switch(random(5))
    {
    case 0:
	command("say You are a person of information and curiosity, "+
	    "and that befits you. Yet, I cannot speak of this with you.");
	break;        
    case 1:
	command("say What knowledge you seek must be learned elsewhere.");
	command("dignity");
	break;
    case 2:
	command("ubow");
	command("say Would that I could, but I cannot say.");
	break;
    case 3:
	command("say That is priviledged information.");
	command("emote looks somewhat apologetic.");
	break;
    case 4:
	command("say Akram would be proud.");
	command("say You've a fine, inquisitive mind. I do not "+
	    "doubt that you will find that which you seek.");
	command("smile joy");
	break;
    }
    return "";    
}

public string
answer_vision()
{
    /* Member who has completed the guru quest */
    if (IS_TORNU(TP))	
    {
	command("say If you were not ready, Jazur would not have "+
	    "allowed you here.");
	command("emote lifts a shadowy hand and blows into it, "+
	    "sending a puff of glittering dust directly into your face.");
	command("say If Jazur wills, you will have a vision about "+
	    "the forging of Akram's dagger.");

	LIST->assign_vision(TP, "alcintaron");
	LOG_EVENT("Alcintaron sent " + TP->query_name() + " a vision");
    }
    else
    {
	command("say You are a person of information and curiosity, and "+
	    "that befits you. Yet, I cannot speak of this with you.");                
    }
    return "";
}

public string
answer_dagger()
{
    if (!this_player()->test_bit("Avenir", GUILD_GROUP, AKRAM_DQ))
    {   
	object key = clone_object(OBJ + "alcin_key");
	string name = this_player()->query_real_name();

	key->move(TO);

	command("say Akram's dagger was magnificent. Its creation was "+
	    "surpassed only by the orb.");
	command("say You have been to Akram's tomb, so you are permitted "+
	    "this privilege.");
	command("say My name is known in another place. Give this key "+
	    "to the one who serves there, and the secret of its forging "+
	    "shall be opened unto you.");

	command("give "+ OB_NAME(key) +" to "+ name);

	LIST->assign_vision(TP, "alcintaron");
	LOG_EVENT("Alcintaron sent " + CAP(name) + " a vision");
    }
    else
    {
	command("say Akram's dagger was very special, but I expect you "+
	    "know that, having had one made for you already.");
    }
    return "";
}

public string
race_sound()
{
    return "speaks barely above a whisper, saying";
}

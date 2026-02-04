/*  From the mansion:
 *    "where a golden-haired girl flush with the first bloom "+
 *    "of womanhood - you somehow know her name is "+
 *    "Isabella - is sleeping soundly.  "+
 *
 *  Created by Lilith, July 2008
 *    Isabella will be used by Gorboth to give the key to the Mansion
 *     to the Covenmaster (Bofur) when the recoded guild opens.     
 *
 *  Modifications:
 *    Lilith, Dec 2008
 *    -making the npc more interactive, having her answer questions and 
 *     wander the guildhall having conversations that promote theme/RP.
 *    -she is randomly cloned by the room cave1.c
 */

#include "../guild.h"

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

inherit "/std/monster";

int start_travelling();
int alarm_id1;

public void arm_me()
{
    clone_object("/d/Terel/calathin/obj/ltorch")->move(TO);
    clone_object("/d/Terel/calathin/obj/ltorch")->move(TO);
    clone_object("/d/Faerun/flowers/heather_white")->move(TO);

}


/* 
 * This is masked to allow for parse() style questions.
 */
public void
catch_question(string question)
{
    int i, j;

    if (dont_answer_unseen &&
	(!this_player()->check_seen(this_object()) ||
	    !CAN_SEE_IN_ROOM(this_object())))
    {
	set_alarm((rnd() * 3.0) + 1.0, 0.0, unseen_hook);
	return;
    }

    /* Strip trailing period of question mark. */
    if (wildmatch("*[.\\?]", question))
	question = extract(question, 0, -2);

    posed_question = lower_case(question);

    foreach(mixed *arr : ask_arr)
    {
	/* Found a straight string match. */
	if (member_array(posed_question, arr[0]) >= 0)
	{
	    set_alarm(rnd() * 4.0, 0.0,
		&answer_question(arr[1], arr[2]));
	    return;
	}

	/* Checking parseable bits. */
	string *rex = regexp(arr[0], "\\[.*\\]|'.*'");

	foreach(string pattern : rex)
	{
	    /* Not a match, skip. */
	    if (parse_command(posed_question, ({ }), pattern))
	    {
		set_alarm(rnd() * 4.0, 0.0,
		    &answer_question(arr[1], arr[2]));
		return;
	    }
	}
    }
}

string
what_me()
{
    switch(random(4))
    {
        case 0:
            command("say I know the answer to your question, but it is "+
               "not my place to give it.");
            break;
        case 1:
            command("say Truly you cannot expect me to answer that!");
            break;
        case 2:
            command("vlaugh");
            break;
        case 3:
            command("say Ask that question elsewhere.");
            break;
    }
    return "";    
}

public void create_monster()
{
    ::create_monster();

    set_living_name("isabella");
    set_name("isabella");
    set_title("the Favoured Childe of the Shadow of Death");
    set_race_name("human");
    set_gender(G_FEMALE);

    add_adj(({ "young", "female", "golden-haired" }) );    
    set_short("young golden-haired female human");

    set_long("At first glance, she appears to be a "+
        "girl flush with the first bloom of womanhood.\n"+
        "She is wearing a pair of brown suede trousers, a cream "+
        "blouse with long flowing sleeves, a short suede vest, a "+
        "red carnelian signet ring, and a pair of brown calf-high "+
        "boots.\n"+
        ""); 
    
    default_config_npc(150);
    
    set_base_stat(SS_OCCUP,150);  
    
    set_all_attack_unarmed(40,40);
    set_all_hitloc_unarmed(50);

    set_skill(VAMP_SKILL_BITE,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_BLOCK,100);
    
    set_skill(SS_ELEMENT_AIR,100);
    set_skill(SS_FORM_DIVINATION,100);
    
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(LIVE_I_SEE_INVIS,100);

    add_prop(LIVE_I_QUICKNESS,200);
    add_prop(CONT_I_HEIGHT, 180);    
    add_prop(MAGIC_I_RES_POISON,100);
    add_prop(MAGIC_I_RES_MAGIC,50);
    add_prop(MAGIC_I_RES_FIRE,50);
    add_prop(MAGIC_I_RES_AIR,50);
        
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop("_live_i_gave_blood", 1);

    add_prop(OBJ_S_WIZINFO,"This is npc of the vampyr and "+
    "Bloodguard guilds.\n");
    
    object shadow=clone_object(SHADOW_DIR+"occ_shadow");
    if (shadow)
    {
        int result=shadow->shadow_me(TO, "occupational", OCC_GUILD_STYLE, 
        OCC_GUILD_NAME, "");
        TO->add_blood(TO->query_max_blood());
        TO->set_incognito(1);
    }

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"help", "job", "task", "quest"}), 
        "say I task you with caring for the Eldest, as I have for "+
        "all these centuries. Offer your blood or that of others, "+
        "fill the sconces with fresh torches, fill the vase with "+
        "flowers, and always give him the respect due his station.", 1);
    add_ask(({ "[about] [the] / [a] / [an] 'vampyr' / 'vampyrs' / "+
        "'vampire' / 'vampires'" }),
	  "say Embraced by all that life would be if it was undying, "+
        "we drank our fill from the fountain of immortality. "+
        "And it drank of us, until we were shadows of death", 1);
    add_ask(({"[what] [does] [the] [word] 'vampyr' / 'vampyrs' 'mean' / 'means'"}), 
        "say The word vampyrs means Shadows of Death in this land. "+
        "Alive yet undying, we are shades enfleshed, "+
        "dwelling in the twilight of Death's shadow, and death comes "+
        "swiftly and silently to those upon whom our shadows fall.");
    add_ask(({ "[about] [the] 'coven' / 'Coven'" }),
        "say I have invited all the kindred to join us here, that "+
        "they might remember their connection to the fount and "+
        "form a new Coven based in this, my ancestral home.", 1);
    add_ask(({ "[about] [the] 'bloodguard' / 'bloodguards'" }),
        "say Bloodguards are bound by oath to serve and protect the "+
        "Coven, in exchange for certain gifts.", 1);
    add_ask(({ "[about] [the] / [a] / [an] 'gift' / 'gifts'" }),
        "say Even the smallest taste of immortality "+
        "is worth dying for if you relinquish it.", 1);
    add_ask(({"[about] [the] / 'statue' / 'eldest' / 'fount' / 'fountain'" }),
        "say The fount of immortality, he requires very little, "+
        "but is displeased by neglect.", 1);
    add_ask(({"[about] 'neglect' / 'neglecting' [of] [the] [fount]" }),
        "say To neglect the fount is to reduce the flow of our power "+
        "through his displeasure. Remember, He can destroy any of us at will.", 1);
    add_ask(({"[about] [what] [does] [the] / 'statue' / 'eldest' "+
        "'wants' / 'want' / 'expects' / 'expect' / 'require' / 'requires'"}),
        "say Offer your blood or that of others, fill the sconces with "+
        "fresh torches, fill the vase with flowers, and offer him "+
        "the respect due his station.", 1);
    add_ask(({"who are you" }),
        "say I am Isabella. This is my ancestral home. I was the "+
        "Eldest's only caretaker for many centuries.", 1);
    add_ask(({"[for] [your] 'intro' / 'introduction' / 'name'" }),
        "say I am Isabella. This is my ancestral home. I was the "+
        "Eldest's only caretaker for many centuries.", 1);
    add_ask(({"[who] [is] [the] 'covenmaster' / 'leader'" }),
        "say The answer to that question is a secret I will not reveal.", 1);
    add_ask(({ "[about] [the] 'mansion' / 'guildhall' / 'crypt'" }),
        "say My family lived here long ago, in a time almost beyond memory, "+
        "when the climate was much warmer and the valley grew wine grapes. "+
        "I was embraced here, and have cared for the Eldest in this place "+
        "ever since.", 1);
    add_ask(({ "[about] [the] 'valley' [of] [the] [shadow] [of] [death]" }),
        "say It was named the Valley of the Shadow of Death long long ago, "+
        "when the vampyres fell upon this house like ravening wolves and "+
        "death followed for all who dwelt here, but me. The villagers "+
        "fled, and carried with them stories of the valley where the "+
        "shadows of death reside.", 1);
    add_ask(({"shadows of death"}), 
        "say It is what the word vampyrs means in this land: "+
        "Shadows of Death. Alive yet undying, we are shades enfleshed, "+
        "dwelling in the twilight of Death's shadow, and death comes "+
        "to those upon whom our shadows fall.");
    add_ask(({"[what] [does] [the] [word] 'vampyr' / 'vampyrs' 'mean' / 'means'"}), 
        "say It is what the word vampyrs means in this land: "+
        "Shadows of Death. Alive yet undying, we are shades enfleshed, "+
        "dwelling in the twilight of Death's shadow, and death comes "+
        "swiftly and silently to those upon whom our shadows fall.");
   add_ask(({"[about] 'drink' / 'drain' / 'blood' / 'bite'"}),
        "say Those who have drunk from the Fount have the ability to "+
        "absorb from their prey's blood some of their traits. In some "+
        "ways you might say that we are what we eat.", 1);
    

    setuid();
    seteuid(getuid());

    set_alarm(0.5,0.0,arm_me);

    seq_reset();
    seq_new ("travel", 1); // never stop
    start_travelling();
  
}

void
do_sleep()
{
    this_object()->remove_object();
}

public void feed_eldest()
{
    clone_object("/d/Terel/guilds/vamp/npc/ribos_knight")->move(environment(TO));
    command("tackle knight");
}

int
start_travelling()
{
    seq_addfirst ("travel", 
       ({ "enter hole", "", "bow statue", "say to statue I come bearing a gift.",
          "@@feed_eldest@@", 
          "vsay to statue Feed, my lord Katashi.", "", "", "", "kneel statue", 
          "worship statue", "", "", "sing", "", "dance", "", "vdance statue", "",    
          "smile statue", "", "listen statue", "", "get torch from east sconce", 
          "drop torch", "put torch in east sconce", "smile satisfied", "", "",
          "", "", "", "", "bow statue", "", "", 
          "n", "up", "n", "", "peer", "touch sarcophagus", "",
          "smile item", "", "", "vsay A veritible treasure trove!", 
          "vsay With these the vampyrs hold sway over life and death, "+
          "herding the mortals like shepherds do sheep.", "vlaugh", "",
          "vsay And if the shepherds have a taste for mutton, surely "+
          "their flock will not mind...", "vsay Provided the shepherds "+
          "do not become rabid wolves run amok amongst them.", "", 
          "vsay Come, walk with me a bit, will you?",
          "s", "", "vsay That is the error past Covens have made...",
          "vsay Forgetting that we can be symbiotes, rather than parasites.",
          "vsay That is what Bloodguards are for. To serve you, and to "+
          "serve as reminders that mortals and vampyres can co-exist.",          
          "vsay It is in our own best interests to foster connections with "+
          "mortals, to treat with them, to lull them into a sense of security.", 
          "vsay They have a purpose in the scheme of things, a greater scheme "+
          "than any of them shall live to know.", "", 
          "vsay Through them we can build a world we might walk freely in, "+
          "feared and respected, but not hunted like beasts, not abhorred as "+
          "the antithesis of life.", "", "", "", "",
          "w", "", "", "vsay I invited the lost ones of Emerald into the "+
          "fold, that they might remember The Fount of their immortality.", "",
          "", "", "caress coffin", "", "vthoughtful", "",        
          "vsay In terms of enlightened self-interest, it behooves we "+
          "Vampyres to watch over the mortals like shepherds over sheep. "+
          "They are our food.", "vsay But more than that, they are "+
          "reminders of our humanity -- contact with the mortals, relationships "+
          "with the mortals, helps maintain contact with reality -- who we are, "+
          "who we once were, and the monsters we can become if we descend "+
          "into the madness of predatory bloodlust for too long.", "",              
          "vsay You have the power to create a world you want to live in.",
          "vsay Or you can let it deteriorate into a hell-hole unfit for "+
          "vampyres and mortals alike.", "", 
          "vsay Choose. The path of the despot, or that of the guardian.",
          "vsay Choose. The path of destruction and despair, or the path "+
          "of the shepherd who guards and cares for his flock that he might "+
          "eat well off the fat of the land.",
          "vsay Choose. The obvious or the subtle.",
          "vsay Choose.", "", "", 
          "vpower", "", "", "vthoughtful", "", "", "", "nod .", "bow",
          "e", "", "", 
          "vsay As immortals, you are fated to watch the world evolve. "+
          "To watch beauty die and be born anew.", "",
          "vsay As immortals you have the power to influence the world that "+
          "is, and the world that may be.", "",
          "vsay Listen to me.", "clap loud", "", 
          "vsay You walk in this world, and so does your food. ",
          "vsay Being invested in a world that works for everyone makes for "+
          "a life that is more than mere existance.", "",
          "vsay That is what Bloodguards are for. To serve you, and to "+
          "serve as reminders that mortals and vampyres can co-exist.",
          "vshine", "", "vrise", "",
          "d", "", "", 
          "say Pray tell, what care have you given the Eldest in my absense?",
          "exa board", "", "", "vpensive", "say Interesting...", "n", 
          "touch sarcophagus", 
          "smile item", "", "say What a superb collection of artifacts!", 
          "say Truly it was a brilliant idea to reopen the path of the "+
          "Bloodguards to mortals.", "", "", "say Come. Walk with me.", 
          "s", "", 
          "say What a thrill you must find it, the taste of blood upon your lips!",  
          "say And what a pleasure to know that we are what we feed upon, "+
          "that we may absorb our prey's traits from their very blood.",
          "vshine", "", "w", "", "", 
          "say Lovely books. So much knowledge lies within them.", "", "",
          "vtaste", "", "e", "", "s", "", "bow statue", "", "", "kneel statue", 
          "say to statue Some are not caring for you as well as they might, Sire.",
          "say to statue I have flowers for you. I know your fondness for them.",
          "", "put flowers in vase", "say Heather, from the moors.", "", "", 
          "listen statue", "nod", "", "vrevere statue", "", "bow statue",
          "n", "nod item", "", "", "vpensive", "", "", "", "", "smile",
          "e", "vtaste", "", "",
          "wave", "", "", "vsay Time to fly.", "", "", "@@do_sleep@@"}) );
  return 0;
}


public string query_eyes_colour()
{
    return "bright blue";
}

public string query_eyes_type()
{
    return "mesmerizing";
}

public int query_eyes_number()
{
    return 2;
}

public string query_hair_length()
{
    return "long";
}

public string query_hair_style()
{
    return "loose";
}

public string query_hair_colour()
{
    return "golden";
}

public string return_colour_desc()
{
    return "white";
}


public int special_attack(object victim)
{
    if (!(ABILITY_DIR+"bite")->query_ability_active(TO))
    {
        command("vsavage");
    }
    return 0;
}

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);

    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
		  "introduce myself to " + s_who);
}

public int filter_valid_vampire(object player)
{
    if (!interactive(player))
    {
        return 0;
    }
    if (player->query_wiz_level())
    {
        return 0;
    }
    if (!IS_BG(player) && !IS_VAMP(player))
    {
        return 0;
    }
    if (player->is_emerald_vampire())
    {
        return 0;
    }
    return 1;
}



/*
 * check_meet enables the npc to greet players it
 * comes into contact with.
 */
void
check_meet(object tp)
{
    int i = random(6);

    if (!present(tp, environment(this_object())))
		  return;

    if (tp->query_met(query_real_name()))
    {
        if (i > 3)     
            command("say to "+ tp->query_real_name() +" Hello again.");
        else 
            command("nod . at "+ tp->query_real_name());
        return;
    }

    if (filter_valid_vampire(tp))
    {
        switch(i)
        {
            case 0:
                command("vnod "+ tp->query_real_name());
                break;
            case 1:
                command("vkiss "+ tp->query_real_name());
                command("say How lovely to see you.");
                break;
            case 2:
                command("vcurtsey "+ tp->query_real_name());
                break;
            case 3:
                command("vgrin "+ tp->query_real_name());
                command("say Are you fresh from battle or from slumber?");
                break;
            case 4:
                command("vhug "+ tp->query_real_name());
                break;
            case 5:
                command("vtrace "+ tp->query_real_name());
                break;
        }
        return;
    }
    command("vturn "+ tp->query_real_name());
    command("say to "+ tp->query_real_name() +" Take care that you "+
        "pay the proper respects to the Eldest, or I'll not vouch "+
        "for your safety in this place.");
    return;
}

void
init_living()
{
    ::init_living();

    if (interactive(this_player()))
    {
        if (alarm_id1)
            return;
        alarm_id1 = set_alarm(2.0, 0.0, &check_meet(this_player()));
            return;
    }
}

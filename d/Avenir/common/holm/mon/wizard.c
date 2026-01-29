/* file name:     /d/Avenir/common/holm/t_camp/wizard.c
 *  creator(s):   (Rangorn , Feb 97)
 *  revisions:    
 *                Lilith Jan 2022: fixed runtime error.
 *                Lilith Dec 2021: added magic wand, added damage spell.
 *                       Arman cleared wand for implementation 12/31/21.
 *                Lilith Feb 2002: fixed say to, and do_die with amulet
 *                Lilith Oct 1997: fleshed Nemur out a bit more    
 *       
 *  purpose:      The mastermind behind the trolobys in the camp.
 *                Has magical wand, robe, and cursed amulet.
 *
 *  note:         Nemur committed a crime that got him banished to the Holm.
 *                Because the service he provides (making trolobies) is 
 *                useful, Hunters do not Hunt him or enter the confines of
 *                the troloby camp, assuring Nemur's safety---as long as he
 *                continues to produce.
 *  bug(s):
 *  to-do:
 */         
 
inherit "/d/Genesis/specials/npc/stat_based_specials.c";
inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/log_asks";
inherit "/d/Avenir/inherit/defeat";
inherit "/lib/unique";

#include "../holm.h"
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Genesis/gems/gem.h"

object amulet;
 
int attacked;

void
create_monster()
{
    setuid();
    seteuid(getuid());

    set_name("nemur");
    add_name(({"wizard", "wizard_nemur"}));
    set_title("Glim-Nodal the Great, Wizard Extraordinary");
    set_race_name("human");
    set_gender(G_MALE);
    set_adj("humpbacked");
    set_adj("small");
    set_long("This is a small hunchbacked human.\n"+
        "His leathery cheeks have been etched with deep wrinkles.\n"+
        "A big lump has grown out of his back, giving him a vaguely "+
        "grotesque appearance.\n"+         
        "His eyes are ageless and glowing with malice.\n");

    set_stats( ({ 100, 100, 100, 100, 100, 120 }) );
    
    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_ALCHEMY, 90);
    set_skill(SS_SPELLCRAFT, 90);
    set_skill(SS_UNARM_COMBAT, 80);  
    set_skill(SS_AWARENESS, 90);   
    set_skill(SS_SPELLCRAFT, 90); 
    set_skill(SS_FORM_ABJURATION, 90);
    set_skill(SS_FORM_TRANSMUTATION, 90);
    set_skill(SS_ELEMENT_AIR, 90);
    set_skill(SS_ELEMENT_LIFE, 90);
    set_skill(SS_ELEMENT_FIRE, 90);
	
    set_all_attack_unarmed(35, 35);
    set_all_hitloc_unarmed(15);

    add_prop("_cont_i_height", 110);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_INVIS, 5 + random(10));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_act_time(5);
    add_act("emote gets a blank look over his face.");
    add_act("sigh");
    add_act("emote seems caught up in some kind of mental struggle."); 
    add_act("emote peers at you with a malicious look in his face.");  

    set_chat_time(7);
    add_chat("What are you doing here pure one?");
    add_chat("Stay awhile. I've need of fresh blood.");
    add_chat("I once trapped a demon and enslaved him to my will.");
    add_chat("Perhaps I one day will be able to leave this accursed island."); 
    add_chat("I am second only to the Lord of the Third Hour.");
    add_chat("It was a misjudgement, to let my ambitions be known.");
    
    set_cchat_time(4);
    add_cchat("You will perish in flames for this, pure one.");
    add_cchat("You've no respect for your elders!");
     
    set_default_answer(VBFC_ME("ask_city"));
    add_ask(({"ambition", "ambitions", "troloby", "trolobies" }),
        VBFC_ME("ask_ambition"));        
    add_ask(({"amulet", "azmanizt", "Azmanizt", "ruby amulet"}),
        VBFC_ME("ask_amulet"));
    add_ask(({"free demon", "free me", "bonding", "bond", "bondage"}),
        VBFC_ME("ask_amulet"));
    add_ask(({"release", "release me", "release amulet", "release azmanizt", 
        "release demon", "release me from bonding with Azmanizt", 
        "release me from bonding"}), 
        VBFC_ME("ask_amulet"));
}

public void
add_introduced(string name)
{
    command("say Your name is of no interest to me.");
    command("say However, I expect you've heard of me already, so...");
    command("introduce me");
}

public void
equip_me()
{
    object robe, sandals, wand;

    robe = clone_unique(HOLM_OBJ +"wiz_robe", 6, HOLM_OBJ +"robe", 1, 25);
    robe->move(this_object());

    sandals = clone_object(HOLM_OBJ + "sandals");
    sandals->move(this_object());
	
	wand = clone_unique(HOLM_OBJ +"wiz_wand", 8, 0, 0, 40);
    if (wand)
    {
        wand->move(this_object());
        command("hold wand");
    }
		
    amulet = clone_unique(HOLM_OBJ +"amulet", 5, 0, 0, 25);
    if (!objectp(amulet))
	amulet = RANDOM_GEM(-1);
    amulet->move(TO);

    command("wear all");
    refresh_living();
}
           
string
ask_city()    
{
    command("say Don't bother me with your pathetic questions.");   
    command("peer");
    return "";
}

string 
ask_ambition()
{
    command("say You think I would tell you?");
    command("laugh mock");
    return "";
}

string
get_task(int i)
{
    string str;
    switch (i)
    {
        case 0..7:   str = "a pinch of ash from the bazaar apothecary"; 
                           break;
        case 8..12:  str = "a black velvety flower, known as belladonna";
                           break;
        case 13..16: str = "some of that lichen known as bloodcreep"; break;	
        case 17..19: str = "a pair of scarlet-gold scale boots, the kind "+
                           "that those shadow-elf hunters wear"; break;
        case 20..25: str = "a shield from one of the ogres that live deep "+
                           "in the Utterdark"; break;   
        case 26..40: str = "a tooth from the Great Worm that lives in the "+
                           "fiery depths of the Utterdark--You'd better "+
                           "take some friends along..."; break;
        default: str = "a...hmm...I don't know...ask me again later"; break;
    }
    return str;
}

string 
ask_amulet()
{
    int stat;
    string str;

    if (!CAN_SEE(TO, TP))
    {
        command("say Interesting, indeed, that the air asks "+
            "questions without the voice of a God.");        
        return "";
    }
    command("smile slyly at "+ TP->query_real_name());
    if (present("nemur_ruby_amulet" , TP))
    {
        command("ask "+ TP->query_real_name() +" Do you wish me "+
            "to release you from the bonding with Azmanizt?");
        stat = TP->query_average_stat() / 10;
        str = get_task(stat);
        command("say to "+ TP->query_real_name() +" If you do, bring me "+
            str +". And then we'll see.");
        return "";
    }
    command("say to "+ TP->query_real_name() +" I'm very familiar with "+
       "that amulet. I made it, in fact.");
    command("cackle deligh");
    return "";
}

int 
give_back(object obj, object from)
{
    if (!from)
    {
        set_alarm(1.0, 0.0, &obj->remove_object());
        return 0;
    }
    command("say to "+ from->query_name() +" This isn't what I wanted "+
        "from you!");
    command("give "+ obj->query_name() +" to "+ from->query_real_name());        
    return 1;
}

int
do_release(object obj, object from)
{
    object ob;
    if (ob = present("nemur_ruby_amulet", from))
    {
        command("say to "+ from->query_real_name() +" You have given me "+
            "what I asked for...");
        command("say to "+ from->query_real_name() +" I suppose I'll take "+
            "pity on you.");
        command("say to "+ from->query_real_name() +" I do hope that you "+
            "have learned that I, Nemur Glim-Nodal the Great, am not some"+
            "one to be trifled with!");
        command("emote launches into a long-winded chant.");
        set_alarm(1.0, 0.0, &obj->remove_object());
        set_alarm(2.0, 0.0, &ob->remove_object());
        return 1;
    }
    set_alarm(1.0, 0.0, &give_back(obj, from));
    return 1;    
}

void
react_meet(object tp)
{
    object ob;

    if (ob = present("nemur_ruby_amulet", tp))
    {
        command("say to "+ TP->query_real_name() +" I sense the "+
            "nearness of my ruby amulet.");
        command("cackle mad");
        command("ask "+ TP->query_real_name() +" Do you wish me "+
            "to release you from the bonding with Azmanizt?");

        if (amulet->query_prop(MAGIC_AM_MAGIC))
            amulet->remove_object();
    }
}

public void
init_living()
{
    ::init_living();

    if (interactive(TP))
        set_alarm(1.0, 0.0, &react_meet(TP));
} 

public void
enter_inv(object obj, object from)
{ 
    string it, item;
    int stat;

    ::enter_inv(obj, from);

    if (!living(from))
        return;
    // This is part of the task to get Nemur to take the 
    // amulet back.
    stat = (from->query_average_stat() / 10);
    switch (stat)
    {
        case 0..7:   it = "/d/Avenir/common/obj/ashpinch"; 
             break;
        case 8..12:   it = "/d/Avenir/common/herbs/nightshade";
             break;
        case 13..16:  it = "/d/Avenir/common/herbs/bloodcreep";
             break;		
        case 17..19:  it = "/d/Avenir/common/holm/obj/m_boots1"; 
             break;
        case 20..25: it = "/d/Avenir/common/dark/obj/oshield"; 
             break;                               
        case 26..40: it = "/d/Avenir/common/dark/obj/worm_leftover"; 
             break;
    }
    item = MASTER_OB(obj);
    if (item != it)
    {
        set_alarm(1.0, 0.0, &give_back(obj, from));
        return;
    }
    set_alarm(1.0, 0.0, &do_release(obj, from));
    return;
}

/* damage special with magic_dt */
public int
do_damage(object victim)
{
    mixed * hitresult;
    int avg_stat, hurt;
    string how, hdesc;

    // Choose power of hit based on mob stat size.
    hitresult = do_stat_based_attack(TO, victim, MAGIC_DT);

    // The attack was evaded
    if (intp(hitresult))
	return 1;

    if (hitresult[0] <= 0)
    {
	// Handle misses.
	query_combat_object()->tell_watcher("A stream of flame "+
	  "erupts from "+ QTNAME(TO) + "fingertip and "+
	  "just misses " + QTNAME(victim) +"!", victim);
	victim->catch_msg("A stream of flame erupts from "+ 
      QTNAME(TO) +"'s fingertip and just misses you!\n");
	return 1;
    }
    // hitresult as percentage of health
    how = "unharmed";
    if (hitresult[0] > 0)
	how = "a slight singeing of your hair.";
    if (hitresult[0] > 5)
	how = "a bit of warmth where the flame grazed you.";
    if (hitresult[0] > 10)
	how = "a mild burn where the flames licked you.";
    if (hitresult[0] > 25)
	how = "a painful burn where the flames singed you!";
    if (hitresult[0] > 50)
	how = "agony as the flame sears a layer off your skin!";

    hdesc = hitresult[1];
    query_combat_object()->tell_watcher(QCTNAME(TO) + " casts a "+
      "spout of flame toward "+ QTNAME(victim) + " that brushes "+
      victim->query_possessive() +" "+ hdesc +"\n", victim); 
    victim->catch_msg(QCTNAME(TO) + " casts a spout of flame that "+
      "tumbles toward your "+ hdesc +"!\n");
    victim->catch_msg("You feel " + how + "\n");

    return 1;
}



void
do_react(object ob)
{
    object *obs, trol;

    if (!present(ob, environment(this_object())))
        return;
    if (random(3))
	{
		command("shouts a word of power that sends a shock through you!");
        ob->add_attack_delay(5 +random(5));		
        return;
    }
    obs = FIND_STR_IN_OBJECT("troloby", environment(this_object()));
    if (!sizeof(obs))
    {
        command("sob angr");
        call_other("/d/Avenir/common/holm/t_camp/c6", "do_troloby_jump");
    }
	obs = FIND_STR_IN_OBJECT("troloby", environment(this_object()));
	if (sizeof(obs))
	{	
        command("shout Trolobies! Aid your Master!");
        trol = obs[0];
        tell_room(environment(this_object()), 
        "With a deafening roar the troloby throws "+
        "himself in front of his master, taking the blows.\n");
        trol->throw_myself(this_object());
		return;
	}
	command("say Did you kill all of my creations? I will make more.");
	command("say Perhaps I will turn YOU into a troloby!");
    return;   
}  

/* Evade attack 4 out of 10 tries */                                                                            
int 
query_not_attack_me(object who, int aid)
{
    if (random(10) > 5)
    {
        /* This will block an attack */
        who->catch_msg(QCTNAME(this_object()) +" chants a phrase "+
             "that seems to protect him from your attack.\n");
        return 1;
    }
    return 0;
}

void
attacked_by(object ob)
{
    set_alarm(2.0, 0.0, &do_react(ob));
 
    if (!(attacked))
    {
        attacked = 1; // To prevent extra con more than once
        set_stat_extra(SS_CON, 50);
        refresh_living();
    }
    ::attacked_by(ob);
}

int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return 1;
    }

    switch (random(5))
    {
        case 0..1: command("heal me");
            return 0; break;
        case 2: command("cure me");
            return 0; break;
        case 3: do_react(victim);
            return 0; break;
        case 4: do_damage(victim);
		    return 0; break; 
        default: break;
    }
    return 0;
}

void
return_abuse(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    /* Play with Fire, get Burned! */
    command("say to "+ OB_NAME(actor) +" You paltry, pathetic sin'ur!");
    command("kill "+ OB_NAME(actor));
    do_react(actor);
}

void
return_dis(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    /* Do the stuff. */
    command("say to "+ OB_NAME(actor) +" If you have no respect for "+
        "beings superior to yourself...");
    command("say to "+ OB_NAME(actor) +" I will be forced to teach "+
        "you.");
}

void
return_respect(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    /* Do the stuff. */
    command("nod "+ OB_NAME(actor));
    command("say to "+ OB_NAME(actor) +" You are a good child.");
}

void
emote_hook(string emote, object actor, string adverb)
{
    /* See if we want to trigger on the emote. If so, call a little alarm
     * for the reaction function.
     */
    switch(emote)
    {
        case "caress":
        case "grope":
        case "fondle":
        case "lick":
        case "french": 
        case "tickle":
	      set_alarm(3.0, 0.0, &return_dis(actor, adverb) );
            return;
        
        case "poke":
        case "spit":
        case "kick":
        case "slap":
	      set_alarm(3.0, 0.0, &return_abuse(actor, adverb) );
            return;

        case "kiss":
        case "bow":
        case "grovel":
        case "curtsey":
            set_alarm(3.0, 0.0, &return_respect(actor, adverb) );
	      return;
    }
}

void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    if (killer && ENV(TO) == environment(killer)) 
    {
        command("say You thought you could kill me?");
        command("say to "+ OB_NAME(killer) +
            " I will be seeing you again!");
    }

    tell_room(ENV(TO), QCTNAME(TO) + "'s clothing stands empty before "+
        "you, then collapses to the ground in a puff of air.\n");

    STATSERV_LOG_EVENT("holm", "Wizard Nemur defeated");
    ::do_die(killer);
}

string 
race_sound()
{
    return "says in a rasping voice";
}

/* Stop knights from cheating with mercy. */
public int
query_disallow_mercy(void)
{
        return 1;
}

// file name:     /d/Avenir/union/npc/dowd.c
// creator(s):    Cirion (c) Marc Prud'hommeaux
// purpose:       Trainer and Avenger
// note:          Clones by /d/Avenir/union/room/white.c
// last update:   Lilith   09 Sept 2001
//                Added plantilsi_amon function and attacks
//                SUMMONING & USING HIM COSTS THE FLAME 
/*
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code. Removed all follow/assist code.
 * 			  NPC is a trainer, nothing more.
 *  Lilith, Oct 2021: Bringing Ogre raids back, so bringing 
 *            Dowd back as a summonable npc--to defend the gates only.
 */
#pragma strict_types

#include "../defs.h"
inherit (NPC + "npc");

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

int alarm_id = 0;

public void 
create_monster()
{
    set_name("dowd");
    set_living_name("dowd");
    set_race_name("human");
    set_adj("shadowy");

    set_long("His face seems veiled by shadows, an ancient "+
	"enigma, unchanging.\n");

    /* This is Dowd, the ultimate warrior of shadow */
    set_base_stat(SS_OCCUP, 400);
    set_stats(({ 225, 255, 255, 225, 226, 200 }));

    set_gender(G_MALE);
    set_appearance(75);
    set_alignment(0);

    set_union_npc();
    TO->set_union_sphere(SPH_FLAME);

    set_skill(SS_LANGUAGE,      50);
    set_skill(SS_ACROBAT,       80);
    set_skill(SS_AWARENESS,     95);
    set_skill(SS_DEFENCE,       90);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_PARRY,        100);
    set_skill(SS_WEP_KNIFE,    150);
    set_skill(SS_WEP_SWORD,    150);
    set_skill(SS_SWAY,         150);
    set_skill(SS_FLING,        150);
    set_skill(SS_SLASH,        150);

    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_QUICKNESS, 200 + random(25));
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);
	add_prop(LIVE_I_NO_CORPSE, 1); // stuff of shadows, he leaves no corpse.

    set_mm_in("steps into a shadow and disappears.");
	set_mm_out("steps out of swirling shadows.");
	
    set_act_time(90);
    add_act("emote narrows his eyes.");
    add_act("emote draws the shadows close about him.");

    set_cact_time(16);
    add_cact("assist nadia");
	add_cact("assist cyrus");
    add_cact("sway");
    add_cact("emote is in a blood-rage the likes of which "+
      "you have never seen before.");
    add_cact("emote dances with incredible grace and "+
      "speed as he lays about him with his sword.");
    add_cact("emote shifts like a shadow, always just beyond reach.");
    add_cact("say I am the flame-shadow which dances at the edges "+
      "of your sight. Watch and learn.");

    add_ask(({ "help" }), "say When you require assistance, "+
      "you need only to say the words of power.", 1);
    add_ask(({ "hmm" }), "say Hmm indeed.", 1);
    add_ask(({ "key" }), 
      "say The keys are many. Keys are answers. "+
      "What is the question?", 1);
    add_ask(({ "task" }), "say I have none for you.", 1);
    add_ask(({ "amon" }), 
      "say An innocuous word, of itself. It means: in strength.", 1);
    add_ask(({ "dowd" }), 
      "say It is the name by which I may be Called.", 1);
    add_ask(({ "plantilsi" }),
      "say Such is a word of power. It is the equivalent of "+
      "Calling a Name three times, a summoning that cannot "+
      "be ignored or refused.", 1);
    add_ask(({ "plantilsi amon", "plantilsi amon dowd"}),
      "say Utter that phrase in my presense only in direst "+
      "need. With it you may Call me fully from the Shadows, "+
      "and with me all the glory of the Flame shall fight at "+
      "the Gates.", 1); 
    add_ask(({"follow", "follow me"}), 
      "say Alas, my days of following are over.", 1);	  
    add_ask(({ "return", "return home", "leave", "leave me" }), 
      VBFC_ME("do_leave"), 1);
    add_ask(({ "assist", "assist me", "help" }), 
      VBFC_ME("do_assist_ask"), 1);

    equip(({OBJ+"knife", DEAD+"obj/falcata",
	    OBJ+"shirt", OBJ+"pants", OBJ+"boots",
	    OBJ+"cape", OBJ+"gloves", OBJ+"combat_veil"}));

    set_alarm(0.5, 0.0, &command("mark all"));
    set_alarm(0.5, 0.0, &command("veil me"));
}

private void
leave(void)
{
    command("emote melds with the shadows and disappears.");
    remove_object();
}

public void
attacked_by(object who)
{
    set_alarm(1.0, 0.0, leave);
    ::attacked_by(who);
}

/*
 * Mask these from regular union npc's to avoid problems.
 */
public void add_introduced(string str) { }
public void summon_for_union_ceremony(object where) { }

/* Called when a union member asks him to leave or return */
string
do_leave()
{
    if (!IS_MEMBER(TP))
    {
	command("say Might I suggest you leave by way of the Underdark?");
	return "";
    }
    else
    {
	command("ectios");
	command("say May your passion feed the Flame, my other self.");
	command("emote gathers shadows around him.");
	set_alarm(3.0, 0.0, leave);
	return "";
    }
    return "";    
}

/* He used to follow whoever summoned him, but now
 * He goes to one place, just outside the Gates.
 */
void
do_gate_move()
{
	TO->move_living("X", ENTRY, 1);
	command("emote swears an oath that no ogre or dark elf shall "+
	  "enter the Halls as long as he draws breath!");
	command("kill ogre");
}

/* I have been summoned to fight at the Gate (for 20 mins)  */
void 
plantilsi_amon()
{
    command("sway");
    set_alarm(1200.0, 0.0, leave);

	if (IS_MEMBER(TP) || FRIEND(TP))
	{
	    command("bow "+ TP->query_name());
	    command("say I am here, amon.");
	    command("say There is a price to be paid for Calling me. "+
		  "That price is Blood and Fire.");
		command("say I will join Nadia and Cyrus at the Gates.");
		set_alarm(2.0, 0.0, do_gate_move);
	}    
}

/* I have been summoned to fight at the Gate (for 20 mins)  */
void 
do_assist_ask()
{
    command("sway");

	if (IS_MEMBER(TP) || FRIEND(TP))
	{
	    command("bow "+ TP->query_name());
	    command("say I am here to serve.");
	    command("assist "+ TP->query_name());
	}    
}

/* 
 *  I'll attack if I'm not busy killing something else.
 */
void
do_slay(object victim)
{
    if(query_attack()) 
	return;   // always concentrate on fighting

    command("kill "+ victim->query_name());
    command("us Abrud charus amon Jazur!");
}

/* Should I attack this living? */
int
do_this_check()
{
    /* Reset. (See init_living) */
    alarm_id = 0;

    if (TP->query_prop("_i_summoned_dowd"))
	    TP->remove_prop("_i_summoned_dowd");

	if (IS_MEMBER(TP) || FRIEND(TP))
	{
	    command("bow "+ TP->query_name());
	    command("say I am here, amon.");
	    command("say There is a price to be paid for Calling me. "+
		  "That price is Blood and Fire.");
	}    

    if(query_attack())
        return 0;    // always concentrate on fighting

    if (interactive(TP))
		return 0;    // Don't attack players, they must attack me.
	
    if (TP->query_race() == "ogre" || 
        TP->query_race() == "dark elf")    
	    return 1;   // attack our historical enemies    
}


/*
 * Function name: init_attack
 * Description:   Called from init_living() in monster.c
 */
public void
init_attack()
{
    int i = check_call(monster_aggressive);
    if (!i) 
	return;
    if (alarm_id)
	return;
    if (do_this_check()) 
	alarm_id = set_alarm(itof(random(4) + 1), 0.0, 
	  &do_slay(this_player()));
}

void 
init_living()
{
    ::init_living();

    if (alarm_id)
	return;

    if (do_this_check()) 
	alarm_id = set_alarm(itof(random(4) + 1), 0.0,
	  &do_slay(this_player()));

}

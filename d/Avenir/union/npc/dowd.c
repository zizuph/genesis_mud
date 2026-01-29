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
 *
 */
#pragma strict_types

#include "../defs.h"
inherit (NPC + "npc");

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>


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
    set_stats(({ 200, 200, 255, 225, 226, 150 }));

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
    set_skill(SS_WEP_MISSILE,  100);
    set_skill(SS_WEP_KNIFE,    150);
    set_skill(SS_WEP_SWORD,    150);
    set_skill(SS_SWAY,         150);
    set_skill(SS_FLING,        100);
    set_skill(SS_SLASH,        150);

    add_prop(LIVE_I_SEE_INVIS, 1 + random(4));
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_QUICKNESS, 80 + random(25));
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);

    set_act_time(90);
    add_act("emote narrows his eyes.");
    add_act("emote draws the shadows close about him.");

    set_cact_time(16);
    add_cact("assist");
    add_cact("emote glares about him with icy rage.");
    add_cact("emote is in a blood-rage the likes of which "+
      "you have never seen before.");
    add_cact("emote dances with incredible grace and "+
      "speed as he lays about him with his sword.");
    add_cact("emote shifts like a shadow, always just beyond reach.");
    add_cact("emote fades from sight for a long moment.");
    add_cact("say I am the flame-shadow which dances at the edges "+
      "of your sight.");

    add_ask(({ "help" }), "say When you require assistance, "+
      "you need only to say the words.", 1);
    add_ask(({ "hmm" }), "say Hmm indeed.", 1);
    add_ask(({ "key" }), 
      "say The keys are many. Keys are answers. "+
      "What is the question?", 1);
    add_ask(({ "task" }), "say I have none.", 1);
    add_ask(({ "amon" }), 
      "say An innocuous word, of itself. It means: in strength.", 1);
    add_ask(({ "dowd" }), 
      "say It is the name by which I may be Called", 1);
    add_ask(({ "plantilsi" }),
      "say Such is a word of power. It is the equivalent of "+
      "Calling a Name three times, a summoning that cannot "+
      "be ignored.", 1);
    add_ask(({ "plantilsi amon", "plantilsi amon dowd"}),
      "say A phrase which once held power but does so no longer.", 1);

    equip(({OBJ+"knife", DEAD+"obj/falcata",
	    OBJ+"shirt", OBJ+"pants", OBJ+"boots",
	    OBJ+"cape", OBJ+"gloves", OBJ+"combat_veil"}));

    set_alarm(0.5, 0.0, &command("mark all"));
    set_alarm(0.5, 0.0, &command("veil me"));
}

private void
leave(void)
{
    command("emote disappears into the shadows.");
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
public void init_living() { }
public void add_introduced(string str) { }
public void summon_for_union_ceremony(object where) { }


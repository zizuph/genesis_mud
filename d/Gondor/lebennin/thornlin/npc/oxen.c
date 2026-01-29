/*
 * thornlin/npc/oxen.c
 * Coded by : Boromir
 *
 * Revision history:
 *	11-Dec-1997, Gnadnar:	fixed bug in hit-ox code,
 *				cleaned it up a bit while i'm in here.
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit LIB_DIR + "logkill.c";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "../locals.h"
#include "../ox_quest.h"

#define A_HORNS 0
#define A_LHORN 1
#define A_RHORN 2

#define H_HEAD 0
#define H_BODY 1
#define H_HORNS 3

#define KILLED_OK       "_killed_correctly"
#define HIT_SKILLS      ({ SKILL_AVG, TS_STR, TS_DEX, SKILL_END, SS_WEP_CLUB })
#define HIT_TASK        TASK_ROUTINE

void
create_creature()
{
    set_name("ox");
    set_pname("oxen");
    set_race_name("ox");
    set_gender(0);
    // set_short("white long-horned cow");

    set_adj(({"white","long-horned"}));
    set_long(BSN("This is a white ox, with long horns. The ox "+
	"looks like it could be one of the kine of Araw."));

    // ick. why would you see all this when you look at an animal?
    // "This ox bears a fine example of a hunting horn, it is too bad that "+
    // "the horn probably would be damaged if you just attacked the ox.\n"));

    set_act_time(10);
    add_act("emote chews on some grass.");
    add_act("emote moves slowly around.");
    add_act("emote turns slowly to face you.");
    add_act("emote turns slowly to face you and stomps his right hoof "+
      "in the ground.\n"+
      "You don't feel safe here.");

    set_stats(({ 50+(random(10)*2), 10+(random(10)*2), 40+(random(15)*2),
	2+(random(10)*2),  2+(random(10)*2), 90}));
    set_alignment(50-random(100));
    set_whimpy(45);

    add_prop(CONT_I_WEIGHT, 300000);
    add_prop(CONT_I_VOLUME, 250000);
    add_prop(CONT_I_HEIGHT, 170);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_skill(SS_UNARM_COMBAT,40+(random(25)*2));
    set_skill(SS_DEFENCE,15+(random(15)*2));
    set_skill(SS_BLIND_COMBAT,50);

    add_prop(OBJ_I_NO_INS, 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,           %usage, attack_desc */
    set_attack_unarmed(A_HORNS, 15, 3+random(12), W_SLASH,  50, "both horns");
    set_attack_unarmed(A_LHORN, 30, 3+random(12), W_SLASH,  25, "left horn");
    set_attack_unarmed(A_RHORN, 30,  3+random(12), W_SLASH,  25, "right horn");

    /* Hit_loc,             *Ac  (im/ sl/ bl/ ma),  %hit, hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   5 }), 30, "head");
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   0 }), 30, "body");
    set_hitloc_unarmed(H_HORNS,({  5,  5,  5,   0 }), 40, "horns");
}


void
init_living()
{
    ::init_living();
    add_action("my_hit", "hit");
}


public void
do_die(object killer)
{
    if (query_prop(KILLED_OK))
	add_leftover(OBJ_DIR +"horn",
	  "horn", 2, 0, 1, 1);
    else
	add_leftover(OBJ_DIR +"horn_damaged",
	  "horn", 2, 0, 1, 1);

    ::do_die(killer);
}



int
my_hit(string str)
{
    object	target, weapon;
    int		is_wielded;
    string	tmpstr;

    if (!strlen(str))
	NF0("Hit whom with what?\n");

    str = LOW(str);

    /* check for "hit ox" */
    if ( parse_command(str, ({ TO }), "[the] %o", target) )
    {
	write("You slap the ox on the nose with your hand.\n");
	command("kill " + TP->query_real_name());
	return 1;
    }
    /* check for "hit ox with <something>
     * do this in two calls to parse_command() to avoid a bug with 
     * having two %'s returning objects in a single format string
     */
    if ( !parse_command(str, ({ TO }), "[the] %o 'with' [the] %s",
	target, tmpstr) )
    {
	NF0("Hit whom with what?\n");
    }

    if ( !parse_command(tmpstr, all_inventory(TP), "%o", weapon) )
    {
	NF0("Hit the ox with what?\n");
    }

    is_wielded = ( member_array(weapon, TP->query_weapon(-1)) >= 0 );
    if ( !is_wielded || !weapon->id("_thornlin_ox_hammer_") )
    {
	if ( is_wielded )
	    write("You hit the ox with the "+weapon->short()+".\n");
	else
	    write("You slap the ox clumsily with the "+weapon->short()+".\n");
	command("kill "+TP->query_real_name());
	return 1;
    }

    /* ok, they are wielding the correct hammer ...*/
    write("Swinging the hammer, you try to kill the ox with "+
      "a single blow ...\n");
    say("Swinging a hammer, "+QTNAME(TP)+
      " tries to deliver a deadly blow to the ox ...\n");

    // prop check, skill check
    if ( (!(TP->query_prop(I_ASKED_HAMMER)) && !(TP->query_prop(I_ASKED_HORN)))
      || (TP->resolve_task(HIT_TASK, HIT_SKILLS) <= 0))
    {
	write("... but you miss!\n"
	  +   "The "+short()+" bellows furiously and charges you!\n");
	say("... but "+TP->query_pronoun()+" misses.\n");
	command("kill "+TP->query_real_name());
	return 1;
    }

    tell_room(ENV(TO),
      "The hammer connects with the head of the ox, right between his eyes.\n"
      + "The "+short()+" drops to the ground like a stone.\n");

    add_prop(KILLED_OK, 1);
    TP->add_prop(I_KILLED_OX, 1);
    heal_hp(-10000);
    do_die(TP);
    return 1;

}

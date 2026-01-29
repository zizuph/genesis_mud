// file name: gfaerie.c
// creator(s): Zielia (modified faerie created by Ilyian for use in the ziggurat)
// purpose: This mischievous faerie is a pet of Mizrun and distills
//	    nepenthe, an alcoholic drink so powerful it can cause
//	    the drinker to lose memory. This fairy also bestows the
//	    Mizrun's blessing by erasing the blessed person's name from
//	    another interactive's memory with the appropriate offering.
// revisions: Lilith Dec 2021/Jan 2022: Got the targetted name-forget
//       portion of Mizrun's blessing working.
// note:
// bug(s):
// to-do: Catch a fairy quest.

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";

#include "zigg.h"
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>


/* defines for attacks */
#define A_WINGS	  0
#define A_RHAND   1
#define A_LHAND   2
#define A_BITE    3
#define A_RFOOT   4
#define A_LFOOT   5

/* defines for hitlocs */
#define H_HEAD    0
#define H_BODY    1
#define H_LEGS    2
#define H_WINGS   3

#define FAERIE_ID      "_Avenir_park_faerie"


private static int alarm, seq;

void
create_creature()
{
    setuid();
    seteuid(getuid());
    set_name(({"faerie", "fairy"}));
    add_name(FAERIE_ID);
    set_race_name("faerie");
    set_short("tiny green faerie");
    set_gender(G_FEMALE);
    set_adj(({"tiny", "green"}));
    set_long("She is a tiny green fairy.\n"+
      "She is tiny for a fairy, no bigger than a man's "+
      "thumb.\n"+
      "She looks beautiful.\n"+
      "She seems to be feeling very well.\n"+
      "She is looking dazed.\n"+
      "Her iridescent wings shimmer as she flaps them.\n"+
      "She has innocent dark green eyes.\n"+
      "Her hair is long, pale gold and dripping wet.\n"+
      "She has pale green skin.\n");

    set_alignment(300);

    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(CONT_I_WEIGHT,200);
    add_prop(CONT_I_VOLUME,300);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_m_out("flits");
    set_m_in("flits in");

    set_stats(({2,70,30,30,90,50}));

    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_SNEAK, 60);
    set_skill(SS_HIDE, 60);
    set_skill(SS_AWARENESS, 85);
    set_skill(SS_BLIND_COMBAT, 93);

    set_attack_unarmed(A_WINGS,3,3,W_BLUDGEON,10,"wings");
    set_attack_unarmed(A_RHAND,3,3,W_BLUDGEON,10,"right hand");
    set_attack_unarmed(A_LHAND,3,3,W_BLUDGEON,10,"left hand");
    set_attack_unarmed(A_BITE,5,8,W_IMPALE,50,"bite");
    set_attack_unarmed(A_RFOOT,3,3,W_BLUDGEON,10,"right foot");
    set_attack_unarmed(A_LFOOT,3,3,W_BLUDGEON,10,"left foor");

    set_hitloc_unarmed(H_HEAD, 70, 2,"head");
    set_hitloc_unarmed(H_BODY, 95 , 60,"body");
    set_hitloc_unarmed(H_LEGS, 90 , 30,"legs");
    set_hitloc_unarmed(H_WINGS, 75 , 8,"wings");

    set_cact_time(10);
    add_cact("emote screams in a high pitched voice.");
    add_cact("glare enemy");
    add_cact("growl angr enemy");
    add_cact("emote waves her wings in irritation.");
    add_cact("whine soft");
    add_cact("fume");
    add_cact("point enemy");
    add_cact("shap enemy");
    add_cact("pout .");
    add_cact("emote utters a loud exclamation in a lost language.");

    set_act_time(2);
    add_act("@@act");

    add_leftover(PK + "obj/faerie_wing","wing",2,0,0,0);
}

public void
enter_env(object to, object from)
{
    add_prop(OBJ_M_NO_GIVE, "She doesn't want to go there.");
    add_prop(OBJ_I_NO_GET, "She darts away from you, "+
      "laughing impishly.\n");
    ::enter_env(to, from);
}

public int
leave(void)
{
    object room = ENV();

    if (room == find_object(ZIG_RL2 +"mizrun"))
    {
	tell_room(room,
	  QCTPNAME(TO) +" iridescent wings flutter as she "+
	  "hovers in the air a moment, getting her bearings, "+
	  "before flying upwards to join the dancing green lights "+
	  "high above.\n", ({}), TO);
	TO->remove_object();
    }
    else
    {
	tell_room(room,
	  QCTPNAME(TO) +" iridescent wings flutter as she "+
	  "hovers in the air a moment, getting her bearings, "+
	  "before flying away, a luminous green trail streaking "+
	  "behind her.\n", ({}), TO);
	TO->remove_object();
    }

   return 1;
}

public string
act(void)
{
    if (seq)
	return "";

    if (TO->query_prop(OBJ_I_INVIS))
	return "";

    switch(random(17))
    {
    case 0:
	command("hide");
	break;
    case 1:
	command("giggle wicked");
	break;
    case 2:
	command("stretch");
	break;
    case 3:
	command("emote flits around your head.");
	break;
    case 4:
	command("emote stretches her wings and yawns.");
	break;
    case 5:
	command("smile ador");
	break;
    case 6:
	command("hiccup");
	break;
    case 7:
	command("laugh misch");
	break;
    case 8:
	command("emote rubs her eyes and smiles tiredly.");
	break;
    case 9:
	command("emote sings a rousing drinking song in an ancient language.");
	break;
    case 10:
	command("emote flits around happily.");
	break;
    case 11:
	command("emote sings in a high, lilting voice.");
	break;
    case 12:
	command("emote blinks.");
	break;
    case 13:
	command("gasp");
	break;
    case 14:
	command("smile playfully");
	break;
    case 15:
	command("twinkle");
	break;
    case 16:
	command("laugh softly");
	break;
    }

    return "";
}

public void
faerie_escape(object tp, int count)
{
    object room = environment(TO);
    seq = 1;

    switch(count++)
    {
    case 0:
	break;
    case 1:
	tell_room(room,
	  "Seeming dazed, the tiny green faerie picks herself off the "+
	  "ground, brushing green droplets and chips of glass off "+
	  "her pale green skin.\n", ({}), TO);
	break;
    case 2:
	tell_room(room,
	  "The tiny green faerie jumps, launching herself into the air "+
	  "and pumping her iridescent wings as she takes flight.\n",
	  ({}), TO);
	break;
    case 3:
	if (present(tp, room))
	{
	    tell_object(tp,
	      "The tiny green faerie's iridescent wings flutter as she "+
	      "hovers in the air, pausing a moment to stick her tongue "+
	      "out at you before flying away, a luminous green trail "+
	      "streaking behind her.\n");

	    tell_room(room,
	      "The tiny green faerie's iridescent wings flutter as she "+
	      "hovers in the air, pausing a moment to stick her tongue "+
	      "out at "+ QCTNAME(tp)+ " before flying away, a luminous "+
	      "green trail streaking behind her.\n", ({tp}), TO);

	    TO->move_living("M", PK +"glade", 0, 1);

	}
	else
	{
	    leave();
	}

	break;
    default:
	count = -1;
	break;
    }

    if (count > 0)
    {
	set_alarm(3.0, 0.0, &faerie_escape(tp, count));
    }
    else
    {
	seq = 0;
    }
}

private void
timeout(int count, object tp)
{
    switch(count)
    {
    case 0:
	tp->catch_msg(QCTNAME(TO) +" tinkles in your ear: Hurry up and "+
	    "make your choice, the Lady grows bored easily and so do I.\n");
	tp->catch_tell("\nWho shall it be: ");
	alarm = set_alarm(150.0, 0.0, &timeout(1, tp));
	break;
    case 1:
	tp->catch_msg(QCTNAME(TO) +" tinkles in your ear: You take far "+
	    "too long to decide, your chance is now gone!\n");
        alarm = 0;
	seq = 0;
	move(ENV(ENV()));
	set_alarm(2.0, 0.0, leave);
	break;
    }
}

private void
forget_me(object me, string who)
{
    string name;

    /* Timed out. */
    if (!alarm)
	return;

    remove_alarm(alarm);
    alarm = set_alarm(300.0, 0.0, &timeout(0, me));

    name = OB_NAME(me);

    if (!strlen(who))
    {
	me->catch_msg(QCTNAME(TO) +" tinkles in your ear: Are you deaf?\n");
	me->catch_msg(QCTNAME(TO) +" tinkles in your ear: Name me a name "+
	  "of one that should forget you.\n");

	me->catch_tell("\nWho shall it be: ");
    object oldp = this_player();
    set_this_player(me);    
	input_to(&forget_me(me, ), 0);
    set_this_player(oldp);
	return;
    }

    who = lower_case(who);

    if (who == "q" || who == "quit" || who == "none")
    {
	me->catch_msg(QCTNAME(TO) +" tinkles in your ear: very well if "+
	  "that's your choice.\n");
	me->catch_msg(QCTNAME(TO) +" tinkles in your ear: Just don't expect "+
	  "your offering back.\n");
	me->catch_msg(QCTNAME(TO) +" sticks her tongue out at you as she "+
	   "back-wings off your shoulder.\n");
	tell_room(ENV(me), "As "+ QTNAME(TO) +" back-wings off "+ QTPNAME(me) +
	   " shoulder, sticking her tongue out at "+ HIM(me) +" as she "+
	   "goes.\n", ({me}), TO);

	remove_alarm(alarm);
	alarm = 0;
	seq = 0;

	move(ENV(ENV()));
	set_alarm(2.0, 0.0, leave);
	return;
    }

    if (!SECURITY->exist_player(who))
    {
	me->catch_msg(QCTNAME(TO) +" tinkles in your ear: That name is "+
	    "beyond my reach.\n");

	me->catch_tell("\nChoose another: ");
    object oldp = this_player();
    set_this_player(me);    
	input_to(&forget_me(me, ), 0);
    set_this_player(oldp);
	return;
    }

    int forgot_someone = 0;
    // We also forget the one who will forget us.  And if we don't know them,
    // we will forget someone else at random, that is logged in.
    if (me->query_remembered(who) || me->query_introduced(who))
    {
        (ZIG_OBJ + "altar_mizrun")->gf_forget(who, me->query_real_name());
        (ZIG_OBJ + "altar_mizrun")->gf_forget(me->query_real_name(), who);
        forgot_someone = 1;
    }
    else
    {
        string* can_forget = ({});
        mixed* remembered = m_indexes(me->query_remembered());
        foreach(string name : remembered)
        {
            object player = find_player(name);
            if (player)
            {
                can_forget += ({ name });
            }
        }
        if (sizeof(can_forget))
        {
            (ZIG_OBJ + "altar_mizrun")->gf_forget(who, me->query_real_name());
            (ZIG_OBJ + "altar_mizrun")->gf_forget(me->query_real_name(),
                one_of_list(can_forget));
            forgot_someone = 1;
        }
    }

    if (forgot_someone)
    {
        me->catch_msg(QCTNAME(TO) +" tinkles in your ear: I will do what I can, "+
	    "but I make no guarantees.\n");
    }
    else
    {
        me->catch_msg(QCTNAME(TO) +" tinkles in your ear: A name for a name.\n");
    }

    me->catch_msg(QCTNAME(TO) +" flits off your shoulder.\n");
    tell_room(ENV(me), QTNAME(TO) +" flits off "+ QTPNAME(me) +
	" shoulder.\n", ({me}), TO);

    remove_alarm(alarm);
    alarm = 0;
    seq = 0;

    move(ENV(ENV()));
    set_alarm(2.0, 0.0, leave);
}

public void
faerie_blessing(object tp, int count)
{
    object room = environment(TO);
    seq = 1;

    switch(count++)
    {
    case 0:
	break;
    case 1:
	if (!present(tp, room))		{return;}

	tp->catch_tell("As you place the offering next to the decanter"+
	  ", something solid falls into the basin with "+
	  "a soft 'plop'.\n");
	tell_room(room, "As "+ QTNAME(tp) +" places an offering "+
	  "next to the decanter, something solid falls "+
	  "into the basin with a soft 'plop'.\n", ({tp}), TO);

	break;
    case 2:
	tell_room(room,
	  QCNAME(TO) +" erupts out of the basin, a "+
	  "miniature geyser of green liquid rising in her wake.\n",
	    ({}), TO);
	break;
    case 3:
	if (present(tp, room))
	{
	    tp->catch_msg(
	      QCTPNAME(TO) +" iridescent wings flutter as she "+
	      "hovers in the air, pausing a moment as though to listen to "+
	      "something, and then fliting toward you and landing on your "+
	      "shoulder.\n");

	    tell_room(room,
	      QCTPNAME(TO) +" iridescent wings flutter as she "+
	      "hovers in the air, pausing a moment as though to listen to "+
	      "something, and then fliting toward "+ QTNAME(tp) +" and "+
	      "landing on "+ HIS(tp) +" shoulder.\n", ({tp}), TO);

	    TO->move(tp, 1);
	}
	else
	{
	    leave();
	    count = -1;
	    seq = 0;
	}
	break;
    case 4:
	// Start blessng here.
    {
	string name = OB_NAME(tp);

	tp->catch_msg(QCTNAME(TO) +" tinkles in your ear: The Lady Mizrun "+
	  "is most pleased by your offering and so she bid me offer "+
	  "you this boon.\n");
	tp->catch_msg(QCTNAME(TO) +" tinkles in your ear: Give me the name "+
	  "of one you wish would forget you and I shall slice his "+
	  "mind with Her blessed knife.\n");

	alarm = set_alarm(150.0, 0.0, &timeout(0, tp));
	tp->catch_tell("\nWho shall it be: ");
    object oldp = this_player();
    set_this_player(tp);    
	input_to(&forget_me(tp, ), 0);
    set_this_player(oldp);
	count = -1;
    }
	break;
    default:
	count = -1;
	break;
    }

    if (count > 0)
    {
	set_alarm(3.0, 0.0, &faerie_blessing(tp, count));
    }

}

private void
do_attack(object who)
{
    if (present(who, environment()))
    {
	command("kill " + who->query_real_name());
	command("scream");
    }
}

public void
defend_altar(object who)
{
    if (present(who, environment()))
    {
	command("emote streaks down from the nebulous vapors above, "+
	  "screaming loudly. ARRGGGGGGHHHHHH!!!!");
        add_prop(NPC_I_NO_FEAR, 1);
	command("kill " + who->query_real_name());
	add_prop(LIVE_O_ENEMY_CLING, who);
	command("scream");
    }
}

public void
faerie_help_out(object attacker)
{
    if (!query_attack() && random(2))
	set_alarm(itof(random(6) + 2), 0.0, &do_attack(attacker));
}

public void
attacked_by(object who)
{
    TO->add_prop(LIVE_O_ENEMY_CLING, who);
    filter(all_inventory(ENV(TO)),
	&->id(FAERIE_ID))->faerie_help_out(who);
}

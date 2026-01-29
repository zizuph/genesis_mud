inherit "/std/armour";
inherit "/d/Shire/common/lib/tell";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include <comb_mag.h>
#include <ss_types.h>
#include "defs.h"

create_armour() {
    set_name(({"boots"}));
    set_short("pair of combat boots");
    set_pshort("pairs of combat boots");
    set_adj(({"combat"}));
    set_long(
	  "A pair of combat boots.\n"
	+ "They are obviously made for combat and shielding. "
	+ "They are lite and fits your legs nicely. They will "
	+ "probably increase your kicking capability.\n"
    );

    set_ac(42);
    set_at(A_FEET);

    add_prop(OBJ_I_VALUE, 135+random(100));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1000);
}

init()
{
    ::init();
    add_action("do_kick", "kick");
}

int
do_kick(string str)
{
    object attacker;
    int r,d;
  
    if(!query_worn())
	return 0;

    if(str)
	attacker = present(lower_case(str), EP);
    else
	attacker = this_player()->query_attack();
  
    if(!attacker)
	return notify_fail(
	    "Who do you want to attack with your combat boots?\n");

    if (!living(attacker)) {
	return 0;
    }

    if (attacker == this_player())
    {
	write("What? Kick yourself??\n");
	return 1;
    }


    if(NPATTACK(attacker))
	return notify_fail("You can't fight here.\n");

    if(member_array(attacker, TP->query_enemy(-1))==-1)
	if(!F_DARE_ATTACK(TP, attacker))
	    return notify_fail("Uhum, you do not dare to attack!\n");

    TP->add_prop(LIVE_O_SPELL_ATTACK, TO);
    TP->attack_object(attacker);

    TP->catch_msg(
	"You prepare to launch a kick upon " + QTNAME(attacker) + ".\n");
    attacker->catch_msg(
	QCTNAME(TP)+" seems to prepare an attack upon you!\n");
    say(QCTNAME(TP) + " prepares to attack " + QTNAME(attacker)+ ".\n",
	  ({ TP, attacker}) );

    return 1;
}


public void
spell_attack(object me, object vict)
{
    int r, dam;
    int uskill;
    mixed res;
    string how_kick, good;

    uskill = me->query_skill(SS_UNARM_COMBAT);

    res = vict->hit_me(
		    F_PENMOD(50-random(25), uskill),
		    W_BLUDGEON,
		    TP,
		    -1);

    /* res = ({ proc_hurt, hloc, phit, dam }) */

    switch(res[1])
    {
	case "head":
	    how_kick = "(You) jump[s] up and kick[s] (his) head!";
	    break;
	case "left arm":
	case "right arm":
	    how_kick = "(You) swing[s] around and hit[s] (his) " + res[1] + "!";
	    break;
	case "body":
	    how_kick = "(You) spin[s] around and force [your] foot " +
		       "into (his) body!";
	    break;
	case "legs":
	    how_kick = "(You) sweep[s] (him) and hit[s] [his] feet!";
	    break;
	default:
	    how_kick = "(You) kick (him) and hit[s] [his] " + res[1] + "!";
	    break;
    }


    switch(res[0])
    {
	case -1:
	    good = "However, [your] kick missed completely!";
	    break;
	case 0..9:
	    good = "{Unf;F}ortunately [your] strike only grazes [him].";
	    break;
	case 10..19:
	    good = "[Your] attack hits [him] good!";
	    break;
	case 20..39:
	    good = "[You] cackle[s] grinningly as [you] kick[s] the guts out "
		 + "of [him]!";
	    break;
	case 40..59:
	    good = "[You] smash[es] [him] severely, and (he) {has;have;*} "+
		   "difficulties in standing upright!";
	    break;
	case 60..79:
	    good = "[Your] attack lands {beautifully;smashingly}, and "+
		   "{(he) looks very confused;you can't see straight for a moment;*}!";
	    break;
	case 80..99:
	    good = "[You] snicker[s] as [your] fell attack devastates "+
		   "[him], sending [him] several meters through the air!";
	    break;
	default:
	    good = "(He) stand(s) staggered for a moment as (he) "+
		   "realizes the awesome power of [your] attack!";
    }

    tellem(me, vict, how_kick + "\n" + good + "\n");

    if(HP(vict)<=0)
	vict->do_die(me);
}

     

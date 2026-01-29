#include "defs.h"
#include <wa_types.h>

inherit "/std/shadow";
inherit "/d/Immortal/rogon/open/tell";

hand_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	 int phit, int dam)
{
    string how;
    string hand;
    string what;

    if (dt == 0)
    {
	how = "$punch";
	what = "hand";
    }
    else if (dt == W_BLUDGEON)
    {
	how = "$crush";
	what = "fist";
    }
    else if (dt == W_SLASH)
    {
	how = "$slash";
	what = "claws";
    }
    else
    {
	how = "$pierce";
	what = "claws";
    }

    if (aid == W_RIGHT)
	hand = "right";
    else
	hand = "left";

    produce_message(TO, enemy, phurt,
	({
	"$N $aim at #n's &body with his &right &fist, but $miss #him by inches!",
	"$N $launch a terrible swing against #n's &body, but #he #duck and #jump away!",
	"$N $scream out in anger, as $p &right &fist unmercifully strikes #n's &body!",
	"$N $roar in terrible insane anger, as $s &strike a mighty strike hitting #n's "+
	    "&body with $p &right &fist!!",
	"$N $laugh evilly at #n, as $s &strike a terrible blow hitting #n's &body!!",
	"$N $cackle at #n with an omnious glee, as $p &right &fist shatters #p &body "+
	    "with awesome power!!",
	"$N $send #n sprawling into the air as $s &strike #n with $p terrible &right "+
	    "&fist's!!",
	"In a scene of insane vanguish, $n &strike #n's &body with $p &right &fist!!",
	"$N &strike #n's &body terribly using $his mighty &right &fist!!!",
	"#N #have no chances against $n's ungodly powers as $s &strike #n's &body with $p "+
	    "terrible &right &fist!!!!",
	"#N #scream out in agony and pain as $n &strike through #his &body!!!\n" +
	    "#N almost #die on the spot!!!!!",
	"In an unearthly scream of utter pain and destruction, " +
	    "#n #fall like a puddle of meat under $n's " +
	    "deadly &right &fist's singular devastation!!!!!"
	}), ([ "&strike":how, "&body":hdesc, "&right":hand, "&fist":what ])
    );

    if (HP(enemy) <= 0)
    {
	enemy->command("scream");
	enemy->catch_msg(
	    "A deadly scene of fire and destruction is your last view of the "
	  + "world as you are demolished firmly and stepped upon by the "
	  + "immensely large and terrible Balrog." +
	    "You die immediately.\n");
	tell_room(ENV(TO),
	    "In a devastating scene of brutal power and destruction, the " +
	    "immensely large and terrible Balrog demolishes " + QTNAME(enemy) +
	    " as he firmly steps upon him and squeezes his remains into the floor!!\n"+
	    QCTNAME(enemy) + " dies instantly.\n", enemy);
	enemy->do_die(TO);
    }
    return 1;
}

foot_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	 int phit, int dam)
{
    string how_kick;
    string good;

    switch (hdesc)
    {
	case "head":
	    how_kick = "$N $jump up and $kick #n's head!";
	    break;
	case "left arm":
	case "right arm":
	    how_kick = "$N $swing around and $kick #n's " + hdesc + "!";
	    break;
	case "body":
	    how_kick = "$N $spin around and $force $p foot " +
		       "into #n's body!";
	    break;
	case "legs":
	    how_kick = "$N $sweep #n's feet!";
	    break;
	default:
	    how_kick = "$N $kick #n hitting #p " + hdesc + "!";
	    break;
    }

    switch (phurt)
    {
	case -1:
        case -2:
	    good = "However, $p kick missed completely!";
	    break;
	case 0..9:
	    good = "But $his strike only grazed #him.";
	    break;
	case 10..19:
	    good = "It hurts #n badly!";
	    break;
	case 20..39:
	    good = "$_You $cackle grinningly as $he $kick the guts out "
		 + "of #n!";
	    break;
	case 40..59:
	    good = "$_You $smash #him severely, and #n #have "+
		   "difficulties in standing upright!";
	    break;
	case 60..79:
	    good = "It lands ${beautifully;smashingly}, and "+
		   "${#he looks very confused;you can't see straight for a moment}!";
	    break;
	case 80..99:
	    good = "$_You $snicker as $your fell attack devastates "+
		   "#n, sending #him several meters through the air!";
	    break;
	default:
	    good = "#_You #stand staggered for a moment as #_you "+
		   "#realize the awesome power of the $race's attack!";
    }

    tellem(TO, enemy, how_kick + " " + good + "\n");

    if (HP(enemy) <= 0)
    {
	enemy->catch_msg(
	    "As the Fire Spirit launches the terrible kick you feel bones " +
	    "crush and your heart stops beeting as you land like a gory " +
	    "piece of meat, utterly massacrated and dead...\n");
	tell_room(ENV(TO),
	    QCTNAME(TO) + " launches a terrible kick hitting " + QTNAME(enemy) +
	    " awfully, crushing " + HIS_HER(enemy) + " mere bones to a " +
	    "bloody splinter of gore, splat and blood, whereby " + QTNAME(enemy) +
	    " lands as a piece of dead meat in a corner.\n", enemy);
	enemy->do_die(TO);
    }
    return 1;
}

/*
 * Function name: cr_did_hit
 *
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *		  humanoid combat. (called from heart_beat)
 *
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *		  dt:	 The current damagetype
 *		  phit:  The %success that we made with our weapon
 *		  dam:	 The damamge made in hitpoints
 */
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	   int phit, int dam)
{
    if (aid == W_RIGHT || aid == W_LEFT)
	return hand_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (aid == W_FOOTR || aid == W_FOOTL)
	return foot_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    return 0;
}

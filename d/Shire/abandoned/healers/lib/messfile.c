/*  -*- LPC -*-  */
/*
 * messfile.c
 *
 * It is my firm belief that players want more vivid attack descriptions,
 * hence this file is made to make other descriptions than usual.
 *
 * It relies on the damage type definitions, but these coinside with
 * W_IMPALE, W_SLASH and W_BLUDGEON, so you can use this file for plain
 * weapon damage as well.
 *
 * It uses the TELL_FILE: /d/Immortal/rogon/lib/tell.c to produce the
 * messages. See that file for an introduction to the action-format.
 *
 * Sir Rogon.
 *
 * It can be interesting to compare with standard messages:

    "$You aim for #'s{_head}, but $miss.",
    ({
    "$You $hit #n's _head with $your _weapon, without effect.",
    "$You $tickle #n's _head with $your _weapon.",
    "$You $graze #n's _head with $your _weapon.",
    "$You $hurt #n's _head with $your _weapon.",
    "$You $hurt #n's _head with $your _weapon, rather bad.",
    "$You $hurt #n's _head with $your _weapon, very bad.",
    "$You $smash #n's _head with $your _weapon, very hard.",
    "$You $smash #n's _head with $your _weapon, with a bone crushing sound.",
    "$You $massacre #n's _head with $your _weapon."
    });

 */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <options.h>

inherit TELL_FILE;

static private mapping message = ([ 
    DT_IMPALE: ({
       "$You $stab the air next to #n with $your _weapon.",
       ({
	   "#N #giggle as $you harmlessly $poke #his tummy with $your _weapon.",
	   "$You $nick $your _weapon in #his _head#{with a near stab!;.}",
	   "$You $puncture #n's _head with $your _weapon.",
	   "$You $impale #n's _head with $p _weapon#{!;.}",
	   "$You $puncture #n's _head neatly with $p _weapon.",
	   "$You $give #n a shallow puncture in #p _head with $p _weapon.",
	   "$You $give #n a painful puncture wound in #p _head with $p _weapon!",
	   "With a staggering performance, $n $spin $p _weapon and yields #n a " +
	       "thorough puncture in #p _head!",
	   "$N $deal a deep, piercing blow into #n's _head with $p _weapon! "+
	       "#S #bleed profusely!",
	   "$N $impale #n's _head deep and gory with $p _weapon!!"
       }),
       "$N's _weapon impales #n's chest and #s #die with a gurgling sound in #p throat."
   }),
      
   DT_SLASH: ({
       "$N $swing $p _weapon aimlessly around #n.",
       ({
	   "The air whistles as #n narrowly avoids $n's _weapon's dangerous slash.",
	   "$N's _weapon touches #n's _head, making a {nice;dangerously close;sour} flesh wound.",
	   "$N $cut #n's _head neatly with $p _weapon.",
	   "$N $perform a nice swing with $p _weapon. It strikes #n's _head.",
	   "$N $slash #n's _head with $p _weapon, and blood begins to trickle!",
	   "#N #are badly hurt as $n's _weapon slashes #p _head deeply.", 
	   "$N $hit #n wickedly with your $p _weapon, leaving a gaping, bloody wound.",
	   "$N $gut #n's _head with a mighty slash, and #p blood begins to trickle.",
	   "$N's slash with $p _weapon hews deeply into #n's _head, and #s is momentarily stunned.",
	   "$N $strikes #n's _head in absolute {beauty;terror;*}, $trembling #o in utter fair of "+
	       "$n's extreme ${performance;violence}!!"
	  }),
	  "$N $swing $p _weapon towards #n's _head and $hit #o with a sickening crunching sound. "+
	  "#N ${falls lifeless to the ground in a puddle of blood;hear a sharp snap and die}."
      }),
          
   DT_BLUDGEON: ({
       "$N $swing around $p _weapon, hitting but thin air.",
	({
	      "#N #laugh mockingly as $n barely $bump $p _weapon into #p _head.",
	      "#N #sigh badly as $n's _weapon hits #p _head.", 
	      "$N almost $unbalance #n as $p _weapon hits #p _head.",
              "$N $perform a heavy blow with $p _weapon, hitting #n's _head.",
	      "#N #stagger as $n crushingly $hammer $p _weapon upon #p _head.",
              "$N crushingly $schmack #n's _head with $p _weapon.",
	      "$N $smash $p _weapon upon #n's _head, with a bone crushing sound.",
	      "$N $break several of #n's bones as $n smash $p _weapon into #p _head.",
	      "$N's _weapon almost crushes #n to a bloody pulp with a mighty blow into #p _head."
          }),
	  "$N's _weapon brutaly crushes #n's _head with a shattering force. #S "+
	  "{is knocked down on the _floor leaving a smashed and barely recognizable corpse.;see red, black, then nothing.;*}",
      }),

      DT_ACID: ({
	  "$N $make a sour stench with $p acid near #n.",
	  ({
	      "$N $stain #n's skin with acid.",
	      "$N's acid $sting #n's skin.",
	      "$N $burn #n somewhat with $p acid.",
	      "$N's acid stings #n's eyes!",
	      "$N's burning acid makes #n whine in pain!",
	      "$N's acid eats through #n's flesh and #s screams in agony!\n"
	  }),
	  "$N's acid eats #n alive, "+
	  "{leaving a smoking, mangled corpse and a sickening stench of burned flesh;"+
	  "and you almost manage to scream in pain before you die;"+
	  "leaving a smoking, mangled corpse and a sickening stench of burned flesh}."
      }),

      DT_HEAT: ({
	  "$N $make the air hot around #n.\n",
          ({
	      "$N $snicker as $s $burn some of #n's hair off.",
	      "$N's heat surrounds #n, making #o sweat profusely.",
	      "$N's fire scorches #n and red blisters appear on #p skin.",
	      "$N's flames envelops #n and #s #cry out loudly in pain.",
	      "$N $burn #n severely, carbonizing #p entire body.",
	      "$N $burn #n almost completely to cinders, and #s #scream in agony."
          }),
	  "$N's flames totally consume #n, "+
	  "and #s ${falls lifeless to the ground, still burning.;"+
	  "choke a scream before you die in agony.}"
      }),

      DT_COLD: ({
	  "$N $make the air cold around #n's ears.\n",
	  ({
	      "$N $cover #n with rime, making #o shiver{ing;;*} from the cold.",
	      "$N $cover #n's body with snow and ice.",
	      "$N's cold makes #n's skin crackle in a glitter of ice.",
	      "$N's cold makes #n's limbs stiffen, and #s {has;have;*} problems moving.",
	      "$N $freeze #n badly, and #s #yelp in pain!",
	      "$N's cold partly makes #n ice, and #s #freeze completely for a moment.",
          }),
	  "$N $freeze #n to a solid ice statue"+
	  "${ that tilts and hits the ground with a THUD!;"+
	  ". You hit the ground with a THUD before dying an agonizing death}.",
      }),

      DT_IMPACT: ({
	  "$N $miss #n.",
          ({
	      "$N $shake #n, but #s #stand firmly.",
	      "$N's blast pushes #n backwards, but #s #regain #p balance.",
	      "$N's blow knocks #n off #p feet!",
	      "$N's impact makes #n fall and roll a few meters before getting up again.",
	      "$N's blast sends #n sprawling backwards, landing hard on #p head.",
	      "$N's forceful impact hurls #n on #p back, breaking some of #p bones in the process.",
          }),
	  "$N's final blast smashes #n's bones to shards, and #p "+
	  "{skull crumbles to dust.;head crumbles to nothing as you meet certain death.;*}"
      }),

      DT_ELECTRICITY: ({
	  "$N $charge the air around #n.",
          ({
	      "#N #sizzle as $n $charge #o with current.",
	      "#N #jump as $n $give #o an electric shock.",
	      "$N's attack causes sparks to fly from #n's fingers.",
	      "$N's lightning hits #n and stuns #o.",
	      "#N's body stiffens as $n's lightning flashes around #o.",
	      "$N's lightning ravages #n's body while #s #spasm and #scream terribly.",
          }),
	  "#N's nervous system flashes up as $n's lightning provides a fine light show. "+
	  "#N {then falls lifeless to the ground.;"+
	  "fall over in a very electrifying death.;*}"
      }),

      DT_VIBRATION: ({
	  "#N #laugh as $n's strike tickles #p side.",
	  ({
	       "#N #are slightly amazed as #p belly shakes to and forth.",
	       "$N $shake #n making him puke on #p shoes.",
	       "$N $laugh as #s #shake around like a maniac.",
	       "$N's strike unbalances #n shattering #p legs.",
	       "$N's strike breaks #n's ribs and tears #p cartilage.",
	       "#N #are knocked down and stunned as $n's strike breaks #p bones and muscles."
	  }),
	  "$N's major head strike turns #n's eyes to jelly, #p ears quiver and #p head is "+
	  "filled with a load HUM {as the brain ceases to function.;the moment before you realize your death.;*}"
      }),

      DT_RADIATION: ({
	  "#N #close #n's eyes for a second.",
	  ({
		"#N's eyes is temporarily blinded due to $n's attack.",
		"$N's flash of light makes #n stumble in #p feet.",
		"$N's intense flash of light stunnes #n for seconds.",
		"$N's intense radiaton make #n's face swell up.",
		"In an explosion of intense light and smoke, #s #are knocked down and stunned.",
		"Hot smoke and light knocks #n down screaming in agony and pain."
	  }),
	  "$N's extreme radiation falls upon #n with devastating effect. "+
	  "#S #fall down, #puke on #p shoes, {dying instantly with scorches and "+
	  "inner damages.;and you die feeling a terrible pain in your body.;*}"
      }),

      DT_VACUUM: ({
	  "#N #smile as #s #listen to $n's funny crackling sounds.",
	  ({
		"$N's attack sizzles through #n's ears.",
		"$N's strike stuns #n with a roaring sound.",
		"$N $shock #n with an intense and painful noise.",
		"$N's shock slams into #n's body, knocking #o down.",
		"#N #are torn apart as a devastating shock hits #p body.",
		"$N's shattering blow strikes #n, breaking #p ribs and organs."
	  }),
	  "$N's blast annihilates #n's entire skeleton, reducing #o to a "+
	  "gelatinous pulp. {(Try a spatula.);You die at once.;*}"
      })
]);

void
do_tell(object att, object def, string mess, string desc, string what)
{
    mess = replace_string(mess, "_weapon", what);
    mess = replace_string(mess, "_head", desc);
    if(environment(att)->query_prop(ROOM_I_INSIDE))
	mess = replace_string(mess, "_floor", "floor");
    else
	mess = replace_string(mess, "_floor", "ground");

    tellem(att, def, mess);
}

int
message(object att, object enemy, int dt, string hdesc, int phurt, string what)
{
    int size;
    int no;

    if (!living(enemy))
	return 0;

    if(member_array(dt, ({ DT_IMPALE, DT_SLASH, DT_BLUDGEON, DT_ACID, DT_HEAT,
			   DT_COLD, DT_IMPACT, DT_ELECTRICITY, DT_VIBRATION,
			   DT_RADIATION, DT_VACUUM })) == -1 )
    {
        tellem(att, enemy, "$You $aim for #n's " + hdesc + ", but $miss.\n");
	return 1;
    }

    if (HP(enemy) <= 0)
    {
	do_tell(att, enemy, message[dt][2] + "\n", hdesc, what);
	return 1;
    }

    switch(phurt)
    {
	case -1:
	    do_tell(att, enemy, message[dt][0]+"\n", hdesc, what);
	    break;
	case 0:
            do_tell(att, enemy, message[dt][1][0]+"\n", hdesc, what);
            break;
        case 1..99:
            size = sizeof(message[dt][1]) - 1;
            no = ftoi(pow(itof(phurt)/100.0, 0.33) * itof(size));  
            if (no >= size) no = size - 1;
	    do_tell(att, enemy, message[dt][1][1+no]+"\n", hdesc, what);
	    break;
	default:
	    do_tell(att, enemy, message[dt][2]+"\n", hdesc, what);
    }
    return 1;
}








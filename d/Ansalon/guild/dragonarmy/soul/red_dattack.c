#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "../guild.h"

int
query_dattack_damage_type()
{
    return W_IMPALE;
}

int
query_dattack_weapon_pen(object tp, object weapon)
{
    int pen = tp->query_stat(SS_STR) /2;
    pen += tp->query_stat(SS_DEX) /2;
    pen += tp->query_stat(SS_INT) /5;
    pen /= 3;
    pen += (3 * weapon->query_pen()) / 4;
    return pen;
}

void
dattack_message(object tp, object target,
  string weapon, int weapon_type,
  int phurt, string hitloc, int phit, int dam)
{
    string *attack_message;

    if (phurt >= 0)
    {
	switch(phurt)
	{
	case 0:
	    attack_message = ({
	      "Crouching low, you set your " +weapon+ " into a " +
	      "defensive position, keeping "+
	      target->query_the_name(tp)+ " back while you formulate " +
	      "a plan of attack.\n",

	      "Crouching low, " +tp->query_the_name(target)+ " sets "+
	      HIS(tp)+ " " +weapon+ " into a defensive position, keeping "+
	      "you back while " +HE(tp)+ " formulates a plan of attack.\n",

	      "Crouching low, "+QTNAME(tp)+ " sets " +HIS(tp)+ " "+
	      weapon+ " into a defensive position, keeping "+
	      QTNAME(target)+ " back "+
	      "while " +HE(tp)+ " formulates a plan of attack.\n"
	    });
	    break;
	case 1..2:
	    attack_message = ({
	      "You thrust forward at " +target->query_the_name(tp)+ " with "+
	      "your " +weapon+ ", but inflict little more than a graze "+
	      "on " +HIS(target)+ " " +hitloc+ ".\n",
	      tp->query_The_name(target)+ " thrusts forward at you with "+
	      HIS(tp)+ " " +weapon+ ", but inflicts little more than " +
	      "a graze upon your " +hitloc+ ".\n",
	      QCTNAME(tp)+ " thrusts forward at " +QTNAME(target)+
	      " with " +HIS(tp)+ " " +weapon+ ", but inflicts " +
	      "little more damage than a graze.\n"
	    });
	    break;
	case 3..5:
	    if(weapon_type == W_SWORD || weapon_type == W_KNIFE)
		attack_message = ({
		  "With a wild laugh, you fake a thrust with your " +weapon+
		  ", and then nonchalantly backhand " +target->query_the_name(tp)+
		  " across " +HIS(target)+ " " +hitloc+ " with the " +
		  "flat of your blade.\n",

		  "With a wild laugh, " +tp->query_the_name(target)+ " fakes a thrust with " +
		  HIS(tp)+ " " +weapon+ ", and then nonchalantly backhands " +
		  "you across your " +hitloc+ " with the flat of " +
		  HIS(tp)+ " blade.\n",

		  "With a wild laugh, " +QTNAME(tp)+ " fakes a thrust with " +
		  HIS(tp)+ " " +weapon+ " at " +QTNAME(target)+ ", and then " +
		  "nonchalantly backhands " +HIM(target)+ " across " +
		  HIS(target)+ " " +hitloc+ " with the flat of " +HIS(tp)+ " " +
		  "blade.\n"
		});
	    else
		attack_message = ({
		  "You swiftly strike out at " +target->query_the_name(tp)+
		  "'s " +hitloc+ ", but only score a glancing blow with " +
		  "your " +weapon+ ".\n",
		  tp->query_The_name(target)+ " swiftly strikes out at your "+
		  hitloc+ ", but only manages to score a glancing blow with "+
		  HIS(tp)+ " " +weapon+ ".\n",
		  QCTNAME(tp)+ " swiftly strikes out at "+
		  QTNAME(target)+ "'s " +hitloc+
		  ", but only scores a glancing blow with " +HIS(tp)+ 
		  " " +weapon+ ".\n"
		});
	    break;
	case 6..10:
	    if(weapon_type == W_SWORD || weapon_type == W_KNIFE)
		attack_message = ({
		  "Breaking through " +target->query_the_name(tp)+ "'s guard, " +
		  "you bash " +HIM(target)+ " with the hilt of your " +weapon+ ".\n",

		  "Breaking through your guard, " +tp->query_the_name(target)+ " bashes you " +
		  "with the hilt of " +HIS(tp) + " " +weapon+ ".\n",

		  "Breaking through " +QTNAME(target)+ "'s guard, " +QTNAME(tp)+
		  " bashes " +HIM(target)+ " with the hilt of " +HIS(tp)+
		  " " +weapon+ ".\n"
		});
	    else
		attack_message = ({
		  "Reversing your " +weapon+ ", you craftily strike " +target->query_the_name(tp)+
		  " with a solid blow to the " +hitloc+ ".\n",

		  "Reversing " +HIS(tp)+ " " +weapon+ ", " +tp->query_the_name(target)+
		  " craftily strikes you a solid blow to the " +hitloc+ ".\n",

		  "Reversing " +HIS(tp)+ " " +weapon+ ", " +QTNAME(tp)+
		  " craftily strikes " +QTNAME(target)+ " a solid blow " +
		  "to the " +hitloc+ ".\n"
		});
	    break;
	case 11..20:
	    attack_message = ({
	      "You lunge towards " +target->query_the_name(tp)+ "'s " +hitloc+
	      " with your " +weapon+ ", scoring a minor flesh wound.\n",

	      tp->query_The_name(target)+ " lunges forward at your " +hitloc+ " with "+
	      HIS(tp)+ " " +weapon+ ", scoring a minor flesh wound.\n",

	      QCTNAME(tp)+ " lunges forward at " +QTNAME(target)+ "'s " +hitloc+
	      ", scoring a minor flesh wound.\n"
	    });
	    break;
	case 21..30:
	    attack_message = ({
	      "You drive forward at " +target->query_the_name(tp)+ "'s " +hitloc+
	      ", piercing a gaping wound with your " +weapon+ ".\n",

	      tp->query_The_name(target)+ " drives forward at your " +hitloc+
	      ", piercing a gaping wound with " +HIS(tp)+ " " +weapon+ ".\n",

	      QCTNAME(tp)+ " drives forward at " +QTNAME(target)+ "'s "+
	      hitloc+ ", piercing a gaping wound with " +HIS(tp)+
	      " " +weapon+ ".\n"
	    });
	    break;
	case 31..50:
	    attack_message = ({
	      "Lunging powerfully with your " +weapon+ ", you "+
	      "open a crippling wound in " +target->query_the_name(tp)+
	      "'s " +hitloc+ ".\n",

	      "Lunging powerfully at you with " +HIS(tp)+ " " +weapon+
	      ", " +tp->query_the_name(target)+ " opens a crippling wound in your " +
	      hitloc + ".\n",

	      "Lunging powerfully with " +HIS(tp)+ " " +weapon+ ", "+
	      QTNAME(tp)+ " opens a crippling wound in " +
	      QTNAME(target)+ "'s " +hitloc+ ".\n"
	    });
	    break;
	case 51..75:
	    attack_message = ({
	      "Avoiding a desperate attack by " +target->query_the_name(tp)+
	      ", you thrust your " +weapon+ " down into "+
	      HIS(target)+ " " +hitloc+ " with deadly accuracy.\n",

	      "Avoiding a desperate attack of yours, " +tp->query_the_name(target)+
	      " thrusts " +HIS(tp)+ " " +weapon+ " down into "+
	      "your " +hitloc+ " with deadly accuracy.\n",

	      "Avoiding a desperate attack by " +QTNAME(target)+
	      ", " +QTNAME(tp)+ " thrusts " +HIS(tp)+ " "+
	      weapon+ " down into " +QTNAME(target)+ "'s "+
	      hitloc+ " with deadly accuracy.\n"
	    });
	    break;
	case 76..99:
	    attack_message = ({
	      "In shock, " +target->query_the_name(tp)+ " clutches " +
	      HIS(target)+ " " +hitloc+ " as you deal " +HIM(target)+
	      " a mortal wound. You notice in grim satisfaction the " +
	      "ammount of blood starting to pool around " +HIM(target)+
	      ".\n",

	      "In shock, you clutch your " +hitloc+ " after " +
	      tp->query_the_name(target)+ " deals you a mortal wound. You notice " +
	      "in horror a great deal of your lifeblood is starting " +
	      "to pool around your feet.\n",

	      "In shock, " +QTNAME(target)+ " clutches at " +
	      HIS(target)+ " " +hitloc+ " after " +QTNAME(tp)+
	      " deals " +HIM(target)+ " a mortal wound. You notice " +
	      "in morbid fascination a great deal of blood starting " +
	      "to pool around " +QTNAME(target)+ ".\n"
	    });
	default:
	    attack_message = ({
	      "In triumph, you raise your " +weapon+ " in a mock " +
	      "salute, then with a downward lunge you swiftly " +
	      "impale " +target->query_the_name(tp)+ " to the ground, "+
	      "dealing " +HIM(target)+ " a gruesome "+
	      "death blow.\n",

	      "In triumph, " +tp->query_the_name(target)+ " raises " +HIS(tp)+ " " +
	      weapon+ " in a mock salute to you, then with a savage " +
	      "downward lunge, " +HE(tp)+ " impales you to the ground, "+
	      "dealing you a gruesome death blow.\n",

	      "In triumph, " +QTNAME(tp)+ " raises " +HIS(tp)+ " " +
	      weapon+ " in a mock salute, then with a savage " +
	      "downward lunge, " +HE(tp)+ " impales " +QTNAME(target)+
	      " to the ground, dealing " +HIM(target)+ " a gruesome "+
	      "death blow.\n"
	    });
	    break;
	}

	tp->catch_tell(attack_message[0]);
	target->catch_tell(attack_message[1]);
	tp->tell_watcher(attack_message[2], target);
    }
    else
    {
	tp->catch_tell("You snarl in anger as your well-timed thrust "+
	  "at " +target->query_the_name(tp)+ " is anticipated and " +
	  "deftly avoided.\n");
	target->catch_tell(tp->query_The_name(target)+ " snarls in anger at "+
	  "you as you anticipate "+HIS(tp)+" attack and deftly avoid it.\n");
	tp->tell_watcher_miss(QCTNAME(tp)+ " snarls in anger as " +HIS(tp)+
	  " well-timed thrust at " +QTNAME(target)+ " is anticipated and deftly "+
	  "avoided.\n", target);
    }
}


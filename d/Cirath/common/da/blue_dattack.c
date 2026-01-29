#include <macros.h>
#include <wa_types.h>
#include "../guild.h"

void
dattack_do_die(object tp, object target)
{
    object corpse, head;

    target->do_die(tp);
    return;
/*
    if (target->query_prop(LIVE_I_NO_CORPSE))
    {
	target->do_die(tp);
	return;
    }
    else
    {
        if (!objectp(corpse = (object)target->make_corpse()))
        {
            corpse = clone_object("/std/corpse");
            corpse->set_name(query_name());
            corpse->change_prop(CONT_I_WEIGHT, query_prop(CONT_I_WEIGHT));
            corpse->change_prop(CONT_I_VOLUME, query_prop(CONT_I_VOLUME));
            corpse->add_prop(CORPSE_S_RACE, query_race_name());
            corpse->add_prop(CONT_I_TRANSP, 1);
            corpse->change_prop(CONT_I_MAX_WEIGHT,
                                query_prop(CONT_I_MAX_WEIGHT));
            corpse->change_prop(CONT_I_MAX_VOLUME,
                                query_prop(CONT_I_MAX_VOLUME));
            corpse->add_leftover(query_leftover());
        }

        corpse->add_prop(CORPSE_AS_KILLER,
                         ({ killer->query_real_name(),
                                killer->query_nonmet_name() }) );
        corpse->move(environment(this_object()), 1);
        move_all_to(corpse);
    }

    if (!enemy->query_prop(LIVE_I_NO_CORPSE))
    {
        enemy->add_prop(LIVE_I_NO_CORPSE, 1);
        enemy_race = QRACE(enemy);
        i = enemy->query_prop(CONT_I_WEIGHT);

        enemy->do_die(who);
        FIXEUID;
        pulp = clone_object("/std/leftover");
        pulp->set_amount(i);
        pulp->leftover_init("pulp", enemy_race);
        pulp->set_adj(({"bloody",enemy_race}));
        pulp->set_short("bloody "+enemy_race+" pulp");
        pulp->set_long("This is the pulp that is left after you thoroughly "+
                       "smash "+LANG_ADDART(enemy_race)+".\n");
        pulp->move(ENV(who), 0);
    }
*/
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
	      "Crouching low, you swing your " +weapon+ " in an arc, keeping " +
	      target->query_the_name(tp)+ " back while you formulate " +
	      "a plan of attack.\n",

	      "Crouching low, " +tp->query_the_name(target)+ " swings " +
	      HIS(tp)+ " " +weapon+ " in an arc, keeping " +
	      "you back while " +HE(tp)+ " formulates a plan of attack.\n",

	      "Crouching low, " +QTNAME(tp)+ " swings " +HIS(tp)+ " " +
	      weapon+ " in an arc, keeping " +QTNAME(target)+ " back " +
	      "while " +HE(tp)+ " formulates a plan of attack.\n"
	    });
	    break;
	case 1..2:
	    attack_message = ({
	      "With a careless swing of your " +weapon+ ", you manage to graze the " +
	      hitloc+ " of " + target->query_the_name(tp)+ ".\n",

	      "With a careless swing of " +HIS(tp)+ " " +weapon+ ", " +
	      tp->query_the_name(target)+ " manages to graze your " +hitloc+ ".\n",

	      "With a careless swing of " +HIS(tp)+ " " +weapon+ ", " +
	      QTNAME(tp)+ " manages to graze the " +hitloc+ " of " +QTNAME(target) + ".\n"
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
		  "With a swift swing, you strike " +target->query_the_name(tp)+
		  " a glancing blow to the " +hitloc+ " with the haft " +
		  "of your " +weapon+ ".\n",

		  "With a swift swing, " +tp->query_the_name(target)+ " strikes you a glancing " +
		  "blow to the " +hitloc+ " with the haft of " +HIS(tp)+
		  " " +weapon+ ".\n",

		  "With a swift swing, " +QTNAME(tp)+ " strikes " +QTNAME(target)+
		  " a glancing blow to the " +hitloc+ " with the " +
		  "haft of " +HIS(tp) + " " +weapon+ ".\n"
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
	      "You slash at " +target->query_the_name(tp)+ "'s " +hitloc+
	      " with your " +weapon+ ", scoring a minor flesh wound.\n",

	      tp->query_The_name(target)+ " slashes at your " +hitloc+ " with "+
	      HIS(tp)+ " " +weapon+ ", scoring a minor flesh wound.\n",

	      QCTNAME(tp) + " slashes at " +QTNAME(target)+ "'s " +hitloc+
	      ", scoring a minor flesh wound.\n"
	    });
	    break;
	case 21..30:
	    attack_message = ({
	      "You slash at " +target->query_the_name(tp)+ "'s " +hitloc+
	      ", cutting a painful wound with your " +weapon+ ".\n",

	      tp->query_The_name(target)+ " slashes at your " +hitloc+ ", cutting " +
	      "a painful wound with " +HIS(tp)+ " " +weapon+ ".\n",

	      QCTNAME(tp)+ " slashes at " +QTNAME(target)+ "'s " +
	      hitloc+ ", cutting a painful wound with " +HIS(tp)+
	      " " +weapon+ ".\n"
	    });
	    break;
	case 31..50:
	    attack_message = ({
	      "With a powerful swing of your " +weapon+ ", you slash " +
	      "open a crippling wound in " +target->query_the_name(tp)+
	      "'s " +hitloc+ ".\n",

	      "With a powerful swing of " +HIS(tp)+ " " +weapon+
	      ", " +tp->query_the_name(target)+ " opens a crippling wound in your " +
	      hitloc + ".\n",

	      "With a powerful swing of " +HIS(tp)+ " " +weapon+ ", " +
	      QTNAME(tp)+ " opens a crippling wound in " +
	      QTNAME(target)+ "'s " +hitloc+ ".\n"
	    });
	    break;
	case 51..75:
	    attack_message = ({
	      "Avoiding a desperate attack by " +target->query_the_name(tp)+
	      ", you bring your " +weapon+ " down upon " +
	      HIS(target)+ " " +hitloc+ " with deadly accuracy.\n",

	      "Avoiding a desperate attack of yours, " +tp->query_the_name(target)+
	      " brings " +HIS(tp)+ " " +weapon+ " down upon " +
	      "your " +hitloc+ " with deadly accuracy.\n",

	      "Avoiding a desperate attack by " +QTNAME(target)+
	      ", " +QTNAME(tp)+ " brings " +HIS(tp)+ " " +
	      weapon+ " down upon " +QTNAME(target)+ "'s " +
	      hitloc+ " with deadly accuracy.\n"
	    });
	    break;
	case 76..99:
	    attack_message = ({
	      "In shock, " +target->query_the_name(tp)+ " clutches " +
	      HIS(target)+ " " +hitloc+ " as you deal " +HIM(target)+
	      " a mortal wound. You notice in grim satisfaction the " +
	      "amount of blood starting to pool around " +HIM(target)+
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
	    break;
	default:
	    attack_message = ({
	      "In triumph, you raise your " +weapon+ " in a mock " +
	      "salute, then with a downward chop upon " +target->query_the_name(tp)+
	      "'s neck you deal " +HIM(target)+ " a gruesome " +
	      "death blow.\n",

	      "In triumph, " +tp->query_the_name(target)+ " raises " +HIS(tp)+ " " +
	      weapon+ " in a mock salute to you, then with a savage " +
	      "downward chop upon your neck, " + HE(tp)+
	      " deals you a gruesome death blow.\n",

	      "In triumph, " +QTNAME(tp)+ " raises " +HIS(tp)+ " " +
	      weapon+ " in a mock salute, then with a savage " +
	      "downward chop upon " +QTNAME(target)+ "'s neck" +
	      " deals " +HIM(target)+ " a gruesome " +
	      "death blow.\n"
	    });
	}

	tp->catch_tell(attack_message[0]);
	target->catch_tell(attack_message[1]);
	tp->tell_watcher(attack_message[2], target);
    }
    else
    {
	tp->catch_tell("You snarl in anger as your well-timed slash " +
	  "at " +target->query_the_name(tp)+ " is anticipated and " +
	  "deftly avoided.\n");
	target->catch_tell(tp->query_The_name(target)+ " snarls in anger at "+
	    "you as you anticipate "+HIS(tp)+" attack and deftly avoid it.\n");
	tp->tell_watcher_miss(QCTNAME(tp)+ " snarls in anger as " +HIS(tp)+
	  " well-timed slash at " +QTNAME(target)+ " is anticipated and deftly " +
	  "avoided.\n", target);
    }
}


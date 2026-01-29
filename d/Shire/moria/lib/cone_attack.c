/*
 * cone_attack.c
 *
 * This file is to be inherited by cone-breathing worms, like
 * for instance the dragon inside of Moria.
 *
 */

/*----------------------------------------------------------------------------

  Description.
  ------------
  A cone attack is done by specifying the target. A random number
  of additional targets are selected (now just random, in the future
  I hope to get a ranged system with positions within the room).


          |<--------length-------->|<-r->|
                               ......._
                         .....     .    .
                   .....           .     .
         ,   ....._________________.o|   !
     '## /=  .....-----------------.#'   !
     |_--\_        .....           .     .
                         .....     .    .
  Dragon breathes              .......-


  It must be inherently much more dangerous to be damaged by the
  enemy's natural element attack than any wizards conjuration of 
  the elements, thus the attacks will be strong. How strong is defined
  in the variable: 

      cone_size :   
	  CONE_TINY        (0)
	  CONE_SMALL       (1)
	  CONE_MEDIUM      (2)
	  CONE_LARGE       (3)
	  CONE_SUPER_LARGE (4)
	  CONE_HUGE        (5)

      cone_length: [meters]
          Tells how far the cone can reach.

      cone_duration:
          How many seconds this attack continues. (Must be < cone_size.)

      cone_prepare:
          How many seconds to prepare the attack.
	  Multipliers: x0.25 0 rnds.
	               x0.50 1 rnd.
                       x0.75 2 rnds.
                       x1.00 3 rnds.

      cone_recharge:
          How many seconds until next cone attack.

      cone_method:
          CONE_NORMAL (0)
	      A normal cone attack.
	  CONE_INTENSIFIED (1)
	      Will double all damage, but fumble possibility
	      doubles also, and cone_length and cone_length is
	      halved.
	  CONE_WEAK (2)
	      cone_length doubles, but halves the damage.
	  CONE_SWEEP (3)
	      Affects all in an area by sweeping the cone
	      over an area. cone_length is reduced.

-------------------------------------------------------------------------
*/

/*---  Global variables ---*/

#ifdef WHEN_FINNISHED

object objMainTarget;

/*
 * Function name:   get_more_targets
 * Arguments:       main_target 
 * Description:     Tries to find out other targets close to main_target.
 * Returns:         All targets to be affected. First in array is the
 *                  poor lad which is aimed upon.
 */
varargs object *
get_targets()
{
    object room = ETO;
    object *targets = INV(ROOM) - ({ TO });

    /*--- Still the magic system does not take into consideration
          what to do with items worn by players, but I will! ---*/
    if (!objectp(main_target))
	return targets;
    if (!sizeof(targets))
	return ({ main_target });
    
    // For now I will just return them all. Natural, since no ranged
    // combat exists.

    return ({ main_target, targets });
}

string
cone_start()
{
    if (living(objMainTarget))
	action("$N $turn against #n and $breathe a cone of fire!\n", 
	       victim[0]);
    else
	action("$N $aim against " + QTHESHORT(victim[0]) + " and $breathe " +
	       "a cone of fire!\n");
}

varargs void
do_elemental_attack(object aim_at)
{
    object *living_targets;
    object *dead_targets;
    object *all_targets;

    all_targets = get_all_target(aim_at);
    living_targets = FILTER_LIVE(all_targets);
    dead_targets = FILTER_DEAD(all_targets);

    if (!sizeof(living_targets))
	return;

    if (!aim_at)
	objMainTarget = aim_at;
    else
	objMainTarget = living_targets[random(sizeof(living_targets))];

    cone_start();

    // Ok, calculate the result.
    // Attack size => Maximum threshold.
    //                Purity.
    //                Criticals?

    
    


void
do_fry()
{
    object *victim = FILTER_LIVE(all_inventory(ENV(TO))) - ({ TO });
    object *tmpvic;
    int succ, hits, max_success, i;
    int d_res;
    mixed att_desc;
    mixed did_hurt;
    string how, good;
    int no, class;
    string vic_str;

    if(!sizeof(victim))
	return;
    no = sizeof(victim);
    vic_str = COMPOSITE_LIVE(victim);

    succ = random(700)+300;

    TO -> catch_msg("You breathe fire upon "+vic_str+".\n");
    tell_room(ENV(TO),
	    QCTNAME(TO)+" opens its nostrils and breathes fire upon "+vic_str+"!!\n",
	    victim + ({TO}));
    for(i=0; i<no; i++) {
	tmpvic = victim-({victim[i]});
	if(sizeof(tmpvic)==0)
	    vic_str = "you";
	else
	    vic_str = "you and "+FO_COMPOSITE_LIVE(tmpvic, victim[i]);
	victim[i]->catch_msg(
	    QCTNAME(TO)+" breathes fire upon "+vic_str+"!!\n");
    }
    for(i=0; i<no; i++) {
	d_res = victim[i]->query_magic_res(MAGIC_I_RES_FIRE);
	hits  = random(succ * (100 - d_res) /100) + 1;

    /*	did_hurt =  ({ proc_hurt, hitloc description, phit, dam }) */
	did_hurt = victim[i]->hit_me(hits, MAGIC_DT, TO, -1);

	switch(did_hurt[2])
	{
	    case 0..15:		good = "poor"; break;
	    case 16..30:	good = "weak"; break;
	    case 31..59:	good = "dangerous"; break;
	    case 60..75:	good = "powerful"; break;
	    case 76..91:	good = "nasty"; break;
	    case 92..110:	good = "awesome"; break;
	    case 111..200:	good = "devastating"; break;
	    case 201..500:good = "massacrating"; break;
	    default:	good = "deadly"; break;
	}

	tellem(TO, victim[i],
	    "$Your cone of fire hits #name with "+good+" flames!\n", 1);

	message(TO, victim[i], DT_HEAT, "", did_hurt[0]);

	if(victim[i]->query_hp() <=0)
	    victim[i]->do_die(TO);
    }
}

#endif

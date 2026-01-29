/* aldarion 95.07.09 */

/* to do: remove all s_egg's if player dies
   put random() into set_alarm DELAY
   description others see when egg hatches
   autoloading
*/


inherit "/std/object";
#include "/d/Kalad/defs.h"

#define DELAY_1 120.0 /* delay between laying and about to hatch */
#define DELAY_2 90.0  /* delay between trying to and actually hatching */

void pre_hatch();
void hatch();
void damage_player();
void tell_others(string str);

void
create_object()
{
    set_name("egg");
    set_short("spider's egg");
    set_long("Spider's egg that will hatch at a random point in the "
       +"future.\n");

    add_prop(OBJ_I_INVIS, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

    set_alarm(DELAY_1, 0.0, pre_hatch);
}


/*
 * Function   : pre_hatch
 * Description: egg about to hatch
 * Arguments  : none
 * Returns    : void
 */

void
pre_hatch()
{
    object host = environment(TO);

    switch (random(3)){
    case 0:
      tell_object(host,"You feel an uncomfortable itching under your skin.\n");
      tell_others(QCTNAME(host) + " looks uncomfortable.\n");
      break;
    case 1:
      tell_object(host, "You have an uncontrollable itching feeling.\n");
      tell_others(QCTNAME(host) + " itches uncontrollably.\n");
      break;
    case 2:
      tell_object(host, "You experience a strange pulsating feeling.\n");
      break;
    }

    set_alarm(DELAY_2, 0.0, hatch);

    return;
}

      
		
/*
 * Function   : hatch
 * Description: spider's egg hatches into baby spider
 * Arguments  : none
 * Returns    : void
 */

void
hatch()
{
  string body_part;
  object host = environment(TO);

  switch(random(6)){
  case 0:
    body_part = "head";
    break;
  case 1:
    body_part = "left leg";
    break;
  case 2:
    body_part = "right leg";
    break;
  case 3:
    body_part = "left arm";
    break;
  case 4:
    body_part = "right arm";
    break;
  case 5:
    body_part = "torso";
    break;
  default:
    body_part = "body";
    break;
  }

  tell_object(host, BS("Your skin becomes painfully taut, and then explodes!" +
    "  A baby spider pops out and scurries away.\n"));

  tell_others(BS("The " + body_part + " of " + QTNAME(host) + " erupts in " +
	 "a volcano of putrid fluids.  A small spider emerges and scurries " +
	 "quickly away.\n"));

  TO->damage_player(); 
  TO->remove_object(); /* my work is done */

  return;
}


/*
 * Function   : damage_player
 * Description: do damage to the player
 * Arguments  : none
 * Returns    : void
 */

void
damage_player()
{
  /* damage inflicted is 10-20% of maximum hp */
  int damage = (10 + random(11));
  object host = environment(TO);

  host->set_hp(host->query_hp() - (damage * host->query_max_hp())/100);

  if(host->query_hp() <= 0)
    host->do_die(TO);

  return;
}
  

/*
 * Function   : tell_others
 * Description: tell people other than the host what's going on
 * Arguments  : str: the string to tell people
 * Returns    : void
 */

void
tell_others(string str)
{
  object host = environment(TO); /* host is the person I am in */
  object *others;                /* others are all but the host */
  int i;

  /* put all living objects in room apart from host into array */
  others = FILTER_LIVE(all_inventory(environment(host))) - ({host});

  /* and now tell them the message */
  for(i = 0; i < sizeof(others); i++)
    others[i]->catch_msg(str);

  return;
}

/*
 * This bird will follow its finder until its killed of.
 */

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void my_heart_beat();

object target;
string name;

create_creature()
{


   if (!IS_CLONE)
      return;
   seteuid(getuid(this_object()));
   set_name("bird");
   set_living_name("bird");
   set_race_name("bird"); 
   set_long("The bird flies around your head, making it spin around"
	    + " and around.\n");
   set_gender(G_NEUTER);
   add_prop(LIVE_I_NEVERKNOWN, 1);

   set_stats(({ 5, 10, 2, 15, 15, 25 }));

   set_attack_unarmed(0,  8, 8,W_IMPALE, 100, "beak");
   set_hitloc_unarmed(0, ({ 8, 8, 8, 8 }), 100, "body");

   set_act_time(3);
   add_act("@@sing");

   add_prop(CONT_I_WEIGHT, 50);   /* 0.05 Kg  */
   add_prop(CONT_I_VOLUME, 100);   /* 0.10 Ltr */

   trig_new("%s 'arrives.' %s", "get_owner");

}

sing() {
  int ran;
  ran = random(3);

  switch(ran) {
  case 0:
    tell_room(environment(), "The bird sings a merry tune.\n");
    break;
  case 1:
    tell_room(environment(), "The bird flies up and down in circles.\n");
    break;
  case 2:
    tell_room(environment(), "The bird dives down and catches a maggot from "
	      + "the ground.\n");
    break;
  }
}

get_owner(str1,str2) {

  if(!target) {
    target = this_player();
    name = target->query_name();
    name = lower_case(name);
    tell_room("yes");
  }
}

/*
 * Function name:   heart_beat
 * Description:     Perform all heart_beat routines. Simply taken from
 *                  living/heart_beat.c, since add_heart_beat won't work.
 * Arguments:       num: Number of lost heart beats, sent as argument
 *			 If num == 0, it's a normal heart_beat
 */
static void
heart_beat(int num)
{
    add_age(num+1);

    call_out("restart_heart",1);

    decr_tmp_stats(num);
    drink_heart_beat(num);
    heal_living(num);
    my_heart_beat();

    remove_call_out("restart_heart");
}

my_heart_beat() {

  if (!present(name,environment()))
    {
      if(!(target = find_player(name)))
	{
	  say(QCTNAME(this_object()) + " runs away in search for its"
	      + " friend.\n");
	  remove_object();
	}
      say(QCTNAME(this_object()) + " looks in all directions...\n"
	  + "And then flies after " + QCTNAME(target) + ".\n");
      move(environment(target));
      say(QCTNAME(this_object()) + " flies in.\n");
    }
}
/* For the solamnian Knights */

query_knight_prestige() { return(-1); } /* It's more fun if its not killed */


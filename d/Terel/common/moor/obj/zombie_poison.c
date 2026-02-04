/* zombie poison for tomb dwellers
 *  Lilith Jan 2022
 *
 */

#include "/d/Terel/include/Terel.h"
#include <poison_types.h>
#include <macros.h>
#include <ss_types.h>

#define TR(x)       tell_room(environment(poisonee), (x), poisonee);
#define POSSESS(x)  x->query_possessive()
#define POISON_LOG  "/d/Terel/log/zombie_poison"

inherit "/std/poison_effect";

void
create_poison_effect()
{
  set_name("_td_poison");
  set_short("zombie scratch");
  set_long("It's an ugly, infected scratch that you got from one of the "+
    "tomb dwellers.\n");
  add_item(({"scratch", "scratchmark"}), 
    "It is an ugly, infected scratch you got from one of the zombie tomb "+
    "dwellers.\n");	
  set_adj("zombie");
  set_interval(20);
  set_time(180);
  add_prop(OBJ_M_NO_DROP, "If only it was that easy...");
  set_strength(30);
  set_damage(({POISON_HP, 100, POISON_STAT, SS_STR, POISON_USER_DEF, 10}));
  set_poison_type("standard");
  set_silent(1);
}


void
special_damage (int damage)
{
    int msg_num = random(5);

    if (!objectp(poisonee))
	return;

    // player and room tells
    switch (msg_num)
        {
          case 0:
            poisonee->catch_msg("Your scratch throbs painfully.\n");
            TR(QCTNAME(poisonee) + " winces " + POSSESS(poisonee) +
                 " and rubs a scratch.\n");
    		poisonee->heal_hp(-20);
            break;
          case 1:
            poisonee->catch_msg("The zomie scratch is starting to look "
			    +"more infected.\n");
            TR(QCTNAME(poisonee) + "looks pained.\n");
            poisonee->add_panic(5);
            break;
          case 2:
            poisonee->catch_msg("The zombie scratch is slowly turning "
			    +"green!\n");
            poisonee->add_fatigue(-10);
            break;
          case 3:
            poisonee->catch_msg("The scratch from the zombie is becoming "
                +"more painful. You wonder if it will be the death of you.\n");
            TR(QCTNAME(poisonee) + " muffles a pained cry.\n");
			poisonee->add_mana(-10);
            break;
          case 4:
            poisonee->catch_msg("Your zombie scratch is starting to "
                +"drain pus!\n");
            TR(QCTNAME(poisonee) +" looks grossed-out for a moment.\n");
            break;
          default:
            poisonee->command("$shiver");
            break;
        }

}

void
timeout()
{
  poisonee->catch_msg("Your zombie scratch seems to be healing cleanly.\n");
  ::timeout();
}

void
reconfig_me(int newstr)
{
  set_damage(({POISON_HP, newstr, POISON_STAT, SS_STR,
               POISON_USER_DEF,10}));
}

void
kill_player()
{
    write_file(POISON_LOG, 
        ENV(TO)->query_cap_name()+ "("+ ENV(TO)->query_average_stat() + 
        ") died from zombie scratch "+ ctime(time()) +" .\n");
   ::kill_player();
}

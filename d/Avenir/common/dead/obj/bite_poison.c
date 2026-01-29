/* bite poison for revenants in the Catacombs.
 *  Lilith Aug 2021
 *
 */

#include <poison_types.h>
#include <macros.h>
#include "/d/Avenir/common/common.h"

#define TR(x) tell_room(environment(poisonee), (x), poisonee);
#define DEATH_LOG	"/d/Avenir/log/bite_death"
#define WRITE_THIS_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + \
             this_player()->query_name() + "(" + \
             this_player()->query_average_stat() + ") " + \
             (msg)))

inherit "/std/poison_effect";

void
create_poison_effect()
{
  set_name("_Avenir_revenant_bite_poison");
  set_short("nasty bitemark");
  set_long("It's an ugly, swollen, disgustingly infected bite mark.\n");
  add_name(({"bitemark", "bite mark"}));
  set_interval(50);
  set_time(180);
  add_prop(OBJ_M_NO_DROP,"If only it was that easy...");
  set_strength(20);
  set_damage(({POISON_HP, 30, POISON_STAT, SS_DEX, POISON_USER_DEF,1}));
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
            poisonee->catch_msg("Your bitemark throbs painfully.\n");
            TR(QCTNAME(poisonee) + " winces " + POSSESS(poisonee) +
                 " and rubs a bitemark.\n");
    		poisonee->heal_hp(-5);
            break;
          case 1:
            poisonee->catch_msg("The bitemark swells painfully and turns "
			    +"lurid blue.\n");
            TR(QCTNAME(poisonee) + "looks pained.\n");
            poisonee->add_panic(5);
            break;
          case 2:
            poisonee->catch_msg("The bitemark is growing more infected, "
			    +"making you feel tired.\n");
            poisonee->add_fatigue(-5);
            break;
          case 3:
            poisonee->catch_msg("It is becoming more difficult to move "
			    +"without extreme pain. You feel like this bitemark "
				+"may be the death of you.\n");
            TR(QCTNAME(poisonee) + " seems to be struggling not to cry out.\n");
			poisonee->add_mana(-5);
            break;
          case 4:
            poisonee->catch_msg("The pain in your bite area seems to be "
			    +"lessening a bit.\n");
            TR(QCTNAME(poisonee) +" looks a bit better.\n");
            break;
          default:
            poisonee->command("$shiver");
            break;
        }

}

void
timeout()
{
  poisonee->catch_msg("Your bitemark seems to be healing cleanly.\n");
  ::timeout();
}

void
reconfig_me(int newstr)
{
  set_damage(({POISON_HP, newstr, POISON_STAT, SS_DEX,
               POISON_USER_DEF,1}));
}

kill_player()
{
   write_file(DEATH_LOG, ENV(TO)->query_name()
            + "("+ENV(TO)->query_average_stat()
            + ") died from a bitemark on "+ctime(time())+" "
            + " at "+file_name(ENV(ENV(TO))) + ".\n");
   ::kill_player();
}

/* created by Aridor 02/23/94 */

#include "../local.h"

inherit C_FILE

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#define MY_ROOM  CAVERN + "b1"


void
create_creature()
{
    int i;

    set_name("spider");
    set_race_name("spider");
    set_adj("big");
    add_adj("black");

    set_gender(2);
    set_long("It is a big black spider with eight legs and a black head " +
	     "with large eyes looking at you with suspicion. It is about " +
	     "the size of a catapult boulder and looks just as threatening " +
	     "as a flying one.\n");

    set_stats(({ 10, 15, 20, 2, 1, 200}));

    set_hp(5000);
    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;

    set_skill(SS_DEFENCE, 9);
    set_attack_unarmed(2,   5, 5, W_IMPALE, 100, "bite");

    set_hitloc_unarmed(1,  ({3, 3, 3}), 30, "body");
    set_hitloc_unarmed(2,  ({2,11, 2}), 64, "leg");
    set_hitloc_unarmed(4,  ({1, 7, 1}),  6, "head");


}

void
do_die(object killer)
{
  (MY_ROOM)->add_player_killed_spider(killer);
  ::do_die(killer);
}

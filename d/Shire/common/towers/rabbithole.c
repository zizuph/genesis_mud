/*
 * rabbithole.c
 *
 * This object is cloned into path2.c, and is used to solve the
 * White Towers quest. If a player puts the two keys of the doors
 * of the tower in this hole, a few checks have to be made before
 * giving out the quest experience:
 *
 *	- Both doors should be locked.
 *	- The player must have visited the 4th floor of the second tower.
 *
 * The person who inserts the second key will get the experience, and
 * has solved the quest. The keys have to be destroyed, so the quest
 * can be solved again.
 *						Tricky 
 */

inherit "/std/container";

#include "/sys/stdproperties.h"
#include "defs.h"

//   Prototypes
void check_solved(object who);

int alarm_id;

void
create_container()
{
    set_name(({"hole","rabbithole"}));
    set_long("A rabbithole. Not unlike hobbits, rabbits dig holes "
	   + "to live in. This hole shows no sign of recent activity.\n");

    add_prop(CONT_I_MAX_VOLUME, 3000); 	/* 3 litres of volume */
    add_prop(CONT_I_TRANSP, 0); 	/* 3 litres of volume */
    add_prop(OBJ_M_NO_GET, "Get the hole? It is immaterial! Try the sky.\n");
}

int
enter_inv(object obj, object from)
{
    alarm_id = set_alarm(0.5,0.0,&check_solved(),from);
    ::enter_inv(obj, from);
}

void
check_solved(object who)
{
    int forgotten, amount;

    remove_alarm(alarm_id);
    if (!who)
	return;

    if (present("tower1_key", this_object()) &&
	present("tower2_key", this_object()))
    {
	seteuid(getuid());

	if ((STAND_DIR + "tower1_doora")->query_locked() == 0)
	    forgotten = 1;

	if ((STAND_DIR + "tower2_doora")->query_locked() == 0)
	    forgotten = 1;

	if (who->query_prop("_seen_4th_floor_of_tower_2") == 0)
	    forgotten = 1;

	if (forgotten)
	{
	    tell_object(who, "Nothing happens. Perhaps you forgot something?\n");
	    return;
	}

	/* Solved the quest! Set the questbit */
	who->set_bit("Shire", TOWERQUEST_GROUP, TOWERQUEST_BIT);

	/* NEVER add more exp than the player has */
	if (who->query_exp() < TOWERQUEST_EXP)
	    amount = who->query_exp() * 3 / 4;
	else
	    amount = TOWERQUEST_EXP;

	who->add_exp(amount,0);            /* Add quest experience */

	/* Log it to file */
	log_file("QUESTS", "White Towers: " + extract(ctime(time()), 4, 15)+ " "
		+ capitalize(who->query_real_name()) + " got " + amount
		+ "xp.\n");

	tell_object(who,  "Congratulations! You solved the quest!\n"
			+ "You feel more experienced.\n");

	/* Now destroy both keys */
	present("tower1_key")->remove_object();
	present("tower2_key")->remove_object();
    }
}

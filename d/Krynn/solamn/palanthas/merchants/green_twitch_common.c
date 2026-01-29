/*
 * The common room of the Green Twitch Inn.  Players may
 * purchase a key to unlock a cot that folds out from the
 * wall like a prison bed.
 *
 * When full thief system is in place, this room will need
 * support for picking open a cot.
 *
 * Mortis 01.2006
 */

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include "../local.h"

inherit MERCH_ROOMBASE;

#define TRIED_TO_PICK		"_tried_to_pick"

int start_here(string str);

string
query_to_jail()
{
  return "north";
}

void
reset_palan_room()
{
}

void
create_palan_room()
{
	SHORT("Common room of the Green Twitch Inn");
    LONG("This is the common room of the Green Twitch Inn.  The walls are "
	+ "lined with cots that fold down suspended on chains except along the "
	+ "south where there is a red brick fireplace.  The floor and walls are "
	+ "of translucent marble, and great oakwood beams support the low "
	+ "ceiling.  Green paper lanterns hang from ceiling beams shedding green "
	+ "candlelight about the room.  Travellers, merchant sailors, and other "
	+ "citizens lay reclined on some of the cots.\n");

	ITEM(({"wood", "beams", "oakwood", "oak", "ceiling"}), "Great oakwood "
	+ "beams support a low ceiling above.  From them hang green paper "
	+ "lanterns.\n");
	ITEM(({"fire", "fireplace", "brick", "bricks", "spit"}), "There is a "
	+ "fireplace in the south of the common room built from red bricks.  It "
	+ "sheds flickering light about the room.\n");
	ITEM(({"paper", "lantern", "lanterns", "paper lanterns", "green paper",
		   "green lanterns", "green paper lanterns"}), "Green paper "
	+ "lanterns hang from the great oakwood ceiling beams shedding green "
	+ "candlelight about the room adding to the warm atmosphere.\n");
/*	ITEM(({"window", "windows"}), "There are windows to either side of the "
	+ "entry door in the west wall.  You can peer out them with <view "
	+ "plaza>.\n"); Perhaps east windows into an alley. */
	ITEM("floor", "The marble blocks of the floor are tinted beige likely "
	+ "from high traffic, but they are polished nonetheless.\n");
	ITEM(({"wall", "walls", "marble"}), "The translucent marble of the "
	+ "walls is polished and clean.\n");
	ITEM(({"cot", "cots", "bed", "beds"}), "Fold out cots serve as beds here "
	+ "in the common room of the Green Twitch Inn.  The cots fold up into "
	+ "walls where they snap into a latch lock.  If you have a key from the "
	+ "barkeep, you can unlock one allowing it to fold out horizontally "
	+ "suspended by chains for a comfortable night's sleep.\n");
	ITEM(({"chain", "chains"}), "Chains at either end of the fold out cots "
	+ "keep them suspended horizontally for a comfortable night's sleep.\n");
	ITEM(({"lock", "latch", "latch lock"}), "Latch locks with a keyhole "
	+ "keep the fold out cots flat against the wall until ready for use.\n");
	ITEM("keyhole", "There is a keyhole in each of the latch locks.  The "
	+ "barkeep rents keys if you're interested in spending the night.\n");

	reset_palan_room();

	EXIT(MERCH + "green_twitch", "north", 0, 0);
}

void
init()
{
    ::init();
    ADD(&start_here(), "start");
	ADA("pick");
}

int
start_here(string str)
{
    object key;

    NF("Start where?\n");

	if (!str || str != "here")
		return 0;

	if (!(key = present("_green_twitch_common_key", TP)))
	{
	    TP->catch_msg("You need a key from the barkeep to unlock a wall cot "
		+ "first.\n");
	    return 1;
	}

	TP->catch_msg("You turn the key in the latch lock releasing a cot from "
	+ "the wall for you to sleep on.\nYou will awaken here the next time "
	+ "you enter the realms.\n");
	say(QCTNAME(TP) + " turns a key in a latch lock above a cot releasing it "
	+ "from the wall for " + HIM(TP) + " to sleep on.\n");
	key->remove_object();
	TP->set_temp_start_location(MASTER_OB(TO));
	return 1;
}

int
pick(string str)
{
	int skill, diff;

	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[latch] 'lock' / 'keyhole' / 'cot'"))
		return 0;

	if (TP->query_prop(TRIED_TO_PICK) == 1)
	{
	    skill = TP->query_skill(SS_OPEN_LOCK);
		diff = 51 + random(30);

		if (skill > diff)
		{
			write("The latch lock opens with a subdued \"clunk\", and a cot "
			+ "folds out from the wall for you to sleep on.\nYou will awaken "
			+ "here the next time you enter the realms.\n");
			TP->set_temp_start_location(MASTER_OB(TO));
			return 1;
		}

		if (diff - skill <= 20)
		{
			write("The latch lock is too difficult for your skills.\nYou "
			+ "pray to Hiddukel no one saw you.\n");
			TP->command("peer search");
			return 1;
		}

		if (diff - skill > 20)
		{
			write("The latch lock is too difficult for your skills.\nA "
			+ one_of_list(({"merchant", "merchant sailor", "sleepy citizen",
				"bureaumancer", "traveller", "little boy", "little girl"}))
			+ " points at you yelling:  Thief!  Call the constable!\nYou "
			+ "hear the trodding of heavy footsteps growing near.\n");
			say("A " + one_of_list(({"merchant", "merchant sailor",
				"sleepy citizen", "bureaumancer", "traveller", "little boy",
				"little girl"})) + " points at " + QCTNAME(TP) + " yelling:  "
			+ "Thief!  Call the constable!\nYou hear the trodding of heavy "
			+ "footsteps growing near.\n");
			return 1;
		}
	}

	else
	{
		TP->add_prop(TRIED_TO_PICK, 1);
		write("Pick the lock on one of the cots?  Are you sure you want to "
		+ "try that in a crowded room like this?\n");
		TP->command("peer thought");
		return 1;
	}
}

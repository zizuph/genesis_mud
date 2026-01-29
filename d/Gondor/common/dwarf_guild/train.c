/*
 * /d/Gondor/common/dwarf_guild/trainhall.c
 *
 * The training hall of the dwarven race guild.
 *
 * /Mercade, 3 November 1993
 *
 * Revision history:
 */

#pragma save_binary

inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"

#define TRAINER (DWARVEN_RACE_GUILD_NPCS + "trainer")

/*
 * Prototype
 */
void reset_room();

/*
 * Global variable
 */
object trainer;

void
create_room()
{
    set_short("training hall of the " + DWARVEN_RACE_GUILD_NAME);
    set_long(BSN("This cave is rather large and in it you may train skills " +
	"if the trainer is present. On the floor you see a mat to prevent " +
	"injuries when training. To the west you see the main cave of this " +
	"guild complex. There is a door leading to the private chambers " +
	"of the trainer. When the trainer is present, you may either " +
	"<learn> new skills or <improve> skills you already have."));

#include "cavedesc.h" /* some add_items for the rocky cave etc. */

    remove_item("floor");
    add_item( ({ "floor", "ground", "mat" }),
	BSN("The mat on the floor is rather large and is very soft. It is " +
	"meant to prevent anyone from sustaining injuries in case (s)he " +
	"falls when training."));

    add_item( ({ "door" }),
	BSN("The door leads to the private chambers of the trainer. It is " +
	"made of solid oak and looks very sturdy. You have no business in " +
	"the private chambers of the trainer so you should leave the door " +
	"for what it is. The door is closed and locked."));
    add_cmd_item( ({ "door" }), ({ "open", "unlock" }),
	BSN("There is no way you can unlock or open that door."));

    add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_S_WIZINFO,
	BSN("This training hall is open for everyone. However, only members " +
	"of the " + DWARVEN_RACE_GUILD_NAME + " are entitled to train all " +
	"skills to the maximum. Currently this applies only to SS_AXE " +
	"however."));

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "guild", "west");

    reset_room();
}

void
reset_room()
{
    if (!objectp(trainer))
    {
	trainer = clone_object(TRAINER);
	trainer->arm_trainer();
	trainer->move_living("M", TO);
	tell_room(TO, QCNAME(trainer) + " enters the cave from " +
	    POSSESSIVE(trainer) + " chambers.\n");
    }
    else if (ENV(trainer) != TO)
    {
	trainer->move_living("X", TO);
    }
}

/*
 * Function name: sk_query_max
 * Description  : This function will be queried by the skill decay system
 *                and it will make sure the trainer is loaded and then
 *                pass the question on to the trainer.
 * Arguments    : int skill  - the skill to query.
 *                int silent - true if the call is silent, should be 1 always,
 *                             but I don't bother with it since it should
 *                             always be silent ;-)
 * Returns      : int - the maximum trainable for this_player() for 'skill'.
 */
varargs int
sk_query_max(int skill, int silent)
{
    if (!objectp(trainer))
    {
	reset_room();
    }

    /* If the call comes through this object, it is always from the and
     * it must therefore always be a silent call.
     */
    return trainer->query_skill_decay_max(skill);
}
/*
 * /d/Shire/claws/rooms/throne.c
 *
 * The room where all the things that the Captain orc has decided
 * will be set into action. The Captain must be here to punish
 * players, or if he wants to approve new warriors.
 *
 * Turgon, 16.10.96
 * 
 * Modification log:
 * 
 */
inherit "/d/Shire/room";

#include <ss_types.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/guild/claws/claw_defs.h"

object throne;

create_room()
{
	set_short("Throne hall");
	set_long("This is where the chief of the Black Claw Clan recides "+
		"when he is not out fighting. Here all things that has been decided "+
		"will be set into action. Torches are lined up on the walls to "+
		"provide light, and the walls are covered with blood-stained "+
		"clothing and armours. The throne itself is set about 4 feet above "+
		"the ground, close to the east-wall, and behind it hang tapestries "+
		"which must have seen better days. The ceeling is about 20 feet up "+
		"and it is easy to tell that orc's have no part in forming the caves. "+
		"Down from the walls water trickle, and that is possibly the reason "+
		"to why it is so humid in here. West, a small arched passage lead "+
		"out of here.\n");


	add_item("passage", "The passage seems to lead directly west, out of this "+
		"room. The arch is covered with blood, and some fresh dwarven skulls "+
		"is set on it.\n");
	add_item("clothing", "IT looks like the clothing is human made, and there "+
		"is stained blood on them. Must be some trophy from a battle or so.\n");
	add_item(({"armours","armour"}), "The armours that hang on the walls are mostly broken "+
		"and seems of little use.\n");

	add_exit("training", "west", 0, 0, 0, 0);

	reset_room();

	if (!objectp("throne")) room_add_object("/d/Shire/guild/claws/obj/throne", 1);

	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
}


void
init()
{
	::init();
    add_action("do_seize", "seize");
}
/*
 * Function name: do_praise
 * Description:   Approve new warriors. Max 24.
 * Arguments:     tp - The player to approve.
 * Returns:       1 - If ok.
 *                0 - If something went wrong.
 */
/*
int
do_praise(object tp)
{
*/

/*
 * function name: do_seize
 * Description:   enables a player to seize the captain rank in the guild
 *       	  if the player has the iron crown which is the token of
 *  	          the captain.
 * returns:       1 - if success, 0 if failure.
 */
int
do_seize(string str)
{
    object tp = this_player();
    int rank;
    string who;

    notify_fail("Seize what?\n");
    if (!str)
	return 0;

    notify_fail("Seize what?\n");
    if (str != "throne")
	return 0;

    if (!present("_captain_ob_", tp))
    {
    write("But you must gain the token of the Captain before "+
        "you can do that!\n");
    return 1;
    }

    write("You put the Iron Crown on your head, and declare yourself "+
        "to be the sole leader of the Black Claws!\n");
    tp->command("wear crown");
    say(QCTNAME(tp)+" declare "+HIM_HER(tp)+"self to be the sole "+
        "leader of the Black Claws.\n");


    THRONE->make_captain(tp->query_real_name());

    return 1;
}

/*
 * This is the room where you can find the key to the first White Tower.
 * Related file: tower1_key.c
 *
 *					Tricky, 28-2-92
 */
inherit "/std/room";

#include "defs.h"

/*
 * This variable will be reset when the key is destroyed, so
 * there will always be only one key in the game.
 */
object the_key;

void
create_room()
{
    set_short("Around tower");
    set_long("@@my_long");

    add_item(({"tower","white tower"}), break_string(
	  "The white tower was built long ago to protect the surrounding "
	+ "land from the invasion of evil forces.\n", 70));

    add_item(({"path","paths"}), break_string(
	  "The path encircles both towers. Many feet have crossed it, "
	+ "but now the grass is growing back.\n",70));

    add_item("grass", "@@grass_long");

    add_exit(STAND_DIR + "path9", "north");
    add_exit(STAND_DIR + "path7", "west");
}

/*
 * Function name:   can_find_key
 * Description:	    Only if the key has not been found yet, and if
 *		    the player has not solved the quest, can the key
 *		    be found.
 * Returns:	    1 if the key can be found, or 0 if not.
 */
int
can_find_key()
{
    object tp;

    tp = this_player();

    return (!the_key) && living(tp) &&
	   (tp->test_bit("Shire", TOWERQUEST_GROUP, TOWERQUEST_BIT) == 0);
}

string
my_long()
{
    string str;

    str = "You are southeast of the southernmost white tower. The path "
* "bends around the tower here.";

    if (can_find_key())
	str += " Something is sparkling in the grass.";

    return break_string(str + "\n", 70);
}

string
grass_long()
{
    seteuid(getuid());

    if (can_find_key())
    {
	the_key = clone_object(STAND_DIR + "tower1_key");
	the_key->move(this_object());
	return "Looking more closely at the grass reveals a key!\n";
    }

    return break_string(
	  "The grass looks quite ordinary. It grows everywhere around "
	+ "the towers, and has not been trodden on since years.\n", 70);
}

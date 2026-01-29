/* By Amelia 1998
 * Modified by Ckrik Jan 1998
 *  modified by Amelia to make unsearchable in high tide 3/24/98
 * Modified by Ckrik March 1998
 * Search failure message due to tide changed.
 */

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "defs.h"

#define MAX_FIND 3

public string
find_stuff(object player, string str)
{
    object ob;
    object tides;
    int ran = random(10);


    tides = find_object(TIDE);
    if (tides->query_tide_level() > 2)
	return "Hmm ... you find nothing interesting around here. "+
	"Everything must be under water.\n";

    if((str == "debris" || str == "shore" ||
	str == "sand" || str == "for shell" || 
	str == "here" ||
	str == "for shells") &&
      (TO->query_num_searched() < MAX_FIND))
    {
	setuid();
	seteuid(getuid(TO));

	switch (ran)
	{
	case 0:
	    ob = clone_object(OBJ_DIR + "driftwood");
	    break;

	case 1:
	    ob = clone_object(OBJ_DIR + "coconut");
	    break;

	case 2:
	    ob = clone_object(OBJ_DIR + "flotsam");
	    break;

	case 3:
	    ob = clone_object(OBJ_DIR + "jetsam");
	    break;
	case 4:
	    ob = clone_object(OBJ_DIR + "old_l_shoe");
	    break;

	case 5:
	    ob = clone_object(OBJ_DIR + "old_r_shoe");
	    break;

	default:
	    ob = clone_object(OBJ_DIR + "shell");
	    break;
	}
	TO->set_searched(TO->query_num_searched() + 1);
	if (ob->move(player))
	    ob->move(environment(player));
	return "You find " + LANG_ASHORT(ob) + "!\n";
    }

    return "You find nothing of value there.\n";
}

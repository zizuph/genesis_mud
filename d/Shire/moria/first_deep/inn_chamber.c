#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("The Inn Chamber");
    set_long(
	"You have entered into what must be the Inn Chamber.\n" +
	"This is a large cavernous complex with dozens of guest rooms " +
	"cut into the walls. Obviously, travelers along Durin's Way " +
	"used to stay here, as it is said that it is 26 miles (42 km) " +
	"from the West-gate and 23 miles (37 km) from the East-gate " +
	"in the Dimrill Valley.\n");
    add_item(({"chamber", "hall", "inn", "complex"}),
	"The chamber is very large, in fact 420'x140', that is 130 by 43 " +
	"meters. You notice that Durin's Way leaves in the western and " +
	"eastern directions through some grand portals.\n");
    add_item(({"portal", "portals"}),
	"Which one, the eastern or the western portal?\n");
    add_item(({"east portal", "eastern portal"}),
	"The eastern portal is still magnificient in its devour architecture. "+
	"It stands semiarced with fabled creatures winding upwards on its sides. "+
	"It seems to be worms and dragons of some kind, a pompeus and forceful " +
	"entrance into the City of the Khazad, Khazad-dum.\n");
    add_item(({"west portal", "western portal"}),
	"The western portal is not as elaborate as the eastern pompeus exit, " +
	"but still awes you in its more simple beauty. It seems to be perfectly " +
	"arched, and it seems to be a kind entrance into the more wild parts of " +
	"Moria, the Mines. The Mines is known to consist of twisting little " +
	"mining channels where even the dwarves of old used to get lost. Not " +
	"like the magnificient Avenues and Lanes of Khazad-dum.\n");
    add_item(({"rooms", "guest rooms", "guest room"}),
	"As the dwarves left this place a long time ago, the rooms have been " +
	"unattended, thus there is probably very little of interest there now.\n");
    add_exit(MINES_DIR + "corr6", "west"); // For now.
    add_exit(THIS_DIR + "dway1", "east");
}

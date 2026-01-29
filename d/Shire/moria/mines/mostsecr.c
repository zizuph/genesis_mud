#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Most secret room");
    set_long(
	"You have found an even more Secret Room.\n"
      + "This room seems as empty as the first one, so "
      + "you would have to return east again.\n");
    EAST("secret");
}

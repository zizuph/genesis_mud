#include "forest.h"

create_forest()
{
    set_short("Narrow valley");
    set_long(
	"You seem to have arrived in a narrow valley. "+
	"The cliffs from the south on your western side have now met "+
	"large boulders in the north and the east making this a very "+
	"narrow valley in the dense forest. There are no other "+
	"possibilities for you than to return south or southeast.\n");

    SOUTH("f0002");
    SOUTHEAST("f0102");
}

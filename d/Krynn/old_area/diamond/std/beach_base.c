/* Beach base file for the Diamond Isle
 * By Kentari, April 23, 1997
 */

#include <macros.h>
#include "../local.h"

inherit OUT_BASE;

public void
reset_dim_room()
{
}

public void
create_beach()
{

}

nomask void
create_dim_room()
{
    set_short("Beach ouside of Diamond City");
    set_long("This is the beach of the Diamond Isle, between the " +
	"walls of Diamond City and the fog covered sea. The sand " +
	"is soft under your feet, and the smell of the sea fills " +
	"your nostrils. ");
    AI(({"beach","beaches"}),
	"The soft sand of the beach is a pleasant change from the " +
	"usual rigors of the road. Within the sand you see occasional " +
	"sparkles, making it appear as if there are diamonds dispersed " +
	"over the beach.\n");
    AI("sparkles","This is a type of beach sand and gives the " +
	"appearance of diamonds within the sand.\n");
    AI(({"walls","wall","walls of Diamond City"}),
	"Made of nondescript, smooth stone, these walls tower over " +
	"the City, protecting it from whomever would try to disturb " +
	"the present tranquility.\n");
    AI(({"sea","fog","fog covered sea"}),
	"The rhythmic crashing of the clear blue waves upon the shore " +
	"soothes the mind, and you see a thick, probably magical, fog " +
	"cover the sea about 25 feet from shore, masking the location " +
	"of the Isle.\n");

    OUTSIDE;
    LIGHT;

    create_beach();
    reset_room();

}


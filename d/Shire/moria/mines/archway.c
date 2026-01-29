#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Archway");
    set_long(
	"This is a north-south going sloped archway. "+
	"There is a draft of cool humid air from the south here.\n");
    add_item(({"passage","archway"}),
	"The passage is arched, and axe-patterns adorn the ceiling.");
    add_item(({"ceiling","patterns","axe-patterns"}),
	"The ceiling is ornamented with patterns shaped like axe-heads.");
    add_item(({"draft","air"}),
	"Strangely enough, cool air seems to come from the south.");
    NORTH("bighalls");
    SOUTH("stneslab");
}

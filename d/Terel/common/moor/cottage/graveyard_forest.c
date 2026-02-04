// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

void
create_room()
{
    set_short("forested area overlooking graveyard");
    set_long(
	"There is a small forested area here, overgrown with trees that "+
	"have sprung up over the past few decades. To the west is the crest "+
	"of the hill the cottage was built on. Under a giant elm tree "+
	"to the north black gravestones stick up through the snow like the " +
	"decayed fingernails of a gigantic corpse. You can reach it from the "+
	"path west of here.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_item(({"tree", "trees", "elm", "elm tree"}), 
       "The grotesque vine-encumbered tree silently waves its knotted " +
       "branches far aloft.\n"
    );

    add_item(({"grave", "graves", "gravestone", "tombstone"}), (
       "The black gravestones are very smooth and bear no markings.\n"));

    add_exit("cottage_graveyard", "west", 0);

}



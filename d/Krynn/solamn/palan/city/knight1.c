/* created by Aridor 09/14/93 */

#include "../local.h"

inherit STREET_BASE


query_to_jail()
{
  return "southeast";
}

void
create_palan_room()
{
    set_short("Knights' Avenue");
    set_long(BS("This avenue looks like is was just recently finished. " +
		"The street itself is paved with blocks of cubic stones, " +
		"and both sides of the avenue are lined " +
		"with trees, to the east you can still see an open ground, " +
		"looking ready for development. It is obvious that this will be the finest " +
		"neighborhood in all of Palanthas. To the west, a very " +
		"bright and shiny building is visible through the trees. " +
		"There is a path leading to it.",SL));

    add_exit(ROOM + "street18","southeast",0,1);
    add_exit(ROOM + "street11","northwest",0,1);
    add_exit(CLUB_ENTRANCE,"west","@@not_yet",1);

    add_item(({"avenue","street"}),
	     BS("The street is carefully laid out with blocks of stone, " +
		"to ensure that no dirt or even mud can disturb your steps. " +
		"",SL));
    add_item(({"building","buildings","neighborhood"}),
	     BS("There are no buildings to your east yet, but a very impressive white " +
		"building is to your west.",SL));
    add_item(({"impressive white building","white building","impressive building"}),
	     BS("It is a white painted building and quite tall, you can't make out " +
		"any details though unless you go into it. You have a sense of " +
		"goodness washing over you as you look at the building.",SL));
    add_item(({"tree","trees","side","sides"}),
	     BS("The sides of the avenue is lined with trees, that have been " +
		"planted here not very long ago. Thus, the trees do not offer much " +
		"shade yet.",SL));
    add_item(({"stone","stones","block","blocks","paving block","paving blocks"}),
	     BS("The blocks are laid out on the road.",SL));
    add_item(({"path"}),
	     BS("It is a recently swept path, and looks very tidy. The path leads " +
		"up to the white building to your west.",SL));

}



not_yet()
{
  write("You walk along the path and enter the white building.\n");
  return 0;
}

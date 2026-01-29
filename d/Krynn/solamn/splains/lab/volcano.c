/* Inside at the bottom of the volcano. There is no exit to the outside,
 * except flying or by magic.
 *
 * Aridor 09/95
 */
#include "local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("At the bottom of a volcano");
    set_long("You seem to be at the bottom of a volcano. All around you " +
	     "are vertical walls rising high up towards " +
	     "the sky. The only thing you can see straight up is a little " +
	     "patch of blue. Towards your west, some kind of cave seems " +
	     "to continue into the inside of the rock.\n");
    add_item("walls","Even though they are not completely smooth, you " +
	     "don't think it's possible to climb up.\n");
    add_cmd_item(({"up","walls","wall"}),"climb","Despite yourrr best efforts, " +
		 "you fail at climbing more than a handhold above the floor.\n");
    add_item(({"blue","sky"}),"It's deep blue, and very very far away.\n");
    add_item("volcano","Fortunately for you, it doesn't seem to be active " +
	     "any more.\n");
    add_item("cave","You can't see much, but there seems to be an artificial " +
	     "light inside the cave.\n");
    add_item(({"light","artificial light"}),
	     "You see any details without going west.\n");

    add_exit(LAB,"west");
}

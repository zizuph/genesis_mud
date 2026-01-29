// file name: crypt66
// creator: Ilyian (September 1, 1995)
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch
// purpose: Room in the underground crypts
// note: Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"

void
create_crypt_room()
{
    acat("60","west");
    add_exit(BARROW+"sliding", "up", 0, 0, 1);
    add_exit(BARROW+"sliding", "climb", 0, 0, 1);
    add_exit(BARROW+"sliding", "chute", 0, 0, 1);
    add_exit(BARROW+"sliding", "enter", 0, 0, 1);
    add_prop("bottom_of_chute", 1);
/* Default is the standard random description. */
    crypt_long(crypt_desc[random(sizeof(crypt_desc))] 
    	+" There is an opening in the southern wall, above a shallow "
        +"pool of water. "+crypt_desc2[random(sizeof(crypt_desc2))]);
	add_item(({"opening", "opening in the floor", "chute", "hole"}),
	    "It looks like a rather steep chute. You cannot "
		+"see where it leads from here, but if you are "
		+"careful you might be able to climb up and find "
		+"out.\n");
	add_item(({"pool", "water"}), "A shallow pool of water, perhaps "
	    +"no deeper than halfway to your knees. You can see a couple "
		+"of corpses floating in it.\n");		
	add_item(({"corpse", "corpses", "floating corpses"}),
	    "You can see that there are a couple of corpses floating "
		+"at the far end of the pool.\n");
    add_tell("You hear a scraping sound rushing toward you.\nA body "
	    +"flies out of a hole in the south wall and splashes into "
		+"a pool of water.\n");
    reset_domain_room();
 }

void
reset_domain_room()
 {
  set_searched(0);    ::reset_domain_room();
 }

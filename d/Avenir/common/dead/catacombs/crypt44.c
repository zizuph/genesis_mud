// file name: crypt44
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
    acat("43", "northwest");

    add_exit(CRYPT+"crypt111","hole", 0, 10, 1);
	add_exit(CRYPT+"crypt111","enter", 0, 10, 1);
    add_exit(CRYPT+"crypt111","down", 0, 10, 1);
	
    /* Default is the standard random description. */
    crypt_long(crypt_desc[random(sizeof(crypt_desc))] +" "+
	    crypt_desc2[random(sizeof(crypt_desc2))] +" "+
	    "There is a large hole in the ground, and a horrible, vile, dank "+
		"stench emits from it.\n");
	AI(({"hole", "large hole", "projections"}), 
	    "The opening is uneven and you can see the walls are rough "+
		"with jagged projections that you could use as hand-holds "+
		"to enter the hole if you were able to overcome your "+
		"revulsion at the stench arising from it in waves.\n");
	add_tell("A moaning sound rises up out of the hole.");
	
    reset_domain_room();
 }

void
reset_domain_room()
{
    set_searched(0);    ::reset_domain_room();
}

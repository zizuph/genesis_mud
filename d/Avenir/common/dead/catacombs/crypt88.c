// file name: crypt88
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
  acat("89","west");
  acat("87","south");

/* Default is the standard random description. */
    crypt_long(crypt_desc[random(sizeof(crypt_desc))] 
	+" Water invades the floor here, and there are strange sucking "
	+"sounds coming from somewhere below the surface. "
	+ crypt_desc2[random(sizeof(crypt_desc2))]);
    add_item(({"pool", "water", "pool of water"}), 
	    "Water has accumulated here, or perhaps is bubbling up from below. "
		+"It is difficult to tell. It is so dark it is impossible to "
		+"see into it, and it smells a bit brackish.\n");

  reset_domain_room();
 }

void
reset_domain_room()
 {
  set_searched(0);    ::reset_domain_room();
 }

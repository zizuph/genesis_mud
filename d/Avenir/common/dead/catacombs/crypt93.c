// file name: crypt93
// creator: Ilyian (September 1, 1995)
// last update  Lilith, July 2021
// purpose: Room in the underground crypts connects to entrance
// note:   Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"

void
create_crypt_room()
{
  acat("_entr","north"); 
  acat("68","west");


    /* Default is the standard random description. */
    crypt_long(crypt_desc[random(sizeof(crypt_desc))] 
	     +" "+ crypt_desc2[random(sizeof(crypt_desc2))]
         +" Some light filters in from around the corner to the north.");

   add_prop("_catacomb_niche", 5);
   
   reset_domain_room();

 }

void
reset_domain_room()
 {
  set_searched(0);    ::reset_domain_room();
 }

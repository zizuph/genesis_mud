// file name: crypt_s6
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
  acat("1","south");

/* Default is the standard random description. */
  crypt_long(crypt_desc[random(sizeof(crypt_desc))]
       +" "+ crypt_desc2[random(sizeof(crypt_desc2))]
	   +" There is a bier made of white granite in the center of the "
	   +"room. The north wall looks like a shrine of sorts, with bones "
	   +"and skulls arranged to form a macabre trefoil symbol. Lamps "
	   +"have been suspended from the ceiling and they cast a golden "
	   +"light upon the room.\n");

    add_item(({"north wall", "trefoil", "trefoil symbol", "shrine"}),
        "The bones of the dead have been cleaned and stacked neatly "
		+"together to form a three-lobed trefoil symbol on the north "
        +"wall.\n");
    add_item(({"bier", "granite bier", "white bier", "granite"}),
	    "It is a big rectangular slab of white granite flecked "
		+"with minerals like feldspare and quartz.\n");
	add_item(({"bowls", "bowl", "bowls of oil", "lamp", "lamps", "light", "lights", 
	    "ceiling", "glass bowls", "ceiling"}),
        "Large glass bowls filled with oil have been suspended with chains " 
        +"from the ceiling. From below, the light they cast is faint, but "
        +"they provide enough illumination to cause the smooth, pure "
        +"white limestone of the ceiling to sparkle and glow. You find "
        +"yourself wondering what mortal hands tend these lamps.\n");
	AI(({"bone", "bones", "long bones", "wall", "back wall","ossuary"}),
      "These bones have all been cleaned and dried and stacked neatly, "
      +"perhaps even reverently, in aesthetically pleasing patterns "
      +"along the walls of this chamber, from floor to ceiling. "
      +"\n");
    AI(({"skull", "skulls"}),
      "Everywhere you look, skulls grin back at you. They shine a bit "
      +"as if they have been polished.\n");		
 	
		
    reset_domain_room();
 }

void
reset_domain_room()
 {
    add_prop(ROOM_I_LIGHT, 2);
    set_searched(0);    ::reset_domain_room();
 }

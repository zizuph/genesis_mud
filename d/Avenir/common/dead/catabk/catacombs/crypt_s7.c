// file name: crypt_s7
// creator: Ilyian (September 1, 1995)
// last update:
// purpose: Room in the underground crypts
// note: Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
// bug(s):
// to_do:
// updates:  Lilith June 2021 : Added an exit to the Mascarvin 
//               quest area.

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"
#define SLIT  DEAD +"mascarvin/spots"

int 
enter_slit()
{
	object   slit = find_object(SLIT);

    if(slit && sizeof(filter(all_inventory(slit), interactive)))
    {
        write("There is someone already squeezed into the "
		   +"slit, so you cannot fit in there.\n");
        return 1;
    }

  write("You squeeze into the slit in the wall.\n"
      +"The mist swirls around your legs as you "
	  +"wriggle eastward, pulling yourself through "
	  +"by your fingertips.\n");
  say(QCTNAME(TP) + " squeezes into the slit in the wall.\n");
  return 0;
}

void
create_room()
{
  acat("36","northwest");
  add_exit(SLIT, "enter", enter_slit, 1, 50);

/* Default is the standard random description. */
  crypt_long(crypt_desc[random(sizeof(crypt_desc))] 
     +" The mist seems to be sinking into a slit "
	 +"near the floor.\n");
  
  add_item(({"slit", "hole"}),
      "There is a slit in the wall running up from the "
     +"floor. Some of the mist seems to be sinking "
	 +"toward it. If you are careful you can probably enter "
	 +"the slit.\n");

  reset_room();
 }

void
reset_room()
 {
  crypt_reset();
}

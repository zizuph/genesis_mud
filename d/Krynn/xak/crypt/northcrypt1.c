/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

int mcan = 1;
object shadow;

void
reset_xak_room()
{
    mcan = 1;
}

void
create_xak_room()
{
        set_short("The North Crypt");
        set_long(BS(
           "You are in the north corridor of the crypt beneath"
	 + " the temple of Mishakal. Coffins line the walls here"
	 + " and the stench of death assails your nostrils. You"
	 + " feel danger here, this is a place for the DEAD!", 70));

	add_exit(CDIR + "northcrypt2.c", "east", 0);
	add_exit(CDIR + "entry.c", "south", 0);

	add_item(({"crypt", "coffin", "coffins"}), "@@coffin");
	INSIDE
        DARK
}

coffin()
{
    if (!mcan)
      {
	  write(BS("You examine the surrounding crypt and coffins."
		   + " everything seems normal. Well as normal as can be"
		   + " expected for such a gloomy place as this.", 70));
	  return "";
      }
    seteuid(getuid(this_object()));
    mcan--;
    shadow = clone_object(MONSTER + "shadow.c");
    shadow->move(TO);
    write(BS("You examine the crypt and the coffins when suddenly"
	     + " a ghostly form emerges from the shadows!", 70));
    SAY(" is poking around the coffins examining them"
	+ " when suddenly a ghostly figure emerges from the shadows!");
    return "";
}


/* created by Kentari 11/19/96 *
 * using code by Aridor as an example */

inherit "/std/room";
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

#define VAULTGUARD "/d/Krynn/kentari/mnstrs/v-guard.c"

object guardian;


create_room()
{
    set_short("Kentari's Vault");
    set_long("You are inside Kentari's Vault, where he stores most "
         +   "of his, and of Genesis', valued products.  Guarding "
         +   "over this room you feel a powerful unseen presence that "
         +   "you don't want to anger. Racks of valuable equipment fill "
	 +   "the room, and various trophies from Kentari's adventures "
	 +   "adorn the walls. A small altar to Paladine can be seen in "
	 +   "the back of the room.\n");

    add_exit("/d/Krynn/kentari/workroom.c","out", 0);
    add_prop(ROOM_I_INSIDE, 1);
 
    add_item(({"racks","equipment"}),
	"Within the multitude of racks you see equipment and items of " +
	"every kind.  Weapons of the rarest and sharpest quality, " +
	"armours of finest make, and items of power and magic fill " +
	"every rack.  The value of the objects in this room is " +
	"beyond calculations and the thing of wishes and dreams.\n");
   
    add_item(({"trophies","trophy"}),
	"Various mounted and preserved heads of some of the greatest " +
	"monsters of the realms are seen here.  An evilfaced draconian " +
	"head, the uruk Bolg's head, Legion leader Mergula's head, " +
	"the Witchking of the Angmarim's head, and the head of the " +
	"Nazgul all are shown here.  You gain a new respect for " +
	"Kentari's battle prowess.\n");

    add_item(("altar"),
	"This is where Kentari prays and meditates to his Patron God " +
	"Paladine.  A simple altar, it shows humbleness before one's " +
	"God, and it is surprising, yet fitting that it is considered " +
	"one of Kentari's most prized things.\n");

    add_item(("presence"),
	"Though you cannot see it, you get the feeling that attacking " +
	"anyone in here, or trying to use the Vault without proper " +
	"access will incur the wrath of this being.  You decide to be " +
	"a bit more careful while in this room.\n");

    reset_room();
}


reset_room()
{
  if (!guardian)
    (guardian = clone_object(VAULTGUARD))->move_living(0,this_object());
}

query_prevent_snoop()
{
   return 1;   
}

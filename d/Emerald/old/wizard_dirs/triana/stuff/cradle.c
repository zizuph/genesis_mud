inherit "/std/receptacle";
#include "/d/Wiz/triana/defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

public void
create_container()
{
	set_name("cradle");
	add_name("wooden cradle");
	set_adj("small");
	add_adj("wooden");
	set_short("wooden cradle");
	set_long(break_string("A small wooden cradle, hand-crafted by a loving hand. " +
	"On the outside of the cradle are beautiful carvings of birds, trees "+ 
	"and woodland animals. With close inspection, it appears a lot of love was " +
	"put into its creation, as the creator was thinking of the child that would soon inhabit it. " +
	"Below the pictures, an inscription reads: Gayle Nguyet, beloved child of Alia and Carnival.\n",75));
    add_prop(CONT_I_WEIGHT,     1200);          /* 1.2 kg        */
    add_prop(CONT_I_VOLUME,     500);           /* Empty volume. */
	add_prop(CONT_I_MAX_VOLUME, 100000);
	add_prop(CONT_I_MAX_WEIGHT, 1000000);
	add_prop(CONT_I_CLOSED, 0);

	seteuid(getuid());
}


public void
fill_cradle()
{
	object baby;
	baby = clone_object("/d/Wiz/triana/stuff/baby.c");
	baby -> move(this_object());
  
  }


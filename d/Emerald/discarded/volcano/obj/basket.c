inherit "/std/receptacle";
#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

public void
create_container()
{
	set_name("basket");
	add_name("Wicker basket");
	add_name("wicker basket");
	set_pname("baskets");
	set_adj("small");
	add_adj("hand-woven");
	set_long("This is a hand-woven " +
	"basket made from materials the women " +
	"of the camp gather to make the necessities of life.  It is well made " +
	"and looks like it could hold small items.\n\n");
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_WEIGHT,     1200);          /* 1.2 kg        */
    add_prop(CONT_I_VOLUME,     500);           /* Empty volume. */
    add_prop(CONT_I_MAX_VOLUME, 3*1000);       /* 3.0 l          */
    add_prop(CONT_I_MAX_WEIGHT, 5*1000);      /* 5.0 kg        */
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(OBJ_I_VALUE,       50+random(11));
	add_prop(CONT_I_CLOSED, 0);

	seteuid(getuid());
}



public void
fill_pouch()
{
	object f1, f2;
	int i;
	for (i=0; i<5; i++)
	{
		f1=clone_object(VOBJ + "corn.c");
	}
	f1 -> move(this_object());
	f2=clone_object(VOBJ + "berries.c");
	f2 -> move(this_object());
  
  }


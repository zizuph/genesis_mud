inherit "/std/drink";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(250);
    set_alco_amount(20);
    set_name("gnomeflinger");
    add_name("mug");
    set_short("gnomeflinger");
    set_pshort("gnomeflingers");
    set_long(BS("So, this is the infamous gnomeflinger, drink of REAL" +
      	" gnomes.  It froths and bubbles a bit.  Might eat through the "+
      	"mug if you don't drink it quickly...", 70));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

init()
{
    add_action("drink", "drink");
}

drink(str)
{
    if (str != "gnomeflinger")
      return 0;
    if (environment(TP)->query_short() != "Theplacewherepeoplecometoget")
      {
	  write("A gnomeflinger, you remember, can not be drunk outside the " +
		"gnomish bar, for liability reasons. Not wishing to cause " +
		"trouble for the adorable little gnomes, you pour out your " +
		"drink instead.\n");
	  say(QCTNAME(TP) + " pours a mug of some liquid on the ground.  It " +
	      " sizzles, burning a whole several centimeters deep.\n");
	  set_alarm(1.0,0.0,"remove_object");
	  return 1;
      }
}

inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("gin");
    set_adj(({"bladderwrack"}));
    set_short("bulb of bladderwrack gin");
    set_pshort("bulbs of bladderwrack gin");
    set_long("The small amount of bladderwrack gin contained in a kelp "+
      "bulb is still not for the faint hearted. Under the overpowering "+
      "smell of alcohol, there "+
      "is the scent of juniper berries picked from salt-stained bushes "+
      "grown in a howling gale atop a seaside bluff.  The pungent scent "+
      "of bladderwrack brings to mind a shipwreck smashed on rocks -- "+
      "streaming seaweed from its timbers.\n");
    set_soft_amount(10);
    set_alco_amount(100);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
}

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit ELEMENTALIST_COMPONENTS + "component_base";

public void
create_component()
{
    set_component_type("earth");

    set_adj( ({ "radiant", "brown" }) );
    set_id_long("This is the component used for some of Lady "+
           "Gu's prayers in the Elementalist Guilds of "
           + "Calia.\n");
    set_unid_long("This is a " + short() + " whose nature is unlike anything "
		  + "you've ever seen before.\n");
}

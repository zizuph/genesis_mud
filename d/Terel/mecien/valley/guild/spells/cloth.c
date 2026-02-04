inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>

create_container(){

set_name("cloth");
add_adj("glorious");
set_short("large shimmering velvet cloth, trimmed with silver and gold");
set_long("A beautiful cloth, fashioned of red velvet, trimmed "
+"with silver and gold tassels and embroidery. Depicted in the center "
+"of the cloth is a large silver four-pointed star.\n");
add_prop(CONT_I_TRANSP, 1);
add_prop(CONT_I_MAX_WEIGHT, 999999);
add_prop(CONT_I_MAX_VOLUME, 999999);
add_prop(OBJ_I_NO_GET, "For some reason you are unable to even touch it!\n");

}


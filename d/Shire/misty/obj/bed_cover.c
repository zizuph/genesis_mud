inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
  seteuid(getuid());

    set_name("cover");
    add_name("_bed_cover_for_goblin_hotel_");
    set_pname("covers");
    set_adj("bed");
    set_short("bed cover");
    set_pshort("bed covers");
    set_long("This is simple bed cover. You may be able to put it on "+
             "some empty bed.\n");

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, 100);
}

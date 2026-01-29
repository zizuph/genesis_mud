/* Retsina, the wine of Argos */
inherit "/std/drink";
#include <stdproperties.h>
 
create_drink()
{
    set_name(({"retsina","wine","bottle of retsina"}));
    set_short("bottle of retsina");
    set_pshort("bottles of retsina");
    set_long(
       "It is a white wine of Argosian vintage. It an odd pine aroma.\n");
    set_soft_amount(200);
    set_alco_amount(25);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 400);
}

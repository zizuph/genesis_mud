/* Brazier to hold the torch */
inherit "/std/container";
#include <stdproperties.h>

public void
create_container(void)
{
    set_name("sconce");
    add_name("brazier");
    set_adj(({"tall","stone"}));
    set_short("tall stone sconce");
    set_long("It is a tall sconce made from heavy grey "
      +"granite. It seems to be made to hold a light "
      +"source. Around it on the floor are strange patterns "
      +"of dots.\n");
    set_no_show_composite(1);
    add_prop(OBJ_M_NO_GET, "It is far too heavy.\n");
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000 + 1500);
    add_prop(CONT_I_MAX_WEIGHT, 10000 + 1500);
    add_prop(OBJ_I_VALUE, 58);
}

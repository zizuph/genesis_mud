/* A tray */
inherit "/std/container";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define BS(xx)        break_string(xx, 70)
#define BSN(xx)       break_string(xx + "\n", 70)
#define TO            this_object()
#define TP            this_player()

create_container()
{
    set_name("tray");
    set_short("silver tray");
    set_long("An elegant silver tray.\n");
    set_adj("silver");
    add_prop(CONT_I_WEIGHT, 900);
    add_prop(CONT_I_MAX_WEIGHT, 9000);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 1);
}

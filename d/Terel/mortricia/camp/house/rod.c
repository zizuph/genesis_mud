/* A black ebony rod. */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define BSN(xx) break_string(xx+"\n", 72)
#define TP      this_player()
#define TO      this_object()

create_object()
{
    set_name("rod");
    set_adj("black");
    set_short("black rod");
    set_long(BSN(
        "It's a long black rod. It looks as if it is " +
        "made of ebony. It's fastened to the wheel."
    ));
    add_prop(OBJ_I_VALUE, 90);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_M_NO_GET, 1);
}

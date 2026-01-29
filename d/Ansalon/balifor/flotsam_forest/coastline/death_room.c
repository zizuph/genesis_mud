#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit FOREST_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("");
    set_long("\n");

    reset_flotsam_room();
}

void
die_seq()
{

    return;

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    tell_room(TO, "You fall down towards the rocky cliff " +
      "bottom!\n\n\n\nYou scream!\n\nAAAAAAHHHHHHHHHH!\n");
    tell_room(TO, "\nYou smash into the rocks at the bottom " +
      "of the cliff!\n\n");
    tell_room(CROOM + "cliff_bottom","Something or someone " +
      "seems to have fallen off the cliff!\nWhatever it was " +
      "lands with a 'crunch' before you.\n");

    ob->move(CROOM + "cliff_bottom");
}


/* 
 * Base room for the College of Elemental Magic in Calia.
 * Contains any functionality common to the rooms in their tower
 *
 * Bishop, 13.1.2000.
 *
 */

inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";


static string basic_desc = "The floor is slightly warm to the touch" +
    " and made out half light grey and half dark grey marble tiles," +
    " creating a checkerboard pattern. Every tile - even the walls - emits" +
    " soft light, bathing the room in its glow.";
static string corridor_desc = "You stand in a corridor in the Marble" +
    " Tower.";
static string stair_desc = "";

public void
enter_inv(object ob, object from)
{

    // Security routine. Don't want other wizards checking the guild out.
    // At least not without permission.
    if (ob->query_wiz_level() > 0 && ob->query_name() != "Bishop")
    {
        log_file("college_wizard_entry", capitalize(ob->query_real_name())
            + " entered " + file_name(this_object()) + " at " +
            ctime(time()) + ".\n");
    }

    ::enter_inv(ob, from); 
}

varargs void
make_college_room(int special)
{
    if(!special)
    {
        add_item("floor", "The floor is made out of perfectly square" +
            " marble tiles, half dark grey and half light grey, in a" +
            " checkerboard pattern. It's warm to the touch and softly" +
            " glowing.\n");
        add_item(({"tile", "tiles"}), "The tiles are perfectly cut into" +
            " squares. The patterns in the marble seem to continue from one" +
            " tile to the adjacent ones.\n");
        add_item(({"pattern", "patterns"}), "The patterns in the marble" +
            " continue from one tile to the next flawlessly.\n");
        add_item(({"wall", "walls"}), "The walls are made from solid marble," +
            " with a shade somewhere in between the dark and light grey floor"+
            " tiles. The patterns in the marble connect perfectly with the" +
            " patterns on the floor and ceiling.\n");
        add_item("ceiling", "The ceiling is made out of marble, with a very" +
            " light, almost white shade. The patterns in the marble connect" +
            " perfectly with the patterns on the walls.\n");
    }

    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_LIGHT, 3);
    add_prop(ROOM_I_HIDE, 80);
}

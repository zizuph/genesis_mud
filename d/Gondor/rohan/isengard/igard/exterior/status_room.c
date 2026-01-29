/*
 *  IGARD_EXTERIOR + "status_room.c"
 *
 *  Room before the entrance to Isengard.
 *    This room is time-sensitive such that it will exit
 *    to pre- or post-ent Isengard depending on the
 *    Gondor clock.
 *
 *  Last modified by Alto, 03 January 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"
#include "/d/Gondor/common/lib/clock.h"

inherit IGARD_LIB + "igard_funcs.c";

public void        create_gondor();
public string      long_desc();
int                rq_stage_stored = rq_stage();


public int
query_gate_broken()
{
    if (rq_stage_stored < RQ_LEFT_HENNETH_ANNUN)
        {
        return 0;
        }

    return 1;
}


public void
create_gondor()
{
    set_short("A street leading up to the southern gate of Isengard");
    set_long(&long_desc());

    sky_add_items();

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_prop(ROOM_I_INSIDE, 0);

    add_item(({"street", "wide street"}), "This wide street leads north "
        + "to the great gate. It is made from great flat stones, "
        + "squared and laid with great skill. No blade of grass can "
        + "be seen in any joint.\n");
    add_item(({"stones", "flat stones", "great flat stones"}), "The "
        + "flat and squared stones are made from the same black rock "
        + "used in the construction of the ring wall.\n");
    add_item(({"door", "doors", "gate", "gates", "entrance",
        "great gate", "great southern gate"}), "Two mighty doors of "
        + "iron lie to the north. You will need to approach further to "
        + "make out their details.\n");
    add_item(({"landscape", "natural landscape", "terrain"}), "Here at "
        + "the foot of the Misty Mountains, the landscape is partly flat "
        + "but also has many sudden projections of black rock. The wall "
        + "before you is made from a combination of these natural "
        + "outcroppings as well as quarried stone worked by the hands "
        + "of Men.\n");
    add_item(({"rock", "black rock"}), "The great ring wall is made "
        + "from black rock, both natural and that quarried by the hands "
        + "of Men.\n");
    add_item(({"isengard", "fortification"}), "The fortification of "
        + "Isengard stands "
        + "directly in front of you. It can only be entered through "
        + "a gate in the southern section of its ring wall.\n");

    add_exit("/d/Gondor/rohan/isengard/isenroad/isenroad4", "south");

    if (!query_gate_broken())
    {
        add_exit(IGARD_WALL     + "gate.c",        "north");
        add_item(({"wall", "ring wall", "ringed wall"}), "A great wall "
           + "of black stone stands at least one hundred feet tall and "
           + "curves away to the west and east. It appears to be made "
           + "partly from the natural landscape but also by the hand of "
           + "Men. Standing this close to the wall makes it impossible "
           + "to determine how far it extends or what lies on the other "
           + "side. You can, however, see the peaks of the Misty "
           + "Mountains above it.\n");
    }

    if (query_gate_broken())
    {
        add_exit(IGARD_WALL     + "closed_gate.c", "north");
        add_item(({"wall", "ring wall", "ringed wall", "rubble",
           "heap of rubble"}), "The great wall "
           + "of Isengard once stood at least one hundred feet tall and "
           + "curved away to the west and east as far as the eye could "
           + "see. Now it is nothing but an impassible heap of rubble.\n");
    }

    reset_room();
}


string
long_desc()
{
    if (query_gate_broken())
    {
      return "The street here leads directly up to what was once the "
      + "great southern gate "
      + "of Isengard, home of Saruman the Wise." + sky_desc() 
      + " The massive Ring Wall is now little more than an impassible "
      + "heap of rubble.\n";
    }

    return "The street here leads directly up to the great southern gate "
      + "of Isengard, home of Saruman the Wise." + sky_desc() 
      + " The massive Ring Wall stretching out to the east and west "
      + "dominates your line of sight, although you can see the southern "
      + "peaks of the Misty Mountains above it.\n";
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
}


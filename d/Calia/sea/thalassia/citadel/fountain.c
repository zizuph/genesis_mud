
/*  Air Fountain in the Citadel of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

void
create_water_room()
{
    set_short("Air Fountain of Thalassia");
    set_long("This is the most fascinating thing you have laid your "+
        "eyes upon in a long time. It appears to be a fountain of "+
        "sorts, but instead of water falling down into a basin, it "+
        "is actually air bubbles floating upwards into a basin. The "+
        "fountain itself is of mermaids and tritons holding their "+
        "hands above their heads, looking upwards. The bubbles are "+
        "rising from their mouths as if they are chanting, or singing. "+
        "A steady stream of air rises into the basin, and is somehow "+
        "recirculated to the bottom, where it rises again. To the "+
        "north you see the entrance to the Temple of Diabrecho, while "+
        "to the south sits the Royal Palace, surrounded by a garden. "+
        "West of here lies the hot water spring house and east lies "+
        "the cold water spring house.\n");

    add_item("fountain","It appears to be a fountain of "+
        "sorts, but instead of water falling down into a basin, it "+
        "is actually air bubbles floating upwards into a basin. The "+
        "fountain itself is of mermaids and tritons holding their "+
        "hands above their heads, looking upwards.\n");

    add_item(({"temple","Temple","Temple of Diabrecho","temple of diabrecho"}),
        "The Temple of Diabrecho is a large structure constructed of solid "+
        "silver, making it glitter brightly in the light. Along the pediment "+
        "you can see many statues made of gold. High above you, on top of "+
        "the temple sits the golden dome.\n");

    add_item(({"statue","statues"}),"The golden statues are sculptures of "+
        "past rulers of the city as well "+
        "as prominent people of the city.\n");

    add_item(({"garden","well kept garden"}),"The garden surrounds "+
        "the Royal Palace south of you. It appears to be well taken "+
        "care of by the citizens of this fair city.\n");

    add_item(({"palace","Palace","royal palace","Royal Palace",
        "massive royal palace","massive Royal Palace"}),
        "South of you is the Royal Palace of Thalassia, finely "+
        "constructed with colourful marble. The palace itself "+
        "is two stories tall. Surrounding the palace is a well kept "+
        "garden.\n");

    add_item(({"dome","golden dome","beautiful dome","beautiful golden dome"}),
        "This massive golden dome rises up into the water far above any "+
        "other object in this city. The dome itself must be over one "+
        "hundred feet high and two hundred feet wide at the base. It sits "+
        "atop the Temple of Diabrecho.\n");

    add_item(({"house","spring house"}),"Do you want to look at the "+
        "hot water spring house or the cold water spring house?\n");

    add_item("hot water spring house",
        "To the west you see the hot water spring house, which houses "+
        "the magical hot water spring that was granted to the citizens of "+
        "this city by Lord Diabrecho himself. From this place you cannot "+
        "see the entrance to this building.\n");

    add_item("cold water spring house",
        "To the east you see the cold water spring house, which houses "+
        "the magical cold water spring that was granted to the citizens of "+
        "this city by Lord Diabrecho himself. From this place you cannot "+
        "see the entrance to this building.\n");

    add_item(({"bubble","bubbles","air bubble","air bubbles"}),
        "The bubbles are a refreshing sight to see with your lungs "+
        "crying out for the air they so desperately need.\n");

    add_item(({"mermaid","mermaids","triton","tritons"}),"These "+
        "statues are perfectly sculpted from marble and decorated "+
        "with silver and gold. The creatures portrayed are "+
        "life-sized replicas of the creatures you see swimming around "+
        "this city.\n");

    add_item("basin","This large basin sits atop the fountain to "+
        "catch all of the air bubbles and recirculate them to the "+
        "bottom somehow. There is a very steady stream of air "+
        "rising into it and it seems like there is almost no "+
        "water in it at all.\n");

    add_swim_exit(THALC+"temple1","north",0,1);
    add_swim_exit(THALC+"hot","west",0,1);
    add_swim_exit(THALC+"cold","east",0,1);
    add_swim_exit(THALC+"palace_1_15","south",0,1);
    add_swim_exit(THALC+"citadel8","northwest",0,1);
    add_swim_exit(THALC+"citadel12","northeast",0,1);
    add_swim_exit(THALC+"citadel5","southwest",0,1);
    add_swim_exit(THALC+"citadel16","southeast",0,1);
}

void
init()
{
    ::init();
    add_action("enter_basin","enter");
}

int
enter_basin(string str)
{
    notify_fail("Enter what?  The basin?\n");
    if (str == "basin")
    {
        write("You swim up into the basin. You breath a sigh of "+
            "relief as the pure air enters your lungs once more.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) +
            " swims up into the basin.\n", this_player());
        this_player()->move_living("M",THALC+"inbasin",0);
        tell_room(environment(this_player()), QCTNAME(this_player()) +
            " arrives and takes in a deep breath of air.\n", this_player());
        return 1;
    }
    return 0;
}

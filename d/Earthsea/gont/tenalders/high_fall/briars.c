/*
 * coded by Amelia 3/16/97
 * old forest room north of Ten Alders
 * specials:  search for herbs
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/herbs/specials/hs";

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"

private object bunny;

public void
reset_room()
{
    ::reset_room();

    if(!objectp(bunny))
    {
        bunny = clone_object("/d/Earthsea/gont/tenalders/npc/rabbit");
        bunny->move(this_object());
        bunny->command("emote hops in.");
    }
}

public void
create_earthsea_room()
{
    set_short("A briar patch");
    set_long("You find yourself inside a dense briar patch. " +
        "Although sharp spiky thorns threaten to gouge you, there is " +
        "a soft nest on the ground of green grass. It is a fine spot " +
        "for a small animal to seek protection.\n");
    add_item((({"green grass", "grass", "nest", "soft nest"})),
        "On the floor of the patch the ground is surprisingly soft, " +
        "like a soft nest for a small animal seeking protection.\n");
    add_item((({"thorns", "spiky thorns", "briars", "briar patch"})),
        "The wall of thorny briars makes a natural defense against " +
        "predators.\n");
    reset_room();
    add_exit("n6", "back");
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
}

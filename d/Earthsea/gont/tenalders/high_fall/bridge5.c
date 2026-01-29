/*
 * coded by Amelia 3/16/97
 * bridge ne of Ten Alders
 * specials:  room_tell.c 
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

public void
create_earthsea_room()
{
    set_short("A hanging bridge");
    set_long("A bridge made from old rope, suspended over " +
        "a wide ravine. To the northeast you see a vast waterfall " +
        "that roars down into the river below the bridge. The " +
        "white water swirls dangerously far below.\n");
    add_item((({"waterfall", "river", "maelstrom", "white water", "water"})),
        "Far below you see white swirling water that comes from the " +
        "vast waterfall to the northeast of the bridge.\n");
    add_item((({"bridge", "rope bridge"})),
        "You are standing on an old rope bridge, which extends " +
        "across a ravine far above a rapid river. It sways " +
        "with every move.\n");
    add_item("ravine",
        "The ravine is a vast chasm that extends to a large cliff " +
        "beyond.\n");
    set_tell_time(15);
    add_tell("The bridge sways perilously under your feet.\n");
    add_tell("You look down at the swirling maelstrom far " +
        "below, and feel intense vertigo.\n");
    add_tell("You feel very dizzy.\n");
    add_tell("Your foot slips on the damp rope, you almost fall!\n");
    add_exit("ne7", "east", 0, 2, 0);
    add_exit("bridge4", "west", 0, 2, 0);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        ob->catch_tell("As you step forward, the bridge sways " +
            "dangerously under your feet.\n");
    }
}

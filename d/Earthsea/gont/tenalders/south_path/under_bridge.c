#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

private object troll;

public void
create_earthsea_room()
{
    set_short("Under the wooden bridge");
    set_long("You are standing under the wooden bridge " +
        "with just barely enough room to stand up straight. It is " +
        "rather dark down here, and you can see signs that some " +
        "creature uses this area as its den. It leads back further " +
        "to what looks like a cave, but it is too dark to see " +
        "what could be in it.\n");
    add_item((({"bridge", "wooden bridge", "river"})),
        "Just overhead is a wooden bridge, which is like a roof " +
        "over this place. A fast-flowing blue river flows past, " +
        "rushing south to the sea, and occasionally you can see " +
        "a small fish leap up in it.\n");
    add_item((({"den", "cave"})),
        "A very dark cave goes back into the hill, where some " +
        "nasty creature has a den, as you can see from the refuse " +
        "and bits of fish and bones lying about here.\n");
    add_exit("bridge", "up");
    add_exit("troll_cave", "east", "@@troll_there");
    reset_room();
}

public void
reset_room()
{
    if(!objectp(troll))
    {
        troll = clone_object("/d/Earthsea/gont/tenalders/npc/troll");
        troll->move(this_object());
        troll->command("emote snarfles in.");
    }
}

public int
troll_there()
{
    if(present("_ophotee_", this_object()))
    {
        write("The troll won't let you pass.\n");
        return 1;
    }

    return 0;
}

#pragma strict_types
#pragma no_clone

inherit "/d/Earthsea/std/room";

#include <macros.h>
#include <stdproperties.h>

private object *birds = allocate(5);
private int coconuts, dung, egg;

public void
reset_room()
{
    object to = this_object();
    int i, cloned = 0;

    coconuts = 0;
    dung = 1;
    egg = 1;

    for(i = 0; i < 5; i++)
    {
        if(!birds[i])
        {
            birds[i] = clone_object(
                "/d/Earthsea/gont/beach/npc/bird"
            );

            if(birds[i]->id("seagull") || birds[i]->id("puffin"))
            {
                birds[i]->add_leftover(
                    "/d/Earthsea/gont/beach/obj/gull_gut", "gut",
                    1, 0, 0, 1);
            }

            birds[i]->move(to);
            cloned = 1;
        }
    }

    if(cloned)
    {
        set_alarm(1.0, 0.0, &tell_room(to, "A swarm of birds swoop " +
            "down to check the nest but begin to scatter when they " +
            "find it empty.\n"));
    }
}

public void
create_earthsea_room()
{
    set_short("Top of the tree");
    set_long("Lush green fronds lie directly beneath you, delicately " +
        "supported by uncomfortably short branches stemming from the " +
        "trunk of the tree. A large nest lies at the center of " +
        "the trunk.\n");
    add_item(({"frond", "fronds", "green frond", "green fronds",
        "lush frond", "lush fronds", "lush green frond",
        "lush green fronds"}),
        "They don't look like they could support your weight for " +
        "very long, especially since they are already weighted with " +
        "coconuts! Perhaps you should just make your way down?\n");
    add_item(({"coconut", "coconuts"}),
        "Dozens of coconuts hang from the bases of the fronds, causing " +
        "them to droop down towards the ground.\n");
    add_item(({"tree", "white tree", "tall tree", "tall white tree",
        "top"}),
        "You are at the top of a tall white tree. Perhaps too tall...\n");
    add_item(({"branch", "branches", "short branch", "short branches",
        "uncomfortably short branch", "uncomfortably short branches"}),
        "The branches are short. Very short...\n");
    add_item(({"nest", "large nest"}),
        "A large nest made of sticks and mud. There are a few " +
        "shattered eggs lying in it, and it is caked with " +
        "a fine layer of guano.\n");
    add_item(({"sticks", "stick", "mud"}),
        "The nest is made of sticks and mud.\n");
    add_item(({"eggs", "egg", "shattered eggs", "shattered egg"}),
        "Eggs of various sizes, many recently hatched.\n");
    add_item(({"guano", "bird guano", "layer", "layer of guano"}),
        "The nest is covered with bird guano, both old and new.\n");
    add_exit("/d/Earthsea/gont/beach/beach_rooms/beach15", "down");
    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "search_func");
    setuid();
    seteuid(getuid());
    reset_room();
}

public int
jump(string str)
{
    object tp = this_player();
    int i;

    if(!str || !parse_command(str, this_object(),
        "[carefully] [on] [a] [the] [uncomfortably] [short] 'branch' / " +
        "'branches"))
    {
        write("You aren't sure that you want to jump here at all, " +
            "though if you were very careful you might be able to " +
            "jump on the branches and knock down a coconut or two.\n");
        return 1;
    }

    if(coconuts >= 10 || !random(10))
    {
        say(QCTNAME(tp) + " jumps carefully on a short branch, but " +
            "fails to knock down any coconuts.\n");
        write("You jump carefully on a short branch, but fail to " +
            "knock down any coconuts.\n");
        return 1;
    }

    say(QCTNAME(tp) + " jumps carefully on a short branch and manages " +
        "to knock down a few coconuts!\n");
    write("You jump carefully on a short branch and manage to knock " +
        "down a few coconuts!\n");

    for(i = 0; i < 2+random(2); i++)
    {
        clone_object("/d/Earthsea/gont/beach/obj/fresh_coconut")->move(
            "/d/Earthsea/gont/beach/beach_rooms/beach15");
        coconuts++;
    }

    tell_room("/d/Earthsea/gont/beach/beach_rooms/beach15",
        "A few coconuts fall from the sky and barely miss your head!\n");

    return 1;
}

public void
init()
{
    ::init();
    add_action(jump, "jump");
}

public string
search_func(object tp, string str)
{
    if(str == "guano" || str == "layer" ||
        str == "layer of guano")
    {
        if(!dung)
        {
            return "You scrape through the layer of guano " +
                "but come up empty handed.\n";
        }

        clone_object("/d/Earthsea/gont/beach/obj/dung_dust")->move(
            tp, 1);
        dung = 0;
        return "You scrape through the layer of guano and " +
            "collect a pile of dust.\n";
    }

    if(str == "egg" || str == "eggs" || str == "shattered egg" ||
        str == "shattered eggs")
    {
        if(!egg)
        {
            return "You scour through the shattered eggs " +
                "but come up empty handed.\n";
        }

        clone_object("/d/Earthsea/gont/beach/obj/hollow_egg")->move(
            tp, 1);
        egg = 0;
        return "You scour through the shattered eggs and manage to " +
            "find an intact, though strangely hollow, egg.\n";
    }

    return 0;
}

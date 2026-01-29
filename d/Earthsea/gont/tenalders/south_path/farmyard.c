#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#define KARGS ({ \
    "/d/Earthsea/gont/tenalders/npc/karg1", \
    "/d/Earthsea/gont/tenalders/npc/karg2", \
    "/d/Earthsea/gont/tenalders/npc/karg3", \
    "/d/Earthsea/gont/tenalders/npc/karg4", \
    "/d/Earthsea/gont/tenalders/npc/karg5", \
})

private int ambush_on = 1;

public void
create_earthsea_room()
{
    set_short("Farmyard");
    set_long("The path ends here in a farmyard. To the east " +
        "stands a large barn, and to the west is a farm cottage. Both " +
        "buildings are boarded shut. The roof of the cottage is " +
        "blackened as if it had been set afire and burned out. The " +
        "stench of burned thatch and something like burned hide or " +
        "hair fills your nostrils.\n");
    add_item((({"cottage", "farm cottage", "thatch", "thatched roof"})),
        "The thatched roof of " +
        "the cottage is blackened in spots, as though someone had tried " +
        "to set fire to it, but it was too damp to burn all the way.\n");
    add_item("buildings", "The buildings are boarded shut " +
        "and apparently the inhabitants left in a hurry, " +
        "having prepared for some sort of siege.\n");
    add_item("barn", "The tall barn is boarded shut, and appears " +
        "abandoned.\n");
    add_exit("farm_path_1", "south");
}

public void
ambush()
{
    object *kargs = allocate(4), to = this_object();
    int x = 4;

    setuid();
    seteuid(getuid(to));

    if(!present("karg", to))
    {
        while(x--)
        {
            kargs[x] = clone_object(KARGS[random(sizeof(KARGS))]);
            kargs[x]->move(to);
        }

        kargs[3]->command("shout ATTACK!!");
        tell_room(to, "A band of kargs comes running in, screaming " +
            "warcries!\n");
        tell_room(to, "AMBUSH!!\n");
    }
}

public void
init()
{
    ::init();

    if(ambush_on)
    {
        ambush_on = 0;
        ambush();
    }
}

public void
reset_room()
{
    ambush_on = 1;
}

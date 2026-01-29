/* Ashlar, 13 Jul 97 - The slavemaster's hut */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include <stdproperties.h>
#include <language.h>

inherit OUTER_IN;

object master,slave,collar;

int key_among_straw;

void
reset_neraka_room()
{
    if (!objectp(collar))
    {
        collar = clone_object(NOBJ + "slave_collar");
        collar->move(TO,1);
    }
    if (!objectp(master))
        master = clone_npc(NNPC + "slavemaster");
    if (!objectp(slave))
    {
        slave = clone_npc(NNPC + "fslave1");
        master->command("emote chains the slave to the wall.");
        collar->add_prop(CONT_I_CLOSED, 1);
        collar->add_prop(CONT_I_LOCK, 1);
    }
}


void
create_neraka_room()
{
    set_short("inside a large stone hut");
    set_long("You have entered a large stone hut. The floor is covered " +
        "with dirty straw, and the walls are streaked with grime. " +
        "A metal grating covers a hole in one end of the room. " +
        "@@slave@@\n");

    add_item_inside();
    add_item(({"straw","dirty straw","smelly straw"}),
        "The straw is not only dirty, but also smelly. The inhabitant of " +
        "this hut seems not overly concerned with cleanliness.\n");

    add_search(({"straw","dirty straw","smelly straw"}),
        7, "find_key", 1);

    add_item(({"grating","grate","metal grating"}),
        "It is made of thick metal bars, and covers a hole which is a " +
        "few decimeters wide.\n");

    add_item("hole","It is a dark hole. Looking down it you think you " +
        "can see the faintest glitter, as of water down there. There is " +
        "a smell of sewage wafting up from the hole.\n");

    add_exit(NOUTER+"black/b23","west");

    reset_room();
    key_among_straw = 0;
}

string
slave()
{
    if (objectp(slave) && (E(slave) == TO))
        return "A young female slave sits in a corner, chained to the wall.";
    else
        return "An empty iron collar is fastened to the wall by a chain.";
}

void
set_key_among_straw()
{
    key_among_straw = 1;
}

int
query_key_among_straw()
{
    return key_among_straw;
}

mixed
find_key(object searcher, string searched)
{
    object key;

    if (key_among_straw)
    {
        setuid();
        seteuid(getuid(this_object()));
        key = clone_object(NOBJ + "slave_key");
        key->add_prop(OBJ_M_NO_GET,"@@foil1");
        key->move(TO);
        
        key_among_straw = 0;
        return "You find a " + key->short() + " among the " + searched + ".\n";
    }
    else
        return 0;
}

void
plop2()
{
    tell_room(TO,"You hear a soft plop coming from down below the metal " +
        "grating. Something must have fallen into water down there.\n");
}

void
plop()
{
    set_alarm(2.0,0.0,plop2);
}

#pragma strict_types
#pragma no_clone

inherit "/d/Earthsea/std/room";

#include "check_tide.h"
#include <macros.h>

#define KARG "/d/Earthsea/gont/tenalders/npc/karg1"

private object karg_1, karg_2, karg_3;
private string extra_long;

public void create_landing() { }

public void
set_extra_long(string str)
{
    extra_long = str;
}

public int
air(string s)
{
    if(!strlen(s) || !parse_command(s, this_object(), "[the] [sea] 'air'"))
        return notify_fail("Smell what? The air?\n");

    write("This place stinks with the stench of foul smelling " +
        "dirty kargs.\n");

    return 1;
}

public void
init()    
{
    ::init();
    add_action(air, "smell");
    add_action(check_tide, "check");
}

public nomask void
create_earthsea_room()
{
    create_landing();

    set_short("Ship landing");

    set_long("The white sandy beach is littered with even more camp " +
             "fires. Around the camp fires lie many " +
             "temporary sleeping arrangements. Crudely made " +
             "swords, spears, and axes lie next to many of the " +
             "arrangements. Several large ships " +
             "have anchored in the cove near here and small " +
             "landing boats have landed here as well. Their " +
             "owners do not seem to be too friendly." +
             (extra_long ? (" " + extra_long + "\n") : "\n"));

    add_item(({"ship", "ships", "boat", "boats", "landing boats",
               "landing boat"}),
             "Taking a closer look at the markings painted on the " +
             "boats and ships, you conclude that these ships must " +
             "be from Kargad, the archipelago of islands to the east.\n");
    add_item(({"fire", "camp fire", "fires", "camp fires"}),
             "The fires are burning red hot. Some of them have " +
             "meat roasting on top.\n");
    add_item(({"sleeping arrangements", "sleeping arrangement",
               "arrangements", "arrangement"}),
             "The arrangements lie on the ground around " +
             "the fires.\n");
    add_item(({"tide","tides"}),
             "The eternal tides rise and fall at the whim of the " +
             "relentless sea. Why don't you check it?\n");
}

public void
reset_room()
{
    object to = this_object();

    if(karg_1 || karg_2 || karg_3)
        return;

    tell_room(to, "A small boat moves in from the sea.\n");
    karg_1 = clone_object(KARG);
    karg_1->move(to);
    karg_1->command("emote jumps out of the boat.");
    karg_2 = clone_object(KARG);
    karg_2->move(to);
    karg_2->command("emote leaps in screaming wildly in Kargish!");
    karg_3 = clone_object(KARG);
    karg_3->move(to);
    karg_3->command("emote gets out of the boat.");
}

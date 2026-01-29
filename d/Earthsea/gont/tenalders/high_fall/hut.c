/*
 * old hut
 * Coded by Amelia 11/22/97
 * contains chest with a scroll
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>

private object chest;
private int bed_made = 0;

public void
create_earthsea_room()
{
    object door;

    set_short("Dilapidated hut");
    set_long("This poor hut is constructed from blocks of " +
        "sod set together with only earth as mortar. The floor " +
        "is packed dirt, and a chimney blackened by years of " +
        "smoke leads from a small dirty hearth to the roof. " +
        "You notice a bed of sorts in the " +
        "north corner. It is cheerless here, as if someone rejected " +
        "by society lived as a hermit, not caring for any " +
        "niceties. There is a walking stick or staff in the " +
        "corner set against the wall.\n");
    add_item((({"chimney", "smoke" })),
        "A thick black residue covers the chimney, as if " +
        "years of smoke had darkened it. It extends to a " +
        "hole in the roof.\n");
    add_item((({"sod", "blocks of sod"})),
        "The blocks of sod seem to hold together by their " +
        "weight and the mud packed carelessly into the cracks " +
        "between.\n");
    add_item((({"walking stick", "staff"})),
        "As you examine the staff more closely, you see that " +
        "it is made from ash, but ... it seems to have been broken " +
        "and clumsily patched back together.\n");
    add_item((({"bed", "old bed"})),
        "In the north corner of the hut you see an old bed with " +
        "a tattered coverlet lying on it. " + "@@bed_made");
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();

    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/hut_in");
    door->move(this_object(), 1);
}

public void
reset_room()
{
    if(!sizeof(FILTER_LIVE(all_inventory(this_object()))))
    {
        if(chest)
        {
            chest->remove_object();
        }

        bed_made = 0;
    }
}

public string
bed_made()
{
    if(bed_made)
    {
        return "The bed is neatly made.\n";
    }

    return "It looks as though someone needs to make the bed.\n";
}

public int
make_bed(string str)
{
    object tp, to;

    if(str != "bed")
    {
        return notify_fail(capitalize(query_verb()) + " what?\n");
    }

    if(bed_made)
    {
        write("The bed is already made.\n");
        return 1;
    }

    to = this_object();

    write("You straighten the coverlet on the bed and fold " +
        "the corners under neatly.\n");
    say(QCTNAME(this_player()) + " straightens the coverlet on the " +
        "bed, folding the corners under neatly.\n");

    bed_made = 1;

    if(!chest)
    {
        chest = clone_object("/d/Earthsea/gont/tenalders/obj/items/scroll_chest");
        chest->move(this_object(), 1);
        tell_room(this_object(), "With the covers nicely straightened, " +
            "you notice there is a cedar chest at the foot of " +
            "the bed.\n");
    }

    return 1;
}

public void
init()
{
    ::init();

    add_action(make_bed, "make");
    add_action(make_bed, "straighten");

    write("From the corner of your eye you see some dark shape "+
        "disappear into the shadows.\n");
}

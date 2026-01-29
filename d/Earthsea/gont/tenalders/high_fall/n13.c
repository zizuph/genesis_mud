/*
 * coded by Amelia 3/16/97
 * old forest room north of Ten Alders
 * slightly changed syntax on unlock --Amelia 7/26/98
 * Changed level of awareness for player to enter tree to 10
 *
 * Player has to have awareness of level 10 to be able
 * to find the unusual door and unlock it 
 * Once unlocked, the player can open a door and create
 * the entrance
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_forest_room";

#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h";

#define SEARCHED_BARK  "_searched_bark"

private int unlocked = 0, open_door = 0, snap_id;

public void
create_forest_room()
{
    set_short("Under a tall redwood tree");
    set_long("The path ends at the foot of a giant tree which towers " +
        "above you just to the south from " +
        "here, standing out against the other trees due to its great size " +
        "and girth. Some distance above, the tree shows claw marks " +
        "scratched deep into the bark. Only a few of the widespread " +
        "branches bear life in the form of long thin evergreen needles. " +
        "The wind soughs through the branches making a dry rasping " +
        "noise. The clearing beneath the tree is surrounded by a wreath of " +
        "thick thorn-covered bushes and briars.\n");
    add_item((({"wreath", "bushes", "briars"})),
        "Dense bushes and thorny briars prevent you from leaving the " +
        "trail here.\n");
    add_item((({"floor", "forest floor"})),
        "The forest floor is fairly steep, and it is " +
        "difficult to walk here.\n");
    add_item((({"tree", "redwood tree"})),
        "A giant redwood tree towers above you to the south.\n");
    add_item("cracks", "@@see_door");
    add_item("bark", "This old tree has holes and cracks in its bark.\n");
    add_item((({"holes", "hole"})), "@@see_holes");
    add_item((({"door", "strange door"})), "@@exa_door");
    add_item("lock", "@@exa_lock");
    add_cmd_item((({"door", "strange door"})), "open", "@@open_door");
    reset_room();
    add_tell("From somewhere you hear a faint buzzing noise.\n");
    set_tell_time(120);
    add_exit("n12", "north");
    add_exit("inside_tree", "enter", "@@enter_tree", 0, 1);
}

public void
snap_shut()
{
    snap_id = 0;
    unlocked = 0;
    open_door = 0;
    tell_room(this_object(), "The tree makes a loud cracking noise, as " +
        "the door in the bark slams shut.\n", ({}));
}

public int
enter_tree()
{
    object tp = this_player();

    if(unlocked && open_door)
    {
        write("You enter the strange door in the tree.\n");
        tell_room(this_object(), QCTNAME(tp) + " enters into the tree.\n",
            ({ tp }));

        if(!snap_id)
        {
            snap_id = set_alarm(15.0, 0.0, snap_shut);
        }

        return 0;
    }

    write("You try to enter the tree and run smack into " +
        "hard wood.\n");
    tell_room(this_object(), QCTNAME(tp) + " runs into the tree!\n",
        ({ tp }));

    return 1;
}

public string
open_door()
{
    object tp = this_player();

    if(tp->query_skill(SS_AWARENESS) >= 10 && open_door)
    {
        return "The door is already open.\n";
    }

    if(tp->query_skill(SS_AWARENESS) >= 10)
    {
        if(unlocked)
        {
            open_door = 1;
            tell_room(this_object(), QCTNAME(tp) + " pushes against the bark " +
                "of the tree and reveals a large hole.\n", ({ tp }));
            return "You open the strange door.\n";
        }

        return "The door is locked.\n";
    }

    return "Open what?\n";
}

public string
see_door()
{
    if(this_player()->query_skill(SS_AWARENESS) >= 10)
    {
        return "As you examine the cracks in the tree bark more " +
            "closely, it seems that they form the pattern of a " +
            "strange door.\n";
    }

    return "This old tree has many cracks in its bark which " +
        "form interesting patterns.\n";
}

public string
exa_door()
{
    string door_open;

    if(this_player()->query_skill(SS_AWARENESS) >= 10)
    {
        if(open_door)
        {
            door_open = " The door stands open.\n";
        } else {
            door_open = " The door is closed.\n";
        }

        return "You see the outlines of a strange door in the " +
            "cracks in the bark." + door_open;
    }

    return "You find no door.\n";
}

public string
see_holes()
{
    if(this_player()->query_skill(SS_AWARENESS) >= 10)
    {
        return "Among the cracks and holes in the tree bark, there " +
            "is a hole that has an unusual shape...almost like " +
            "a keyhole...\n";
    }

    return "This is an old tree with many holes and cracks in " +
        "its bark.\n";
}

public string
exa_lock()
{
    if(this_player()->query_skill(SS_AWARENESS) >= 10)
    {
        return "One of the holes in the tree bark resembles " +
            "a keyhole.\n";
    }

    return "You find no lock.\n";
}

public int
unlock(string str)
{
    object tp = this_player(), *key;

    if(!str || tp->query_skill(SS_AWARENESS) < 10 ||
        (str != "door" && str != "door with key" &&
        str != "lock with key" && str != "lock"))
    {
        return notify_fail("Unlock what?\n");
    }

    key = FIND_STR_IN_OBJECT("_redwood_tree_key_", tp);

    if(sizeof(key))
    {
        write("You put the redwood key into the strange " +
            "lock in the bark door and turn it. The lock clicks, but " +
            "the key seems to be stuck.\n");
        key[0]->remove_object();
        tell_room(this_object(), QCTNAME(tp) +
            " unlocks the bark door.\n", ({ tp }));
        unlocked = 1;
        return 1;
    }

    return notify_fail("You do not have the right key.\n");
}

public int
pick(string str)
{
    if(str == "lock")
    {
        write("You cannot seem to pick the lock.\n");
        return 1;
    }

    return 0;
}

public void
init()
{
    ::init();
    add_action(unlock, "unlock");
    add_action(pick, "pick");
}

public void
reset_room()
{
    unlocked = 0;
    open_door = 0;
}

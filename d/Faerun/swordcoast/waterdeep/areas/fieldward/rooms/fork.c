/*
* fieldward/rooms/fork.c
* A fork in the road north of the North Gate of Waterdeep.
* A waystation stands here.
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_ROOM;

int invis_safeguard();
int block_exit();

void
create_fieldward_room()
{
    set_short("A waystation on the road to Waterdeep");
    set_extraline(
        "You stand on the High Road. It runs inland to the north, and into the "
        + "city of Waterdeep to the southwest. A smaller road forks off of the "
        + "main road here, and runs into the farmlands to the east."
        + "\nA waystation stands here.\n"
    );

    setup_outskirt_room();

    add_item(
        "waystation",
        "At the fork in the road stands a large, rustic-looking main building "
        + "accompanied by a small stable. It appears to be a waystation, "
        + "where weary wanderers upon the High Road may stop to replenish "
        + "their supplies, as well as their spirits.\n"
    );
    add_item(
        ({ "building", "buildings" }),
        "The waystation consists of a main building and a stable.\n"
    );
    add_item(
        ({ "stable", "small stable" }),
        "It is a stable, suitable for storing a small number of horses.\n"
    );
    add_item(
        ({
            "main building", "rustic-looking main building", "large building",
            "large main building", "large rustic-looking main building",
            "large, rustic-looking main building"
        }),
        "It looks positively inviting, you could enter it if you wanted.\n"
    );
    add_item(
        ({ "small road", "smaller road" }),
        "It branches out from the High Road and trails off into the farmlands "
        + "to the east.\n"
    );
    add_item(
        ({ "farmland", "farmlands", "landscape" }),
        "The landscape to the east is covered with fields and dotted with "
        + "farms.\n"
    );
    add_item(
        ({ "farm", "farms" }),
        "You can see several farms, interspersed among the fields to the "
        + "east.\n"
    );
    add_item(
        ({ "field", "fields", "crop" }),
        "Covering the farmlands to the east are vast fields where crop is "
        + "grown.\n"
    );
    add_item(
        "main road",
        "It is the High Road, a trade route that runs from Luskan to "
        + "Waterdeep.\n"
    );

    add_exit(SHR_LINK, "north", invis_safeguard);
    add_exit("foo", "east", block_exit);
    add_exit(FIELDW_ROOM + "northgate", "southwest");
}

int
invis_safeguard()
{
    if (TP->query_wiz_level() && !TP->query_invis())
    {
        write("\nDID YOU FORGET THAT YOU ARE VISIBLE? AGAIN?!?\n\n");
        return 1;
    }

    return 0;
}

int
block_exit()
{
    write(
        "A jet of sharp, blue flame shoots out from the ground in front of "
        + "you as you try to travel easts! The mages of Waterdeep will likely "
        + "seal off this anomaly soon, but for now it is safest not to tangle "
        + "with it.\n"
    );
    return 1;
}

int
enter_waystation(string arg)
{
    string *valid_args = ({
        "main building",
        "rustic-looking main building",
        "large building",
        "large main building",
        "large rustic-looking main building",
        "waystation"
    });

    if (member_array(arg, valid_args) != -1)
    {
        set_dircmd("waystation");
        write("You enter the waystation.\n");
        tell_room(
            TO,
            QCTNAME(TP) + " enters the waystation.\n",
            TP
        );
        TP->move_living("M", FIELDW_ROOM + "waystation01");
        tell_room(
            FIELDW_ROOM + "waystation01",
            QCTNAME(TP) + " arrives from the outside.\n",
            TP
        );
        return 1;
    }

    switch (arg)
    {
        case "stable":
            notify_fail("The stable appears to be for horses, mostly.\n");
            break;
        case "building":
            notify_fail("Enter which building? The waystation?\n");
            break;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(enter_waystation, "enter");
}

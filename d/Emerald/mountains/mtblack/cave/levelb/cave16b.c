/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"

void 
create_room()
{
    object door,key;

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    set_short("This is a strange dark place. "); 
    set_long("   " +
        "You have entered a strange room. It's strange because Tulix " +
        "hasn't decided what to do with it yet.\n\n");

    add_item(({"walls","wall"}), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n"
        );
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n");
    
    door=clone_object(CAVE_DIR + "obj/door16b.c");
    door->move(this_object());
    door->set_key(135876);

/*
    key=clone_object(CAVE_DIR + "obj/gold_key.c");
    key->move(this_object());
    key->set_key(135876);
*/

}

void
init()
{
    ::init();
    add_action("do_emote", "emote");
    add_action("do_emote", ":");
}

int
do_emote(string str)
{
    if (!str)
    {
    notify_fail("Emote what?\n");
    return 0;
    }
    else
    {
        this_player() -> catch_msg(
             "You emote: " + QCTNAME(this_player()) +
            " " + str + "\n");
        say(QCTNAME(this_player()) + " " + str + "\n");
        return 1;
    }
    return 0;
}

int
query_snoop(object ob)
{
        notify_fail("Snoop whom?\n");
        return 0;
}

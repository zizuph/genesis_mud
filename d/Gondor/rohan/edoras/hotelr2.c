/*
 *  The hotel room of the Sleeping Stallion
 *  
 *  copied from the hotel room in Re Albi 
 *
 *  created by unknown 
 *  modified for The Sleeping Stallion by Olorin on 6-jan-93
 *
 *  Copied for a second hotel room for the expansion of the 
 *  Dunlending Area.
 *  /d/Gondor/rohan/farm/farm/camp/
 *  Part of the Lost Sword quest.
 *
 *  Raymundo, Spring 2020
 */

inherit "/d/Gondor/common/room";
#include "/d/Gondor/common/lib/gs_include.c"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

void
create_room()
{
  set_short("Hotel room above the Sleeping Stallion");
  set_long(BS("You are in a well-decorated hotel room above the Sleeping "
    + "Stallion inn. There is a plush carpet on the floor, and a four-poster "
    + "bed. The walls are a light pink and decorated with painted "
    + "flowers. You can even smell flowers in the air. All in all, "
    + "this is quite a fancy room!"));

    add_item("room", "This is a hotel room, where people can spend the "
        + "night.\n");
    add_item("bed", "This is a four-poster bed with a pink netting draped "
        + "over it.\n");
    add_item( ({"post", "posts"}), "The posts look like they're made of oak "
        + "and carved vines all over them.\n");
    add_item( ({"vine", "vines", "carvings", "carving", "carved"}), 
        "This is the work of a master wood worker. They vines look like "
        + "They're almost alive.\n");
    add_item( ({"carpet", "plush carpet"}), "The carpet is thick and "
        + "soft, and green like spring grass.\n");
    add_cmd_item( ({"carpet", "plush carpet"}), ({"touch", "feel"}),
        "The carpet feels soft.\n");
    add_item( ({"wall", "walls"}), "The walls are painted pink. They have "
        + "flowers stenciled on them.\n");
    add_item( ({"flower", "flowers", "stencil", "stencils", "stenciled"}),
        "The flowers make you think of fields of daisies. They're quite "
        + "well done.\n");
    add_item("inn", "You are in the inn.\n");
    add_item("floor", "The floor is covered with plush carpet.\n");
    add_item("ceiling", "The ceiling is covered with the same copper ceiling "
        + "tiles you saw in the hallway.\n");
    add_item( ({"tile", "tiles", "ceiling tiles", "copper tiles", "copper"}),
        "The ceiling tiles are very intricate and well done, quite "
        + "upscale and luxurious.\n");
    add_item( ({"net", "netting"}), "The pink netting is sheer. You can "
        + "see through it, but it obscures very slightly what you're looking "
        + "at.\n");
    add_cmd_item( ({"net", "netting", "through netting", "through net"}), 
        ({"peer", "look", "see"}), "You see a bed through the netting.\n");

    add_cmd_item("here", "start", "You cannot start here. The room is "
        + "already occupied!\n");
  add_exit(EDORAS_DIR + "hotel_hall", "west");
    add_npc(EDORAS_DIR + "npc/jaine", 1);
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

init()
{
  ::init();
    add_action("do_smell", "smell");
    
}

void
reset_room()
{
    if(!present("jaine"))
    {
        add_npc(EDORAS_DIR + "npc/jaine", 1);
    }
}

int
do_smell(string str)
{
    if(!strlen(str))
    {
        write("You breathe deeply through your nose and smell the pleasant "
            + "aroma of roses.\n");
        say(QCTNAME(TP) + " breathes through " + HIS_HER(TP) + 
            "nose, smiling at the scent of flowers.\n");
        return 1;
    }
    if(str == "flowers" | str == "flower" | str == "scent" | str == "air")
    {
        write("You breathe deeply through your nose and smell the pleasant "
            + "aroma of roses.\n");
        say(QCTNAME(TP) + " breathes through " + HIS_HER(TP) + 
            "nose, smiling at the scent of flowers.\n");
        return 1;
    }
    else
        return 0;
}
/*
 *  /d/Emerald/telberin/gazebo.c
 *
 *  This gazebo is the location of the public bulletin board and
 *  portal to the common board in Telberin.
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/telberin/telberin_building";

#include <std.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/sys/paths.h"


/*
 * Function name:        create_telberin_building
 * Description  :        set up the building
 */
public void
create_telberin_building()
{
    object board;

    set_short("within a gazebo in the Magic Quarter of Telberin");
    set_em_long("You stand within an impressive gazebo, obviously"
      + " designed to accommodate a great number of people at one"
      + " time. Ornate lattice work is trimmed along the edges of"
      + " wood which has been framed out in long eaves which cover"
      + " a wide circular floor. At the center of the structure,"
      + " beneath a tall sloping roof, is an octagonal wooden pillar"
      + " which various persons within the city use as a public"
      + " notice board. Alongside various posters and other bits"
      + " of printed information is a bulletin board. A stairway"
      + " leads into one side of the central octagon, leading"
      + " up to some higher location within the gazebo. A pleasant"
      + " breeze blows through the gazebo, bringing with it honey-sweet"
      + " aromas from the Royal Fruit Garden whose southernmost trees"
      + " hang their branches over the roof.\n");

    add_item( ({ "gazebo", "area", "here", "room" }), long());
    add_item( ({ "lattice work", "lattice", "edges" }),
        "The lattice work recalls images of birch leaves and"
      + " flowing water. Great artistry was employed by the"
      + " responsible builder, who obviously went to great lengths"
      + " to make this a beautiful and serene structure.\n");
    add_item( ({ "eaves", "roof", "long eaves", "circular roof",
                 "up", "ceiling" }),
        "The roof is formed of eaves which radiate out from a central"
      + " pillar in the middle of the gazebo. Lattice work is trimmed"
      + " along the edges of the roof where smaller pillars support"
      + " the extremities.\n");
    add_item( ({ "pillar", "pillars" }),
        "Which pillar do you mean, the central pillar, or the smaller"
      + " pillars?\n");
    add_item( ({ "central pillar", "octagonal pillar",
                 "octagonal wooden pillar" }),
        "A very large central pillar supports the roof of this"
      + " gazebo. Its perimeter forms an octagon along the floor"
      + " boards, with each side a brief wall before turning to"
      + " meet its neighboring sides. An opening in one of these"
      + " walls houses a narrow stair.\n");
    add_item( ({ "small pillar", "smaller pillar", "small pillars",
                 "smaller pillars", "small wooden pillar",
                 "small wood pillar", "smaller wooden pillar",
                 "smaller wood pillar", "small wooden pillars",
                 "small wood pillars", "smaller wood pillars" }),
        "Wooden pillars support the eaves of the roof which hang"
      + " out over the gazebo floor. They are carved in a swirling"
      + " pattern and painted white. Between each pillar is a"
      + " waist-high railing.\n");
    add_item( ({ "rail", "railing", "waist-high railing" }),
        "The railings run between pillars which support the roof."
      + " They form the perimeter of the gazebo.\n");
    add_item( ({ "floor", "wide floor", "circular floor",
                 "wide circular floor", "down", "ground" }),
        "The floor of the gazebo is comprised of hardwood boards, which"
      + " have been sealed in a thick oil finish of some kind.\n");
    add_item( ({ "oil", "finish", "thick oil finish" }),
        "The oil finish on the floorboards is probably meant to"
      + " increase the durability of the wood against the stepping"
      + " foot. It also increases the beauty of the material, giving"
      + " it an excellent sheen.\n");
    add_item( ({ "public board", "notice board", "notice", "notices",
                 "public notice board", "public notice",
                 "public notices", "poster", "posters",
                 "information", "printed information" }),
        "The walls of the central pillar are covered with notices and"
      + " other types of printed information. Very little here seems"
      + " of interest, other than the bulletin board, which at times"
      + " contains interesting opinions from the populace.\n");
    add_item( ({ "stair", "stairway", "stairs", "staircase",
                 "steps" }),
        "The stairway enters the central pillar through an opening"
      + " in one of its sides. It appears to lead up into some"
      + " inner chamber within the pillar itself.\n");
    add_item( ({ "wall", "walls", "walls of the pillar",
                 "pillar wall", "pillar walls" }),
        "The perimeter of the pillar is made up of eight walls"
      + " in an octagonal facing. Most of them are covered with"
      + " public notices and the like. An opening leads from one"
      + " of them onto a stairway leading upward.\n");
    add_item( ({ "opening" }),
        "The opening leads up to some other level which is not"
      + " visible from here.\n");
    add_item( ({ "tree", "trees", "branch", "branches",
                 "southernmost tree", "southernmost trees" }),
        "A few branches trail from the trees of the Royal Fruit Garden"
      + " to touch the roof of the gazebo. Their blossoms fill the"
      + " area with a delightful aroma.\n");
    add_item( ({ "blossom", "flower", "flowers", "blossoms" }),
        "The blossoms from the fruit trees have a fiercely sweet"
      + " aroma, which at times is almost enough to cause one to"
      + " swoon. The slight breeze keeps the smells wafting pleasantly"
      + " through the gazebo.\n");
    add_item( ({ "breeze", "wind" }),
        "A breeze blows through the gazebo, every so often lifting"
      + " the edge of a poster or notice along the walls.\n");
    add_item( ({ "garden", "fruit", "fruit garden", "royal garden",
                 "royal fruit garden" }),
        "The Royal Fruit Garden lies just north of this gazebo. A few"
      + " of its southernmost trees have extended their branches"
      + " in over the rooftop.\n");

    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from inside the gazebo.");
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit("/d/Emerald/telberin/common_board_room", "up");
    add_exit("/d/Emerald/telberin/channelers_way01", "south", 0, 1, 1);

    board = clone_object("/std/board");
    board->set_board_name(BOARD_DIR + "telberin_boards");
    board->set_num_notes(25);         /* Number of notes         */
    board->set_anonymous(1);          /* You may write anonymous */
    board->set_silent(0);             /* Make noise when reading */
    board->set_show_lvl(0);           /* Full wizards or higher  */
    board->set_remove_lvl(15);        /* Full wizards or higher  */
    board->set_remove_str("You somehow failed.\n");
    board->set_use_gedit(0);          /* Don't use that marvellous editor */
    board->move(TO);
} /* create_telberin_building */


public mixed
query_location_ids()
{
    return "[the] [large] 'gazebo'";
}

public mixed
query_location_closed()
{
    return 0;
}

public mixed
query_location_desc()
{
    return "It's a large gazebo.\n";
}


public string
query_entry_desc()
{
    return "into the gazebo";
}

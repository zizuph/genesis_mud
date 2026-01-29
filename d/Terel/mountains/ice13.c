/*
    Modified 3 May 2003, by Bleys
        - fixed a typo in the set_long()

    28/04-17 Znagsnuf    
    Updated with the room an exit north, leading to the Ghastly Keep.
*/

inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

create_room()
{   
    set_short("Ice Wall");
    set_long("Snow and ice stand packed against the stony mountain side," 
      + " part revealed, showing a silver-veined rock. Upon the rock is" 
      + " carved a circular pattern with writing in its midst." 
      + " The wind howls loudly here, wild from the north, shaking bits"
      + " of snow and ice down from above. Two deep ruts in the icy"
      + " puddles is leading north.\n");
   
    add_item( ({"ruts", "rut"}), "Twin lines of tracks have been "
                   + "created from years of merchant wagons which have "
                   + "followed the path through the mountain pass.\n");

    add_item(({"circle", "circular pattern", "pattern"}),
      "A pattern of circles etched upon the cliff facing, one within the"
      + " other. In the midst thereof are letters.\n");

    add_item(({"writing", "letters"}), "They are very strange and unknown.\n");
    add_cmd_item("writing", "read", "DOL ASYU KOSS UDAS\n");

    add_item("rock", "It shows through from the snow and ice.\n");

    add_exit("/d/Terel/mountains/ice8", "east", 0);
    add_exit("/d/Terel/mountains/ghastly_keep/rooms/gkeep_ent2", "north", 0);
}
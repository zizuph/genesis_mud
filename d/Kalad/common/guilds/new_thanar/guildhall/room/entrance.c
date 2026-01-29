/**********************************************************************
 * - entrance.c                                                     - *
 * - The entrance room to the Guildhall of Thanar                   - *
 * - Created by Damaris@Genesis 3/2004                              - *
 * - New Standrad file for new area for guild. Typos fixed.         - *
 *   by Mirandus@Genesis 01/2018                                    - *
 **********************************************************************/

#pragma strict_types
#include "../guild.h"

inherit THANAR_STD_ROOM;

/*
 * Function name: block_exit()
 * Description  : Blocks the exit should we need to.
 */
public int
block_exit()
{
    write("You may not go this way, at this time.\n");
    return 1;
}

/*
 * Function name: members_only()
 * Description  : Allows only guild members to pass.
 */
public int
members_only()
{
    if ((TP->query_race() == "human" &&
         member_array(TP->query_race_name(), VALID_SUBRACES) >= 0) ||
         this_player()->query_wiz_level())
    {
    /* Is an acceptable race, pass through as normal */

    return 0;
    }

    write("A magical force prevents you from entering.\n");
    return 1;
}

object book;

/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
void
create_std_thanar()
{

    set_short("Sanctum Sanctorum");
    set_long("You have stepped into the sanctum of the Thanarian "+
      "Cathedral. Only those most revered by Thanar are welcome "+
      "within this space. The area is filled with priceless artifacts "+
      "ancient tomes, gilded texts and other holy relics. These have "+
      "been collected and amassed for use in holy ceremonies and for "+
      "the priests and priestesses of the order. To the north you are" +
      "able to see the chambers of the Thanarian Order. Those who wish "+
      "to identify themselves as followers of Thanar should proceed there. "+
      "Six paintings line the walls and a statue has been erected in the "+
      "centre of the room.\n");
      
    add_item(({"room", "area", "entrance", 
    "sanctum sanctorum", "sanctum"}),query_long);
    add_item(({"painting", "paintings"}),
      "There are beautiful paintings that line the oval walls here. "+
      "There are a total of six paintings and you should be able "+
      "to look a bit closer at each one.\n");
    add_item(({"first painting", "painting one"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth of "+
      "history. The scene depicted is of a small male human child "+
      "being compassionate towards some lowly demi-humans.\n");
    add_item(({"second painting", "painting two"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth of "+
      "history. The scene depicted is of a young male human "+
      "standing at large well serving water to the lowly demi-humans.\n");
    add_item(({"third painting", "painting three"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth "+
      "of history. The scene depicted is of a young male human "+
      "standing in a city square preaching the compassion of Thanar and the "
      +"path that demi-humans should follow.\n");
 
    add_item(({"fourth painting", "painting four"}),
      "The painting is quite exquisite and it tells a story "+
      "of ages old. The simple brush strokes along the canvas "+
      "bring out the scene in this painting to display such "+
      "truth of history. The scene depicted is of a young male "+
      "human standing in a city square with a mass of black "+
      "snakes surrounding him protecting him from demi-humans.\n");
    add_item(({"fifth painting", "painting five"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas "+
      "bring out the scene in this painting to display such "+
      "truth of history. The scene depicted is of a young male "+
      "human kneeling before an apparition of the great god Thanar.\n");
    add_item(({"sixth painting", "painting six"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth of "+
      "history. The scene depicted is of the great god Thanar "+
      "lifting up humanity while scattered below are demi-humans "+
      "who strive to be more like humans.\n");
    add_item(({"statue"}),
      "The statue is made from obsidian and it is the figure "+
      "of a noble human carrying a scroll in his hand and a "+
      "snake in the other. At the foot of the statue is a golden "+
      "plaque, which you may read.\n");
    add_item(({"texts", "ancient texts", "holy texts", "relics", "holy relics",
    "ancient relics", "tomes", "ancient tomes", "holy tomes", "gilded texts",
    "gilded tomes", "ancient relics", "artifacts", "priceless artifacts"}),
    "Secured behind lock and key you see beautiful relics, tomes, and "+
    "other assorted artifacts collected by the Thanarian Order for use in "+
    "holy ceremonies. Treatises on demi-humans, scripture, engraved boxes "+
    "ancient writings, and other items make up the collection.\n");
    add_item(({"treatises","scripture","engraved boxes","boxes","box",
    "engraved box","writings","ancient writings","ancient writing"}),
    "Within the items secured there are texts drafted by priests of the "+
    "Thanarian Order on many things. The engraved boxes appear to hold "+
    "incense that is used within the Cathedral.\n");
    add_item(({"scroll"}),
      "The scroll is part of the statue and is unreadable.\n");
    add_item(({"plaque","gold plaque", "golden plaque"}),
      "Welcome to the Temple of Thanar.\n\n"+
      "We are pleased that you have found your way here.\n"+
      "If you are human you may enter our grand temple\n"+
      "and learn more about the Great Thanar and our cause.\n\n"+
      "Chosen Minister of Thanar\n");
    add_cmd_item("plaque", "read","Welcome to the Temple of Thanar.\n\n"+
      "We are pleased that you have found your way here.\n"+
      "If you are human you may enter our grand temple\n"+
      "and learn more about the Great Thanar and our cause.\n\n"+
      "Chosen Minister of Thanar\n");
      
    clone_object(GUILD_DIR + "book")->move(this_object());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit("join", "north", members_only);
    add_exit(RDIR + "upper_mid5", "south");
    set_no_exit_msg(get_all_no_exits(({"s","n"})),
    "There is a wall blocking your path.\n");

}

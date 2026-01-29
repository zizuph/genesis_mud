/*
 * Pathway to Elementalist Temple
 * 
 * This is the pathway leading to the Elementalist Temple valley
 * that houses the Elemental Clerics, Elemental Worshippers, and
 * Elemental Seekers guilds.
 *
 * Created by Petros, April 2010
 */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

inherit "/std/room";
inherit "/d/Calia/lib/try_item";

/*
 * Function:    create_room
 * Description: Standard room creation function.
 */
public void
create_room()
{
    set_short("In a valley in the Calian foothills");
    set_long("You are standing in a luscious green valley teeming with "
        + "life. A cool breeze rustles the grass, creating a flowing "
        + "wave pattern in the landscape. A small rocky path to your "
        + "east leads up the gently sloping hillside. A large crystalline "
        + "structure is the prominent feature of this valley and it is "
        + "surrounded by a stone wall made of interleaving grey bricks. "
        + "A sense of peace overwhelms you as you gaze at the marvelous "
        + "materials used to construct the building. You can go into the "
        + "complex through the pointed archway to your north.\n\n");
                    
    try_item( ({ "bricks", "grey bricks", "brick", "grey brick", "wall",
        "stone wall", "grey rock", "rock" }),
        "The stone wall surrounding the large crystalline structure is "
      + "about 20 feet high and is made up of interleaving grey bricks. "
      + "The grey brick is unique to Calia, is slightly porous, yet is "
      + "very well indurated, making it perfect for fortifying walls.\n");
      
    try_item( ({ "valley", "green valley", "luscious green valley",
        "luscious valley" }),
        "You are standing in a marvelously green deep valley in the middle "
      + "of the Calian foothills. It is rather large and is surrounded by "
      + "mountains which protect it from the harsh elements. A large "
      + "crystalline structure surrounded by a wall sits in the middle of "
      + "the valley.\n");

    try_item( ({ "landscape", "grass", "stalks", "pattern", "wave pattern",
        "flowing pattern", "flowing wave pattern"}),
        "Everywhere you look, there is abundant grass. Strangely enough, "
      + "the grass is not overgrown. The cool breeze that flows through "
      + "the stalks of the grass create a flowing wave pattern that is "
      + "mesmerizing to look at.\n");

    try_item( ({ "path", "rocky path", "small rocky path", "east", "up",
        "hill", "hillside", "gently sloping hillside" }),
        "A gently sloping hill to your east has a small rocky path "
      + "that leads out of this valley. Besides the path, you see "
      + "plenty of flora.\n");

    try_item( ({ "crystalline structure", "crystalline", "temple",
        "structure", "prominent feature", "feature", "building", "complex" }),
        "A marvelously constructed crystalline structure sits in the middle "
      + "of the valley. The building looks like a giant crystal dome "
      + "surrounded by a grey wall. The entrance to the structure is to "
      + "your north through a pointed archway.\n");

    try_item( ({ "north", "pointed archway", "archway", "arch" }),
        "Looking to the north, you find a pointed archway in the middle "
      + "of the grey stone wall. It seems to lead into the structure "
      + "to your north. Through the opening, you can see evidence of a "
      + "garden beyond the walls.\n");

    try_item( ({ "garden", "opening" }),
        "You cannot see much of the garden through the opening in the "
      + "archway. It may be better to take a closer look by heading north "
      + "into the complex.\n");
      
    try_item( ({ "materials", "marvelous materials", "marble", "white marble" }),
        "The materials used to construct the crystalline structure stand "
      + "out as extremely rare in the land of Calia. The crystalline "
      + "material is known to be extremely rare, and is known to be used "
      + "in the Crystalline Palace, the home of the Calians. The white "
      + "marble comes from the quarries of Argos, and the grey rock is "
      + "known to be hard to obtain.\n");

    try_item( ({ "flora", "fauna", "life", "butterfly", "butterflies",
        "flowers", "flower", "wildflower", "wildflowers", "fields",
        "fields of wildflowers", "flocks", "flocks of butterflies" }),
        "Fields of wildflowers can be seen along the hillside, the type of "
      + "which have mostly disappeared from the Calian landscape as most of "
      + "Calia has given way to grasslands. Among the fields are flocks of "
      + "butterflies, one of the great natural beauties of Calia.\n");
                
    add_prop(ROOM_I_INSIDE, 0);
    add_exit(ELEMENTALIST_GARDEN + "garden_11g", "north","@@do_enter",1);
    add_exit(ELEMENTALIST_TEMPLE + "path2", "up");

    setuid();
    seteuid(getuid());
}

int
do_enter()
{
    string ogname, lgname;
    
    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        write("You hear a voice booming from above:\n"+
            "The Soulless may not enter here!\n");
        return 1;
    }
    
    ogname = TP->query_guild_name_occ();
    lgname = TP->query_guild_name_lay();

    if (member_array(ogname, BANNED_GUILDS) != -1)
    {
        write("You hear a voice booming from above:\n"+
            "You are not permitted to enter here!\n");
        return 1;
    }
    
    if (member_array(lgname, BANNED_GUILDS) != -1)
    {
        write("You hear a voice booming from above:\n"+
            "You are not permitted to enter here!\n");
        return 1;
    }
    
    return 0;
}
/*
 * Entrance of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"
#include <time.h>
#include <language.h>
#include <stdproperties.h>

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes

public void
create_temple_room()
{
    set_short("Entrance to the Elemental Temple");
    set_long("You are standing in the extremely spacious entrance to the "
        + "Elemental Temple. To your south is the way back out into the "
        + "Temple gardens. Hanging on the wall is a spectacular tapestry. "
        + "Besides the tapestry, the entry area is currently quite bare and "
        + "doesn't have any other remarkable features except for the five arches "
        + "to the north that lead into the Temple proper.\n\n");
    
    try_item( ({ "five arches", "arches", "arch", "entrance", "front",
        "grey rock", "grey rock material", "surfaces" }),
        "Five arches approximately the height of ten grown men take up most "
      + "of the front of the temple. Along the rims of each arch are carved "
      + "symbols and pictures. The walls of the temple are made of the same "
      + "grey rock material that is seen in the wall surrounding the garden "
      + "outside. However, here the surfaces of the rock have been polished "
      + "and are shiny and smooth.\n");
    
    try_item( ({ "symbols", "pictures", "symbol", "picture", "carving", }),
        "The symbols and pictures carved into the the rims surrounding the "
      + "arches depict the story of the Elementals of Calia. It shows the "
      + "Elementals involved in the creation of the world. Each arch has "
      + "a special emphasis related to each Elemental.\n");

    try_item( ({ "calendar", "tapestry", "spectacular tapestry" }),
        "@@calendar@@.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED,1);                   
    add_exit(ELEMENTALIST_TEMPLE + "greathall", "north");
    add_exit(ELEMENTALIST_GARDEN + "garden_11g", "south"); 
}

/*
 * Function:    calendar
 * Description: Describes the time of year in the Calian calendar.
 *              The description is used in the description of the
 *              tapestry.
 */
public string
calendar()
{
    int real_time, real_day;
    string day, month, image, rmonth;

    real_time = time();
    
    day = TIME2FORMAT(real_time,"d");
    real_day = atoi(day);

    month = TIME2FORMAT(real_time,"mmm");

    image = "This finely woven tapestry is a myriad of colours "+
        "and shapes. Focusing your energies upon the cloth, you are "+
        "granted a vision ";

    switch (month)
    {
        case "Jan":
            rmonth = "Moon of Frost On the Temple";
            image += "of the Holy Temple of Psuchae surrounded by the "+
                "dark forest. All things are covered with a gentle white "+
                "frost, glowing in the full moon above them.";
            break;
        case "Feb":
            rmonth = "Moon of the Dark Red Calves";
            image += "of a farmer kneeling in waning moonlight as a coming "+
                "dawn welcomes the birth of a calf, and the joy of new life.";
            break;
        case "Mar":
            rmonth = "Moon of the Snowblind";
            image += "of a full moon piercing the clouded night sky, its "+
                "light glinting off flakes of heavily falling snow, marking "+
                "the final fury of the season. You can barely make out a "+
                "conclave of pilgrims huddled in prayer in the midst of "+
                "five stone obelisks.";
            break;
        case "Apr":
            rmonth = "Moon of the Grass Appearing";
            image += "of small strands of grass just breaking the surface "+
                "of the ground, reaching up to touch the moon far above "+
                "them.";
            break;
        case "May":
            rmonth = "Moon When the Ponies Shed";
            image += "of dapple-grey pony, grazing contentedly among dogwood "+
                "trees. Strands of silvery hair are caught among the pink "+
                "blooms of the branches, and shine softly in the moonlight.";
            break;
        case "Jun":
            rmonth = "Moon of the Dancing Satyrs";
            image += "of pagan satyrs, dancing in celebration of the "+
                "solstice. They hold large bowls raised above their heads "+
                "in a gesture of celebration in the afternoon sun, even as "+
                "the new moon rises behind them.";
            break;
        case "Jul":
            rmonth = "Moon When the Cherries are Ripe";
            image += "of a small bird carrying a dark red fruit in its "+
                "beak as it flies near a babbling stream. The water appears "+
                "to glow as moonlight dances across its surface.";
            break;
        case "Aug":
            rmonth = "Moon of Golden Grasses";
            image += "of a lone cottage in a field of tall grasses, heavily "+
                "laden with grains. The scene is bathed in the firey glow of "+
                "a golden harvest moon.";
            break;
        case "Sep":
            rmonth = "Moon of the Changing Seasons";
            image += "of fishermen mending their nets and preparing their "+
                "boats to stand against the storms of winter seas. You can "+
                "just make out a tattoo on one of the sailors of a moon "+
                "enshrouded in thunderclouds.";
            break;
        case "Oct":
            rmonth = "Moon of the Olive Harvest";
            image += "of several ceramic amphorae stacked against a "+
                "crumbling brick wall. Each cask is filled with fresh "+
                "olive oil, and is stamped with the symbol of the olive "+
                "grower, a full moon flanked by five stars.";
            break;
        case "Nov":
            rmonth = "Moon of the Falling Leaves";
            image += "of yellow and golden brown leaves falling to the "+
                "ground illuminated by the moon shining high above them.";
            break;
        default:
            rmonth = "Moon of the Popping Trees";
            image += "of a stark landscape thickly populated with leafless "+
                "trees. Shadows cast by a young moon dramatically emphasize "+
                "the movement of the branches as they snap in the bitter "+
                "winter winds.";
            break;
    }
     
    return image+" Delicately embroidered along the bottom of the "+
        "tapestry are celestial symbols indicating that it is the "+
        LANG_ORD2WORD(real_day)+" day of the "+rmonth; 
}

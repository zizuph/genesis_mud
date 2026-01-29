/*
 * Base file for outside of Bag End/Bagshot Row
 * Finwe, April 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

//inherit "/std/room";
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";
inherit HERB_SEARCH;

int lawn_cut;   // -1 = no lawn to cut here, 0 = lawn not cut, 1 = lawn cut

void create_outside_room() {}
public string long_desc();

void lawn_status(int lawn)
{
    lawn_cut = lawn;
}

public void
create_area_room()
{
// A rocky path west of the Old Forest in the Downs.

//    set_area("west");
//    set_areaname("Waymeet"); 
//    set_land("Westfarthing");
//    set_areatype(0);
//    set_areadesc("well travelled road");


    create_outside_room();
    add_std_herbs("plain");

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
}
void add_smial_close()
{
    add_item(({"smial", "hobbit hole"}),
        "It is a burrow tunneled into the large hill. Windows are set " +
        "in the smial and look out through a garden growing in front of " +
        "them.\n");
    add_item(({"narrow strips of lead", "narrow strip of lead",
            "strips of lead", "strip of lead", "lead", "lead came",
            "lead cames"}),
        "It is strips of lead that are used to hold the panes of glass " +
        "together in the window.\n");
    add_item(({"glass", "pane of glass", "panes of glass"}),
        "They are clear and make up the window. They are mostly square " +
        "with other shapes in the window. They are held in place with " +
        "narrow strips of lead.\n");
}

/*****************************************************************************/
void add_bagend_garden()
{
    add_item(({"garden", "flower garden"}),
        "It is full of flowers and small bushes. It grows in front of " +
        "the smial providing a colorful backdrop in front of the " +
        "window.\n");
    add_item(({"flowers"}),
        "They are all sizes and colors. Some are tall while others " +
        "are short and small. The flowers are all colors and shapes " +
        "and some even fragrant. \n");
    add_item(({"bushes", "shrubs", "bush", "shrub"}),
        "They are woody plants that are smaller than trees. They grow " +
        "in the garden among the flowers.\n");
    add_item(({"woody plants", "woody plant"}),
        "They are shrubs and bushes growing in the garden.\n");
}

void add_bagend_front()
{
    add_item(({"smial", "hobbit hole"}),
        "It is a burrow tunneled into the large hill. Windows are set " +
        "in the smial and look out through a garden growing in front of " +
        "them.\n");
    add_item(({"path"}),
        "It runs east and west past the front of the smial through the " +
        "lawn. Flagstones are set in the lawn marking the path.\n");
    add_item(({"flagstone", "flagstones"}),
        "They are irregular shaped flat stones set into the lawn and mark " +
        "the path running alongside the smial.\n");
    add_item(({"lawn", "grass"}),
        "It is well cared for and green. The grass grows around the " +
        "flagstones.\n");
}
void add_windows()
{
    add_item(({"narrow strips of lead", "narrow strip of lead",
            "strips of lead", "strip of lead", "lead", "lead came",
            "lead cames"}),
        "It is strips of lead that are used to hold the panes of glass " +
        "together in the window.\n");
    add_item(({"glass", "pane of glass", "panes of glass"}),
        "They are clear and make up the window. They are mostly square " +
        "with other shapes in the window. They are held in place with " +
        "strips of lead.\n");
}
/*****************************************************************************/
public void init()
{
    ::init();
    add_action("cut_grass", "cut");
}

public string long_desc()
{
    string  time  = CLOCK->query_time_of_day(),
    desc = CAP(query_short()) + ". ";

    if (!(CLOCK->query_war()))
    {
        desc += describe_time(time);
    }
    else
    {
        desc += describe_war(time);
    }

    if (strlen(extraline))
        desc += extraline;

    if(lawn_cut == 0)
        desc += "The grass has not been cut recently and is long.";
    else if(lawn_cut == 1)
        desc += "The grass was recently cut.";
    else if(lawn_cut == -1) // don't show lawn status
        desc += "";

    if (functionp(vbfc_extra))
        desc += " " + vbfc_extra();
    return (desc + "\n");
}


int cut_grass(string lawn)
{
    if(lawn_cut == -1)
    {
        write("The " + lawn + " doesn't need to be cut here.\n");
        return 1;
    }
    else if(lawn_cut == 0)
    {
        switch(lawn)
        {
            case "grass":
            case "lawn":
            {
                write("You cut the " + lawn + ".\n");
                say(QCTNAME(TP) + " cuts the " + lawn + ".\n");
                lawn_status(1);
                return 1;
            }
            default:
            {
                write("Cut what, the lawn?\n");
                return 1;
            }
        }
    }
    else
    {
        write("The " + lawn + " was recently cut.\n");
        return 1;
    }
}
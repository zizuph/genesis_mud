// ROOM:  palace garden 5

    /* Calia Domain

    HISTORY

    [96-02-25] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN5.DOC].

    PURPOSE

    This is one of 14 garden rooms surrounding Calia palace.  See comments in
    Room 1 for layout details.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <macros.h>
#include "crdefs.h"
#include "cant_plant.c"

// FUNCTIONS

// Function:  init

/*

Purpose:  define commands available in this location (called by system when
room is entered)

Arguments:  none

Returns:  nothing

*/

void
init()

    {

    ::init();
    add_action(plant_seed, "plant");    /* function in "cant_plant.c" */

    }

// ROOM DEFINITION

void
create_room()

    {

    /*  VARIABLES  */

    /*  Each color in the "colors" array must have a corresponding entry in the
        ROSE ITEMS section.  */

    string *colors = ({"blue", "red", "purple"});
    string color = colors[random(sizeof(colors))];

    /*  One of the following remarks will be returned to the player if he does
        too much examining ("iron" item).  */

    string *remarks = ({
        "Don't you have anything more important to do?",
        "Iron is iron.",
        "Are you bored?",
        "You know wrought iron when you see it, and you see it here.",
        "It's not as pretty as the flowers.",
        "This is a garden - look at the flowers!",
        "You notice that it is made to be wielded in any hand... just kidding!"
        });

    /*  DESCRIPTION  */

    set_short("Calia Palace Gardens, north side");

    set_long("You are walking on a smooth gravel path " +
        "through a rose-covered trellis that stands " +
        "at the west entrance to the formal gardens.  The " + color + " " +
        "roses and plentiful green leaves cover the bulk of the trellis, " +
        "so you can only get a glimpse of the vines to the southwest " +
        "and the gardens to the east, but there are many gaps in " +
        "the canopy that allow narrow rays of sunlight to fall to the " +
        "ground in a variety of criss-crossing angles.\n");

    /*  EXITS  */

    add_exit(CROAD + "garden4", "southwest", 0);
    add_exit(CROAD + "garden6", "east", 0);

    /*  ITEMS  */

    add_item(({"garden", "gardens", "formal gardens"}),
        "You can't see much of the formal gardens from here, but " +
        "it's clear that they are broad and open and filled with a " +
        "variety of flowers.\n");

    add_item(({"vine", "vines"}),
        "From this vantage point you can tell that the vines are " +
        "covered with flowers, but you can't discern what kind.\n");

    add_item(({"path", "gravel", "ground", "gravel path",
        "smooth gravel path"}),
        "The gravel is composed of small blue and gray stones, " +
        "all smooth and shiny.  They make an agreeable crunching " +
        "sound as you walk on them.\n");

    add_item(({"bloom", "flower", "rose"}),
        "You inspect one of the roses carefully and cannot help but " +
        "admire the skill and effort that went into the cultivation " +
        "of such flawless flowers.\n");

    add_item(({"leaf", "leaves", "green leaf", "green leaves"}),
        "The leaves are glossy, healthy, and deep green, and there's " +
        "not a single trace of insect damage or decay.\n");

    add_item(({"trellis", "rose-covered trellis"}),
        "The roses grow so thickly that you can't see much of " +
        "the trellis itself, but a small part that's visible " +
        "through a gap in the rose canopy reveals that it is made " +
        "of sturdy wrought iron.\n");

    add_item(({"iron", "wrought iron"}),
        remarks[random(sizeof(remarks))] + "\n");

    add_item(({"palace", "gap", "gaps", "small gap", "small gaps"}),
        "You peek through one of the gaps in the rose canopy, and you " +
        "can just barely see an edge of the crystal palace.  It dawns " +
        "on you that the criss-crossing rays of light coming though " +
        "these gaps must be reflected from the angled facets of " +
        "the crystalline palace walls.\n");

    add_item(({"edge", "wall", "walls"}),
        "All you can see of the palace wall is a bit of an edge " +
        "sparkling in the sunlight.\n");

    add_item(({"rays", "narrow rays", "sunlight", "canopy", "rose canopy"}),
        "Rays of sunlight stream through the small gaps in the rose " +
        "canopy, and they reflect off the gravel to illuminate the " +
        "interior of the trellis.  You find it curious how they intersect " +
        "at a variety of angles.\n");

    /*  ROSE ITEMS  */

    switch (color)

        {

        case "blue":

            add_item(({"flowers", "roses", "blue flowers",
                "blue roses", "blooms"}),
                "These are Caliana roses, developed by the " +
                "Calian Landscaping Department.  They have large, " +
                "round blooms, and each of the many layers of petals " +
                "has a silvery satin sheen on the outside and a " +
                "rich sapphire blue on the inside.  When the " +
                "sunlight touches them, they reveal " +
                "a curious translucence - they seem to absorb the " +
                "light and radiate it from within as an eerie blue glow.\n");

            add_item(({"glow", "blue glow", "eerie blue glow"}),
                "It looks like a blue flame is burning deep within " +
                "the rose, but you know that it's really only " +
                "the sunlight being filtered through the petals.\n");

            add_item(({"petal", "petals", "layer", "layers",
                "layer of petals", "layers of petals", "color", "colors"}),
                "Each petal has a satin-like texture.  They're deep blue " +
                "on the inside and silvery on the outside.  When " +
                "light strikes the interior of the flower, it " +
                "reflects off the silvery surfaces and makes the " +
                "blue sufaces appear to glow.\n");

            break;

        case "red":

            add_item(({"flowers", "roses", "red flowers",
                "red roses", "blooms"}),
                "These are Victory roses, developed by the " +
                "Calian Landscaping Department.  They have long " +
                "petals that open into large trumpet-shaped blooms.  " +
                "Their intense ruby color is so uniform that one " +
                "layer of petals seems to dissolve into the next.\n");

            add_item(({"petal", "petals", "layer", "layers",
                "layer of petals", "layers of petals", "color", "colors"}),
                "The vivid ruby color is so perfectly consistent " +
                "that it's difficult to tell where one ends and " +
                "the next begins.  The petals are large and rounded and " +
                "have a sumptuous velvety texture.\n");

            break;

        case "purple":

            add_item(({"flowers", "roses", "purple flowers",
                "purple roses", "blooms"}),
                "These are rare Thalassian Royal roses, " +
                "preserved and cultivated by the " +
                "Calian Landscaping Department.  Once the pride of " +
                "gardeners on the Thalassian Islands, a few " +
                "samples were fortuitously brought to Calia for " +
                "study before the islands' demise.  The colors of " +
                "the petals are astonishing, exhibiting " +
                "every possible variation of purple shading - some " +
                "are uniform light or dark colors, while others " +
                "sport mottled, swirled, or streaked patterns.\n");

            add_item(({"petal", "petals", "layer", "layers",
                "layer of petals", "layers of petals", "color", "colors"}),
                "Even within a single flower the variation in " +
                "color is surprising.  One layer of petals may have " +
                "an even tone of medium purple, the next may be " +
                "an intense deep shade or nearly white, and " +
                "another may combine streaks of every possible " +
                "hue in between.\n");

            add_item(({"pattern", "patterns"}),
                "No two patterns look alike.\n");

            add_item(({"swirled pattern", "swirled patterns"}),
                "The swirled patterns remind you of the swirling " +
                "mist that rings Mt. Kyrus.\n");

            add_item(({"mottled pattern", "mottled patterns"}),
                "The mottled patterns look a little like maps.\n");

            add_item(({"streaked pattern", "streaked patterns"}),
                "The streaky patterns look like streaky bacon strips, " +
                "only purple.\n");

            break;

        default:

            add_item(({"flowers", "roses", "blooms"}),
                "These roses are artificial!  The Landscaping " +
                "Department must be on strike!  This should be reported " +
                "to the local wizards..\n");

        }

    }

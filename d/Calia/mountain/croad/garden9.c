// ROOM:  palace garden 9

    /* Calia Domain

    HISTORY

    [96-02-27] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN9.DOC].

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

    string *colors = ({"yellow", "pink", "white"});
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
        "at the east entrance to the formal gardens.  The " + color + " " +
        "roses and plentiful green leaves cover the bulk of the trellis, " +
        "so you can only get a glimpse of the vines to the southeast " +
        "and the gardens to the west, but there are many gaps in " +
        "the canopy that allow narrow rays of sunlight to fall to the " +
        "ground in a variety of criss-crossing angles.\n");

    /*  EXITS  */

    add_exit(CROAD + "garden8", "west", 0);
    add_exit(CROAD + "garden10", "southeast", 0);

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

        case "yellow":

            add_item(({"flowers", "roses", "yellow flowers",
                "yellow roses", "blooms"}),
                "These are Gelsey roses, a wild strain that was " +
                "cultivated for many years in gardens throughout " +
                "Calia.  The name comes from an ancient fairy tale, " +
                "but the tale has been forgotten - only the name " +
                "of the princess-heroine persists in modern " +
                "folklore.  The layers of petals are longer on the " +
                "outside than on the inside, ruffled, and tightly " +
                "packed.  When the rose is fully opened it looks like " +
                "a little yellow tutu.\n");

            add_item(({"petal", "petals", "layer", "layers",
                "layer of petals", "layers of petals", "color", "colors"}),
                "The petals are quite sheer and lacy, and they are a " +
                "bit deeper shade of yellow in the center than at " +
                "the tips.  The whole rose looks as if it " +
                "could be whisked away by the slightest breeze.\n");

            add_item(({"center", "tips", "tip"}),
                "It's somewhat difficult to determine where the center " +
                "ends and the tip begins - your vision is becoming a " +
                "bit fuzzy from examining the rose so closely.  When " +
                "you regain your focus, you confirm that the " +
                "petals are exquisite and delicate, and you delight " +
                "in the subtle fragrance that clings to your hair and " +
                "clothing as you withdraw.\n");

            break;

        case "pink":

            add_item(({"flowers", "roses", "pink flowers",
                "pink roses", "blooms"}),
                "These are Puff roses, a variety developed from wild " +
                "roses by the Calian Landscaping Department.  They " +
                "are quite unusual in that their many layers of petals " +
                "end in long hairlike structures, making the entire " +
                "flower look like a pink powderpuff.  The blooms are " +
                "small and almost perfectly spherical, and it's more " +
                "by scent than appearance that you identify them " +
                "as roses.\n");

            add_item(({"petal", "petals", "layer", "layers",
                "layer of petals", "layers of petals", "color", "colors"}),
                "It's difficult to identify individual layers of " +
                "petals because the hairlike structures merge " +
                "together into something resembling a fine pink fur " +
                "coat.  Although you would expect its sweet fragrance " +
                "to be rather attractive to bees, you wonder how a " +
                "bee could ever pollinate such a flower.\n");

            add_item(({"structures", "hairlike structures"}),
                "The hairlike structures hardly look like they come " +
                "from a plant.  If you didn't see them growing here, " +
                "you suspect they came from a pink fox or mink.\n");

            break;

        case "white":

            add_item(({"flowers", "roses", "white flowers",
                "white roses", "blooms"}),
                "These are Shimmer roses, a rare wild strain from " +
                "East Calia.  The petals are large and brilliant " +
                "white, and they open fully to form a " +
                "broad reflective surface.  When the light strikes " +
                "them, they seem to sparkle and shimmer like diamonds.\n");

            add_item(({"petal", "petals", "layer", "layers",
                "layer of petals", "layers of petals", "color", "colors",
                "surface", "reflective surface", "waxy surface"}),
                "The petals are arranged in only a few layers and have " +
                "a shiny, waxy surface.  You notice that each petal " +
                "is graced by a fine filigree of silvery veins.\n");

            add_item(({"filigree", "fine filigree", "silvery vein", "vein",
                "veins", "silvery veins"}),
                "Silvery veins cover the surface of each petal.  From " +
                "only a modest distance they are nearly imperceptible, " +
                "but they greatly enhance the reflectivity of " +
                "the white petals.  Up close, they look like " +
                "threads of miniature crystals.\n");

            add_item(({"crystal", "crystals", "miniature crystals",
                "threads"}),
                "Your eyes begin to hurt from focusing so intently on " +
                "the white petals, and you decide that there's nothing " +
                "to be gained from closer examination of the roses.\n");

            break;

        default:

            add_item(({"flowers", "roses", "blooms"}),
                "These roses are artificial!  The Landscaping " +
                "Department must be on strike!  This should be reported " +
                "to the local wizards.\n");

        }

    }

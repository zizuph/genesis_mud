// ROOM:  palace garden 8

    /* Calia Domain

    HISTORY

    [96-02-25] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN8.DOC].

    PURPOSE

    This is one of 14 garden rooms surrounding Calia palace. See comments in
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

    string *darks =
        ({"aquamarine", "maroon", "amethyst", "ruby", "turquoise", "carmine",
        "vermillion", "sapphire", "violet", "red"});

    string *brights =
        ({"cream", "yellow", "sky blue", "silver", "gold", "pink", "orange"});

    string *greenplants =
        ({"ferns", "junipers", "hollies", "evergreens", "spruces"});

    string *flowers =
        ({"mums", "tulips", "azaleas", "zinnias", "poppies", "peonies",
        "crocuses", "petunias", "geraniums", "rhododendrons", "snapdragons"});

    string *bunches =
        ({"diagonals", "diamonds", "triangles", "squares", "octagons",
        "zigzags", "swirls", "ovals", "whorls", "crescents", "spirals"});

    string *adjects =
        ({"dazzling","stunning","impressive","vivid","striking"});

    string dark1 = darks[(random(sizeof(darks)))];
    string dark2 = darks[(random(sizeof(darks)))];
    string bright1 = brights[(random(sizeof(brights)))];
    string bright2 = brights[(random(sizeof(brights)))];
    string flower1 = flowers[(random(sizeof(flowers)))];
    string flower2 = flowers[(random(sizeof(flowers)))];
    string flower3 = flowers[(random(sizeof(flowers)))];
    string flower4 = flowers[(random(sizeof(flowers)))];
    string greenplant = greenplants[(random(sizeof(greenplants)))];
    string bunch1 = bunches[(random(sizeof(bunches)))];
    string bunch2 = bunches[(random(sizeof(bunches)))];
    string adject = adjects[(random(sizeof(adjects)))];

    /*  DESCRIPTION  */

    set_short("Calia Palace Gardens, north side");

    set_long("This is the east end of the formal gardens, bounded " +
        "by the palace to the south and a stone wall to the north.  " +
        "You stand amidst vast flowerbeds arrayed " +
        "in " + adject + " " + bunch1 + " of " + dark1 + " " + flower1 +
         " edged with " + bright1 + " " + flower2 + ".  " +
        "The " + bunch1 + " are separated from each other by " +
        "low " + greenplant + " of varying breadth, " +
        "and the " + greenplant + " are themselves punctuated by " +
        "contrasting " + bunch2 + " of " + dark2 + " " + flower3 +
        " bordered by " + bright2 + " " + flower4 + ".  " +
        "The flowerbeds extend from the crystalline palace to " +
        "the stone wall and are planted so densely that you " +
        "can't walk anywhere but on the gravel path.  As you " +
        "stand admiring the stunning display, you feel a bit " +
        "intoxicated by the alluring fragrance that wafts " +
        "from the blooms.\n");

    /*  EXITS  */

    add_exit(CROAD + "garden7", "west", 0);
    add_exit(CROAD + "garden9", "east", 0);

    /*  ITEMS  */

    add_item(({"garden", "gardens", "formal garden",
        "formal gardens","display"}),
        "This area of the garden is open and airy, and the flowerbeds " +
        "are awash in color from the thousands of blooms.  The " +
        "stunning visual impression created by the massed blooms is " +
        "matched by the intoxicating effect of their perfume.\n");

    add_item(("stunning display"),
        "The Landscaping Department is happy to hear that " +
        "you find the display stunning.  Perhaps this is " +
        "a good time to try out the 'praise' command?\n");

    add_item(({"wall", "stone wall", "protective wall"}),
        "The wall is made of meticulously cut and fitted stones and " +
        "serves to protect the garden from the winds " +
        "that sometimes howl across the summit.\n");

    add_item(({"flower", "flowerbed", "flowers", "flowerbeds",
        dark1 + " " + flower1,
        bright1 + " " + flower2,
        dark2 + " " + flower3,
        bright2 + " " + flower4,
        flower1, flower2, flower3, flower4, "bloom", "blooms"}),
        "The overwhelming presentation of color and perfume " +
        "makes it difficult for you to focus on any one " +
        "particular flower.  You step back, breathe deeply, take " +
        "in the gardens as a whole, and marvel at the way " +
        "that the display shows off all of the plants " +
        "and flowers to their best advantage.\n");

    add_item(({"plants", greenplant, "low " + greenplant}),
        "Their deep green color contrasts dramatically with " +
        "the flowers, and you can detect a slightly spicy " +
        "aroma emanating from them that tempers the sweetness " +
        "of the floral fragrance.\n");

    add_item(({"path","gravel"}),
        "The gravel is composed of small blue and gray stones, " +
        "all smooth and shiny.  They make an agreeable crunching " +
        "sound as you walk on them.\n");

    add_item(({"palace", "colors", "color"}),
        "The faceted sides of the palace reflect a panoply of green, " +
        dark1 + ", " + bright1 + ", and a host of other colors from " +
        "the flowerbeds.   As you move, the colors dance and leap " +
        "in an extravagant kaleidoscopic parade.\n");

    }

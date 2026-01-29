// OBJECT:  gingerbread building

    /* Calia Domain

    HISTORY

    [2001-12-19] Created by Uhclem from
        [C:\CALIA\YULEWARE\GINGER\BUILDING.DOC].

    [2002-01-09] Uhclem changed this object so that is is not food; that is, it
        inherits std/object rather than std/food. This change makes the object
        inedible, which is good because it's far too valuable for quest
        purposes, and avoids the heap handling problems that arise when an
        object changes its descriptive text.

    PURPOSE

    A structure built in 16 stages by gingerbread men (and women) during the
    season of Yule.  It begins as a single scrap of raw building material
    (stage 0), and if the builders are left undisturbed, it will steadily
    progress from a simple hut (stage 1) all the way to a vast gingerbread
    empire (stage 16).  The final stage enables the player to reveal the
    gingerbread emperor and complete the gingerbread quest. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <language.h>
#include "defs.h"

// GLOBAL VARIABLES

int Building_Amount = 0;
int Building_Stage = 0;
string Building = "";

// FUNCTIONS

// Function:  break_building(object)

/*

Purpose:  break the building into edible pieces.  The player will receive both
gingerbread crumbs (scraps of various shape) and one gingerbread person; the
type of gingerbread person is determined by Building_Stage, queried by the
cookie object through the select_cookie function.

Arguments:  string specifying this building.

Returns:  1/0.

*/

int
break_building(string str)

{

    object tp = this_player();
    object to = this_object();
    object building;
    object cookie;
    object crumbs;
    object room;
    int cookie_selector;
    int i = 1;

    if (stringp(str) &&
        parse_command(str, all_inventory(tp) + all_inventory(environment(tp)),
        "%o", building))

    {

        if (building == to)

        {

            crumbs = clone_object(GINGERBREAD_CRUMBS);
            crumbs->set_heap_size(random(5) + Building_Stage + 2);
            crumbs->move(tp);

            room = environment();

            if (room == tp)

            {

                room = environment(tp);

            }

            tell_room(room, QCTNAME(tp) + " breaks " + LANG_ADDART(short()) +
                " into small pieces.\n", ({tp}));

            if (Building != "")

            {

                cookie_selector = Building_Stage + 16;
                cookie = clone_object(GINGERBREAD_COOKIE + cookie_selector);
                cookie->move(tp);

                tp->catch_msg("You break " + LANG_ADDART(short()) +
                    " into small pieces and discover " + cookie->short() +
                    " inside!\n");

            }

            else

            {

                tp->catch_msg("You break " + LANG_ADDART(short()) +
                    " into small pieces.\n");

            }

            remove_object();

            return 1;

        }

    }

    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;

}

// Function:  update_building()

/*

Purpose:  change building description when a new stage is completed.

Arguments:  none.

Returns:  nothing.

*/

void
update_building()

{

    string *buildings =  ({"simple hut", "rough shack", "modest bungalow",
        "rustic cabin", "tidy cottage", "sturdy lodge", "stately house",
        "spacious inn", "imposing monastery", "majestic cathedral",
        "quaint hamlet", "picturesque village", "intricate town",
        "elaborate city", "lavish kingdom", "vast empire"});

    /*
     *  For reference purposes, the occupants of the buildings are: 

     *   hut          hermit
     *   shack        hunter
     *   bungalow     whaler
     *   cabin        astrologer
     *   cottage      beekeeper
     *   lodge        rogue
     *   house        merchant
     *   inn          wench
     *   monastery    abbot
     *   cathedral    bishop
     *   hamlet       weaver
     *   village      watchman
     *   town         crier
     *   city         mayor
     *   kingdom      king
     *   empire       emperor    
     */

    string *long_descs =
        ({
        "a simple hut with just a little icing on top to" +
        " suggest a thatched roof",
        "a rough shack such as one might construct for a short stay" +
        " in a rugged area; some icing is layered on to give the" +
        " effect of raw timbers",
        "a modest seaside bungalow with some decorative icing" +
        " that looks like waves and foam",
        "a rustic cabin of sturdy but unsophisticated" +
        " construction, a dwelling of practical proportions with just" +
        " a bit of icing striped on to represent windows",
        "a tidy cottage that's both practical and pretty, edged" +
        " with icing that looks like flower-boxes and climbing ivy",
        "a sturdy lodge that might be found deep in the forest or" +
        " high on a mountain; some dark icing looks like" +
        " shutters closed to keep out prying eyes",
        "a stately house of generous proportions, crafted with" +
        " care for someone who can afford the best, with a bit" +
        " of icing applied to simulate brickwork and masonry",
        "a spacious inn that must enclose many rooms large and" +
        " small, some for the boisterous convivialty of the" +
        " crowd, others for more intimate pleasures, and icing is" +
        " painted on in various places to simulate windows," +
        " some brightly lit, some dark",
        "an imposing monastery that's as much fortress" +
        " as spiritual retreat, capped with icing that appears" +
        " to be the permanent snow cover of some mountain location",
        "a stately cathedral with icing that's painstakingly" +
        " applied to form miniature stained-glass windows",
        "a quaint hamlet of gingerbread houses, each crafted in" +
        " fine detail and trimmed with decorative icing" +
        " that couldn't possibly be the work of human hands," +
        " or elf, hobbit, goblin, dwarf, or gnome hands either",
        "a picturesque village with gingerbread" +
        " streets, gingerbread houses, gingerbread" +
        " fences, gingerbread shops, gingerbread spittoons..." +
        " well, maybe not gingerbread spittoons, but it does seem" +
        " to have just about everything a village needs," +
        " albeit in gingerbread form",
        "an intricate town that must have taken extraordinary" +
        " time and effort to construct, and tiny bits of" +
        " icing have been applied to resemble lamplights," +
        " flowers, and other decorative touches",
        "an elaborate city with buildings both large" +
        " and small, each constructed in a distinct" +
        " style with extraordinary care and skill and decorated" +
        " with icing to resemble marble, timber, brick, or tile," +
        " as if a college of gingerbread architects, masons," +
        " and carpenters had been hard at work here",
        "an extensive kingdom with cities, forests, fields," +
        " lakes, and rivers, each coated with icing in" +
        " appropriate colors in impossibly fine detail, as" +
        " if individual trees, bricks, leaves, and waves" +
        " had been crafted sparately and then seamlessly assembled",
        "a vast empire of fortresses, palaces," +
        " cities, towns, mountains, forests, fields, lakes," +
        " and rivers, all coated with icing that seems to" +
        " bring the various features to life; you get the" +
        " impression that if you waited long enough, you might" +
        " actually see the trees grow and the rivers" +
        " cascade through the mountains"
        });

    int n = Building_Stage - 1;
    string *adj_noun = explode(buildings[n], " ");

    Building = adj_noun[1];
    remove_name(query_name());
    remove_adj(query_adj());
    set_name("gingerbread");
    add_name(Building);
    add_name("_calia_gingerbread_building");
    set_adj("gingerbread");
    add_adj(adj_noun[0]);
    set_short(adj_noun[0] + " gingerbread " + adj_noun[1]);

    set_long("This is fresh gingerbread " +
        ({"baked in the form of ",
        "fashioned into ",
        "shaped like "})[random(3)] +
        long_descs[n] + ". Although the gingerbread looks tasty," +
        " the " + Building + " is too big to put in your mouth.\n");

    /*
     *  I'd like to save players from endlessly examining the building in hopes 
     *  of finding some secret panel or hidden treasure. Hopefully after they
     *  get the same response a few times they'll get the hint.    
     */

    add_item(({"icing", "multicolored icing",
        "thatched roof", "roof", "raw timbers",
        "timbers", "waves", "foam", "windows", "window",
        "flower boxes", "boxes", "flower box", "box",
        "climbing ivy", "ivy", "shutters", "shutter",
        "brickwork", "masonry", "snow cover", "snow",
        "stained-glass windows", "stained glass",
        "gingerbread streets", "gingerbread houses",
        "gingerbread fences", "gingerbread shops",
        "gingerbread street", "gingerbread house",
        "gingerbread fence", "gingerbread shop",
        "streets", "houses", "fences", "shops", "street",
        "house", "fence", "shop", "lamplights", "lamplight",
        "flowers", "flower", "buildings", "marble",
        "timber", "brick", "tile", "cities", "forests",
        "fields", "forest", "field", "lakes", "rivers",
        "lake", "river", "trees", "bricks", "leaves",
        "fortresses", "palaces", "cities", "towns", "mountains"}),
        "Every part of the " + Building + " is made of" +
        " gingerbread and icing; you detect nothing unusual about" +
        " it except the exceptional patience and skill of" +
        " whoever made it.\n");

    /*
     *  As construction progresses, the building gets bigger, heavier, and more 
     *  valuable.    
     */

    add_prop(OBJ_I_VOLUME, Building_Amount * 50);
    add_prop(OBJ_I_WEIGHT, Building_Amount * 10);
    add_prop(OBJ_I_VALUE, Building_Amount * 10);

}

// Function:  build_me(num)

/*

Purpose:  Build the building.

Arguments:  integer, the number to add to Building_Amount.

Returns:  string, current stage of development.

*/

string
build_me(int num)

{

    int i = 1;
    int previous_stage = Building_Stage;
    string previous_building = Building;
    Building_Stage = 0;
    Building_Amount += num;

    /*
     *  Since the minimum building amount is 2, the following loop is 
     *  guaranteed to execute at least once.    
     */

    while (i < Building_Amount && Building_Stage < 16)

    {

        i *= 2;
        Building_Stage += 1;

    }

    tell_room(environment(),
        "The gingerbread people " +
        ({"suddenly", "abruptly", "spontaneously"})[random(3)] +
        " " +
        ({"spring to life", "jump up", "rise"})[random(3)] +
        "," +
        ({
        " huddle together for a moment as if discussing something,",
        " look around carefully to see if anyone is watching,",
        ""  /*  this entry intentionally null  */
        })[random(3)] +
        " " +
        ({
        "work furiously",
        "labor swiftly but methodically",
        "rush about in a whirlwind of activity"
        })[random(3)] +
        " " +
        ({
        "for a few seconds",
        "for a short time",
        "until some vague, distant noise disturbs them"
        })[random(3)] +
        ", then " +
        ({
        "just as quickly",
        "simultaneously",
        "in an instant"
        })[random(3)] +
        " " +
        ({
        "they assemble in their original positions",
        "they lie back down",
        "they stop, find the places where they previously lay,"
        })[random(3)] +
        " and " +
        ({
        "become still again",
        "cease all motion",
        "return to an inanimate state"
        })[random(3)] +
        ".\n");

    if (Building_Stage != previous_stage)

    {

        update_building();

        if (previous_building == "")

        {

            tell_room(environment(), "You see that the gingerbread" +
                " cookies have constructed " + LANG_ADDART(short()) + "!\n");

        }

        else

        {

            tell_room(environment(), "You see that the" +
                " gingerbread cookies have expanded the" +
                " gingerbread " + previous_building +
                " into " + LANG_ADDART(short()) + "!\n");

        }

        return Building;

    }

    return 0;

}

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("You smell many spices, but the strongest scent is of ginger.\n");

}

// Function:  query_recover()

/*

Purpose:  this building is never recovered; if a player breaks the building and
gets the cookie inside, which is the part needed for the quest, the cookie is
covered by a special recovery routine in the gingerbread dispenser.

Arguments:  none.

Returns:  0.

*/

int
query_recover()

{

    return 0;

}

// Function:  init()

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();

    add_action(break_building, "break");
    add_action(break_building, "crush");
    add_action(break_building, "smash");

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_name("gingerbread");  /*  first word of description  */
    add_name("scrap");
    add_name("_calia_gingerbread_building");
    set_adj("gingerbread");  /*  so player can take 'gingerbread scrap'  */
    set_short("scrap of gingerbread");
    set_pshort("scraps of gingerbread");

    set_long("It's a large, irregularly-shaped scrap of" +
        " gingerbread. It looks tasty, but it's too big to" +
        " put in your mouth.\n");

    /*
     *  Since this object continuously transforms itself into different 
     *  buildings, we don't want it to merge with another, which would probably
     *  be in a different stage of construction, should more than one ever be
     *  in the same room.    
     */

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_M_NO_SELL, "Demand for secondhand gingerbread is," +
        " alas, at an all-time low; you would do better to trade" +
        " in a commodity that people actually wanted.\n");

    /*
     *  ITEMS    
     */

    /*
     *  "uid" settings required for cloning.    
     */

    setuid();
    seteuid(getuid());

}

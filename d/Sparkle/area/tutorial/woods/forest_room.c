/*
 *  /d/Sparkle/area/tutorial/woods/forest_room.c
 *
 *  This is the standard file for the rooms in Silverdell that are
 *  in the Sterling Woods.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#pragma no_clone
#include "../defs.h"

inherit SD_ROOM;
inherit LIB_DIR + "herbsearch";

/* Global Variables */
public string      Tree_Type   = "";  /* what trees grow here? */
public string      Location    = "";  /* what part of the woods ? */
public string      Extraline   = " "; /* added material for room desc */

/* Prototypes */
public void        create_forest_room();
nomask void        create_silverdell();
public void        plant_trees(string type);
public void        add_forest_herbs();
public void        set_forest_location(string arg);
public string      describe_short();
public string      describe_long();
public void        add_woods_items();
public string      exa_woods();
public string      exa_trees();
public string      exa_branches();
public int         climb_tree(string arg);
public void        init();
public void        clone_animal();

public void        set_extraline(string s) { Extraline += s; }


/*
 * Function name:        create_forest_room
 * Description  :        dummy file for inheriting rooms
 */
public void
create_forest_room()
{
} /* create_forest_room */


/*
 * Function name:        create_silverdell
 * Description  :        set up the room with area presets
 */
nomask void
create_silverdell()
{
    //By default, these rooms are instanced.
    instance_entrance = 0;

    create_forest_room();
    add_outdoor_items();

    setuid();
    seteuid(getuid());
} /* create_silverdell */


/*
 * Function name:        plant_trees
 * Description  :        set up the room with a certain type of trees
 * Arguments    :        string type - the type of tree
 */
public void
plant_trees(string type)
{
    Tree_Type = type;

    set_short(describe_short);
    set_long(describe_long);
    add_forest_herbs();
} /* plant_trees */


/*
 * Function name:        add_forest_herbs
 * Description  :        set up the herbs in the room based on the type
 *                       of tree that grows there.
 */
public void
add_forest_herbs()
{
    string  *herbs = ({ "" });

    switch(Tree_Type)
    {
        case "oak":
            herbs = ({ HERB_DIR + "gargleroot",
                       HERB_DIR + "gargleroot",
                       HERB_DIR + "leaf" });
            break;
        case "pine":
            herbs = ({ HERB_DIR + "clove",
                       HERB_DIR + "gargleroot",
                       HERB_DIR + "leaf" });
            break;
        case "silverwood":
            herbs = ({ HERB_DIR + "stiltberry",
                       HERB_DIR + "silverberry",
                       HERB_DIR + "leaf" });
            break;
        case "fir":
            herbs = ({ HERB_DIR + "gargleroot",
                       HERB_DIR + "stiltberry",
                       HERB_DIR + "leaf" });
            break;
        case "ash":
        default:
            herbs = ({ HERB_DIR + "clove",
                       HERB_DIR + "clove",
                       HERB_DIR + "clove" });
            break;
    }

    set_up_herbs(herbs, ({ "ground", "roots", "bushes" }), 3);
} /* add_forest_herbs */


/*
 * Function name:        set_forest_location
 * Description  :        set a location dependant description for the
 *                       variable Location.
 * Arguments    :        string arg - the location
 */
public void
set_forest_location(string arg)
{
    string txt;

    switch(arg)
    {
        case "n":
            Location = "near the northern edge of";
            break;
        case "ne":
            Location = "near the northeastern edge of";
            break;
        case "e":
            Location = "near the eastern edge of";
            break;
        case "se":
            Location = "near the southeastern edge of";
            break;
        case "s":
            Location = "near the southern edge of";
            break;
        case "sw":
            Location = "near the southwestern edge of";
            break;
        case "w":
            Location = "near the western edge of";
            break;
        case "nw":
            Location = "near the northwestern edge of";
            break;
        case "mid":
        default:
            Location = "deep within";
            break;
    }
} /* set_forest_location */


/*
 * Function name:        describe_short
 * Description  :        provide a tree and status-dependant short
 *                       description for the room.
 * Returns      :        string - the short description
 */
public string
describe_short()
{
    string  txt;
    string  condition = one_of_list( ({
                            "dark ",
                            "gloomy ",
                            "quiet ",
                            "lonely " }) );
    string  woods     = " the Sterling Woods";

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        condition = one_of_list( ({
            "serene ",
            "peaceful ",
            "beautiful ",
            "lush ", }) );
    }

    return "amidst a " + condition + "gathering of " + Tree_Type
      + " trees " + Location + woods;
} /* describe_short */


/*
 * Function name:        describe_long
 * Description  :        provide a tree and status-dependant long
 *                       description for the room
 */
public string
describe_long()
{
    string  txt = "You are standing " + short(this_player()) + ". ";

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        switch(random(2))
        {
            case 0:
                txt += "A fresh, resin-scented breeze blows through"
                  + " the trees, filling your lungs with the smell"
                  + " of the now-beautiful forest.";
                break;
            case 1:
                txt += "The branches of the trees sway gently to and"
                  + " fro above your head here, almost as if to signal"
                  + " their appreciation for your good deeds in the"
                  + " land that have restored them to health.";
                break;
            default:
            case 2:
                txt += "Pleasant sounds echo through the forest, a clear"
                  + " signal that your deeds have restored these lands"
                  + " to their rightful state.";
        }
    }
    else
    {
        switch(random(8))
        {
            case 0:
                txt += "A strange, ill-scented breeze blows through the"
                  + " forest, filling your lungs with smells you neither"
                  + " recognize nor welcome.";
                break;
            case 1:
                txt += "The branches of the trees sway ominously to and"
                  + " fro, creaking such that you feel your pulse begin"
                  + " to quicken. This is not a welcoming place.";
                break;
            case 2:
                txt += "Fearful sounds and the calls of wild animals"
                  + " echo through the forest. The woods do not seem to"
                  + " be at peace.";
                break;
            case 3:
                txt += "Bending slightly with the breeze, the trunks of"
                  + " the trees creak and moan all around you.";
                break;
            case 4:
                txt += "There is a sense of forboding in the darkness"
                  + " that seems to hang like fog in this forest.";
                break;
            case 5:
                txt += "Faint glimpses of light peer down from above,"
                  + " struggling to find their way through the thick"
                  + " matting of branches above.";
                break;
            case 6:
                txt += "A sudden silence has fallen over the forest. Just"
                  + " as the quiet begins to get to you, a sudden"
                  + " howl shatters the stillness.";
                break;
            case 7:
                txt += "The branches overhead move restlessly in the"
                  + " breeze, scratching against one another like"
                  + " nervous fingers in the dark.";
                break;
        }
    }

    return txt + Extraline + "\n\n";
} /* describe_long */



/*
 * Function name:        add_woods_items
 * Description  :        add add_items appropriate for the woods
 */
public void
add_woods_items()
{
    try_item( ({ "forest", "woods", "sterling forest", "sterling wood",
                 "sterling woods", "forest", "area", "here" }), exa_woods);
    try_item( ({ "tree", "trees", Tree_Type, Tree_Type + "s",
                 Tree_Type + " tree", Tree_Type + " trees" }), exa_trees);
    try_item( ({ "branch", "branches", "needles", "needle", "leaf",
                 "leaves", "branches above", "matting",
                 "thick matting" }), exa_branches);
} /* add_woods_items */


/*
 * Function name:        exa_woods
 * Description  :        provide a status and tree-dependant description
 *                       for an add_item
 * Returns      :        string - the description
 */
public string
exa_woods()
{
    string  txt;

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        txt = "The Sterling Woods are now a place of beauty and"
          + " serenity.";
    }
    else
    {
        txt = "The Sterling Woods are a rather ominous place. Strange"
          + " sounds echo from all directions.";
    }

    return txt + " " + capitalize(Tree_Type) + " trees surround"
      + " you here.\n";
} /* exa_woods */


/*
 * Function name:        exa_trees
 * Description  :        provide a status and tree-dependant description
 *                       for an add_item
 * Returns      :        string - the description
 */
public string
exa_trees()
{
    string  txt;

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return capitalize(Tree_Type) + " trees stand tall and proud here,"
          + " their branches swaying peacefully in the gentle breeze.\n";
    }
    else
    {
        return capitalize(Tree_Type) + " trees crowd around you, almost"
          + " seeming to bear down on you with their long branches.\n";
    }
} /* exa_trees */


/*
 * Function name:        exa_branches
 * Description  :        provide a status and tree-dependant description
 *                       for an add_item
 * Returns      :        string - the description
 */
public string
exa_branches()
{
    string  txt;

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "The branches of the " + Tree_Type + " trees frame the" 
          + " beautiful blue sky above your head.\n";
    }
    else
    {
        return "The " + Tree_Type + " branches above your head twist"
          + " and sway beneath the gloomy sky.\n";
    }
} /* exa_branches */


/*
 * Function name:        climb_tree
 * Description  :        allow players to try to climb the trees
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_tree(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [a] [" + Tree_Type + "] 'tree' / 'trees'"))
    {
        return 0; /* bad syntax */
    }

    notify_fail("There are no branches low enough to grasp.\n");
    return 0;
} /* climb_tree */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_tree, "climb");
} /* init */


/*
 * Function name:        clone_animal
 * Description  :        bring the right amount of creatures into
 *                       this room
 */
public void
clone_animal()
{
    int     i, n;
    object *animal = allocate(random(4));
    string  size;

    if (present("_tutorial_animal", this_object()))
    {
        return;
    }

    for (i = 0, n = sizeof(animal); i < n; i++)
    {
        if (!objectp(animal[i]))
        {
            size = one_of_list( ({ "small", "medium", "large" }) );

            animal[i] = clone_object(NPC_DIR + "forest_animal");
            animal[i]->config_animal(size);
            animal[i]->set_restrain_path(WOODS_DIR);
            animal[i]->arm_me();
            animal[i]->move_living("M", this_object());
            tell_room(environment(animal[i]),
                one_of_list( ({
                    "You hear a snap of twigs as a beast wanders in.\n",
                    "A forest creature arrives.\n",
                    "An animal slinks in silently.\n", }) ));
        }
    }
    return;
} /* clone_animal */


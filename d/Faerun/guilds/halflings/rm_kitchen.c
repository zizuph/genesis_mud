/*
 *  /d/Faerun/guilds/halflings/rm_kitchen.c
 *
 *  Here, halflings can take initiative with one of their
 *  most cultivated and time-honoured skills and traditions:
 *  Baking pies!
 *
 *  Created March 2016, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room";

#include "halflings.h"
#include <cmdparse.h>          /* for PARSE_COMMAND_*      */
#include <files.h>             /* for IS_HEAP_OBJECT, etc. */
#include <macros.h>            /* for QCTNAME, etc.        */
#include <stdproperties.h>     /* for OBJ_M_NO_DROP, etc.  */
#include <time.h>              /* for CONVTIME             */

/* Global Variables */
public object      Pie_Case;
public mixed      *Current_Baker = 0;
public mixed       Current_Maker = 0;
public int         Might_Burn = 10;
public int         Pie_Alarm = 0;
public object      Current_Fruit;
public object      Current_Dough;
public object      Current_Formula;
public string     *Spices = ({ "salt",
                               "sugar",
                               "pepper",
                               "nutmeg",
                               "cloves",
                               "allspice",
                               "cinnamon",
                               "paprika",
                               "allspice",
                               "ginger", 
                               "vanilla", });


/* prototypes */
public void        create_room();
public string      exa_oven();
public string      exa_smoke();
public void        init();
public int         bake_pie(string arg);
public int         baking_fumble(object who, string fruit_choice,
                                 mixed fruit = 0);
public void        remove_ingredients(object fruit, object dough,
                                      object formula);
public void        pie_step_one(object who, string fruit_choice,
                                object fruit);
public void        pie_step_two(object who, string fruit_choice,
                                object fruit);
public void        pie_step_three(object who, string fruit_choice,
                                  object fruit);
public void        pie_step_four(object who, string fruit_choice,
                                 object fruit);
public void        finish_baking();
public void        notify_finished();
public void        notify_burning();
public int         get_kitchen_objects(string arg);

public mixed       query_baker() { return Current_Baker; }
public mixed       query_status() { return get_alarm(Pie_Alarm); }


/* Definitions */
#define            NEARBY_ROOM       (HALFGLD_DIR + "rm_join")
#define            BAKING_TIME       300.0   /* 5 minutes */
#define            DOUGH_NAME        "_halfling_baking_dough"
#define            FORMULA_NAME      "_halfling_baking_formula"
#define            ACCEPTABLE_FRUITS ({ "apple",             \
                                        "apricot",           \
                                        "avocado",           \
                                        "banana",            \
                                        "berry",             \
                                        "blackberry",        \
                                        "blackcurrant",      \
                                        "blueberry",         \
                                        "boysenberry",       \
                                        "cantaloupe",        \
                                        "currant",           \
                                        "cherry",            \
                                        "cherimoya",         \
                                        "cloudberry",        \
                                        "coconut",           \
                                        "cranberry",         \
                                        "damson",            \
                                        "date",              \
                                        "dragonfruit",       \
                                        "durian",            \
                                        "elderberry",        \
                                        "feijoa",            \
                                        "fig",               \
                                        "goji berry",        \
                                        "gooseberry",        \
                                        "grape",             \
                                        "grapes",            \
                                        "raisin",            \
                                        "raisins",           \
                                        "grapefruit",        \
                                        "guava",             \
                                        "huckleberry",       \
                                        "huckleberries",     \
                                        "jabuticaba",        \
                                        "jackfruit",         \
                                        "jambul",            \
                                        "jujube",            \
                                        "juniper berry",     \
                                        "kiwi fruit",        \
                                        "kumquat",           \
                                        "lemon",             \
                                        "lime",              \
                                        "loquat",            \
                                        "lychee",            \
                                        "mango",             \
                                        "marion berry",      \
                                        "melon",             \
                                        "cantaloupe",        \
                                        "honeydew",          \
                                        "watermelon",        \
                                        "melon",             \
                                        "miracle fruit",     \
                                        "mulberry",          \
                                        "nectarine",         \
                                        "olive",             \
                                        "orange",            \
                                        "blood orange",      \
                                        "clementine",        \
                                        "mandarine",         \
                                        "tangerine",         \
                                        "papaya",            \
                                        "passionfruit",      \
                                        "peach",             \
                                        "pear",              \
                                        "persimmon",         \
                                        "physalis",          \
                                        "plum",              \
                                        "prune",             \
                                        "pineapple",         \
                                        "pomegranate",       \
                                        "pomelo",            \
                                        "purple mangosteen", \
                                        "quince",            \
                                        "raspberry",         \
                                        "salmonberry",       \
                                        "rambutan",          \
                                        "redcurrant",        \
                                        "salal berry",       \
                                        "salak",             \
                                        "satsuma",           \
                                        "star fruit",        \
                                        "strawberry",        \
                                        "tamarillo",         \
                                        "tamarind",          \
                                        "ugli fruit",        \
                                     })



/*
 * Function name:        create_room
 * Description  :        the constructor for the area
 */
public void
create_room()
{
    set_short("a well-stocked kitchen");

    set_long("Here is a truly marvelous sight - the kitchen"
      + " of a guild of halflings, stocked full of all one"
      + " could need. A huge oven dominates the center"
      + " of the far wall, resting beside an ice-chest."
      + " The wall to the left has a large assortment of"
      + " spices and baking vessels resting on some"
      + " shelves, and to the right is a long table where"
      + " baked goods can cool.\n");

    add_item( ({ "here", "kitchen", "room", "area",
                 "well-stocked kitchen" }),
        "A halfling could spend all day in a place like"
      + " this!\n");
    add_item( ({ "glass" }),
        "The glass of the case is smudged with numerous"
      + " fingerprints.\n");
    add_item( ({ "finger prints", "prints", "print", "smudge",
                 "finger print", "fingerprint", "fingerprints" }),
        "So many bakers, so little pie ...\n");
    add_item( ({ "baker", "bakers" }),
        "Well, you could be one if you wanted to. Just start"
      + " baking a pie!\n");
    add_item( ({ "guild", "guild of halflings",
                 "halfling guild" }),
        "No halfling guild would be complete without a"
      + " proper kitchen. This one does not disappoint.\n");
    add_item( ({ "proper kitchen" }),
        "Even better than the one mum had when you were"
      + " just a wee sprout!\n");
    add_item( ({ "mum", "mom", "mother", "tools", "tool",
                 "eating", "delicious eating" }),
        "Blinking, you realize your mind wandered a bit"
      + " there, and you focus back on matters at hand.\n");
    add_item( ({ "oven", "huge oven" }), exa_oven);
    add_item( ({ "far wall" }),
        "The far wall houses an oven and an ice-chest.\n");
    add_item( ({ "wall", "walls" }),
        "Which wall are you interested in?\n");
    add_item( ({ "ice-chest", "ice chest", "chest" }),
        "Peeking into the ice-chest, you see a stack of"
      + " prepped and wrapped pie-dough squares, chilling"
      + " until someone with an itch for baking feels like"
      + " taking one to use.\n");
    add_item( ({ "stack", "dough", "pie-dough", "pie dough",
                 "square", "pie-dough square", "squares",
                 "pie-dough squares", "pie dough squares",
                 "pie square", "pie squares",
                 "dough square", "dough squares", }),
        "They look just perfect! Maybe you want to take one"
      + " so you can bake a pie? Sure you do!\n");
    add_item( ({ "wall to the left", "left wall" }),
        "Shelves along the left wall house various spices"
      + " and baking vessels. It is a proud display.\n");
    add_item( ({ "display", "proud display" }),
        "Arranging things properly in a kitchen is an art"
      + " few take the time to perfect. Fortunately,"
      + " halflings like yourself take pride in such things"
      + " as a matter of course.\n");
    add_item( ({ "shelf", "shelves" }),
        "These are very handsome shelves, displaying many"
      + " spices, some secret formula, and lots of baking vessels.\n");
    add_item( ({ "formula", "secret formula" }),
        "That formula is the secret to baking a good pie. It would"
      + " be suicide to try to make one without it!\n");
    add_item( ({ "handsome shelf", "handsome shelves" }),
        "What could be more handsome than an assortment of"
      + " tools that lead to delicious eating?\n");
    add_item( ({ "spices", "spice", "various spices" }),
        "Let's see, there is salt, sugar, pepper, nutmeg,"
      + " cloves, allspice, cinnamon, paprika, and"
      + " vanilla.\n");
    add_item( ({ "sugar" }),
        "That's probably your favorite one!!!\n");
    add_item( ({ "salt" }),
        "Nothing ruins a good dish more than lack of good"
      + " seasoning.\n");
    add_item( ({ "pepper" }),
        "Useful for more than just making your cat sneeze!\n");
    add_item( ({ "nutmeg" }),
        "Oh golly, what doesn't taste better with a scratch"
      + " of nutmet dusted on it?\n");
    add_item( ({ "clove", "cloves" }),
        "Hmmm ... gotta be careful with those. A little"
      + " goes a long way, but what a rich aroma.\n");
    add_item( ({ "allspice" }),
        "Similar to the nutmeg, but with more going on.\n");
    add_item( ({ "cinnamon" }),
        "One word. Yummy.\n");
    add_item( ({ "paprika" }),
        "Just add a bit to a chocolate dish for that extra"
      + " little zing!\n");
    add_item( ({ "vanilla" }),
        "It's got that something extra, you know. Hard to"
      + " really taste - but what a smell!\n");
    add_item( ({ "vessel", "vessels", "baking vessel",
                 "baking vessels" }),
        "Well, really it is just a bunch of pie dishes."
      + " You don't imagine anything else gets made in here"
      + " do you?\n");
    add_item( ({ "dish", "pie dish", "dishes", "pie dishes" }),
        "If you haven't already gotten one, these are the"
      + " start of a journey toward the licking of one's"
      + " lips.\n");
    add_item( ({ "table", "long table", "cooling table",
                 "goods", "baked goods", "pie", "pies" }),
        "The table contains a long glass pie case where one could"
      + " put any pies that need to cool before their owners come"
      + " to claim them.\n");
    add_item( ({ "right", "right wall" }),
        "A long table sits before the right wall. It"
      + " looks like a VERY important table!\n");
    add_item( ({ "important table", "very important table",
                 "VERY important table" }),
        "Important, yes! Well ... potentially. Probably."
      + " DEFINITELY.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is scuffed and looks like a place of"
      + " constant activity.\n");
    add_item( ({ "activity", "constant activity" }),
        "This place is usually quite active. Don't break"
      + " that tradition!\n");
    add_item( ({ "up", "roof", "ceiling" }),
        "It isn't very high. I mean, this IS a halfling"
      + " guild.\n");
    add_item( ({ "smoke", "dark smoke", "billowing smoke",
                 "billowing dark smoke", "dark billowing smoke",
                 "billows", "billows of smoke" }), exa_smoke);
    add_item( ({ "door", "oven door" }),
        "The oven door is very sturdy looking.\n");

    add_cmd_item( ({ "oven" }),
                  ({ "open" }),
        "Halflings learn from a young age not to open ovens unless"
      + " there is a good reason to do so! If a pie has finished"
      + " baking, of course, you could simply get it from the"
      + " oven.\n");

//    add_exit("rm_join", "west");

    Pie_Case = clone_object("/std/container");

    Pie_Case->set_name("case");
    Pie_Case->add_name(PIE_CASE);
    Pie_Case->add_adj( ({ "long", "glass", "pie", }) );
    Pie_Case->set_short("long glass pie case");
    Pie_Case->set_no_show_composite(1);
    Pie_Case->set_long("This pie case is made of glass, and is quite"
      + " large, capable of holding many pies until the responsible"
      + " bakers might show up to retrieve their creations.\n");
    Pie_Case->add_prop(OBJ_M_NO_GET, "The pie case is far too large"
      + " to take. You might be able to get a pie from it, however.\n");
    Pie_Case->add_prop(CONT_I_WEIGHT, 10000);
    Pie_Case->add_prop(CONT_I_MAX_WEIGHT, 50000);
    Pie_Case->add_prop(CONT_I_VOLUME, 10000);
    Pie_Case->add_prop(CONT_I_MAX_VOLUME, 50000);

    Pie_Case->move(this_object());
} /* create_room */


/*
 * Function name:        exa_oven
 * Description  :        Allow the player to get a state-
 *                       dependent description of the oven.
 * Returns      :        string - the description
 */
public string
exa_oven()
{
    int    my_pie;

    if (sizeof(Current_Baker))
    {
        my_pie = (Current_Baker[0] == this_player());
    }

    string oven_txt = "This oven is just lovely. It is large, made"
      + " of strong metal, and looks just perfect for baking. ";

    if (!Current_Baker)
    {
        return oven_txt + "Perhaps you'd like to <bake> something in"
                        + " it?\n";
    }

    if (sizeof(get_alarm(Pie_Alarm)) > 1)
    {
        if (get_alarm(Pie_Alarm)[1] == "notify_burning")
        {
            if (my_pie)
            {
                oven_txt += "Noooooooooooooooo!!! You forgot to take"
                  + " your pie out in time, and now it has burned!"
                  + " What shame! What horror!! Well ............"
                  + " you should definitely take the poor thing"
                  + " out of the oven. Hopefully no one noticed"
                  + " this downright disgrace yet.";
            }
            else
            {
                oven_txt += "The oven is currently in use. TERRIBLE"
                  + " AND DISGRACEFUL USE!!! Someone has forgotten"
                  + " about their pie, and burned it! You should take"
                  + " the poor thing out of the oven.";
            }
        }
        else if (get_alarm(Pie_Alarm)[1] == "notify_finished")
        {
            if (my_pie)
            {
                oven_txt += "Ah, your pie has finished baking. You"
                  + " should take it out now before it burns. Just"
                  + " imagine how it will taste!!";
            }
            else
            {
                oven_txt += "The oven is currently in use. But you"
                  + " can smell that the pie inside is finished baking."
                  + " You should take it out of the oven so it doesn't"
                  + " burn. Yes, That would be the only decent thing to do!"
                  + " Afterwards you could start on making a new pie.";
            }
        }
        else
        {
            oven_txt += "The oven is currently in use. You can smell "
              + ((my_pie) ? "your " : "someone's ")
              + Current_Baker[1] + " pie on its way to perfection.";
        }
    }

    return oven_txt + "\n";
} /* exa_oven */


/*
 * Function name:        exa_smoke
 * Description  :        Allow the player to get a state-
 *                       dependent description of the oven.
 * Returns      :        string - the description
 */
public string
exa_smoke()
{
    string  smoke_txt = "You find no smoke.";

    if (sizeof(get_alarm(Pie_Alarm)) > 1)
    {
        if (get_alarm(Pie_Alarm)[1] == "notify_burning")
        {
            smoke_txt = "Yes! Smoke is just billowing out of the"
              + " oven. Oh, for the love of all that is holy, some"
              + " fool has gone and BURNED A PIE! Do something!!";
        }
    }

    return smoke_txt + "\n";
} /* exa_smoke */


/*
 * Function name:        init
 * Description  :        set up the commands for the player
 */
public void
init()
{
    ::init();

    add_action(bake_pie, "bake");
    add_action(bake_pie, "make");
    add_action(get_kitchen_objects, "get");
    add_action(get_kitchen_objects, "take");

} /* init */


/*
 * Function name:        bake_pie
 * Description  :        Allow guild members to bake a pie here.
 * Arguments    :        string arg -- what was typed following the verb
 * Returns      :        1 -- success, 0 -- failure
 */
public int
bake_pie(string arg)
{
    mixed  *objs;
    string *pietype = ACCEPTABLE_FRUITS;
    string  othertype;
    string  fruit_choice = "";
    object  fruit;
    int     heap_amount;
    object  dough;
    object  formula;

    if (!strlen(arg))
    {
        notify_fail("Bake what? ... ooo ... a pie??\n");
        return 0;
    }

    if (arg == "pie" || arg == "a pie")
    {
        notify_fail("Great idea! Using the oven, you can <bake [type]"
          + " pie> once you've got all the ingredients ready.\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
            "[a] [an] %w 'pie'", fruit_choice))
    {
        notify_fail("Huh? Were you trying to bake a pie, perhaps?\n");
        return 0;
    }

    fruit = PARSE_COMMAND_ONE(arg, all_inventory(this_player()),
                "[the] [a] [an] %i 'pie'");

    if (!objectp(fruit))
    {
        if (PARSE_COMMAND_SIZE)
        {
            notify_fail("Be specific! Just choose one ingredient"
              + " for the pie or it gets too confusing.\n");
            return 0;
        }

        if (IN_ARRAY(fruit_choice, ACCEPTABLE_FRUITS))
        {
            notify_fail("Sounds delicious! Er ... you'd probably need"
              + " to find at least one " + fruit_choice + " though."
              + " As nice as it sounds, you can't just wish a pie into"
              + " being!\n");
            return 0;
        }

        notify_fail("How can you try to make a pie out of"
          + " something you don't even have?\n");

        return 0;
    }

    if (!strlen(fruit_choice))
    {
        fruit_choice = "error-berry";
    }

    if (!fruit->id(fruit_choice) &&
         fruit->query_herb_name() != fruit_choice ||
        !IN_ARRAY(fruit_choice, ACCEPTABLE_FRUITS))
    {
        notify_fail("Err ... you'd need to find some sort of tasty"
          + " fruit or something. Baking a pie out of "
          + LANG_ADDART(fruit_choice) + " just isn't the way"
          + " things are done around here.\n");
        return 0;
    }

    /* We can't allow players to discard things they shouldn't be able
     * to!
     */
    if (fruit->query_auto_load() || fruit->query_prop(OBJ_M_NO_DROP))
    {
        notify_fail("No ... that item cannot leave you. You can't make"
          + " a pie out of it, sadly.\n");
        return 0;
    }

    else if (fruit->query_keep() && !fruit->query_unsellable())
    {
        notify_fail("That item is currently set to be kept. You"
          + " will first need to <unkeep> it.\n");
        return 0;
    }

    dough = present(DOUGH_NAME, this_player());

    if (!dough)
    {
        notify_fail("Oh yes, " + fruit_choice +  " pie is just"
          + " delicious. But you'd first need to get some dough"
          + " from the ice-chest.\n");
        return 0;
    }

    formula = present(FORMULA_NAME, this_player());

    if (!formula)
    {
        notify_fail("Sure, sure! But ... first get some of the"
          + " secret formula from the shelf. Can't make a proper"
          + " pie without the secret formula!\n");
        return 0;
    }

    if (sizeof(get_alarm(Pie_Alarm)) > 1)
    {
        if (get_alarm(Pie_Alarm)[1] == "notify_burning")
        {
            notify_fail("The oven is currently in use. TERRIBLE"
              + " AND DISGRACEFUL USE!!! Someone has forgotten"
              + " about their pie, and burned it! You should take"
              + " the poor thing out of the oven.\n");
            return 0;
        }
        else if (get_alarm(Pie_Alarm)[1] == "notify_finished")
        {
            notify_fail("The oven is currently in use. But you"
              + " can smell that the pie inside is finished baking. Maybe"
              + " you should take it out of the oven so it doesn't"
              + " burn. Yes, That would be the only decent thing to do!"
              + " Afterwards you could start on making a new pie.\n");
            return 0;
        }

        notify_fail("The oven is currently in use. You can smell"
          + " someone's " + Current_Baker[1] + " pie on its"
          + " way to perfection.\n");
        return 0;
    }

    if (Current_Maker == this_player())
    {
        notify_fail("You are already making a pie. One at a time!\n");
        return 0;
    }

    if (Current_Maker)
    {
        notify_fail("It looks as if someone else is just about to"
          + " put a pie in the oven.\n");
        return 0;
    }

    /* Looks like everything is in order. Let's start the baking
     * process.
     */

    if (Current_Maker)
    {
        if (Current_Maker == this_player())
        {
            notify_fail("You are already making a pie. One at a"
              + " time!\n");
            return 0;
        }

        notify_fail("Oh, it looks like " + QTNAME(Current_Maker)
          + " is just about to put a pie in the oven. Let's"
          + " let " + Current_Maker->query_objective()
          + " finish first.\n");
        return 0;
    }

    Current_Maker = this_player();

    write("You grab a pie-plate from the shelf and begin making"
      + " a pie.\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " grabs a pie-plate from the shelf and begins making a pie.\n");

    set_alarm(3.0, 0.0, &pie_step_one(this_player(), fruit_choice, fruit));

    return 1;
} /* bake_pie */


/*
 * Function name:        baking_fumble
 * Description  :        perform some important checks to
 *                       make sure the player hasn't messed up
 *                       something while the pie-making process
 *                       is taking place.
 * Arguments    :        object who - the player
 *                       string fruit_choice - the pie-type
 * Returns      :        int 1 - it got messed up
 *                       int 0 - no problem, keep baking
 */
public int
baking_fumble(object who, string fruit_choice, mixed fruit = 0)
{
    object  dough;
    object  formula;

    dough = present(DOUGH_NAME, this_player());
    formula = present(FORMULA_NAME, this_player());

    if (environment(who) != this_object())
    {
        who->catch_tell("What are you doing? You can't just walk"
          + " out of the kitchen while making a pie!! Well, I guess"
          + " you CAN, but why DID you? You'll have to start all"
          + " over now.\n");
        return 1;
    }

    if (!dough && calling_function() == "pie_step_one")
    {
        who->catch_tell("Hey, what happened? You've somehow"
          + " lost your dough! Blast it ... alright, let's just"
          + " get another and start over.\n");
        return 1;
    }

    if (!fruit && calling_function() == "pie_step_two")
    {
        who->catch_tell("What the ... ??! You no longer have"
          + " your " + fruit_choice + "! Looks like you'll"
          + " have to find one and start over.\n");
        return 1;
    }

    if (!formula && calling_function() == "pie_step_three")
    {
        who->catch_tell("Oh, hang it all! Where did the formula"
          + " go? Looks like you'll need to start over - you just"
          + " can't bake a proper pie without that.\n");
    }

    if (calling_function() == "pie_step_four")
    {
        if (Pie_Alarm)
        {
            who->catch_tell("Huh? Looks like somehow the oven became"
              + " occupied. How the heck did that happen? Oh well,"
              + " you clean up and decide to start over.\n");
            return 1;
        }
        else
        {
            remove_ingredients(fruit, dough, formula);
        }
    }

    return 0;
} /* baking_fumble */


/*
 * Function name:        remove_ingredients
 * Description  :        the pie has been made, so lets remove
 *                       all of the ingredients
 * Arguments    :        object fruit - the fruit ingredient
 *                       object dough - the dough ingredient
 *                       object formula - the formula ingredient
 */
public void
remove_ingredients(object fruit, object dough, object formula)
{
    int     heap_amount;

    dough->remove_object();
    formula->remove_object();

    /* If the fruit object in question is a heap,
     * we have to deal with that a bit differently.
     */
    if (IS_HEAP_OBJECT(fruit))
    {
        heap_amount = fruit->num_heap();

        if (heap_amount > 1)
        {
            fruit->set_heap_size(heap_amount - 1);
        }
        else
        {
            fruit->remove_split_heap();
        }
    }
    else
    {
        fruit->remove_object();
    }
} /* remove_ingredients */


/*
 * Function name:        pie_step_one
 * Description  :        Part of the process of making a pie.
 * Arguments    :        object who - the player 
 *                       string fruit_choice - the name of the fruit
 *                       object fruit - the fruit object
 */
public void
pie_step_one(object who, string fruit_choice, object fruit)
{
    if (baking_fumble(who, fruit_choice))
    {
        who->command("$facepalm");
        Current_Maker = 0;
        return;
    }

    who->catch_tell("You carefully lay your dough along the base of"
      + " the pie-plate.\n");
    tell_room(this_object(), QCTNAME(who) + " carefully lays some"
      + " dough along the base of a pie-plate.\n", who);

    set_alarm(5.0, 0.0, &pie_step_two(who, fruit_choice, fruit));

    return;
} /* pie_step_one */


/*
 * Function name:        pie_step_two
 * Description  :        Part of the process of making a pie.
 * Arguments    :        object who - the player 
 *                       string fruit_choice - the name of the fruit
 *                       object fruit - the fruit object
 */
public void
pie_step_two(object who, string fruit_choice, object fruit)
{
    if (baking_fumble(who, fruit_choice, fruit))
    {
        who->command("$facepalm");
        Current_Maker = 0;
        return;
    }

    who->catch_tell("You place the " + fruit_choice + " right"
      + " in the middle of the fresh dough base.\n");
    tell_room(this_object(), QCTNAME(who) + " places "
      + LANG_ADDART(fruit_choice) + " into the pie "
      + who->query_pronoun() + " is making.\n", who);

    set_alarm(2.0, 0.0, &pie_step_three(who, fruit_choice, fruit));

    return;
} /* pie_step_two */


/*
 * Function name:        pie_step_three
 * Description  :        Part of the process of making a pie.
 * Arguments    :        object who - the player 
 *                       string fruit_choice - the name of the fruit
 *                       object fruit - the fruit object
 */
public void
pie_step_three(object who, string fruit_choice, object fruit)
{
    if (baking_fumble(who, fruit_choice, fruit))
    {
        who->command("$facepalm");
        Current_Maker = 0;
        return;
    }

    who->catch_tell("You sprinkle some of the secret formula" 
      + " over the " + fruit_choice + ".\n");
    tell_room(this_object(), QCTNAME(who) + " sprinkles some"
      + " secret formula into the pie.\n", who);

    set_alarm(5.0, 0.0, &pie_step_four(who, fruit_choice, fruit));

    return;
} /* pie_step_three */


/*
 * Function name:        pie_step_four
 * Description  :        Part of the process of making a pie.
 * Arguments    :        object who - the player 
 *                       string fruit_choice - the name of the fruit
 *                       object fruit - the fruit object
 */
public void
pie_step_four(object who, string fruit_choice, object fruit)
{
    if (baking_fumble(who, fruit_choice, fruit))
    {
        who->command("$facepalm");
        Current_Maker = 0;
        return;
    }

    who->catch_tell("The " + fruit_choice + " seems to grow and"
      + " multiply as the secret formula takes effect, completely"
      + " filling the pie-plate! Casting a dash of "
      + one_of_list(Spices) + " in for good measure, you whisk"
      + " the pie into the oven and close the oven door.\n");
    tell_room(this_object(), QCTNAME(who) + " takes the"
      + " finished pie and places it in the oven, closing the"
      + " oven door afterwards.\n", who);

    Pie_Alarm = set_alarm(BAKING_TIME, 0.0, finish_baking);
    Current_Baker = ({ this_player(), fruit_choice });
    Current_Maker = 0;

    return;
} /* pie_step_four */


/*
 * Function name:        finish_baking
 * Description  :        A pie has finished baking, so lets start
 *                       the countdown till it will be burned.
 */
public void
finish_baking()
{
    tell_room(this_object(), "The unmistakably delicious smell of"
      + " baked " + Current_Baker[1] + " pie wafts from the oven."
      + " You could take the pie out now, as it has finished"
      + " baking.\n");

    remove_alarm(Pie_Alarm);
    Pie_Alarm = 0;

    if (!Pie_Alarm || !sizeof(get_alarm(Pie_Alarm)))
    {
        Pie_Alarm = set_alarm(30.0, 30.0, notify_finished);
    }

    Might_Burn = 10;

    return;
} /* finish_baking */


/*
 * Function name:        notify_finished
 * Description  :        A pie has finished baking, so lets start the
 *                       countdown (5 minutes) till it will be
 *                       burned.
 */
public void
notify_finished()
{
    string pie_txt = "The unmistakably delicious smell of"
      + " baked " + Current_Baker[1] + " pie wafts from the oven."
      + " You could take the pie out now, as it has finished"
      + " baking. ";

    switch (Might_Burn)
    {
        case 10:
            break;
        case 5:
            pie_txt += "In fact, you smell that the pie might be"
                     + " getting a bit over-done.";
            break;
        case 2:
            pie_txt += "In fact, you can smell that the pie is"
                     + " going to BURN if left in much longer!";
            break;
        case 0:
            tell_room(this_object(), "Oh no! A TERRIBLE smell comes"
              + " from the oven. The smell of ... a BURNING PIE!!!\n");

            remove_alarm(Pie_Alarm);
            Pie_Alarm = 0;

            if (!Pie_Alarm || !sizeof(get_alarm(Pie_Alarm)))
            {
                Pie_Alarm = set_alarm(10.0, 10.0, notify_burning);
            }

            return;
            break;
        default:
            Might_Burn--;
            return;
            break;
    }

    Might_Burn--;

    tell_room(this_object(), pie_txt + "\n");
} /* notify_finished */

            
/*
 * Function name:        notify_burning
 * Description  :        A pie has burned, so let's advertise that
 *                       disgraceful fact.
 */
public void
notify_burning()
{
    tell_room(this_object(), "Dark smoke billows from the oven.\n");
    tell_room(NEARBY_ROOM, "Dark smoke billows out of the kitchen.\n");
} /* notify_burning */


/*
 * Function name:        get_kitchen_objects
 * Description  :        let the player get things from the kitchen
 * Arguments    :        string arg - what was typed after the verb
 * Retrurns     :        1 - success, 0 - failure
 */
public int
get_kitchen_objects(string arg)
{
    object  kitchen_ob;
    int     my_pie;
    string  pie_type;

    if (!strlen(arg))
    {
        return 0; /* let the mudlib handle it. */
    }

    if (parse_command(arg, ({}),
        "[a] [an] [the] [some] [pie] [dough] [pie-dough] 'square'"
      + " / 'squares' [from] [the] [ice] [chest] [ice-chest]") ||
        parse_command(arg, ({}),
        "[a] [an] [the] [some] [pie] 'dough' [from] [the] [ice]"
      + " [chest] [ice-chest]"))
    {
        if (present(DOUGH_NAME, this_player()))
        {
            notify_fail("You've already gotten one. Let's not"
              + " be greedy, now!\n");
            return 0;
        }

        kitchen_ob = clone_object("/std/object");

        kitchen_ob->set_name(DOUGH_NAME);
        kitchen_ob->add_name( ({ "pie-dough", "dough", "square" }) );
        kitchen_ob->add_adj( ({ "pie-dough", "dough" }) );

        kitchen_ob->set_short("pie-dough square");
        kitchen_ob->set_long("This is a perfectly made square of"
          + " pie dough, ready to be used in baking your favorite"
          + " type of pie.\n");

        kitchen_ob->add_prop(OBJ_I_WEIGHT, 50);
        kitchen_ob->add_prop(OBJ_I_VOLUME, 80);

        write("You open the ice-chest and take a square of"
          + " pie-dough.\n");
        tell_room(this_object(), QCTNAME(this_player())
          + " opens the ice-chest and takes something out"
          + " of it.\n", this_player());

        if (kitchen_ob->move(this_player()))
        {
            tell_room(this_object(), "Whoa! Fumble!!\n");
            kitchen_ob->move(environment(this_player()));
        }

        return 1;
    }

    if (parse_command(arg, ({}),
        "[a] [an] [the] [some] [secret] 'formula'"
      + " [from] [the] [very] [handsome] [shelf] [shelves]"))
    {
        if (present(FORMULA_NAME, this_player()))
        {
            notify_fail("You've already gotten one. Let's not"
              + " be greedy, now!\n");
            return 0;
        }

        kitchen_ob = clone_object("/std/object");

        kitchen_ob->set_name(FORMULA_NAME);
        kitchen_ob->add_name( ({ "formula", "shaker" }) );
        kitchen_ob->add_adj( ({ "secret", "shaker of secret" }) );

        kitchen_ob->set_short("shaker of secret formula");
        kitchen_ob->set_long("This formula has been handed down"
          + " by countless generations of halflings. It makes the"
          + " perfect pie, every time!\n");

        kitchen_ob->add_prop(OBJ_I_WEIGHT, 50);
        kitchen_ob->add_prop(OBJ_I_VOLUME, 80);

        write("You grab the shaker of secret formula from the shelf.\n");
        tell_room(this_object(), QCTNAME(this_player())
          + " grabs something from the shelf.\n", this_player());

        if (kitchen_ob->move(this_player()))
        {
            tell_room(this_object(), "Whoa! Fumble!!\n");
            kitchen_ob->move(environment(this_player()));
        }

        return 1;
    }

    if (sizeof(Current_Baker))
    {
        my_pie = (Current_Baker[0] == this_player());
        pie_type = Current_Baker[1];
    }

    if (parse_command(arg, ({}),
        "[a] [an] [the] [my] [" + pie_type + "] 'pie'"
      + " [from] [out] [of] [the] [oven]"))
    {
        if (sizeof(get_alarm(Pie_Alarm)) > 1)
        {
            switch(get_alarm(Pie_Alarm)[1])
            {
                case "notify_burning":
                    kitchen_ob = clone_object("/std/object");
                    kitchen_ob->set_name("mound");
                    kitchen_ob->set_adj( ({ "charred", "black" }) );
                    kitchen_ob->set_short("charred black mound");
                    kitchen_ob->set_long("Ugh. This charred black"
                      + " mound is in roughly the shape of a pie."
                      + " But clearly, some highly irresponsible"
                      + " baker went and left it in the oven WAY"
                      + " too long, and this is the result. What a"
                      + " total disgrace ... \n");
                    kitchen_ob->add_prop(OBJ_I_WEIGHT, 200);
                    kitchen_ob->add_prop(OBJ_I_VOLUME, 300);

                    write("You open the oven, fanning away the"
                      + " billows of smoke, and take out all that"
                      + " remains of this most irresponsible baking"
                      + " venture - nothing more than a charred"
                      + " black mound! UNACCEPTABLE!!\n");
                    tell_room(this_object(), QCTNAME(this_player())
                      + " opens the oven and removes a charred"
                      + " black mound, fanning smoke away in the"
                      + " process.\n", this_player());

                    if (kitchen_ob->move(this_player()))
                    {
                        write("Oops, you dropped it.\n");
                        kitchen_ob->move(this_object());
                    }

                    break;
                case "notify_finished":
                    kitchen_ob = clone_object(GUILD_FOOD + "halfling_pie");
                    kitchen_ob->set_pie_type(pie_type);
                    kitchen_ob->set_baker(
                                    Current_Baker[0]->query_real_name());
                    kitchen_ob->setup_pie();

                    write("You open the oven and carefully remove"
                      + " the " + pie_type + " pie.\n");
                    tell_room(this_object(), QCTNAME(this_player())
                      + " opens the oven and carefully removes "
                      + LANG_ADDART(pie_type) + " pie.\n", this_player());

                    if (my_pie)
                    {
                        write("Oh, you have done well! It looks just"
                          + " perfect!\n");

                        if (kitchen_ob->move(this_player()))
                        {
                            write("Oops, you dropped it.\n");
                            kitchen_ob->move(this_object());
                        }
                    }
                    else
                    {
                        write("You quickly move the pie to the"
                          + " pie case to allow it to cool until"
                          + " the baker can return and claim it.\n");
                        tell_room(this_object(), QCTNAME(this_player())
                          + " places the pie into the pie case to allow"
                          + " it to cool until the owner can return"
                          + " and claim it.\n", this_player());
                        kitchen_ob->move(Pie_Case);
                    }

                    break;
                default: /* should never happen, but just in case */
                    notify_fail("The pie in this oven is still baking, and"
                      + " not ready to be taken out. Sniffing the"
                      + " aroma from the oven, you get a sense of the"
                      + " doneness of the pie. There are probably"
                      + " around "
                      + CONVTIME(ftoi(get_alarm(Pie_Alarm)[2]))
                      + " yet to wait.\n");
                    return 0;
                    break;
            } /* switch(get_alarm(Pie_Alarm)[1]) */

            remove_alarm(Pie_Alarm);
            Pie_Alarm = 0;

            return 1;
        } /* if (sizeof(get_alarm(Pie_Alarm)) > 1) */

        notify_fail("You open the oven and peek in, but the oven"
          + " is currently empty.\n");
    }

    return 0;
} /* get_kitchen_objects */

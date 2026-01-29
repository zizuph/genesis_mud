/*
 *  /d/Shire/guild/smiths/obj/tool_roll.c
 *
 *  This is the object members of the Smiths guild can use for the
 *  purposes of dismantleing, reconstructing, and fabricating items in
 *  the realms they become familiar with.
 * 
 *  Created August 2019, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../smiths.h"


/* Definitions */
#define              REPAIR_MASTER  (SMITHSDIR_OBJ + "repair_master")
#define              WARNING_PROP   "_obj_i_dismantle_warning"

/* Global Variables */
public mapping       Knowledge_Map = ([]);
public string        Fail_Msg = "";
public int           Power_Rating = 0;
public string        Obj_Category = "";


/* Prototypes */
public void          create_object();
public void          init();
public int           all_checks_passed(object who, object obj,
                                       string vb);
public int           do_dismantle(string arg);
public int           do_reconstruct(string arg);
public int           do_fabricate(string arg);
public int           show_knowledge(string arg);
public int           knowledge_points(object who, string obj,
                                      int increase = 0);
public mixed         forge_check(object who);
public string        knowledge_level(int k_number, int full = 0);


/*
 * Function name:        create_object
 * Description  :        the constructor
 */
public void
create_object()
{
    set_name("tool-roll");

    add_name( ({ "roll", "_smith_tool_roll" }) );
    add_adj( ({ "leather", "tool" }) );

    set_short("leather tool-roll");
    set_long("This tool roll is made of finely crafted leather, with"
      + " many pouches and folds which hold a smith's arsenal of"
      + " metal-working implements. Using it, you can <dismantle>"
      + " or <reconstruct> any type of armour or weapon for which"
      + " you have sufficient <knowledge> of it's make. If you are"
      + " a true master of any form, you might even be able to"
      + " <fabricate> it from scratch.\n");

    add_item( ({ "leather", "crafted leather", "finely-crafted leather",
                 "finely crafted leather" }),
        "The leather of your tool-roll is tanned a lovely shade of"
      + " dark brown, and has been made supple by much use.\n");
    add_item( ({ "pouch", "pouches", "fold", "folds" }),
        "Your tool-roll has been cleverly crafted to hold an"
      + " impressive number of tools.\n");
    add_item( ({ "tool", "tools", "arsenal", "implements",
                 "metal-working implements", "implement",
                 "metal-working implement", "smiths arsenal",
                 "smith's arsenal",
                 "smiths arsenal of metal-working implements",
                 "smith's arsenal of metal-working implements", }),
        "You have everything you need in here to work your"
      + " trade.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 3785);
    add_prop(OBJ_M_NO_DROP, "You must not rid yourself of your"
      + " precious tool-roll!\n");
    add_prop(OBJ_M_NO_SELL, "The tool-roll is more valuable to"
      + " you than gold!\n");

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        init
 * Description  :        add some actions for players
 */
public void
init()
{
    ::init();

    add_action("do_dismantle", "dismantle");
    add_action("do_reconstruct", "reconstruct");
    add_action("do_fabricate", "fabricate");
    add_action("show_knowledge", "knowledge");
} /* init */


/*
 * Function name:        all_checks_passed
 * Description  :        Many of the routines here need to check for
 *                       the same set of things, and establish the
 *                       same parameters. So, we'll go ahead and have
 *                       them available in this one routine that all
 *                       can use.
 * Arguments             object who - the player
 *                       object obj - the object
 *                       string vb  - the verb
 * Returns               1 - passed the test, 0 - failed the test
 */
public int
all_checks_passed(object who, object obj, string vb)
{
    if (!IS_WEAPON_OBJECT(obj) &&
        !IS_ARMOUR_OBJECT(obj))
    {
        Fail_Msg = "You can only " + vb + " armours or weapons.\n";
        return 0;
    }

    if (vb != "dismantle")
    {
        if (!forge_check(this_player()))
        {
            Fail_Msg = "You must be near a great forge of the Smith's"
              + " Guild in order to do this!\n";
            return 0;
        }
    }

    if (IS_ARMOUR_OBJECT(obj))
    {
        Power_Rating = obj->query_ac();
    }
    else
    {
        Power_Rating = (obj->query_hit() + obj->query_pen()) / 2;
    }

    if (obj->query_prop(MAGIC_AM_MAGIC))
    {
        if (obj->query_prop("_obj_s_imbue_short"))
        {
            Fail_Msg = "There are strange magicks about this item"
              + " that make it impossible for you to proceed with"
              + " any certainty of success.\n";

            return 0;
        }

        Obj_Category = MASTER_OB(obj);
    }
    else
    {
        switch (Power_Rating)
        {
            case 0..19:
                Obj_Category = "basic";
                break;
            case 20..39:
                Obj_Category = "quality";
                break;
            default:
                Obj_Category = "fine";
                break;
        }
    }

    return 1;
} /* all_checks_passed */


/*
 * Function name:        do_dismantle
 * Description  :        Allow players to try to dismantle a weapon
 *                       or armour to gain knowledge about its
 *                       construction and repair.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_dismantle(string arg)
{
    object   obj;
    int      k_points;

    if (!strlen(arg))
    {
        notify_fail("What do you wish to dismantle?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o", obj))
    {
        notify_fail("You don't seem to have one of those.\n");
        return 0;
    }

    if (!all_checks_passed(this_player(), obj, query_verb()))
    {
        notify_fail(Fail_Msg);
        return 0;
    }

    if (obj->query_prop(WARNING_PROP) != 
        this_player()->query_real_name())
    {
        notify_fail("Dismantling this item will destroy it. Are"
          + " you certain you wish to proceed? If so, you may"
          + " try once more.\n");

        obj->add_prop(WARNING_PROP, this_player()->query_real_name());
        return 0;
    }

    k_points = knowledge_points(this_player(), Obj_Category);

    if (k_points >= 100)
    {
        notify_fail("You have already achieved complete mastery of"
          + " this item. There is nothing to be gained by dismantling"
          + " it.\n");
        return 0;
    }

    k_points = knowledge_points(this_player(), Obj_Category, 1);

    write("You roll out your tools and begin working to dismantle"
      + " the " + obj->short() + ".\n\n");

    if (this_player()->query_wiz_level())
    {
        write("WIZINFO: Knowledge increased to " + k_points + "!\n\n");
    }

    if (k_points >= 100)
    {
        write("As you finish dismantling it, you feel a sense of"
          + " great accomplishment - you have reached complete"
          + " mastery with this item! You will have no further"
          + " need to dismantle it in the future to gain knowledge."
          + " You have learned all there is to know.\n");
        return 1;
    }

    write("Having completed the dismantling process, you feel"
      + " yourself " + knowledge_level(k_points, 1) + " of this"
      + " type of item.\n\n");

    write("The " + obj->short() + " has been destroyed.\n");

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " rolls out a leather tool-set and works carefully to"
      + " dismantle " + LANG_ADDART(obj->short()) + ", which"
      + " is soon destroyed in the process.\n", this_player());

/*
    obj->remove_object();
*/

    return 1;
} /* do_dismantle */


/*
 * Function name:        do_reconstruct
 * Description  :        Allow players to try to repair a broken
 *                       weapon or armour that they have sufficient
 *                       knowledge to succeed with.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_reconstruct(string arg)
{
    int      times_repaired = 0;
    object   obj;
    int      k_points;
    int      knowledge_needed = 10;

    if (!strlen(arg))
    {
        notify_fail("What do you wish to reconstruct?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o", obj))
    {
        notify_fail("You don't seem to have one of those.\n");
        return 0;
    }

    if (!all_checks_passed(this_player(), obj, query_verb()))
    {
        notify_fail(Fail_Msg);
        return 0;
    }

    if (!obj->query_prop(OBJ_I_BROKEN))
    {
        notify_fail("That doesn't seem to need any reconstruction.\n");
        return 0;
    }

    /* Here, we need to do some kind of mudlib check (yet to be
     * supported) for how many times a given item has been
     * repaired. I'll propose a basic process here.

    times_repaired = obj->query_prop(OBJ_I_REPAIRED);

    switch (times_repaired)
    {
        case 1:
            knowledge_needed = 20;
            break;
        case 2:
            knowledge_needed = 50;
            break;
        default;
            break;
    }
    */

    k_points = knowledge_points(this_player(), Obj_Category);

    if (k_points < knowledge_needed)
    {
        notify_fail("You would need at to posses "
          + knowledge_level(knowledge_needed) + " of this item before"
          + " you could reconstruct it in its current condition. "
          + capitalize(knowledge_level(k_points)) + " of its"
          + " properties you may have, but it is not enough. You"
          + " will need to <dismantle> this item for study to"
          + " advance your knowledge.\n");

        return 0;
    }

    write("You roll out your leather tool-set and, using your "
      + knowledge_level(k_points) + " of this item, reconstruct"
      + " the " + obj->short() + ". It looks good as new!\n");

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " rolls out " + this_player()->query_possessive() 
      + " leather tool-kit and works expertly to reconstruct "
      + LANG_ADDART(obj->short()) + " back to a servicable state.\n",
        this_player());

    /* Here we'll do some repair function which I am not yet sure of
     * from the mudlib ...

    obj->set_broken(0);
    times_repaired++;

    obj->add_prop(OBJ_I_REPAIRED, times_repaired);
     */

    return 1;
} /* do_reconstruct */


/*
 * Function name:        do_fabricate
 * Description  :        Allow players to try to fabricate a copy
 *                       of a weapon or armour that they have
 *                       completely mastered.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_fabricate(string arg)
{
} /* do_fabricate */


/*
 * Function name:        show_knowledge
 * Description  :        Give players a sense of their knowledge
 *                       level of a given armour or weapon, or
 *                       show them their general levels.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
show_knowledge(string arg)
{
} /* show_knowledge */


/*
 * Function name:        knowledge_points
 * Description  :        This routine returns the number of knowledge
 *                       points a player has for a given weapon or
 *                       armour. It can also add to that total if
 *                       specified.
 * Arguments    :        object who    - the player
 *                       string obj    - the weapon/armour index
 *                       int increase  - if true we increase the
 *                                       knowledge for this obj
 *                                       (default = false)
 * Returns      :        int - the number of knowledge points for
 *                             this object.
 */
public int
knowledge_points(object who, string obj, int increase = 0)
{
    int     k_points = REPAIR_MASTER->get_info(who, obj);

    if (increase)
    {
        k_points++;
        REPAIR_MASTER->set_info(who, obj, k_points);
    }

    return k_points;
} /* knowledge_points */


/*
 * Function name:        forge_check
 * Description  :        We require players to be at a forge
 *                       for certain things, so we check that here.
 * Arguments    :        object who - the player
 * Returns      :        obj - the forge object
 *                       0   - not at a forge
 */
public mixed
forge_check(object who)
{
    return present("_great_smith_forge", environment(who));
} /* forge_check */


/*
 * Function name:        knowledge_level
 * Description  :        Supply word descriptors for threshholds of
 *                       the knowledge of a given armour/weapon.
 * Arguments    :        int k_number - the knowledge value
 *                       int full - true if we want the full message
 *                                  and not just the level
                                    description (default = false)
 * Returns      :        string - the descriptor
 */
public string
knowledge_level(int k_number, int full = 0)
{
    string  k_increment = "";
    string  k_desc = "";

    switch (k_number % 10)
    {
        case 1:
            k_increment = "slightly more aware of your ";
            break;
        case 2:
            k_increment = "gaining familiarity with your ";
            break;
        case 3:
            k_increment = "slightly more confident with your ";
            break;
        case 4:
            k_increment = "somewhat more familiar with your ";
            break;
        case 5:
            k_increment = "gaining confidence in your ";
            break;
        case 6:
            k_increment = "more and more familiar with your ";
            break;
        case 7:
            k_increment = "fairly confident now in your ";
            break;
        case 8:
            k_increment = "extremely familiar with your ";
            break;
        case 9:
            k_increment = "about to surpass your ";
            break;
        default:
            k_increment = "just beginning your ";
            break;
    }

    switch (k_number)
    {
        case 0..9:
            k_desc = "rudimentary understanding";
            break;
        case 10..19:
            k_desc = "basic knowledge";
            break;
        case 20..29:
            k_desc = "reasonable understanding";
            break;
        case 30..39:
            k_desc = "fundamental knowledge";
            break;
        case 40..49:
            k_desc = "thorough understanding";
            break;
        case 50..59:
            k_desc = "low-level mastery";
            break;
        case 60..69:
            k_desc = "deep knowledge";
            break;
        case 70..79:
            k_desc = "artisan understanding";
            break;
        case 80..89:
            k_desc = "near-total knowledge";
            break;
        case 90..99:
            k_desc = "in-depth mastery";
            break;
        default:
            k_desc = "complete mastery";
            break;
    }

    if (!full)
    {
        return k_desc;
    }

    return k_increment + k_desc;
} /* knowledge_level */

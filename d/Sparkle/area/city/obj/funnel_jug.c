/*
 *  /d/Sparkle/area/city/obj/funnel_jug.c
 *
 *  This is a quest object used in the geyser quest given out at:
 *
 *      /d/Sparkle/area/city/rooms/inside/sparkle_pub.c
 *
 *  By the npc:
 *
 *      /d/Sparkle/area/city/npc/bartender.c
 *
 *  The code is inspired by:
 *
 *      /d/Gondor/common/obj/bucket.c
 *
 *  It allows players to collect water in an area, pour that water on a
 *  fire, if one is around, and also gather spray from the geyser that is
 *  near Sparkle for the quest.
 * 
 *  Created October 2018, by Cooper Sherry (Gorboth)
 */
inherit "/std/container";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../defs.h"


/* Global Variables */
public mixed         Filled = 0;   /* whatever this is filled with     */
public int           J_Number = 0; /* The number the bartender gave it */


/* Prototypes */
public void          create_container();
public void          init();
public int           do_fill(string arg);
public int           do_pour(string arg);
public void          geyser_fill(int eruption_state);
public string        describe();
public void          describe_contents(object for_obj, object *obarr);
public void          set_j_number(int i);
public int           query_filled();
public void          leave_env(object old, object dest);

public void          set_filled(mixed m)     { Filled = m; }
public int           query_j_number()   { return J_Number; }


/*
 * Function name:        create_container
 * Description  :        the constructor
 */
public void
create_container()
{
    set_name("funnel-jug");

    add_name( ({ "jug", PUB_QUEST_ITEM }) );
    add_adj( ({ "funnel" }) );

    set_short("funnel-jug");
    set_long("@@describe@@");

    add_item( ({ "funnel", "metal funnel" }),
        "The funnel is fixed firmly in place, making it easy to <fill>"
      + " the jug with anything that happens to fall toward its"
      + " mouth.\n");
    add_item( ({ "mouth", "mouth of the jug", "jug mouth" }),
        "The mouth of the funnel-jug is plugged by, well ..."
      + " a funnel!\n");

    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 4785);
    add_prop(CONT_I_VOLUME, 0);
    add_prop(CONT_I_MAX_VOLUME, 3785);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_M_NO_INS, "The mouth of the jug is too narrow for"
      + " that to fit.\n");

    setuid();
    seteuid(getuid());
} /* create_container */


/*
 * Function name:        init
 * Description  :        add some actions for players
 */
public void
init()
{
    ::init();

    add_action("do_fill", "catch");
    add_action("do_fill", "fill");
    add_action("do_pour", "pour");
    add_action("do_pour", "empty");
} /* init */


/*
 * Function name:        do_fill
 * Description  :        Allow players to fill this with water, if
 *                       some is in the room.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_fill(string arg)
{
    int     at_geyser = MASTER_OB(environment(this_player())) ==
                        "/d/Genesis/start/human/wild2/geyser";
    int     geyser_state = environment(
                             this_player())->query_geyser_eruption();
    string  gtxt;
    int     jug_state = query_filled();

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (arg == "jug" || arg == "funnel jug" || arg == "funnel-jug")
    {
        notify_fail("Fill the funnel-jug with what?\n", 10);
        return 0;
    }

    if (parse_command(arg, ({}),
                        "[the] [funnel] 'jug' / 'funnel-jug'"
                      + " [with] 'water' / 'geyser' / 'spray' / 'vapor'"
                      + " / 'vapour' [from]"
                      + " [the] [geyser]") ||
        parse_command(arg, ({}),
                        "[the] [hot] 'vapor' / 'vapour'"
                      + " / 'water'  / 'spray' [from] [the] [geyser] [in]"
                      + " [with] [the] [funnel] [funnel-jug] [jug]") ||
        arg == "water" || arg == "vapor" || arg == "geyser" ||
        arg == "vapour" || arg == "hot water")
    {
        if (at_geyser)
        {
            switch (geyser_state)
            {
                case 3..5:
                    gtxt = "Be patient! You just need to wait and"
                         + " let it happen!";
                    break;
                default:
                    gtxt = "If you're trying to catch some water from the"
                         + " geyser, you'll just need to wait until the"
                         + " thing erupts, and let the funnel do its work"
                         + " on its own. You could hold it, and wait, or"
                         + " leave it on the ground and come back for it"
                         + " later (hopefully no one would steal it!)";
                    break;
            }

            if (jug_state == 1)
            {
                gtxt = "You've already got what you need!";
            }

            write(gtxt + "\n");
            return 1;
        }

        if (environment(this_player())->query_prop(OBJ_I_CONTAIN_WATER))
        {
            if (strlen(Filled))
            {
                notify_fail("The funnel-jug is already " + Filled + ".\n");
                return 0;
            }

            write("You fill the funnel-jug with water.\n");
            tell_room(environment(this_player()), QCTNAME(this_player())
              + " fills " + this_player()->query_possessive()
              + " funnel-jug with water.\n", this_player());
            Filled = "filled up with water";
            return 1;
        }

        notify_fail("You do not see a water source that will"
          + " allow that here.\n");
        return 0;
    }

    notify_fail("What do you want to fill with what?\n");
    return 0;
} /* do_fill */


/*
 * Function name:        do_pour
 * Description  :        Allow players to empty the jug, if it is
 *                       already filled with something.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_pour(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[water] [liquid] [out] [of] [the] [funnel]"
      + " 'jug' / 'funnel-jug'"))
    {
        notify_fail("What are you trying to " + query_verb() + "?\n");
        return 0;
    }

    if (!Filled)
    {
        notify_fail("The funnel-jug is empty already.\n");
        return 0;
    }

    write("You tip the funnel-jug upside-down, letting all its contents"
      + " splash onto the ground. You check to make sure, and yes, it"
      + " is clearly no longer " + Filled + ".\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " empties " + this_player()->query_possessive() + " funnel-jug"
      + " onto the ground with a splash.\n",
        this_player());

    Filled = 0;
    return 1;
} /* do_pour */


/*
 * Function name:        geyser_fill
 * Description  :        Fill the jug up with the spray from the
 *                       geyser
 * Arguments    :        eruption_state - the state of the geyser
 *                                        eruption:
 *                          0-1: not erupting
 *                            2: rumbling
 *                            3: fumes emerging
 *                            4: eruption! roaring geyser
 *                            5: roar subsides a little
 */
public void
geyser_fill(int eruption_state)
{
    object  jug_area = environment(this_object());
    int     on_player = living(jug_area);

    if (on_player)
    {
        switch (eruption_state)
        {
            case 0..1:
                return;
                break;
            case 2:
                jug_area->catch_tell("\nAh, this is it! You finger"
                  + " your funnel-jug eagerly.\n");
                return;
                break;
            case 3:
                jug_area->catch_tell("\nYou hold your funnel-jug up"
                  + " trying to position it just right to catch as"
                  + " much spray from the geyser as possible.\n");
                return;
                break;
            case 4:
                jug_area->catch_tell("\nThis might be working! You"
                  + " keep the funnel-jug steady, trying to catch"
                  + " enough to get it full.\n");
                return;
                break;
            default:
                break;
        }

        if (query_filled())
        {
            jug_area->catch_tell("\nIt looks like your funnel-jug was"
              + " already too full to get any spray from this"
              + " eruption in it!\n");
            return;
        }

        jug_area->catch_tell("\nYou notice that your funnel-jug has"
          + " caught a large quantity of the spray, and is now"
          + " full!\n");

        Filled = "filled with strange-smelling bubbly liquid";
        return;
    }

    if (query_filled())
    {
        return;
    }

    tell_room(jug_area, "\nYou notice bubbly liquid flowing over the"
      + " brim of the funnel-jug on the ground, which has been"
      + " completely filled by the spray from the geyser.\n");

    Filled = "filled with strange-smelling bubbly liquid";
    return;
} /* geyser_fill */


/*
 * Function name:        describe
 * Description  :        Tell us details about the jug, very much
 *                       state-dependent.
 * Returns      :        string - the description
 */
public string
describe()
{
    string  j_txt;

    j_txt = "What looks to have once been a glass flotation device,"
          + " perhaps for a fishing net, has been fashioned into a"
          + " somewhat crude jug. A metal funnel has been pressed into"
          + " place in its mouth. ";

    if (J_Number)
    {
        j_txt += "The number \"" + J_Number + "\" has been scratched"
               + " near it's base.";
    }

    return j_txt + "\n";
} /* describe */


/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 *
 * We mask this so that the container shows things the way we
 * want, rather than the way the mudlib wants.
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell("  The funnel-jug is " + ((Filled) ? Filled :
        "empty") + ".\n");
} /* describe_contents */


/*
 * Function name:        set_j_number
 * Description  :        Assign a catalog number for this jug
 * Arguments    :        int i - the catalog number
 */
public void
set_j_number(int i)
{
    J_Number = i;

    add_item( ({ "number", "number " + J_Number, J_Number + "" }),
        ((J_Number) ? "The number \"" + J_Number + "\" has been"
      + " scratched into the glass of the jug. Perhaps this is some way to"
      + " keep track of many such items?\n" : "You see nothing there.\n"));
} /* set_j_number */


/*
 * Function name:        query_filled
 * Description  :        Provide info on what is in the jug.
 * Returns      :        int 0 - empty
 *                           1 - filled with geyser liquid
 *                           2 - filled with water
 */
public int
query_filled()
{
    switch(Filled)
    {
        case "filled up with water":
            return 2;
            break;
        case "filled with strange-smelling bubbly liquid":
            return 1;
            break;
        default:
            break;
    }

    return 0;
} /* query_filled */


/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 * 
 * We mask this to provide a bit of quest prompting.
 */
public void
leave_env(object old, object dest)
{
    int     at_geyser;

    if (objectp(dest))
    {
        at_geyser = MASTER_OB(dest) ==
            "/d/Genesis/start/human/wild2/geyser";
    }

    if (at_geyser && !query_filled())
    {
        old->catch_tell("Maybe you can just leave the funnel-jug on"
          + " the ground and come back for it later. Hopefully no"
          + " one would steal it! I guess it might be better than"
          + " waiting around for the geyser to erupt.\n");
    }

    ::leave_env(dest, old);
} /* leave_env */

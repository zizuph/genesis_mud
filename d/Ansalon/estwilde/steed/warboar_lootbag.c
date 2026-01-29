/*
Inherited by Estwilde war boars to allow lootbags to be
attached to them.

Based on:
Filename: /d/Shire/bree/rooms/town/stable/obj/bree_saddlebag.c
          /d/Terel/calathin/npc/terel_horse_saddlebag.c

Purpose:  Allows steed to wear a pack, and provides fill and
          empty commands for it.

Arman, October 2021.

*/

#include <composite.h>
#include <wa_types.h>
#include <adverbs.h>
#include <const.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

//Function prototypes

int do_fill(string arg);
int do_empty(string arg);
int do_strap(string arg);
string additional_longdesc();
int do_unstrap(string arg);
int do_open(string arg);
int do_close(string arg);
int boarloot(string arg);

/* The following functions are borrowed virtually identical from
   /d/Genesis/std/pack.c.
 */

int item_filter(object ob);
public int pack_fill_fail();
public int pack_empty_fail();
public void empty_me_pack();
public void fill_me_pack();
public void pack_fill_hook(object *moved_items);
public void pack_empty_hook(object *moved_items);

object saddlebag;

/*
 * Function:    : query_valid_person
 * Description  : Checks to see if person operating on pack is leader or driver of steed
 * Arguments    : object this_player()
 * Returns      : 1 if driver||leader == person messing with pack, 0 = wrong person
 */
query_valid_person()
{
    object leader, driver;

    if (driver = present("__rider_object", TP))
    {
        return 1;
    }

    if (leader = present("__leader_object", TP))
    {
        if (leader->query_leader() == TP)
            return 1;
    }

    return 0;
}

/*
 * Function:    : do_fill
 * Description  : parses the command for a player to fill the saddlebag.
 * Arguments    : "saddlebag on <steed>"
 * Returns      : true if the fill command succeeds.
 */
int
do_fill(string arg)
{

    object steed;
    string target;

    if (!present("boarbag"))
      return 0;

    notify_fail("Fill what on what?\n");

    if (!arg)
      return 0;

    parse_command(arg, environment(TP), "[the] %o 'on' %o",target , steed);

    if (steed != TO)
      return 0;

    fill_me_pack();
    return 1;
}

/*
 * Function:    : do_empty
 * Description  : parses the command that allows the player to empty
 *                the saddlebag.
 * Arguments    : "saddlebag on <steed>"
 * Returns      : true if the empty succeeded.
 */
int
do_empty(string arg)
{

    object steed;
    string target;

    if (!present("boarbag"))
      return 0;

    notify_fail("Empty what on what?\n");
    if (!arg)
        return 0;

    parse_command(arg, environment(TP), "[the] %s 'on' %o",target , steed);

    if (!query_valid_person())
    {
        notify_fail("You can't empty the boarbag because you're not " +
            "leading or riding the boar.\n");
        if (steed)
        {
            tell_room(E(TP), QCTNAME(TP) + " tried to empty the " +
              "bag on the " + steed->steed_short() + ".\n", TP);
        }
        return 0;
    }

    if (steed != TO)
        return 0;

    empty_me_pack();

    return 1;
}

/*
 * Function:    :  do_strap
 * Description  :  parses the command to strap the saddlebag to
 *                 the steed's back, also performs the move.
 * Arguments    :  "<saddlebag> on <steed>"
 * Returns      :  true if the strap command succeeded.
 */
int
do_strap(string arg)
{

    object steed;
    string junk;

    notify_fail("That boar already carries a boarbag!\n");
    if (present("boarbag"))
        return 0;

    notify_fail("Strap what?\n");

    if (!arg)
        return 0;

    if (!present("boarbag",TP))
        return 0;

    parse_command(arg, environment(TP), "[the] 'boarbag' 'on' %o", steed);
    parse_command(arg, all_inventory(TP), "[the] %o %s", saddlebag, junk);

    if (!present(saddlebag,TP))
    {
        saddlebag=0;
        return 0;
    }

    if (!steed)
    {
        saddlebag=0;
        return 0;
    }

    if (steed != TO)
    {
        saddlebag=0;
        return 0;
    }

    if (saddlebag->move(steed))
    {
        write ("The boarbag seems to be too heavy for the "+
            steed->steed_short()+" to carry.\n");
        saddlebag=0;
        return 0;
    }

    write ("You strap the boarbag to the " + steed->steed_short() + "'s back.\n");
    say (QCTNAME(TP) + " straps a boarbag to the back of the " +
       steed->steed_short() + ".\n");

    return 1;
}

/*
 * Function:     additional_longdesc
 * Description:  if this_object (the horse) has a saddlebag, show it
 */
string
additional_longdesc()
{
    if (!present("boarbag"))
    {
        return "";
    }

    return " " +capitalize(TO->query_pronoun())+ " has a boarbag strapped to "+
        TO->query_possessive()+" back.\n";
}

/*
 * Function     :  do_unstrap
 * Description  :  parses and performs a command to unstrap the saddlebag
 *                 on the steed and return it to the player.
 * Arguments    : "<saddlebag> on <steed>"
 * Returns      : true if the unstrap succeeded
 */
int
do_unstrap(string arg)
{

    object steed;
    string target;

    if (!present("boarbag"))
        return 0;

    notify_fail("Unstrap what on what?\n");
    if (!arg)
        return 0;

    parse_command(arg, environment(TP), "[the] %s 'on' %o",target , steed);

    if (!query_valid_person())
    {
        notify_fail("You failed to unstrap the boarbag because you're not " +
            "leading or riding the steed.\n");

        if (steed)
        {
            tell_room(E(TP), QCTNAME(TP) + " tried to unstrap the boarbag " +
                "from the " + steed->steed_short() + ".\n", TP);
        }

        return 0;
    }

    if (!steed)
        return 0;

    if (steed != TO)
        return 0;

    if (!saddlebag)
        return 0;

    if (saddlebag->move(TP))
    {
        write ("You untie the straps of the "+saddlebag->short()+
            " and it drops heavily to the ground.\n");

      say (QCTNAME(TP)+" unties the straps of the " +steed->steed_short()+
           "'s "+saddlebag->short()+", and it falls heavily to"+
           "the ground.\n");

      saddlebag->move(environment(TO));

      saddlebag=0;

      return 1;
    }
    else
    {

        write ("You take the "+saddlebag->short()+" from the "+
	     steed->steed_short()+"'s back.\n");

        say (QCTNAME(TP)+" takes a "+saddlebag->short()+ " from the back "+
	     "of the "+ steed->steed_short()+".\n");

        saddlebag=0;

        return 1;
    }
}


/*
 * Function     : do_open
 * Description  : if the saddlebag is on the steed, parses and
 *                performs an open command for it.
 * Arguments    : "<saddlebag> on <steed>"
 * Returns      : true if the open command succeeded.
 */
int
do_open(string arg)
{

    object steed;
    string target;

    if (!present("boarbag"))
        return 0;

    notify_fail("Open what from what?\n");

    if (!arg)
      return 0;

    parse_command(arg, environment(TP), "[the] %s 'on' %o",target , steed);

    if (!steed)
        return 0;

    if (steed != TO)
        return 0;

    if (!saddlebag)
        return 0;

    if (!saddlebag->query_prop(CONT_I_CLOSED))
    {
        write ("The boarbag is already open!\n");
        return 1;
    }

    saddlebag->add_prop(CONT_I_CLOSED, 0);

    write ("You open the boarbag on the "+
        steed->steed_short()+"'s back.\n");

    say (QCTNAME(TP)+" opens the boarbag on the "+
       steed->steed_short()+"'s back.\n");

    return 1;
}

/*
 * Function     : do_close
 * Description  : if the saddlebag is on the steed, parses and
 *                performs a close command for it.
 * Arguments    : "<saddlebag> on <steed>"
 * Returns      : true if the close command succeeded.
 */
int
do_close(string arg)
{

    object steed;
    string target;

    if (!present("boarbag"))
      return 0;

    notify_fail("Close what on what?\n");

    if (!arg)
      return 0;

    parse_command(arg, environment(TP), "[the] %s 'on' %o",target , steed);

    if (!steed)
        return 0;

    if (steed != TO)
        return 0;

    if (!saddlebag)
        return 0;

    if (saddlebag->query_prop(CONT_I_CLOSED))
    {
        write ("The "+saddlebag->short()+" is already closed!\n");
        return 1;
    }

    saddlebag->add_prop(CONT_I_CLOSED, 1);

    write ("You close the "+saddlebag->short()+" on the "+
         steed->steed_short()+"'s back.\n");

    say (QCTNAME(TP)+" closes the saddlebag on the "+
       steed->steed_short()+"'s back.\n");

    return 1;
}


/*
 * Function     : item_filter
 * Description: used to filter out certain objects when shifting stuff
 *              in or out of pack, like non-sellables, non-droppables,
 *              containers etc.
 * Argument:    the object to be tested
 * returns:     true if the object is to be filtered
 */
int
item_filter(object ob)
{

    return !((ob->query_prop(OBJ_M_NO_SELL)) ||
         (ob->query_prop(OBJ_M_NO_GIVE)) ||
         (ob->query_prop(OBJ_M_NO_DROP)) ||
         (!(ob->query_prop(OBJ_I_VALUE))) ||
         (ob->query_prop(CONT_I_IN)) || /* containers */
         (ob->query_worn()) ||
         (ob->query_wielded()) ||
         (ob->query_prop(LIVE_I_IS)) ||
         (ob->query_prop(OBJ_I_HAS_FIRE)) ||
         (ob->id("message")) ||
         (ob->id("note")) ||
         !CAN_SEE(this_player(), ob));
}

/*
 * Function     : pack_fill_fail
 *  Description:  during a fill command, tests if the pack is closed
 *  Arguments:    none
 *  Returns:      true if the saddlebag is closed.
 */

public int
pack_fill_fail()
{

    if (saddlebag->query_prop(CONT_I_CLOSED))
    {
        write("The " + saddlebag->short() + " is closed.\n");
        return 1;
    }

    return 0;
}

/*
 *     Function:    pack_empty_fail
 *     Description: during an empty command, tests if the pack is closed.
 *     Arguments:   none
 *     Returns:     true if the pack is closed.
 */
public int
pack_empty_fail()
{

    if (saddlebag->query_prop(CONT_I_CLOSED))
    {
        write("The " + saddlebag->short() + " is closed.\n");
        return 1;
    }

    return 0;
}

/*
 *     Function:     pack_fill_hook
 *     Description:  Gives messages to all concerned for a fill command
 *     Arguments:    array of objects that are moved
 *     Returns:      nothing
 */
public void
pack_fill_hook(object *moved_items)
{

    if (!sizeof(moved_items))
    {
        write("You didn't put anything in the " + saddlebag->short() + ".\n");
    }
    else
    {
        write("You store " + COMPOSITE_ALL_DEAD(moved_items) + " " +
            "in the " + saddlebag->short() + ".\n");
        say(QCTNAME(this_player()) + " stores " +
            COMPOSITE_ALL_DEAD(moved_items) + " " +
            "in the " + saddlebag->short() + ".\n");
    }
}

/*
 *     Function:    fill_me_pack
 *     Description: perform the actual pack filling
 *     Arguments:   none
 *     Returns:     none
 */
public void
fill_me_pack()
{
    object *conts, *moved;

    if (pack_fill_fail())
    {
        return;
    }

    conts = filter(all_inventory(this_player()), item_filter);
    moved = filter(conts, not @ &->move(saddlebag));

    pack_fill_hook(moved);
}

/*
 *   Function:     pack_empty_hook
 *   Description:  writes messages to all concerned on an empty command
 *   Arguments:    array of objects that are moved
 *   Returns:      nothing
 */
public void
pack_empty_hook(object *moved_items)
{

    if (!sizeof(moved_items))
    {
        write("You didn't retrieve anything from the "
          + saddlebag->short() + ".\n");
    }
    else
    {
        write("You retrieve " + COMPOSITE_ALL_DEAD(moved_items) +
            " from the " + saddlebag->short() + ".\n");

        say(QCTNAME(this_player()) + " retrieves " +
            COMPOSITE_ALL_DEAD(moved_items) + " from the " +
            saddlebag->short() + ".\n");
    }
}


/*
 *      Function:     empty_me_pack
 *      Description:  perform the actual empty
 *      Arguments:    none
 *      Returns:      none
 */
void
empty_me_pack()
{
     object *conts, *moved;

     if (pack_empty_fail())
     {
         return;
     }

     conts = filter(all_inventory(saddlebag), item_filter);
     moved = filter(conts, not @ &->move(this_player()));

     pack_empty_hook(moved);
}


int
boarloot(string arg)
{
    object steed = TP->query_steed();
    string target;
    object *conts;

    if (!present("boarbag"))
      return 0;

    if (!query_valid_person())
    {
        notify_fail("You can't check the boarbag because you're not " +
            "leading or riding the boar.\n");

        if (steed)
        {
            tell_room(E(TP), QCTNAME(TP) + " tried to check the " +
              "boarbag on the " + steed->steed_short() + ".\n", TP);
        }
        return 0;
    }

    conts = filter(all_inventory(saddlebag), item_filter);

    if (!sizeof(conts))
    {
        notify_fail("Your boarbag is empty.\n");
        return 0;
    }

    saddlebag->describe_contents(TP, conts);

    return 1;
}

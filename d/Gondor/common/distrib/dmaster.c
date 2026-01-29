/*
    /d/Gondor/common/distrib/dmaster.c

    The master room to control distribution of objects to
    any who enter Gondor.

    Commands supported here:
        * push (big red) button - Clones distributors into
          each Gondor entry room.
        * pull (the) lever - Removes each distributor that
          was cloned.
        * recall - Removes all items from the game. Be careful
          with this one. It removes all, not just the ones cloned
          by the distributor.
        * view -  See where each item is.

    Additional files:

    distrib.h - Changeable defines
    distrib.c - Actual distributor

    Coded by Gwyneth on April 20, 2000
*/

inherit "/std/room.c";

#include "/d/Gondor/defs.h"
#include "distrib.h"
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

/* Global variables */
object *dist_array = ({});
int turned_on = 0;

/* Prototypes */
int push(string str);
void distribute_start();
int pull(string str);
void distribute_halt();
int view();
int recall();
int distribute();

public void
create_room()
{
    set_long("Gears, levers, whistles, buttons, knobs, switches and " +
        "other various gnomish looking contraptions surround you. A " +
        "large sign on one wall indicates that this is the Master " +
        "Distribution Room. Further, it indicates that one may push " +
        "the big red button to start Distribution if brave enough " +
        "to do so, pull the lever to halt the Distribution, distribute " +
        "items to everyone in Gondor, view " +
        "the location of all items of the type being distributed, " +
        "and recall all items of the type being distributed in case " +
        "of something gone wrong.\nWords have been scrawled on the " +
        "ground with white chalk: Have fun!\n");
    set_short("Master Distribution Room");

    add_item(({"gear", "gears", "levers", "whistles", "whistle",
        "buttons", "knobs", "knob", "switches", "switch",
        "contraptions", "contraption"}), "Everywhere you look you see " +
        "gnomish contraptions. Two that catch your eye are a big red " +
        "button and a lever.\n");
    add_item(({"button", "big button", "red button", "big red button"}),
        "A label next to the big red button indicates that pushing this " +
        "button will start The Distribution. Please be sure you know " +
        "what you are doing before pushing this button.\n");
    add_item("lever", "A lable next to this lever indicates that pulling " +
        "the lever will halt The Distribution (especially in the case " +
        "that you actually didn't know what you were doing when pushing " +
        "The Button).\n");
    add_item("words", "They read: Have fun!\n");
    add_item("sign", "It reads: Master Distribution Room\n");

    add_cmd_item("sign", "read", "It reads: Master Distribution Room\n");
    add_cmd_item("words", "read", "They read: Have fun!\n");

    add_prop(ROOM_I_NO_CLEANUP, 1);
}

void
init()
{
    ::init();

    add_action(distribute, "distribute");
    add_action(push, "push");
    add_action(pull, "pull");
    add_action(recall, "recall");
    add_action(view, "view");

}

/* Function name: push
 * Description: Checks if argument is appropriate, and if startup is
       currently going on. Gives fail message if wrong arguments or
       if startup process is ongoing, otherwise gives distribution
       startup messages and calls the distribute_start() function.
 * Arguments: string str - big red button/big button/red button/button
 * Returns: 1 on success, 0 on failure
*/
int
push(string str)
{
    string name = TP->query_real_name();

    /* Only wizards of liege or above, or Gondor wizards
       can startup the distributors */
    if(WIZ_CHECK < WIZ_LORD &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
    {
        notify_fail("Only Gondorian wizards and wizards of rank lord " +
            "or above may startup the Distributor.\n");
        return 0;
    }

    /* No argument given */
    if(!strlen(str))
    {
        notify_fail("Push what? The big red button?\n");
        return 0;
    }

    /* Wrong arguments */
    if(!parse_command(lower_case(str)), ({}), "[the] [big] [red] 'button'"))
    {
        return 0;
    }

    if(turned_on)
    {
        write("Master Distributor already activated. Testing if " +
            "any distributors are missing.\n");
        distribute_start();
        return 1;
    }

    /* Alert the room that distribution is now active */
    write("You jam your finger down on the big red button.\n");
    say(QCTNAME(TP) + " jams " + POSSESSIVE(TP) + " finger down " +
        "on the big red button.\n");
    tell_room(TO, "A mechanical voice booms, 'Master " +
        "Distributor now activated!'\n");

    /* Call the distribute_start function */
    distribute_start();

    /* Keep track of on/off status */
    turned_on = 1;

    return 1;
}

void
distribute_start()
{
    object distributor;
    string *drooms = DROOMS;
    int i, size = sizeof(drooms);
    
    for(i = 0; i < size; i++)
    {
        drooms[i]->teleledningsanka();

        if(!present("distributor", find_object(drooms[i])))
        {
            distributor = clone_object(DISTRIBUTOR);
            distributor->move(drooms[i]);
            tell_room(TO, "A mechanical voice booms, '" + 
                file_name(find_object(drooms[i])) + ":\nBug " +
                "distributor added successfully.'\n");
            dist_array += ({ distributor });
        }
        else
        {
            tell_room(TO, "A mechanical voice booms, '" + 
                file_name(find_object(drooms[i])) + ":\nDidn't " +
                "load either from error or because one already " +
                "exists there.'\n");
        }
    }

    return;
}

int
pull(string str)
{
    /* Only wizards of liege or above, or Gondor wizards
       can shutdown the distributors */
    if(WIZ_CHECK < WIZ_LORD &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
    {
        NF("Only Gondorian wizards and wizards of rank lord or above " +
            "may shutdown the Distributor.\n");
        return 0;
    }

    /* No arguments */
    if(!strlen(str))
    {
        notify_fail("Pull what? The lever?\n");
        return 0;
    }

    /* Wrong arguments */
    if(!parse_command(lower_case(str), ({}), "[the] 'lever'"))
    {
        notify_fail("Pull what? The lever?\n");
        return 0;
    }

    /* It's turned off, but check for any extra distributors */
    if(!turned_on)
    {
        write("The Master Distributor is already turned off. " +
            "Testing for extra distributors.\n");
        distribute_halt();
        return 1;
    }

    /* Alert the room that the Master Distributor has been shutdown */
    write("With all of your strength, you pull the lever to " +
        "shutdown the Master Distributor.\n");
    say(QCTNAME(TP) + " pulls the lever to shutdown the Master " +
        "Distributor.\n");
    tell_room(environment(TP), "A mechanical voice booms, 'NO!!! Don't " +
        "pull that lev...' suddenly falling silent as the " +
        "Master Distributor is shutdown.\n");

    /* Call the distribution halting function */
    distribute_halt();


    /* Keep track of the on/off status */
    turned_on = 0;

    return 1;
}

void
distribute_halt()
{
    int i, size = sizeof(dist_array);

    /* Loop to find and remove each distributor in the array.
       If present, it will be removed and the room notified
       of such, otherwise, the room will be notified as to
       its absence. */
    for(i = 0; i < size; i++)
    {
        if(objectp(dist_array[i]))
        {
            dist_array[i]->remove_object();
            tell_room(TO, "A mechanical voice whispers in its last " +
                "breath, 'Distributor " + (i + 1) +
                " removed.'\n");
        }
        else
        {
            tell_room(TO, "A mechanical voice whispers in its last " +
                "breath, 'Distributor " + (i + 1) +
                " not found.'\n");
        }

    }

    /* Remove the elements of the array, as we've removed them all
       from the game. */
    if(size > 0)
    {
        dist_array = ({ });
    }
    else
    {
        tell_room(TO, "A mechanical voice whispers, 'No " +
            "distributors found.'\n");
    }

    return;
}

int
recall()
{
    object *oblist, owner;
    int i, size;

    /* Only wizards of liege or above, or Gondor wizards
       can recall the items. */
    if(WIZ_CHECK < WIZ_LORD &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
    {
        NF("Only Gondorian wizards and wizards of rank lord or above " +
            "may recall items.\n");
        return 0;
    }

    /* Find a list of objects cloned from the current master copy */
    oblist = object_clones(find_object(DOBJ));
    size = sizeof(oblist);

    if(size < 1)
    {
        tell_room(TO, "A mechanical voice booms, 'No items " +
            "found in the lands.'\n");
        return 1;
    }

    
    /* Loop to send message to the object's owner, notify the room
       of it's removal and remove each object.
    */
    for(i = 0; i < size; i++)
    {
        owner = environment(oblist[i]);
        if(interactive(owner))
        {
            tell_room(TO, "A mechanical voice booms, 'Removed " +
                "item from " + owner->query_name() +
                "'.\n");
            owner->catch_tell(DEPARTURE);
        }
        else
        {
            tell_room(TO, "A mechanical voice booms, 'Removed " +
                "item from " + file_name(owner) + ".'\n");
            tell_room(owner, ROOM_DEP);
        }

        oblist[i]->remove_object();
    }

    return 1;
}

int
view()
{
    int i, size;
    object *oblist, where;

    /* Only wizards of liege or above, or Gondor wizards
       can startup the distributors. */
    if(WIZ_CHECK < WIZ_LORD &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
    {
        NF("Only Gondorian wizards and wizards of rank lord or above " +
            "may view the items.\n");
        return 0;
    }

    oblist = object_clones(find_object(DOBJ));
    size = sizeof(oblist);

    if(size < 1)
    {
        tell_room(TO, "A mechanical voice booms, 'No items found " +
            "in the realms!'\n");
        return 1;
    }

    /* Loop to notify the room of the whereabouts of the the objects. */
    for(i = 0; i < size; i++)
    {
        where = environment(oblist[i]);

        if(interactive(where) && !where->query_npc())
        {
            tell_room(TO, "A mechanical voice booms, 'Item found " +
                "on player: " + where->query_name() + ".'\n");
        }
        else if(interactive(where))
        {
            tell_room(TO, "A mechanical voice booms, 'Item found " +
                "on living: " + file_name(where) + ".'\n");
        }
        else
        {
            tell_room(TO, "A mechanical voice booms, 'Item found " +
                "in: " + file_name(where) + ".'\n");
        }
    }
    
    return 1;
}

int
distribute()
{
    object *oblist;
    int i, size;

    /* Only wizards of liege or above, or Gondor wizards
       can distribute the items. */
    if(WIZ_CHECK < WIZ_LORD &&
       SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
    {
        NF("Only Gondorian wizards and wizards of rank lord or above " +
            "may distribute items.\n");
        return 0;
    }

    tell_room(TO, "A mechanical voice booms, 'Distributing " +
        "items to all in the Gondor " +
        "lands now!'\n");

    oblist = users();
    size = sizeof(oblist);

    /* Loop to distribute items to all players in Gondor */
    for(i = 0; i < size; i++)
    {
        if(environment(oblist[i])->query_domain() == "Gondor")
        {
            tell_room(TO, "A mechanical voice booms, 'Distributed item to " +
                oblist[i]->query_name() + "!'\n");
            clone_object(DOBJ)->move(oblist[i]);
        }
    }


    tell_room(TO, "A mechanical voice booms, 'Distribution " +
        "complete!'\n");

    return 1;
}


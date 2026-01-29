/*
 * Dol Guldur Post Office - /d/Gondor/rhovanion/dolguldur/post.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/room_tell";
inherit "/d/Genesis/lib/post";
inherit "/lib/trade";

#define NUM_RUNNERS  50
#define RUNNER_VALUE 288 
#define NF0(x)           { NF(x); return 0; }

static int         Fee = RUNNER_VALUE;
static int         runners = NUM_RUNNERS;
object             actor;

/*
 * Function name:        create_room()
 * Description  :        Creates the room
 */
void
create_gondor()
{
    set_short("Post office");
    set_long("You are inside a small shack that serves as the post office " +
        "here in Dol Guldur. There is a long wooden counter stretched " +
        "across the eastern wall, where a fat orc seems to be running " +
        "things. A cluster of smaller orcs serving as messengers are " +
        "also huddled behind the counter, often being hit by a " +
        "vicious backhand if they get in the way of the fat orc. Or " +
        "sometimes even if they don't. Several bright lanterns have been " +
        "hung on the walls here to ensure there is enough light for the " +
        "fat orc to work by, or even just so that people can read the " +
        "sign on the counter. An open doorway in the western wall leads " +
        "back out to the city.\n");
  
    add_item( ({"desk", "counter", "long counter", "wooden counter",
            "long wooden counter"}),
        "The fat orc who runs this post office is sitting behind this " +
        "long wooden counter, behind huge stacks of letters from all " +
        "over. There is a sign here you can read.\n");
    add_item( ({"shack", "small shack", "post office"}),
        "This small shack is really not exceptionally well built, but " +
        "it seems to serve its purpose.\n");
    add_item( ({"runner", "runners", "smaller orc", "smaller orcs",
            "messenger", "messengers", "cluster", "cluster of orcs",
            "cluster of small orcs", "cluster of smaller orcs"}),
        "These orcs are small and cowardly, each of them waiting their " +
        "turn to serve as a messenger.\n");
    add_item( ({"city", "dol guldur"}),
        "The city of Dol Guldur can be seen beyond the doorway in the " +
        "western wall, well, the parts of it that have been restored " +
        "anyways.\n");
    add_item( ({"up", "ceiling"}),
        "The ceiling here is just a series of warped wooden planks " +
        "stretched out across a couple of thick wooden beams.\n");
    add_item( ({"down", "floor"}),
        "The floor of the post office has been pieced together by " +
        "slabs of flat, if broken, stone.\n");
    add_item( ({"wall", "walls"}),
        "The walls of the shack are made out of wood, with no openings " +
        "save for the doorway that leads back out into the city.\n");
    add_item( ({"door", "doorway", "open doorway", "open door"}),
        "Beyond this open doorway, you can see the restored city of " +
        "Dol Guldur.\n");
    add_item( ({"plank", "planks", "wooden plank", "wooden planks",
            "warped wooden plank", "warped wooden planks", "warped plank",
            "warped planks"}),
        "There are hundreds of warped wooden planks laid across some " +
        "thick wooden beams, providing walls and a roof for the post " +
        "office.\n");
    add_item( ({"beam", "beams", "thick beam", "thick beams", "wood beam",
            "wood beams", "wooden beam", "wooden beams", "thick wooden beam",
            "thick wooden beams", "thick wood beam", "thick wood beams"}),
        "These thick wooden beams are the skeleton of the small shack " +
        "which serves as the local post office. There are hundreds of " +
        "warped wooden planks nailed into the beams to make the walls " +
        "and roof.\n");
    add_item( ({"nail", "nails"}),
        "These are just nails used to attach the planks to the beams. " +
        "You can't take them.\n");
    add_item( ({"stone", "stones", "slab", "slabs", "flat slab", "flat slabs",
            "flat stone", "flat stones", "broken slab", "broken slabs",
            "broken stones", "slab of stone", "slabs of stone", 
            "broken stone", "slab of broken stone", "slabs of broken stone"}),
        "There are several slabs of broken stone laid out across the " +
        "floor here.\n");
    add_item( ({"lantern", "lanterns", "bright lantern", "bright lanterns"}),
        "There are a LOT of lanterns in here! It seems like the fat " +
        "orc who runs the post office really doesn't like it if things " +
        "get too dark in here.\n");
    add_item( ({"fat orc", "postmaster", "farl", "postmaster farl", "orc"}),
        "This fat orc seems to be the one running things here. He appears " +
        "to be perpetually annoyed and grumpy, and his body language " +
        "makes it clear that he would rather you leave him alone.\n");
    add_item( ({"sign", "wooden sign"}),
        "A wooden sign sits prominently on the counter. You " +
        "can read it for more information.\n");

    /* Some tells are duplicated to give a higher occurance rate */
    add_tell("A small orc enters at a dead run, delivering a scroll to " +
        "the fat orc behind the counter.\n");
    add_tell("The fat orc gives a scroll to one of his runners, who then " +
        "scurries off as fast as he can run.\n");
    add_tell("A small orc enters at a dead run, delivering a scroll to " +
        "the fat orc behind the counter.\n");
    add_tell("The fat orc gives a scroll to one of his runners, who then " +
        "scurries off as fast as he can run.\n");
    add_tell("A small orc enters at a dead run, delivering a scroll to " +
        "the fat orc behind the counter.\n");
    add_tell("The fat orc gives a scroll to one of his runners, who then " +
        "scurries off as fast as he can run.\n");
    add_tell("A small orc enters at a dead run, delivering a scroll to " +
        "the fat orc behind the counter.\n");
    add_tell("The fat orc gives a scroll to one of his runners, who then " +
        "scurries off as fast as he can run.\n");
    add_tell("The fat orc gives a vicious backhanded slap to the face of " +
        "a small orc runner.\n");
    add_tell("The fat orc grumbles as he goes through the stacks of " +
        "mail on the counter.\n");
    
    add_exit(DG_DIR + "main2", "west", 0, 0, 0);

    set_no_exit_msg( ({"north", "northeast", "east", "southeast", "south", 
            "southwest", "northwest"}),
        "There appears to be a wall blocking you, the only way out is " +
        "through the doorway in the western wall.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 5);

    config_default_trade();
    set_tell_time(150);
}

/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */
void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}
/*enter_inv*/

/*
 * Function name:        do_read
 * Description  :        Reading the sign in the post office
 */
int
do_read(string str)
{ 
    if(!str)
    {
        notify_fail("Read what? The sign?\n");
        return 0;
    }
    
    if((str != "sign") && (str != "sign"))
    
    { 
        notify_fail("Read what? The sign?\n");
        return 0;
    }
    
    write("Shut up and be quiet! People are trying to read letters, or " +
        "write letters in here! Also, I'm too busy working, so be quiet " +
        "for my sake if nothing else!\n- Postmaster Farl " +
        "\n\nHire Runner - 2 Gold\n");
    SAYBB(" reads the sign on the northern wall.");
    return 1;
}
/*do_read*/

/*
 * Function name:        leave_inv
 * Description  :        Needed to take mail folders from mortals
 */
void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
/*leave_inv*/

/*
 * Function name:        rent_runner
 * Description  :        Renting an orc messenger
 */
public int
rent_runner(string str)
{
    int     n;
    mixed   res;
    string  give, change;
    object  runner;

    actor = TP;

    if (!strlen(str) || (str != "runner" && str != "a runner"))
    {
       NF0("What exactly do you wish to rent?\n");
       return 0;
    }

    if (!runners) {
        write("The fat orc shakes his head unhappily indicating that " + 
            "he is out of runners.\n");
        return 1;
    }

    if (pointerp(res = pay(Fee, TP)) && (sizeof(res) > 1))
    {
        give = text(res);
        change = text(res[sizeof(MONEY_TYPES)..]);
        write("You toss " + text(res) + " to the fat orc" +
            (strlen(change) ? " and he gives you " + 
                change + " back as change" : "") +
            ".\nA runner trots out from behind the counter, ready " +
            "to deliver your messages!\n");
        tell_room(environment(actor), QCTNAME(actor) + " rents a runner.\n",
            actor);
        runners--;
        runner = clone_object(DG_OBJ_DIR + "runner.c");
        if (runner->move(TP)) {
            runner->move(environment(TP), 1);
        }

        return 1;
    }

    write("It seems you do not have enough money to afford a runner.\n");
    return 1;
}
/*rent_runner*/

public void
init() 
{
    ::init();

    add_action(rent_runner,  "rent");
    add_action(rent_runner,  "hire");
    add_action(do_read,      "read");

    post_init();
}

void
reset_room()
{
    runners = NUM_RUNNERS;
}
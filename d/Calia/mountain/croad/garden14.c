// ROOM:  palace garden 14

    /*  Calia Domain

    HISTORY

    [96-02-23] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN14.DOC]

    PURPOSE

    This is one of 14 garden rooms surrounding Calia palace.  See comments in
    Room 1 for layout details.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <macros.h>
#include "crdefs.h"
#include <stdproperties.h>
#include GARDEN_QUEST

// FUNCTIONS

// Function:  plant_seed

/*

Purpose:  Plant a seed in this room.  To be successful, player must have a
trowel and a seed from room garden7, and he must have fed the fish in the pond
there.  Failure to meet all the requirements may result in interference from
the local frog.

Arguments:  string containing text typed by the player.

Returns:  0/1

*/

int
plant_seed(string str)

    {

    object tp = this_player();
    object seed = present("seed", tp);
    object trowel = present("trowel", tp);

    /*  The following arrays are used to guide the frog around the palace if he
        needs to return a seed to the pond in garden7.  There is no living frog
        object, just a series of tell_room statements.  The rooms and
        directions refer to the rooms the frog will encounter upon leaving this
        room to make a loop around the palace and the exits he will take from
        each of those rooms (the last exit in the list brings him back here).
        The suffix "cl" is for a clockwise loop and "cc" is for
        counterclockwise.  A random function will put the clockwise or
        counterclockwise values into arrays *rooms and *exits later.  Object
        frog_room will be used during the frog's journey to point to his
        current location.  */

    string *rooms_cl = ({"garden13", "croad27", "garden1", "garden2",
        "garden3", "garden4", "garden5", "garden6", "garden7", "garden8",
        "garden9", "garden10", "garden11", "garden12", "garden13"});

    string *exits_cl = ({"west", "west", "northwest", "northwest", "north",
        "northeast", "east", "east", "east", "east", "southeast", "south",
        "southwest", "southwest", "following a small path"});

    string *rooms_cc = ({"garden13", "garden12", "garden11", "garden10",
        "garden9", "garden8", "garden7", "garden6", "garden5", "garden4",
        "garden3", "garden2", "garden1", "croad27", "garden13"});

    string *exits_cc = ({"northeast", "northeast", "north", "northwest",
        "west", "west", "west", "west", "southwest", "south", "southeast",
        "southeast", "east", "east", "following a small path"});

    string *exits;
    string *rooms;
    object frog_room;

    /*  The following arrays are used to randomize the actions of the frog so
        that players do not always see the exact same text when he comes by.
        */

    string *entrances =({

        "suddenly races past you!\n",

        "comes rushing at you shouting a high-pitched 'ni! ni! ni!'  " +
            "You quickly jump out of the way to let him pass.\n",

        "comes rushing along the garden path!\n",

        "suddenly hops into view.  " +
            "He's in such a hurry that he almost bumps into you!\n",

        "comes hopping at breakneck speed along the path!\n",

        "arrives, obviously in a big hurry!  " +
            "Seeing you blocking the path, he makes a great leap " +
            "over your head and continues on his way.\n"});

    string *spitseeds = ({

        "The frog comes to an abrupt stop, " +
            "spits a seed into the center of the pond, " +
            "then resumes his mad dash along the gravel path.\n",

        "The frog comes to a sudden stop when he gets close " +
            "to the pond, sliding on the path and scattering " +
            "gravel everywhere.  He takes careful aim, spits a seed " +
            "into the center of the pond, then continues on his way.\n",

        "The frog stops so abruptly that he skids on the gravel path " +
            "and plunges headlong into the pond!  He spits out a seed, " +
            "then leaps out of the water just in time to avoid being " +
            "swallowed by one of the fish.\n",

        "The frog hops onto one of the benches and takes a few seconds " +
            "to relax and admire the flowers.  To your surprise he " +
            "suddenly spits out a seed with a loud 'ptui!' that lands " +
            "right in the middle of the pond, then he winks at you and " +
            "hops off the bench.\n",

        "The frog leaps over the pond, spitting a seed directly into " +
            "its center as he descends in a graceful arc.  " +
            "He lands on the gravel path with a soft thud, " +
            "then scrambles away.\n"});

    int i;

    int num_entrances = sizeof(entrances);
    int num_spitseeds = sizeof(spitseeds);

    /*  Next statement ensures that variable str contains string data to avoid
    type mismatch if player enters "plant" with no argument.  */

    if(!stringp(str)) str = " ";

    if(!wildmatch("*seed", str))

        {

        write("Plant what?\n");
        return 1;

        }

    else if(!objectp(seed))

        {

        write("You could probably plant a seed here " +
            "if you had a seed to plant.\n");

        return 1;

        }

    else if(!objectp(trowel))

        {

        notify_fail("You try to dig a little hole to plant the seed in, " +
            "but you quickly realize that you don't have the right tool.\n");

        return 0;

        }

    else

        {

        /*  To reach this point, player must have a seed and a trowel to plant
        it with.  If the player is using the wrong seed or has not fed the
        fish, the local frog will prevent completion of the quest.  */

        write("You dig a little hole with your trowel " +
            "in a patch of bare ground and drop the seed into it.\n");

        say(QCTNAME(tp) + " digs a little hole in a patch of " +
            "bare ground and drops a seed into it.\n");

        if(!(seed->query_prop(GARDEN_QUEST_SEED)))

            {

            /*  Wrong seed.  */

            tell_room(this_object(),
                "A little orange frog jumps down from a high branch, " +
                "snatches the seed with a flick of his long pink tongue, " +
                "and then scrambles back up into the trees!  " +
                "He swallows the seed and leans back on a clump of leaves, " +
                "looking down on you with a big, satisfied grin.\n");

            log_file("garden_quest", tp->query_name() +
            " planted wrong seed.\n");

            seed->remove_object();
            return 1;

            }

        else if((tp->query_prop(CALIA_I_GARDEN_QUEST_STAGE)) != FED_FISH)

            {

            /*  Player didn't feed the fish.  Local frog has instructions to
            return the seed to the pond in garden7.  */

            tell_room(this_object(),
                "A little orange frog jumps down from a high branch and " +
                "snatches the seed with a flick of his long pink tongue! " +
                "The frog leaves north.\n");

            seed->remove_object();

            if(random(2))  /*  Select clockwise or counterclockwise run.  */

                {

                rooms = rooms_cl;
                exits = exits_cl;

                }

            else

                {

                rooms = rooms_cc;
                exits = exits_cc;

                }

            for (i = 0; i < 15; i++)

                {

                frog_room = find_object(CROAD + rooms[i]);

                tell_room(frog_room,
                    "A tiny orange frog " + entrances[random(num_entrances)]);

                if (rooms[i] == "garden7")
                    tell_room(frog_room, spitseeds[random(num_spitseeds)]);

                tell_room(frog_room,
                    "The tiny orange frog hops away " + exits[i] + ".\n");

                if (i == 0)
                    tell_room(frog_room,
                    "You stand in amazement as the frog races away.  " +
                    "A few moments later, you hear him approaching " +
                    "from the opposite direction.\n");

                }

            tell_room(this_object(),
                "A few moments later, the frog returns looking " +
                "rather fatigued, but he still manages to slip past " +
                "you up into the trees.\n");

            log_file("garden_quest", tp->query_name() +
                " didn't feed fish.\n");

            return 1;

            }

        else

            {

            /*  Player has the correct seed and has fed the fish.  */

            tell_room(this_object(),
                "A tiny orange frog high up in the trees " +
                "slowly climbs down, his gaze fixed on the seed.  " +
                "He stops his descent not far over your head, " +
                "but still out of reach.\n");

            write("You cover the seed up carefully, " +
                "but you notice that the ground seems a little dry.  " +
                "You suspect that this seed will need some watering.\n");

            seed->remove_object();
            say(QCTNAME(tp) + " carefully covers the seed with soil.\n");
            tp->add_prop(CALIA_I_GARDEN_QUEST_STAGE, PLANTED_SEED);
            return 1;

            }

        }

    }

// Function:  water_seed

/*

Purpose:  Lets the player water the seed he has planted.  This is the final
step of the garden quest and the player will get xp if he has performed the
steps correctly.  If not, he will simply water some ground.  Player must have a
filled watering can.

Arguments:  string containing text typed by the player.

Returns:  0/1

*/

int
water_seed(string str)

    {

    object tp = this_player();
    object watering_can = present("watering can", tp);

    /*  Next statement ensures that variable str contains string data to avoid
        type mismatch if player enters "water" with no argument.  */

    if(!stringp(str)) str = " ";

    if(!objectp(watering_can))

        {

        write("You are forbidden to water anything here unless " +
            "you are using a proper watering can.\n");

        return 1;

        }

    if(str != "seed")

        {

        /*  If the player tries to water something other than "seed," let the
            routine in the watering can handle it.  */

        notify_fail("Water what?\n");
        return 0;

        }

    if((tp->query_prop(CALIA_I_GARDEN_QUEST_STAGE)) != PLANTED_SEED)

        {

        if ((watering_can->water_something("ground")))

            {

            write("A tiny orange frog high up in one of the trees " +
                "looks down on you with a quizzical expression, " +
                "as if he is wondering why you are sprinkling water " +
                "on this particular patch of ground.\n");

            say("A tiny orange frog high up in one of the trees " +
                "looks down with a quizzical expression, " +
                "as if he is wondering why " +
                QTNAME(tp) + " is sprinkling water " +
                "on this particular patch of ground.\n");

            log_file("garden_quest", tp->query_name() +
                " didn't plant seed.\n");

            }

        else

            {

            write("Your watering can is empty!\n" +
                "A tiny orange frog nearly falls out of " +
                "the tree laughing at you!\n");

            say("A tiny orange frog nearly falls out of the tree " +
                "laughing at " + QTNAME(tp) + " as " +
                tp->query_pronoun() + " tries to water the ground " +
                "with an empty watering can!\n");

            }

        return 1;

        }

    else

        {

        write("You make sure that you have your watering can " +
            "pointed directly at the spot where you planted the " +
            "seed and tilt it slightly toward the ground.\n");

        if (!(watering_can->water_something("ground")))

            {

            say(QCTNAME(tp) + " stands for a few moments holding " +
                "an empty watering can over a bare patch of ground, " +
                "while in the branches overhead " +
                "a tiny orange tree frog rolls his eyes " +
                "in exasperation.\n");

            write("You stand holding the watering can over " +
                "a bare patch of ground for a few moments until " +
                "it occurs to you that no water is coming out of it, " +
                "while in the branches overhead " +
                "a tiny orange tree frog rolls his eyes " +
                "in exasperation.\n");

            return 1;

            }

        /*  All quest requirements are satisfied.
            Now check to see if player has done this quest before.
            Quest bit:  Calia group 1 bit 12.  */

        if(tp->test_bit("Calia", GARDEN_QUEST_GROUP, GARDEN_QUEST_BIT))

            {

            /*  Player did it before.  */

            say("A tiny orange frog watches with mild curiosity as " +
                QTNAME(tp) + " waters the seed, then looks around to " +
                "see if anything else is happening in the garden.\n");

            write("A tiny orange frog looks down on you from his " +
                "perch in the trees with an expression " +
                "of profound boredom on his face, " +
                "as if he has seen you do this before.\n");

            log_file("garden_quest", tp->query_name() + " gets " +
                "no experience, " + ctime(time()) + ".\n");

            }

        else

            {

            tell_room(this_object(),
                "A tiny orange frog jumps down from a tree and frolics " +
                "in the stream of water!  He then scampers back up the " +
                "tree trunk and returns to his favorite spot among the " +
                "branches, looking very wet and happy.\n");

            tp->set_bit(GARDEN_QUEST_GROUP, GARDEN_QUEST_BIT);
            tp->add_exp(GARDEN_QUEST_EXP);
            write("You feel more experienced!\n");
            tp->command("save");

            log_file("garden_quest", tp->query_name() +
                " solved garden quest: " + ctime(time()) + ".\n");

            }

        tp->remove_prop(CALIA_I_GARDEN_QUEST_STAGE);

        return 1;

        }

    }

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
    add_action(plant_seed, "plant");
    add_action(water_seed, "water");

    }

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Calia Palace Gardens, somewhere among the willows");

    set_long("You find yourself in a small clearing among the " +
        "willow trees.  There are a few flowers here, " +
        "but they are scattered in irregular clumps, " +
        "not in formal arrangements like the ones in the garden.\n");

    /* EXITS */

    add_exit(CROAD + "garden13", "north", 0);

    /* ITEMS */

    add_item(("path"),
        "There's a little dirt path that leads north " +
        "back to the formal areas of the garden.\n");

    add_item(({"willow","willows","trees","branches"}),
        "These are weeping willows, planted in memory of the many " +
        "warriors who gave their lives on the mountainside.  " +
        "You feel quite tranquil and secure as you stand surrounded " +
        "and shaded by them.  A bit of movement high up in one of " +
        "the trees catches your eye - " +
        "you spy a tiny frog climbing on one of the graceful branches!\n");

    add_item(({"clump","clumps"}),
        "The clumps of flowers vary in size and variety, " +
        "and there has obviously been no attempt made to " +
        "arrange them in a design.\n");

    add_item(({"frog","tiny frog"}),
        "It's a tiny tree frog, commonly known as a Nipeeper because " +
        "of its cheerful call which sounds a bit like a high-pitched " +
        "'ni!'  This one is decked out in blazing orange with black " +
        "stripes and big green eyes.  His garish colors warn predators " +
        "that he is extremely poisonous, but high up in the tree he " +
        "poses no danger to you.\n");

    add_item(({"flower","flowers","plants"}),
        "A variety of flowers grow here, and they've been planted " +
        "without much regard to their arrangement.  You " +
        "suspect that the gardeners put young plants here to mature " +
        "before they are moved to the formal displays.  " +
        "There's plenty of bare ground here for more flowers to " +
        "be planted.\n");

    add_item(({"ground","bare ground"}),
        "The ground here must be fertile, " +
        "judging from the way the trees and flowers are thriving.\n");

    }

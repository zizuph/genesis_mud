/*
 *  /d/Gondor/rohan/entwash/ent2e.c
 *
 *  A quest room for the ENTWASH LARVAE quest.
 *
 *  Coded by Gorboth, Sept 1995
 *
 *  Special thanks to: Olorin, Jeremiah
 */
inherit "/d/Gondor/rohan/entwash/entwash.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/bits.h"
#include "/d/Gondor/defs.h"

#define GONDOR_I_LARVAE_QUEST	"_gondor_i_larvae_quest"
#define NR_BUGS			4

//	Prototypes
int throw_stuff(string str);

//	Global variables
static int  pool = 0;   // larva quest - 0:unsolved, 1:solved

void
reset_room()
{
    pool = 0;
    set_alarm(3.0, 0.0, "make_bug");
}

void
create_swamp()
{
    set_extra_long("Insects are everywhere here, stirring in thick"
      + " clouds of irritating noise. A large pool spreads over the"
      + " northern ground here, and a swift stream passes to the"
      + " south.");

    add_item(({"stream","swift stream"}), BSN(
        "The southernmost remnant of the river Entwash flows south of"
      + " here, its current yet intact. Not far to the east, it can"
      + " be seen fragmenting into many trickles, and fading into the"
      + " mist."));
    add_item(({"insect","insects"}), BSN(
        "These creatures are numerous and persistant here. Swarming"
      + " together one way, and then another, you get the feeling that"
      + " they have taken an interest in your bodily juices."));
    add_item(({"pool", "large pool"}), "@@exa_pool");
    add_item(({"larva","larvae","flower"}), "@@exa_stuff");

    add_exit(ENTWASH_DIR + "ent2d", "west");
    bugs = allocate(NR_BUGS/2 + random(NR_BUGS) + 1);

    set_alarm(1.0, 0.0, "reset_room");

    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    BEACH;
}

string
exa_pool()
{
    string desc;

    if(!pool)
    {
        desc = "There is something very different about this pool."
             + " The water is thick with insects, and many larvae are"
             + " visible floating on the surface.";
    }
    else
        desc = "Something very unsavory has occured in this pool."
             + " Towards the middle of the water, someone has dropped"
             + " a pale-white flower, which has begun to disintegrate and"
             + " spread its poison through the liquid.";

    return BSN(desc);
}

string
exa_stuff()
{
    string desc;

    if(!pool)
    {
        desc = "The larvae which crest the surface of the large pool"
             + " glisten with moisture. This seems to be an important"
             + " breeding pit.";
    }
    else
    {
        desc = "The flower in this pool seems to have killed most of the"
             + " larvae. They have turned grey and drifted into the mud.";
     }

    return BSN(desc);
}

void
init()
{
    ::init();
    add_action(throw_stuff, "throw");
}

/*
 * Function name: reward_player
 * Description:   dummy function for possible quest reward
 * Arguments:     tp - the player who solved the quest
 */
public void
reward_player(object tp)
{
    int  reward;

    if (!tp->query_prop(GONDOR_I_LARVAE_QUEST))
    {
        return;
    }

    tp->catch_msg("You feel that the old man will appreciate this!\n");

    if (tp->test_bit("Gondor", ENTWASH_LARVAE_GROUP, ENTWASH_LARVAE_BIT))
    {
        tp->catch_msg("However, one reward was enough for you!\n");
        return;
    }

    reward = tp->query_exp();
    if (reward > ENTWASH_LARVAE_EXP)
        reward = ENTWASH_LARVAE_EXP;

    tp->set_bit(ENTWASH_LARVAE_GROUP, ENTWASH_LARVAE_BIT);
    tp->add_exp_quest(reward);
    tp->catch_msg("You feel more experienced.\n");
    LOG_QUEST(tp, reward, "ENTWASH LARVAE");
}

/*
 * Function name: throw_stuff
 * Description:   my modified version of your function
 *                which contains some important checks
 * Arguments:     str - the argument to the verb 'throw'
 * Returns:       0 / 1 - failure / success
 */
public int
throw_stuff(string str)
{
    mixed   fail;
    object  obj;

    if (!strlen(str))
    {
        NFN("What do you want to throw?");
        return 0;
    }

    if (!(parse_command(str, all_inventory(TP),
        "%o 'in' / 'into' [the] 'pool' / 'water'", obj)))
    {
        // parse_command() failed
        NFN("What do you want to throw where?");
        return 0;
    }

    // check properties! This is vitally important!
    if (fail = obj->query_prop(OBJ_M_NO_DROP))
    {
        if (!stringp(fail))
            fail = "You cannot throw the "+obj->short()+" away.\n";
        NF(fail);
        return 0;
    }

    TP->catch_msg("You throw the "+obj->short()+" into the "
      + "pool. It is quickly swallowed up by the deep mud.\n");
    tell_room(TO, QCTNAME(TP)+" throws "+LANG_ADDART(obj->short())
      + " into the pool where it is swallowed up in the deep mud.\n",
        TP);

    if (obj->query_herb_name() == "morgurth")
    {
        if (obj->query_dried())
        {
            tell_room(TO, "Due to the fact that the flower was dried,"
              + " and therefore dissolves instantly in the water, there does"
              + " not seem to be much of an effect.\n");

            obj->remove_object();
            return 1;
        }

        if (pool)
        {
            tell_room(TO, "The flower begins to immediately react with "
              + "the waters of the pool, but as the waters have "
              + "already been poisoned before, it has no "
              + "effect.\n");
        }
        else
        {
            tell_room(TO, "The flower begins to immediately react with"
              + " the waters of the pool.\n");
            pool = 1;    // larva quest solved!

            reward_player(TP);
        }
    }

    obj->remove_object();
    return 1;
}


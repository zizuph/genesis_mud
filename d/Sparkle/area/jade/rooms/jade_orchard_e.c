/*
*  /d/Sparkle/area/jade/rooms/jade_orchard_e.c
*  Created 2017-02-20 by Martin Berka on Genesis MUD
*
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <cmdparse.h>
#include <stdproperties.h>

/* Global variables */
int     max_herb_count;
mapping planted_herbs;

/* Prototypes */
int plant_herb(string str);
void start_herb(string herb_file);


/*
 * Function name: create_room
 * Description  : Room constructor
 */
void
create_room()
{
    set_short("In the eastern part of an orchard");
    set_long("Fruit trees of various size grow on all sides, surrounded by "
        + "lively grass. Though every tree seems disciplined and "
        + "well-cared-for, unlike in the rest of the orchard, the ground "
        + "here is a tangled mess of gnarled, overgrown roots. "
        + "Further to the east is a large"
        + "wooden fence running north-south, followed by a cleared area and, "
        + "finally, the trees of the Jade Forest. A path leads northwest and "
        + "south towards some sort of small building.\n");

    add_item( ({ "building", "small building", "some sort of small building" }),
        "The small building is made "
        + "of wood and stands by itself. You will have to travel south to get "
        + "a closer look.\n");
    remove_item("ground");
    add_item( ({"ground", "roots", "gnarly roots", "gnarled roots",
        "overgrown roots", "mess", "tangle", "tangled mess"}),
        "The roots climb writhe over each other like "
        + "(motionless) snakes, the fingers of old trees clawing for "
        + "purchase in the soil. In the poockets of earth between them is an "
        + "abundance of younger plant growth.\n");
    add_item( ({"abundance", "dirt", "earth", "flowers", "growth",
        "plant growth", "younger plant growth", "patches", "soil", "stalks"}),
        "A variety of small stalks and flowers thrive in the dirt between the "
        + "gnarled roots, free from competition with the lush grass that "
        + "dominates most of the orchard. You see a few patches of exposed "
        + "soil - perhaps you could <plant> something here?\n" );

    add_fence( ({"northeast", "southeast" }) );
    add_forest();
    add_orchard( ({"north", "east", "southwest"}) );

    add_exit(ROOM_DIR + "jade_orchard_se", "south");
    add_exit(ROOM_DIR + "jade_orchard_n", "northwest");
    add_exit(ROOM_DIR + "jade_orchard_mid", "west", 0, 5, 1);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    //Accessing the "herbs" global array
    max_herb_count = min(sizeof(herbs), 10); //Number of varieties here

    planted_herbs = mkmapping(herbs, allocate(max_herb_count));
    for (int i = -1; ++i < max_herb_count; )
    {
        planted_herbs[herbs[i]] = -1; //Default herbs have infinite supply
    }


    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Currently unused, consider using for simple herb replenishment
 */
void
reset_room()
{

}

/*
 * Function name: init
 * Description  : Add herb-planting action
 */
void
init()
{
    ::init();
    add_action(plant_herb, "plant");
}

/*
 * Function name: plant_herb
 * Description	: Plant an herb among the roots
 * Arguments	: (string) text following verb.
 * Returns		: (int) 1 - Command recognized
 */
int
plant_herb(string str)
{
    if (!str) //Not sticking anything, so assume it's the emote.
    {
        return 0; //Not certain player even had an action in mind
    }

    if (TP->query_prop(LIVE_O_SPELL_ATTACK) || TP->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You are busy with other things!\n");
        return 1;
    }

    //What are we planting?
    mixed oblist = PARSE_COMMAND(str, TP, "[the] %i [here] [in] / [among] "
        + "[the] [ground] / [dirt] / [soil] / [roots]");
    if (!sizeof(oblist))
    {
        return 0; //Emote
    }

    object to_plant = oblist[0];

    if (to_plant->query_prop(OBJ_I_VOLUME) > 1000)
    {
        write("The pockets between the roots are too small to plant anything "
            + "bigger than your hand!\n");
        return 1;
    }

    string *plant_ancestors = inherit_list(to_plant);
    if (!member_array("/std/herb.c", plant_ancestors))
    {
        write("That is unlikely to grow here.\n");
        return 1;
    }

    int plant_error = to_plant->move(TO); //Hit an error
    if (plant_error)
    {
        if (plant_error == 2)
        {
            write("You start to plant the "  + to_plant->query_short()
                + " in the "
                + "dirt, but cannot seem to release it. You withdraw your hand "
                + "from the soil, still holding it.\n");
            return 1;
        }
        write("You are unable to plant the " + to_plant->query_short() + ".\n");
        return 1;
    }

    write("You bury the " + to_plant->query_short() + " among the roots and "
        + "stand back to look at your work. There really is a vast tangle "
        + "here. You are no longer sure where you planted it.\n");
    tell_room(TO, QCTNAME(TP) + " buries something among the roots.\n", ({TP}));

    /*Will it grow? Skipping: fruit (no time to grow a whole tree), moss
     * (likes shade), lichen (should not bury), algae (not enough water),
     * vegetables (too big),  leaves/bark/wreathes (lack seeds)
     * likes shade, and lichens belong on the surface.
     */
    if (!sizeof( regexp(to_plant->query_names(),
        "(bean|berr|flower|frond|mushroom|seed|stalk|umbel|weed)") ))
    {
        to_plant->remove_object();
        return 1; //Rots in the ground
    }
    string plant_file = plant_ancestors[sizeof(plant_ancestors) - 1];
    to_plant->remove_object();

    //Let this herb spend a day - give or take - getting ready.
    set_alarm( itof(76400 + random(20000)), 0.0, &start_herb(plant_file) );

    return 1;
} /* plant_herb */


/*
 * Function name: replenish_herb
 * Description  : Periodically increase the available amount of an herb
 * Arguments    : (string) filepath of the herb
 */
void
replenish_herb(string herb_file)
{
    if (planted_herbs[herb_file] < 1)
    {
        //0: none left to grow back; negative: infinite supply
        return;
    }

    planted_herbs[herb_file] += min(planted_herbs[herb_file] * 2, 10);
    set_alarm(itof(76400 + random(20000)), 0.0, &replenish_herb(herb_file));
} /* replenish_herb */

/*
 * Function name: search_for_herbs
 * Description  : Mask standard hearb-search function to detect any found herbs
 *      and affect the (limited) supply of them.
 * Arguments:     herbalist - The player searching for herbs
 *                herb_file - the file of the herb the player is looking for
 *                            (optional)
 * Returns:       The message to write
 */
varargs string
search_for_herbs(object herbalist, string herb_file = 0)
{
    if (!strlen(herb_file))
    {
        herb_file = one_of_list(herbs);
    }
    string return_message = ::search_for_herbs(herbalist, herb_file);

    if (wildmatch("You find *", return_message))
    {
        if (planted_herbs[herb_file] > 0)
        {
            planted_herbs[herb_file] -= 1;

            if (planted_herbs[herb_file] < 1)
            {
                planted_herbs = m_delete(planted_herbs, herb_file);
                herbs = m_indices(planted_herbs);
            }
        }
    }

    return return_message;
} /* search_for_herbs */


/*
 * Function name: start_herb
 * Description	: Add an herb to the list of available ones when it is ready
 * Arguments	: (string) filepath of the herb
 */
void
start_herb(string herb_file)
{
    if (!herb_file)
    {
        return;
    }

    if (planted_herbs[herb_file]) //This herb is already present
    {
        if (planted_herbs[herb_file] >= 0)
        {
            planted_herbs[herb_file] += 2;
        }
        return;
    }

    if (m_sizeof(planted_herbs) >= max_herb_count) //Free up space in herb list
    {
        planted_herbs = m_delete(planted_herbs, random(max_herb_count));
    }

    planted_herbs[herb_file] = 2;
    herbs = m_indices(planted_herbs);

    set_alarm(itof(76400 + random(20000)), 0.0, &replenish_herb(herb_file));
} /* start_herb */

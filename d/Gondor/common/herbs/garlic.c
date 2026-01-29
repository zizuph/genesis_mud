/*
 * garlic.c
 *
 * will make vampyrs go wimpy
 * Olorin, April 1993
 * Last mod: check for query_guild_name_occ() too, Olorin 10-jun-1993  
 *           added magic props for Vampire effects, Gorboth 30-May-1997
 *           Fixed the alarm usage, no alarms in jars in racks. 28-Jun-2004
 *           (Fix by Cotillion)
 */
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>


#include "/d/Gondor/defs.h"

#define HP_HEAL 5

int     smell_alarm = 0;

void smell();

void
create_herb()
{
    set_name("bulb");
    add_name(({"cloves", "spice", "_spice"}));
    add_name("dollost_ingr");
    set_adj(({"white", "rose-tinged", "smelly", "mild"}));
    set_herb_name("garlic");
    set_short("mild smelly white rose-tinged bulb");
    set_pshort("mild smelly white rose-tinged bulbs");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a smelly white rose-tinged bulb. "+
                      "It seems to have been dug out of the " + 
                      "earth recently and gives off a sharp pungent smell."));
    set_id_long(BSN("This is a garlic bulb. Garlic (Allium sativum) "+
                    "is a hardy, perennial bulb plant of the lily family growing " +
                    "in warm and moderate climate. It can reach a height "+
                    "of two feet and has very narrow, keeled leaves with " +
                    "dense spherical heads of pinkish flowers. The white "+
                    "rose-tinged bulbs of strong odor are thinly covered and break " +
                    "into separate parts, or cloves. Since ancient times, " +
                    "garlic cloves have been used to flavor dishes. Some rhymes " +
                    "of old days claim that garlic has the magical property of " +
                    "protecting against some kindreds of undead, but for centuries " +
                    "no one in Gondor has been able to verify this claim."));

    set_effect(HERB_HEALING,"hp", HP_HEAL);

    set_id_diff(20);
    set_find_diff(5);

    set_decay_time(3600);
    set_herb_value(72);

    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment"}) );
    add_prop(MAGIC_AM_ID_INFO, ({
        "A magical enchantment has been placed upon this herb.\n", 1,
            "In the dawn of Middle Earth, cloves of garlic such as this"
            + " were touched by Yavanna, and given a power over certain"
            + " breeds of the undead.\n", 10,
            "Vampires will be stricken with great fear at the scent of"
            + " the clove.\n", 20 }) );
}

void
init()
{
    ::init();
    if (interactive(this_player()) && !sizeof(get_alarm(smell_alarm)))
        smell_alarm = set_alarm(2.0, 10.0 + 20.0 * rnd(), smell);
}

int
vampyr_check(object player)
{
    /* Checks for guildmembership in a guild of another domain
     * should not be made contrary to requests of that domain.
     * Olorin
     * 
     * Per Deagol's request, changed to remove effect on guild
     * "Vampires of Emerald"
     */    
    if (player->query_guild_name_occ() == "V of E")
        return 1;

    return 0;
}

void
smell()
{
    object  room = ENV(TO),
        *people,
        me,
        cont = ENV(TO);
    int     i,
        rnd,
        strength;

    while (room && !room->query_prop(ROOM_I_IS))
        room = ENV(room);
    
    if (cont == room || living(cont))
    {
        tell_room(room, "A sharp pungent smell pervades the environment.\n");

        people = all_inventory(room);
        i = sizeof(people);

        /* If there are no players present, the alarm must be removed */
        if (!sizeof(FILTER_PLAYERS(people)))
        {
            remove_alarm(smell_alarm);
            return;
        }
        
        while(i--)
        {
            if (interactive(people[i]) && vampyr_check(people[i]))
            {
                rnd = 195 - random(61) - random(61);
                strength = people[i]->query_stat(SS_DIS)
                    + people[i]->query_stat(SS_OCCUP);
                if (rnd > strength)
                {
                    people[i]->catch_msg("The terrible stench makes you "
                        + "sick. You run away head over heels.\n");
                    tell_room(room, QCTNAME(people[i]) + " flees from "
                        + "the stench.\n",people[i]);
                    people[i]->run_away();
                }
                else
                {
                    people[i]->catch_msg("The terrible stench makes you "
                        + "sick. You want to run away, but you barely "
                        + "manage to overcome your fright.\n");
                    tell_room(room,QCTNAME(people[i]) + " shrinks away "
                        + "from the stench. " + CAP(people[i]->query_pronoun())
                        + " looks terribly frightened.\n",people[i]);
                    people[i]->add_panic(rnd/10);
                }
            }
        }
    } else {
        /* If we're not in a player and not in a room no alarms */
        remove_alarm(smell_alarm);
    }
    
    return;
}

void
enter_env(object dest, object old)
{
    if (objectp(dest) && living(dest) && vampyr_check(dest))
    {
        clear_effect();
        set_poison_file(HERB_DIR + "garlic_vamp_effect");
        set_effect(HERB_POISONING,"garlic",10);
    }
    else
    {
        clear_effect();
        set_effect(HERB_HEALING,"hp", HP_HEAL);
    }
    ::enter_env(dest, old);
}

int
command_eat()
{
    int     result;

    result = ::command_eat();

    if (result)
    {
        setuid();
        seteuid(getuid());
        clone_object(HERB_DIR + "stench_ob")->move(TP, 1);
    }

    return result;
}

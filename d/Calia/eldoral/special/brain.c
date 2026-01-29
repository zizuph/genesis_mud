/*
 * seer_brain.c
 *
 * Master 'brain' object for the Seer and the Lord Quest in Eldoral.
 * Basically remembers where the dagger and cloth are hidden on the
 * island, and resets the location each time the quest is done.
 *
 * Coded by Khail, Jan 7/97
 */
#pragma strict_types

#include "defs.h"

mapping places = (["north" : ({FOREST + "n_forest_4",
                                FOREST + "n_forest_5",
                                FOREST + "n_forest_9"}),
                    "east"  : ({FOREST + "shrine_3",
                                FOREST + "e_forest_15",
                                FOREST + "e_forest_13",
                                FOREST + "e_forest_18"}),
                    "south" : ({FOREST + "shrine_1",
                                FOREST + "shrine_2",
                                FOREST + "s_forest_11",
                                FOREST + "s_forest_19",
                                FOREST + "s_forest_27"}),
                    "west"  : ({FOREST + "w_forest_1",
                                FOREST + "w_forest_3",
                                FOREST + "w_forest_4",
                                FOREST + "w_forest_6"})]);

mapping location;
object dagger,
       cloth,
       poltergeist,
       seer;
int lord_saw_dagger;

public void reset_quest();

public void
set_lord_saw_dagger()
{
    lord_saw_dagger = 1;
}

public int
query_lord_saw_dagger()
{
    return lord_saw_dagger;
}

public void
add_poltergeist(object ob)
{
    poltergeist = ob;
}

public object
query_poltergeist()
{
    return poltergeist;
}

public void
add_seer(object ob)
{
    seer = ob;
}

public object
query_seer()
{
    return seer;
}

public void
add_dagger(object ob)
{
    dagger = ob;
}

public object
query_dagger()
{
    return dagger;
}

public void
add_cloth(object ob)
{
    cloth = ob;
}

public object
query_cloth()
{
    return cloth;
}

public varargs mapping
query_location(mixed flag = 0)
{
    if (!location)
        reset_quest();
    if (flag == "index")
        return m_indexes(location)[0];
    else if (flag == "value")
        return m_values(location)[0];
    return location + ([]);
}

public void
reset_quest()
{
    string index,
           value;

    seteuid(getuid());

    if (location)
        query_location("value")->reset_quest();
 
    location = ([]);

    index = m_indexes(places)[random(m_sizeof(places))];
    value = places[index][random(sizeof(places[index]))];

    location[index] = value;
    value->reset_quest();    

    cloth = 0;
    dagger = 0;

    lord_saw_dagger = 0;

    (RUIN + "seer_tower")->reset_quest();
}

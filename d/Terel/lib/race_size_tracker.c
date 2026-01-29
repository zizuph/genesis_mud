/*
 *  /d/Terel/lib/race_tracker.c
 *
 *  This object keeps track of races and their relative sizes for
 *  use with ~Terel/std/armour.c and ~Terel/std/wearable_item.c
 *
 *  EXAMPLE: race / category / category number
 *          
 *           halfling / SMALL / 1
 *           elf / MEDIUM / 2
 *           dwarf / SMALL|MEDIUM / 3
 *           troll / LARGE / 4
 *           centaur / MEDIUM/LARGE / 6
 *           dragon / HUGE / 8
 *           giant / LARGE|HUGE / 12
 *           shapeshifter? / ANY_SIZE / 15
 *
 *  Torm, Sept 98
 */

#pragma strict_types
#pragma binary_save
#pragma no_inherit
#pragma no_clone

inherit "/std/object";

#include "/d/Terel/include/Terel.h"

#define RACE_SIZES "/d/Terel/log/race_sizes"

//** global variables **//
private mapping gRaceSize = ([]);

//** prototypes **//
public void set_race_size(string s, int i);
public void delete_race(string s);
public int query_race_size(string s);
public void query_races_tracked();
private string get_text(int i);
private int legalRaceSize(int i);


public void
create_object()
{
    setuid(); seteuid(getuid());

    set_name("_terel_race_tracker");

    if (!m_sizeof(gRaceSize))
        gRaceSize = restore_map(RACE_SIZES);
}

public void
set_race_size(string race, int size)
{
    if ((!strlen(race)) || (!legalRaceSize(size)))
        return;

    gRaceSize[race] = size;
    save_map(gRaceSize, RACE_SIZES);
}

public void
delete_race(string race)
{
    mixed races = m_indexes(gRaceSize);

    if (!strlen(race))
        return;

    /* can't remove what's not there */
    if (member_array(race, races) == -1)
        return;

    gRaceSize = m_delete(gRaceSize, race);
    save_map(gRaceSize, RACE_SIZES);
}

public int 
query_race_size(string s)
{ 
    int i;
    mixed races = m_indexes(gRaceSize);
    string race, *temp = explode(s, " ");

    if (sizeof(temp) > 1)
        race = temp[sizeof(temp) - 1];
    else
        race = s;

    if (member_array(race, races) == -1)
        return (SMALL | MEDIUM); // default size for unknown race

    return gRaceSize[race];
}
 
public void
query_races_tracked()
{
    mixed races = m_indexes(gRaceSize),
          sizes = m_values(gRaceSize);
    int i, sz = sizeof(races);

    if (!sz)
        write("No races are tracked at this time.\n");
    else
    {
        write("\nRace name          Race size\n"+
            "============================\n\n");
        for (i = 0; i < sz; i++)
            write(sprintf("%-19s%s\n",races[i],get_text(sizes[i])));
    }
}

private string
get_text(int i)
{
    switch (i)
    {
        case SMALL:
            return "SMALL";
        case MEDIUM:
            return "MEDIUM";
        case (SMALL | MEDIUM):
            return "SMALL/MEDIUM";
        case LARGE:
            return "LARGE";
        case (MEDIUM | LARGE):
            return "MEDIUM/LARGE";
        case HUGE:
            return "HUGE";
        case (LARGE | HUGE):
            return "LARGE/HUGE";
        default:
            return "MEDIUM";
    }
}

private int
legalRaceSize(int size)
{
    if (member_array(size, ({ SMALL, MEDIUM, SMALL|MEDIUM,
        LARGE, MEDIUM|LARGE, HUGE, LARGE|HUGE, ANY_SIZE })) == -1)
        return 0;

    return 1;
}

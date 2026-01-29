/* Function done by Cirion, I just put it into an object. */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit "/std/object";

string
query_auto_load()
{
    return MASTER;
}

int
query_recover()
{
    return 0;

}

create_object()
{
    set_name("race statter");
    add_name(({"statter", "rs"}));
    set_short("race statter");
    set_long("The race statter.\n");
}

init()
{
    add_action("racestat", "rs");
    ::init();
}

int
total()
{
    object *race = filter(users(), &not() @ &->query_wiz_level());
    int i, stat, age;
    int num = sizeof(race);

    for(i=0; i < sizeof(race); i++)
    {
	stat += race[i]->query_average_stat();
	age += race[i]->query_age();
    }

    write(sprintf("Totals-          Number: %-8d Avg. Stat: %-10d Age: %-10d",
	num, stat / num, age * 2 / 60 / 60 / 24 / num) + "\n");
    return 1;
}

int
avg_race_stat(string race_name)
{
    int  num, stat, i, age, j;

    object *race = filter(users(), &->id(race_name));

    race = filter(race, &not() @ &->query_wiz_level());

    if(!(num = sizeof(race)))
	return 0;

    for(i=0; i<num; i++)
    {
	stat += race[i]->query_average_stat();
	age += race[i]->query_age();
    }

    write(sprintf("Race: %-10s Number: %-8d Avg. Stat: %-10d Age: %-10d", race_name, num,
	stat / num, age * 2 / 60 / 60 / 24 / num) + "\n");
    return 1;
}

int
racestat(string str)
{
    if (!str)
    {
	avg_race_stat("human");
	avg_race_stat("elf");
	avg_race_stat("dwarf");
	avg_race_stat("goblin");
	avg_race_stat("gnome");
	avg_race_stat("hobbit");
	total();
	return 1;
    }

    NF("Racestat which race?\n");
    if (str != "human" && str != "elf" && str != "dwarf" &&
      str != "goblin" && str != "hobbit" && str != "gnome")
	return 0;

    avg_race_stat(str);
    return 1;
}



inherit "/std/living";

#include "login.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>

create_living()
{
    ::create_living();
    add_name("body");
}

/* You must call this function to set up the body. A zero parameter
   generates a random race/gender */

static void
start_heart()
{
    /*  Make sure init doesn't start any heartbeats */
}

public varargs void
create_body(string race, string gender)
{
    string *a;
    int *stats, i;
    a = explode(file_name(this_object()), "#");
    if(!a || sizeof(a) != 2)
	return;

    set_name("#" + a[1]);

    if(gender)
	set_gender(gender == "male" ? G_MALE : G_FEMALE);
    else
	set_gender(random(2));

    if (race)
	set_race_name(race);
    else
	set_race_name( RACES[random(sizeof(RACES))]);

    set_adj(({ query_gender_string(), query_race_name(), "body", "of" }));
/*
    set_short(query_gender_string() + " " +query_race_name() +
	      " with a tag labeled \"" + query_race_name() +
	      " " + query_name() + "\"");
*/
    set_short(query_gender_string() + " " +query_race_name() +
	      " " + query_name());

    set_long(capitalize(query_real_name()) +
	     " has an empty and blank stare.\n");
    set_appearance(random(98) + 1);
	     
    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    /* add_prop(OBJ_I_INVIS, 1); */

    switch (query_race_name())
    {
    case "human":
	         /* str, dex, con, int, wis, dis */
	stats = ({  9,   9,   9,   9,   9,   9 });
	break;
    case "elf":
	         /* str, dex, con, int, wis, dis */
	stats = ({  6,   6,   9,  11,  11,  11 });
	break;
    case "dwarf":
	          /* str, dex, con, int, wis, dis */
	stats = ({  14,  4,   11,  7,   9,   9 });
	break;
    case "gnome":
	         /* str, dex, con, int, wis, dis */
	stats = ({  9,   9,  11,  6,   8,   11 });
	break;
    case "hobbit":
	        /* str, dex, con, int, wis, dis */
	stats = ({ 4,   17,  8,   11,  7,   7  });
	break;
    case "goblin":
		/* str, dex, con, int, wis, dis */
	stats = ({ 12,  12,  12,  6,   6,   7  });
	break;
    default:
	         /* str, dex, con, int, wis, dis */
	stats = ({  9,   9,   9,   9,   9,   9 });
    }

    for(i = 0; i < 6; i++)
	stats[random(6)]++;

    for (i = 0 ; i < SS_NO_STATS - 3 ; i++)
	set_base_stat(i, stats[i]);

  /* So all the bodies are 'feeling very well' */
    set_hp(1000);

  /* So all the bodies seem of normal length and width */
    add_prop(CONT_I_HEIGHT, RACEATTR[query_race_name()][0]);
    add_prop(CONT_I_WEIGHT, RACEATTR[query_race_name()][1]*1000);
    add_prop(CONT_I_VOLUME, RACEATTR[query_race_name()][4]*1000);
}

// file name:   s_path6.c
// creator(s):  Farlong
// last update: Ilyian (8 March, 1995)
//              Cirion (18 April, 1997): added the functionality that
//              summons the ship to the Tomb of Akram if a player
//              throws the phial (~Avenir/union/obj/phial) into the sea.
// purpose:
// note:
// bug(s):
// to - do:

inherit "/std/room";
#include <macros.h>
#include <math.h>
#include <stdproperties.h>
#include "park.h"

#define SUMMON_WORDS   ({ "alu shian marish", "ferron ali amektu", "forlith edon", \
                          "ekri shian mos", "tensiu eleni aron", "anthel mistok", \
                          "orin alith erig", "techian shiul" })

static object ship, summoner;
static int summoned;

create_room()
{
    set_short("End of path");
    set_long("The path comes to an abrupt end at a rocky ledge, jutting " +
	  "out over a black sea. Far to the south, over the dark waters, " +
	     "you can make out some sort of fortress. To the east and the " +
	   "west, the edge of the island continues, but it is so thickly " +
	     "covered in vegetation that it is impassible.\n");
    add_item("vegetation",
        "It is incredibly lush and thick, a profusion of "
        + "impassable greenery.\n");

    AE(PK + "s_path5", "northeast", 0);

   add_prop(OBJ_I_CONTAIN_WATER, 1);
   add_prop(ROOM_I_TYPE, ROOM_BEACH);
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_NO_CLEANUP, 1);
   IN

   STDEPATH

   AI(({"ocean", "lake", "water", "sea"}), "The dark sea that surrounds the " +
	   "island churns and swirl with strange currents. The water is " +
	   "black and opaque.\n");
    AI(({"fort", "fortress", "outpost", "building"}), "The fortress stands " +
       "far to the south over the water. It seems to be quite large, but you " +
       "can make out few details from this distance.\n");
    AI(({"ledge", "rock", "path"}), "The path comes to an abrupt end at this " +
       "rocky ledge, which overlooks a dark sea. There seems to be no way " +
       "to go but back north.\n");

  set_searched(0);
  set_search_places(({"shore","edge","water","beach"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(HERB+"nethra");

}
 
reset_room()
{
  set_searched(0);
}

/* Ship summoning function for the Union Guru quest */
string
summon_string(object for_who)
{
    string *words = SUMMON_WORDS;
    int     index;

    index = NAME_TO_RANDOM(for_who->query_name(), 103, sizeof(words));

    return words[index];
}

int
query_ship_summoned()
{
    return summoned;
}

object
query_summoner()
{
    return summoner;
}

void
unsummon()
{
    summoned = 0;
}

varargs void
summon_ship(int with_word)
{
    summoned = with_word + 1;

    if(!ship)
    {
       (SHIP + "union/ship")->teleldensanka();
       ship = find_object(SHIP + "union/ship");
    }

    // If the ship has just been cloned, or if it is in
    // the void room, then summon the ship here.
    if(!ENV(ship) || ENV(ship)->id("ship_void"))
         ship->start_ship();
}

int
do_shout(string str)
{
    str = lower_case(str);

    if(wildmatch("*" + summon_string(TP)+ "*", str))
    {
        summoner = TP;
        set_alarm(3.0, 0.0, &summon_ship(1));
    }

    return 0;
}

void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    // Once the ship arrives, reset the summoned var.
    if(to->id("ship"))
    {
       tell_room(TO, "Gliding over the dark water with, a slender "
           + "ship slowly comes to rest against the shore.\n");
       set_alarm(1.0, 0.0, unsummon);
    }
}

/*
 * This function is called from ~Avenir/union/obj/phial
 * what a player throws the phial into the sea.
 */
int
union_guru_summon_ship()
{
    if(!present(ship) && !summoned)
    {
       summoner = TP;
       set_alarm(1.0, 0.0, summon_ship);
       return 1;
    }

    return 0;
}


// for debugging
string
ship_where()
{
    if(!ship)
       return "no ship";

    return file_name(ENV(ship));
}

void
init()
{
    ::init();

    add_action(do_shout, "shout");
}

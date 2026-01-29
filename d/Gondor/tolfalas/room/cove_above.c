/*
 * /d/Gondor/tolfalas/room/cove_above.c
 *
 *  Toby - 16 Sept 2006
 *
 *  The room handling the climb code to reach the secret cove.
 *
 *  Modification log:
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/tolfalas/lib/room_funcs.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"


#define REVEAL_STEP1 "_player_has_discovered_slope_tolfalas"
#define REVEAL_STEP2 "_player_has_discovered_cove_tolfalas"

string long_desc();
string slope_desc();

public void
create_gondor()
{
   set_short("at a trail on the island of Tolfalas");
   set_long(&long_desc());

   add_item(({"underbrush","dense underbrush"}), 
         "The underbrush is very dense but in some places it looks ruffled and not " +
         "quite as dense.\n");
   add_item(({"slope","steep slope"}), &slope_desc());

   add_prop(OBJ_S_SEARCH_FUN, "do_search");
   add_prop(OBJ_I_SEARCH_TIME, 5);



   add_exit(TOLFALAS_DIR + "room/ruins41", "west", 0, 2);
}

string
long_desc()
{
   string ret_str;

   if(TP->query_guild_name_race() == GUILD_NAME)
      ret_str = "You are on a path having just left the ruins behind you to the west. " +
                "Looking east you have a nice view of the bay of Belfalas between the " +
                "trees. The path ends as abruptly as it started and the underbrush " +
                "take over. Behind the underbrush there is a very steep slope leading " +
                "down into, for you, a well known hidden cove in the Bay of Belfalas.";
   else if(TP->query_prop(REVEAL_STEP2))
      ret_str = "You are on a path having just left the ruins behind you to the west. " +
                "Looking east you have a nice view of the bay of Belfalas between the " +
                "trees. The path ends as abruptly as it started and the underbrush " +
                "take over. Behind the underbrush there is a very steep slope leading " +
                "down into a hidden cove in the Bay of Belfalas.";
   else if(TP->query_prop(REVEAL_STEP1))
      ret_str = "You are on a path having just left the ruins behind you to the west. " +
                "Looking east you have a nice view of the bay of Belfalas between the " +
                "trees. The path ends as abruptly as it started and the underbrush " +
                "take over. Behind the underbrush there is a very steep slope leading " +
                "toward the Bay of Belfalas.";
   else
      ret_str = "You are on a path having just left the ruins behind you to the west. " +
                "Looking east you have a nice view of the bay of Belfalas between the " +
                "trees. The path ends as abruptly as it started and the underbrush take over.";

   return (ret_str + sky_desc() + "\n");
}


string
slope_desc()
{
    if(!(TP->query_prop(REVEAL_STEP1) || TP->query_prop(REVEAL_STEP2) || (TP->query_guild_name_race() == GUILD_NAME)))
           return "You find no slope.\n";
    else
       return("It would be very precarious to just simply walk down, but perhaps the roots " +
              "could give some support in climbing down.\n");
}

/*
 * Function name: init
 * Description  : This function is used to add the command 'climb' to the
 *                player. 
 */
void
init()
{
    ::init();

    add_action("do_climb", "climb");
}


/*
 * Function name: do_climb
 * Description  : This function is called when the player desides to 'climb'
 *                something rather than useing the directions 'up' and 'down'.
 * Arguments    : str - whatever (s)he wants to climb.
 * Returns      : 1/0 (succes/fail)
 */
int
do_climb(string str)
{
    object tp = TP;
    int fatigue;

    if(!(tp->query_prop(REVEAL_STEP1) || tp->query_prop(REVEAL_STEP2) || (TP->query_guild_name_race() == GUILD_NAME)))
           NF0("What?\n");

    if (!strlen(str))
    {
        NF0(CAP(QVB) + " what or where?\n");
    }

    if ((parse_command(str, ({ }), " [down] [the] [steep] 'slope' ")) ||
        (str == "down"))
    {

        fatigue = tp->query_max_fatigue() / 10;

        if (tp->query_fatigue() < fatigue)
        {
            write("You are too tired to climb down the steep slope.\n");
            return 1;
        }

        tp->add_fatigue(-fatigue);
        tp->move_living("climbing down the steep slope", TOLFALAS_DIR + "room/cove02");

        return 1;
    }

    NF0("What exactly do you want to climb?\n");
}

/*
 * Function name: do_search
 * Description  : This function is called when the player desides to 'search'
 *                the undergrowth and slope.
 * Arguments    : str - whatever (s)he wants to search.
 * Returns      : 1/0 (succes/fail)
 */
string
do_search(object player, string search_what)
{
    object tp = player;

    if ((parse_command(search_what, ({ }), " [the] [dense] 'underbrush' ")) )
    {

        if (tp->query_skill(SS_AWARENESS) < 40)
        {
            tp->add_prop(REVEAL_STEP1, 1);
            return ("You scan and prod the underbrush and happen upon a steep slope " +
                   "leading towards the Bay of Belfalas.\n");
        }
        else
        {
            tp->add_prop(REVEAL_STEP2, 1);
            return ("You scan and prod the underbrush and happen upon a steep slope " +
                  "leading towards a hidden cove in the Bay of Belfalas.\n");
        }
    }
    else
       return "";
}





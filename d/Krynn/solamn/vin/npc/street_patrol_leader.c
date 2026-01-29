/* Knight patrol leader for the streets of the new Vingaard, */
/* by Morrigan 1/11/97. (Taken from Teth's Toede)            */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
#include "../local.h"
#include "../knight/guild.h"

inherit M_FILE
inherit VSTD + "vin_knight_base";
inherit AUTO_TEAM

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/d/Krynn/std/patrol";

#define DEBUG 1

#ifdef DEBUG
#define CODER   "boron"
#define TELL(x) tell_object(find_player(CODER), "\n\t* * " + x + " * *\n");
#endif

string do_attack();

void
create_knight_npc()
{
    set_level(4);
    set_act_time(7);
    set_pick_up_team(({"squire", "knight"}));
    set_patrol_time(50);
    set_patrol_path(({ "s", "s", "s", "s", "emote smiles as the sounds "+
    "of the smith working ring out from the west.","s", "e", "e", "e",
    "respect statue", "n", "s", "e", "say The food at the Inn is "+
    "most satisfying, I ate there last night.", "e", "e", "n", "n", "n",
    "n", "n", "s", "s", "s", "s", "s", "w", "w", "w", "w", "say I wasn't "+
    "sure about letting that Darren open a shop here, but he's proved "+
    "himself to be a decent man.", "w", "w", "n", "n", "n", "n", "n" }));

    add_act("@@do_attack", 0);
}

string
do_attack()
{
    int NumOfObjs; // number of objects in the inventory of our environment
    object *objs;
    object obj;
    int i;

    objs = all_inventory(environment()); // get an array of the number of objects
                                         // in the inventory of our environment
    NumOfObjs = sizeof(objs);

    for (i = 1; i <= NumOfObjs; i++)
    {
        obj = inventory(environment(), i - 1);

        if ( (obj->query_race_name() == "draconian") ||
             (obj->query_race_name() == "dragon") )
        {
            return "kattack " + obj->query_race_name();
        }
    }

    if (!random(10))
        return "pledge";
}


public void
init_living()
{
    if (interactive(TP) && TP->query_prop("_i_attacked_in_vingaard"))
    set_alarm(0.5, 0.0, "attack_func", TP);
    init_team_pickup();
    ::init_living();
}

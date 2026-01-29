/*
 * Beehive to get honey from
 * -- Finwe, December 2005
 */

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "defs.h"

inherit "/std/object";

int cuts = 0;

int do_cut(string str);

void create_object()
{
    set_name(({"hive", "beehive"}));
    set_adj("large");
    set_short("large hive");
    set_long("This is a large beehive. It hangs from a branch and is " +
        "generally egg shaped. The beehive was made by honeybees. @@hive_status@@\n");

   add_prop(OBJ_I_WEIGHT, 400);
   add_prop(OBJ_M_NO_GET,1);

}

void init()
{
    ::init();

    add_action("do_cut", "cut");
    add_action("do_cut", "slice");
}

int do_cut(string str)
{
    object *weapons, wepl, wepr, honeycomb;
    int i;

    wepr = TP->query_weapon(W_RIGHT);
    wepl = TP->query_weapon(W_LEFT);

    if(str == "honeycomb from beehive" || str == "honeycomb from hive")
    {
// are they wielding a knife?
        if(wepl->query_wt() != W_KNIFE && wepr->query_wt() != W_KNIFE)
        {
            write("You must be wielding a knife in order to do that.\n");
            return 1;
        }

        else
        {
// is there enough honeycomb left in the hive?
            if(cuts > MAX_CUTS)
            {
                write("There isn't enough honeycomb left to cut from the beehive.\n");
                return 1;
            }
            else
            {
                seteuid(getuid(TO));
                write("You carefully cut a piece of honeycomb from the beehive.\n");
                honeycomb = clone_object(OBJ_DIR + "honeycomb");
                honeycomb->move(TP,1);
                cuts = cuts + 1;
                return 1;
            }
        }
    }
}


string hive_status()
{
    switch(cuts)
    {
        case 0:
        {
            return "The beehive looks whole and undisturbed. It looks like " +
                "you may be able to cut some honeycomb from it.";
            break;
        }
        case 1..2:
        {
            return "It looks like some honeycomb has been cut from it.";
            break;
        }
        default:
        {
            return "It looks tattered and in pieces.";
            break;
        }
    }

}

/*
 * Function    : reset_hive
 * Description : This function just resets the hive so that people can do
 *               the quest again.
 * Arguments   : none
 * Returns     : nothing
 */
public void
reset_hive()
{
    cuts = 0;
}

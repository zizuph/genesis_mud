/* laundress.c
 *
 * Dry-sand laundry npc of Tyr.
 * -
 * April 2013 (Serpine) - Created  
 * ========================================================================
 */

inherit "/d/Cirath/std/monster.c";
inherit "/lib/trade";

#include "defs.h"
#include <cmdparse.h>
#include <ss_types.h>
#include <money.h>
#include <const.h>

#define NUM   4

void
create_monster()
{
    ::create_monster();    

    set_living_name("nesa");
    set_name("nesa");
    set_adj("charismatic");
    add_adj("serene");
    set_title("the wielder of the cleaning sands");
    set_race_name("mul");
    set_gender(1);
    set_long("A mul (half-dwarf) in her fourties, this powerfully " +
        "build woman wears perhaps the cleanest robes you have ever " +
        "witnessed. The dust of Athas seems to literally avoid her as " +
        "as if in fear of its very existance.\n");

    default_config_npc(75);

    set_alignment(300);

//    add_act("say So, what news from outside Tyr?");
//    add_act("emote orders some scullery maids to do their jobs.");
//    add_act("emote seems to be concentrating on something.");
//    add_act("emote smiles warmly.");
//    add_act("say Please don't make trouble. It could get...messy.");
//    add_act("say Would you like to rent a room?");
//
//    seq_new("hubba");
//    seq_addfirst("hubba",({"@@do_give"}));

//    set_act_time(6);
//    MONEY_MAKE_CC(1000)->move(TO, 1);
    config_default_trade();
}



do_launder(string str)
{
    object owner, *target;
    int *money;
    string *desc, oldname, oldnamep, newname, newnamep;
    int i;

    oldname = "";
    newname = "";
    oldnamep = "";
    newnamep = "";

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("growl");
        command("say You are wasting my time. Show yourself.\n");
        return 1;
    }

    target = FIND_STR_IN_OBJECT(str, TP);

    if (sizeof(target) == 0)
    {
        command ("say You don't have that.");
        return 1;
    }

    if (sizeof(target) != 1)
    {
        command ("say Not sure which one.");
        return 1;
    }

    oldname = (target[0]->short());
    desc = explode(oldname," ");
    for (i=0; i < sizeof(desc); i++)
    {
        if (desc[i] == "smelly" || desc[i] == "soiled" || desc[i] == "dirty" )
        {
        }
        else
        {
            if (newname == "")
            {
                newname = desc[i];
            }
            else
            {
                newname = newname + " " + desc[i];
            }
        }
    }
    if (newname != "")
    {
        target[0]->add_adj("clean");
        target[0]->remove_adj("dirty");
        target[0]->remove_adj("soiled");
        target[0]->remove_adj("smelly");
        target[0]->set_short("clean "+newname);
    }

    oldnamep = (target[0]->query_plural_short());
    if (oldnamep != 0)
    {
        desc = explode(oldnamep," ");
        for (i=0; i < sizeof(desc); i++)
        {
            if (desc[i] == "smelly" || desc[i] == "soiled" || desc[i] == "dirty" )
            {
            }
            else
            {
                if (newnamep == "")
                {
                    newnamep = desc[i];
                }
                else
                {
                    newnamep = newnamep + " " + desc[i];
                }
            }
        }
        if (newnamep != "")
        {
            target[0]->add_adj("clean");
            target[0]->remove_adj("dirty");
            target[0]->remove_adj("soiled");
            target[0]->remove_adj("smelly");
            target[0]->set_pshort("clean "+newnamep);
        }
    }

    return 1;
}



void
init_living()
{
    ::init_living();
    add_action("do_launder", "launder");
}



query_knight_prestige()
{
    return(-4);
}

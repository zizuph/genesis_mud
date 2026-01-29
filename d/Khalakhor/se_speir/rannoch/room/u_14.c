/* File         : /d/Khalakhor/se_speir/rannoch/room/s_09.c
 * Creator      : Darragh@Genesis
 * Date         : 01-04-02         
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "room.h"

inherit "/d/Khalakhor/std/room";
inherit HERBSEARCH;

int jump_down();

int
jump_down()
{

    int d_stat = TP->query_base_stat(SS_DEX);
    int dx_stat = TP->query_base_stat(SS_DIS);

    if (d_stat <= 84)
    {
        write("You feel that you lack the courage needed "
            + "to jump down.\n");

        return 1;
    }
    else 
    {
        if (dx_stat >= 150)
        {

            write("Feeling confident, you gracefully jump down from "
                + "the cliff and land perfectly on the ground below.\n\n");

            TP->move_living("jumping off the cliff and down into the "
                          + "forest below. Soon afterwards you hear a soft "
                          + "thud, indicating that " + HE + " managed "
                          + "to land on " + HIS + " feet",
                             ROOM + "w_11",1,0);

            return 1;
        }
        else
        {

            write("Feeling confident, you jump down from the cliff "
                + "and land on the ground below, rather clumsily.\n\n");

            TP->move_living("jumping down the cliff and into the forest "
                          + "below. Soon afterwards you hear a crashing "
                          + "sound, indicating that " + HIS + " landing "
                          + "did not go that well",
                             ROOM + "w_11",1,0);

            return 1;
        }
    }
}

void
create_add_items()
{

    add_cmd_item(({"down","cliff"}),
                   "jump",
                    jump_down);

    add_cmd_item(({"down","cliff"}),
                   "climb",
                   "It does not look possible to climb down the "
                 + "cliff here. But the ground below seems to be "
                 + "clear of rocks, maybe you could jump down "
                 + "there.\n");

    add_exit(ROOM + "t_14.c","north",0,1,0);
}

public void
create_khalakhor_room()
{

    set_short("Another room");
    set_long("Bläh.\n");

    create_add_items();

}

/* rd_pr_03: Promenade section 3: Serpine, 12-04-96 */
 
inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    if (leader) return;
    bring_room_team(TYR_NPC+"tmpl_mid.c", 1, 2, TYR_NPC+"hgiant.c", 1); 
    leader->set_random_move(20);
    leader->set_restrain_path(TYR_NOBLE);
    leader->set_monster_home(TYR_NOBLE+"rd_pr_03");
}
 
void
create_room()
{
    ::create_room();
    set_short("south end of the Promenade");
    set_long("Once planned to be a bustling trade lane with shops "
            +"on either side, this end the road called the Promenade "
            +"has instead become an extention of a noble's property. "
            +"Stately rows of imported trees line the edges of the "
            +"path, shaded by hide tarps. Every so often a slave runs "
            +"up to water a plant, then just as swiftly is gone "
            +"into the well-appointed manor due south.\n");
 
    add_item("slave", "None of the slaves stays long enough to "
            +"be of note.\n");
 
    add_item(({"tree", "trees", "imported trees", "imported tree", "plant"}),
             "They were probably shipped all the way from Gulg or "
            +"Nibenay, which would have cost enough to keep a small "
            +"Trading House in business for a full year.\n");
 
    add_item(({"tarp","hide tarp","tarps","hide tarps"}),
             "A hundred Erdlu probably were skinned to supply this "
            +"much hide.\n");
 
    add_item("manor","Not spectacular, but relatively large.\n");
 
    OUTSIDE
    ADD_SUN_ITEM;
 
    add_exit(TYR_NOBLE+"rd_pr_02.c", "north", "@@roof_message", 1);
    add_exit(TYR_NOBLE+"house8.c", "south", 0, 1);

    reset_room();
}
 
public int
roof_message()
{
    TP->catch_msg("The temperature increases as you "
                 +"enter the shade of the Great Roof.\n");
    return 0;
}

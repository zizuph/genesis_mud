/* rd_ds_04: South eastern section of Diamond Street, 10/17/95. */
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"
 
void
reset_room()
{
    if (leader) return;
    bring_room_team(TYR_NPC+"tmpl_mid.c", 1, 2, TYR_NPC+"hgiant.c", 1); 
    leader->set_random_move(20);
    leader->set_restrain_path(TYR_SLAVE);
    leader->set_monster_home(TYR_SLAVE+"rd_ds_04");
}
 
void
create_room()
{
    set_short("diamond Street southeast");
    set_long("Diamond Street gradually bends from northwest to south, "
            +"skirting the western wall of the slave pens of Tyr. The "
            +"recent upswing in effort to build the mighty Ziggurat has "
            +"called for an expansion of the pits and the number of those "
            +"forced to dwell within. A terrible stench drifts down from "
            +"over the wall: Judging from the tortured moans this "
            +"must be near the pits reserved for disobedient slaves.\n");
 
    add_item(({"pits", "slave pits", "pit", "slave pit"}),
             "You can't see them over the wall: Be happy.\n");
    add_item(({"wall", "western wall"}), "The wall is over 20 feet "
            +"high, with guard towers at each corner.\n");
    add_cmd_item(({"moans", "to moans"}), "listen", "You hear the "
            +"cries of the doomed, begging for freedom.\n");
    add_cmd_item(({"stench", "terrible stench"}), "smell",
             "It smells like excrement and vermin in a stew pot.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_SLAVE+"rd_ds_03.c", "northwest", 0, 1);
    add_exit(TYR_SLAVE+"rd_tr_02.c", "south", 0, 1);

    reset_room();
}

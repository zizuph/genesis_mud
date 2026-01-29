/* rd_hr_01: High road section 1. */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("half-giant", TYR_NPC+"hgiant.c", 1, 1);
}

void
create_room()
{
    set_short("south high road");
    set_long("While only yards away from Caravan Gate to the south, the "+
             "begining of the High Road is remarkably quiet. In addition "+
             "to regularly posted guards, a clever network of large "+
             "desert plants and cunningly laid walls absorb the noise "+
             "before it can offend the dainty ears of Tyr's noble elite. "+
             "Even then, none make their homes this close to the main "+
             "road, prefering to live further northeast.\n");

    add_item(({"walls", "wall"}), "It must have taken many years to have "+
             "devised the positioning of the sound barrier; years and "+
             "huge amounts of currency.\n");
    add_item(({"plants", "plant", "desert plants", "desert plant"}), "In "+
             "addition to being functional as a curtain against sound "+
             "and dust, they are pleasing to the eye and nose: Just as "+
             "nobles prefer it.\n");
    add_item(({"caravan gate", "gate"}), "You can't even see it through "+
             "the shrubs and walls, but it probably is there somewhere.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_CARAVAN+"rd_cw_01.c", "south", "@@check_guard", 1);
    add_exit(TYR_NOBLE+"rd_hr_02.c", "northeast", "@@check_guard", 1);

    reset_room();
}

public int
check_guard()
{
    object guard = present("half-giant", TO);
    if(objectp(guard))
        TP->catch_msg(QCTNAME(guard) + " glares at you as you pass.\n");
    return 0;
}

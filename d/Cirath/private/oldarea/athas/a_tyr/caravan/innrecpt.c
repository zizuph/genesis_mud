/* innrecpt: Place to buy room keys in Golden Inix Inn */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("mila", TYR_NPCS+"rcptnist.c", 1);
}

void
create_room()
{
    set_short("reception desk");
    set_long("Little more then a closet with a small stone desk and flimsy "+
             "wooden staircase leading up, this appears to be where one "+
             "can rent a room to stay overnight in the Golden Inix Inn.\n");

    add_item("staircase", "The wood is low quality but should support the "+
             "weight of non half-giants.\n");

    add_item("desk", "The symbol for 1 gold coin exact is scratched into it.\n");

    INSIDE

    add_exit(TZ_CARAVAN+"innlobby.c", "east", 0, 1);
    add_exit(TZ_CARAVAN+"innroom.c", "up", "@@block", 1);

    reset_room();
}

block()
{
    if(!(present("_tyr_room_key_",TP)))
    {
        write("Your head nearly explodes as a psionic barrage strikes it. "+
              "A voice in your head says 'You lack a key fool!'\n");
        say(QCTNAME(TP)+" attempts to climb the stairs, but stumbles back "+
              "clutching their head.\n");
        return 1;
    }
    return 0;
}

inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("a dining room");
    set_long(BSN("You are in a dining room. There are a table in the "
        + "middle of the room with several chairs around it. By the "
        + "west wall there is a large cabinet. By the south wall there "
        + "is a stove and a cupboard."));
    add_item(({"table"}),BSN("It is a sturdy oak table that looks as if "
        + "is was as good as new. There are two plates set on the table "
        + "and two coups."));
    add_item(({"chair","chairs"}),BSN("The chair looks inviting and "
        + "comfortable. They are all made of redwood.\n"));
    add_item(({"cabinet"}),BSN("It is a plain cabinet with no special "
        + "features."));
    add_item(({"plate","plates"}),BSN("The plate is made out of tin."));
    add_item(({"coup","coups"}),BSN("The coup's are made in some kind of "
        + "wood. They look like they are well used."));
    add_item(({"stove"}),BSN("The stove is made of cast iron and is "
        + "cold."));
    add_item(({"cabinet"}),BSN("It is a rather large cabinet, it does "
        + " not look like it is anything useful in it."));
    add_item(({"cupboard"}),BSN("It is a normal cupboard, and "
        + "it is empty."));
    add_exit(EDORAS_DIR + "houses/ed_house1","east",0);
    add_exit(EDORAS_DIR + "houses/house1r2","north",0);

    add_prop(ROOM_I_INSIDE,1);
    add_monster();

}

void
    add_monster()
{
    clone_object(EDORAS_DIR + "npc/houseman")->move(TO);
}

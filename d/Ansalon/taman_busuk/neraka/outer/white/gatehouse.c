/* Ashlar, 11 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include ARND_MEET
#include <stdproperties.h>
#include <macros.h>

inherit OUTER_IN;

object g1,g2,g3;

void
reset_neraka_room()
{
    if (!objectp(g1))
        g1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"white");
    if (!objectp(g2))
        g2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"white");
    if (!objectp(g3))
        g3 = clone_npc(NNPC + "humsergeant","white");
}

void
create_neraka_room()
{
    set_short("inside the gatehouse");
    set_long("You are standing in the gatehouse, a large room within " +
        "the city wall. A doorway to the west leads out, and a " +
        "circular staircase leads up. Two large tables surrounded with " +
        "chairs are the only pieces of furniture in the room. A large " +
        "fireplace adds warmth and light to the room.\n");

    add_item_inside();
    add_item(({"table","tables","large table","large tables"}),
        "The tables are made of sturdy wood, and are scratched and nicked " +
        "all over.\n");
    add_item(({"chair","chairs"}),
        "Hard wooden chairs are placed around the tables.\n");
    add_item(({"fireplace","large fireplace"}),
        "The large fireplace is set in the southeastern wall. A fire is " +
        "blazing in it.\n");
    add_item("fire","The fire is blazing away in the fireplace.\n");

    add_prop(OBJ_I_HAS_FIRE, 1);

    add_exit(NOUTER+"white/w7","west");
    add_exit(NOUTER+"white/abovegate","up", "@@go_up");

    reset_room();
}

int
go_up()
{
    object g;
    g = g3;
    if (!objectp(g) || (E(g) != TO))
        g = g2;
    if (!objectp(g) || (E(g) != TO))
        g = g1;
    
    if (!TP->query_npc() && g && (E(g) == TO) && (CAN_SEE(g,TP) && CAN_SEE_IN_ROOM(g)))
    {
        write("The " + g->short() + " stops you from going up.\n");
        return 1;
    }
    else
    {
        write("You ascend the staircase.\n");
        return 0;
    }
}

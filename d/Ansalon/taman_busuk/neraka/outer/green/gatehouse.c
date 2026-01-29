/* Carridin */

/* Navarre 25th June 2006, Changed room description
 * to match with the exit, it said southeast exit in 
 * the long, when it was actually southwest.
 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include ARND_MEET
#include <stdproperties.h>

inherit OUTER_IN;

object g1,g2,g3;

void
reset_neraka_room()
{
    if (!objectp(g1))
        g1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"green");
    if (!objectp(g2))
        g2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"green");
    if (!objectp(g3))
        g3 = clone_npc(NNPC + "humsergeant","green");
}

void
create_neraka_room()
{
    set_short("Inside the gatehouse");
    set_long("You are standing in the gatehouse, a large room within " +
        "the city wall. A doorway to the southwest leads out, and a " +
        "circular staircase leads up. Two large tables surrounded with " +
        "chairs are the only pieces of furniture in the room. A large " +
        "fireplace adds warmth and light to the room.\n");
    set_quarter(GREEN);

    add_item_inside();
    add_item(({"staircase","circular staircase"}),
        "The staircase is made of smooth stones, and leads up.\n");
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

    add_exit(NOUTER+"green/g7","southwest");
    add_exit(NOUTER+"green/abovegate","up", "@@go_up");

    reset_room();
}

int
go_up()
{
    object g;
    g = g3;
    if (!objectp(g))
        g = g2;
    if (!objectp(g))
        g = g1;
    
    if (g && !(NERAKA_ADMIN)->query_may_enter_city(TP,g,1))
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

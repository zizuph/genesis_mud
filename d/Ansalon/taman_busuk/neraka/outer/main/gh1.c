/* Ashlar, 19 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include <stdproperties.h>

inherit OUTER_IN;

object g1,g2,g3,giant,troll1,troll2;

#define SGUARD(x)   (x)->add_prop(  "_neraka_is_main_gate_guard", 1)
#define QGUARD(x)   (x)->query_prop("_neraka_is_main_gate_guard")
#define DEBUG(x)    (find_player("ashlar")->catch_msg("GH1: " + x + "\n"))

void
reset_neraka_room()
{
    if (!objectp(g1))
    {
        g1 = clone_npc(NNPC + "cityguard");
        SGUARD(g1);
    }
    if (!objectp(g2))
    {
        g2 = clone_npc(NNPC + "cityguard");
        SGUARD(g2);
    }
    if (!objectp(g3))
    {
        g3 = clone_npc(NNPC + "cityguard");
        SGUARD(g3);
    }
    if (!objectp(giant))
    {
        giant = clone_npc(NNPC + "hillgiant","black");
        SGUARD(giant);
    }
    if (!objectp(troll1))
    {
        troll1 = clone_npc(NNPC + "troll");
        SGUARD(troll1);
    }
    if (!objectp(troll2))
    {
        troll2 = clone_npc(NNPC + "troll");
        SGUARD(troll2);
    }
}

void
create_neraka_room()
{
    set_short("Inside the gatehouse");
    set_long("You are standing in the gatehouse, a large room within " +
        "the city wall. A doorway to the northwest leads out. " +
        "Two large tables surrounded with " +
        "chairs are the only pieces of furniture in the room.\n");

    add_item_inside();
    add_item(({"table","tables","large table","large tables"}),
        "The tables are made of sturdy wood, and are scratched and nicked " +
        "all over.\n");
    add_item(({"chair","chairs"}),
        "Hard wooden chairs are placed around the tables.\n");

    add_exit(NOUTER+"main/r1","northwest");

    reset_room();
}

void
do_assist(object ob)
{
    ob->command("assist guard");
    ob->command("assist gate_guard");
    ob->command("assist second gate_guard");
}

void
extra_defences()
{
    object *g;
    int i,sz;

    DEBUG("extra defences..");
    g = all_inventory(TO) + all_inventory(find_object(NOUTER+"main/r1"));
    sz = sizeof(g);
    for(i=0; i<sz; i++)
    {
        if ((!QGUARD(g[i])) || !random(5))
            continue;
        if (E(g[i]) == TO)
            g[i]->command("nw");
        set_alarm(itof(random(20))/10.0+1.0,0.0,
            &do_assist(g[i]));
    }
}


/*
 * Cabin on the Ergothian galleon. Holds treasure!
 * 
 */
 
#include "../local.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include <composite.h>
#include <filter_funs.h>
#include <money.h>

inherit R_FILE

void set_exit(string exit_name);

object chest, money1, money2, money3;

void
reset_krynn_room()
{
    if(!objectp(chest))
    {
        chest = clone_object(TOBJ + "strongbox");
        chest->move(TO, 1);
    }

    if(!present(money1, chest))
    {
        money1 = MONEY_MAKE_GC(random(30));
        money1->move(chest, 1);

        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }

    if(!present(money2, chest))
    {
        money2 = MONEY_MAKE_PC(random(10));
        money2->move(chest, 1);

        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }

    if(!present(money3, chest))
    {
        money3 = MONEY_MAKE_SC(random(100));
        money3->move(chest, 1);

        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }

}

void
create_krynn_room() 
{

    set_short("Inside a cabin used for storage");
    set_long("You stand inside a quite spacious cabin aboard " +
        "a royal Ergothian galleon. The room is richly furnished, " +
        "and seems to be used to store their most valuable of " +
        "cargo. At the end of the " +
        "cabin is a large window overlooking the vast ocean " +
        "outside. A doorway leads back out to the main deck.\n");
            
    add_item(({"window", "ocean", "vast ocean"}),
        "From here you have a splendid view of the surrounding ocean.\n");            
    add_item("cabin",
        "It looks like it is used to store the most valuable " +
        "of the ship's cargo.\n"); 
    add_item("view",
        "No land in sight. No nothing in sight. Only water.\n"); 
    add_item("doorway",
        "You can see most of the main deck from here. \n");               
    add_item(({"deck", "main deck"}),
        "You see nothing special about it. \n");                
     add_item(({"ship", "warship"}),
         "Everything on this ship seem to have been very " +
         "carefully designed. \n");               

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);

    reset_krynn_room();
}

void set_exit(string exit_name)
{
    remove_exit("out");
    add_exit(exit_name, "out", 0, 1);
}

void clean_loot()
{
    cleanup_loot();
}
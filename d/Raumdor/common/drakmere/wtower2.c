/*     Created by:      Sarr
 *     purpose:		
 *     Location:         
 *     Modified:        Toby, 97-09-17 (fixed typos)
 */
#include "defs.h"
inherit STD_ROOM;

object guard;
object guard2;
object guard3;
object guard4;

void reset_room();

void
create_room()
{
    ::create_room();
    set_short("Inside the west guard tower");
    set_long("You are now with at the top of the guard tower. You can "+
    "see out all around you the countryside of Raumdor. The guards walk "+
    "around, patrolling the walls. The gatehouse is below you to the "+
    "west.\n");
    add_item("countryside","Plains mostly, but you do see some high "+
    "hills and small rock mountains.\n");
    add_item("gatehouse","Where people enter the city.\n");
    add_exit(DRAKMERE_DIR + "wtower","down",0);
    reset_room();
}

void
reset_room()
{
    if(!guard)
    {
        guard = clone_object(DRAKMERE_NPC_DIR + "dguard_s");

        guard->move_living("xxx",TO);
    }
    if(!guard2)
    {
        guard2 = clone_object(DRAKMERE_NPC_DIR + "dguard_s");

        guard2->move_living("xxx",TO);
    }
    if(!guard3)
    {
        guard3 = clone_object(DRAKMERE_NPC_DIR + "dguard_s");

        guard3->move_living("xxx",TO);
    }
    if(!guard4)
    {
        guard4 = clone_object(DRAKMERE_NPC_DIR + "dguard_s");

        guard4->move_living("xxx",TO);
    }

}

int *
query_coordinates()
{
    return ({61, 3, 1});
}

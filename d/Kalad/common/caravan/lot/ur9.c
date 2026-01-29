#include "../default.h"
inherit CVAN_ROOM;

#include <filter_funs.h>

#define KCOUNT 4
object *knights;

void reset_room();

void create_cvan_room()
{
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A hallway in the underground lair");
    set_long("You are travelling down a hallway.\n"+
      "This is a grand hallway, built entirely of sturdy, stone blocks. "+
      "Lining the side walls are rows of stands where several torches have "+
      "been placed. Lit passages lead towards the west and east from here.\n");

    add_item(({ "walls", "wall" }),
      "The walls, along with the rest of the passageway are made entirely "+
      "of solid granite blocks, mortared together to provide additional "+
      "support.\n");

    add_item(({ "torches" }),
      "Standard torches, the kind you find in your general store. They have "+
      "been mounted on torch stands which line the side walls of this "+
      "hallway.\n");

    add_item(({ "stands" }),
      "They line the hallway and currently have torches mounted on them.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur7", "west");
    add_exit(CVAN + "lot/ur11", "east");

    clone_object(CVAN + "door/urdoor")->move(TO);
    clone_object(CVAN + "door/urdoor6")->move(TO);

    reset_room();
}


void reset_knights()
{
    int i;
    knights = ({ });
    for (i=0; i < KCOUNT; i++)
        knights += ({ 0 });
}
/* updated to use cycle rather than manual things,
 * and move() instead of move_living(). 11:24 2004-09-11 Dargoth
 */
void reset_room()
{
    int i;

    if (sizeof(knights) < KCOUNT)
        reset_knights();
    
    for (i=0; i< KCOUNT; i++)
    {
        if (objectp(knights[i]))
            continue;
        knights[i]=clone_object(NPC + "lknight2");
        knights[i]->move(TO,1);
        knights[i]->arm_me();
    }
    
    for (i=1; i< sizeof(knights); i++)
        knights[0]->team_join(knights[i]);

	tell_room(TO, "Several killer knights of Thanar arrive at "
    +"their guard posts.\n");
}

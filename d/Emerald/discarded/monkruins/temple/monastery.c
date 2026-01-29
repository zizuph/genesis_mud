inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
static object *monks=allocate(3);
static object leader;
 
void
reset_room()
{
    int i=sizeof(monks);
 
    if (!leader)
         {
           leader = clone_object(TEMPLE_DIR + "npc/monk2");
           leader->arm_me();
           leader->move_living("into a room", this_object());
         }
    for (i=0 ; i<4 ; i++)
      if (!monks[i])
       {
         monks[i]=clone_object(TEMPLE_DIR + "npc/monk");
         monks[i]->arm_me();
         monks[i]->move_living("into a room", this_object());
         leader->team_join(monks[i]);
       }
}
 
void
create_room()
{
    object door;
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Monastery hallway");
	set_long("   You are standing in the monestary hallway, " +
	"which continues north and south from here.\n\n");
 
    add_exit(TEMPLE_DIR + "dungeon1", "north", 0);
    add_exit(TEMPLE_DIR + "quarters", "south", 0);
 
    door=clone_object(TEMPLE_DIR + "doors/door2_b");
    door->move(this_object());
 
    set_alarm(1.0,0.0,reset_room);
}

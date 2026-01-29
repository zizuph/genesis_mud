/* /d/Krynn/common/warfare/conquer_base.c
 *
 * Base of all rooms which belong to a conquerable area
 * 
 * Inherit this file in addition to the standard room base.
 * If you have an area, it is best to inherit this file once
 * into the baseroom of the area, and make the entire area
 * conquerable in one go.
 * 
 * Copyright by Hans Breckle (Aridor)
 * 03/99
 *
 * Modification history:
 * 21.2.2000 by Milan
 * Modified set_area_name(). First Check if there is defined area of that name.
 */

#include "local.h"

string gAreaName = 0;
int gNpcsThisRoom = 1; /* Max number of npcs in this room */
int gNpcChance = 10;   /* 1 in <gNpcChance> (2 in this case) resets will
			* actually clone an npc (50% chance in this case).
			*/
object* gNpc = ({});
int gRoomRegistered = 0;

varargs void
set_num_npc(int i=0)
{
    gNpcsThisRoom = i;
}

varargs void
set_npc_chance(int i=2)
{
    gNpcChance = i;
}

void
my_reset()
{
    this_object()->reset_room();
}

void
set_area_name(string str)
{
    int rooms, chance;
    float tmp;

    if (!ARMYMASTER->query_area(str))
    {
	log_file("armymaster",
		 ctime(time())[4..15] + " Error in set_area_name: " + 
		 file_name(this_object()) + ". Area: " + str + "\n");
	return;
    }

    gAreaName = str;
    if (gRoomRegistered)
      return;
    ARMYMASTER->register_room(gAreaName);
    gRoomRegistered = 1;
    rooms = ARMYMASTER->rooms_in_area(gAreaName);
    if (rooms <= 10)
      rooms = 10;

    /* the number of rooms which actually have npcs in it depends on the
     * number of rooms in the area. We go by a logarithmic scale here,
     * so that huge areas will not clone an incredible amount of npcs.
     * The max numbers are approximately as follows:
     * Number of rooms         Max npcs until full      (Before change)
     *     27                         12                      12
     *     79                         22                      33
     *    396                         39                     168
     *    503                         41                     215
     *
     * Numbers:
     * 3*rooms:   3 is the average number of npcs per room. If changed below, adjust here.
     * 20*ftoi(): 20 is the linear scale of the npc numbers. Adjust this number after
     *            changing the number below.
     * rooms/10:  10 is the log scaling, which is responsible for the distribution between
     *            lowest and highest value for different room numbers
     */
    tmp = 20.0*log(itof(rooms/10));
    if (tmp <= 1.0)
      tmp = 1.0;
    chance = ftoi(3.0*itof(rooms)/tmp);

    /* initialize the number of npcs for this room */
    if (gNpcsThisRoom == 1 && gNpcChance == 10)
    {
	/* 2+random(3) is the average number of npcs per room (currently 3). If this
	 * number is changed, adjust the number above in the chance calculation also.
	 */
	set_num_npc(random(chance) ? 0 : 2 + random(3));
	set_npc_chance(2);
    }

    set_alarm(0.0,0.0,my_reset);
    set_alarm(0.1,0.0,my_reset);
    set_alarm(0.2,0.0,my_reset);
    set_alarm(0.3,0.0,my_reset);
    set_alarm(0.4,0.0,my_reset);
    set_alarm(0.5,0.0,my_reset);
}

string
query_area_name()
{
    return gAreaName;
}

int
conquer(string str)
{
    if (gAreaName == 0)
    {
      notify_fail("What?\n");
      return 0;
    }
    if (!str || (str != "area" && str != "this area"))
    {
      notify_fail("Conquer what? This area?\n");
      return 0;
    }

    return ARMYMASTER->conquer(this_player(),gAreaName);
}

int
check_area(string str)
{
    if (str != "area")
      return 0;

    if (gAreaName == 0)
    {
      write("You do not recognize this area.\n");
    }
    else
    {
      write("You recognize this area as "+gAreaName+".\n");
    }
    return 1;
}


void
init_conquer()
{
#ifdef WARFARE_ENABLED
    add_action(conquer,"conquer");
    add_action(check_area,"exa",1);
#endif /* WARFARE_ENABLED */
}

void
npc_killed(string npc)
{
    ARMYMASTER->npc_killed(gAreaName,npc);
}


void
reset_conquer_room()
{
    object ob;
    int rooms;

    if (!gAreaName)
      return;

    if (!gNpc)
      gNpc = ({});
    gNpc -= ({ 0 });

    rooms = ARMYMASTER->rooms_in_area(gAreaName);
    if (!random(8 * rooms))
      /* it should take approx 12 hours before the Free People
       * conquer a room back. 8*1.5hours = 12 hours
       */
      ARMYMASTER->conquer_area(gAreaName,"Free People",1);

    if (sizeof(gNpc) >= gNpcsThisRoom)
      return;
    
    if (random(gNpcChance))
      return;
    
    ob = ARMYMASTER->clone_new_npc(gAreaName);
    if (ob)
    {
	ob->move_living("M",this_object());
	gNpc += ({ ob });
    }
}

/* Redefine this function in your room if you need to do something
 * at the change of occupants.
 */
void
area_conquered(string newarmy, string oldarmy)
{
    
}

/* This function is called by the armymaster whenever an area has changed
 * it's owner. We check if the room belongs to the area, ignore it if not.
 * Otherwise, call the local update function.
 */
void
conquer_update(string area, string newarmy, string oldarmy)
{
    if (area != gAreaName)
      return;

    /* Remove all local npcs which might have been left over */
    gNpc->command("emote retreats as the sound of a horn echoes through the area.");
    gNpc->remove_object();
    gNpc -= ({ 0 });

    this_object()->area_conquered(newarmy, oldarmy);
}

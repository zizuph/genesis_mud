#include "/d/Ansalon/common/defs.h"

inherit "/std/room.c";

#define CITADEL_IS_MOVING_HIGH  "citadel_is_moving_high_"
#define CITADEL_IS_MOVING       "citadel_is_moving_"
/* The Flying Citadel, by Sarr */

static object piolet_room;
object current_room;
int altitude;
string curr_dir;

/* Prototypes */

int set_citadel_altitude(int i); /* The range is from 1-3, returns 0 if out of range */
int set_citadel_direction(string s); /* Set the current direction, returns 1 if set, 0*/
                                    /* if it was not */
string query_current_dir();
int stop_citadel(); /* Return 1, if we stoped. If we can't stop at this moment, */
                   /* return 0 */
int set_current_room(object room); /* Set the current room we are in as the room. */
object query_current_room(); /* Give us the current room */

string *possible_citadel_predests(); /* Listing of pre-set destinations */
float calculate_time_distance(string from_domain, string do_domain);
             /* Calculate the time it takes to get from predests, like a boat */

string *
possible_citadel_predests()
{
    string *c_dests;
    c_dests = ({"Sarr's Workroom","/d/Ansalon/sarr/workroom",
                "Teth's Workroom","/d/Krynn/teth/workroom",
                "Skaro's Workroom","/d/Kalad/skaro/workroom",
                "Arman's Workroom","/d/Ansalon/arman/workroom" });
    return c_dests;
}

float 
calculate_time_distance(string from_domain, string to_domain)
{
    return 20.0;
}

void
create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE,1);
    if(!piolet_room)
    {
        call_other("/d/Ansalon/taman_busuk/neraka/citadel/pioletr","??");        
        piolet_room = find_object("/d/Ansalon/taman_busuk/neraka/citadel/pioletr");
    }
}

object
query_piolet_room()
{
    return piolet_room;
}

int
query_citadel_altitude()
{
    return altitude;
}

int
set_citadel_altitude(int i)
{
    if(TO != piolet_room)
        return 0;
    if(i < 1 || i > 3)
        return 0;
    altitude = i;
    return 1;
}

int
set_citadel_direction(string dir)
{
    if(TO != piolet_room)
        return 0;
    curr_dir = dir;
    return 1;
}

string 
query_current_dir()
{
    return curr_dir;
}

int
stop_citadel()
{
    if(TO != piolet_room)
        return 0;
    if(query_prop(CITADEL_IS_MOVING_HIGH)) /* Can't stop in high mode */
        return 0;
    if(query_prop(CITADEL_IS_MOVING))
    {
        remove_prop(CITADEL_IS_MOVING);
        return 1;
    }
    else
        return 2; /* We were already stopped */
}


int
set_current_room(object croom)
{
    if(TO != piolet_room)
        return 0;
    current_room = croom;
    return 1;
}

object
query_current_room()
{
    if(TO != piolet_room)
        return piolet_room->query_current_room();
    else
        return current_room;
}


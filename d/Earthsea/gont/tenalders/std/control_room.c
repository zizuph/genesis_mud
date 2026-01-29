/*
*  coded by Amelia 12/15/97
*  control room for ambushes and
*  for quest herb locations
*/

inherit "/d/Earthsea/std/room";

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#define ON 1
#define OFF 0
#define AMBUSHES 60
#define CONTROL_NUM 15
int *ambush_flags = allocate(AMBUSHES);
int flag;

void
create_earthsea_room()
{
    int i = CONTROL_NUM;
    int j = AMBUSHES;

    set_short("Control Room Central");
    set_long(BS("This is a very bare room. One wall "+
	"has a set of switches and blinking lights.  It "+
	"looks like a control room.\n", 70));
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);

    // which meadow room in High Fall in Tenalders will have 4-leaf clover
    flag = random(4);

    //init ambush_flags to all OFF

    while (j--)
    {
	ambush_flags[j] = OFF;
    }

    // turn CONTROL_NUM of random rooms on for ambushes
    while (i--)
    {
	ambush_flags[random(AMBUSHES)] = ON;
    }


    reset_room();
    add_exit("/d/Earthsea/amelia/workroom", "up");

}

int
query_clover_room()
{
    return flag;
}

int
query_ambush_flags(int x)
{
    if (x <= AMBUSHES)
	return ambush_flags[x];

    //ELSE (error)
    return 0;
}


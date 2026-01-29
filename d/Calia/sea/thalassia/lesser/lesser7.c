
/* 	Lesser Zone of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define CITIZENS 5
#define GUARDS   5

inherit "/d/Calia/std/water_room";
object *guard = allocate(GUARDS);
object *citizen = allocate(CITIZENS);

void
make_guard(int i)
{
    guard[i] = clone_object(SEA_CREATURES+"tin_triton");
    guard[i]->equip_me();
    guard[i]->move(TO);
    tell_room(TO, QCTNAME(guard[i]) + " arrives.\n");
}

void
make_citizen(int j)
{
    citizen[j] = clone_object(SEA_CREATURES+"thalassian_swimming_triton");
    citizen[j]->move(TO);
    tell_room(TO, QCTNAME(citizen[j]) + " arrives.\n");
}

void
reset_room()
{
    int i,j;

    for (i=0; i < GUARDS; i++)
    {
        if (!guard[i])
            set_alarm(0.5, 0.0, &make_guard(i));
    }

    for (j-0; j < CITIZENS; j++)
    {
        if (!citizen[j])
            set_alarm(0.5,0.0,&make_citizen(j));
    }
}

void
create_water_room()
{
    set_short("Lesser Zone of Thalassia");
    set_long("You are swimming around in the Lesser Zone of "+
        "Thalassia. This is the second largest area of the "+
        "entire city and is almost entirely decorated with "+
        "white marble and silver. There are roads leading off to "+
        "the northwest, east and southeast. Surrounding "+
        "you on the southern side you see the silver wall that "+
        "encompasses the entire Lesser Zone. It shines brightly "+
        "in the light making everything around it almost glow.\n");

    add_item(({"wall","silver wall","southwest","southeast",
        "southwest wall","southeast wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Lesser Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northwest, east and southeast.\n");

    add_swim_exit(THALL+"lesser8","northwest",0,1);
    add_swim_exit(THALL+"lesser2","east",0,1);
    add_swim_exit(THALL+"lesser1","southeast",0,1);
    set_alarm(1.0,0.0,"reset_room");
}

public int
clean_up()
{
    int i,j;

    for (i=0; i < GUARDS; i++)
    {
        if (guard[i])
            return 1;
    }

    for (j=0; j < CITIZENS; j++)
    {
        if (citizen[j])
            return 1;
    }

    remove_object();
}

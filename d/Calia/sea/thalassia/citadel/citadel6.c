
/* 	Citadel in Thalassia

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
    guard[i] = clone_object(SEA_CREATURES+"ori_triton");
    guard[i]->equip_me();
    guard[i]->move(TO);
    tell_room(TO, QCTNAME(guard[i]) + " arrives.\n");
}

void
make_citizen(int j)
{
    citizen[j] = clone_object(SEA_CREATURES+"thalassian_swimming_mermaid");
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

    for (j=0; j < CITIZENS; j++)
    {
        if (!citizen[j])
            set_alarm(0.5,0.0,&make_citizen(j));
    }
}

void
create_water_room()
{
    set_short("Citadel of Thalassia");
    set_long("You are swimming around in the citadel of "+
        "Thalassia. Definately the richest area of the "+
        "entire city, it is almost entirely decorated with "+
        "white marble and gold, as well as a fiery material "+
        "known as orichalcum. There are roads leading off to "+
        "the north, south, northeast and southeast. To the east you "+
        "you see the entrance to the hot water spring house. To the "+
        "west you see the bridge leading out of the citadel into the "+
        "lesser zone. In the centre of the bridge looms the guard "+
        "tower. Northwest and southwest you see the orichalcum wall "+
        "that surrounds the entire citadel. It sparkles like fire in "+
        "the lights.\n");

    add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the west into the lesser zone of the city. In the very centre "+
        "of the bridge sits the three storey guard tower.\n");

    add_item(({"wall","orichalcum wall"}),"This fiery metal surrounds the "+
        "wall that encompasses the entire citadel, except where the "+
        "bridges pass through it. When the light hits it, the metal almost "+
        "seems as though it is on fire.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the north, south, northwest and southeast.\n");

    add_item(({"house","spring house","hot water spring house"}),
        "To the east you see the entrance to the hot water spring house, "+
        "which houses the magical hot water spring that was granted to "+
        "the citizens of this city by Lord Diabrecho himself.\n");

    add_swim_exit(THALC+"citadel7","north",0,1);
    add_swim_exit(THALC+"brguard_w_1_1","west",0,1);
    add_swim_exit(THALC+"hot","east",0,1);
    add_swim_exit(THALC+"citadel4","south",0,1);
    add_swim_exit(THALC+"citadel8","northeast",0,1);
    add_swim_exit(THALC+"citadel5","southeast",0,1);
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

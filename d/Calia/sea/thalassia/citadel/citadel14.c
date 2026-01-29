
/* 	Citadel in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define FISH 5
#define GOLDFISH 5

object *fish = allocate(FISH);
object *goldfish = allocate(GOLDFISH);

void
make_fish(int i)
{
    fish[i] = clone_object(SEA_CREATURES+"fish");
    fish[i]->move(TO);
    tell_room(TO, QCTNAME(fish[i]) + " arrives.\n");
}

void
make_goldfish(int j)
{
    goldfish[j] = clone_object(SEA_CREATURES+"goldfish");
    goldfish[j]->move(TO);
    tell_room(TO, QCTNAME(goldfish[j]) + " arrives.\n");
}

void
reset_room()
{
    int i,j;

    for (i=0; i < FISH; i++)
    {
        if (!fish[i])
            set_alarm(0.5, 0.0, &make_fish(i));
    }

    for (j=0; j < GOLDFISH; j++)
    {
        if (!goldfish[j])
            set_alarm(0.5,0.0,&make_goldfish(j));
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
        "the north, south, northwest and southwest. To the west you "+
        "you see the entrance to the cold water spring house. To the "+
        "east you see the bridge leading out of the citadel into the "+
        "lesser zone. In the centre of the bridge looms the guard "+
        "tower. Northeast and southeast you see the orichalcum wall "+
        "that surrounds the entire citadel. It sparkles like fire in "+
        "the lights.\n");

    add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the east into the lesser zone of the city. In the very centre "+
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
        "road leads off to the north, south, northwest and southwest.\n");

    add_item(({"house","spring house","cold water spring house"}),
        "To the west you see the entrance to the cold water spring house, "+
        "which houses the magical cold water spring that was granted to "+
        "the citizens of this city by Lord Diabrecho himself.\n");

    add_swim_exit(THALC+"citadel13","north",0,1);
    add_swim_exit(THALC+"citadel12","northwest",0,1);
    add_swim_exit(THALC+"cold","west",0,1);
    add_swim_exit(THALC+"citadel16","southwest",0,1);
    add_swim_exit(THALC+"citadel15","south",0,1);
    add_swim_exit(THALC+"brguard_e_1_1","east",0,1);
    set_alarm(1.0,0.0,"reset_room");
}

public int
clean_up()
{
    int i,j;

    for (i=0; i < FISH; i++)
    {
        if (fish[i])
            return 1;
    }

    for (j=0; j < GOLDFISH; j++)
    {
        if (goldfish[j])
            return 1;
    }

    remove_object();
}

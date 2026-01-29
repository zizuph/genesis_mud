
/* 	Major Zone of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define FISH 5
#define GOLDFISH 5

inherit "/d/Calia/std/water_room";
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

    for (j-0; j < GOLDFISH; j++)
    {
        if (!goldfish[j])
            set_alarm(0.5,0.0,&make_goldfish(j));
    }
}

void
create_water_room()
{
    set_short("Major Zone of Thalassia");
    set_long("You are swimming around in the Major Zone of "+
        "Thalassia. This is the largest area of the "+
        "entire city and is almost entirely decorated with "+
        "white marble and bronze. There are roads leading off to "+
        "the northeast, south and southwest. Surrounding "+
        "you on the northwestern side you see the bronze wall that "+
        "encompasses the entire Major Zone. It shines brightly in "+
        "the light giving everything around an almost bronze tint.\n");

    add_item(({"wall","bronze wall","northwest","north",
        "northwest wall","north wall"}),"This shiny metal surrounds the "+
        "wall that encompasses the entire Major Zone, except where the "+
        "bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northeast, southwest "+
        "and south.\n");

    add_swim_exit(THALM+"major21","northeast",0,1);
    add_swim_exit(THALM+"major18","southwest",0,1);
    add_swim_exit(THALM+"major19","south",0,1);
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
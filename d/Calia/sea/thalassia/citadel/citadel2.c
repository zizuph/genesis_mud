
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
#define MAGICIANS 5

inherit "/d/Calia/std/water_room";
object *guard = allocate(GUARDS);
object *citizen = allocate(CITIZENS);
object *magician = allocate(MAGICIANS);

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
    citizen[j] = clone_object(SEA_CREATURES+"thalassian_swimming_triton");
    citizen[j]->move(TO);
    tell_room(TO, QCTNAME(citizen[j]) + " arrives.\n");
}

void
make_magician(int k)
{
    magician[k] = clone_object(SEA_CREATURES+"triton_magician");
    magician[k]->equip_me();
    magician[k]->move(TO);
    tell_room(TO, QCTNAME(magician[k]) + " arrives.\n");
}

void
reset_room()
{
    int i,j,k;

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

    for (k=0; k < MAGICIANS; k++)
    {
        if (!magician[k])
            set_alarm(0.5,0.0,&make_magician(k));
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
        "the northwest, northeast, west and east. To the north "+
        "you see the entrance to the massive Royal Palace. Far "+
        "off to the north, above the palace, you see the beautiful golden "+
        "dome of the Temple of Diabrecho. To the south you see "+
        "the bridge leading out of the citadel into the lesser zone.  "+
        "In the centre of the bridge looms the guard tower. Southwest "+
        "and southeast you see the orichalcum wall that surrounds the "+
        "entire citadel. It sparkles like fire in the lights.\n");

      add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the south into the lesser zone of the city. In the very centre "+
        "of the bridge sits the three storey guard tower.\n");

    add_item(({"wall","orichalcum wall"}),"This fiery metal surrounds the "+
        "wall that encompasses the entire citadel, except where the "+
        "bridges pass through it. When the light hits it, the metal almost "+
        "seems as though it is on fire.\n"); 

    add_item(({"dome","golden dome","beautiful dome","beautiful golden dome"}),
        "This massive golden dome rises up into the water far above any "+
        "other object in this city. The dome itself must be over one "+
        "hundred feet high and two hundred feet wide at the base. It sits "+
        "atop the Temple of Diabrecho.\n");

    add_item(({"temple","Temple","Temple of Diabrecho","temple of diabrecho"}),
        "The Temple of Diabrecho is far to the north of here. You can "+
        "only see the dome sitting high atop of it from this location.\n");

    add_item(({"garden","well kept garden"}),"The garden surrounds "+
        "the Royal Palace north of you. It appears to be well taken "+
        "care of by the citizens of this fair city.\n");

    add_item(({"palace","Palace","royal palace","Royal Palace",
        "massive royal palace","massive Royal Palace"}),
        "North of you is the Royal Palace of Thalassia, finely "+
        "constructed with colourful marble. The palace itself "+
        "is two stories tall. Surrounding the palace is a well kept "+
        "garden.\n");

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northwest, northeast, west and east.\n");

    add_swim_exit(THALC+"palace_1_1","north",0,1);
    add_swim_exit(THALC+"citadel1","west",0,1);
    add_swim_exit(THALC+"citadel3","east",0,1);
    add_swim_exit(THALC+"brguard_s_1_1","south",0,1);
    add_swim_exit(THALC+"citadel5","northwest",0,1);
    add_swim_exit(THALC+"citadel16","northeast",0,1);
    set_alarm(1.0,0.0,"reset_room");
}

public int
clean_up()
{
    int i,j,k;

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

    for (k=0; k < MAGICIANS; k++)
    {
        if(magician[k])
            return 1;
    }

    remove_object();
}

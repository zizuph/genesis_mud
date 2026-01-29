
/*  Grand Palace in Thalassia

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

#define NUM 2

object *guard = allocate(NUM);

void
make_monster(int i)
{
    guard[i] = clone_object("/d/Calia/sea/creatures/palace_triton");
    guard[i]->equip_me();
    guard[i]->move(TO);
    tell_room(TO, QCTNAME(guard[i]) + " arrives and guards the door "+
        "to the Royal Administration sleeping quarters.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < NUM; i++)
        if (!guard[i])
            set_alarm(0.5, 0.0, &make_monster(i));
}

void
create_water_room()
{
    set_short("Thalassian Royal Palace");
    set_long("You are inside of the Royal Palace of "+
        "Thalassia. This hallway leads off deeper into the "+
        "palace to the west and south. North from here you see "+
        "the entrance to the Royal Administration sleeping "+
        "quarters. The ceiling itself "+
        "glows brightly, giving off a bright light, illuminating "+
        "the entire area. The walls seem like they are made of pure "+
        "gold and they shine brightly in the light.\n");
    add_item(({"quarters","sleeping quarters"}), "To the north lies "+
        "the Royal Administration sleeping quarters, where the Royal "+
        "Administration rest when not on duty in the palace.\n");
    add_item(({"wall","walls"}),"The walls appear to be "+
        "completely covered in gold.\n");
    add_item("ceiling","The ceiling glows brightly, almost "+
        "magically.\n");
    add_item("hallway","The hallway continues off to the "+
        "west and south, further into the Royal Palace.\n");

    IN;
    
    add_swim_exit(THALC+"palace_2_9","west",0,1);
    add_swim_exit(THALC+"palace_2_13","south",0,1);
    set_alarm(1.0, 0.0, reset_room);
}

public int
clean_up()
{
    int i;

    for (i=0; i < NUM; i++)
        if (guard[i])
            return 1;

    remove_object();
}

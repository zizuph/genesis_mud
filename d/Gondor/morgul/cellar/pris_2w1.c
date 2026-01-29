/*
 * /d/Gondor/morgul/cellar/pris_2w1.c
 * A prison cell.
 *
 * Olorin,  5-nov-1995
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void    reset_room();

int     alarm_id;
object *prisoner = allocate(4 + random(4));

void
create_morgul_cellar_room()
{
    set_level(2);
    set_room_type("wet and dark prison dungeon");
    set_extra_long("Into this dungeon prisoners of the King of Minas "
      + "Morgul are thrown until they are dead and forgotten.");

    add_walls("Set into the walls are iron rings to which chains "
      + "are fastened that hold the prisoners.");
    add_item(({"chain", "chains", "iron chains", }), BSN(
        "The chains are fastened to iron rings set into the walls. "
      + "They are thick and heavy, adding to the pain and torture "
      + "of the prisoners."));
    add_floor("It is covered by water and filth standing one foot "
      + "high.");
    add_ceiling("There is a trap door set into the roof, leading "
      + "out of this dungeon.");

    clone_object(CELLAR_DIR + "doors/prison_down")->move(TO);

    reset_room();
}

void
add_prisoner()
{
    int     i,
            s;

    for (i = 0, s = sizeof(prisoner); i < s; i++)
        if (!objectp(prisoner[i]))
            break;

    if (i == s)
    {
        remove_alarm(alarm_id);
        alarm_id = 0;
        return;
    }

    prisoner[i] = clone_object(MORGUL_DIR + "npc/prisoner");
    prisoner[i]->move_living("M", TO);
}

void
reset_room()
{
    if (!alarm_id || !sizeof(get_alarm(alarm_id)))
       alarm_id = set_alarm(1.0, 1.0, add_prisoner);
}


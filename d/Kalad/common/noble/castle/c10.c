// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

object  noble1, noble2, noble3,
        guard = allocate(3);
int     guard_done; // Have guards been cloned recently?

void reset_room();

void
create_noble_room()
{
    set_short("In the dining room of the High-Lord's castle");
    set_long("You are now in the huge dining room of the "+
      "High-Lord's castle. There are two tables, one small, one "+
      "large. One part of the large one is right here, and it seats many "+
      "nobles. The huge table "+
      "stretches southeasternly across the wall. There is a "+
      "large, glass chandelier hanging over head, with many "+
      "candles lighting the room and casting a prism of light. "+
      "Servants run about the room, serving nobles their food. "+
      "The walls are decorated with tapestries and murals.\n");
    add_item("candles","They burn giving light.\n");
    add_item(({"guests","nobles"}),"They chow down on food.\n");
    add_item("chandelier","A wonderful looking chandelier, it is made out of "+
      "different colored glass, resulting in a giant mirror that "+
      "reflects many different colored lights. It is beautiful.\n");
    add_item("table","Which one? Small or large?\n");
    add_item("small table","The small table has many chairs "+
      "around it, as it is a circle table. There are dishes and "+
      "platters on it with steaming food.\n");
    add_item("large table","This vast table stretches all the "+   
      "way from the northwest, to the southeast end of the room. "+
      "There are dishes and platters on it as well.\n");
    add_item("dishes","Fine china and crystal goblets.\n");
    add_item("platters","Silver platters with food on them.\n");

    INSIDE;

    add_exit(NOBLE + "castle/c11", "east", 0, 0);
    add_exit(NOBLE + "castle/c15", "southeast", 0, 0);
    reset_room();
}

void
reset_room()
{
    noble1 = clone_npcs(noble1, NOBLE + "npc/ym_dinner_noble");
    noble2 = clone_npcs(noble2, NOBLE + "npc/ym_dinner_noble");
    noble3 = clone_npcs(noble1, NOBLE + "npc/of_ball_noble");

    guard_done = 0;
}

void
call_guards(object enemy)
{
    if (guard_done)
        return;

    guard = clone_npcs(guard, NOBLE + "npc/castle_guard");

    guard[0]->team_join(guard[1]);
    guard[0]->team_join(guard[2]);

    if (present(guard[0]))
        guard[0]->command("shout Die trouble maker!");

    guard_done = 1;
}


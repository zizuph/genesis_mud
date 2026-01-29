#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_OUT;
#include "river_drink.h"

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"bubbling stream","stream"}),
      "A bubbling stream flows past you here from the northeast.\n");
    add_item(({"bank","ground","grass"}),
      "The ground at the bank of the stream is covered with short " +
      "browny-green grass.\n");
    add_item(({"valley","hills"}),
      "You stand in a large valley nestled between two hills in the " +
      "middle of Estwilde.\n");
    add_item(({"community","stone buildings","buildings"}),
      "Over the stream to your southeast stand a number of stone buildings. " +
      "Smoke rises lazily from a number of chimneys, telling you " +
      "these finely crafty buildings are occupied.\n");
    add_item(({"great rent","rent","northern hill"}),
      "To your northeast, the cliff-like face of the northern " +
      "hill of this valley is broken by a great rent in its surface, " +
      "where a bubbling stream rushes from its dark depths.\n");
    add_item(({"sturdy bridge","bridge"}),
      "A wooden bridge of dwarven make, crossing the stream to the " +
      "southeastern bank where the settlement is.\n");

    add_exit(IRON + "r5","northwest",0);
    add_exit(IRON + "r4","west",0);
    add_exit(IRON + "r6","southwest",0);
    add_exit(IRON + "bridge","southeast",0);

    add_cmd_item(({"stream","bubbling stream","water","from stream","from bubbling stream"}),
      "drink","@@drink_water");

    reset_dwarf_room();
}

string
short_descr()
{
    return "Before a sturdy bridge at the bank of a bubbling stream";
}

string
long_descr()
{
    return "You stand at the bank of a bubbling stream that runs past you " +
    "from a great rent in the face of the northern hill to your northeast, " +
    "down to your southwest. A sturdy bridge has been constructed here, " +
    "crossing the stream to your southeast, where you see what looks "
    + "like a small community of stone buildings of dwarven make " +
    "nestled in the middle of this large valley.\n";
}

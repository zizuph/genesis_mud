inherit "/d/Gondor/minas/houses/citizens/house";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#define DOOR_ID	"MT_carpenter_n3crc1"

void    add_door();
void    reset_room();

object  citizen;

void
create_room()
{
    add_exit(MINAS_DIR+"rooms/carpentry2","south",0,0);

    set_short("carpenters shop");
    set_long(BSN(
        "This is a workshop of a carpenter, who "+
        "seems to be a distinguished member of the carpenters guild. "+
        "A foot or two from the northern wall you see a workbench. On it "+
        "tools are neatly arranged. A door is leading out east onto the street."));

    add_item("workbench", BSN( 
        "The workbench is very well kept and the tools lying on it "
      + "are placed in neat order. Next to the bench is a lathe."));
    add_item(({"tool","tools"}), BSN(
        "The tools are neatly placed on the workbench. They include "
      + "chisels, table-saws, planers and a knife."));
    add_item("knife","The knife on the workbench looks very sharp and "+
             "seems well used. It "+
             "has a wooden shaft.\nIt looks like it is in prime condition.\n"); 
    add_item(({"chisel","chisels"}),"You see chisels in different sizes "+
               "on the workbench.\n");
    add_item("lathe", BSN(
        "Pedalling with a foot, the carpenter can set a piece of wood "
      + "he is working on into rotation on this lathe. It is used to make and "
      + "decorate round pieces of wood, legs for tables, desks, "
      + "and chairs, for example."));
    add_item(({"table-saw","table-saws"}),"You see saws in different sizes "+
               "on the workbench.\n");
    add_item(({"planer"}),"You see planers in different sizes on the "+ 
               "workbench.\n");

    add_door();
    reset_room();
}

void
add_door()
{
    object  door;

    if (present("door", TO))
        return;

    // clone and configue door
    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id(DOOR_ID);
    door->set_pass_command(({"east", "e"}));
    door->set_door_name(({"wooden door","door"}));
    door->set_other_room(MINAS_DIR + "n3crc1");
    door->set_door_desc(BSN(
        "The door is quite new and expertly crafted. Carved into "
      + "it is the picture of large dividers sitting across a saw, the "
      + "symbol of the craft of carpentry and of the craftsman "
      + "guild of carpenters."));
    door->set_key(DOOR_ID);
    door->move(TO);
}

void
reset_room()
{
    object  key;

    if (objectp(citizen))
        return;

    citizen = clone_object(MINAS_DIR + "npc/carpenter");
    citizen->arm_me();
    key = clone_object("/std/key");
    key->set_key(DOOR_ID);
    key->set_short("iron key");
    key->set_adj(({"black", "iron", }));
    key->set_long("A black iron key, probably for a door.\n");
    key->move(citizen);
    citizen->move(TO);
}


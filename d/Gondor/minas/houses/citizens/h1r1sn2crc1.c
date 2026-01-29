inherit "/d/Gondor/minas/houses/citizens/suspect_home";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_suspect_room()
{

    set_door_id("MT_h1_n2crc1");
    set_door_command(({"s","south"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(MINAS_DIR + "n2crc1");
    set_door_desc(BSN("The wooden door looks rather old, but it "
      + "obviously has been painted regularly so there is hardly "
      + "any wear noticeable."));

    set_suspect(0); // number of the suspect
    set_wealth(1);
    set_side("north");
    set_circle("First Circle");

    set_short("living room");
    set_long(BSN(
        "This is the living room of the house. A humble stool sits in " +
        "the middle of the room next to a battered table. The whole " +
        "room is rather dirty. A door is leading out onto " +
        "the street to the south, while a doorway is leading north into " +
        "the kitchen."));
    add_item(({"stool","humble stool","wooden stool"}), BSN(
        "This wooden stool is quite small. Its three legs are thick, " +
        "but the construction is so poor that you would be afraid to " +
        "sit down upon it. It has apparently seen far too much use " +
        "over the years."));
    add_item(({"table","battered table","wooden table"}), BSN(
        "A wooden table with a great deal of wear and tear. This table " +
        "has probably seen the passage of more years than your parents, " +
        "by its looks. A small cloth sits upon the surface of the table, " +
        "and various tools and pieces of metal and glass rest upon the " +
        "cloth."));
    add_item(({"cloth","small cloth"}), BSN(
        "This small cloth is in the center of the table. It is " +
        "stained an awful gray and is tattered about the edges. " +
        "It seems to you that it is used to polish metal."));
    add_item(({"tools","metal tools"}), BSN(
        "These metal tools are used to work iron and softer metals. " +
        "They are rather delicate, and it seems that they are mainly " +
        "for engraving and minor work, since it would take many " +
        "more tools than these to effect anything significant with " +
        "the metal you see about."));
    add_item(({"metal","pieces of metal","metal pieces"}), BSN(
        "There are predominantly iron pieces here, with an occassional " +
        "fragment of brass. The metal is in the process of minor " +
        "tooling, it seems. When you examine them closely, you " +
        "realize that these pieces are the frames of lamp shutters. " +
        "A lampwright lives here, who apparently takes some of his " +
        "work home with him. This also explains the glass about."));
    add_item(({"glass","glass pieces","pieces of glass"}), BSN(
        "The glass here are in two shapes: square plates and " +
        "hemispheres with elongations at one side of the rim."));

    add_window("The window is very small.");
    add_walls("The walls have a thin layer of dust upon them.");
    add_ceiling();
    add_floor("Some pieces of metal have fallen onto the floor.");

    add_exit(MINAS_DIR + "houses/citizens/h1r2","north",0,0);
}


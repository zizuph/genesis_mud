inherit "/d/Gondor/minas/houses/citizens/suspect_home";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"


void
create_suspect_room()
{
    add_exit(MINAS_DIR + "houses/citizens/h4r2","south",0,0);
    add_exit(MINAS_DIR + "houses/citizens/h4r3","west",0,0);

    set_door_id("MT_h4_alleycrc2");
    set_door_command(({"n","north"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(MINAS_DIR+"alleycrc2");
    set_door_desc(BSN(
        "This wooden door is of mediocre quality. It is aged, but bears " +
        "its age well despite the abuse it seems to have suffered."));

    set_suspect(3);
    set_wealth(0);
    set_side("south");
    set_circle("Second Circle");

    set_short("living room");
    set_long(BSN(
        "This is the living room of this house. The family is obviously " +
        "of small means, but not quite as poor as the houses that you " +
        "saw in the First Circle of the city. You see a table with " +
        "chairs, a bookshelf, and a loom. This room is lit by two " +
        "windows on the northern wall."));
    add_item(({"table","dining table"}), BSN(
        "This wooden table is used as an eating surface and a meeting " +
        "place by the family that lives here."));
    add_item(({"chair","chairs"}), BSN(
        "These four wooden chairs stand about the table, ready to " +
        "support weary bodies."));
    add_item(({"furniture"}), BSN(
        "The furniture in this room consists of the dining table, " +
        "the chairs that accompany it, and a bookshelf."));
    add_item(({"bookshelf","bookcase","shelf","shelves"}), BSN(
        "This wooden bookshelf holds some meagre books and documents " +
        "that the family has collected over time. They do not look " +
        "particularly interesting or valuable."));
    add_item(({"books","documents"}), BSN(
        "The books are mainly some readers for children. You see an " +
        "older copy of 'Forweg and Gilraen' among others. The " +
        "documents are principally the family's records of purchases " +
        "and taxes paid, accumulated over a long time. Quite boring."));
    add_item(({"loom"}), BSN(
        "This loom is apparently used by the mother of this family to " +
        "produce cloth. It is well used, and you note a basket near " +
        "the side of the loom, beneath the stool."));
    add_item(({"basket","straw basket"}), BSN(
        "This straw basket holds the finished products of the loom's " +
        "labour. Right now it contains only some dust and stray " +
        "strands of wool."));
    add_item(({"stool","wooden stool"}), BSN(
        "This small wooden stool is for sitting on while operating the " +
        "loom. The seat is covered with a woolen pad, perhaps a " +
        "product of this very loom."));
    add_item(({"pad","woolen pad"}), BSN(
        "This pad is made from wool and used to cushion the rear of " +
        "a person who sits on the stool."));


    add_window("It is smudged in places.");
    add_walls("A bookshelf stands against on of the walls.");
    add_ceiling("There are some blemishes upon the ceiling.");
    add_floor("Upon the floor a straw basket rests near the loom.");

}

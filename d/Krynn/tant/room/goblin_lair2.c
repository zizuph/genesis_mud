/* Goblin Lair near Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit INROOM;

object gob1, gob2, gob3;

public void
reset_tant_room()
{
    if (!gob1)
    {
        gob1 = clone_object(TNPC + "goblin");
        gob1->move(TO);
    }
    if (!gob2)
    {
        gob2 = clone_object(TNPC + "goblin");
        gob2->move(TO);
    }
    if (!gob3)
    {
        gob3 = clone_object(TNPC + "goblin");
        gob3->move(TO);
    }
}

public void
create_tant_room()
{
    set_short("A lair");
    set_long("You have entered a lair. This cave is obviously " +
        "populated by filthy and decrepit creatures, as garbage is " +
        "strewn everywhere. Blood stains the walls and floor, so " +
        "this is also the cave of something that eats other creatures. " +
        "Going southeast would take you back to the main portion of the " +
        "cave.\n");
    AI(({"lair","cave"}),"The cave is craggy, and not hand-hewn at all.\n");
    AI("garbage","The garbage consists of bones and fur.\n");
    AI("bones","The bones belong to all varieties of creatures.\n");
    AI("fur","None of the fur is of any value anymore.\n");
    AI("bone","There are many bones strewn about.\n");
    AI(({"stains","blood","blood stains"}),"The blood that stains the " +
        "floor and walls comes from many kinds of creatures. It is " +
        "blackened with age.\n");
    AI(({"walls","floor","wall","ceiling"}),"The entire cave is " +
        "natural, made of craggy rocks rather than hand-hewn and " +
        "shaped.\n");
    AI("stench","The stench is of goblins.\n");

    DARK;

    AE(TROOM + "goblin_lair", "southeast", 0, 0);
    reset_tant_room();
}


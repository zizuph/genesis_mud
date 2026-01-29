// file name: fountain.c
// creator(s): Farlong
// last update: Last update: 25 June 94 by Tepisch
//              Ilyian (8 March, 1995)
//              Ilyian (26 April): added diving functions
// purpose: contains the cage w/ the faerie for quest
// note: Diving functions borrowed from Terel by the grace of Procter Sorgum
// bug(s):
// to-do:

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "park.h"

public int
do_dive(string str)
{
    write("You dive down into the murky water, and quickly find the "
      +"large hole at the side of the basin, which you enter.\n"
      +"Blackness and an icy chill surround you.\n");
    this_player()->move_living("into the water",PK + "water/water1");
    return 1;
}

public int
do_breath(string str)
{
    if (str != "breath") return 0;
    write("You take a deep breath of air and hold it in your lungs.\n");
    say(QCTNAME(this_player()) +
      " takes a deep breath of air holds it.\n");
    return 1;
}

private static object cage;

public void
create_room(void)
{
    set_short("Standing in the fountain");
    set_long(
      "You are standing ankle-deep in the water of the"
      +" shallow pool which surrounds the base of the fountain. The"
      +" fearsome marble figure towers over you. Up close, the"
      +" intricate carving of the fountain is quite impressive."
      +" Jets of water keep the pool in constant motion, so that "
      +"you cannot see into it.\n");

    AI(({"figure","statue"}),"The statue is of a titanic elf made from carved "
      +"ebony. In one hand he holds aloft a gigantic trident, and "
      +"in the crook of the other arm is a tiny intricate cage made "
      +"from gold. The head of the statue is thrown back, seemingly "
      +"giving off some sort of victory cry.\n");
    AI(({"water","pool"}),"The water in the pool seems fresh, but you "
      +"cannot see into it because of the swirling rush the jets are "
      +"creating. It seems to all be moving towards the east side "
      +"of the fountain.\n");
    AI(({"jet","jets"}),"Tiny mechanical jets positioned around the "
      +"edges spray water into the fountain, creating eddies in the "
      +"pool and making the water opaque.\n");
    AI(("trident"),"It is an enormous trident, but made of stone, so "
      +"it would be useless even if you could find a way to "
      +"prise it from the statue's grasp.\n");
    AI(({"base","fountain"}),"The base of the fountain is carved from "
      +"one enormous piece of blue-veined marble, quite expertly "
      +"done. It has a shallow basin into which jets spray water "
      +"in colorful patterns. An enormous statue rises up from "
      +"the center of the fountain, carved in ebony. All the water "
      +"in the fountain seems to be moving towards the east side.\n");
    AI(({"carving","carvings"}),"The marble basin is carved with "
      +"strange symbols, almost like runes. They are chisled deep into "
      +"the rock in bas relief.\n");
    AI(({"rune","runes","symbol","symbols"}),"You cannot decipher what "
      +"they might mean, or even if they have a meaning at all.\n");
    AI(({"side","east","east side"}),"The water is all moving towards this "
      +"side of the fountain, so you assume there must be a hole somewhere "
      +"beneath the murky water.\n");
    AI(("hole"),"You cannot see the hole through the murky water, but "
      +"judging by the amount of water that is draining into it, it "
      +"must be quite large.\n");

    AE(PK+"dlord", "back");

    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_prop(ROOM_I_LIGHT, 0);
    IN_IN

    seteuid(getuid(this_object()));
    cage = clone_object(PK + "obj/cage");
    cage->move(this_object());
    cage->fill_cage();
}

public void
init(void)
{
    ::init();
    add_action(   do_dive, "dive" );
    add_action( do_breath, "take" );
}

public void
reset_room(void)
{
    cage->fill_cage();
}

/*
 * home2.c
 * One of the local residences
 * Haven town
 * Created by Tibbit, 10 Mar 1998
 */

#include "../local.h"

inherit HAVENINBASE;

object citizen;

void
reset_haven()
{
    reset_euid();

    if(!citizen)
        (citizen = clone_object(HNPC + "citizen_" +
            (random(2) ? "m" : "f")))->move(TO);
}

void
create_haven()
{
    set_short("Simple wooden home");

    set_long("This is one of the simple, wooden-constructed "+
        "homes of the citizens of Haven. "+
        "You note the one-room habitation, subdivided into "+
        "sleeping and eating areas. The room is mostly bare, "+
        "save for a few simple pieces of furniture."+
        "\n");

    add_item(({"habitation","house","home"}),
        "This home is quite simple, though comfortable. It is made "+
        "from wood.\n");
    add_item(({"area","areas","sleeping area","eating area",
        "sleeping areas","eating areas"}),
        "This house is neatly divided into the area where food is "+
        "prepared and eaten, and the area where the local folks "+
        "lie down at the end of their long day.\n");
    add_item(({"furniture","pieces"}),
        "A simple wooden table is attended by a few stools. "+
        "All appear handmade.\n");
    add_item(({"table","stool","stools"}),
        "There doesn't appear to be anything unusual about the table "+
        "or the wooden stools here.\n");

    add_exit(HROOM+"st5","east");

}


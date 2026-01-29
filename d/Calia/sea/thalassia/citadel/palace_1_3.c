
/*  Grand Palace in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar
                12. 5.16    fixed typo                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define NUM 6

object *guard = allocate(NUM);

void
make_monster(int i)
{
    guard[i] = clone_object("/d/Calia/sea/creatures/palace_triton");
    guard[i]->equip_me();
    guard[i]->move(TO);
    tell_room(TO, QCTNAME(guard[i]) + " arrives.\n");
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
    set_short("Royal Palace guard chamber");
    set_long("This lavishly decorated room serves as a guard "+
        "chamber for the Royal Palace. It is one of the first "+
        "lines of defence for the royal family that resides "+
        "here. The walls are made of gold and covered with "+
        "tapestries, crests and other decorations. North you "+
        "see some type of chamber while south leads to a hallway "+
        "of some type. West you see the throne room.\n");

    add_item(({"wall","walls"}),"The walls appear to be "+
        "completely covered in gold. They are covered in "+
        "tapestries, crests and other decorations.\n");
    add_item("hallway","The hallway leads off to the "+
        "south, further into the Royal Palace.\n");
    add_item(({"decoration","decorations"}),"There are other "+
        "various decorations throughout the room including "+
        "vases, and urns.\n");
    add_item(({"urn","urns"}),"These large urns are made of "+
        "some type of stone and are placed between the urns "+
        "in a symmetrical pattern throughout the room.\n");
    add_item(({"vase", "vases"}),"The vases appear to be made "+
        "of some type of stone and are positioned symetrically "+
        "throughout the room.\n");
    add_item("throne room","The throne room is off to the west "+
        "of this room. Perhaps you should swim there if you want "+
        "to take a better look.\n");
    add_item(({"crest","crests"}),"There are several crests "+
        "on the walls of this room. Each seems to be the crest "+
        "of some family, possibly the crests of the guards "+
        "who work in this palace.\n");
    add_item(({"tapestry","tapestries"}),"There are various "+
        "tapestries hanging on the walls, moving slightly as "+
        "the waters around them flow around them. You count "+
        "five tapestries on the walls, perhaps you could "+
        "look at each one individually (<examine first "+
        "tapestry, etc...>).\n");
    add_item(({"first tapestry", "1st tapestry"}),"The first "+
        "tapestry depicts a lavishly decorated mermaid banging "+
        "on a small drum.\n");
    add_item(({"second tapestry","2nd tapestry"}),"The second "+
        "tapestry depicts a robed and hooded mermaid playing "+
        "some type of flute-like instrument.\n");
    add_item("third tapestry","The third tapestry depicts a "+
        "handsome, naked triton playing a rattle-like instrument.\n");
    add_item("fourth tapestry","The fourth tapestry depicts a "+
        "ceremonially dressed triton playing some type of water-filled "+
        "tube like a flute.\n");
    add_item("fifth tapestry","The fifth tapestry depicts a totally "+
        "concealed creature hitting a bell.\n");

    IN;

    add_swim_exit(THALC+"palace_1_4","north",0,1);
    add_swim_exit(THALC+"palace_1_6","west",0,1);
    add_swim_exit(THALC+"palace_1_8","south",0,1);
    add_swim_exit(THALC+"palace_1_2","east",0,1);
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

/*
    Modified 3 May 2003, by Bleys
        - fixed a couple of typos
    modified June 2008 Lilith
        -the search command "through bones" is too syntax intensive and
         it is not intuitive, added additional search terms.
*/

#include "/d/Terel/include/Terel.h"

inherit STDROOM;
#include <stdproperties.h>

#define AMULET "/d/Terel/mountains/obj/rd_amulet"

object amulet;
int amu = 0;

public string*
query_object_list()
{
    return ({"/d/Terel/mountains/obj/rat",
                 "/d/Terel/mountains/obj/rat",
                 "/d/Terel/mountains/obj/rat",
                 "/d/Terel/mountains/obj/rat",
                 "/d/Terel/mountains/obj/rat",
                 "/d/Terel/mountains/obj/rat"});
}

          

public void
create_room()
{
    set_short("Refuse");
    set_long(
        "This place seems to be a refuse heap. The floor is littered\n"
      +"with bones, rotting food, skins, dung and other things that\n"
      +"are not recognizable.\n");
    add_item(({"skin", "skins", "bone", "refuse", "heap","bones"}),
            "There are bones and skins of many different things here. "+
            "The denizens of this place have feasted on all manner of "+
            "beings.\n");
    add_cmd_item("through bones","dig", "@@dig");
    add_cmd_item("through bones","search", "@@dig");
    add_cmd_item("bones","dig", "@@dig");
    add_cmd_item("bones","search", "@@dig");

    
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Terel/mountains/guardroom","up",0);
    reset_room();
}
void
reset_room()
{
    ::reset_room();
    amu = random(2);
    return;
}

int dig()
{
    write("You start digging through the bones.\n");

    if(amu == 0)
    {
        set_alarm(5.0, -1.0, "get_amulet");
        amu = 1;
        return 1;
    }
    set_alarm(5.0, -1.0, "no_amulet");

    return 1;
}

void
get_amulet()
{
    amulet = clone_object(AMULET);
    amulet->move(TP);
    write("As you dig through the refuse you come across an amulet.\n");
    return;
}

void
no_amulet()
{
    write("You dig through the refuse but find nothing.\n");
    return;
}


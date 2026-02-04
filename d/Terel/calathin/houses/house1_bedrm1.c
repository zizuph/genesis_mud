/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house1.c
 *
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>


inherit STDROOM;
object door;
object chest;
object teddybear;
int teddy;


#include <stdproperties.h>


public void
create_room()
{
 
    ::create_room();
    INSIDE;
    set_short("child room");
    set_long("The bedroom is decorated with children in mind. " +
       "Childlike murals showing children at play are painted on the walls. " +
       "There is a shelf affixed to the west wall just over a small bed. " +
       "A large chest sits against the north wall under a small " +
       "shuttered window.\n");

    add_item(("murals"),"Mostly depicting children at play.\n");
    add_item(("window"),"The small window is closed tight with the outer " +
       "shutters drawn. A single cloth drape covers the window.\n");
    add_item(("drape"),"The cloth drape is covered in multi-colored " +
       "patches for decoration.\n");
    add_item(({"shutter","shutters"}),"Wood shutters used to keep " +
       "the elements out.\n");
    add_item(("patches"),"Multi-colored patches decorate the drape.\n");
    add_item(("bed"),"The small wooden bed is painted white. " +
       "There is a stuffed bed spread covering the bed.\n");
    add_item(("shelf"),"A small shelf used to hold various stuffed " +
       "animals and toys for the child.\n");
    add_item(({"bed spread","covers"}),"The bed spread is made of a fine soft wool covered " +
       "in various multi-colored patches to match the drape coving the window.\n");
    add_item(({"toy","toys","stuffed animals","animals"}),
       "Simple childs toys, mostly stuffed animals.\n");
    
    add_cmd_item(({"drape", "window","curtain"}),
                 ({"tear","rip","open"}),
                 ("It's cold enough inside, why would you want to do that?\n"));

    add_cmd_item(({"small bed","bed"}),
                 ({"sit","lie","lay","lie on","sit on","lay on"}),
                 ("The bed is made for a child, not a stout adventurer like " +
                   "yourself.\n"));
    add_cmd_item(({"covers","bed spread","spread"}),
                 ("lift"),
                 ("@@bear"));
                 teddy = 1;

    door = clone_object(CALATHIN_DIR + "houses/obj/house1_bedrm1_door");
       door->move(TO);
    chest = clone_object(CALATHIN_DIR + "houses/obj/chest");
       chest->move(TO);
       chest->reset_container();

    reset_room();
}

void
reset_room()
{
    ::reset_room();
    teddy = 1;
    return;
}

int
query_bear()
{
    return teddy;
}

int 
bear()
{
    write("You reach down and lift the up the bed spread.\n");

    if(teddy == 1)
    {
        set_alarm(5.0, -1.0, "get_bear");
        teddy = 0;
        return 1;
    }
    set_alarm(5.0, -1.0, "no_bear");

    return 1;
}

void
get_bear()
{
    teddybear = clone_object(CALATHIN_DIR + "houses/obj/teddybear.c");
    teddybear->move(TP);
    write("You find a stuffed bear beneath the spread.\n");
    return;
}

void
no_bear()
{
    write("You find nothing but sheets under the bed spread.\n");
    return;
}



/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house3a.c
 *
 * Calathin external house.
 * 09/30/1999 -- Tomas
 *
 *  Modified: 22 July 2003, by Bleys
 *      - Fixed a couple of typos in the pots add_item
 *
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>


inherit STDROOM;

object door;
object item;
int ite;

#define GLOVES "/d/Terel/calathin/houses/armour/herb_gloves"

public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("living room");
    set_long("From inside the house you can see that its not " +
       "just the ravages of winter that has caused the disrepair. " +
       "Debris is piled in the corners and a rather unpleasant " +
       "odor comes from the pots clustered around the fireplace. " +
       "A pile of straw and blankets sits near the fireplace to " +
       "serve the occupants as a bed.\n");

    add_item(({"window","windows"}),"The windows are covered in filth, its " +
       "a wonder that any light can pass through them.\n");
    add_item(("debris"),"Rotted wood from the walls and ceiling bits and " +
       "pieces of old cloth, rotten foodstuffs litter the floor.\n");
    add_item(({"pots","pot","pans"}),"Disgusting pots filled with vile " +
       "smelling food. It is probably best not to get to close.\n");
    add_item(({"straw","blankets"}),"Makeshift beds lay in front " +
       "of the fireplace. They look as if they haven't been used " +
       "in awhile.\n");
    add_item(("fireplace"),"The cobbled fireplace looks as if someone " +
       "used it to cook with as well as to keep warm.\n");


    add_cmd_item(({"smell", "odor", "pots"}),
                 ({"smell","smell the"}),
                 ("The pots stink of rotted food.\n"));

    add_cmd_item(({"through debris","debris"}),"rummage", "@@rummage");
    ite = 1;





     door = clone_object(CALATHIN_DIR + "houses/obj/house3a_door");
        door->move(TO);

     reset_room();

}


void
reset_room()
{
   ite = 1;
}


int
query_ite()
{
    return ite;
}

int rummage()
{
    write("You start rummaging through the pile of debris.\n");

    if(ite == 1 && TP->query_prop("_terel_gardener_quest"))
    {
        set_alarm(5.0, -1.0, "get_item");
        ite = 0;
        TP->add_prop("_terel_gardener_found", 1);
        return 1;
    }
    set_alarm(5.0, -1.0, "no_item");

    return 1;
}

void
get_item()
{

    item = clone_object(GLOVES);
    item->move(TP);
    write("As you rummage through the pile of debris you find a pair of gloves.\n");
    write_file(TEREL_DIR + "log/found_gloves",
       TP->query_name()+" " + ctime(time()) + "\n");
    return;
}

void
no_item()
{
    write("You rummage through the pile of debris but find nothing.\n");
    return;
}






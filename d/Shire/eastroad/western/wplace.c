#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";

#include "local.h"
#include <cmdparse.h>


object well_obj, bucket;

void
create_room() 
{
   set_short("Water place");
   set_long("This little spot was probably made for tired travellers to rest. "
         + "There is a well here, and the grass looks soft enough to lie "
         + "down in.\n");
   
   add_item("grass", "The grass looks soft. You feel like taking a nap here.\n");
   add_prop(OBJ_I_CONTAIN_WATER, 1);

   add_exit (EAST_R_DIR + "er15s","north");
   add_exit(EAST_R_DIR + "lpath1","west");
   
   reset_shire_room();
}

void
reset_shire_room() 
{
   if (!well_obj) 
   {
      well_obj = clone_object("/d/Shire/common/obj/well.c");
      well_obj->move(this_object());
   }
   
   if(!present("bucket"))
      {
      bucket = clone_object("/d/Shire/common/obj/bucket.c");
      bucket->move(TO);
   }
}


void
init()
{
    ::init();
    add_action("do_climb","enter");
    add_action("do_climb","climb");

}

int
do_climb(string str)
{
    if (!str)
    {
    NFN(CAP(query_verb())+" what?");

	return 1;
    }
    if ((str != "well") && (str != "little well") && (str != "deep well") && 
        (str != "down deep well") && (str != "down well") && 
        (str != "down little well") )
    {
	write("Enter where?\n");
	return 1;
    }
    write("With a great deal of effort, you carefully enter the well and climb down the wall.\n");
    SAYBB(" enters the well.");
    TP->move_living("M",EAST_R_DIR + "wdown",1,0);
    SAYBB(" climbs down the well.");
    return 1;
}

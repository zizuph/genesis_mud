/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
int grapes=0;
 
void
reset_room()
{
    if (grapes) 
        return;
     grapes = 1;
}
 
/* room definition */
void
create_room()
{
   set_short("A vineyard");
   set_long(
       "You are standing in the northeastern corner of a lush vineyard. " +
       "Long rows of lattices overgrown with grape vines run the " +
       "length of the vineyard, while tall palisades stand protectively " +
       "to the north and east.\n");
 
    add_item(({"palisade","palisades"}),
             "It is a solid fence made of tall, straight tree-trunks " +
             "surrounding the vineyard.\n");
 
    add_item(({"lattice","lattices"}),
        "Criss-crossed strips of wood, set upright into square frames, " +
        "these lattices run east-west through the vineyard and are " +
        "covered with grape vines.\n");
 
    add_item(({"vines","vine"}),"@@exavines");
    add_item("grapes","@@exagrapes");
 
    add_cmd_item("grapes","pick","@@pick");
 
    /* exits */
    add_exit(ROOM_DIR+"vyard2","west",0);
    add_exit(ROOM_DIR+"vyard5","south",0);
    reset_room();
}
exavines()
{
   if (grapes) return
      "Covering the lattices, you see red grapes growing on the vines.\n";
 
   return
   "The vines cover the lattice, but all the grapes have been picked.\n";
}
 
exagrapes()
{
   if (grapes) return
       "There is a bunch of red grapes growing on the vines.\n";
 
   return
       "All the grapes have been picked from the vine.\n";
}
 
pick()
{
    object grapes_obj;

    if (!grapes)
       {
          write("All the grapes have been picked from these vines!\n");
          return 1;
       }
    write("You pick a bunch of red grapes from the vines.\n");
    grapes_obj = clone_object(OBJ_DIR+"grapes.c");
    grapes_obj->move(this_player());
    grapes = 0;
    return 1;
}

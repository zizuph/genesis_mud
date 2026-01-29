/* room coded by Elizabeth Cook/Mouse, March 1997 */

inherit "std/room";
#include <stdproperties.h> 
#include "../../mouse.h"  

void create_room()  {
     set_short("The back workroom");
     set_long("   This room is where the wool is washed and dyed. Vats and "+
          "buckets line one side of the room. Jars and crocks fill the "+
          "many shelves on the wall opposite the vats. A small desk "+
          "occupies one corner of the room. You can see the dyed wool "+
          "drying over racks in the yard just beyond an open doorway.\n");
     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,2);
     add_item(({"vats","vat","buckets","bucket"}),"The buckets and vats "+
          "are full of strange smelling liquids. You think it might be "+
          "unwise to stand with your face this close to them.\n");
     add_item(({"jars","jar"}),"The jars are filled with various "+
          "mordanting compounds, such as alum, tin, copper, iron, "+
          "and salt. These are used to fix the color of the dye.\n");
     add_item(({"crocks","crock"}),"The crocks are filled with things "+
          "like plant roots, leaves, and bark used to create the various "+
          "dyes.\n");
     add_item(({"roots","leaves","bark"}),"You look them over, but you "+
          "are unable to determine the types of plants they came from.\n");
     add_item ("shelves","They are full of jars and crocks.\n");
     add_item("desk","It is cluttered with books and papers.\n");
     add_item("books","The books look like they are used for keeping "+
          "various records of business.\n");
     add_item("papers","The papers are a garbled pile of notes and "+
          "correspondence. Underneath this pile of miscellaneous papers "+
          "you find some sort of chart.\n");
     add_item("chart","It appears to be a chart of dyes. You might "+
          "want to read it.\n");
     add_cmd_item("chart","read",
          "               -DYES-            \n"+
          "  Onion skin -  orange        \n"+
          "  Elder leaves -  green       \n"+
          "  Madder root -  red          \n"+
          "  Woad -  blue                \n"+
          "  Bearberry leaves -  violet-gray \n"+
          "  Tansy flowers -  yellow     \n"+
          "  Elder berries -  purple     \n"+
          "  Meadowsweet root -  black   \n"+
          "  Walnut husks and shells -  brown  \n");
     add_item("wool","You can see today's dye lot of wool hanging "+
          "outside to dry.\n");
     add_item("racks","The racks are simply thick wooden dowels "+
          "supported by poles that have been lodged in the ground. "+
          "They are partially filled with drying wool.\n");     
   
       
     add_exit(ROOT+"village/rooms/weaver","east");
   

        
}


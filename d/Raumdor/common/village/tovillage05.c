// -*-C++-*-
// file name:        /d/Raumdor/common/tovillage/tovillage05.c
// creator(s):       Vyasa, 9.2.2020
// revisions:
// purpose:          This room connects the path to the area in the mountain.
// note:           
// bug(s):
// to-do:            Room description + items. Entrance to the mountain.
//                   
//                   
//                   

#include "/d/Raumdor/defs.h"
inherit "/std/room";

create_room() {
    
    set_short("Walking along the path to the village");
    set_long("To be described later.\n" +
             "Once the skeleton is done.\n"+
             "\n");
    add_exit("/d/Raumdor/common/village/tovillage04.c", "northeast", 0);
    add_exit("/d/Raumdor/common/village/tovillage06.c", "south", 0);
    add_item("item", 
         "Item Description.\n");
}

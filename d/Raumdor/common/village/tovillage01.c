// -*-C++-*-
// file name:        /d/Raumdor/common/village/tovillage01.c
// creator(s):       Vyasa, 9.2.2020
// revisions:
// purpose:          Connecting the road to the path to the village
// note:           
// bug(s):
// to-do:            Room description + items.
//                   
//                   
//                   

#include "/d/Raumdor/defs.h"
inherit "/std/room";

create_room() {
    
    set_short("A room connecting the road to the village path");
    set_long("To be described later.\n" +
             "Once the skeleton is done.\n"+
             "\n");
    add_exit("/d/Raumdor/common/road/road05.c", "northeast", 0);
    add_exit("/d/Raumdor/common/village/tovillage02.c", "southwest", 0);
    add_item("item", 
         "Item Description.\n");
}

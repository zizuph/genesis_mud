// file name: d/Avenir/common/outpost/fort8.c
// creator(s): Lilith June 2004
// last update:
// purpose:    
// note:	
// bug(s):
// to-do:       

#pragma strict_types
#include "/d/Avenir/common/outpost/outpost.h"
inherit OUTPOST +"fort_base";

void create_fort_room()
{
    set_short("an east-west tunnel near the forge complex");
    set_long(""+
        " "+
        " "+
        " "+
        " "+
        " "+
        " "+
        ".\n");
       
    add_exit(OUTPOST + "fort5","northwest",0);


} // create_room()


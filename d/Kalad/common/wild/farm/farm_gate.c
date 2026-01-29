/* 20171016 created by Zignur to give access to the new farmlands */


inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void 
create_room()
{
    ::create_room();
    set_short("City Gates");
    set_long("A gravel road at the gates of Kalad. You stand infront of"
      + " the city gates, while wast farmlands stretch out to the west."
      + " The gravel road continues to the west into the farmlands, east"
      + " will take you through the gates into the city. It is possible" 
      + " to travel to the east and to the west.\n\n");  
    
    add_item( ({ "gates", "gate" }),
        "This is the large city gate that protects Kalad from intruders.\n");             
    add_item( ({ "farmlands", "farmland"}),
        "You see a large fields of hay and various other crops.\n");        
    add_item( ({ "field", "fields","crops","hay"}),
        "Large fields of hay and other crops grows nearby.\n");
    add_item( ({ "road", "gravel road", "ground"}),
        "The road is made of hard packed gravel, you see some holes and"
      + " cracks in it. Most likely caused by the dry hot climate.\n");
    add_item( ({ "crack", "cracks","hole","holes"}),
        "The road has several holes and cracks, caused by the dry climate.\n");
    add_item( ({ "gravel", "small gravel","packed gravel","gravels"}),
        "The road consist of small packed gravels.\n");     
   
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit("/d/Kalad/common/farmland/f_road1", "west");
    clone_object(NOBLE(obj/fgdoor1))->move(TO);
}

int
block()
{
    write("The way is not open yet.\nSpazm.\n");
    return 1;
}


/*
 *  Inherit for north east road of Gelan.  
 */ 

inherit "/std/room"; 

#include <stdproperties.h>


void
make_the_room(string extra_long, string where)
{
    set_long("You're on a road running " + where + " of Gelan. " +
             "The road's surface is made of fine, packed gravel, " +
             "in contrast to the " +
             "uneven rocky terrain through which it runs. On either " +
             "side of the road, thorny plants grow in dense clusters. " +
             "Maples grow nearby sprinkled sparsely over the " +
             "landscape." + (stringp(extra_long) ? " " + extra_long : 
             "") + "\n"); 
    add_item(({"road", "surface", "gravel", "packed gravel", "fine gravel"}), 
             "The road is surfaced with fine grey gravel, smooth and " +
             "hard-packed by frequent traffic.\n"); 
    add_item(({"maples", "maple", "trees", "tree"}), 
             "Maple trees dot the landscape. Young and slender, " + 
             "they will have to grow many more years before they " +
             "get big enough to get used for lumber.\n"); 
    add_item(({"plants", "thorny plants", "clusters", "dense clusters"}), 
             "Low plants grow in scattered clusters here. Their " +
             "deep green colour makes an attractive border for " +
             "the road, and their long, sharp thorns make sure " +
             "that travellers don't stray onto the rough, craggy " +
             "ground.\n"); 
    add_item(({"terrain", "rocks", "rocky terrain", "uneven terrain"}), 
             "The surrounding terrain is uneven and rocky. There hasn't " +
             "been any attempt to ready it for planting or building.\n"); 
    add_item(({ "gelan" }), 
             "You are " + where + " of the town of Gelan. " +
             "To get a look at the buildings you will have to enter " +
             "the town.\n"); 
}

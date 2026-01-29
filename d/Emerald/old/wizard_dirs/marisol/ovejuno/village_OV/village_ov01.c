
/* Re Albi village. Village's path I.
 * The crossroad.
 * Coded by Marisol (12/1/97)
 * Copyright (c) Marisol Ramos 1997*/
/* Modified by Marisol (07/12/98). Village of Ovejuno in Emerald.
 *Copyright (c) Marisol Ramos 1998*/


#pragma strict_types
#include "defs.h"
inherit OV_VILLAGE;


void
create_ov_room()
{
    set_short("A mountain's pass");
    set_long("A mountain's pass. High here in the mountain, this "+
        "pass is the access to the town of Ovejuno, one of the most "+
        "inaccesible and remote human settlement in the lands of "+
        "Emerald. In the distance you can hear the sheep bleating "+
        "in their pastures. The road split in this point. One path "+
        "goes straight to the village, another turn north to the lord's "+
        "castle, as the native called it, and the main path goes down "+
        "to the lowlands.\n");


    add_exit("village_ov02", "east");
    add_exit("castle_path/castle_path01", "north");



}


#include "defs.h";

inherit TELBERIN_RI;

void
create_telberin_ri()
{

    set_em_long("You are strolling along the Ri Circle in the mercantile "+
        "quarter. The street is cobblestone and looks beautiful as the "+
        "light flickers on it. You can feel a nice warm breeze here and "+
        "the air is filled with the sweetest scent of roses, coming from "+
        "the rose garden to the east. The sounds of merchants busy with "+
        "their wares can be heard here.\n"); 


    add_item(({"rose", "roses", "garden"}),
        "There is a rose garden east from here and the sweet scents from it "+
        "find their way here and linger. You can reach the garden by way of "+
        "the Royal Circle.\n");

    add_exit("tel05_07", "southeast");
    add_exit("tel04_09", "north");
}
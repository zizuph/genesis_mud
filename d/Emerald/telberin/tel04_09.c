#include "defs.h";

inherit TELBERIN_RI;

void
create_telberin_ri()
{

    set_em_long("You are on the Ri Circle in the mercantile quarter, "+
        "just south of the Western gate and the great West Avenue. The "+
        "street is surprisingly quiet and there is an intoxicating scent "+
        "of sweet roses coming from the rose garden to the east and it "+
        "fills the air here delightfully.\n");

    add_item(({"rose garden","rose bud", "rose buds", "roses"}),
        "You spy a few rose buds peeping through the hedge of the rose "+
        "garden. The sweet scent of roses delightfully fills your senses.\n");

    add_item(({"west avenue", "avenue", "western gate", "west gate"}),
        "To the north is the Western gate and the great West Avenue.\n");
  
    add_item(({"post office", "post", "office"}),
        "The grand Post office of Telberin is just west from here. The "+
        "outline of the building is far from modest. Grand details of "+
        "sculpturing went into creating this building which makes it a "+
        "masterpiece of elven architecture.\n");


    add_exit("tel04_08", "south");
    add_exit("tel04_10", "north");
    add_exit("post", "west");
}

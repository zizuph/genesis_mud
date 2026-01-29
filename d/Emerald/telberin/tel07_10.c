#include "defs.h";

inherit TELBERIN_WAVENUE;

void
create_west_avenue()
{
    set_short("West Avenue of Telberin, outside the Royal Palace");
    set_em_long("You are just outside of the magnificent gates of the Royal "+
        "Palace. Through the large gates you can see the great doors to the "+
        "palace, which are closed. The great West Avenue of Telberin begins "+
        "here at the Royal Circle extending out into the mercantile and "+
        "scientific quarters of the city.\n");

    add_item(({"great doors", "doors"}),
        "You look through the palace gate at the large double doors that "+
        "extend upwards to form an arch in the center of the palace. You "+
        "notice that there are symbols engraved along the outer edges leading "+
        "up to the center of arch.\n");

    add_item(({"arch"}),
        "You look at the arch that stems from the large double doors and "+
        "can see that there are many symbols engraved on the outer edge. "+
        "Above this arch you can clearly see the coat of arms as it draws "+
        "your attention.\n");

    add_item(({"symbols"}),
        "You are unable to recognize the symbols that are engraved on the "+
        "arch.\n");

    add_item(({"circle", "royal circle"}),
        "Royal Circle is the center of the city where the Palace, "+
        "Keepers of Telberin, Temple, and other government buildings are. "+
        "The road that surrounds the Royal Circle bares the same name.\n");



    add_exit("tel07_09", "south");
    add_exit("tel07_11", "north");
    add_exit("tel06_10", "west");
    add_door_exit(ROYAL_GATE, "palace/entry", "east");
}


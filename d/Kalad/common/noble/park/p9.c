inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* SARR */

void
create_room()
{
    ::create_room();
    set_short("Inside the Park of Kabal");
    set_long("You stand inside a beautiful park. A great hedge wall "+
    "surrounds you, providing you with comfort and privacy. You "+
    "are in a little shaded grove. The fountain is to your south.\n");
    add_item("fountain","It looks beautiful, perhaps you should "+
    "examine it more closer?\n");
    add_item(({"hedge","wall"}),"It is made of trees and bushes "+
    "and it towers over you, protecting you from outside.\n");
    add_item(({"animals","animal life","life"}),"You see "+
    "various birds, squirrels and rabbits abound.\n");
    add_item("birds","They sing sweet songs.\n");
    add_item("squirrels","They chatter loudly, jumping from tree "+
    "to tree.\n");
    add_item("rabbits","They hop along the grass, eating at the "+
    "leaves.\n");
    add_item("path","A very nice clean road that reflects the "+
    "bright Kaladian sun.\n");
    add_item("flowers","Flowers of all kinds and colors dot the "+
    "area.\n");
    add_item("trees","Big oak, cedars and pines dot the land, and "+
    "provide shade for you.\n");
    add_item("bushes","Little and big bushes alike with red berries.\n");
    add_item("stones","They are large flagstones.\n");
    add_item("berries","Never-wake-up berries.\n");
    add_exit(NOBLE(park/p10),"south",0,0,-1);
    add_prop(ROOM_NO_TIME_DESC,1);
}


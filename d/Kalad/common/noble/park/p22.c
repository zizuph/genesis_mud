inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* SARR */

int seeds_here;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("Inside the Park of Kabal");
    set_long("You stand inside a beautiful park. A great hedge wall "+
    "surrounds you, providing you with comfort and privacy. The "+
    "path you walk on is made of clean, white stones. There are "+
    "many flowers, trees and bushes all around you, as well as "+
    "various animal life. This is a dead end in the path, and "+
    "large statue stands here.\n");
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
    add_cmd_item("seeds",({"get","take"}),"@@get_seeds@@");
    add_item("seeds","@@seeds@@");
    add_item("bushes","Little and big bushes alike with red berries.\n");
    add_item("stones","They are large flagstones.\n");
    add_item("berries","Never-wake-up berries.\n");
    add_item("fish","@@fish");
    add_exit(NOBLE(park/p21),"northeast",0,0,-1);
    add_prop(ROOM_NO_TIME_DESC,1);
    clone_object(NOBLE(obj/statue))->move(TO);
    reset_room();
}

void
reset_room()
{
    seeds_here = 1;
}

string
fish()
{
    if(seeds_here)
        return "The fish is clutched in the deadly claws of the eagle, "+
        "and its mouth is open. You notice also in the mouth, a "+
        "few seeds.\n";
    else
        return "The fish is clutched in the deadly claws of the eagle, "+
        "and its mouth is open.\n";
}

string
seeds()
{
    if(seeds_here)
        return "Strange small silver seeds.\n";
    else
        return "You find no seeds.\n";
}


string
get_seeds()
{
    if(seeds_here)
    {
        seteuid(getuid());
        clone_object(NOBLE(obj/seeds))->move(TP);
        seeds_here = 0;
        return "You get the seeds from the mouth of the fish.\n";
    }
    else
        return "Get what?\n";
}
    

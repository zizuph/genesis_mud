inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/herbsearch";
#include "/d/Kalad/defs.h"

/* SARR */

int zintra;

void
create_room()
{
    ::create_room();
    set_short("Inside the Park of Kabal");
    set_long("You stand inside a beautiful park. A great hedge wall "+
    "surrounds you, providing you with comfort and privacy. The "+
    "path you walk on is made of clean, white stones. A shadowy "+
    "grove of bushes stands off to the side. "+
    "North leads to the exit of the park, "+
    "while south goes deeper into the park.\n");
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
    add_item("stones","They are large flagstones.\n");
    add_item("berries","Never-wake-up berries.\n");
    add_item("bushes","They form a dark groove.\n");
    add_item("groove","@@groove@@");
    add_exit(NOBLE(park/p3),"north",0,0,-1);
    add_exit(NOBLE(park/p5),"south",0,0,-1);
    add_prop(ROOM_NO_TIME_DESC,1);
    set_up_herbs(({"/d/Kalad/common/herbs/glowshroom"}),({"trees","bushes"}),8);
    reset_room();
}

void
reset_room()
{
    zintra = 1;
    set_searched(0);
}

string
groove()
{
    if(zintra)
        set_alarm(1.0,0.0,"summon_zintra",TP);
    return "You see nothing but darkness within. It looks scary.\n";
}

void
summon_zintra(object ob)
{
    object zin;
    seteuid(getuid());
    zin = clone_object(NOBLE(npc/zintra_in_park));
    zin->arm_me();
    zin->move_living("M",TO);
    tell_room(TO,"Suddenly, a "+zin->short()+" leaps out from within "+
    "the dark groove of bushes!\n");
    zin->command("kill "+lower_case(ob->query_name()));
    zintra = 0;
}


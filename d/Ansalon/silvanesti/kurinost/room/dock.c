
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include <ss_types.h>
#include <macros.h>


inherit KURINOST_OUT;

object ship;

void
add_stuff()
{
    seteuid(getuid(TO));
    if(!ship)
    {
	ship = clone_object(KPATH + "ship/ship");
	ship->start_ship();
    }
}

void
reset_kurinost_room()
{
    // set_alarm(1.0,0.0,add_stuff);
    return;
}

create_kurinost_room()
{
    set_short("Kurinost's dock on the Bay of Balifor");
    set_long("@@long_descr");


    add_item("silvanesti","This is the land of the Silvanesti Elves.  This "+
       "thickly forested regeion covers a large portion of the southeastern "+
       "face of Ansalon.  You are currently in the northeastern section of "+
       "the first elven nation.\n");
    add_item(({"bay","bay of balifor","Bay of Balifor","bay of Balifor"}),
       "The waters of the Bay of Balifor stretch to the north.  The deep "+
        "blue water ripples gently with the breeze.\n");
    add_item("dock","This dock is new in comparison with those slightly "+
       "east from here.  It was hastily built to service the Green "+
       "Dragonarmy's occupation of Silvanesti.\n");
    add_item(({"camp","tents"}),"Some tents lie to the southwest marking "+
       "the Green Dragonarmy's camp.\n");
    add_item("kurinost","The deserted city of Kurinost lies to the south"+
       "east.\n");
    add_item(({"road","path"}),"The path leads southeast towards Kurinost.\n");
    add_item(({"tree","trees"}),"The trees here look normal and healthy.\n");
    add_exit(KROOM + "road","south",0);

    reset_kurinost_room();
}

string
long_descr()
{
    return "You stand at a newly built dock that services the "+
    "Green Dragonarmy.  The Bay of Balifor is to the north "+
    "and the Silvanesti town of Kurinost is to the southeast."+
    "  "+
    season_descr()+tod_descr1()+"\n";

}


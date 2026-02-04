/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";


object refugee1;
object refugee2;
object refugee3;
object refugee4;


public void
reset_room()
{
    if (!refugee1) {
        refugee1=clone_object(MOUNTAIN_DIR + "elderwood/npc/std_refugee");
        refugee1->move(this_object());
    }

    if (!refugee2) {
        refugee2=clone_object(MOUNTAIN_DIR + "elderwood/npc/std_refugee");
        refugee2->move(this_object());
        refugee1->team_join(refugee2);
    }

    if (!refugee3) {
        refugee3=clone_object(MOUNTAIN_DIR + "elderwood/npc/std_refugee");
        refugee3->move(this_object());
        refugee1->team_join(refugee3);
    }

    if (!refugee4) {
        refugee4=clone_object(MOUNTAIN_DIR + "elderwood/npc/std_refugee");
        refugee4->move(this_object());
        refugee1->team_join(refugee4);
    }
 
}


public void
create_room()
{
    ::create_room();

    INSIDE;
    set_long("You stand inside a large canvas tent. Several " +
       "woolen and fur blankets line along the wooden floor of the " +
       "tent. A warm cozy fire burns in a pit dug in the middle of " +
       "the tent.\n");

    add_item(({"tent","tents"}),
       "The tents are made of heavy canvas covered in thick furs. " +
       "The tents look large enough to house atleast eight people.\n");

    add_item(({"fire","pit","firepit"}),
       "A cozy fire burns steadily providing warm to the tent.\n");

    add_item(({"floor","wooden floor"}),
       "A makeshift wooden floor provides shelter from the cold " +
       "earth below. Several blankets and furs provide additional " +
       "insolation from the cold floor.\n");

    add_item(({"woolen blankets","blankets","fur","furs","blanket"}),
       "Several warm looking blankets and furs line the floor.\n");

    add_tell("The fire flickers steadily.\n");
    add_tell("A tent flap blows in the wind.\n");

    add_cmd_item(({"blanket","blankets","fur","furs"}),
                 ({"get","take","steal"}),
                   "These people have nothing. and " +
                   "you would steal their blankets? For shame!\n");

    add_exit(FIELD_DIR  + "field_d2", "out",0,4,1);


    reset_room();
}
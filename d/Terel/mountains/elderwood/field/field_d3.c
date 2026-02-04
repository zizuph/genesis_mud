/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/field";

object refugee1;
object refugee2;
object warrior;
string enter_tent();


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
      if (!warrior) {
        warrior=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior->move(this_object());
        refugee1->team_join(warrior);
    }
}


public void
create_room()
{
    ::create_room();

    set_long(query_long() + "The field ends before a sheer " +
       "cliff face. Someone has build a tent city here. " +
      "Several fires burn about the tents heating food " +
      "and the inhabitants. To the northeast you can see " +
      "a pass leading further into the mountains.\n");

    add_item(({"tent","tents"}),
       "The tents are made of heavy canvas covered in thick furs. " +
       "The tents look large enough to house atleast eight people.\n");

    add_tell("The fire flickers in the cold breeze.\n");
    add_tell("A tent flap blows in the wind.\n");

    add_cmd_item("tent","enter", enter_tent);


    add_exit(FIELD_DIR  + "field_d4", "east",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c3", "south",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c4", "southeast",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_c2", "southwest",0,4,"@@exits");
    add_exit(FIELD_DIR  + "field_d2", "west",0,4,"@@exits");

    reset_room();
}

string
enter_tent()
{

    write("You push aside the tent flap and enter the tent.\n");
       TP->move_living("by entering the tent", 
       MOUNTAIN_DIR + "elderwood/field/tent_d3",1,0);
       return "";
}



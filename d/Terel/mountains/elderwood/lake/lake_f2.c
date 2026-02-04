/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

inherit STDROOM;
// inherit LAKE_BASE;

#define LAKE_DIR           (ELDERWOOD_DIR + "lake/")

public void
reset_room()
{
//    set_fished(0);
}

object fish;

public void
create_room()
{
    ::create_room();
    set_short("southern side of the lake");
    set_long("You are standing waist high in a cold and frigid " +
       "mountain lake. The forest can be seen all along the lake. " +
       "The lake extends north and east. You can return to the forest " +
       "by wading towards the south or west.\n");

    add_cmd_item("north","swim","@@go_north");
    add_cmd_item("east","swim","@@go_east");
    add_cmd_item("west","wade","@@go_west");
    add_cmd_item("northwest","wade","@@go_northwest");
    add_cmd_item("northeast","swim","@@go_northeast");
    add_cmd_item("south","wade","@@go_south");

    add_cmd_item("down",({"swim","dive"}),"You dive down into the water, " +
      "but nothing catches your attention, so you return to the " +
      "surface.\n");

    reset_room();
}

public string
go_north()
{
    write("You swim to the north.\n");
    set_dircmd("north");
    TP->move_living("swims north",LAKE_DIR + "lake_g3", 0, 0);
    return "";
}


public string
go_northeast()
{
    write("You swim to the northeast.\n");
    set_dircmd("northeast");
    TP->move_living("swims northeast",LAKE_DIR + "lake_g4", 0, 0);
    return "";
}

public string
go_northwest()
{
    write("You wade across the lake and enter the forest towards " +
          "the northwest.\n");
    set_dircmd("northwest");
    TP->move_living("wades northwest",FOREST_DIR + "forest_g2", 0, 0);
    return "";
}

public string
go_east()
{
    write("You swim to the east.\n");
    set_dircmd("east");
    TP->move_living("swims east",LAKE_DIR + "lake_f4", 0, 0);
    return "";
}

public string
go_west()
{
    write("You wade west out of the water and enter the forest.\n");
    set_dircmd("west");
    TP->move_living("wades west",FOREST_DIR + "forest_f2", 0, 0);
    return "";
}

public string
go_south()
{
    write("You wade south out of the water and enter the forest.\n");
    set_dircmd("south");
    TP->move_living("wades south",FOREST_DIR + "forest_e3", 0, 0);
    return "";
}


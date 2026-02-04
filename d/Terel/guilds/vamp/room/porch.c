//-*-C++-*-
// file name:      porch.c
// creator(s):     Louie 2006
// last update:    Lilith June 2008 - updated room desc and functionality
// note: 
// bug(s):
// to-do:
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>


public void create_vamp_room()
{

    set_short("Porch");
    set_long("All that remains of a magnificent colonnaded portico "+
        "that once surrounded this ancient mansion is this small "+
        "section just outside the gaping front entrance. Mud-brick "+
        "and plaster debris litters the ground, as though the "+
        "building has some leprotic affliction. Dark and decaying, "+
        "this place is so cold that you doubt any creature would "+
        "take shelter here. East is a side yard, mostly buried "+
        "under rubble and snow.\n");
    add_item(({"debris", "mud-brick", "plaster"}), 
        "The efforts of man are no match for nature.\n");
    add_item(({"ground", "rubble", "litter", "snow"}), 
        "The ruins of the portico clutter the ground, laid waste "+
        "by time and the seasons.\n");
    add_item(({"entrance", "front entrance", "doorway"}), 
        "It is dark and breathes a dank coldness.\n");
    add_item(({"mansion", "building", "shelter", "domus"}), 
        "It was built in another age, and it is slowly decaying "+
        "to ruins.\n");
    add_item(({"portico", "porch"}), "Once a grand structure with "+
        "columns and a roof, it once stretched along the face of "+
        "the mansion and extended northeast toward some out"+
        "buildings.\n");
    add_item(({"yard", "side yard", "outbuildings"}), 
        "The yard is buried under rubble and snow, as are "+
        "the two outbuildings.\n");
    
    add_exit("entry","north", "@@do_north");
    add_exit("outside", "east", "@@do_east");
    add_exit("gate_inside", "south");  
    add_prop(ROOM_I_LIGHT,1);
    remove_prop(ROOM_I_INSIDE);
    
}

int
do_north()
{
    write("You step over a small pile of debris and through "+
        "the doorway.\n");
    say(QCTNAME(TP) +" steps over a pile of debris and through "+
        "the doorway.\n");
    return 0;   
}

int
do_east()
{
    write("You pick your way through the remnants of columns and "+
        "other debris.\n");
    say(QCTNAME(TP) +" walks eastwards, stepping carefully "+
        "through the debris.\n");
    return 0;   
}


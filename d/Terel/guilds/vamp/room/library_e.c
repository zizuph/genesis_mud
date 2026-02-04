//-*-C++-*-
// file name:      library_e.c
// creator(s):     Lilith June 2008
// last update:    
// note:           Council room of sorts of Elder Vamps
// bug(s):
// to-do:  niche for holding special items

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";
//inherit "/d/Genesis/lib/post";

#include <ss_types.h>
#include <math.h>
#include <composite.h>
#include <std.h>
#include <filter_funs.h>
#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>

//#define MAILCHECKER    "/secure/mail_checker"
//#define DIARY_LOG    (LOG_DIR+"diary")

//int alarm_id;

/*
public void configure_shelf(object shelf,int slot)
{
    shelf->set_name("shelf");
    shelf->add_name("recess");
    shelf->add_name("arcosolium");
    shelf->add_name("tomb");
    shelf->add_name("niche");
    shelf->add_name("rack");
    shelf->set_allow_glowing(1);
    shelf->set_allow_nonglowing(1);
    shelf->set_allow_weapon(1);
    shelf->set_allow_armour(1);
    shelf->set_allow_misc(1);
    shelf->set_noshow_obvious(1);
    shelf->set_short("tomb");
    shelf->set_long("This is an arched recess in the wall, once intended "+
    "to hold the remains of the deceased. There is no body here however, "+
    "and the " + shelf->short() + " appears to be used now for "+
    "storage.\n");
}


public void create_shelves()
{
    object shelf=clone_object(OBJ_DIR+"rack");
    configure_shelf(shelf, 1);
    shelf->move(TO);
    
    set_shelves(shelf);
}
*/

public void create_vamp_room()
{

    set_short("Ancient sepulchre");
    set_long("A burial chamber in the deepest, darkest part of the "+
        "catacombs, a chamber whose secrets were lost until the "+
        "oldest and wisest of the vampyrs discovered it and "+
        "converted it to their private purposes.\n"+ 
        "This sepulchre appears to have been dug out of the living "+
        "stone of the mountain long, long ago. A low shelf, just "+
        "long enough to fit a body, was cleared of any remains and "+
        "set aside for storing items of use to the Coven. "+
        "Some chairs have been arranged in a circle around "+
        "a hammered steel bowl in the center of the room. "+
        "The floor is bare stone that once had a design "+
        "painted on it.\n");


    add_item(({"floor", "design", "paint", "decoration"}), 
        "The floor is level and bare stone with "+
        "ancient bits of paint indicating that there was once a "+
        "decoration of some sort there.\n");
    add_item(({"ceiling"}), "The ceiling is the same "+
        "height as most of the other ceilings in this place.\n");
    add_item(({"wall", "walls", "stone", "natural stone"}), 
        "The walls are cut from the natural subterranean stone. They are "+
        "completely unadorned and unpolished.\n");
    add_item(({"chair", "chairs", "circle", "circle of chairs"}), 
        "A half dozen unmatching chairs are arranged in a circle. "+
        "All are so old that the wood looks more like stone.\n");
    add_item(({"darkness"}), 
        "Back the way you came there is a very deep darkness that "+
        "pulses a bit. It has a substance to it that no amount of "+
        "light can conquer. It appears to be the only way out.\n");
    add_cmd_item(({"air", "blood"}), ({"smell", "sniff", "breathe"}),
        "The air is ripe with the coppery scent of blood.\n");
    add_item(({"bowl", "hammered bowl", "hammered steel bowl", "steel bowl"}),
        "It is a broad bowl made of hammered steel and filled with blood. "+
        "It appears to ripple and flash with colours. You feel a compelling "+
        "urge to <stare> into it.\n");
    add_item(({"blood"}), "It is thick and richly red, and it reeks of "+
        "power, power reminiscent of The Eldest, of the most arcane of "+
        "blood-magicks.\n");
        
//    add_exit("library_p", "darkness", 1, 1);

//    create_shelves();


}


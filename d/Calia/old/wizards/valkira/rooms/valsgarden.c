// ROOM:  Valkira's garden - /d/Calia/valkira/rooms/valsgarden.c

    /*  Calia Domain

        HISTORY
        8/17/99 Adaptation by Valkira 8/17/99 using 
                Temple archway leading into the Worshippers Temple
                [/d/Calia/worshippers/temple/archway.c - By Jaacar, 1996
        9/1/99  Directory change, annotation added.
 
        PURPOSE
        Multipurpose portal area and garden.  Will practice placing
        herbs with this file.
    */

// INCLUSIONS AND DEFINITIONS

#pragma save_binary

inherit "/std/room";                   /* standard room                    */
inherit "/d/Calia/std/room_tell_room"; /* Used for room tell routines      */

#include "/d/Calia/domain.h"           /* Default include file for  
                                          Calia Domain                      */
#include <stdproperties.h>             /* ( /sys/stdproperties.h ) This file
                                          holds definition of all the standard
                                          properties that an object can have.
                                          The documentation for the properties
                                          can all be found in the directory
                                           /doc/man/properties              */
#include <macros.h>                    /* ( /sys/macros.h) This file contains
                                          various useful macros.            */
#include <ss_types.h>                  /* ( /sys/ss_types.h) This file 
                                          defines the available stats and 
                                          skills. Use this file in conjunction
                                          with query_stat() and query_skill()
                                          calls.                            */
#include "/d/Krynn/common/herbsearch.h"

#define KRYNN_HERBS "/d/Krynn/common/herbs/"

#define ROOMS  "/d/Calia/valkira/rooms/"

// ROOM DESCRIPTION

void reset_herb_room()
{
    set_searched(random(6));    /* Lots of plant life here */
}

void
reset_room()
{
    reset_herb_room();
}

void
create_room()
{
    object door;


    set_short("Valkira's Garden");
    set_long("This is a quiet spot.  You see all sorts of plants" +
        " here, both ornamental and herbal. A dark green bush with" +
        " white flowers is planted by the window. There is a door" +
        " that will take you back into Valkira's Room. At the" +
        " end of the path there is a sign.\n");

    /* ITEMS */

     add_item(("sign"),
        "      ________________________    \n" +
        "     |                        |   \n" +
        "     |  Calia Workroom --->>> |   \n" +
        "     |  <<<---   Tower Office |   \n" +
        "     |________________________|   \n"); 

    add_item("bush","This is a gardenia. It has dark green leaves" +
        "and white fragrant flowers.\n");

    add_item(("garden"),"The garden is somewhat wild and needs" +
        "tending./n");

    add_item(({"small flowers","flowers"}),"These flowers are "+
        "various colours.  Some grow from the bushes themselves, "+
        "some grow on their own from the ground.\n");

    add_item("door","The door is open, allowing soft breezes" +
        "to drift through to the room beyond.\n");

    add_item("plants","These leafy plants are a beautiful "+
        "green colour and appear to be very healthy.\n");

    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS,1);
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    set_search_places(({"here", "garden", "plants"}));


    add_herb_file(KRYNN_HERBS+"cladina");
    add_herb_file(KRYNN_HERBS+"fireweed");
    add_herb_file(KRYNN_HERBS+"grey_willow");
    add_herb_file(KRYNN_HERBS+"blk_currant");
    add_herb_file(KRYNN_HERBS+"chokecherry");
    add_herb_file(KRYNN_HERBS+"hawthorn");
    add_herb_file(KRYNN_HERBS+"hazelnut");
    add_herb_file(KRYNN_HERBS+"raspberry");
    add_herb_file(KRYNN_HERBS+"saskatoon");
    add_herb_file(KRYNN_HERBS+"crocus");
    add_herb_file(KRYNN_HERBS+"tiger_lily");
    add_herb_file(KRYNN_HERBS+"veronica");
    add_herb_file(KRYNN_HERBS+"chicory");
    add_herb_file(KRYNN_HERBS+"bunchberry");
    add_herb_file(KRYNN_HERBS+"lady_slipper");
   
    set_tell_time(100);
                
    add_tell("A slight breeze touches your cheek.\n");

    /* EXITS */
    door=clone_object(ROOMS+"gdoorin.c"); /* front door from garden */
    door->move(this_object());
    add_exit("/d/Calia/valkira/rooms/valsroom", "door");
    add_exit("/d/Calia/workroom", "east");
    add_exit("/d/Calia/domain_office", "west");
    
}

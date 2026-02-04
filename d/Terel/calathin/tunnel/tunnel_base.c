/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Shaft_base.c
 * 
 * Calathin escape shaft base file
 * Tomas -- July 2000
 *
 * Fixed typo in long desc 
 * Lilith -- May 2008
 */


#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

inherit "/d/Terel/std/room_tell.c";
inherit STDROOM;

#define  DEFAULT   CALATHIN_DIR + "tunnel/"


object pebble;
int ext_sconce = 1;


/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
    start_room_tells();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "The air smells of sweat and burning pitch.\n";
}

/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */ 
public int
do_smell(string str)
{
    NF("Smell what?\n");
    if (!strlen(str))
        return 0;
    
    if (str == "air" || str == "sweat" || str == "pitch") {
        write(smell_desc());
        return 1;
    }
    return 0;
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{

    ::create_room();
    set_short("in a manmade tunnel");
    set_long("@@change_long@@");
 
    set_tell_time(500 + random(200));

    add_item(({"tunnel", "shaft", "tunnels"}),
             "A typical manmade tunnel. Designed for a hasty retreat " +
             "out of the city. Strong beams support the ceiling and walls.\n");
    add_item(({"darkness"}),
             "A dark black void. You cant see anything beyond.\n");
    add_item(({"shaft floor", "floor","ground"}),
         "The floor contains large deposits of dust built up " +
         "over the years.\n");
    add_item(({"deposits","dust"}),
       "Deposits of dust collect around the rocks,support beams " +
       "and the shaft floor. You notice several manmade boot " +
       "prints on the dusty floor\n");
    add_item(({"footprints","prints","boot prints"}),
       "You notice several boot prints on the dusty floor.\n");
    add_item(({"ceiling"}),"The rocky ceiling above is held at bay " +
       "by several wooden support beams spaced evenly throughout " +
       "the shaft.\n"); 
    add_item(({"wooden support beams","wood","support beams","beams"}),
       "The thick beams appear twisted and have splintered over the " +
       "years. Most sag under the constant pressure from the ceiling " +
       "above. You hope that they hold a little while longer.\n");

    add_item(({"walls","wall"}),"The walls rocky surface appear to be " +
       "marred by manmade tools.\n"); 

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");
    add_item(({"pitch","iron sconce","sconce"}),"@@sconce@@");
 
    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),
                   "@@get_pebble");

    add_cmd_item(({"sconce","pitch"}),
                 ({"get","take"}),
                   "You cant remove the sconce or the pitch.\n");

    add_cmd_item(({"pitch","sconce"}),
                 ({"extinguish"}),
                   "@@extinguish");

    add_cmd_item(({"pitch","sconce"}),
                 ({"light"}),
                   "@@light_sconce");

    add_cmd_item(({"walls","wall"}),
                 ({"touch","feel"}),
                   "The walls feel smooth to the touch, almost as if " +
                   "used sandpaper on them. The tunnel looks like it " +
                   "was once underwater.\n");

    INSIDE;

}


get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You pickup a pebble from the ground.\n");
       say(QCTNAME(TP) + " reaches down and picks up a pebble.\n");
    return 1;
}

string
sconce()
{
   if (ext_sconce == 1)
   {
     return "An iron sconce can be seen attached to the rock wall. " +
            "A chain dangling from the sconce holds a large " +
            "pot containing pitch.\n";
   }
     return "An iron sconce can be seen attached to the rock wall. " +
            "A chain dangling from the sconce holds a large " +
            "pot containing burning pitch, which provides " +
            "light to the tunnel.\n";
}
     

public int
extinguish()      // Extinguish the sconce.
{
   if (ext_sconce == 1)
   {
       NF("The sconce isn't lit.\n");
       return 0;
   }

   ext_sconce = 1;  // Extinguish the wall sconce.
   write("Using the iron lid, you snuff out the burning " +
         "pitch within the wall sconce.\n");
   say(QCTNAME(TP) + " snuffs out the burning pitch by closing " +
         "the iron lid on the wall sconce.\n");

   DARK;            // add darkness to the room.

   return 1;
}


public int
light_sconce()        // Light the sconce
{
    if (ext_sconce == 0)
    {
       NF("The wall sconce is already lit.\n");
       return 0;
    }
    if (ext_sconce == 1)   // The sconce is not lit.
    {
       write("You light the pitch within the wall sconce pot.\n");
       say(QCTNAME(TP) + " lights the wall sconce.\n");

       add_prop(ROOM_I_LIGHT, 1);  // Add light to the room.
       ext_sconce = 0;    // add light to the room.
       return 1;
    }
    return 1;
}


string
change_long()
{
    if( ext_sconce == 0 )   // we add light to the long desc.
    {
       return "The tunnel appears to have been abandoned " +
             "a long time ago. You figure the tunnel was designed " +
             "as an escape route for the citizens of Calathin in times " +
             "of trouble. Although dusty and full of cobwebs, the tunnel " +
             "appears to be in good shape. The tunnel is lit " +
             "by burning pitch held in an iron sconce on the wall. ";
    }

    if( ext_sconce == 1 )  // someone extinguished the sconces. No light.
    {
       return "The tunnel appears to have been abandoned " +
             "a long time ago. You figure the tunnel was designed " +
             "as an escape route for the citizens of Calathin in times " +
             "of trouble. Although dusty and full of cobwebs, the tunnel " +
             "appears to be in good shape. You notice an " + 
             "extinguished wall sconce attached to one of the walls. ";         
    }

}


/*
 * /w/petros/sparkle/library/obj/info_packet.c
 *
 * Informational Packet about the Genesis Library
 *
 * Created April 2008, by Petros
 */
 
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <files.h>

#include "defs.h"

// Defines

// Global Variables
public int          destroy_alarm = 0;

// Prototypes
public void             create_object();
public int              read_cmd(string arg);

/*
 * Function name:       create_object
 * Description  :       creates the object.
 */
public void
create_object()
{
    set_name("_informational_packet");
    add_name( ({"informational_packet", "packet"}) );
    add_adj( ({ "little", "informational", "genesis", "library" }) );
    set_short("little informational packet");    
    set_long("This is the Genesis Library informational packet. You can "
           + "<read> it to see what it has to say.\n");
    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_SELL, "No one would want to buy this since it is "
                          + "free informational packet.\n"); 
} // create_object


/* Function name:       init
 * Description  :       adds the action
 */
public void
init()
{
    ::init();    
    
    add_action(read_cmd, "read");
} // init

/* Function name:       read_cmd
 * Description  :       This is the text for the informational packet
 *                      and prints out the message to the person who
 *                      reads it.
 * Arguments    :       arg - parameters
 * Returns      :       0/1 - whether command was successful.
 */
public int
read_cmd(string arg)
{
    object packet;
    
    packet = PARSE_COMMAND_ONE(arg, this_player(), "[the] %i");
    if (packet
        && MASTER_OB(packet) == (LIBRARY_OBJ_DIR + "info_packet"))
    {
        write("You unfold the informational packet and begin to read it.\n\n");
        write("Genesis Library Informational Packet\n"
               + "====================================\n\n"
               + "Welcome to the Genesis Library of Sparkle! Here you will "
               + "find some of the best information about the Donut of "
               + "Genesis, the people that inhabit it, and how to survive in "
               + "this land. Here at the Library, we hope that you will find "
               + "anything you need.\n\n"
               + "The west wing contains most of the information you will "
               + "ever need about the various guilds of the land. The east "
               + "wing contains information about domains, as well as some "
               + "references, guides, and tutorials. You can grab a tutorial "
               + "journal in the tutorials and guides section, and you can "
               + "grab a magic map from the maps and references section.\n\n"
               + "Should you require any assistance, "
               + "please be sure and ask me. Otherwise, <browse> around and "
               + "enjoy the reading. Oh, and if you get lost, you should "
               + "definitely consult the magic map.\n\n"
               + "Nikolon, Head Librarian of the Genesis Library\n"
               + "\n\n");
        // Show others that you are reading the packet
        say( ({ this_player()->query_met_name()
                  + " unfolds a packet and begins to read it.\n",
                "The " + this_player()->query_nonmet_name() 
                  + " unfolds a packet and begins to read it.\n",
                "" // unseen people won't display a message
              }) );
        return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}

public void
vanish(object obj)
{
    if (!objectp(obj))
    {
        return;
    }
    
    if (IS_PLAYER_OBJECT(obj))
    {
        obj->catch_tell("As you drop the " + short() + ", it billows "
            + "slowly to the ground and disappears in a puff of smoke.\n");
        tell_room(environment(obj), "As " + QTNAME(obj) + " drops the "
            + short() + ", it billows slowly to the ground and "
            + "disappears in a puff of smoke.\n", ({ obj }));
    }
    remove_object();
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    // If someone drops this packet in the room, we remove it.
    if (IS_ROOM_OBJECT(dest))
    {
        if (get_alarm(destroy_alarm))
        {
            remove_alarm(destroy_alarm);
        }
        destroy_alarm = set_alarm(0.0, 0.0, &vanish(old));
    }
}

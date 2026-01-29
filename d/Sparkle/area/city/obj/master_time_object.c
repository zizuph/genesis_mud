/*
 * /d/Sparkle/area/city/obj/master_time_object.c
 *
 * This unique object will control all time operations in the
 * City of Sparkle
 *
 * Created April 2008, by Petros
 */
 
#pragma strict_types

inherit "/std/object";
inherit "/d/Sparkle/lib/libs_clock";

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

// Global Variables
string *        registered_npcs;

// Prototypes
public void             create_object();
public void             notify_npcs();
public void             register_npc(string filename);
private void            save_data();
private void            load_data();


/*
 * Function name:       create_object
 * Description  :       creates the object.
 */
public void
create_object()
{
    set_name("_sparkle_master_clock");
    add_name( ({"sparkle_master_clock", "clock"}) );
    set_short("sparkle master clock");    
    set_long("This is the master timekeeper for the City of Sparkle."
           + "\n\n");
           
    load_data();
} // create_object


/* Function name:       init
 * Description  :       adds the action
 */
public void
init()
{
    ::init();    
} // init

/*
 * Function name: load_data
 * Description  : Load the information from disk
 */
void
load_data()
{
    setuid();
    seteuid(getuid());

    registered_npcs = ({ });
    // If the file exists, load it from disk
    if (file_size(SPARKLE_NPC_DATA + ".o") > 0)
    {
        restore_object(SPARKLE_NPC_DATA);
    }
}

/*
 * Function name: save_data
 * Description  : Persists the state of the box to disk
 * Arguments    : none
 * Returns      : nothing
 */
private void
save_data()
{
    seteuid(getuid());
    save_object(SPARKLE_NPC_DATA);
}

public void
notify_npcs()
{
    object * clones;
    int      time_seconds;
    int      number_of_npcs;
    
    number_of_npcs = 0;
    time_seconds = s_get_time();
    foreach (string filename : registered_npcs)
    {
        if (!find_object(filename))
        {
            // The master npc object hasn't even been
            // loaded yet. No npcs exist yet.
            continue;
        }
        clones = object_clones(find_object(filename));
        foreach (object curclone : clones)
        {
            number_of_npcs++;
            curclone->alert_hour_change(time_seconds);
        }
    }
}

public void
register_npc(string filename)
{
    if (!IN_ARRAY(filename, registered_npcs))
    {
        registered_npcs += ({ filename });
        save_data();
    }
}

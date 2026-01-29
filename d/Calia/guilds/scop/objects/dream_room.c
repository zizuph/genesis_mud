/*
 *   Dream room. This is where we place casters who are using the Oneiro spell. 
 *
 *   Bishop, May 2004.
 */
 
  
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define PLAYER_S_LD_IN_ROOM "_player_s_ld_in_room"
#define SCOP_O_SLEEP_LOCATION "_scop_o_sleep_location_"


void
create_room()
{
    set_short("");
    set_long("");
        
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_I_LIGHT, 1);
    
}

public int
query_prevent_snoop()
{
    return 1;
}

void
leave_inv(object ob, object dest)
{
    object old_room, spellob;

    old_room = ob->query_prop(SCOP_O_SLEEP_LOCATION);

    ::leave_inv(ob, dest);
    
    if (objectp(old_room))
    {
        if (old_room != dest)
        {
            //This means the player is leaving the dream room by linkdying 
            //, being teleported in some way, or scrying someone.
 
            spellob = present("_oneiro_ob_", ob);
            
            //Linkdeath:
            if (ob->query_prop(PLAYER_S_LD_IN_ROOM))
            {
                ob->add_prop(PLAYER_S_LD_IN_ROOM, file_name(old_room));
                spellob->dispel_spell_effect(ob, 1);
            }
            //Scrying or being teleported. Add this prop so trans -r won't
            //put them in the dream room with nowhere to go.
            else
            {
                ob->add_prop(LIVE_O_LAST_ROOM, old_room);
            }
        }
    }
}


                  
       
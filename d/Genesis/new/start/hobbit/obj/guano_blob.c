/*
 * File         : /d/Genesis/start/hobbit/obj/guano_blob.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/28/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is a blob of guano.
 * 
 * TODO         :
 * - add check for other blobs => self destruct or heaps
 * - add decay => make it a herb
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types
/* inherits */
inherit "/std/object";


/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <wa_types.h>
#include <formulas.h>
#include "../hobbit.h"
/* defines */
#define SUBLOC "got_blob_of_guano"

/* prototypes */


/* globals */


/*
 * Function name:       create_object
 * Description  :       set up the object
 */
void
create_object()
{
    set_name("blob of guano");
    
    set_long(
      "It is bird excrements.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_WEIGHT, 3);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/28/99.\n");
    
    set_adj("slimy");
    // set_no_show();
    add_item("guano", "It is bird excrements.\n");
    
    
}
// A living was hit by this blob of guano (hehe)
void
enter_env(object to, object from)
{
    if (living(to))
    {
        to->add_subloc(SUBLOC, this_object());
    }
    ::enter_inv(to, from);
}

// If the blob of guano is removed we detect it here
public void
leave_env(object from, object to)
{
    if (living(from))
    {
        from->remove_subloc(SUBLOC);
    }
    ::leave_env(from, to);
}

// Called when listning of subloc should be done.
string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return ""; // Don't show this sublocation as inventory.
    }
    if (for_obj == carrier)
    {
        str = "You are ";
    }
    else
    {
        str = capitalize(carrier->query_pronoun()) + " is ";
    }
    return str + "smeared with guano.\n";
}

// Called when a player sniffs at the blob
void
hook_smelled()
{
    write("The blob smells like rotten fish!\n");
    // this_player()->command("emote grimaces.\n"); // Doesn't work
}



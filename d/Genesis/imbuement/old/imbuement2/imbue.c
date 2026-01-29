/*
 *
 */
#pragma strict_types
#include "imbuement.h"

#include <macros.h>
#include <files.h>


/* Prototypes */

/* Global Variables */
string              imbuement = "r";

#define IMBUE_ROOMS     ({ "efaef",\
                           "/w/lavellan/room_m" })
#define GENERATOR       "/d/Genesis/imbuement/imbuement2/imbuement_master"

/*
 * Function name:        create
 * Description  :        set up
 */
public void
create()
{
    setuid();
    seteuid(getuid());
    
    LISTENER_ADD(this_object());
} /* create */

/*
 * Function name:        notify_new_object
 * Description  :        called when something is cloned
 */
public void
notify_new_object(object obj)
{
//    TELL_G("New object: " + file_name(obj));
    if ((member_array(MASTER_OB(environment(obj)), IMBUE_ROOMS) >= 0) ||
        (member_array(MASTER_OB(environment(environment(obj))), IMBUE_ROOMS) >= 0))
    {
        if (!IS_WEAPON_OBJECT(obj))
            return;
        TELL_G("Imbuing!");
//        GENERATOR->add_imbuement(obj,imbuement,1,1);
        GENERATOR->imbue(obj, imbuement, 1);
    }
}


public void
set(string new)
{
    imbuement = new;
    TELL_G("Set to " + imbuement);
}
/*
 *  /d/Emerald/common/guild/aod/lib/add_spike.c
 *
 *  This module can be included in room files which are intended to
 *  be able to clone trophy spikes into their inventories.
 *
 *  Copyright (c) July 2006, by Cooper Sherry (Gorboth)
 *
 *  Useage:
 *
 *  To use this module, in your create() function, make the following call:
 *
 *      add_spike("unique_id");
 *
 *  This will create a spike in the room upon which players can mount
 *  a trophy of a head they have collected. Save information for the
 *  specific trophy spike is stored in the following directory:
 *
 *      /d/Emerald/common/guild/aod/log/trophy_save/
 *
 *  The file names in the save dir are equivalent to the "unique_id"
 *  arg passed in the add_spike() call. Obviosly, one must take care not
 *  to use the same id twice.
 */
#pragma strict_types

#include "../defs.h"


/*
 * Function name:        add_spike
 * Description  :        add a trophy spike to this room.
 * Arguments    :        string unique_id -- a unique filename for save
 */
public void
add_spike(string unique_id)
{
    object  spike;

    if (!unique_id)
    {
        return; /* no id, no spike */
    }

    spike = clone_object(AOD_OBJ_DIR + "spike");
    spike->set_spike_id(unique_id);
    spike->move(this_object());
    spike->update_spike();
} /* add_spike */

/*
 * /d/Gondor/pelargir/misc/repair_dock.h
 *
 * Definitions for the quest to repair the dock in the harbour.
 *
 * Olorin, January 1997
 */
#ifndef PELARGIR_REPAIR_DOCK_DEFINITIONS
#define PELARGIR_REPAIR_DOCK_DEFINITIONS

#define PELARGIR_I_REPAIR_DOCK          "_pelargir_i_repair_dock"

#define REPAIR_TASK              1
#define REPAIR_REMOVE            2
#define REPAIR_PLANK             4
#define REPAIR_SAW               8
#define REPAIR_REPLACE          16
#define REPAIR_NAIL             32
#define REPAIR_LAST             32
#define REPAIR_DONE             63

#define SET_STAGE(x, i) \
    if ((x)->query_prop(PELARGIR_I_REPAIR_DOCK) & REPAIR_TASK) \
        (x)->add_prop(PELARGIR_I_REPAIR_DOCK, \
               (x)->query_prop(PELARGIR_I_REPAIR_DOCK) | (i) );

#endif /* PELARGIR_REPAIR_DOCK_DEFINITIONS */

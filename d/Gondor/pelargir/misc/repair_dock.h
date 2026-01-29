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
#define REPAIR_REPLACE           4
#define REPAIR_NAIL              8

#define SET_STAGE(x, i)          (x)->add_prop(PELARGIR_I_REPAIR_DOCK, \  
    (x)->query_prop(PELARGIR_I_REPAIR_DOCK) | (i) );  
#endif

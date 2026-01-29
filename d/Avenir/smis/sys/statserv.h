// file name:        /d/Avenir/smis/sys/statserv.h
// creator(s):       Denis, Apr 1996
// purpose:          Header file for statserv.
// note:             For more information see
//			/d/Avenir/smis/modules/statserv.c
//			    and
//			/d/Avenir/smis/doc/statserv.doc
/*  Revision:
 *     Denis, May 1996: Moved with statserv.c and changed
 *			apropriate # defines.
 */
#include "../smis.h"

#define STATSERV_LOG_EVENT(topic, what) \
    SMIS_MANAGER->query_module_object("statserv")->log_event(topic, what)


/*
 * message.c
 *
 * This file is an interface which can be inherited by weapons/spells
 * which wants to produce nifty outputs, like for instance Dain's waraxe.
 *
 * The actual printout is actually done in ./messfile.c
 *
 * Sir Rogon.
 */

#include "defs.h"
#include <language.h>

#define MESS_FILE (THIS_DIR + "messfile")

private object mess_handler;

void
init_handler()
{
    FIXEUID;
    MESS_FILE->load_me();
    mess_handler = find_object(MESS_FILE);
}

varargs void
do_tell(object att, object def, string mess, string desc, mixed what)
{
    if (!objectp(mess_handler))
	init_handler();
    if (!what)
	what = previous_object();
    if (objectp(what))
	mess_handler->do_tell(att, def, mess, desc, LANG_THESHORT(what));
    if (stringp(what))
	mess_handler->do_tell(att, def, mess, desc, what);
}

varargs int
message(object att, object enemy, int dt, string hdesc, int phurt, mixed what)
{
    if (!objectp(mess_handler))
	init_handler();
    if (stringp(what))
	return mess_handler->message(att, enemy, dt, hdesc, phurt, what);
    if (!what)
	what = this_object();
    if (objectp(what))
	return mess_handler->message(att, enemy, dt, hdesc, phurt, what->short());
}

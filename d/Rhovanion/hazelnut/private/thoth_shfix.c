/*
 * thoth_shfix.c
 *
 * Since thoth can't add autoshadows to the player, let this object do
 * it instead. Secure methods used.
 *
 * Do _not_ remove this file if you want Thoth to work, ok?
 *
 * If you want to update it, just remove it and type 'gtoth', provided that
 * you have the toolsoul ~mrpr/private/thoth_ka, you'll get a new one.
 */

#include <macros.h>
#include <filepath.h>
#define THOTH FTPATH(".", "~mrpr/private/thoth")

nomask void
create()
{
    setuid();
    seteuid(getuid());
}

nomask void
add_autoshadow(string what)
{
    if (MASTER_OB(calling_object()) != THOTH)
	return;

    this_player()->add_autoshadow(what);
}

nomask void
log_it(string log, string what)
{
    if (MASTER_OB(calling_object()) != THOTH)
	return;

    log_file(log, what);
}

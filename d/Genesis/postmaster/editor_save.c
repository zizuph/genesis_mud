/*
 * /d/Genesis/postmaster/editor_save
 *
 * When a player is editing something and linkdies, this object is called
 * to save the buffer. When the player re-links, the message can be
 * restored. For reasons of efficiency, the stored messages are kept for
 * no more than a day.
 *
 * /Mercade, 28 October 1994
 *
 * Revision history:
 */

#pragma no_clone     /* No messing with this object */
#pragma no_inherit   /* No messing with this object */
#pragma save_binary  /* Quick loading               */
#pragma strict_types /* You should always be tidy   */

inherit "/std/object";

#include <macros.h>

#define EDITOR   "/obj/edit"
#define SAVE_DIR "/d/Genesis/postmaster/editor_save/"
#define ONE_DAY  86400 /* in seconds */

/*
 * Function name: create_object
 * Description  : Called to create this object when needed.
 */
void
create_object()
{
    set_name("editor_save");

    set_short("another hole in the donut");
    set_long("You should never see this object, but if you do, you " +
	"should examine the source, " + MASTER + " for more information.\n");

    set_no_show();

    setuid();
    seteuid(getuid());

    set_alarm(2.0, 0.0, "test_storage");
}

/*
 * Function name: test_storage
 * Description  : Each time the object is created, it checks whether the
 *                stores messages are still valid.
 */
static void
test_storage()
{
    int     index = -1;
    string *files = get_dir(SAVE_DIR + "*") - ({ ".", ".." });
    int     size  = sizeof(files);
    int     date  = time();

    /* It looks a little ugly, but believe me, it is the fastest routine.
     */
    while(++index < size)
    {
	if ((file_time(SAVE_DIR + files[index]) + ONE_DAY) < date)
	{
	    rm(SAVE_DIR + files[index]);
	}
    }
}

void
linkdie(string message)
{
    string name;

    if ((!strlen(message)) ||
	(!CALL_BY(EDITOR)) ||
	(!objectp(environment(previous_object()))))
    {
	return;
    }

    name = environment(previous_object())->query_real_name();

    if (file_size(SAVE_DIR + name) >= 0)
    {
	rm(SAVE_DIR + name);
    }

    write_file(SAVE_DIR + name, message);
}

string
restore()
{
    string name = this_player()->query_real_name();

    if (!CALL_BY(EDITOR))
    {
	return "Invalid call. May only be called by " + EDITOR + ".\n";
    }

    if (this_player() != this_interactive())
    {
	return "Invalid call. Incorrect interactive player.\n";
    }

    if (file_size(SAVE_DIR + name) <= 0)
    {
	return 0;
    }

    return read_file(SAVE_DIR + name);
}

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>

mapping gNames = ([ ]);

#define SAVE_FILE   "/d/Ansalon/common/cheaters_data"

/*
 * Function name: save_info
 * Description:   Saves the current attackers info
 */
static void
save_info()
{
    if (mappingp(gNames))
    {
        save_map(gNames, SAVE_FILE);
    }
}

/*
 * Function name: restore_info
 * Description:   Restores saved attackers info (after reboot for instance)
 */
static void
restore_info()
{
    if (file_size(SAVE_FILE + ".o") > 0)
    {
        gNames = restore_map(SAVE_FILE);
    }
}

void
create_room()
{
    set_short("Cheaters Admin");
    set_long("This is the administration object for cheaters in Ansalon.\n" +
    "Syntax:\n" +
    "Call add_cheater <name>\n" +
    "Call remove_cheater <name>\n");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    setuid();
    seteuid(getuid());
    restore_info();
}

int
is_cheater(string name)
{
    if (!stringp(gNames[name]))
        return 0;
    else
        return 1;
}

int
add_cheater(string name)
{
    if (!is_cheater(name))
    {
        gNames[name] = this_player()->query_real_name();

        save_info();
    }
}

int
remove_cheater(string name)
{
    gNames = m_delete(gNames, name);

    save_info();
}



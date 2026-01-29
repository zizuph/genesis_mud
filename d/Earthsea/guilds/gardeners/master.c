#pragma strict_types
#pragma no_clone

#include "defs.h"

public int
query_is_member(string name)
{
    return (file_size(MEMBER_DIR(name)) == -2);
}

public int
erase_deleted_member(string name)
{
    string old_dir;

    if(!query_is_member(name))
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    old_dir = GEN_OLD_MEMBER_DIR(name);
    mkdir(old_dir);
    rename(MEMBER_DATA(name) + ".o", old_dir + "data.o");
    rename(MEMBER_NOTES(name) + ".o", old_dir + "notes.o");
    rename(MEMBER_JOURNAL(name) + ".o", old_dir + "journal.o");
    rename(MEMBER_HERBS(name) + ".o", old_dir + "herbs.o");
    rmdir(MEMBER_DIR(name));

    write_file(GARDENER_LOG_MEMBERS,
        sprintf("%-24s [%-15s] left the guild, no longer a player.\n",
        ctime(time()), capitalize(name)));
    return 1;
}

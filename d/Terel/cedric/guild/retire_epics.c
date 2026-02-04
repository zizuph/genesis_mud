#include "guild_defs.h"
public void start()
{
    string *files;
    string name;
    int i;

    setuid();
    seteuid(getuid());

    files = get_dir("/d/Terel/cedric/guild/songs/epic/*.song");
    for (i = 0; i < sizeof(files); i++)
    {
        if (sscanf(files[i], "epic_of_%s.song", name))
        {
             if (!MEMBER_MANAGER->query_member(name))
             {
#if 0
                  write_file("/d/Terel/cedric/guild/songs/epic/old/epic_cleanup.210103", read_file("/d/Terel/cedric/guild/songs/epic/epick_of_" + name) + "\n");
                  rm("/d/Terel/cedric/guild/songs/epic/epic_of_" + name);
#endif
                write_file("/d/Terel/cedric/guild/songs/epic/old/epic_clean_list", name + "\n");
             }
        }
    }
}

public void retire(string *files)
{
    int i;
    for ( i = 0 ; i < sizeof(files) && i < 20; i++)
    {
        write_file("/d/Terel/cedric/guild/songs/epic/old/epic_cleanup.240103", read_file("/d/Terel/cedric/guild/songs/epic/epic_of_" + files[i] + ".song") + "\n");
        rm("/d/Terel/cedric/guild/songs/epic/epic_of_" + files[i] + ".song");
        }

    files = files[20..];
    if (sizeof(files))
    {
        set_alarm(0.0, 0.0, &retire(files));
    }
}

public void start2()
{
    string *files;
    int i;
    string *keep;

    setuid();
    seteuid(getuid());

    keep = ({ "juanita", "karath", "alto", "auberon", "blizzard", "damaris", "diri", "fingolfin", "gnadnar", "hannes", "isatis", "isodora", "mersereau", "mrbobo" });

    files = explode(read_file("/d/Terel/cedric/guild/songs/epic/old/epic_clean_list"), "\n") - ({ "" }) - keep;
    set_alarm(0.0, 0.0, &retire(files));
}

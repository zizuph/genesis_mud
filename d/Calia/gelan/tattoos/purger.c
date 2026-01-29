#pragma strict_types
#include <std.h>

inherit "std/object";

string alpha = "abcdefghijklmnopqrstuvwxyz";
string *purgeme;


public varargs void
query_purge(object who = this_player(), int i = 0)
{
    int j,
        count;
    string *files,
           name;

    if (i < 0 || i > 25)
    {
        if (pointerp(purgeme));
        {
            set_this_player(who);
            dump_array(purgeme);
        }
        purgeme = ({});
        return;
    }

    setuid();
    seteuid(getuid());

    files = get_dir("/d/Calia/gelan/tattoos/tattoo_save/"+
        alpha[i..i] + "/*.o");

    if (!sizeof(files))
    {
        set_alarm(10.0, 0.0, &query_purge(who,++i));
        return;
    }

    count = sizeof(files);

    for (j = 0; j < count; j++)
    {
        sscanf(files[j], "tattoo_save_%s.o", name);
        if (!SECURITY->exist_player(name))
        {
            if (!pointerp(purgeme))
                purgeme = ({});
            purgeme += ({name});
        }
    }
    set_alarm(10.0, 0.0, &query_purge(who,++i));
}

public varargs void
purge_files(int i = 0)
{
    int j,
        count;
    string *files,
           name;

    if (i < 0 || i > 25)
        return;

    setuid();
    seteuid(getuid());

    files = get_dir("/d/Calia/gelan/tattoos/tattoo_save/"+
        alpha[i..i] + "/*.o");

    if (!sizeof(files))
    {
        set_alarm(10.0, 0.0, &purge_files(++i));
        return;
    }

    count = sizeof(files);

    for (j = 0; j < count; j++)
    {
        sscanf(files[j], "tattoo_save_%s.o", name);
        if (!SECURITY->exist_player(name))
        {
            log_file("TATTOO_PURGE", "Removed save " +
                "file of " + name + " on " +
                ctime(time()) + ".\n");
            rm("/d/Calia/gelan/tattoos/tattoo_save/" +
                alpha[i..i] + "/tattoo_save_"+name+".o");
        }
    }
    set_alarm(10.0, 0.0, &purge_files(++i));
}

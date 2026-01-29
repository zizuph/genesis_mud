/*
 * /d/Rhovanion/lib/mapclean.c
 * created by Milan.
 *
 * Usage:
 *
 * call_other("/d/Rhovanion/lib/mapclean",
 *            "clear_directory",
 *            "/d/Rhovanion/directory_you_want_to_clear/");
 *
 * Parameter must end with "/".
 * Note that this will remove all files that contain exactly 1 line.
 */

#pragma no_clone
#pragma no_inherit
#pragma strict_types

public void
clear_directory(string dir)
{
    string  *files, *subdirs;
    int     i, s;

    if (!dir || (dir[strlen[dir]-1..strlen[dir]-1] != "/")) return;
    setuid();
    seteuid(getuid());

    files = get_dir(dir + "*") - ({ ".", ".." });

    if (s = sizeof(files))
    {
        subdirs = ({ });
        for (i = 0 ; i < s ; i++)
            if (file_size(dir + files[i]) == -2)
                subdirs += ({ files[i] });
        files -= subdirs;
        if (s = sizeof(files))
            for (i = 0 ; i < s ; i++)
            {
                if (sizeof(explode(read_file(dir + files[i], 1, 3), "\n")) == 1)
                    rm(dir + files[i]);
            }
    }
    destruct();
}

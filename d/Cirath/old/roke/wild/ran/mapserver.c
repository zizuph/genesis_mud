/* this is an experiment on improving this maze */

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <std.h>

#define NO 0
#define EA 1
#define SO 2
#define WE 3

static float seed;
static mixed *map;
static mixed thepath;

create_object()
{
    set_name("mapserver");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
}

init()
{
    ::init();
    if (!(SECURITY->query_wiz_level(this_player()->query_real_name())))
        return;
    add_action("morph", "morph");
    add_action("mappa", "mappa");
    add_action("syd", "syd");
}

void
setseed(string name)
{
    int t;

    seed = 1.0;
    for (t = 0; t < strlen(name); t += 2)
        seed *= itof(name[t]);
    for (t = 1; t < strlen(name); t += 2)
        seed /= itof(name[t]);
    seed -= itof(ftoi(seed));
}

float
myrandom()
{
    seed = seed * 763.0;
    seed -= itof(ftoi(seed));
    return seed;
}

int
myrand(int val)
{
    return ftoi(myrandom() * itof(val));
}

makemap(string name)
{
    int t, r, rr, dir, u;
    mixed m, path, rpath, rest;

    if (!strlen(name))
        name = "gogga";
    setseed(name);

    m = allocate(28);
    for (t = 1; t < 28; t++)
        m[t] = ({({0, 0}), ({0, 0}), ({0, 0}), ({0, 0})});

    /* south of 1 is out , east of 2 is out */
    m[1][SO] = ({30, 1});
    m[2][EA] = ({31, 1});

    rest = ({});
    path = ({});
    rpath = ({});

    for (t = 3; t < 28; t++)
        rest = rest + ({t});
    /* pick out eleven path-rooms */
    /* first the end-room */
    r = rest[myrand(sizeof(rest))];
    m[r][NO] = ({32, 1});
    rest = rest - ({r});
    path = path + ({r});
    rr = r;

    dir = myrand(4);
    for (t = 0; t < 9; t++)
    {
        r = rest[myrand(sizeof(rest))];
        m[r][dir] = ({rr, 1});
        rest = rest - ({r});
        path = path + ({r});
        rr = r;
        dir = myrand(4);
    }
    if (dir == SO)
        dir = WE;
    m[1][dir] = ({rr, 1});
    rr = path[6];
    dir = myrand(4);
    for (t = 0; t < 2; t++)
    {
        r = rest[myrand(sizeof(rest))];
        m[r][dir] = ({rr, 1});
        rest = rest - ({r});
        path = path + ({r});
        rr = r;
        dir = myrand(4);
    }
    if (dir == EA)
        dir = SO;
    m[2][dir] = ({rr, 1});

    rr = 1;
    for (t = 0; t < 3; t++)
    {
        r = rest[myrand(sizeof(rest))];
        m[r][SO] = ({rr, 1});
        rest = rest - ({r});
        rpath = rpath + ({r});
        rr = r;
    }

    dir = myrand(4);
    for (t = 0; t < 4; t++)
    {
        r = rest[myrand(sizeof(rest))];
        m[r][dir] = ({rr, 1});
        rest = rest - ({r});
        rpath = rpath + ({r});
        rr = r;
        dir = myrand(4);
    }

    for (t = 0; t < sizeof(rest); t++)
    {
        r = rpath[myrand(sizeof(rpath))];
        dir = myrand(4);
        m[rest[t]][dir] = ({r, 1});
    }

    for (t = 0; t < sizeof(path); t++)
    {
        r = rpath[myrand(sizeof(rpath))];
        dir = myrand(4);
        while (m[path[t]][dir][0])
            dir = (dir + 1) % 4;
        m[path[t]][dir] = ({r, 1});
    }

    rest = rest + rpath + path[6..10] + ({1, 2});

    for (t = 1; t < 28; t++)
    {
        for (u = 0; u < 4; u++)
        {
            if (!m[t][u][0])
            {
                m[t][u][0] = rest[myrand(sizeof(rest))];
                while (u == SO && m[t][u][0] == t)
                    m[t][u][0] = rest[myrand(sizeof(rest))];
            }
        }
    }

    map = allocate(28);
    for (t = 1; t < 28; t++)
    {
        map[t] = allocate(4);
        for (u = 0; u < 4; u++)
        {
            map[t][u] = m[t][u][0];
        }
    }
    thepath = ({1});
    for (t = 9; t >= 0; t--)
        thepath += ({path[t]});
}

int
morph(string str)
{
    if (!strlen(str))
        return 0;
    makemap(str);
    write("Map made for: " + str + "\n");
    return 1;
}

int
mappa(string str)
{
    int t;
    for (t = 1; t < 28; t++)
    {
        write(sprintf("%2d: %2d %2d %2d %2d\n", t, map[t][0], map[t][1],
                      map[t][2], map[t][3]));
    }
    write("Path :");
    for (t = 0; t < sizeof(thepath); t++)
        write(" " + thepath[t]);
    write("\n");
    return 1;
}

int
syd(string str)
{
    int s, t, u;
    mixed p, ok;
    if (str && sscanf(str, "%d", t) == 1)
    {
        p = ({});
        while (member_array(t, p) == -1 && t < 28)
        {
            p += ({t});
            t = map[t][SO];
        }
        dump_array(p);
        return 1;
    }
    ok = ({1});
    for (t = 2; t < 28; t++)
    {
        p = ({});
        s = t;
        while (member_array(s, p) == -1 && member_array(s, ok) == -1 && s < 28)
        {
            p += ({s});
            s = map[s][SO];
        }
        if (member_array(s, p) != -1)
        {
            write("Bad :");
            for (u = 0; u < sizeof(p); u++)
                write(" " + p[u]);
            write(" " + s + "\n");
        }
        else
            ok += p;
    }
    return 1;
}

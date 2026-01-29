/*
 * mapserver.c
 *
 * Server that generates a personal map for a player.
 * By Glindor, Nov 2001.
 *
 * Updated 2019.05.31 by Shanoga,
 *   Added checks for maps with no solution. All changes
 *    in makemap() with comments.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include "randefs.h"

#define DEBUG(x) find_player("shanoga")->catch_vbfc("MAPSERVER DEBUG: " + x + "\n")

// First index to map array
#define SOUTHOK 4
#define SOUTHPATH 5

static float seed;
static mapping map;
static mapping thepath;

void
create_object()
{
    set_name("mapserver");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
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
    seed = seed * 763.1;
    seed -= itof(ftoi(seed));
    if (seed == 0.0)
        seed = 0.42;
    return seed;
}

int
myrand(int val)
{
    return ftoi(myrandom() * itof(val));
}

string
descr_dir(int dir)
{
    switch (dir)
    {
      case NO: return "n"; break;
      case SO: return "s"; break;
      case EA: return "e"; break;
      case WE: return "w"; break;
    }
    return "x";
}

void
makemap(string name)
{
    int t, r, rr, dir, u, good_map;
    mixed *m;
    int *bad, *path, *rpath, *rest;
    string cap_name;
    string *test_path_arr;

    if (!mappingp(map)) {
        map = ([]);
        thepath = ([]);
    }
    /*
     * Create a map. Repeat, if necessary, until we have a valid map
     */
    while (good_map != 2)
    {
        // Check if a map already exists
        if (pointerp(map[name]))
        {
            // Get an array of the correct path to solve the maze
            test_path_arr = ({ });
            m = map[name];
            for (t = 1; t < sizeof(thepath[name]); t++)
                test_path_arr += ({descr_dir(member_array(thepath[name][t], m[thepath[name][t-1]]))});
            
            // An unsolvable maze will have an "x" exit and we should
            //  create a new maze using the capitalized name. If the
            //  capitalized name fails, start adding whitepsaces.
            if (member_array("x",test_path_arr) == -1)
            {
                good_map = 2;
                return;
            }
            else
            {
                good_map = 1;
                if (!cap_name)
                    cap_name = capitalize(name);
                else
                    cap_name = cap_name + " ";
            }
        }
        
        // The first time through, use the player's name for the maze.
        // If the map is invalid, use cap_name (defined above)
        if (!good_map)
            setseed(name);
        else
            setseed(cap_name);

        m = allocate(28);
        for (t = 1; t < 28; t++)
            m[t] = allocate(6);

        /* south of 1 is out , east of 5 is out */
        m[1][SO] = 30;
        m[1][SOUTHOK] = 1;
        m[5][EA] = 31;

        rest = ({});
        path = ({});
        rpath = ({});

        for (t = 2; t < 28; t++)
            rest = rest + ({t});
        rest -= ({5});

        /* pick out eleven path-rooms */
        /* first the end-room */
        r = rest[myrand(sizeof(rest))];
        m[r][NO] = 32;
        rest = rest - ({r});
        path = path + ({r});
        rr = r;

        /* Nine rooms in the path */
        for (t = 0; t < 9; t++)
        {
            dir = myrand(4);
            r = rest[myrand(sizeof(rest))];
            m[r][dir] = rr;
            rest = rest - ({r});
            path = path + ({r});
            if (dir == SO) 
                m[r][SOUTHPATH] = 1;
            rr = r;
        }
        
        /* The path starts from room 1, where south is already taken */
        dir = myrand(4);
        if (dir == SO)
            dir = WE;
        m[1][dir] = rr;

        /* Two rooms from eastern entrance */
        rr = path[6];
        for (t = 0; t < 2; t++)
        {
            dir = myrand(4);
            r = rest[myrand(sizeof(rest))];
            m[r][dir] = rr;
            rest = rest - ({r});
            path = path + ({r});
            if (dir == SO) 
                m[r][SOUTHPATH] = 1;
            rr = r;
        }
        
        /* Coming from room 2 (east entrance) */
        dir = myrand(4);
        if (dir == EA)
            dir = SO;
        m[2][dir] = rr;

        /* A path leading south and out */
        rr = 1;
        for (t = 0; t < 3; t++)
        {
            r = rest[myrand(sizeof(rest))];
            m[r][SO] = rr;
            m[r][SOUTHOK] = 1;
            rest = rest - ({r});
            rpath = rpath + ({r});
            rr = r;
        }

        /* A path leading to the out path */
        for (t = 0; t < 4; t++)
        {
            dir = myrand(4);
            r = rest[myrand(sizeof(rest))];
            m[r][dir] = rr;
            if (dir == SO && m[rr][SOUTHOK]) {
                m[r][SOUTHOK] = 1;
            }
            rest = rest - ({r});
            rpath = rpath + ({r});
            rr = r;
        }

        /* All rooms should have an exit to the out path.
           This avoids dead ends. */
        for (t = 0; t < sizeof(rest); t++)
        {
            r = rpath[myrand(sizeof(rpath))];
            dir = myrand(4);
            m[rest[t]][dir] = r;
            if (dir == SO && m[r][SOUTHOK]) {
                m[rest[t]][SOUTHOK] = 1;
            }
        }

        /* One exit in each room along the correct path should go to
           the out path */
        for (t = 0; t < sizeof(path); t++)
        {
            r = rpath[myrand(sizeof(rpath))];
            dir = myrand(4);
            while (m[path[t]][dir])
                dir = (dir + 1) % 4;
            m[path[t]][dir] = r;
            if (dir == SO && m[r][SOUTHOK]) {
                m[path[t]][SOUTHOK] = 1;
            }
        }

        /* These are the rooms that are allowed as path destinations.
           The 6 rooms last in the path are not allowed so you are
           very unlikely to get through by chance. */
        rest = rest + rpath + path[6..10] + ({1, 5});

        for (t = 1; t < 28; t++)
        {
            for (dir = 0; dir < 4; dir++)
            {
                if (!m[t][dir])
                {
                    r = rest[myrand(sizeof(rest))];
                    /* Exits to the south may not loop */
                    while (dir == SO && r == t)
                        r = rest[myrand(sizeof(rest))];
                    m[t][dir] = r;
                    if (dir == SO && m[r][SOUTHOK]) {
                        m[t][SOUTHOK] = 1;
                    }
                }
            }
        }

        /* Finally, there should always be a path south that leads out.
           It's likely so, but we must check. */
        while (1)
        {

            /* Propagate southok fully */
            u = 1;
            while (u == 1)
            {
                u = 0;
                for (t = 1; t < 28; t++)
                {
                    if (!m[t][SOUTHOK] && m[m[t][SO]][SOUTHOK])
                    {
                        m[t][SOUTHOK] = 1;
                        u = 1;
                    }
                }
            }
            bad = ({});
            for (t = 1; t < 28; t++)
                if (!m[t][SOUTHOK])
                    bad += ({t});
            if (sizeof(bad) == 0) break;

            /* Locate loop */
            rest = ({});
            t = bad[0];
            while (t > 1 && t < 28 && member_array(t, rest) == -1)
            {
                rest += ({t});
                t = m[t][SO];
            }
            if ((u = member_array(t, rest)) != -1)
                rest = rest[u..];
            /* Find one that is not in the path */
            for (t = 0; t < sizeof(rest); t++)
            {
                if (member_array(rest[t], path) == -1)
                {
                    m[rest[t]][SO] = 1;
                    m[rest[t]][SOUTHOK] = 1;
                    break;
                }
            }
            /* Found, do another lap */
            if (t < sizeof(rest)) continue;

            /* So, the loop is within the path? Hmm... */
            /* Find exit that is not part of the path */
            for (t = 0; t < sizeof(rest); t++)
            {
                if (!m[rest[t]][SOUTHPATH]) 
                {
                    m[rest[t]][SO] = 1;
                    m[rest[t]][SOUTHOK] = 1;
                    break;
                }
            }
            /* Found, do another lap */
            if (t < sizeof(rest)) continue;
            /* This should not happen! */
            // if (this_player()->query_real_name() == "shanoga")
            // {
                // write("This should not happen.\n");
                // dump_array(rest);
            // }
            break;
        }

        /* Copy the map to the global var */
        map[name] = allocate(28);
        for (t = 1; t < 28; t++)
        {
            map[name][t] = allocate(4);
            for (u = 0; u < 4; u++)
            {
                map[name][t][u] = m[t][u];
            }
        }
        thepath[name] = ({1});
        for (t = 9; t >= 0; t--)
            thepath[name] += ({path[t]});
    }
}

int
query_dest(string name, int from, int dir)
{
    /*
     * Handle the exits to the outer world specially here.
     * This means that if there is any problems with the map
     * generation the player can still get out if the first room.
     */
    if (from == 1 && dir == SO) return 30;
    if (from == 5 && dir == EA) return 31;

    makemap(name);
    return map[name][from][dir];
}

/*
 * Tell the server that a player has entered.
 * This allows it to precompute the map in a separate alarm
 * thus reducing the risk for evaluation problems.
 */
int
arrived(string name)
{
    set_alarm(0.0, 0.0, &makemap(name));
}

/* Test functions */

void
init()
{
    ::init();
    if (!(SECURITY->query_wiz_level(this_player()->query_real_name())))
        return;
    add_action("morph", "morph");
    add_action("mappa", "mappa");
    add_action("syd", "syd");
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
    mixed *m;
    
    if (!strlen(str)) {
        dump_array(m_indexes(map));
        return 1;
    }

    if (!pointerp(map[str])) {
        write("No map for " + str + "!\n");
        return 1;
    }
    write(sprintf("%2s: %2s %2s %2s %2s\n", "", descr_dir(0) , descr_dir(1),
                  descr_dir(2), descr_dir(3)));
    m = map[str];
    for (t = 1; t < 28; t++)
    {
        write(sprintf("%2d  %2d %2d %2d %2d\n", t, m[t][0], m[t][1],
                      m[t][2], m[t][3]));
    }
    write("Path :");
    for (t = 0; t < sizeof(thepath[str]); t++)
    {
        if (t >= 1)
            write(" " +
                  descr_dir(member_array(thepath[str][t], m[thepath[str][t-1]])));
        write(" " + thepath[str][t]);
    }
    write("\n");
    return 1;
}

int
syd(string str)
{
    int s, t, u;
    mixed p, ok;
    string name,rest;
    mixed *m;
    
    if (!str || strlen(str) == 0)
    {
        write("Usage: syd <name> [loc]\n");
        return 1;
    }
    if (sscanf(str, "%s %s", name, rest) != 2)
    {
        name = str;
        rest = "";
    }
    
    if (!pointerp(map[name])) {
        write("No map for " + name + "!\n");
        return 1;
    }
    m = map[name];

    if (rest && sscanf(rest, "%d", t) == 1)
    {
        p = ({});
        while (member_array(t, p) == -1 && t < 28)
        {
            p += ({t});
            t = m[t][SO];
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
            s = m[s][SO];
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

void
test_it(string str)
{
    int t;
    write("Testing random for " + str + "\n");
    setseed(str);
    
    dump_array(seed);
    for (t = 0; t < 30; t++)
    {
        myrandom();
        dump_array(seed);
    }
}

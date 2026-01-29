/*
 * A* implementation in LPC.
 *
 * This is designed to work with the Khalakhor coordinate system.
 * It should however be pretty easy to modify it for other systems.
 *
 * It actually ended up being much faster than I thought it'd be.
 * But still, don't use it when you don't have to. It can potentially
 * end up loading many files.
 *
 * - Cotillion
 *
 * Copyright Erik Gävert <erik@gavert.net>
 */
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

/*
 * MAX_COST
 *
 * How long paths it should consider before just giving up.
 * This is cost from the starting point.
 */
#define MAX_COST 150
 

/*
 * HIGH_DISTANCE
 *
 * A really high distance value assigned to rooms without coordinates.
 * They might be checked eventually anyway.
 */
#define HIGH_DISTANCE 1000

/* QUALITY
 *
 * When set to higher values more time will be spent expaming rooms-
 * Raise/Lower depending on cpu usage.
 */
#define QUALITY   4


/* Node Structure */
#define N_OBJ     0                     /* Node object */
#define N_SRC     1                     /* Path cost to reach this node */
#define N_DST     2                     /* Estimated distance to target */

mixed
node(object ob, int src_cost, int dst_cost)
{
    return ({ ob, src_cost, dst_cost });
}

int
compare_node(mixed n1, mixed n2)
{
    return  (n2[N_SRC] + n2[N_DST]) - (n1[N_SRC] + n1[N_DST]);
}

/*
 * Manhattan distance, happily ripped from the internet :)
 */
int
distance(object src, object dst)
{
    int *a = src->query_local_coords();
    int *b = dst->query_local_coords();

    if (!a || !b)
        return HIGH_DISTANCE;
    
    int a1 = a[0] * 2;
    int a2 = a[1] * 2 - (a[0] % 2)-2*(a[0] / 2);
    int a3 = -a1 - a2;
    int b1 = b[0] * 2;
    int b2 = b[1] * 2 - (b[0] % 2) - 2 * (b[0] / 2);
    int b3 = -b1 - b2;

    // 2*D/path_div lets me scale the value.  Scaling is nice because you
    // can adjust the accuracy/speed tradeoff.  If you want a faster
    // search, you can get an approximate answer.
    return 2 * (ABS(a1-b1)+ABS(a2-b2)+ ABS(a3-b3)) / QUALITY;    
}

/*
 * The cost of moving from src to dst
 * object - the src
 * int    - the exit number in the source
 * object - the destination
 */
int
cost(object src, int exit, object dst)
{
    return 1 + src->query_tired_exit(exit);
}

/*
 * Function Name: find_path
 * Description  : Locates the shortest path between two rooms.
 *                It will do so efficently if there is a coordinate system
 *                in the rooms, otherwise it'll be very inefficient.
 * Arguments    : object - start room
 *                object - destination room
 *
 * Returns      : mapping - The commands to follow to reach the destination.
 *                          Indexed on the room they should be used in.
 *                          (object) /d/Foo/bar : (string) "east"
 */
string *
find_path(object start, object destination)
{
    object room;
    mixed current_node;
    mapping visited = ([ ]);
    mixed *queue = ({ });
    mapping map = ([ ]);
    int exit, tries;

    queue += ({ node(start, 0, distance(start, destination)) });

    while (sizeof(queue))
    {
        tries++;
        
        current_node = queue[0];
        queue = queue[1..];

        if (current_node[N_OBJ] == destination)
            break;

        exit = -1;
        foreach (string file : current_node[N_OBJ]->query_exit_rooms())
        {
            int i, size;
            object ob;
            mixed dst, old;
            exit++;
            
            /* Keep track of exit number for the cost function */
            
            if (LOAD_ERR(file))
                continue;

            ob = find_object(file);

            dst = node(ob, current_node[N_SRC] +
                cost(current_node[N_OBJ], exit, ob),
                distance(ob, destination));

            if (dst[N_SRC] > MAX_COST)
                continue;
            
            if (old = visited[ob])
            {
                /* If this path is worse abort */
                if (old[N_SRC] <= dst[N_SRC])
                    continue;
            }

            visited[ob] = dst;
            map[ob] = ({ current_node[N_OBJ],
                         current_node[N_OBJ]->query_exit_cmds()[exit] });
            
            i = -1;
            size = sizeof(queue);
            while (++i < size)
            {
                if (compare_node(dst, queue[i]) >= 0)
                {
                    if (i == 0)
                        queue = ({ dst }) + queue;
                    else
                        queue = queue[0..i-1] + ({ dst }) + queue[i..];
                    dst = 0;
                    break;
                }
            }

            if (dst)
                queue += ({ dst });            
        }
    }

    if (current_node[N_OBJ] == destination)
    {
        mapping path = ([ ]);
        mixed tmp;
        object ob;

        ob = destination;
        while (ob != start && (tmp = map[ob]))
        {
            ob = tmp[0];
            path[ob] = tmp[1];
        }

        return path + ([ ]);
    }

    return 0;
}


mixed
start_fun()
{
    setuid();
    seteuid(getuid());
    
    return find_path(environment(this_player()),
        find_object("/d/Khalakhor/se_speir/port/room/dining"));
    
}

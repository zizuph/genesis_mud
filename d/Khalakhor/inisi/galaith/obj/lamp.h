#ifndef LAMP_DEFS
#define LAMP_DEFS


#define LTELL_ROOM(r, o, x, y, n)                    \
    tell_room((r), ({ ((x) + G_METNAME(o) + (y)), \
                      ((x) + G_TNONMET(o) + (y)), \
                      ((x) + "someone" + (y)) }), (n), (o))


#define G_METNAME(x)  ((x)->query_name())
#define G_TNONMET(x)  ("the " + (x)->query_nonmet_name())


#endif LAMP_DEFS
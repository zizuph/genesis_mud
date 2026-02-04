inherit "/std/shadow";

#include <macros.h>
#include <living_desc.h>
#include <std.h>

/* Don't autoload this shadow!! */

public void
autoload_shadow(mixed arg)
{
    remove_shadow();
}

/*
 * Let's shadow the communicate function in /std/living/cmdhooks.c to
 * ensure that all say cmds are also made to the horse's environment.
 */

public int
communicate(string str)
{
    string verb;
    object horse, where, *dumb;

    query_shadow_who()->communicate(str);
    
    verb = query_verb();
    if (str == 0)
        str = "";
    if (verb[0] == "'"[0])
        str = extract(verb, 1) + " " + str;

    horse = environment(this_player())->query_horse();
    if (!horse) return 1;
    where = environment(horse);
    if (!where) return 1;
    dumb = ({ this_player(), horse });
    if (horse->query_horse_flea()) dumb += ({ horse->query_horse_flea() });
    
    tell_room(where,
         ({ METNAME + LD_SAYS + LD_UNDERSTANDS(str) + "\n",
            TART_NONMETNAME + LD_SAYS + LD_UNDERSTANDS(str) + "\n",
            UNSEEN_NAME + LD_SAYS + LD_UNDERSTANDS(str) + "\n"      }),
         dumb );
    return 1;
}

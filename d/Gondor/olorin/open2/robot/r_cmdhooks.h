/*
  robot/r_cmdhooks.c

  This is a subpart of robot.c

  Copied from /std/living/c
*/

#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <std.h>

#include "/d/Genesis/login/login.h"

static string  race;

/*
 * Function name: set_race_real
 * Description:   Makes the npc truly this race
 * Arguments:     arg - the race name
 */
public void
set_race_real(string arg)
{
    race = arg;
}
 
/*
 * Function name: query_race
 * Description:   returns the race - always the same as query_race_name()
 * Returns:       the race
 */
public string
query_race()
{
    return race;
}
 
/*
 * Function name: race_sound
 * Description:   returns the communication sound from this object to ob
 * Arguments:     ob - the object we are communicating with.
 * Returns:       the sound
 */
public string
race_sound(object ob)
{
    seteuid(getuid());
    if (!RACESOUND[race])
        return "says";
    if (!RACESOUND[race][ob->query_race()])
        return "says";
    return RACESOUND[race][ob->query_race()];
}
 
/*
 * Function name: communicate
 * Description:   say something to someone else
 * Arguments:     str - what to say
 * Returns:       always 1
 */
public int
communicate(string str)
{
    int     i;
    object *peop;
    string  verb = query_verb();

    if (extract(verb, 0, 0) == "'")
    {
        if (strlen(str))
            str = extract(verb, 1) + " " + str;
        else
            str = extract(verb, 1);
    }
    peop = FILTER_LIVE(all_inventory(environment()));
    i = sizeof(peop);
    while(i--)
        peop[i]->catch_msg(QCTNAME(this_object()) + " "
          + race_sound(peop[i]) + ": " + str + "\n");

    if (this_object()->query_option(OPT_ECHO))
        write("You say: " + str + "\n");
    else
        write("Ok.\n");

    return 1;
}
 

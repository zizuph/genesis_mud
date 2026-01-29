// file name:        /d/Avenir/common/bazaar/infidel/obj/globe.c
// creator(s):       Cirion
// revision history: Denis, Jan'97: Misc changes.
//
//               Cirion, 24 March 97:
//               Changed all these ENV(whatever)'s to a global
//               variable, 'room'.
//
//                   Denis, May'97: Fixed it again. Usage of this_player()
//                                  in set_alarmed function.
//
//               Lilith, Oct'04: Changed colour of smoke. It appeared
//                  green after it broke but it was blue in the globe.
//                  The clear() func was adding light levels to the
//                  room in error.
//                  Also added remove_alarms.
//
//               Lilith, Nov '04: made keepable and recoverable,
//                  made it a heap, added magical properties
 
//                   Made it nonstackable
//                    Made it not glow 50% of the time
//                    Ibun
//
// purpose:      Smoke globe, used by Nochipa (../mon/nochipa.c)
//                   and sneaky human (../mon/sneaky.c).
//                   Kicks everybody out of the room in different directions
//                   if their constitution is not great enough.
//               Makes it hard to see so its hard to fight.
//               Makes its hard for magic users to cast spells.
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <cmdparse.h>
#include <filter_funs.h>
#include "/d/Avenir/common/common.h"

inherit "/std/object";
inherit "lib/keep";
 
void clear();

object room;
int m, alarm1, alarm2;

void
create_object()
{
    set_name("_av_alphum_globe");
    add_name(({"glass", "globe"}));
    set_adj(({"transparent","blue"}));
    set_short("transparent blue globe");
    set_long("It is a small blue globe, made from thin, fragile " +
             "glass. Within the globe, a thick blue mist swirls " +
             "around.\n");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_S_WIZINFO, "This globe, when broken, will creake " +
        "a smoke that will add 3 levels of darkness to itself " +
        "for 15 seconds. It will make livings in the same room " +
        "cough, and possibly, if the con check fails, flee the " +
        "room. It also adds and anti-magic prop to the room it " +
        "is in for the duration of the smoke, disrupting the " +
        "concentration of those who fail the dis check.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 30, "transformation" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"You sense a latent magical aura surrounding it.\n", 10 }));

    will_not_recover = random(2);
}

void
cough()
{
    string *cmds = ({ "cough", "choke", "gag", "sneeze", "swallow" });
    object *people = FILTER_LIVE(all_inventory(room));
    int     i;

    if (!sizeof(people))
        return;

    for (i = 0; i<sizeof(people); i++)
       if (random(100) > people[i]->query_stat(SS_CON))
           people[i]->command("$" + cmds[random(sizeof(cmds))]);
}


void
gam_effect(object who)
{
    if(!objectp(who))
        return;

    if (who->query_prop(LIVE_I_CONCENTRATE))
    {

        who->catch_tell("About you there is a rush of air and force. "+
            "A thousand dove's wings brush against you.\n");

        tell_room(environment(this_object()), "You can hear the cooing "+
            "of many doves.\n");

        if(who->query_stat(SS_DIS) > 80 + random(200))
        {
           /* A highly disciplined magic user will not be distracted.*/
           return;
        }
        else
        /* break his spell */
        who->cmdhooks_break_spell("The cooing of the doves and "+
            "the tickle of their feathers distracts you.\n");
    }
}

/* globe anti magic */
void
gam()
{
    object who = TP;

    if(!objectp(who))
        return;

    set_alarm(1.0, 0.0, &gam_effect(who));
}

int
do_break(string arg)
{
    object *ob;

    if (!stringp(arg))
    {
        notify_fail("Smash what?\n");
        return 0;
    }

    if (!parse_command(arg, deep_inventory(ENV(TP)), "%i", ob))
    {
        notify_fail("Smash what?\n");
        return 0;
    }

    ob = NORMAL_ACCESS(ob, 0, 0);
    if (!sizeof(ob) || ob[0] != TO)
    {
        notify_fail("Smash what?\n");
        return 0;
    }

    write("You smash the " + short() + " against the ground.\n");
    say(QCTNAME(TP) + " smashes " + LANG_ASHORT(TO) +
        " against the ground.\n");
    tell_room(ENV(TP), "The globe shatters and starts to emit " +
              "a thick blue smoke, which quickly obscures your " +
              "vision.\n");
    room = ENV(TP);
    if (present("_av_alphum_globe", room))
    {
        remove_object();
        return 1; // No stacking!!
    }
    move(room, 1);
    add_prop(OBJ_I_LIGHT, -3);
    add_prop(OBJ_M_NO_GET, 1);
    set_no_show();
    room->add_my_desc("The air is thick with a foul, bluish " +
              "smoke that hangs over everything.\n", TO);
    room->add_prop(ROOM_S_DARK_LONG,
                  "The smoke everywhere makes it impossible to see.\n");
    room->add_prop(ROOM_S_DARK_MSG, "The smoke makes it impossible to");

    /* Don't want to interfere with room code */
    if (!room->query_prop(ROOM_M_NO_MAGIC))
    {
        room->add_prop(ROOM_M_NO_MAGIC, gam);
        m = 1;
    }
    alarm1 = set_alarm(15.0 + itof(random(20)), 0.0, clear);
    alarm2 = set_alarm(2.0, 5.0, cough);
    return 1;
}

void
clear()
{
    add_prop(OBJ_I_LIGHT, 0);
    remove_prop(OBJ_I_LIGHT);

    if (alarm1)
        remove_alarm(alarm1);
    if (alarm2)
        remove_alarm(alarm2);

    tell_room(room, "The smoke clears away.\n");
    room->remove_prop(ROOM_S_DARK_LONG);
    room->remove_prop(ROOM_S_DARK_MSG);

    /* don't want to interfere with room code */
    if (m)
    {
        room->add_prop(ROOM_M_NO_MAGIC, 0);
        room->remove_prop(ROOM_M_NO_MAGIC);
    }

    remove_object();
}

void
init()
{
    ::init();
    add_action(do_break, "break");
    add_action(do_break, "smash");
    add_action(do_break, "shatter");
    add_action(do_break, "crush");
}
 
public string
query_recover()
{
    return MASTER + ":";
}

// file name:        /d/Avenir/common/bazaar/infidel/obj/globe.c
// creator(s):       Cirion
// revision history: Denis, Jan'97: Misc changes.
//
//               Cirion, 24 March 97: 
//               Changed all these ENV(whatever)'s to a global
//               variable, 'room'.
//
//		     Denis, May'97: Fixed it again. Usage of this_player()
//				    in set_alarmed function.
//
//               Lilith, Oct'04: Changed colour of smoke. It appeared
//                  green after it broke but it was blue in the globe.
//                  The clear() func was adding light levels to the 
//                  room in error.
//                  Also added remove_alarms.
//
//               Lilith, Nov '04: made keepable and recoverable,
//                  made it a heap, added magical properties
// 
// purpose:      Smoke globe, used by Nochipa (../mon/nochipa.c)
//		     and sneaky human (../mon/sneaky.c).
//		     Kicks everybody out of the room in different directions
//		     if their constitution is not great enough. 
//               Makes it hard to see so its hard to fight.
//               Makes its hard for magic users to cast spells.
// note:             
// bug(s):           
// to-do:            

# pragma strict_types
# include <cmdparse.h>
# include <filter_funs.h>
# include "/d/Avenir/common/common.h"
inherit "/std/heap";
inherit "/lib/keep";

void clear();

object room;
int m, alarm1, alarm2;

void
create_heap()
{
    set_heap_size(1);
    set_name("globe"); 
    add_name("glass");
    set_adj(({"transparent","blue"}));
    set_short("transparent blue globe");
    set_long("It is a small blue globe, made from thin, fragile " +
             "glass. Within the globe, a thick blue mist swirls around.\n");

    add_prop(HEAP_I_UNIT_VALUE, 50);
    add_prop(HEAP_I_UNIT_VOLUME, 400);
    add_prop(HEAP_I_UNIT_WEIGHT, 400);

    if (!query_prop(HEAP_S_UNIQUE_ID))
    {
        add_prop(HEAP_S_UNIQUE_ID,
            MASTER + ":" + singular_short(this_object()));
    }

    add_prop(OBJ_S_WIZINFO, "This globe, when broken, will creake a smoke "+
        "that will add 3 levels of darkness to itself for 15 seconds. It "+
        "will make livings in the same room cough, and possibly, if the "+
        "con check fails, flee the room. It also adds and anti-magic "+
        "prop to the room it is in for the duration of the smoke, disrupt"+
        "ing the concentration of those who fail the dis check. "+ 
        ".\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "transformation" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"You sense a latent magical aura surrounding it.\n", 10 })); 

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

    who->catch_tell("About you there is a rush of air and force. "+
        "A thousand dove's wings brush against you.\n");

    tell_room(environment(this_object()), "You can hear the cooing "+
        "of many doves.\n");

    if(who->query_stat(SS_DIS) > 80 + random(200))
    {
       /* A highly disciplined magic user will not be distracted.*/
       return;
    }
    else if (who->query_prop(LIVE_I_CONCENTRATE))
    {
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

public int
smash_globe(object where)
{
    set_no_show();

    add_prop(OBJ_I_LIGHT, -3);
    add_prop(OBJ_M_NO_GET, 1);

    room = where;

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
}

int
do_break(string str)
{
    object obj;

    NF(CAP(QVB) + " what?\n");
    if (!strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] 'globe' / 'sphere'"))
        return 0;
    /*
    objs = CMDPARSE_ONE_ITEM(str, "one_globe", "globe_access");
    if (!sizeof(objs))
	return 0;
     */

    if (num_heap() > 1)
    {
	leave_behind = 1;
	obj = force_heap_split();
    }
    else
    {
	obj = this_object();
    }

    write("You smash " + LANG_THESHORT(obj) + " against the ground.\n");
    say(QCTNAME(TP) + " smashes " + LANG_ASHORT(obj) + " against the ground.\n");
    tell_room(ENV(TP), "The globe shatters and starts to emit " +
              "a thick blue smoke, which quickly obscures your vision.\n");

    room = ENV(TP);

    obj->move(room, 1);
    obj->smash_globe(room);
    return 1;
}
   
void
clear()
{   
    add_prop(OBJ_I_LIGHT, 0);
    remove_prop(OBJ_I_LIGHT);
 
    tell_room(room, "The smoke clears away.\n");
    room->remove_prop(ROOM_S_DARK_LONG);
    room->remove_prop(ROOM_S_DARK_MSG);
   
    /* don't want to interfere with room code */
    if (m)
    {
        room->remove_prop(ROOM_M_NO_MAGIC);
    }
    if (alarm1)
        remove_alarm(alarm1);
    if (alarm2)
        remove_alarm(alarm2);

    remove_object();
}

void
init()
{
    ::init();

    if (environment() != this_player())
	return;

    add_action(do_break, "break");
    add_action(do_break, "smash");
    add_action(do_break, "shatter");
    add_action(do_break, "crush");
}

/*
 * Function name: query_recover
 * Description  : This function is called to see whether this object may
 *                recover.
 */
public string
query_recover()
{
    string file = MASTER;
    return file + ":heap#" + num_heap() + "#";
}

/*
 * Function name: init_recover
 * Description  : This function is called when item recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_recover(string str)
{
    string foobar;
    int    num;

    if (sscanf(str, "%sheap#%d#%s", foobar, num, foobar) == 3)
    {
        set_heap_size(num);
    }
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */

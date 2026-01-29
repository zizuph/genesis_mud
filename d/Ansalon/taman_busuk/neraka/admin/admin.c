/* admin.c
 * Ashlar, 11 Jul 97
 * This is the main administration object for Neraka.
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

#define DEBUG(x)    (find_player("stralle")->catch_msg("NADMIN: " + x + "\n"))

mapping attack_running =
    ([ "white" : 0, "black" : 0, "blue" : 0, "red" : 0, "green" : 0,
       "main" : 0 ]);

/* Prototypes */
void adminlog(string s);

void
create_room()
{
    set_short("Neraka Admin");
    set_long("This is the administration object of Neraka.\n");

    setuid();
    seteuid(getuid());
    LOAD_ERR(WAGONS_ADMIN);
    LOAD_ERR(PARROT_ADMIN);
    LOAD_ERR(ATTACKERS_ADMIN);
    LOAD_ERR(NERAKA + "admin/dragonadmin");
}

/*
 * Function name: query_may_enter_temple
 * Description:   Check whether a living may enter the temple of takhisis
 * Arguments:     object l - The living to check access
 *                object g - The guard that checks access
 *                int strict - Strict rules (military and noble only)
 * Returns:       1/0 indicates whether l may pass the guard g
 */
varargs int
query_may_enter_temple(object l, object g, int strict)
{
    object pass;

    /* There must be a guard to block entry */
    if (!objectp(g))
        return 1;

    /* The guard must be able to see the player */
    if ((!CAN_SEE(g,l)) || (!CAN_SEE_IN_ROOM(g)) || (E(g) != E(l)))
        return 1;

    /* No mortal Knights may enter */
    if (l->query_guild_member("Solamnian Knights"))
    {
        g->command("sneer");
        g->command("say Begone, foul Knight, or our Queen will devour " +
            "your soul..");
        return 0;
    }

    /* Allow dragonarmy officers and other high ranking individuals */
    if (l->query_guild_member("Priests of Takhisis"))
    {
        l->catch_msg(QCTNAME(g) + " salutes you as you pass by.\n");
        tell_room(E(l), QCTNAME(g) + " salutes " + QTNAME(l) + " as " +
            HE(l) + " passes by.\n", l);
        return 1;
    }

    /* Allow people with a city pass */
    if ((l->query_alignment() < 0) && (pass=P(VALID_PASS_ID,l)) && !strict)
    {
        l->catch_msg("You show your " + pass->short() + " to " +
            QTNAME(g) + ", and " + HE(g) + " motions for you to pass by.\n");
        tell_room(E(l), QCTNAME(l) + " shows something to " +
            QTNAME(g) + ", who motions for " + HIM(l) + " to pass by.\n", l);
        return 1;
    }
    
    /* Block other NPC's quietly. */
    if (l->query_npc())
        return 0;

    /* All others are firmly turned away */
    g->command("stare . " + l->query_real_name());
    g->command("say You have no business in the Temple of Takhisis!");
    return 0;
}

/*
 * Function name: query_may_enter_city
 * Description:   Check whether a living may enter the inner city
 * Arguments:     object l - The living to check access
 *                object g - The guard that checks access
 *                int strict - Strict rules (military and noble only)
 * Returns:       1/0 indicates whether l may pass the guard g
 */
varargs int
query_may_enter_city(object l, object g, int strict)
{
    object pass;

    /* There must be a guard to block entry */
    if (!objectp(g))
        return 1;

    /* The guard must be able to see the player */
    if ((!CAN_SEE(g,l)) || (!CAN_SEE_IN_ROOM(g)) || (E(g) != E(l)))
        return 1;

    /* Is the person an offender? */
    if (ATTACKERS_ADMIN->query_know_person(g,l))
    {
        if (random(2))
            g->command("say You're only entering over my dead body.");
        else
            g->command("say I'd say there are two chances of you " +
            "entering here.. No way and no how.");
        return 0;
    }

    /* No mortal Knights may enter */
    if (l->query_guild_member("Solamnian Knights"))
    {
        g->command("smirk");
        g->command("say We don't allow Knights in here.");
        return 0;
    }

    if (l->query_guild_member("Heralds of the Valar") ||
        l->query_guild_member("Gondorian Rangers Guild") ||
        l->query_guild_member("Rangers of the Westlands") ||
        l->query_guild_member("Calian warrior's guild"))

    {
        g->command("grin stoi");
        g->command("say Known supporters of the Knights have " +
            "no business here.");
        return 0;
    }
    
    /* Allow dragonarmy officers and other high ranking individuals */
    if (l->query_guild_member("Priests of Takhisis") ||
        (l->query_guild_member("Dragonarmy") &&
        l->query_dragonarmy_rank() >= 1))
    {
        l->catch_msg(QCTNAME(g) + " salutes you as you pass by.\n");
        tell_room(E(l), QCTNAME(g) + " salutes " + QTNAME(l) + " as " +
            HE(l) + " passes by.\n", l);
        return 1;
    }

    if (l->query_race_name() == "kender" || l->query_race_name() == "dwarf")
    {
        g->command("say Begone foul " + l->query_race_name() + ".");
        return 0;
    }

    l->catch_msg(QCTNAME(g) + " motions for you to pass.\n");
    tell_room(E(l), QCTNAME(g) + " motions for " + QTNAME(l) +
        " to pass.\n", l);
    return 1;

    /* Allow people with a city pass */
    if ((pass=P(VALID_PASS_ID,l)) && !strict)
    {
        l->catch_msg("You show your " + pass->short() + " to " +
            QTNAME(g) + ", and " + HE(g) + " motions for you to pass by.\n");
        tell_room(E(l), QCTNAME(l) + " shows something to " +
            QTNAME(g) + ", who motions for " + HIM(l) + " to pass by.\n", l);
        return 1;
    }

    /* Block other NPC's quietly. */
    if (l->query_npc())
        return 0;

    /* All others are firmly turned away */
    g->command("laugh . at " + l->query_real_name());
    g->command("say You can't enter. Now go away quickly, little " + 
        (l->query_gender() == 1 ? "girl" : "boy") + ".");
    return 0;
}

/* Functions related to handling attacks */

void
do_lower_portcullis(string cr)
{
    call_other(cr, "lower_portcullis");
}

void
do_raise_portcullis(string cr)
{
    if (!call_other(cr, "query_attack_going_on"))
        call_other(cr, "raise_portcullis");
}       

void
do_extra_defences(string cr)
{
    int still_attacking;

    still_attacking = call_other(cr, "query_attack_going_on");

    if (!still_attacking)
    {
        string q;
        q = lower_case(call_other(cr, "query_quarter"));
        if (!stringp(q) || (q == ""))
            q = "main";
        attack_running[q] = 0;
        set_alarm(itof(45+random(45)), 0.0, &do_raise_portcullis(cr));
        return;
    }

    call_other(cr, "extra_defences");
    set_alarm(itof(25+random(10)), 0.0, &do_extra_defences(cr));
}

void
respond_to_attack(string path)
{
    /* path is the file path where to look for:
       abovegate.c  -  A room controlling the portcullis
     */

    /* The rooms must load */
    if (LOAD_ERR(path + "abovegate"))
    {
        adminlog("Could not load " + path);
        return;
    }

    /* The first response is lowering the portcullis */
    set_alarm(itof(2+random(3)),0.0,&do_lower_portcullis(path + "abovegate"));

    /* Then we'll throw in some extra defences */
    set_alarm(itof(8+random(7)),0.0,&do_extra_defences(path + "abovegate"));
}

void
do_extra_defences_on_main()
{
    int still_attacking;
    string cr = NOUTER+"main/r1";

    still_attacking = call_other(cr, "query_attack_going_on");

    if (!still_attacking)
    {
        string q;
        q = lower_case(call_other(cr, "query_quarter"));
        if (!stringp(q) || (q == ""))
            q = "main";
        attack_running[q] = 0;
        set_alarm(itof(25+random(25)), 0.0,
            &do_raise_portcullis(cr));
        return;
    }

    call_other(NOUTER+"main/gh1", "extra_defences");
    set_alarm(itof(25+random(10)), 0.0, &do_extra_defences(cr));
}

void
respond_to_attack_on_main()
{
    if (LOAD_ERR(NOUTER+"main/gh1"))
    {
        adminlog("Could not load main/gh1");
        return;
    }
    set_alarm(itof(2+random(3)),0.0,&do_lower_portcullis(NOUTER+"main/r1"));
    set_alarm(itof(5+random(5)),0.0,&do_extra_defences_on_main());
}

/*
 * Function name: attack_on_gate
 * Description:   Initiate defence measures due to an attack on a city gate
 * Arguments:     string gate - colour of gate that is attacked, or "" if main
 *                  gate
 */
void
attack_on_gate(string gate)
{
    switch(gate)
    {
        case "white":
        case "green":
        case "black":
        case "red":
        case "blue":
        case "main":
            if (attack_running[gate])
                return;
            adminlog("Attack on gate '"+gate+"'");
            attack_running[gate] = 1;
            if (gate=="main")
                respond_to_attack_on_main();
            else
                respond_to_attack(NOUTER + gate + "/");
            break;
    }
}

/*
 * Function name: adminlog
 * Description:   Adds a line to the admin log of Neraka
 * Arguments:     string s - The line to add
 */
void
adminlog(string s)
{
}

/* filter function */
static int
tn_filter(object ob, string *subdir, string basedir)
{
    object e;
    int i;
    string f;

    e = environment(ob);
    if (!e)
        return 0;

    f = file_name(e);
    for (i = 0; i < sizeof(subdir); i++)
    {
        if (wildmatch("/d/Ansalon/taman_busuk/" + basedir + "/" + subdir[i] + "*", f))
    	    return 1;
    }
    return 0;
}

/*
 * Function name: tell_neraka
 * Description:   sends a message to players in Neraka
 * Arguments:     mixed subdir
 *                      string - to players in that subdir
 *                      string * - to players in the subdirs in the array
 *                mixed message
 *                      string - message to send
 *                      string * if io = 3, then the first item is outside
 *                              message, the second is inside message
 *                int io
 *                      1 - send to outside rooms only
 *                      2 - send to inside rooms only
 *                      3 - send to inside and outside rooms
 *                object *exclude
 *                      an array of rooms not to send the message to
 * Returns:       (object *) the players that were within the rooms
 */
varargs public object *
tell_neraka(mixed subdir, mixed message, int io = 1, object *exclude = ({ }), string basedir = "neraka")
{
    object *p;
    int i;

    if (stringp(subdir))
        subdir = ({ subdir });

    p = filter(users(), &tn_filter(,subdir,basedir));

    for (i = 0; i < sizeof(p); i++)
    {
        if (member_array(E(p[i]), exclude) >= 0)
            continue;
            
    	if (io == 1 && !E(p[i])->query_prop(ROOM_I_INSIDE))
    	{
    	    p[i]->catch_msg( stringp(message) ? message : message[0] );
    	}
    	else if (io == 2 && E(p[i])->query_prop(ROOM_I_INSIDE))
    	{
    	    p[i]->catch_msg( stringp(message) ? message : message[0] );
    	}
    	else if (io == 3)
    	{
    	    if (E(p[i])->query_prop(ROOM_I_INSIDE))
    	    {
    	        p[i]->catch_msg( stringp(message) ? message : message[1] );
    	    }
    	    else
    	    {
    	        p[i]->catch_msg( stringp(message) ? message : message[0] );
    	    }
    	}
    }
    return p;
}

/* A hack! */
varargs public object *
tell_sanction(mixed subdir, mixed message, int io = 1, object *exclude = ({ }), string basedir = "sanction/room")
{

    return tell_neraka(subdir, message,io,exclude,basedir);
    }

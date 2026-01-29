/*
 * Standard routines for the rooms outside of the inner gates
 * of the city (fourth to seventh Gate)
 * This file handles the password check
 *
 * To be inherited by the room files.
 *
 * 11-nov-1994, Olorin
 */
#include <language.h>
#include <macros.h>
#include <std.h>

#include "/d/Gondor/defs.h"

#define MT_I_WRONG_PASSWORD	"_MT_i_wrong_password"
#define MT_I_GAVE_PASSWORD	"_MT_i_gave_password"

varargs string set_gate_room(string str = 0);

int     gate_closed = 0;
string  gate_room;

void
close_gate()
{
    gate_room->close_gate();
}

int
pass_gate()
{
    object  tp = TP;

    if (!strlen(gate_room))
        set_gate_room();

    if (gate_room->query_gate_open())
    {
        set_alarm(0.0, 0.0, close_gate);
        return 0;
    }

    if (tp->query_wiz_level())
    {
        if (tp->query_real_name()=="elessar")
        {
            write("The guard bows before you, saying: Hail Gondor, my Lord and King!\n"
                + "The guards says: Nothing to report!\n");
            say("The guard bows before "+QTNAME(tp)+", saying: Hail Gondor, my Lord and King!\n"
                + "The guards says: Nothing to report!\n");
        }
        else if (SECURITY->query_wiz_domain(tp) == "Gondor")
        {
            write("The guard bows before you, saying: Hail, Wizard of Gondor!\n"
                + "The guards says: You may pass!\n");
            say("The guard bows before "+QTNAME(tp)+", saying: Hail, Wizard of Gondor!\n"
                + "The guards says: You may pass!\n");
        }
        else
        {
            write("The guard bows before you, saying: Hail, Wizard!\n"
                + "The guards says: You may pass!\n");
            say("The guard bows before "+QTNAME(tp)+", saying: Hail, Wizard!\n"
                + "The guards says: You may pass!\n");
        }
        return 0;

    }
    write("A guard stops you, saying: No-one may pass this Gate without a password!\n");
    say("A guard stops "+QTNAME(tp)+", saying: No-one may pass this Gate without a password!\n");
    return 1;
}

int
check_password(string str)
{
    int     n;
    object  tp = TP;
    string  vb = query_verb(),
            name = tp->query_real_name(),
            dummy = 0,
            pw;

    if (vb[0..0] == "'")
    {
        if (strlen(str))
            str = vb[1..(strlen(vb)-1)] + " " + str;
        else
            str = vb[1..(strlen(vb)-1)];
        vb = "say";
    }

    str = LOW(str);

    if (vb == "whisper")
    {
        if (!strlen(str))
        {
            NF0(CAP(vb)+" what?\n");
        }
        if (parse_command(str, ({ }), " [guard] [the] 'password' [is] %w", dummy))
            str = dummy;
    }
    else
    {
        if (!strlen(str))
        {
            NF0("What do you wish to say?\n");
        }
        if (parse_command(str, ({ }), " [the] 'password' [is] %w", dummy))
            str = dummy;
    }

    if (tp->query_prop(MT_I_WRONG_PASSWORD) && (strlen(dummy)))
    {
        write("The guard glares at you.\n" +
              "The guard says: Begone!\n");
        say("The guard glares at "+QTNAME(tp)+".\n" +
              "The guard says: Begone!\n");
        return 1;
    }
    n = (LANG_ORDW(LOW(TO->query_circle())) + 1);
    pw = M_TIRITH_PW_MASTER->query_password(n, name);


    if (str != pw)
    {
        if (!strlen(dummy))
        // a normal 'say' with argument != pw
            return 0;

        // the player tried the wrong password!
        write("The guard peers suspiciously at you.\n" +
              "The guard says: What are you trying to do?\n" +
              "The guard says: That is not the correct password!\n");
        say("The guard peers suspiciously at "+QTNAME(tp)+".\n" +
            "The guard says: What are you trying to do?\n" +
            "The guard says: That is not the correct password!\n");
        tp->add_prop(MT_I_WRONG_PASSWORD, 1);
    }
    else if (gate_closed)
    {
        write("You give the correct password.\n"
          +   "The guard says: Sorry, but by order of the Steward, the gate has to remain closed!\n"
          +   "The guard says: So I cannot let you pass, even though you know the correct password!\n");
        say(QCTNAME(tp)+" gives the correct password.\n"
          +   "The guard says: Sorry, but by order of the Steward, the gate has to remain closed!\n"
          +   "The guard says: So I cannot let you pass, even though you know the correct password!\n");
    }
    else
    {
        write("You give the correct password.\n");
        say(QCTNAME(tp)+" gives the correct password.\n");
	tp->add_prop(MT_I_GAVE_PASSWORD, 1);
        if (!strlen(gate_room))
            set_gate_room();

        gate_room->open_gate(5);
    }

    return 1;
}

varargs string
set_gate_room(string str = 0)
{
    int     i;
    mixed  *exits;

    if (strlen(str))
        gate_room = str;
    else if ((i = (member_array("@@pass_gate@@",
        (exits = TO->query_exit())))) >= 0)
        gate_room = exits[i-2];

    return gate_room;
}

public void
init_gate()
{
    add_action(check_password, "stsay");
    add_action(check_password, "whisper");
    add_action(check_password, "say");
    add_action(check_password, "'", 1);
}

void
init_gate_closed()
{
    gate_closed = 1;
    init_gate();
}

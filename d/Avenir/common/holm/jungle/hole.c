//-*-C++-*-
// file name:    /d/Avenir/common/holm/jungle/lava_hole.c
// creator(s):   Lilith May 31 1997
// revised:
// purpose:      Place to start slide down lava tube
// note:         
// bug(s):
// to-do:
#pragma strict_types

/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
#include "/sys/cmdparse.h"
#include <filter_funs.h>

#define L_TUBE "d/Avenir/common/holm/jungle/lava_tube"
int i_pl;
void set_full(int i) {    i_pl = i;    }

void create_domain_room()
{
    set_short("A part of the jungle with a hole on the ground");
    set_long("A part of the jungle with a hole on the ground.\n");
    LIGHT;
    IN;	
		
}

int l_tube(string str)
{
    string qvb;

    qvb = query_verb();
    notify_fail(capitalize(qvb) +" what?\n");
    if (!parse_command(str, ({ }), 
        "[in] [the] 'hole' / 'tube' / 'crack'"))
    if (!parse_command(str, ({ }), 
        "[myself] [into] [the] 'hole' / 'tube' / 'crack'"))
        return 0;    

    if (i_pl > 0)
    {
        switch(random(4))
        {
            case 0:                        
                write("As you approach the opening, you can hear screams "+
                    "coming from it.\nYour courage fails you.\n");
                break;
            case 1:                        
                write("It looks awfully dark down there, are you "+
                    "sure you want to do that?\n");
                break;
            case 2:                        
                write("Shrieks of fear and pain echo from within "+
                    "the hole, turning your arms and legs to "+
                    "rubber.\nYou don't have the strength to do "+
                    "that right now.\n");
                break;
            case 3:                        
                write("Air ripe with the smell of decaying flesh "+
                    "wafts up from the hole, turning your stomach."+
                    "\nYou decide to wait a moment, to let your "+
                    "stomach settle.\n");
                break;
        }
        return 1;
    }
    write("You fling yourself down into the hole.\nDarkness "+
        "and a horrible stench immediately overwhelm you, and "+
        "you experience a weightless sensation.\n");
    say(QCTNAME(TP)+ " enters the hole.\n"+ capitalize(POSSESS(TP)) +
        " long, drawn-out cry fills your ears.\n");
    i_pl = 1;
    TP->move_living("M", L_TUBE, 1);
    return 1;
}

int push_it(string str)
{
    object *obs, ob;

    notify_fail("Push who?\n");
    if (!str)
        return 0;
    notify_fail("Push who into the hole?\n");
    if (!parse_command(str, environment(TP), 
        "[the] %s [into] [the] 'hole' / 'tube' / 'crack'", str))
        return 0;    

    obs = FIND_STR_IN_OBJECT(str, this_object());

    notify_fail(capitalize(str) +" isn't here.\n");
    if (!sizeof(obs))
        return 0;
    notify_fail("You can only push one at a time!\n");
    if (sizeof(obs) > 1)
        return 0;

    ob = obs[0];

    if (i_pl > 0) 
    {
        write("Ooops! You missed!\n");
        ob->catch_msg(QCTNAME(TP) +" tried to push you down into "+
            "the hole!\n");     
        return 0;
    }
    
    write("You give "+ QTNAME(ob) +" a hard shove, sending "+
        OBJECTIVE(ob) +" tumbling down into the hole.\n");                
    ob->catch_msg(QCTNAME(TP) +" shoves you toward the hole! "+
        "You teeter on the edge with one foot swaying wildly "+
        "over the foul-smelling hole, then lose your balance "+
        "completely and tumble down!\n");
    say(QCTNAME(TP) +" shoves "+ QTNAME(ob) +" toward the "+
        "hole!\n"+ capitalize(PRONOUN(ob)) +" teeters on the "+
        "edge for a moment, then tumbles down into the foul-"+
        "smelling darkness!\n", ({ TP, ob }));
    i_pl = 1;
    ob->move_living("M", L_TUBE, 1);
    return 1;
}

void init()
{
    ::init();

    add_action(l_tube,    "enter");
    add_action(l_tube,    "jump");
    add_action(l_tube,    "lower");
    add_action(push_it,   "push");
    add_action(push_it,   "shove");
}


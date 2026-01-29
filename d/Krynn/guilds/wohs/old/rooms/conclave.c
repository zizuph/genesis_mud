/*
 * The conclave room. 
 *
 * Originally by Jeremiah
 *
 * Reworked by Cotillion, Feb 23 2003
 */
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit TOWERROOM;

int study_enter(string color, string dir);
public varargs int control_access(int grant, string str = 0);
int pull(string str);

#define ENTER_PROP "krynn_wohs_study"

void
create_tower_room()
{
    set_short("Conclave board room and lobby");
    set_long("This is the area of the conclave of the mages of Wayreth. " +
        "Here the masters of the three factions of mages have " +
        "their private studies. White is to the north, Red is " +
        "to the west, and Black is to the south. A colored bell " +
        "cord hangs in front of each of the three offices of the " +
        "Wayreth conclave and an exit leads east to the stairwell.\n");

    AI(({"spectres","powerful spectres","spectre","guardian","subtle spectres"}),
        "Though you can't see them, you have no doubt that they'll make " +
        "their presence known should you attempt to enter an office unbidden.\n");

    AI(({"colored cord","cord","cords","bell cord","bell cords","colored bell cords"}),
        "Which bell cord? The white, red, or black cord?\n");
    
    AI(({"white cord","white bell cord","silk"}),
        "Pull this cord, made of thick, pure white silk, to ring the bell " +
        "inside the office of the master of the White " +
        "Robed Mages.\n");
    AI(({"red cord","red bell cord","satin"}),
        "Pull this cord, made of thick, vibrant crimson satin, to ring the " +
        "bell inside the office of the master of the Red " +
        "Robed Mages.\n");

    AI(({"black cord","black bell cord"}),
        "Pull this cord, made of thick, deep midnight velvet, to ring the " +
        "bell inside the office of the master of the " +
        "Black Robed Mages.\n");
    
    add_exit("stairwell08", "east");
    add_exit("whitestudy",  "north", &study_enter(WHITE, "north"));
    add_exit("blackstudy",  "south", &study_enter(BLACK, "south"));
    add_exit("redstudy",    "west",  &study_enter(RED, "west"));
    
    clone_object(OBJ + "conclave_board")->move(this_object());
}


int
pull(string str)
{
    string word, room, dir;
    int i;

    notify_fail("Pull which bell cord?\n");
    if (!stringp(str))
    {
        return 0;
    }
    
    if (!parse_command(str, ({ }), "[the] %w [bell] [cord]", word))
    {
        return 0;
    }
    
    if ((i = member_array(capitalize(word), ({ RED, BLACK, WHITE }))) < 0)
    {
        return 0;
    }
    
    /* This is the directions in the same order as in the array above */
    dir = ({ "west", "south", "north" })[i];
    i = member_array(dir, query_exit_cmds());
    room = query_exit_rooms()[i];
    
    write("You pull the " + word + " bell cord and a faint ringing is " +
        "heard in the office to the "  + dir + ".\n");
    
    say( QCTNAME(TP)+" pulls the " + word + " bell cord and a " +
        "faint ringing is heard in the office to the " + dir + ".\n");
    
    tell_room(room, "A bell materializes above the door and " +
        "rings, signaling that someone is outside and wishing " +
        "for your attention.\n");
    return 1;
}

int
study_enter(string color, string dir)
{
    if (TP->query_wiz_level())
    {
        write("The spectral guardian bows deeply as you enter the " + 
            "study to the " + dir + ".\n");
        say("The spectral guardian bows deeply as " + QCTNAME(TP) + 
            " enters the study to the " + dir + ".\n");
        return 0;
    }
    
    if (ADMIN->conclave_head(color) == TP->query_real_name())
    {
        write("The spectral guardian obediently reports that no " +
            "one has entered your office since you left and humbly " +
            "steps aside as you enter your office.\n");

        say("The spectral guardian briefly reports to "+QCTNAME(TP)+" and " +
            "humbly steps aside for "+HIM(TP)+" as "+HE(TP)+
            " enters "+HIS(TP)+" office.\n");
        return 0;
    }

    if (member_array(color, TP->query_prop(ENTER_PROP)) < 0)
    {
        write("A powerful and ghastly spectral guardian appears before " +
            "you and with a single, freezing touch " +
            "halts all your thoughts of entering the office of the Head " +
            "of the " + color + " Robed Wizards.\n");
        say("A powerful and ghastly spectral guardian appears before " + 
            QTNAME(TP) + " and with a touch halts all " + HIS(TP) + 
            " thoughts of continuing " + dir + ".\n"); 
        return 1;
    }
}

void
init()
{
    /* There are slightly special add_actions
     * In reality the function call will be control_access(int, str)
     * It's confusing but if a , is added it will runtime 
     */
    ADD(&control_access(1), "permit");
    ADD(&control_access(1), "grant");
    ADD(&control_access(0), "remit");
    ADD(&control_access(0), "revoke");
    ADD(pull, "pull");
    ::init();
}



public varargs int 
control_access(int grant, string str = 0)
{
    object target;
    string color, *tmp;

    if (TP->query_wiz_level())
    {
        NF("Wizards should play with the prop if they deem it necessary.\n");
        return 0;
    }

    if (!CONCLAVE(TP))
    {
        NF("You are not a member of the conclave.\n");
        return 0;	
    }

    NF("Grant whom permission to enter your office?\n");
    if (!str)
    {
        return 0;
    }
    
    color = ORDER(TP);

    target = P(str, TO);
    
    if (!objectp(target) || !living(target))
        return 0;

    tmp = target->query_prop(ENTER_PROP);
    if (!pointerp(tmp))
        tmp = ({ });
    
    if (grant)
    {
        tmp += ({ color });
        write("You grant " +  target->query_the_name(TP) + 
            " permission to enter your office.\n");
        target->catch_msg(TP->query_The_name(target) + 
            " grants you permission to enter " + HIS(TP) + " office.\n");
        
    } else {
        if (member_array(color, tmp) < 0)
        {
            NF("That person does not currently have permission to " + 
                "enter your office.\n");
            return 0;
        }

        write("You revoke " + target->query_the_possessive_name(TP) + 
            " permission to enter your office.\n");
        target->catch_msg(TP->query_The_name(target) + 
            " revokes your permission to enter " + HIS(TP) + " office.\n");
        tmp -= ({ color });
    }
    
    target->add_prop(ENTER_PROP, tmp);
    return 1;
}


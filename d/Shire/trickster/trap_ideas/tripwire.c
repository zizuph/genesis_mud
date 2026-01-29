#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include "/d/Shire/trickster/trickster.h"
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <std.h>
#include <tasks.h>

//   Prototypes
void remake_trap();
void make_them_laugh(object player);

int   Trap_qual, ready = 0, armed = 0;
string  Room, Trap_setter, Wire_file, Direction = "somewhere";

void
set_up_trap(int qual, string setter, string dir, string file)
{
    Direction = dir;
    Trap_qual = qual;
    Trap_setter = setter;
    Wire_file = file;
}

void
remake_trap() 
{
    int i;
    
    for (i = 0;i < sizeof(ENV(TO)->query_exit_cmds()) ; i++)
    {
        if (ENV(TO)->query_exit_cmds()[i] == Direction)
            {
            Room = ENV(TO)->query_exit_rooms()[i];
         }
    }
}

void
create_object()
{
    set_name("trickster_trip_object");
    add_name(({"trap","tripwire","wire"}));
    set_short("@@my_short@@");
    set_long("@@my_long@@");
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_GET,"@@myget@@");
}

string
my_short() 
{
    return "short";
}

string my_long()
{
    return "long\n";
}

string
myget()
{
    return query_verb() + " what?\n";
}

void
init()
{
    string lastroom = file_name(TP->query_prop(LIVE_O_LAST_ROOM));
    ::init();
    
    add_action("do_trip","sneak");
    add_action("do_trip",Direction);
    add_action("do_disarm","disarm");
    //   To make sure it doesn't go off when cloned
    if (!ready)
        {
        set_alarm(0.5,0.0,remake_trap);
        ready = 1;
        return;
    }
    if (Room != lastroom)
        return;
    if (TP->query_real_name() == Trap_setter)
        {
        write("You carefully avoid your trip wire so that you will not "+
            "set it off.\n");
        return;
    }
    if (TP->resolve_task(TASK_ROUTINE, ({SS_FR_TRAP,SS_AWARENESS}),TO,
            ({Trap_qual*3})) >= 0)
    {
        write("You carefully avoid a tripwire which has been placed here.\n");
        return;
    }
    if (!random(5))
        {
        //   They might be lucky and not trip over it
        return;
    }
    say(QCTNAME(TP)+" trips over a tripwire and falls.\n");
    write("You trip over a hidden tripwire  and fall on your face!\n");
    if (armed)
        {
        make_them_laugh(TP);
    }
}

int
do_trip(string str)
{
    if (str)
        {
        return 0;
    }
    if (TP->query_real_name() == Trap_setter)
        {
        write("You carefully avoid your trip wire so that you will not "+
            "set it off.\n");
        return 0;
    }
    if (TP->resolve_task(TASK_ROUTINE, ({SS_FR_TRAP,SS_AWARENESS}),TO,
            ({Trap_qual*3})) >= 0)
    {
        write("You manage to have avoided a tripwire as you walked "+Direction+".\n");
        return 0;
    }
    if (random(4)) //  They might be lucky 
        {
        return 0;
    }
    tell_room(ENV(TO),QCTNAME(TP)+" trips and falls over a cleverly "+
        "hidden tripwire as they walk "+Direction+".\n",TP);
    TP->catch_msg("You trip over a trip wire as you walk "+Direction+
        " landing on your face!\n\nOuch!!\n");
    tell_room(Room,QCTNAME(TP)+" arrives falling right on "+HIS_HER(TP)+
        " face!!!\n",TP);
    if (armed)
        {
        set_alarm(0.1,0.0,&make_them_laugh(TP));
    }
    return 0;
}

int
do_disarm(string str)
{
    int success;
    
    if(!str)
        {
        notify_fail(capitalize(query_verb())+ " what?\n");
        return 0;
    }
    
    if (member_array(str,TO->query_names()) == -1 || str != "vial")
        {
        notify_fail(capitalize(query_verb())+ " what?\n");
        return 0;
    }
    
    //   Players lose some mana for attempting this
    if (TP->query_mana() < 20)
        {
        notify_fail("You are to mentally exhausted to disarm the "+str+"!\n");
        return 0;
    }
    TP->add_mana(-10);
    
    if (this_player()->resolve_task(TASK_ROUTINE, ({SS_FR_TRAP}), TO,
            ({Trap_qual})) > 0)
    {
        if (str == "vial")
            {
            if (!armed)
                {
                notify_fail(CAP(query_verb())+" what?\n");
                return 0;
            }
            write("You successfully removed the vial from the wire.\n");
            say(QCTNAME(TP) + " successfully removed a vial from a trip wire.\n");
            setuid(); seteuid(getuid());
            clone_object(LAUGH_VIAL)->move(TP,1);
            armed = 0;
            return 1;
        }
        write("You successfully disarmed the trip wire.\n");
        say(QCTNAME(TP) + " successfully disables a trip wire here.\n");
        if (armed)
            {
            write("But you failed to noticed the vial on the wire which has just dropped to the ground!\n");
            make_them_laugh(TP);
        }
        if (Wire_file)
            {
            setuid(); seteuid(getuid());
            clone_object(Wire_file)->move(ENV(TP));
        }
        remove_object();
        return 1;
    }
    
    write("You try to disable the trap, but you just don't think you "+
        "managed it.\n");
    if (armed && !random(2))
        {
        write("Your tampering with the tripwire has caused a vial to drop from it!\n");
        make_them_laugh(TP);
    }
    return 1;
}

void
make_them_laugh(object player)
{
    object laugh;
    
    armed = 0;
    setuid(); seteuid(getuid());
    laugh = clone_object(LAUGH_OBJ);
    laugh->move(ENV(player));
}

void
arm_trap()
{
    armed = 1;
}

int
query_armed()
{
    return armed;
}

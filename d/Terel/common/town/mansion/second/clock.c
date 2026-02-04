/*
 *  Example Chair turned into a clock you can climb inside.
 *
 *		Napture
 */
 
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

#define CLOCK_O_OCCUPIED "_clock_i_occupied"

public int no_command();

create_object()
{
    set_name(({"clock", "grandfather", "grandfather clock"}));
    set_short("clock");
    set_long("This magnificent clock is made from pure oak. " +
	"Despite a loud ticking\nsound eminating from the clock, " +
	"the hands appear to remain still.\n");
    add_prop(OBJ_M_NO_GET, "For some strange reason, the clock seems " +
                           "to be attached to the wall.\n");
    add_prop(OBJ_M_NO_DROP, "Some how you managed to pick up the clock!\n" +
                            "Just for that, it's stuck to your hands!\n");
    add_prop(OBJ_I_INVIS,1);

    add_item(({"hands", "face", "clock face", "clock hands"}),
    	"The hands state the time as two minutes before twelve.\n");
}

init()
{
    ::init();
    add_action("climb_in","enter");
    add_action("climb_in","climb");
    add_action("climb_out","leave");
    add_action("climb_out","out");
    add_action("do_all_commands", "", 1);    
}

public int
do_all_commands(string str)
{
    string verb;
    string *not_allowed;

    if (query_prop(CLOCK_O_OCCUPIED)!=this_player())
        return 0;
        
    not_allowed=({"n","north","s","south","w","west","e","east","nw",
                  "northwest","sw","southwest","se","southeast",
                  "northeast","ne","teleport", "u","up","d","down",
                  "goto","home"});

    verb = query_verb();

    if (member_array(verb,not_allowed)==-1)
        return 0;
    else 
        return no_command();
    
    return 1; /* should never occur */
}
     

no_command()
{
    write("You have to leave the clock to do that!\n");
    return 1;
}


climb_in(string str)
{
    object ob1, who, *list;
    string check;
  
    if (!str)
        return 0;
 
    if ((str=="out") || (sscanf(str,"out %s",check)==1))
        if (!(this_player()->command("out")))  {
            write("You will have to leave the clock, not climb out.\n");
            return 1;
            }
        else return 1;
    if (sscanf(str,"into %s",check)==1)
        str = check;

    if (sscanf(str,"in %s",check)==1)
        str = check;
        
/*   This code only allows for visible objects.
    list=FIND_STR_IN_OBJECT(str,environment(this_player()));
    notify_fail("Can't find any "+str+" here.\n");
    if (member_array(this_object(),list)==-1)
        return 0;
 */
    notify_fail("Can't find any "+str+" here.\n");
    if (!parse_command(str, environment(this_player()), "%o", ob1))
        return 0;
    if ((who = query_prop(CLOCK_O_OCCUPIED)))
        if (who!=this_player())  {
            write(QCTNAME(who)+" is already crouched inside the clock.\n");
            return 1;
            }
        else  {
            write("You are already in the clock!\n");
            return 1;
            }
    change_prop(CLOCK_O_OCCUPIED, this_player());
    this_player()->add_prop(LIVE_S_EXTRA_SHORT," crouched inside a clock");
    write("You climb into the clock.\n");
    write("The ticking sound seems to get louder in here.\n");
    say(QCTNAME(this_player())+" climbs into the clock.\n");
    return 1;
}
    
climb_out(string str)
{
    object ob1, who, *list;
    string check;
    
    notify_fail("You are not inside the clock.\n");
    if (query_prop(CLOCK_O_OCCUPIED)!=this_player())
        return 0;
    change_prop(CLOCK_O_OCCUPIED,0);
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    write("You leave the clock.\n");
    say(QCTNAME(this_player())+" climbs out of the clock.\n");
    return 1;
}



/*
 * Example chair made invisible.
 *
 *  Napture
 */
 
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

#define CHAIR_O_OCCUPIED "_chair_i_occupied"
#define PLAYER_I_STANDS  "_player_i_stands"

public int no_command();

create_object()
{
    set_name(({"chair","small chair"}));
    set_short("small chair");
    set_long("A small uncomfortable chair.\n");
    add_prop(OBJ_M_NO_GET, "The chair seems to be attached to the floor!\n");
    add_prop(OBJ_I_INVIS, 1);
}

init()
{
    ::init();
    add_action("sit_down","sit");
    add_action("stand_up","stand");
    add_action("stand_up","leave");
    add_action("stand_up","climb");
    add_action("stand_up","step");
    add_action("do_all_commands", "", 1);
}

public int
do_all_commands(string str)
{
    string verb;
    string *not_allowed;

    if (query_prop(CHAIR_O_OCCUPIED)!=this_player())
        return 0;
        
    not_allowed=({"n","north","s","south","w","west","e","east","nw",
                  "northwest","sw","southwest","se","southeast",
                  "northeast","ne","teleport", "u","up","d","down",
                  "destruct", "Destruct", "Goto", "goto","home"});

    verb = query_verb();

    if (member_array(verb,not_allowed)==-1)
        return 0;
    else 
        return no_command();
    
    return 1; /* should never occur */
}
     

no_command()
{
    write("You have to leave the chair to do that.\n");
    return 1;
}


sit_down(string str)
{
    object ob1,who,*list;
    string check;
  
    if (!str)
        return 0;

    if (sscanf(str,"down on %s",check)==1)
        str = check;

    if (sscanf(str,"on %s",check)==1)
        str = check;

/*  Only works for visible objects!
    list=FIND_STR_IN_OBJECT(str,environment(this_player()));
    notify_fail("Can't find any "+str+" here.\n");
    if (member_array(this_object(),list)==-1)
        return 0;
*/
    notify_fail("Can't find any " +str+ " here.\n");
    if (!parse_command(str, environment(this_player()), "%o", ob1))
        return 0;
    if ((who = query_prop(CHAIR_O_OCCUPIED)))
        if (who!=this_player())    {
            write(QCTNAME(who)+" is already on the chair.\n");
            return 1;
            }
        else  {
            write("You are already on the chair!\n");
            return 1;
            }
    change_prop(CHAIR_O_OCCUPIED,this_player());
    this_player()->add_prop(LIVE_S_EXTRA_SHORT," sitting on a chair");
    write("You sit down on the chair.\n");
    say(QCTNAME(this_player())+" sits down on the chair.\n");
    return 1;
}

stand_chair(string str)
{
    object ob1,who,*list;

/* Here again, just remove all this...
    list=FIND_STR_IN_OBJECT(str,environment(this_player()));
    notify_fail("Can't find any "+str+" here.\n");
    if (member_array(this_object(),list)==-1)
        return 0;
*/
    notify_fail("Can't find any "+str+" here.\n");
    if (!parse_command(str, environment(this_player()), "%o", ob1))
        return 0;
    if (who = query_prop(CHAIR_O_OCCUPIED))
        if (who!=this_player())    {
           write(QCTNAME(who)+" is already on the chair.\n");
           return 1;
           }
        else  {
            write("You are already on the chair!\n");
            return 1;
            }   
    change_prop(CHAIR_O_OCCUPIED,this_player());
    this_player()->change_prop(PLAYER_I_STANDS,1);
    this_player()->change_prop(LIVE_S_EXTRA_SHORT," standing on a chair");   
    write("You stand on the chair.\n");
    say(QCTNAME(this_player())+" stands on the chair.\n");
    return 1;
}
    
stand_up(string str)
{
    object who,*list;
    string check;

    if (str && (sscanf(str,"on %s",check)==1 ||
       ((check=str)!="up" && (check=str)!="down")))
    {
        if (stand_chair(check))
            return 1;
        return 0;
    }
    if (str && str!="down" && str!="up")
        return 0;

    notify_fail("You are not sitting on it.\n");
    if (query_prop(CHAIR_O_OCCUPIED)!=this_player())
        return 0;
    change_prop(CHAIR_O_OCCUPIED,0);
    this_player()->change_prop(PLAYER_I_STANDS,0);
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    write("You leave the chair.\n");
    say(QCTNAME(this_player())+" stands " + str + " from the chair.\n");
    return 1;
}


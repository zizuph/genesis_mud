inherit "/d/Shire/common/lib/rom.c";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>

int open;

create_rom()
{
    set_short("Tunnel under trollshaws.");
    set_long("You have entered a secret passage in the tunnels. "
       	    +"It is dark here and the air is moisty, with an utter "
       	    +"evil and foul smell. The smell of trolls!. There is only "
       	    +"one way to go, and that is down. This looks just like "
       	    +"a place where trolls would dwell. For light they fear, "
       	    +"and to stone they will turn if upon light they dwell! "
       	    +"The stairs down here are steep and difficult to climb "
       	    +"(They are not made yet  ;)and it is impossible to see what lay beyond them because "
       	    +"of the darkness in here.\n");
       	    
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);
    
    /* add_exit(TROLLSH_DIR + "stunnelA", "down",0,4); NOT MADE YET */
    add_exit(TROLLSH_DIR + "stunnel3","north",0);
    
    add_item(({ "wall", "walls"}),
    		"The walls are dark and moisty, they look smooth.\n");
    		
    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "search");
    
    add_item("lever", "Yes, this is a common lever!\n");
    
    add_call("pull", "[the] [hidden] 'lever'", "pull_lever");
}



string
search(object tp, string str)
{
    if((str=="wall" || str=="walls" || str=="here" || str=="room" || str=="tunnel") && 
       TP->query_skill(SS_AWARENESS)>40) 
        return "Your search reveals a lever hidden on the wall!!!\n";   
    else
        return 0;
        
}

init()
{
    ::init();
    add_action("pull_lever", "pull");
}

pull_lever(string arg)
{
    notify_fail("What is it exactly you are trying to do eh?\n");
    if(arg !="lever")
    return 0;
    if (open)
    {
        write("You desperatly pull the lever, but nothing happens. That must "
             +"be because the door already is open!\n");
        say(QCTNAME(TP) + " desperatly pulls the lever, but nothing happens!\n");
    }
    else
    {
        write("You pull the lever, and a door suddenly is revealed!\n");
        say(QCTNAME(TP) + " pulls on a lever on the wall, revealing a secret passage!\n");
        add_exit(TROLLSH_DIR + "sec_tunnel3", "north", 0);
        open = 1;
        set_alarm(10.0,0.0,"close_door");
    }
    return open;
}

int
close_door()
{
    tell_room(TO, "The secret passage suddenly disappears!\n");
    call_other(TROLLSH_DIR + "sec_tunnel3", "close_door");
    remove_exit("north");
    open = 0;
    return open;
}

query_open()
{
    return open;
}   

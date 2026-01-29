#include "defs.h";

inherit LIB_DIR + "rom";
chk_spider();

int cut;
object nasty_troll;

create_rom()
{
	set_short("secret passage");
	set_long(
		 "You have entered a secret passage in the tunnel. "
		+"It is awfully dark here, and the smell rips trough your heart! "
		+"You can see large footprints on the floor, probably made by "
		+"some huge troll. There are cobwebs hanging down from the walls, "
		+"so it must have been quite a while since anyone have been here.\n");
		
		add_item(({"tunnel"}),
			 "The tunnel is dark and moisty, and it seems like it has been carved "
			+"out of just earth.\n");
		add_item(({"footprints"}),
			 "They are really huge, maybe you should just leave this place "
			+"before any of those who made these footprints shows themselves!!\n");
			
		add_item(({"floor"}),
			 "The floor is all blood stained, filled with dried guts everywhere.\n");
			 
		add_item(({"cobwebs","cobweb"}),
			 "The cobwebs are huge, probably made by the evil spider guarding the "
		        +"tunnel. It doesn't look too strong.\n");
		        
		add_prop(ROOM_I_LIGHT,-1);
		add_prop(ROOM_I_INSIDE, 1);
		add_prop(OBJ_I_SEARCH_TIME, 3);
		add_prop(OBJ_S_SEARCH_FUN, "search");
		
		add_call("cut", "[the] 'cobweb'", "cut_cobweb");
		
		add_exit(TROLLSH_DIR + "stunnel2", "east", 0, 3);
                add_exit(TROLLSH_DIR + "tunnel2", "west", "@@chk_spider");
}

chk_spider()
{
    cut = 0;
    if("cobweb" != "cut_cobweb")
    /*
    if(!present("spider",find_object("/d/Shire/common/trollsh/tunnel2")))
    */
    {
        return 0;
    }
    else
    {
        write("There is too much cobweb for you to enter that way...\n");
        say("The cobweb prevents "+QCTNAME(TP)+" from going west!\n");
        /*add_item("cobweb", "The exit is blocked by cobweb, but it doesn't look too strong!\n");*/
        return 1;

    }
}

string
search(object tp, string str)
{
    if(str=="cobweb")
        return "As you search the cobweb carefully, you notice that it is not that strong.\n"+
               "You might be able to cut it with a sharp blade.\n";
               
    else
        return 0;
}

init()
{
    ::init();
    add_action("cut_cobweb", "cut");
}

cut_cobweb(string arg)
{
    notify_fail("What are you trying to cut?\n");
    if(arg !="cobweb")
    return 0;
    if (cut)
    /*
    if (!present("spider", find_object(TROLLSH_DIR + "tunnel2")))
    */
    {
        write("You desperatly try to cut the cobweb which is not here anymore!\n");
        say(QCTNAME(TP) + " desperatly tries to cut the cobweb which is not here anymore!\n");
    }
    else
    { 
        write("You cut the cobweb with a clean cut.\n");
        say(QCTNAME(TP) + " cuts the cobweb with a clean, nice cut.\n");
   	cut = 1;
    }
    return cut;
}

reset_web()
{
    cut = 0;
}

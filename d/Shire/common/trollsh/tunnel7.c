inherit "/d/Shire/common/lib/rom.c";

#include "/d/Shire/common/defs.h"

create_rom()
{
    set_short("Stairs going under the tunnels");
    set_long(
    	     "You are walking downwards some stairs. It is a dark and creepy "
    	    +"place, with a foul sence in the air. There is some strange marks "
    	    +"on the wall, some utter foul and evil signs. And the smell in here.. "
    	    +"it must be worse then anything else you ever have smelled. You can "
    	    +"continue further north, but that would be on your own risk. "
    	    +"On the wall there is a sign.\n");
    	    
    add_exit(TROLLSH_DIR + "tunnel4", "north", 0, 2);
    add_exit(TROLLSH_DIR + "tunnel3", "southeast", 0, 2);
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    
    add_item(({ "marks", "mark", "signs", "sign" }), "The writing is in some strange foreign "
        		+"language, most likely in the Black tongue, since all trolls are using "
    			+"that foul language. But there is also some writing in what "
    			+"seems to be the common tongue, and from that you can \n" 
    			+"read: \n"
    			+"  \n"
    			+"@@common_tongue@@ \n");
    			
    add_item(({ "stairs", "stair" }), "The stairs are steep, and they are carved out of "
    				     +"black rock, not any good craftswork, not the work "
    				     +"dwarves would have done.\n");
    				     
    add_call("smell", " [the] [foul] 'air'", "do_smell");
    
}
/*
init()
{
    ::init();
    add_action("do_smell","smell");
}
*/
int
do_smell(string arg)
{
    if (arg)
    {
        write("You inhale the air deeply, with a big smile on your face!\n"+
 	      "Yakes.......What an aweful smell in here!!!!\n");	
 	say(QCTNAME(TP)+" inhales the air deeply, with a big smile on his face!\n");
	TP->command("puke");
	TP->command("shiver");
        TP->add_fatigue(-20);
        return 1;
    }
    else
    notify_fail("Smell what?\n");
    return 0;
}

string
common_tongue(string str)
{
    if (TP->query_skill(SS_LANGUAGE) > 40)
    {
        return "Thou shallt not enter these tunnels without Azog's leave! "
              +"Thou willt findet death if thou ist not worthy!!\n";
    }
    else
    if (TP->query_skill(SS_LANGUAGE) > 20)
    {
        return "Thou soher nso ekftd thsee mineee wothoit Azog's lvaefr!!\n"
              +"Thou ....f ...fd.  death.  thou..  i.t..  wor..y!!!\n";	
        TP->command("ponder");
    }
    else {
    return "toesa sgftd ned sfgtr tsese fdghlk wigfds AZOG's lebyui!!\n";
    TP->command("shrug");
         }
}
/*
int
do_smell(string arg)
{
    if (!id(arg))
    return 0;
    else
    {
        write("You inhale the air deeply, with a big smile on your face!");
        say(QCTNAME(TP)+" inhales the air deeply, with a big smile on his face!");
        this_player()->command("puke");
        TP->command("shiver");
        return 1;
    }
}
*/

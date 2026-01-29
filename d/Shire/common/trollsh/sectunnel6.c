inherit "/d/Shire/common/lib/rom.c";
inherit "/d/Immortal/rogon/lib/tell";
inherit "/d/Immortal/rogon/lib/message";

#include "/d/Shire/common/defs.h"

create_rom()
{
    set_short("Stairs going under the tunnels.");
    set_long(
    	     "You are walking downwards in some stairs. It is a dark and creepy "
    	    +"place, with a foul sense in the air. There are some strange marks "
    	    +"on the wall, some utter foul and evil signs. And the smell in here.. "
    	    +"it must be worse then anything else you ever have smelled. You can "
    	    +"continue further downwards, but that would be on your own risk.\n");
    	    
    add_exit(TROLLSH_DIR + "sectunnel5", "up", 0, 7);
    add_exit(TROLLSH_DIR + "undtunnel1", "north", 0, 4);
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    
    add_item(({ "marks", "mark", "signs", "sign" }), "The writing is in some strange foreign language, "
   +"most likely the Black tongue, since all Trolls use "+
   "that foul, uncouth language.\n");
    			
    add_item(({ "stairs", "stair" }), "The stairs are steep, and they are carved out of "
    				     +"black rock, not any good craftswork, not the work "
    				     +"dwarves would have done.\n");
    				     
    add_call("smell", "[the] 'air'", "do_smell");
    
}

/*
int
common_tongue(string str)
{
    if (TP->query_skill(SS_LANGUAGE) > 30)
    {
        write("Thou shallt not enter these tunnels without Azog's leave!\n");
        TP->command("tremble");
        return 1;
    }
    else
    if (TP->query_skill(SS_LANGUAGE) > 20)
    {
        write("Thou soher nso ekftd thsee mineee wothoit Azog's lvaefr!!\n");
        TP->command("ponder");
        return 1;
    }
    else {
    write("toesa sgftd ned sfgtr tsese fdghlk wigfds AZOG's lebyui!!\n");
    TP->command("shrug");
    return 1;
         }
}

*/
int
do_smell(string arg)
{
    if (!id(arg))
    return 0;
    action("$N $inhale the air deeply, with a smile on $p face!");
    TP->command("puke");
    TP->command("shiver");
    return 1;
}

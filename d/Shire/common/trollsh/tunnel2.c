

#include "defs.h";

inherit "/d/Shire/common/trollsh/tunnrom";
object spider;
create_tunnrom()
{
    set_short("dark tunnel");
    set_long(
        "You are at the bottom the stairs which lead down from the trollshaws. "
       +"It is dark here, and almost impossible to see what moves in the shadows. "
       +"The air is tense and evil is radiating down here. Water trickles down "
+"the wall. The walls are covered with cobwebs all over, except for a small "
       +"sign with some markings.\n");
       
    add_prop(ROOM_I_LIGHT,-1);
    add_prop(ROOM_I_INSIDE,1);
    
    add_item(({"stairs","stair" }),
        "Well, its not stairs actually, but the path is so steep so it is almost like stairs.\n");
        
    add_item("tunnel",
        "The tunnel is dark and humid. It looks like trolls have haunted this place.\n");
        
    add_item(({"cobweb","web"}),
"The cobweb looks like it has been made from a quite large spider, and it is huge\n");

    add_item(({"marks","mark","markings","signs","sign" }), "The writing is in some strange foreign "
        		+"language, most likely in the Black tongue, since all trolls are using "
    			+"that foul language. But there is also some writing in what "
    			+"seems to be the common tongue, and from that you can \n"
    			+"read: \n"
    			+"  \n"
    			+"@@common_tongue@@ \n");

    add_item(({ "stairs", "stair" }), "The stairs are steep, and they are carved out of "
    				     +"black rock, not any good craftswork, not the work "
    				     +"dwarves would have done.\n");
    
    add_exit(TROLLSH_DIR + "tunnel3", "north", 0, 2);
    add_exit(TROLLSH_DIR + "tunnel1", "up", 0, 5);    
      
      spider = clone_object(TROLLSH_DIR + "npc/" + "spider");
      spider->move(TO);
 
}
reset_tunnrom()
{
   if (!spider) 
   { 
      spider = clone_object(TROLLSH_DIR + "npc/" + "spider");
      spider->move(TO);
   }

}
 

init(){
       ::init();
        add_action("do_smell", "smell");
        add_action("exa_air", "exa");
       }

string
common_tongue(string str)
{
    if (TP->query_skill(SS_LANGUAGE) > 30)
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


do_smell(str)
{
    if(str=="air" || str=="the air")
    {
        write("You inhale the air deeply, with a big smile on your face!\n");
        say(QCTNAME(TP)+" inhales the air deeply, with a big smile on his face!\n");
        this_player()->command("puke");
        TP->command("shiver");
        return 1;
    }
      notify_fail(capitalize(query_verb()) + " what, the air perhaps?\n");
      return 0;
}

exa_air(str)
{
    if(str=="air" || str=="the air")
    {
        write("You inhale the air deeply, with a big smile on your face!\n");
        say(QCTNAME(TP)+" inhales the air deeply, with a big smile on his face!\n");
        this_player()->command("puke");
        TP->command("shiver");
        return 1;
    }

}

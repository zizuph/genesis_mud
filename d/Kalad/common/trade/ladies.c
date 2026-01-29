inherit "/std/room";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_room()
{
    set_short("The Ladies Restroom");
    set_long("You are in the ladies restroom. It is a filthy, smelly "
             +"room. The walls are carved with words and drawings. "
             +"Here can you relieve yourself. You can either urinate or "
	+"defecate.\n");
     add_exit(TRADE(restaurant),"out",0);
     add_item("words","They are readable.\n");
     add_item("drawings","Mostly they are drawings of body-parts.\n");
     add_cmd_item("words","read","They are unusefull words.\n");
     /* Maybe the words can give clues to quests. Mail me if you have an */
     /* Idea.                             ~Huib                          */
}

void
init()
{
     ::init();
     add_action("shit","shit");
     add_action("shit","defecate");
     add_action("piss","piss");
     add_action("piss","urinate");

}

int
shit()
{
     set_alarm(2.0 , 0.0 , "shit_more" , ({ this_player() ,0 }) );
     return 1;
}

int
shit_more(mixed args)
{
    object ob;
    int time;

    ob = args[0];
    time = args[1];

    switch(time)
    {
       case 0:
	ob->catch_msg("You settle down on one of the latrines and start to defecate..\n");
	say(QCTNAME(this_player()) + " settles down to defecate.\n");
       break;
       
       
       case 1:
       ob->catch_msg("You press..\n");
       break;
       
       case 2:
       ob->catch_msg("You press harder..\n");
       break;

       case 3:
       ob->catch_msg("Your face turns red...\n");
       break;

       case 4:
       ob->catch_msg("And then suddenly...\n");
       break;

       case 5:
       ob->catch_msg("SPLASH!!!!!\n");
       say("You hear a loud splash.\n");
       break;

       case 6:
       ob->catch_msg("You feel relieved as you did your job well and stand "
                    +"up.\n");
       say("As " +QCTNAME(this_player()) + " stands up the room fills itself with"
                  + " a rotten smell.\n");
       break;
      
       default:
       return 1;
     }
     set_alarm(1.0 , 0.0 , "shit_more" , ({ ob , time+1}) );
} 

int
piss()
{
     write("You urinate and feel very relieved.\n");
     say (QCTNAME(this_player()) + " urinates and looks very relieved.\n");
     return 1;
}

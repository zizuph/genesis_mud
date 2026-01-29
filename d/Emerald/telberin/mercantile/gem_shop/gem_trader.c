inherit "/d/Emerald/std/elf.c";

#include <macros.h>


void tale_tell(string *story,int increment);
string emerald_tale();



public void
create_elf()
{
    set_name("Yliar");
    set_short("chubby roundfaced male elf");
    set_long("You see an elf, rather small for his race. His whole demeanor " +
       "reveals that this is someone who really enjoys comfort. He is " +
       "presently sitting leaned back in a large cuhsioned chair behind " +
       "the counter.\n");
       
    config_elf(50);
    set_adj(({"chubby", "roundfaced"}));
    set_gender(G_MALE);
    set_size_descs("short", "fat");
    add_ask(({"casing","glass casing","emerald","large emerald"}),
       emerald_tale); 
    //add_ask("orhil",orhil_tale);

    set_act_time(8);
    add_act("emote fishes out a loupe from a pocket and attentively " +
        "studies a gem through it.\n");
    add_act("emote picks up a gem and cleans it with a piece of cloth.\n");
    add_act("emote stares contentedly around in the room.\n");
    add_act("emote places a big gem on one of the scale pans. " +
        "He grins with joy when the scale pan drops to the counter with " +
        "with a big clinging noise.\n");
          

}


void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if (old)
    {
        clear_act();
    }
}


string
orhil_tale()
{
    /*string orhil=({"say Orhil was a rich nobleman of the Manthiex family",
        "say*/ 
}
string
emerald_tale()
{
    string *emerald=({"say A most fantastic stone isn't it?", "say It is such a " + 
        "gem that makes this profession so exciting.", "say The sad chain of " +
        "events that made it available to me takes some joy out of it, " +
        "though.", "say You see, it came into my possession through the " +
        "misfortune someone else.","say Poor Orhil.", "sigh sadly"});
    set_alarm(1.0,0.0,tale_tell(emerald,0));

    return "";
}    

  
  
void
tale_tell(string *story,int increment)
{
     command(story[increment]);

    if ((sizeof(story)-1) != increment)
    {
        
        increment=(increment + 1);
        set_alarm(2.0, 0.0, &tale_tell(story,increment));    
    }
    
}

	
	    
/* /d/Faerun/guilds/vampires/obj/vamp_puzzle_box4.c
 * 
 * Nerull 2021
 */

inherit "/std/object.c";

#include <stdproperties.h>
#include "../guild.h"

int correct_nr1;   
int correct_nr2;   
int correct_nr3; 

int dial_nr1;
int dial_nr2;
int dial_nr3;

int cooldown = 0;


void
set_correct_nr1(int i)
{
    correct_nr1 = i;
    
    return;
}


void
set_correct_nr2(int i)
{
    correct_nr2 = i;
    
    return;
}


void
set_correct_nr3(int i)
{
    correct_nr3 = i;
    
    return;
}


int
query_correct_nr1()
{
    return correct_nr1;
}


int
query_correct_nr2()
{
    return correct_nr2;
}


int
query_correct_nr3()
{
    return correct_nr3;
}


void
destroy_box()
{
    //VAMPIRES_OBJHANDLER->set_box1_inactive();
           
    remove_object();
}


int
check_me()
{
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) != 4)
    {
        return 0;
    }
    
    write("You feel this object is radiating an aura of "
    +"coldness when you try to pick it up. You let it be.\n");
    
    return 1;
}


void
create_object()
{  
    set_name("seashell");
    add_name("sea shell");
    add_name("shell");
    
    set_adj("fine");
    add_adj("red");
    
    set_short("fine red seashell");
    set_pshort("fine red seashell");
       
    set_long("This is a rather pretty sea shell, coloured red like "
    +"blood. It has been polished by seawater for probably decades, "
    +"giving the outside a very smooth nice look. Though, in dark "
    +"contrast, the inside of the shell is for some reason way "
    +"rougher. It measures about two inches in diameter, and is "
    +"thicker than usual.\n");

    add_item(({"inside"}),
        "Partly hidden inside the "
        +short()+", you notice a tiny button "
        +"and three small dials.\n");  

    add_item(({"button", "tiny button", "tear", "tear-shaped button"}),
        "This is a tiny button shaped like a tear. You think this "
        +"button can be pressed.\n");    

    add_item(({"dials", "dial", "tiny dial",
        "tiny dials", "small dial", "small dials"}),
        "All the three small dials have tiny, faint "
        +"arrow-marks engraved on "
        +"them. Around each dial you see tiny numbers ranging "
        +"from zero to ten. You can check left, middle or the right "
        +"dial to see what number they point at. The dials " 
        +"can also be adjusted.\n");  

    add_item(({"number", "numbers", "tiny number", "tiny numbers"}),
        "The numbers surrounding each dial ranges from zero to ten.\n");            
    
    add_prop(CONT_I_VOLUME,  1000);
    add_prop(CONT_I_WEIGHT,  500);
    add_prop(OBJ_M_NO_STEAL, check_me);
    add_prop(OBJ_M_NO_GET, check_me);
    
    setuid();
    seteuid(getuid());
    
    //A box fades away after 3 hours.
    set_alarm(PUZZLEBOX_EXPIRE, 0.0, &destroy_box());
}


void
reset_cooldown()
{
    cooldown = 0;
    
    return;
}


int
press_button(string str)
{
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) != 4)
    {
        return 0;
    }
    
    if (str != "button")
    {
        write("Perhaps you should 'press button'?\n");
        
        return 1;
    }
    
    if (cooldown == 1)
    {         
        write("You press the tear-shaped "
        +"button inside the "+short()+", but nothing "
        +"happens. Maybe it has been pressed recently by someone?\n");
         
        return 1;
    }
     
    if ((dial_nr1 == correct_nr1) && (dial_nr2 == correct_nr2) 
    && (dial_nr3 == correct_nr3))
    {
        write("With a faint 'click', you press the tear-shaped "
        +"button inside the bottom of the "+short()+".\n");
        
        if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 4)
        {       
            //write("A powerful alien force invades your mind!\nYou are paralyzed!\n");
            
            SEEKER_LOG("seeker_log",
            "The investigator " +this_player()->query_name() 
            +" finished puzzle 4.\n");
            
            VAMPIRES_MAPPINGS->set_vampires_seeker(this_player()->query_name(), 5);
            
            if (!present("box4_paralyze", this_player()))
            {
                clone_object(BOX4_PARALYZE)->move(this_player(), 1);
            }
            
                        
            VAMPIRES_OBJHANDLER->set_box4_inactive();
            
            write("The "+short()+" suddenly fades away.\n");
            
            destroy_box();
            
            return 1;
            
            // Add successlogg here.           
        }

        cooldown = 1;        
        
        set_alarm(120.0, 0.0, &reset_cooldown());
     
        return 1;        
    }
    
    SEEKER_LOG("seeker_log",
    "The player " +this_player()->query_name() 
    +" failed puzzle 4.\n");
      
    write("With a faint 'click', you press the tear-shaped "
        +"button inside bottom of the "+short()+".\n");
        
    cooldown = 1;        
        
    set_alarm(120.0, 0.0, &reset_cooldown());
      
    return 1;
}


int
check_dial(string str)
{
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) != 4)
    {
        return 0;
    }
    
    if (str == "left dial")
    {
        write("You examine the left dial, and you notice that it points at " 
            +"the number "+dial_nr1+".\n");
          
        return 1;
    }
               
    if (str == "middle dial")
    {   
        write("You examine the middle dial, and you notice that "
        +"it points at the number "+dial_nr2+".\n");
          
        return 1;
    }
           
    if (str == "right dial")
    {
        write("You examine the right dial, and you notice that it "
        +"points at the number "+dial_nr3+".\n");
          
        return 1;
    }
              
    if (str == "dial" || str == "dials")
    {
        write("Check which dial, the left, middle or the right dial?\n");
        
        return 1;
    }
        
    return 0;
}


int
adjust_dial(string str)
{
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) != 4)
    {
        return 0;
    }
    
    if (str == "left dial")
    {
        dial_nr1 = dial_nr1 + 1;
      
        if (dial_nr1 > 10)
        {
            dial_nr1 = 0;
        }

        write("You adjust the left dial on the "
        +short()+". Its tiny, faint " +
        "arrow-mark now points at the number: "+dial_nr1+".\n");
        
        return 1;
    } 
        
    if (str == "middle dial")
    {
        dial_nr2 = dial_nr2 + 1;
      
        if (dial_nr2 > 10)
        {
            dial_nr2 = 0;
        }

        write("You adjust the middle dial on the "
        +short()+". Its tiny, faint " +
        "arrow-mark now points at the number: "+dial_nr2+".\n");
        
        return 1;
    } 
            
    if (str == "right dial")
    {
        dial_nr3 = dial_nr3 + 1;
      
        if (dial_nr3 > 10)
        {
            dial_nr3 = 0;
        }

        write("You adjust the right dial on the "
        +short()+". Its tiny, faint " +
        "arrow-mark now points at the number: "+dial_nr3+".\n");
        
        return 1;
    } 
        
    write("Adjust what, the left, middle or the right dial?\n");
    
    return 1;
}             


public int 
check_seen(object for_obj)
{
    // Wizards can always see us.
    if (for_obj->query_wiz_level())
    {
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 4)
    {
        return 1;
    }
               
    return 0;
}        


void
init()
{
    ::init();
    add_action(press_button, "press");
    add_action(check_dial, "check");
    add_action(adjust_dial, "adjust");
}
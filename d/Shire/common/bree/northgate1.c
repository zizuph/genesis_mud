inherit "/d/Shire/common/lib/rom";
#include "/d/Shire/common/defs.h"

#include "defs.h"

create_rom()
{
    set_short("Northern gate of Bree.\n");
    set_long("You are standing in front of the northern gate of the village "
    	    +"Bree. The Gatekeeper's lodge is empty. The road leads out to the "
    	    +"Deadmans Dike' which is north of here. The gate is usually closed "
    	    +"because the road going north from here is all grown over by bushes. "
    	    +"You can see a lot of bushes around here, blocking most of the view. "
    	    +"You can see a road going up to the hill just east of here.\n");
    	    
    add_item("gate", "There is no guards at this gate, but you can see that "
     		    +"they have put up a strong lock on the gate. The gate is "
     		    +"made of wood and looks very strong.\n");
    
    add_item("marshes", "A bit difficult to see anything behind this tall gate?\n");
    
    add_item(({"hill","hills","road","path"}), "You are "+
    "standing near the top of the Bree-Hill, though this is the "+
    "northwest corner, the main hill is southeast of here, you can "+
    "even take the road there.\n");
    
    add_item(({"bushes","bush","shrubs"}), "The shrubbery around here is "+
    "quite dense and overgrown. Upon closer examination, however, you "+
    "think you see an opening in one of the bigger bushes.\n");

    add_item(({"opening"}),"You might be able to enter the opening.\n");

    add_exit(BREE_DIR + "nroad1","south",0,2);

    add_call("enter", "[into] [the] 'opening' / 'bushes' / 'bush'", "do_enter2"); 

/*  I used add_call here because its a thing i know works, and due to the 
    error which was here with that you could only write enter to go into the 
    bushes, i think it was best to do so. It is quite easy to use.:
            
    add_call("enter", "[into] [the] 'opening' ", "do_enter2");

    enter: The command to do the act.
    into : Alternative command, 'enter into opening'.
    the  : Also an alternative command to use, 'enter into the opening' or 'enter the opening'.
    opening : Where to enter.
    
    You can also write: 'enter opening' but now you have more options on how to write it, 
    and i think its a good thing to have.

    So, you can write: 
    
    enter opening,
    enter into opening,
    enter the opening,
    enter into the opening
    
    to enter a certain place, nice and easy if you ask me :)
    
    Hope this helps a bit in explaining how to use the syntax.
    
    add_call("command", "[alt command] [more alt commands] [thousand_alternative_commands_can_be_added] 
    'where_to_enter' / 'another_word_for_where_to_enter' / 'several_options_for_where_to_enter'", 
    "function_to_call");
    
    -Sir Odin, 20.5.94
*/

}

/*
void
init()
{
     ::init();
    add_action("do_enter","enter");
}

int
do_enter(string str)
{
    if (str = "opening")
      { 
     write("You enter the opening in the bushes.\n");
    say(QCTNAME(TP) + " enters the bushes.\n");
     TP->move_living("M","/d/Shire/common/bree/path1",1);
     return 1;
    }

   else
   NF("Enter what?\n");
   return 0;
}
*/

int 
do_enter2(string arg)
{
    if(arg)
    {
    	write("You enter the opening in the bushes\n");
    	say(QCTNAME(TP) + " enters an opening in the bushes.\n");
    	TP->move_living("M","/d/Shire/common/bree/path1",1);
        tell_room("/d/Shire/common/bree/path1", QCTNAME(TP)+" arrives "+
        "from the bushes.\n",TP);
    	return 1;
    }
    else
    notify_fail("Enter what?\n");
    return 0;
}
     

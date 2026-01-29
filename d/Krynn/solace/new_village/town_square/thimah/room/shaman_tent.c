/* 
*Thimah's Tent
*Created by Leia
*3/28/2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

#include "/d/Ansalon/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <cmdparse.h>

inherit SHBASE;

object human;
string str;
object potion;

void
make_thimah()
{
    if(!human)
        {
            human = clone_object(SHAMAN);
            human->move(TO);
        }
}

void
reset_shaman_room()
{
    make_thimah();
}

create_shaman_room()
{
    add_exit(SOUTHTENT, "south");
    set_short("A Shaman's Tent");
    set_long("You have entered a shaman's tent. In the center of the floor is a fire that has been built as part of a ritual. Above the fire, is a stone slab. Your guess is that the stone is used to create steam by pouring water onto it. Not much else is found inside the tent, aside from a few voodoo dolls in the back.\n");
	add_item(({"fire"}), "The fire is quite warm, and glows with an unearthly red color. Looking at it more closely you are sure the shaman has put some sort of a hex upon it.\n");
	add_item(({"stone", "stone slab", "slab"}), "The stone slab is cracked in the center and charred a deep black color. It is supported by two large rocks the shaman probably found in a field somewhere.\n");
	add_item(({"rocks", "rock"}), "The rocks are ordinary, yet large, rocks that could be found in any of numerous fields.\n");
	add_item(({"dolls", "doll", "voo doo dolls"}), "There are several of these dolls scattered about the back of the tent. Each of them has several needles protruding from painful looking spots of the body. You're thankful none of the dolls look like you.\n");
    add_item(({"tent"}), "The tent is circular in shape and supported by long sticks. A hole in the ceiling lets the steam escape from inside. The tent itself seems to be made from leather of some sort.\n");
	add_item(({"bucket", "pail"}), "The bucket is filled approximately halfway with water. There is a ladle hanging from the side down into the water.\n");
	add_item(({"ladle", "spoon"}), "The ladle is nothing more than a simple wooden dipping spoon for spooning the water onto the hot rock.\n");
    reset_shaman_room();
}

void
prepare_potion(object player, int stage)
{
    float time;
    
    set_this_player(player);
    switch(stage)
    {
        case 1:
            if(human)
            {
                human->command("emote pulls a small wooden bowl from somewhere in the back of the tent.\n");
                time = 3.5;
            }
            break;
        case 2:
            if(human)
            {
                human->command("emote grinds some herbs together to form a fine powder.\n");
                time = 3.5;
            }
            break;
        case 3:
            if(human)
            {            
                human->command("emote reaches into a pouch, pulling something from it and adding it to the powder.\n");
                time = 3.5;
            }
            break;
        case 4:
            if(human)
            {            
                human->command("emote adds a leaf to the bowl and continues grinding the ingredients together.\n");
                time = 3.5;
            }
            break;
        case 5:
            if(human)
            {
                human->command("emote adds some water to the bowl and stirs the mixture into a potion.\n");
                time = 3.5;
            }
            break;
        case 6:
            if(human)
            {             
                human->command("say Here, quickly now, get this to the well and pour it into the fountain before anymore drink of that filth.\n");
                time = 3.5;
            } 
            break;
        default:
            if(human)
            {             
                write("The shaman hands you a potion of cleansing.\n");
                say("The shaman hands " +QTNAME(TP)+ " a potion of some sorts.\n");
                if(!present(P_NAME, this_player()))
                {
                    potion = clone_object(POTION);
                    potion->move(player);
                }
        
                else
                    write("You already have a potion of cleansing.\n");
            }
        return;
    }
    
    set_alarm(time, 0.0, &prepare_potion(player, ++stage));
}            

int
check_props()
{
    if(TP->query_prop(OFF_LEAF) & TP->query_prop(OFF_WATER) & TP->query_prop(OFF_ANG) & TP->query_prop(OFF_FIR) & TP->query_prop(OFF_SAS))
    {
        human->command("say I will now prepare the potion of cleansing for you.\n");
        set_alarm(5.0,0.0, &prepare_potion(TP, 1));
        return 1;
     }
     
     else
         return 1;
}

void
init()
{
    ::init();
    add_action("determine_item", "offer");
}

int
determine_item(string str)
{
    int s;
    mixed * item;
    str = lower_case(str);
    
    if(!present("thimah", this_object()))
    {
        write("Who do you suppose you would offer it to?\n");
        return 1;
    }
    
    if(TP->test_bit("krynn", GROUP, G_BIT))
    {
        write("The shaman does not accept your offering because you have already completed this task for him.\n");
        return 1;
    }
    
    if(TP->test_bit("krynn", GROUP, E_BIT))
    {
        human->command("say Get out of here! You help those who wish to harm the life of innocent creatures!\n");
        return 1;
    }

    if(!strlen(str))
    {
        write("Offer what?\n");
        return 1;
    }
    
    if(!parse_command(str, all_inventory(this_player()), "[the] %i", item))
    {
        write("Offer what?\n");
        return 1;
    }
    
    item = NORMAL_ACCESS(item, 0, 0);
    s = sizeof(item);
    
    if (s > 1)
    {
	    write("You can only offer one ingredient at a time.\n");
	    return 1;
    }

    if (!s)
    {
	    write("Offer what?\n");
	    return 1;
    }

    if(item[0]->query_name() == VL_NAME)
    {
        if(TP->query_prop(OFF_LEAF))
        {
            write("You have already supplied the leaf.\n");
            return 1;
        }
        
        else
        {
            human->command("say Thank you, earth child."); 
            item[0]->remove_object();
            TP->add_prop(OFF_LEAF, 1);
            check_props();
            return 1;
        }
    }
    
    if(item[0]->query_name() == W_NAME)
    {
        if(TP->query_prop(OFF_WATER))
        {
            write("You have already supplied the water.\n");
            return 1;
        }
        
        else
        {
            human->command("say Thank you, earth child.");
            item[0]->remove_object();
            TP->add_prop(OFF_WATER, 1);
            check_props();
            return 1;
        }
    }
    
    if(item[0]->query_herb_name() == "angeltear")
    {
        if(TP->query_prop(OFF_ANG))
        {
            write("You have already supplied the angeltear.\n");
            return 1;
        }
        
        else
        {
            human->command("say Thank you, earth child.");
            item[0]->remove_object();
            TP->add_prop(OFF_ANG, 1);
            check_props();
            return 1;
        }
    }
    
    if(item[0]->query_herb_name() == "fireweed")
    {
        if(TP->query_prop(OFF_FIR))
        {
            write("You have already supplied the fireweed.\n");
            return 1;
        }
        
        else
        {
            human->command("say Thank you, earth child.");
            item[0]->remove_object();
            TP->add_prop(OFF_FIR, 1);
            check_props();
            return 1;
        }
    }
    
    if(item[0]->query_herb_name() == "saskatoon")
    {
        if(TP->query_prop(OFF_SAS))
        {
            write("You have already supplied the saskatoon.\n");
            return 1;
        }
        
        else
        {
            human->command("say Thank you, earth child.");
            item[0]->remove_object();
            TP->add_prop(OFF_SAS, 1);
            check_props();
            return 1;
        }
    }
    
    else
    {
        write("Sorry, but that is not one of the required ingredients.\n");
        return 1;
    }
}
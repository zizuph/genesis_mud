/*
magic_stone.c

A magic stone, created for the Highbulp, who doesn't know how to use it!

It can be used in two different ways:
- rub stone, to cast light or to turn it off again
- smash stone [into ground], to create a flash, blinding everyone except 
the thrower for a short period of time

Created by Arcturus
16.05.2005

*/

#include "/sys/macros.h"  
#include "/sys/stdproperties.h"   /* We want to use standard properties */
#include "/d/Ansalon/common/defs.h"
#include "/sys/ss_types.h"
#include "/d/Ansalon/kalaman/sewers/local.h"
#include <filter_funs.h>

inherit "/std/object";

int light;

int limit;

void
create_object()
{
    set_name("stone");
    set_adj("small");
    add_adj("shiny");
    set_short("small shiny stone");
    set_pshort("small shiny stone");
    
    set_long("@@stone_desc");
    
    add_prop(OBJ_M_NO_SELL, "The shopkeeper doesn't intend to buy a stone. ");
    add_prop(OBJ_I_VALUE, 4000);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 40);

    add_prop(MAGIC_AM_MAGIC, ({25, "enchantment"}));
    
    add_prop(MAGIC_AM_ID_INFO, ({"It seems this stone was enchanted by " + 
        "a black robed mage.\n", 10, "The stone seems to shed some light " + 
        "when it is rubbed.\n", 25, "If the stone is smashed " + 
        "against the floor, it produced a bright flash, which " + 
        "will blind all but the one who threw the stone.\n", 35})); 

    seteuid(getuid(TO));
    
    light = 0;
    limit = 40 + random(30);
        
}

void
init()
{
    add_action("rub_stone", "rub");
    add_action("smash_stone", "smash");
}

int
rub_stone(string str)
{
    if (str != "stone") 
    {
        notify_fail("Rub what?\n"); 
        return 0;
    }
    if(TP->query_skill(SS_APPR_OBJ) < 25)
    {
        notify_fail("Rub what?\n"); 
        return 0;
    }
    
    limit--;
    
    if(!limit)
    {
        write("You rub the stone, but it crumbles to dust in your hand. \n");
        say(QCTNAME(TP)+ " rubs a small stone, but it crumbles to dust. \n");
        
        add_prop(OBJ_I_LIGHT, 0);
        remove_object();
        
        return 1;
    }
    
    if(light)
    {
        write("You rub the stone, and the light fades away.\n");
        say(QCTNAME(TP) + " rubs a small shiny stone, and the light fades away.\n"); 
        
        add_prop(OBJ_I_LIGHT, 0);
        light = 0;
        
        return 1;
    }
    else
    {
        write("You rub the stone, and suddenly a bright light appears from the stone, illuminating the area.\n");
        say("Suddenly a bright light appears from the stone of " + QTNAME(TP) + ", illuminating the area.\n"); 
        
        add_prop(OBJ_I_LIGHT, 1);
        light = 1;
        
        return 1;
    }
}


string
stone_desc()
{
    string temp = "The stone looks like an ordinary stone. ";
    
    if(TP->query_skill(SS_APPR_OBJ) > 25)
    {
        if(!light)
            temp += "Upon closer inspection you notice that the stone slowly absorbs light from its surroundings. ";
        else
            temp += "The stone sheds a bright light upon its surroundings. ";
    }
    
    if(limit < 10)
    {
        if(TP->query_skill(SS_APPR_OBJ) > 25)
        {
            string slimit = "You notice several cracks in the stone. ";
            if(TP->query_skill(SS_APPR_OBJ) > 40 && limit < 5)
            {
                slimit += "The stone seems to fall apart pretty soon. ";
            }
            
            temp += slimit;
        }
    }
        
    temp += "\n";
    
    return temp;
}

int
smash_stone(string str)
{
    object *ob;
    
    if (str != "stone") 
    {
        notify_fail("Smash what?\n"); 
        return 0;
    }
    
    write("You smash the stone to pieces on the ground. \n" +
          "There is a very bright flash of light, blinding everyone except you!\n");
    say(QCTNAME(TP)+ " suddenly smashes the small stone to pieces on the ground. \n" +
          "There is a very bright flash blinding you!\n");
    
    
    //Blind em all :)
    
    ob = FILTER_LIVE(all_inventory(environment(TP))) - ({ TP });
    
    for(int i = 0; i < sizeof(ob); i++)
    {
        object flash;
        flash = clone_object(OBJECTS + "blind_obj");
        flash->set_time(20 + random(20));
        flash->move(ob[i]);
    }    
    
    remove_object();
    return 1;
}
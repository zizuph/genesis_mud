/*
 * Pot of honey
 * Based on the honeypot in Calia, originally coded by Zima 8/15/96
 * By Finwe September 2003
 */

inherit "std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
//#include "honey.h"

#define  MAX_HONEY_AMT 5
 
int      honey_amt=0;   
 

void set_honey_long();
void set_honey_amt(int amt);
void reset_honey();
int query_honey_amt();
//int do_eat(string str);

void create_object() 
{
    set_name("honeypot");
    add_name("honey");
    set_adj(({"earthen","crock"}));
    set_short("earthen crock of honey");
    set_honey_amt(MAX_HONEY_AMT); 
 
    add_item(({"crock","earthen crock of honey","crock of honey", "honey"}),
               "@@exa_honey");
    add_cmd_item(({"crock","crock of honey", "earthen crock of honey","honey"}),
                ({"smell","sniff"}), "@@smell_honey");
    add_cmd_item(({"crock","crock of honey", "earthen crock of honey","honey"}),
                "taste", "@@taste_honey");
 
//    add_prop(OBJ_I_WEIGHT, 200000);
}
 
void reset_honey()
{ 
    set_honey_amt(MAX_HONEY_AMT); 
}

int query_honey_amt() 
{ 
    return honey_amt;
}
 

void set_honey_amt(int amt)
{
    if ((amt<0)||(amt>MAX_HONEY_AMT)) 
        honey_amt=0; 
    else 
        honey_amt=amt;
   set_honey_long();
}
 

void set_honey_long() 
{
    string desc;

    switch (honey_amt) 
    {
        case 5:
            desc="It is full of sweet, golden honey.\n";
            break;
        case 4:
            desc="It is almost full of sweet golden honey.\n";            
            break;
        case 3:
            desc="It is half full sweet golden honey.\n";             
            break;
        case 2:
            desc="It has a little bit of sweet golden honey left in the crock.\n";             
            break;              
        case 1:  
            desc="It is almost empty, only a bit of cold honey remains.\n";
            break;
        default: 
        desc="It is empty, only a coating of honey on the inside.\n";
    }
    desc="It is a large earth crock, used to hold honey. "+desc;
    this_object()->set_long(desc);
}
 
string exa_honey() 
{
   if (honey_amt>0)
      return("It is thick, golden honey. It is made from the nectar " +
      "of flowers by thousands of honeybees. The honey is a sweet " +
      "treat for anyone lucky enough to enjoy it. It looks like you " +
      "can stick your finger in and eat it if there is any left.\n");
   else
      return ("There is no honey left in the pot, only a thin coating "+
              "of its former contents.\n");
}
 

int do_eat(string str) 
//int do_eat(string Parms) 
{
//   object TP=this_player();
   object Tr=environment(TP);
//   object spoon=present("spoon",TP);
   object honey_obj;
//   string *Parm;
 
// must specify honey in pot 
//    if (!(Parms)) return 0;
    if (str !="finger in honey")
    {
        notify_fail("Eat what?\n");
        return 0;
    }
/*
    Parm=explode(Parms," ");
    if ((member_array("honey",Parm)==-1) ||
        ((member_array("pot",Parm)==-1)&&(member_array("honeypot",Parm)==-1)))
        return 0;
*/ 
// must be honey in pot and must have any spoon 
   if (!honey_amt)
   { 
        write("There is no honey left in the pot!\n"); 
        return 1; 
   }
 
// have player eat spoonful of honey 
   if (TP->eat_food(100)) 
   {
      write("You eat some of the honey from the pot.\n");
      tell_room(Tr,QCTNAME(TP)+" eats some honey from the pot.\n",TP);
      TP->add_hp(10+random(10));
      write("You feel nourished by the golden, sweet honey.\n");
      set_honey_amt((honey_amt-1));
   }
    else 
    { //  unable to eat food...too full maybe? 
      write("You try to eat some honey from the pot, but you are too full.\n");
    }
 
   return 1;
}

init()
{
    ::init();
//    add_action("do_eat",   "eat");
    add_action ("do_eat", "stick");
//    add_action("do_taste", "taste");
}

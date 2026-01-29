inherit "/std/monster";                                                         
                                                                                
#include "/d/Shire/common/defs.h"                                               
#include <ss_types.h>                                                           
#include <stdproperties.h>                                                      
/*
 * Removed by Elessar, to avoid the redeclaration problem after the GD change.
 * Jan 19th, 1995.
#include "/d/Shire/prestige.h"                                                  
*/
#include "/d/Shire/common/monster/tobacco.h"                                    
#include "/d/Shire/common/make_money.h"                                         
                                                                                
#define races ({"human","gnome","elf","dwarf","orc","troll","goblin","hobbit"}) 
#define STORROOM MICH_DIR +"storroom"                                           
                                                                                
//   Prototypes
void return_introduce(string who);

create_monster()                                                               
{                                                                               
 if (!IS_CLONE) return;                                                         
                                                                                
 set_name("overhill");                                                          
 add_name("butcher");                                                           
 set_race_name("hobbit");                                                       
 set_short("red-faced massive hobbit");                                         
 set_long("This is a very fat, massive hobbit with quite strong arms and \n" +  
    "plain red face. His is a local butcher. He is a professional and \n" +     
    "able to cut a cow flesh into pieces in a very few minutes. Great guy!\n"); 
 set_adj(({"red-faced","massive"}));                                            
 add_prop(CONT_I_WEIGHT,7000);                                                  
 add_prop(CONT_I_HEIGHT,450);                                                   
 set_stats(({75,45,45,33,33,33}));                                              
                                                                                
 set_title("the butcher of Michel Delving");                                    
 set_skill(SS_AWARENESS,50);                                                    
 set_skill(SS_DEFENCE,50);                                                      
 set_skill(SS_WEP_AXE,90);                                                      
                                                                                
 clone_tobacco();                                                               
 set_alignment(random(50));                                                     
 remove_prop(NPC_M_NO_ACCEPT_GIVE,0);                                           
                                                                                
 set_chat_time(60);                                                             
 add_chat("I am hounestly earning my money.");                                  
 add_chat("Last day was really hot!");                                          
 add_chat("My prices are the lowest in the Westfarthing!");                     
 add_chat("I work fast.");                                                      
 add_chat("I hate gnats. How about you?");                                      
                                                                                
 set_act_time(50);                                                              
 add_act("smile fri");                                                          
 add_act("emote cuts off another flesh part.");                                 
 add_act("emote murmurs another merry song.");                                  
 add_act("emote tears off a fine piece of muttons liver.");                     
 add_act("emote waves with his hand at another fly.");                          
                                                                                
 set_cchat_time(10);                                                            
 add_cchat("You have to get yourself to flee, my friend.");                     
 add_cchat("I hope my axe hurts you!");                                         
                                                                                
 trig_new("%w 'introduces' %s","react_introduce");                              
 set_alarm(1.0,0.0,"equip_me");                                                 
                                                                                
}                                                                               
equip_me()                                                                      
{                                                                               
    object axe,tunic;                                                           
    tunic = clone_object(MICH_DIR + "arm/h_robe");                              
    tunic->move(TO);                                                            
    command("wear all");                                                        
    command("emote checks the blade of his axe");                               
    axe = clone_object(MICH_DIR + "wep/b_axe");                                 
    axe->move(TO);                                                              
    command("wield all");                                                       
}                                                                               
int                                                                             
react_introduce(string who, string dummy)                                       
{                                                                               
    if (who)                                                                    
    {                                                                           
        who = lower_case(who);                                                  
        set_alarm(3.0,0.0,&return_introduce(who));
        return 1;                                                               
    }                                                                           
}                                                                               
                                                                                
void                                                                            
return_introduce(string who)                                                    
{                                                                               
    object obj;                                                                 
    if (obj = present(who,environment()))                                       
    {                                                                           
            command("eyebrow" + who);                                           
            command("cheer");                                                   
            command("say Nice to meet you " + capitalize(who) + ".");           
            command("say We here adore introducing!");                          
            command("introduce me");                                            
            command("emote smiles widely.");                                    
    }                                                                           
}                                                                               
                                                                                
                                                                                
public void                                                                     
enter_inv(object obj, object from)                                              
{                                                                               
  ::enter_inv(obj, from);                                                       
  if (!living(from))                                                            
  {                                                                             
   return;                                                                      
  }                                                                             
  if (obj->query_name()=="corpse")                                              
    {                                                                           
    set_alarm(1.0,0.0,"appraising",obj,from);}                                  
    else                                                                        
    {                                                                           
      command("say I don't need this.");                                        
      command("drop " + obj->query_short());                                    
      return;                                                                   
    }                                                                           
}                                                                               
void appraising(object obj,object from)                                         
{                                                                               
  int i;                                                                        
  command("emote looks closer at the corpse, studying it carefully.");          
  if (member_array(obj->query_race(), races) == 1)                              
     {                                                                          
      command("emote peers angrily at you!");                                   
      command("say This is " + obj->query_race() +"s corpse!");                 
      command("drop corpse");                                                   
      command("say I would call militia next time you do this.");               
      return;                                                                   
     }                                                                          
  set_alarm(2.0,0.0,"cook",obj,from);                                           
}                                                                               
void cook(object obj, object from)                                              
{                                                                               
  int price;                                                                    
  price = (obj->query_prop(CONT_I_WEIGHT)/100+from->query_skill(111)/10);       
  command("say Fine! I think I can make a nice stew from this meat.");          
  command("say But you definetly are to be rewarded....");                      
  command("emote licks his lips greedily.");                                    
  command("say ...with "+ price + " coppers.");                                 
  make_copper(price);                                                           
  command("give coins to "+from->query_real_name());                            
  set_alarm(2.0,0.0,"cook0",obj,price);                                         
  command("emote starts tearing off the guttons from the "+                     
     obj->query_race() +"s corpse.");                                           
  return;                                                                       
}                                                                               
void cook0(object obj, int price)                                               
{                                                                               
  int amount,k;                                                                 
   amount = obj->query_prop(CONT_I_WEIGHT) / 2;
  if (amount>1000)                                                              
  {                                                                             
     price = 5 + ( amount * amount) / 600;  /* man values */                    
    k = amount / obj->query_prop(OBJ_I_VOLUME);                                 
     if (k>10) k=10;                                                            
    set_alarm(5.0,0.0, "make_stew", amount, price, obj);                        
  }                                                                             
  else { set_alarm(0.1,0.0,"make_stew",amount,price,obj);}                      
  command("emote gives the meat to his wife.");                                 
}                                                                               
void make_stew(int amount,int price,object obj)                                 
{ object stew;                                                                  
                                                                                
  stew = clone_object("/std/food");                                             
  stew->set_name(obj->query_race()+" meat");                                    
   stew->add_name(({"meat","smoked meat"}));
  stew->set_pname("meats");                                                     
  stew->set_short("piece of smoked "+ obj->query_race()+" meat");               
  stew->set_pshort("pieces of smoked "+ obj->query_race()+" meat");             
  stew->set_adj(({"smoked","juicy"}));                                          
  stew->set_long("This is a juicy piece of smoked "+                            
  obj->query_race() +"s meat.\n");                                              
  stew->set_amount(amount);                                                     
  stew->add_prop(OBJ_I_WEIGHT,amount);                                          
  stew->add_prop(OBJ_I_VOLUME,amount);                                          
  stew->add_prop(OBJ_I_VALUE,price);                                            
  stew->add_prop(HEAP_S_UNIQUE_ID,obj->query_race()+" meat");                   
                                                                                
  stew->move(STORROOM);                                                         
}                                                                               
query_knight_prestige() { return(-2); }                                         

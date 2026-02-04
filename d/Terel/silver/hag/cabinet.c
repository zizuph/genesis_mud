inherit "/std/container";
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"


int open_cabinet(string str);
int close_cabinet(string str);
int unlock_cabinet(string str);
int lock_cabinet(string str);


object toad;
object key;

void
create_container()
{
 
    seteuid(getuid(TO));
    
        set_name("cabinet");
        add_name("ragata:cabinet");
        set_short("sturdy wooden cabinet");
        add_adj("sturdy");
        add_adj("wooden");
        add_adj("wood");
        set_long("@@long_desc");
       // description is in the room long description
        set_no_show_composite(1);
        
        add_item(("keyhole"),"You look through " +
           "the keyhole to see what is inside the cabinet " +
           "and realize that something is staring back at you.\n");
 
        add_prop(CONT_I_RIGID,1);
        add_prop(CONT_I_MAX_WEIGHT,28000);
        add_prop(CONT_I_WEIGHT,26000);
        add_prop(CONT_I_MAX_VOLUME,25000);
        add_prop(CONT_I_VOLUME,9000);
        add_prop(OBJ_I_VALUE,0);
        add_prop(CONT_I_LOCK,1);
        add_prop(CONT_I_CLOSED,1);
        add_prop(OBJ_M_NO_GET,1);
       
        reset_container();    

}
 
void
reset_container()
{
  add_prop(CONT_I_LOCK,0);
  add_prop(CONT_I_CLOSED,0);
  if(!present("ragata:toad",TO))
  {
     toad=clone_object(HAG + "toad");
     toad->move(TO);
  }
  add_prop(CONT_I_CLOSED,1);
  add_prop(CONT_I_LOCK,1);
}

void
init()
{
    ::init();
    add_action(open_cabinet,"open");
    add_action(close_cabinet,"close");
    add_action(unlock_cabinet,"unlock");
    add_action(lock_cabinet,"lock");
}

int
open_cabinet(string str)
{
   if((str == "cabinet")) 
     {
      if(query_prop(CONT_I_LOCK) == 1)
      {
       write("You'll need to unlock the cabinet " +
       "to open it.\n");
       return 1;
      }
       if(query_prop(CONT_I_CLOSED) == 1)
        {
      
         write("You open the cabinet.\n");
         say(QCTNAME(TP) + " opens the cabinet.\n");
         add_prop(CONT_I_CLOSED,0);
           if(present("ragata:toad",TO))
           {
               toad->move(HAG + "hovel");
               write ("A slimy toad hops from the cabinet to the " +
                     "floor before you.\n");
               say("A slimy toad hops from the cabinet to the floor.\n", HAG + "hovel"); 
            }
            return 1;
         }
         else
         {
           write("The cabinet is already open.\n");
          }
         return 1;
        }
     else
     { 
      notify_fail("Open what?\n");
      return 0;
      }
      
}

int
lock_cabinet(string str)
{
   if((str == "cabinet"))

     {
      if(query_prop(CONT_I_CLOSED) == 0)
        {
         write("You'll need to close the cabinet before " +
         "you can lock it.\n");
         return 1;
         }
      if(query_prop(CONT_I_LOCK) == 0)
       {
        if(present("ragata:cabinet_key",TP))
        {
         write("You lock the cabinet.\n");
         say(QCTNAME(TP) + " locks the cabinet.\n");
         add_prop(CONT_I_LOCK,1);
         return 1;
         }
         write("You'll need the proper key to lock the " +
         "cabinet.\n");
         return 1;
        }
       else
       {
       write("The cabinet is already locked.\n");
       return 1;
       }
      }
     else
     { 
      notify_fail("Lock what?\n");
      return 0;
  }      
}

int
unlock_cabinet(string str)
{
   if((str == "cabinet")) 
     {
      if(query_prop(CONT_I_CLOSED) == 0)
        {
         write("The cabinet is open already.\n");
         return 1;
         }
      if(query_prop(CONT_I_LOCK) == 1)
       {
        if (TP->query_wiz_level())     
        {
           add_prop(CONT_I_LOCK,0);
           write("Using your wizardly powers you magically unlock " +
                 "the cabinet without a key!\n");
           return 1;
        }
        if(present("ragata:cabinet_key",TP))
        {
         key=present("ragata:cabinet_key",TP);
         write("You unlock the cabinet.\n");
         write("The " + key->short() + " breaks as the " +
         "cabinet is unlocked.\n");
         key->remove_object();
         say(QCTNAME(TP) + " unlocks the cabinet.\n");
         add_prop(CONT_I_LOCK,0);
         return 1;
        }
         write("You'll need the proper key to unlock the " +
         "cabinet.\n");
         return 1;
        }
       else
       {
       write("The cabinet is already unlocked.\n");
       return 1;
       }
      }
     else
     { 
      notify_fail("Unlock what?\n");
      return 0;
  }      
}


int
close_cabinet(string str)
{
   if((str == "cabinet"))
     {
      if(query_prop(CONT_I_CLOSED) == 1)
       {
        write("The cabinet is already " +
        "closed.\n");
       }
      else
       {
         add_prop(CONT_I_CLOSED,1);
         write("You close the cabinet.\n");
         say(QCTNAME(TP) + " closes the cabinet.\n");
        }
       return 1;
       }
     else
     {  
      notify_fail("Close what?\n");
      return 0;
      }
}

string
long_desc()
{
  if(query_prop_setting(CONT_I_CLOSED) == 1)
    {
         return "The closed wooden cabinet looks well made.\n";
    }
    else
     {
         return "The wooden cabinet is open.\n ";
      }
}
 

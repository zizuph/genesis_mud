inherit "/std/container";
#include "/d/Terel/include/Terel.h"

int open_chest(string str);
int close_chest(string str);
int unlock_chest(string str);
int lock_chest(string str);


object slingshot;
object key;
object pebble;

void
create_container()
{
 
    seteuid(getuid(TO));
    
        set_name("chest");
        add_name("tomas:chest");
        set_short("decorated chest");
        add_adj("decorated");
        add_adj("wooden");
        add_adj("wood");
        set_long("@@long_desc");
        
        add_item(("keyhole"),"You look through " +
           "the keyhole to see what is inside the chest. " +
           "All you see is darkness; you'll need to open " +
           "the chest to see what it holds.\n");
 
        add_prop(CONT_I_RIGID,1);
        add_prop(CONT_I_MAX_WEIGHT,250000);
        add_prop(CONT_I_WEIGHT,4000);
        add_prop(CONT_I_MAX_VOLUME,25000);
        add_prop(CONT_I_VOLUME,4000);
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
  if(!present("tomas:slingshot" || "tomas:pebble"),TO)
  {
  slingshot=clone_object(CALATHIN_DIR + "/houses/obj/slingshot");
     slingshot->move(TO);
  pebble=clone_object(CALATHIN_DIR + "/houses/obj/pebble");
     pebble->move(TO);

  }
  add_prop(CONT_I_CLOSED,1);
  add_prop(CONT_I_LOCK,1);
}

void
init()
{
    ::init();
    add_action(open_chest,"open");
    add_action(close_chest,"close");
    add_action(unlock_chest,"unlock");
    add_action(lock_chest,"lock");
}

int
open_chest(string str)
{
   if((str == "chest") || (str == "decorated chest")) 
     {
      if(query_prop(CONT_I_LOCK) == 1)
      {
       write("You'll need to unlock the chest " +
       "to open it.\n");
       return 1;
      }
       if(query_prop(CONT_I_CLOSED) == 1)
        {
         write("You open the chest.\n");
         say(QCTNAME(TP) + " opens the chest.\n");
         add_prop(CONT_I_CLOSED,0);
         }
         else
         {
           write("The chest is already open.\n");
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
lock_chest(string str)
{
   if((str == "chest") || (str == "decorated chest"))

     {
      if(query_prop(CONT_I_CLOSED) == 0)
        {
         write("You'll need to close the chest before " +
         "you can lock it.\n");
         return 1;
         }
      if(query_prop(CONT_I_LOCK) == 0)
       {
        if(present("tomas:chest_key",TP))
        {
         write("You lock the chest.\n");
         say(QCTNAME(TP) + " locks the chest.\n");
         add_prop(CONT_I_LOCK,1);
         return 1;
         }
         write("You'll need the proper key to lock the " +
         "chest.\n");
         return 1;
        }
       else
       {
       write("The chest is already locked.\n");
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
unlock_chest(string str)
{
   if((str == "chest") || (str == "decorated chest")) 
     {
      if(query_prop(CONT_I_CLOSED) == 0)
        {
         write("The chest is open already.\n");
         return 1;
         }
      if(query_prop(CONT_I_LOCK) == 1)
       {
        if(present("tomas:chest_key",TP))
        {
         key=present("tomas:chest_key",TP);
         write("You unlock the chest.\n");
         write("The " + key->short() + " breaks as the " +
         "chest is unlocked.\n");
         key->remove_object();
         say(QCTNAME(TP) + " unlocks the chest.\n");
         add_prop(CONT_I_LOCK,0);
         return 1;
        }
         write("You'll need the proper key to unlock the " +
         "chest.\n");
         return 1;
        }
       else
       {
       write("The chest is already unlocked.\n");
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
close_chest(string str)
{
   if((str == "chest") || (str == "decorated chest"))
     {
      if(query_prop(CONT_I_CLOSED) == 1)
       {
        write("The chest is already " +
        "closed.\n");
       }
      else
       {
         add_prop(CONT_I_CLOSED,1);
         write("You close the chest.\n");
         say(QCTNAME(TP) + " closes the chest.\n");
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
         return "The chest looks as if a child " +
            "went wild with a paintbrush on it.\n " +
            "The chest is closed.\n";
    }
    else
     {
         return "The chest looks as if a child " +
            "went wild with a paintbrush on it.\n " +
            "The chest is open.\n";
      }
}
 

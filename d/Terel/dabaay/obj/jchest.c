inherit "/std/container";
inherit "/lib/unique";
#include "/d/Terel/include/Terel.h"
#define GEM_DIR "/d/Genesis/gems/obj/"
#define ULOG DABAAY_DIR + "log/unlock_jchest"

int open_chest(string str);
int close_chest(string str);
int unlock_chest(string str);
int lock_chest(string str);
int remove_chest(mixed blah);
int empty_out(object ob);

string *rgems = ({"alexandrite","beryl_red","diamond","emerald","ruby"}),
       *mgems = ({"sapphire","jade","pearl","spinel_blue","aquamarine","bloodstone"}),
       *cgems = ({"moonstone","garnet","carnelian","amber","onyx","topaz"}),
       *cgems2 =({"chrysoprase","garnet","turquoise","coral","agate"});



object scythe;
object key;

void
create_container()
{
 
    seteuid(getuid(TO));
    
        set_name("chest");
        add_name("jenglea's chest");
        set_short("blackened-steel chest");
        add_adj("blackened");
        add_adj("blackened-steel");
        add_adj("steel");
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
//  clone_unique(DABAAY_DIR + "weapon/jstaff",5,GEM_DIR + rgems[random(sizeof(rgems))])->move(TO);
  clone_object(GEM_DIR + rgems[random(sizeof(rgems))])->move(TO);
  clone_object(GEM_DIR + mgems[random(sizeof(mgems))])->move(TO);
  clone_object(GEM_DIR + mgems[random(sizeof(mgems))])->move(TO);
  clone_object(GEM_DIR + cgems[random(sizeof(cgems))])->move(TO);
  clone_object(GEM_DIR + cgems[random(sizeof(cgems))])->move(TO);
  clone_object(GEM_DIR + cgems2[random(sizeof(cgems2))])->move(TO);
  clone_object(GEM_DIR + cgems2[random(sizeof(cgems2))])->move(TO);
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
empty_out(object ob)
{
    if (ob->move(ENV(TO)))
        return 0;
    else
        return 1;
}

int 
remove_chest(mixed blah)
{
   tell_room(ENV(TO), "The "+short()+
       " rapidly dissolves into nothing.\n",0);
   map(all_inventory(TO), empty_out);
   TO->remove_object();
}

int
open_chest(string str)
{
   if((str == "chest") || (str == "blackened-steel chest")) 
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
         set_alarm(30.0, -1.0, "remove_chest");
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
   if((str == "chest") || (str == "blackened-steel chest"))

     {
      if(query_prop(CONT_I_CLOSED) == 0)
        {
         write("You'll need to close the chest before " +
         "you can lock it.\n");
         return 1;
         }
      if(query_prop(CONT_I_LOCK) == 0)
       {
        if(present("jenglea's key",TP))
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
   if((str == "chest") || (str == "blackened-steel chest")) 
     {
      if(query_prop(CONT_I_CLOSED) == 0)
        {
         write("The chest is open already.\n");
         return 1;
         }
      if(query_prop(CONT_I_LOCK) == 1)
       {
        if(present("jenglea's key",TP))
        {
         key=present("jenglea's key",TP);
         write("You unlock the chest.\n");
         write("The " + key->short() + " breaks as the " +
         "chest is unlocked.\n");
         key->remove_object();
         say(QCTNAME(TP) + " unlocks the chest.\n");
         write_file(ULOG, TP->query_name()+" " + ctime(time()) + "\n");
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
   if((str == "chest") || (str == "blackened-steel chest"))
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
         return "A sturdy chest of a darkened steel.\n" +
            "The chest is closed.\n";
    }
    else
     {
         return "A sturdy chest of a darkened steel.\n" +
            "The chest is open.\n";
      }
}
 

//              Igneous' Snare Trap Shadow

//      Shadows objects so when they are picked up the person
//      Attempting to pick up the shadowed object becomes trapped
//      By the snare.  

//      Copyright  Chad Richardson  Oct 1996


#pragma save_binary

inherit "/std/shadow";

#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <tasks.h>

#define SNARE_OB "/d/Shire/trickster/obj/snare_ob"
#define QSW  query_shadow_who()

//  Prototypes
void remove_snare_shadow();
mixed my_no_get();
int disarm();

string *Trap_names;
string Rope_file, Trap_setter;
int Trap_qual = 0, Not_ready = 0;

void
set_trap_qual(int qual)
{
   Trap_qual = qual;
   return;
}

void
set_trap_setter(string name)
{
   Trap_setter = lower_case(name);
   return;
}

void
set_where_rope_from(string str)
{
   Rope_file = str;
}

public varargs string
short(object for_obj)
{
   string extra;
   int level;
   
   level = TP->query_skill(SS_AWARENESS) + TP->query_skill(SS_FR_TRAP);
   level = level - Trap_qual;
   
   switch (level)
   {
      case 10..45:
      extra = "";    // You won't notice anything unless you examine it 
      break;
      case 46..200:
      extra = "suspicous looking ";
      break;
      default:
      extra = "";
      break;
   }
   return extra + QSW->short(for_obj);
}

varargs public mixed
long(string str, object for_obj)
{
   string extra;
   int level;
   
   level = TP->query_skill(SS_AWARENESS) + TP->query_skill(SS_FR_TRAP);
   level = level - Trap_qual;
   
   switch (level)
   {
      case 10..45:
      extra = "There is something odd about the "+QSW->short()+".\n";
      break;
      case 46..200:
      extra = "This "+QSW->short()+" has been trapped!!!\n";
      break;
      default:
      extra = "";
      break;
   }
   return QSW->long(str,for_obj) + extra;
}

void
set_up_trap()
{
   int i;
   
   Trap_names = QSW->query_names();
   for (i = 0; i < sizeof(Trap_names); i++)
   {
      QSW->add_cmd_item(Trap_names[i],"disarm","@@disarm");
   }
   QSW->update_actions();
   QSW->add_prop(OBJ_M_NO_GET, my_no_get);
   return;
}

mixed
my_no_get()
{
   object trap;
   
   if (Not_ready)
      {
      Not_ready = 0;
      return;
   }
   if (TP->query_real_name() == Trap_setter)
      {
      return "Now why would you want to spring your trap after going "+
      "to all that trouble of setting it up?\n";
   }
   // Trap is sprung so the shadow is removed
   remove_snare_shadow();
   
   //    Now we trap the poor fellow *grin*
   setuid(); seteuid(getuid());
   trap = clone_object(SNARE_OB);
   trap->hang(TP);
   trap->move(ENV(TP));
   
   tell_room(ENV(QSW),QCTNAME(TP)+" is snared by a trap when "+HE_SHE(TP)+
      " picks up "+QSW->short()+" and is flung upside-down and hung from "+
      HIS_HER(TP)+" ankles!!\n",TP);
   TP->catch_msg("As you pick up the "+QSW->short()+" you notice it's been "+
      "trapped!!!  A rope wraps around your ankles and you are "+
      "suspended upside-down from your feet.\n");
   return 0;
}

void
remove_snare_shadow()
{
   int i;
   
   Not_ready = 1;
   QSW->remove_prop(OBJ_M_NO_GET);
   for (i = 0; i < sizeof(Trap_names); i++)
   {
      QSW->remove_cmd_item(Trap_names[i]);
   }
   QSW->update_actions();
   set_alarm(0.5,0.0,remove_shadow);
   return;
}

int
query_snare_shadow()
{
   return 666;
}

int
query_trap_quality()
{
   return Trap_qual;
}

string
query_trap_setter()
{
   return Trap_setter;
}

int
disarm()
{
   if (TP->query_real_name() == Trap_setter)
      {
      TP->catch_msg("You decide that you know a better place to set this "+
         "trap up so you quickly remove it.\n");
      if (Rope_file)
         {
         setuid(); seteuid(getuid());
         clone_object(Rope_file)->move(ENV(QSW));
       }
      tell_room(ENV(QSW), QCTNAME(TP) +" quickly removes the trap from "+
         "the "+ QSW->short() +", apparently not satisified with it's " +
         "present location.\n",TP);
      remove_snare_shadow();
      return 1;
   }
   
   if (TP->query_mana() < 20)
      {
      notify_fail("You are too mentally exhausted to do disarm "+
            "the "+QSW->short()+"!\n");
      return 0;
   }
   //  Causes us some mental strain to do this
   TP->add_mana(-10);
   if (TP->resolve_task(TASK_DIFFICULT, ({SS_FR_TRAP})) > 0)
   {
      TP->catch_msg("You managed to disarm the "+QSW->short()+"!\n");
      if (Rope_file)
         {
         setuid; seteuid(getuid());
         clone_object(Rope_file)->move(ENV(QSW));
       }
      tell_room(ENV(QSW), QCTNAME(TP) + " managed to disarm the "+
         QSW->short() + ".\n",TP);
      remove_snare_shadow();
      return 1;
   }
   notify_fail("You were unable to disarm the "+QSW->short()+".\n");
   return 0;
}

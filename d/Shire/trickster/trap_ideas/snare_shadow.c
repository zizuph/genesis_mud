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
#define SNARE_DISARM "/d/Shire/trickster/obj/snare_disarm"
#define QSW  shadow_who

//  Prototypes
void remove_snare_shadow();
mixed my_no_get();

string Rope_file, Trap_setter;
int Trap_qual = 0;
object disarm_ob;

int
query_trickster_shadow()
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

string
query_rope_file()
{
   return Rope_file;
}

void
set_trap_qual(int qual)
{
   Trap_qual = qual;
}

void
set_trap_setter(string name)
{
   Trap_setter = lower_case(name);
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
   level = level - Trap_qual / 20;
   
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
   level = level - Trap_qual / 20;
   
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

mixed
query_prop(string prop)
{
   if (prop == OBJ_M_NO_GET)
      return my_no_get();
   if (prop == HEAP_S_UNIQUE_ID)
      return QSW->query_prop(HEAP_S_UNIQUE_ID) + "_trapped";
   return QSW->query_prop(prop);
}

mixed
my_no_get()
{
   object trap;
   
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
set_up_trap()
{
   setuid(); seteuid(getuid());
   disarm_ob = clone_object(SNARE_DISARM);
   disarm_ob->set_disarm_object(TO,QSW);
   disarm_ob->move(ENV(QSW));
}

void
remove_snare_shadow()
{
   set_alarm(0.1,0.0,remove_shadow);
}

void
remove_shadow()
{
   if (disarm_ob)
      disarm_ob->remove_object();
   destruct();
}

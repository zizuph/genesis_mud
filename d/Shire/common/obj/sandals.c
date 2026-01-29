inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
#define tp   query_worn()

int alarm_id;

void
create_armour()
{
   set_name("sandals");
   set_short("pair of small sandals");
   set_long("These sandals are small, and probably only fit little folk, "+
   "like hobbits or gnomes.\n");
   add_adj(({"small","walking"}));
   
   set_ac(1);
   set_at(A_FEET);

   add_prop(OBJ_I_VALUE, 150);
   add_prop(OBJ_I_WEIGHT, 275);
   add_prop(OBJ_I_VOLUME, 500);


}

wear_me()
{
   alarm_id = set_alarm(1.0,60.0,"rest_player",tp);
   SAY(QCTNAME(tp)+ " wears the "+short()+".\n");
   tp->catch_msg("You strap your sandals on tightly.\n");
   return 1;
}

void
leave_env(object from, object to)
{
    ::leave_env();
    remove_alarm(alarm_id);
}

int
remove()
{
   remove_alarm(alarm_id);
   return 1;

}
int
rest_player()
{
   if(tp->query_race_name() == "hobbit") return 0;
   if(tp->query_race_name() == "gnome") return 0;
   if(tp->query_race_name() == "elf") return 1;
   if(tp->query_race_name() == "goblin") return 1;
   if(tp->query_race_name() == "dwarf") return 1;
   if(tp->query_race_name() == "human") return 1;
   if(!TO->query_broken())
     {
       tp->add_fatigue(27);
       tp->catch_msg("Adding 27 fatigue points.");
       return 1;
      }
     else
     return 0;

}

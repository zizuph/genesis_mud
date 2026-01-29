inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"

#define IDLE TP->query_idle_time()

int alarm_id, walking;

void
create_armour()
{
   set_name("sandals");
   set_pname("sandals");
   add_name(({"sandal","pair"}));
   set_short("pair of small walking sandals");
   set_pshort("pairs of small walking sandals");
   set_long("These sandals are made for walking, as evidenced by "+
   "their sturdy construction and high quality of materials. "+
   "They look like they will fit a dwarf perfectly.\n");
   add_adj(({"small","walking"}));
   
   walking = 0;
   set_ac(1);
   set_at(A_FEET);

   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_I_WEIGHT, 275);
   add_prop(OBJ_I_VOLUME, 500);


}

int
wear(object arm)
{
   alarm_id = set_alarm(1.0,1.0,"rest_player",TP);
   return 1;
}

void
leave_env(object from, object to)
{
    ::leave_env();
    remove_alarm(alarm_id);
}

public int
remove_armour(object arm)
{
   remove_alarm(alarm_id);
   return 1;

}
int
rest_player()
{


if(!IDLE > 30000)
{
   if(TP->query_race() == "dwarf")
   {
   if(!TO->query_broken())
     {
       TP->add_fatigue(10);
       TO->got_hit();
       return 1;
      }

    }
     TP->add_fatigue(-10); /* Walking in the wrong shoes */
     return 1;

}


}

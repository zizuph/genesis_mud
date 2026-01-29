inherit "/std/object";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void do_smell();
void remove_smell();


void
create_object()
{
   
   set_name("cowpie");
   add_name(({"dung","waste","pile","heap"}));
   set_short("large cowpie");
   add_adj(({"pile","smelly"}));
   
   set_long("This is a huge smelly cowpie. It smells horribly!\n");
   
   add_prop(OBJ_I_WEIGHT, 1400);
   add_prop(OBJ_I_VOLUME, 14000);
   add_prop(OBJ_I_VALUE, 0);
   
   set_alarm(15.0,25.0,"do_smell");
   set_alarm(600.0,0.0,&remove_smell());
   
}

void
do_smell()
{
   tell_room(ENV(TO), "A strong stench from the cowpie wafts " +
       "up to your nose. It smells awful!\n");
   
}

void
remove_smell()
{
   TO->remove_object();
   
}

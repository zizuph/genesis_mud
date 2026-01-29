// An object that blinds you
//   -Ilyian, Oct 1995

inherit "/std/object";
#include "../infidel.h";

void start_blind();
void stop_blind();

create_object()
{
   set_short("blind_obj");
   set_long("This object blinds you.");
   set_no_show(1);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_M_NO_DROP, 1);
   add_prop(OBJ_M_NO_SELL, 1);
}

void start_blind()
{
   int time;
   time = 300 - ENV(TO)->query_stat(4);
   if(time<0)
     time = 20;

   ENV(TO)->catch_tell("The light blinds you completely!\n");
   ENV(TO)->add_prop(LIVE_I_BLIND,
       ENV(TO)->query_prop(LIVE_I_BLIND) + 100);
   
   set_alarm(itof(time), 0.0, stop_blind);
}

void stop_blind()
{
   ENV(TO)->add_prop(LIVE_I_BLIND,
       ENV(TO)->query_prop(LIVE_I_BLIND) - 100);

   ENV(TO)->catch_tell("Your eyes clear up and you can see again.\n");
   remove_object();
}
   

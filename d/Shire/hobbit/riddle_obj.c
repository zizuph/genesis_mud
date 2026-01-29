#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "hobbit.h"
#include <macros.h>
#include <formulas.h>


void set_answer(string str);
void set_riddler(object ob);
int times_up();

string ans;
object riddler;
int alarm_id;


void
set_answer(string str)
{
   ans = str;
    return;

}

void
set_riddler(object ob)
{
   riddler = ob;
   return;

}

int
times_up()
{
   
  tell_room(ENV(TO),"Time has expired on the riddle posed by "+
   QCTNAME(riddler)+".  The answer was "+ans+".\n");
   remove_alarm(alarm_id);
   remove_object();
   return 1;
}



int
do_answer(string str)
{

   if(!present(riddler,environment(this_object())))
   {
     write("You can't answer a riddle when the riddler has left!\n");
     return 1;
   }

   if(!str)
   {
     write(capitalize(query_verb())+ " what?\n");
     return 1;
   }

   if(str != ans)
   {
     write("You answer "+str+" and that is incorrect.\n");
     say(QCTNAME(TP)+ " answers: "+str+", and "+
     QTNAME(riddler)+" shakes "+HIS_HER(riddler)+
     " head, as that answer is incorrect.\n", ({riddler,TP}));
    riddler->catch_msg(QCTNAME(TP)+ " answers: "+str+", and you "+
    "smile slightly, knowing that "+HE_SHE(TP)+" is incorrect.\n");

     return 1;
   }


     write("You answer "+str+" and that is correct.\n");
     say(QCTNAME(TP)+ " answers: "+str+", and "+
     QTNAME(riddler)+" nods "+HIS_HER(riddler)+
     " head slowly, acknowledging the correct answer.\n", ({riddler,TP}));
    riddler->catch_msg(QCTNAME(TP)+ " answers: "+str+", and you "+
    "have to acknowledge that "+HE_SHE(TP)+" is correct.\n");

   set_alarm(1.0,0.0,"remove_object");
   return 1;

}



void
create_object()
{

    set_short("riddle_obj");
    set_name("riddle_obj");
    add_name("_hob_riddle_obj_");
    set_long("You won't see this, I'm using set_no_show. :)");

   set_no_show();

   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
   add_prop(OBJ_M_NO_GET, 1);

   alarm_id =  set_alarm(180.0,0.0,"times_up");

}


void
init()
{
    ::init();
    add_action("do_answer","answer");
    add_action("do_answer","solution");

}


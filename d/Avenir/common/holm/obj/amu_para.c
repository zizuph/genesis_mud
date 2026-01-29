inherit "/std/paralyze";
#include "/d/Avenir/common/common.h";

int mess_type;

create_paralyze()
{
    ::create_paralyze();
    set_name("");
    set_long("");
    add_prop(OBJ_I_NO_DROP,"Drop what.\n");
    set_stop_verb("");
    set_fail_message("You can't do that.\n"); 
}

int stop(string str)
{

  if(query_verb()=="vitals"||query_verb()=="look"||
   query_verb()=="stats"||query_verb()=="date"||query_verb()=="scream"||
   query_verb()=="say"||query_verb()=="appraise"||
   query_verb()=="shout"||query_verb()=="examine"||query_verb()=="inventory")
       return 0;
   return ::stop();
}

set_message_type(int type)
{
    mess_type=type;
}



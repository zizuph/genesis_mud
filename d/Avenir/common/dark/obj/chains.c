// file name: ~Avenir/common/dark/obj/chains.c
// creator(s): Denis
// revision history:
// purpose: used by imps (~Avenir/common/dark/obj/imp.c) to hold enemies.
//          used not only as mentioned in long description but also
//          for holding in special attack.
//          (in fact player still cannot be locked in these chains :) )
// note:
// bug(s):
// to-do: change valid verbs checking to an array.

inherit "/std/paralyze";
#include "/d/Avenir/common/common.h";

int mess_type;

create_paralyze()
{
    ::create_paralyze();
    set_name("chains");
    set_long("You are securely attached by these chains to the wall.\n");    
    add_prop(OBJ_I_NO_DROP,"You cannot drop them they securely fasten you "+
             "to the wall.\n");
    set_stop_verb("");
    set_fail_message("You are securely locked in chains, you cannot do "+ 
                     "that.\n"); }

int stop(string str)
{
    if(query_verb()=="quit"||query_verb()=="vitals"||query_verb()=="look"||
      query_verb()=="stats"||query_verb()=="date"||query_verb()=="scream"||
      query_verb()=="say"||query_verb()=="help"||query_verb()=="appraise"||
      query_verb()=="shout"||query_verb()=="examine"||query_verb()==
      "inventory")
        return 0;
    return ::stop();
}

set_message_type(int type)
{
    mess_type=type;
}

set_remove_time(int time)
{
    set_alarm(itof(time),0.0,"remove_object");
}

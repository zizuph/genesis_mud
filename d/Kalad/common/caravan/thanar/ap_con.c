inherit "/std/object";
#include "/d/Kalad/defs.h"
#define THANAR_TALK "_thanar_talk"

/* Sarr */

object thanar;

void
set_thanar(object ob)
{
    thanar = ob;
}


void
create_object()
{
    set_name("controler");
    set_long("controler.");
    set_no_show();
    add_prop(OBJ_M_NO_DROP,1);
}

void
init()
{
    ::init();
    AA(do_speak,thsay);
}

int
do_speak(string str)
{
    NF("Make the "+thanar->short()+" say what?\n");
    if(!str)
	return 0;
    tell_room(E(thanar),"The "+thanar->short()+" thunders: "+str+"\n");

    /* added a log-file to see if they make the apparition talk
      nonsense or use it as intended - for roleplaying */
    log_file("apparition",TP->query_real_name()+" said   "+
      str+" at time: "+extract(ctime(time()),4,15)+".\n");
    return 1;
}


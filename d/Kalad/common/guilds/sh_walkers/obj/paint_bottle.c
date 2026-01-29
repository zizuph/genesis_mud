inherit "/std/object";
#include "/d/Kalad/defs.h"


int uses = 6;
int
check_uses()
{
    uses = uses -1;
    if(uses == 0)
    {
        write("You have used up all the paint, and discard the bottle.\n");
        return 1;
}
}

void
create_object()
{
    set_name("bottle");
    set_adj("red");
    add_adj("paint");
    set_short("red paint bottle");
    set_long("This is a small glass bottle filled with heavy, red "+
    "ink. It has a cap on it with a stick and brush to write with. "+
    "If you want, you can leave a message in the room with "+
    "'paintwrite <text>'.\n");
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,30);
}

void
init()
{
    ::init();
    AA(do_paint,paintwrite);
}

int
do_paint(string str)
{
    object mess;
    string smess;
    mess = present("_kalad_shadow_mess_",E(TP));
    if(mess)
    {
        write("You add to the old message here, your own message.\n");
        say(QCTNAME(TP)+" bends down and scribles something with some "+
        "red paint.\n");
        log_file("paint_messages",str+" by, "+TP->query_name()+"\n");
        smess = mess->query_message();
        mess->set_message(smess+"  ...Another message follows this one...\n"+
        str);
      if(check_uses())
          remove_object();
        return 1;
    }
    else
    {
        write("You bend down and write your message with the paint.\n");
        say(QCTNAME(TP)+" bends down and scribles something with some "+
        "red paint.\n");
        seteuid(getuid());
        log_file("paint_messages",str+" by, "+TP->query_name()+"\n");
        mess = clone_object("/d/Kalad/common/guilds/shadow_walkers/mess");
        mess->set_message(str);
        mess->move(E(TP));
        if(check_uses())
            remove_object();
        return 1;
    }
}


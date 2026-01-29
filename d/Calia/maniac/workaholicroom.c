
/* 
   Intensive work room.

   Coded by Maniac
*/

inherit "/std/room.c";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


void
advice1(object ob)
{
    if (ob->query_real_name() == "maniac") 
        ob->catch_msg("Remember to go busy clear, busy WPCL and invis.\n");  
}


void
advice2(object ob)
{
    if (ob->query_real_name() == "maniac") 
        ob->catch_msg("Remember to go busy clear and vis.\n");  
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 
 
    if (living(ob) && (ob->query_real_name() != "maniac")) { 
        ob->move(from); 
        ob->catch_msg("No admittance.\n"); 
    }

    set_alarm(1.0, 0.0, &advice1(ob)); 
}


void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to); 
     
    set_alarm(1.0, 0.0, &advice2(ob)); 
}



void
create_room()
{
    set_short("Maniac's intensive work room");

    set_long("This is Maniac's intensive work room. You shouldn't be here " +
             "if your name is not Maniac.\n");

    seteuid(getuid()); 

    add_prop(ROOM_I_INSIDE, 1);
}



inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

int alarm_h;

void create_object()
{
 setuid();
 seteuid(getuid());
 set_name("_trickster_smoke_object_");
 set_no_show_composite(1);
 add_prop(OBJ_I_NO_GET,"");
}

void clear_out()
{
 tell_room(ENV(TO),"The smoke finally dissapates, enabling you to see "+
   "your surroundings once again.\n");
 remove_object();
}

void explode()
{
 add_prop(OBJ_I_LIGHT,-9999);
 tell_room(ENV(TO),"With a loud hissing noise a cloud of dense smoke "+
   "fills the room, blocking out all light, making it impossible to "+
   "see!\n"+
   "Cover your mouth when you cough noisily!\n");
 set_alarm(10.0,0.0,&clear_out());
}


inherit "/std/object";
#include <stdproperties.h>
#include "/sys/macros.h"

#define TP this_player()

//   Prototypes
int bury_corpse(string str);

int alarm_id;
void
create_object()
{
   set_name("corpse");
   set_pname("corpses");
   set_long("They are dried remains of a humanoid species.\n");
   set_short("corpse");
   set_pshort("corpses");
   alarm_id = set_alarm(1.0,0.0,&bury_corpse());
}


void
init()
{
    ::init();

   add_action("bury_corpse","bury");
}

int
bury_corpse(string str) {
   remove_alarm(alarm_id);
    if (str == "corpse")
    {
    write("You dig in the ground and bury the corpse.\n");
    say(QCTNAME(TP) + " buries the corpse.\n");
     return 1;
    }
    return 0;
}


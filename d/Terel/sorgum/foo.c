#include "/d/Terel/include/Terel.h"
#include <filepath.h>
inherit "/std/object";

init()
{
  ::init();
    add_action("fekish", "fekish");
    add_action("wigwam", "wigwam");    
}

create_object()
{
  set_name("gizmo");
  set_short("gizmo");
  set_long("A strange gizmo.  By using the command 'fekish' you think " +
           "it might take you to Sorgum's workroom.  The 'wigwam'" + 
           "command probably takes you back.\n");
 add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);  
  add_prop(OBJ_I_NO_DROP, 1);
}
void
enter_env(object new, object old)
{
   ::enter_env(new, old);
     new->catch_msg("*** A strange gizmo enters your inventory!\n");
   return;
}
int
fekish(string str)
{
  TP->add_prop("_fekish", MASTER_OB(environment(TP)));
  TP->catch_msg("You feel yourself magically transferred.\n");
  TP->move_living("X", "/d/Terel/sorgum/workroom");
  return 1;
}

int
wigwam(string str)
{
  TP->catch_msg("You feel yourself magically transferred.\n");
  if (TP->query_prop("_fekish")) {
    TP->move_living("X", TP->query_prop("_fekish"));
  }
  else {
    TP->catch_msg("Opps there was a problem... you end up in your start " +
                  "location\n");
    TP->move_living("X", TP->query_default_start_location());
  }
  TP->catch_msg("The gizmo disintegrates.\n");
  set_alarm(1.0, -1.0, "blow_away");
  return 1;
}

blow_away()
{
  remove_object();
}

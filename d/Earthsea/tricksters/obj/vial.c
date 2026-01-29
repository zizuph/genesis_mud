inherit "/std/object";

#include <stdproperties.h>

#include "../defs.h"

void create_object()
{
 setuid();
 seteuid(getuid());
 set_name("_trickster_laughgas_vial_");
 set_no_show_composite(1);
 add_prop(OBJ_I_NO_GET,"");
}

void infest_all()
{
 object *all_here,laugh_obj;
 int i;

 all_here=ENV(TO)->subinventory();
 for(i=0;i<sizeof(all_here);i++)
  {
   laugh_obj=clone_object(TRICKSTERS+"obj/laughgas");
   laugh_obj->move(all_here[i]);
   laugh_obj->start();
  }
 remove_object();
}

void go_off()
{
 TR(TO,"The glass vial breaks on impact on the ground, releasing a "+
       "strange gas.\n");
 set_alarm(1.0,0.0,&infest_all());
}

void arm()
{
 set_alarm(1.0,0.0,&go_off());
}


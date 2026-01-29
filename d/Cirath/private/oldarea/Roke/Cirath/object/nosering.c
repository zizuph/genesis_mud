inherit "/std/object";

#include <macros.h>
#include "/d/Roke/common/defs.h"
#include <cmdparse.h>
#include <ss_types.h>
#include "/std/combat/combat.h"
#include <wa_types.h>
#include "/d/Roke/Cirath/defs.h"

int material;

query_auto_load()
{
  string name;
  int i;
  sscanf(file_name(this_object()),"%s#%d", name, i);
  return name+":"+material;
}

int
set_descs()
{
  material = query_prop("_ring_s_material");
  set_adj(material);
}

init_arg()
{
  material = query_prop("_ring_s_material");
  TP->add_subloc("nose_ring",TO);

}

public string 
show_subloc(string subloc, object me, object for_obj)
{
  string data;

  if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    return "";

  if(for_obj != me)
    data = capitalize(this_player()->query_pronoun()) + 
           " has a "+material+" ring in "+TP->query_possessive()+
           " nose.\n";
  else
    data = "You have your "+material+" ring in your nose.\n";

  return data;
}

create_object()
{
  set_short("nose-ring");
  set_name("ring");
  add_name("ciubori_ring");
  
  call_out("set_descs",1);
  
  set_long("This is a nose-ring.\n");

  add_prop(OBJ_M_NO_DROP,1);
  this_object()->set_no_show_composite(0);
}

init()
{
  ::init();
}

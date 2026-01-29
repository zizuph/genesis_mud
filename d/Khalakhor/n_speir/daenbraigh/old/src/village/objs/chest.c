/*
 * Goblin's elder chest.
 * Contains a scroll with confusion spell,
 * a skull from Sa Morgan
 * a sceptre from Port Macdunn
 *
 * TAPAKAH, 05/2005
 */

#pragma strict_types;

#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit "/std/receptacle";

string *contents;
void fill_chest();

void
create_receptacle()
{
  if(!IS_CLONE)
    return;
  ::create_receptacle();
  
  set_name("chest");
  add_name(V_OBJID + "chest");
  set_adj(({"sturdy","iron"}));

  set_short("sturdy iron chest");
  set_pshort("sturdy iron chests");
  set_long("The chest is made of iron and looks very sturdy. Two leather " +
	   "strips run along its lid. It doesn't have any other ornaments "+
	   "but an intricated lock. It seems very heavy.\n" );

  add_prop(CONT_I_WEIGHT,50000);
  add_prop(CONT_I_MAX_WEIGHT,65000);
  add_prop(CONT_I_VOLUME,10000);
  add_prop(CONT_I_MAX_VOLUME,30000);
  add_prop(CONT_I_RIGID,1);
  add_prop(CONT_I_CLOSED,0);
  add_prop(CONT_I_IN,1);
  add_prop(OBJ_I_VALUE,350);

  set_pick(40);
  add_item(({"strip","strips"}),
	   "The strips look to be the only ornament of the chest. "+
	   "They allow to carry it around easier.\n");
  add_item(({"lock"}),
	   "The lock looks very intricated and you only wonder what the "+
	   "key for it may look like.\n");

  contents = ({V_SCROLL,V_SKULL,V_SCEPTRE});
  setuid();
  seteuid(getuid());
  reset_receptacle();
  add_prop(CONT_I_LOCK,1);
  add_prop(CONT_I_CLOSED,1);
  set_key(V_KEY_VALUE);
}

int
elder_awake()
{
  object elder;
  
  return ENV(TO)
    && (elder = present(V_OBJID+"_elder",ENV(TO)))
    && (! elder->query_prop(V_IS_ASLEEP));
}

void
enter_inv(object obj, object from)
{
  if (living(obj)) {
    write("You cannot put that into the chest.\n");
    return;
  }
  if (elder_awake()) {
    write("The elder does not allow you to mess with the chest.\n");
    return 0;
  }
  ::enter_inv(obj,from);
}

void
leave_inv(object obj, object to)
{
  object elder;
  
  if (elder_awake()) {
    write("The elder does not allow you to mess with the chest.\n");
    return 0;
  }
  ::leave_inv(obj,to);
}

int
do_default_pick(string str)
{
  object elder;
  
  if (elder_awake()) {
    write("The elder does not allow you to mess with the chest.\n");
    return 0;
  }
  ::do_default_pick(str);
  return 1;
}

void
reset_receptacle()
{
  ::reset_receptacle();
  fill_chest();
}

void
init()
{
  ::init();
}

void
fill_chest()
{
  int i,j;
  
  j = sizeof(contents);
  for(i=0;i<j;i++) 
    if(! present(contents[i],TO))
      clone_object(contents[i])->move(TO);
}

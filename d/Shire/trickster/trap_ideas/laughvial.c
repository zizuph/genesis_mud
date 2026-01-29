//	Igneous' laughgas vial

//	Obtained when someone disarms a tripwire trap

//      Copyright  Chad Richardson  Oct 1996

inherit "/std/object.c";

#include "/d/Shire/common/defs.h"
#include "/d/Shire/trickster/trickster.h"

void
create_object()
{
   set_name("vial");
   set_short("glass vial of laughing gas");
   set_pshort("glass vials of laughing gas");
   set_long("A small glass vial filled with a strange brew of alchemical "+
      "magic which creates a gas which causes people to laugh "+
      "when they breathe it in.\n");
   add_adj(({"small","glass"}));
   add_name(({"laughgas","laughing gas","blub"}));
   
   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_WEIGHT, 15);
   add_prop(OBJ_I_VALUE, 25);
}

void
init()
{
   ::init();
   
   add_action("make_em_laugh","toss");
   add_action("make_em_laugh","throw");
   add_action("make_em_laugh","break");
}

int
make_em_laugh(string str)
{
   if (member_array(str, TO->query_names()) >= 0)
      {
      write("You throw the "+short()+" towards the ground!!\n");
      say(QCTNAME(TP)+" throws a "+short()+" towards the ground!\n");
      setuid(); seteuid(getuid());
      clone_object(LAUGH_OBJ)->move(ENV(TP),1);
      remove_object();
      return 1;
   }
   notify_fail(CAP(query_verb())+" what?\n");
   return 0;
}

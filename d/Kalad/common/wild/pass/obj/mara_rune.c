inherit "/std/object";
#include "/d/Kalad/defs.h"
/* The Mara Rune, it is the only thing that can slay the Desert
Marauder of the Kalad Desert */
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("rune");
   set_adj("mara");
   set_long("A piece of glaringly white silver that has been twisted "+
      "into the shape of an upside down 'v' with a curving line running "+
      "tangent to the apex of the 'v'.\n");
   add_prop(OBJ_I_WEIGHT,250);
   add_prop(OBJ_I_VOLUME,250);
}
void
init()
{
   ::init();
   AA(use,use);
}
int
use(string str)
{
   if(!str || str != "rune")
      {
      NF("You can't use a '" + str + "'.\n");
      return 0;
   }
   write("You use the mara rune.\n");
   say(QCTNAME(TP) + " uses the mara rune.\n");
   set_alarm(3.0, 0.0, "effect", environment(this_player()));
   return 1;
}
void
effect(object env)
{
   tell_room(env, "A scintillating light expands forth from the mara rune " +
      "to bathe the entire area with its brilliance.\n");
   object bedloner = present("saddam", env);
   if (bedloner)
        bedloner->react_rune();
   return;
}
 

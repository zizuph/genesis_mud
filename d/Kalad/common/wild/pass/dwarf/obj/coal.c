inherit "/std/object.c";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by korat */
void
create_object()
{
   ::create_object();
   set_name("coal");
   set_adj("small pile of");
   set_pshort("small piles of coal");
   set_long("A small pile of coal, freshly dug out of the rock.\n");
   add_prop("korat_quest_coal",1);
   add_prop(OBJ_I_VALUE,1);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_M_NO_SELL,1);
}

void
init()
{
   ::init();
   add_action("crush","crush");
}

int
crush(string str)
{
   object *wep;
   object coaldust;
      NF("Crush what?\n");
   if (!str) return 0;
   if (str != "coal" && str != "pile of coal")
      return 0;
   
   /* ok, lets crush it if they wield a weapon */
   wep = TP->query_weapon(-1);
   if (!sizeof(wep))
      {
      NF("Crush the coal with what? You must wield a weapon to do that!\n");
      return 0;
   }
   seteuid(getuid());
   coaldust = clone_object("/d/Kalad/common/wild/pass/dwarf/obj/coal_dust");
   coaldust -> move(TP);
   write("You crush the coal with your weapon, grinding it into "+
      "fine-grained dust.\n");
   say(QCTNAME(TP)+" crushes a piece of coal with "+TP->query_possessive()+
      " weapon, grinding it into a fine-grained dust.\n");
   TO->remove_object();
   return 1;
}

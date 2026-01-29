/* spider.c: Food for the Red Eye Inn. */

inherit "/std/food";

#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_food() {
   set_name("spider");
   add_name("plate");
  add_name("poached");
  set_short("plate of poached spider");
    set_pname("spiders");
    add_pname("plates");
  set_pshort("plates of poached spider");
   set_long("@@long_desc");
   add_prop(OBJ_I_VALUE, 0);
   set_amount(150);
   add_prop(OBJ_I_WEIGHT,160);
   add_prop(OBJ_I_VOLUME,140);
}

string
long_desc()
{
  string desc;
  desc = "The sight of the undefinable objects on the dirty "
    + "plate makes you sick. It looks like a heap of squashed "
    + "insects. ";
  if(TP->query_npc()) return BSN(desc);
  switch(QRACE(TP))
  {
    case "goblin":
      desc = "This plate of poached spider looks truely appetizing " 
        + "and smells so delicious that you feel like devouring "
        + "it right now. "; break;
    case "elf": 
    case "human":
    case "hobbit":
    case "dwarf":
    case "gnome":
    default:
  }
  return BSN(desc);
}

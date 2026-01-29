/* temple/obj/h_book.c is cloned by temple/npc/monk.c,
        monk2.c and abbed.c  */
inherit "/std/object";
 
#include "/d/Emerald/defs.h"
 
void
create_object()
{
  seteuid(getuid(this_object()));
  set_name("book");
  set_short("holy book");
  set_adj("holy");
  set_long("The "+short()+" does not interest you, perhaps because " +
      "you fail to understand the language of this book?\n");
 
  add_prop(OBJ_I_WEIGHT,500);
  add_prop(OBJ_I_VOLUME,300);
  add_prop(OBJ_I_VALUE,200+random(50));
}
 
init()
{
 ::init();
 if (environment()==this_player())
   add_action("do_read","read");
}
 
int
do_read(string str)
{
  notify_fail("Read what?\n");
  if (!parse_command(str,TP,"[the][holy]'book'"));
    { return 0; }
  write("You try to decipher something from the holy book but fail.\n");
  return 1;
}

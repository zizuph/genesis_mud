inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <chapel.h>
#include "/d/Emerald/sys/paths.h"

int flag;

/* Prototypes */
void destruct_it(object ob);

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   if (!from || living(ob))
      return;
   set_alarm(1.0, 0.0, &destruct_it(ob));
}

void
destruct_it(object ob)
{
   if (ob && present(ob)) {
      flag = 1;
      ob->remove_object();
      flag = 0;
   }
}

void
leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);
   if (!flag && ob->wedding_stuff())
      clone_here("" + MASTER_OB(ob))->move(this_object());
}

void
create_room()
{
   int i;
   
   set_short("Shop storeroom");
   set_long("You are in a rather large storeroom.  To the "+
      "south you can make out a large wedding shop.\n");
   
   add_exit(CHAPEL_DIR + "shop", "south");
   add_prop(ROOM_I_INSIDE, 1);
   
   clone_object(CHAPEL_DIR + "obj/bouquet")->move(this_object());
   clone_object(CHAPEL_DIR + "obj/dress")->move(this_object());
   clone_object(CHAPEL_DIR + "obj/veil")->move(this_object());
   clone_object(CHAPEL_DIR + "obj/train")->move(this_object());
   clone_object(CHAPEL_DIR + "obj/tuxedo")->move(this_object());
}

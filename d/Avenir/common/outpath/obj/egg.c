// file name:    egg
// creator(s):   Cirion, April 1996
// last update:
// purpose:      An egg that hatches grubs
// note:         
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/object";
#include "../outpath.h"

int    hatch_alarm;

void   hatch();

void create_object()
{
   set_name("egg");
   set_short("slimy white egg");
   set_adj(({"slimy","white"}));
   set_long("It is a small, translucent white egg, slimy "
     +"and nasty. Inside the egg you can see a long form "
     +"moving around inside.\n");

   add_cmd_item("egg", ({"eat","taste","swallow"}), "It would just make "
     +"you sick.\n");

   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 20);

}

void init()
{
   ::init();
   add_action("do_break","break");
   add_action("do_break","smash");
   add_action("do_break","open");

   if(interactive(TP) && !sizeof(get_alarm(hatch_alarm)))
     hatch_alarm = set_alarm(itof(random(900) + 1), 0.0, hatch);
}

int do_break(string str)
{
   NF(CAP(QVB)+" what?\n");
   if(!str || !strlen(str))
     return 0;

   if(!parse_command(str, ({}), "[the] 'egg' %s", str))
     return 0;

   write("You try to "+QVB+" open the egg.\n");
   say(QCTNAME(TP)+" tries to "+QVB+" open "+LANG_THESHORT(TO)+".\n");
   hatch();
   return 1;
}

void hatch()
{
   object   where = ENV(TO);
   object   grub;

   if(living(where))
   {
     where->catch_msg("The slimy white egg starts to "
        +"shake vigourously, and it slips out of your hand!\n");
     move(ENV(where));
   }

// Infinite loop, people, the real infinite loop.
//   while(!ENV(TO)->query_prop(ROOM_I_IS))
//    move(ENV(TO), 1); // Move it to the outermost room...

   while(ENV(TO) && !ENV(TO)->query_prop(ROOM_I_IS))
       move(ENV(ENV(TO)), 1); // Move it to the outermost room...

   if(!sizeof(filter(all_inventory(ENV(TO)), interactive)))
     return;

   seteuid(getuid());
   grub = clone_object(MON+"grub");
   grub->move(ENV(TO), 1);
   
   tell_room(ENV(TO), "The "+short()+" shivers and breaks "
      +"open, and "+LANG_ADDART(grub->short())+" slowly "
      +"crawls out.\n");

    set_alarm(0.0, 0.0, remove_object);
}

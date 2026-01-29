inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

int uses;

reset_object(arg){
   uses = 3;
}

init(){
   add_action("sprinkle", "sprinkle");
   ::init();
}

sprinkle(string str){
   object who;
   uses--;
   if(!str){
      write("You sprinkle the sacred water all about this place.\n");
      say(QCTNAME(this_player()) + " sprinkles water all about.\n");
      check_empty();
      return 1;
   }
   if (str)
      who = present(lower_case(str), environment(this_player()));
   if (!who)
      {
      if (!str || (str == "myself"))
         who = environment(this_object());
      else
         return 0;
   }
   write("You sprinkle " + who->query_name() + " with the sacred water.\n");
   say(QCTNAME(this_player()) + " sprinkles " + who->query_name() +
      " with a vial of water.\n", ({who,this_player()}));
   who->catch_msg(QCTNAME(this_player()) + " sprinkles you with a vial of water.\n");
   check_empty();
   return 1;
}

check_empty(){
   object vial;
   if(uses < 1){
      seteuid(getuid(this_object()));
      vial=clone_object("/d/Terel/mecien/vial");
      vial->move(this_player());
      this_object()->remove_object();
   }
}


create_object()
{
   set_name("water");
   set_adj("holy");
   add_name("vial");
   add_name("spring water");
   set_short("small crystal vial of water");
   set_long("A small beautiful cut-crystal vial. It is etched with a\n"
      + "simple four-pointed star.\nIt contains a small amount of water.\n");
   add_cmd_item(({"water", "vial", "holy water"}),
      "drink", "@@drink_water");
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 50);
   reset_object();
}

drink_water(){
   object vial;
   seteuid(getuid(this_object()));
   vial=clone_object("/d/Terel/mecien/vial");
   vial->move(this_player());
   this_object()->remove_object();
   write("You drink the water from the crystal vial.\n");
   say(QCTNAME(this_player()) + " drinks a small vial of water.\n");
   return 1;
}


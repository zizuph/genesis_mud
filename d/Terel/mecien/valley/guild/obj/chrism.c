/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

int uses;

reset_object(arg){
   uses = 3;
}

init(){
   add_action("anoint", "anoint");
   ::init();
}

anoint(string str){
   object who;
   uses--;
   if(!str){
      write("Anoint who?\n");
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
   write("You anoint " + who->query_name() + " with the holy oil.\n");
   say(QCTNAME(this_player()) + " anoints " + who->query_name() +
      " with holy oil.\n", ({who,this_player()}));
   who->catch_msg(QCTNAME(this_player()) +
     " anoints you with holy oil.\n");
   who->add_prop("anointed", 1);
  who->add_mana(10);
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
   set_name("oil");
   set_adj("holy");
   add_name("vial");
    add_name("sacred_oil");
    add_name("holy_oil");
   add_name("chrism");
   set_short("small crystal vial of holy oil");
   set_long("A small beautiful cut-crystal vial. It is etched with a\n"
      + "simple four-pointed star.\nIt contains chrism.\n");
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


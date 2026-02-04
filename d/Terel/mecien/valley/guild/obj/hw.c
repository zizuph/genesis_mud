/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

int uses;
object who;

#define TP this_player()
#define ENV environment
reset_object(arg){
   uses = 3;
}

init(){
   add_action("sprinkle", "sprinkle");
   ::init();
}

sprinkle(string str){
   uses--;
   if(!str){
      write("You sprinkle the sacred water all about this place.\n");
      say(QCTNAME(this_player()) + " sprinkles water all about.\n");
   ENV(TP)->add_prop("blessed", 1);
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
   if(who->query_alignment()<-800){
      who->catch_msg("Your body burns madly from the water!\n");
      who->add_panic(50);
      tell_room(environment(who), QCTNAME(who) + " cries out in agony!\n", who);
   who->hit_me(20 + random(20), MAGIC_DT, this_player(), -1);
   check_undead(who);
  check_empty();
      return 1;
   }
   if(who->query_alignment()<-400){
      who->catch_msg("You feel a burning sensation on your body.\n");
      who->add_panic(25);
      who->command("moan");
     check_undead(who);
  check_empty();
      return 1;
   }
if(who->query_alignment()<-200){
      who->catch_msg("You feel uncomfortable.\n");
  check_empty();
      return 1;
   }
   who->add_prop("blessed", 1);
  check_empty();
   return 1;
}

check_undead(object who){
if(who->query_prop(LIVE_I_UNDEAD)){
who->hit_me(90, MAGIC_DT, this_player(), -1);
  who->catch_msg("The water seems to eat away at your body!\n");
  tell_room(environment(who), QCTNAME(who) + 
     " seems to go mad from the touch of water!\n", who);
}
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
   object vial, curse;
   seteuid(getuid(this_object()));
   vial=clone_object("/d/Terel/mecien/vial");
   vial->move(this_player());
   write("You drink the water from the crystal vial.\n");
   say(QCTNAME(this_player()) + " drinks a small vial of water.\n");
   curse=present("mystic_curse", this_player());
  if(curse){
     curse->remove_object();
}
   remove_object();
   return 1;
}


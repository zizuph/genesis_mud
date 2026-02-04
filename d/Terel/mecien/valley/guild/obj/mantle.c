/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <filter_funs.h>
#define MYSTIC_RANK 130003


#define TP this_player()

init(){
   add_action("touch", "touch");
   ::init();
}

object *
my_parse_this(string str, string form)
{
   object   *oblist, *tmplist;
   int      i;
   
   tmplist = ({});
   if (!CAN_SEE_IN_ROOM(TP)) return tmplist;
   
   if (!str || (!parse_command(lower_case(str), environment(TP),
               form, oblist)))
   return ({});
   
   oblist = NORMAL_ACCESS(oblist, 0, 0);
   
   if (!sizeof(oblist)) return ({});
   
   for (i = 0; i < sizeof(oblist); i++) {
      if (objectp(oblist[i]) && living(oblist[i]) &&
            (TP != oblist[i]) && CAN_SEE(TP, oblist[i]))
      tmplist = tmplist + ({ oblist[i] });
   }
   return tmplist;
}


touch(string str)
{
   object *ob;
   
   notify_fail("Touch who?\n");
   if (!str) return 0;
   ob = my_parse_this(str, " %l ");
   if (!sizeof(ob)) return 0;
   
   TP->catch_msg("You touch " + QTNAME(ob[0]) + " with the edge of " +
      "your sacred mantle.\n");
   ob[0]->catch_msg(QCTNAME(TP) + " touches you with " +
      TP->query_possessive() + " sacred mantle.\n");
   say(QCTNAME(TP) + " touches " + QTNAME(ob[0]) + " with the edge of "
      + TP->query_possessive() + " sacred mantle.\n",
      ({ ob[0], TP }));
   if(this_object()->query_prop("blessed")){
      if(ob[0]->query_alignment()<-500){
         ob[0]->catch_msg("You feel foul.\n");
         ob[0]->command("shiver");
      }
      if(ob[0]->query_alignment()>500){
         ob[0]->catch_msg("You feel warmth and peace.\n");
         ob[0]->command("smile joyfully");
      }
   }
   return 1;
}

create_armour(){
   set_name("mantle");
   set_adj("gray");
   add_name("mystic_mantle");
   add_name("sacred_mantle");
   
   set_short("gray mantle");
   set_long("A beautiful silvery-gray mantle.\n");
   set_ac(15);
   set_at(A_BODY);
   set_am(({0, 0, 0}));
   add_prop("mystic_armour", 1);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 2000);
   /*add_prop(OBJ_I_VALUE, comp_value(25)); */
}

wear_how(int location){
   
   string pos;
   
   if(TP->query_skill(MYSTIC_RANK)<2){
      TP->catch_msg("You feel as though you have violated some order.\n");
   }
  if(TP == wearer)
  pos = "your";
   else
  pos = wearer->query_possessive();
   
   return " by wrapping it around " + pos + " shoulders";
}


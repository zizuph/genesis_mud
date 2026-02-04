/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*  Mystic Cloud.c */
/*  janus 921029 */

inherit "/std/object";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define BS(xx)    break_string(xx, 72)
#define TO        this_object()
#define TP        this_player()
#define NF(xx)    notify_fail(xx)
#define ETO       environment(TO)
#define EN environment

int duration = 0;
int stuff_id;
object tree_room;

init()
{
   ::init();
   add_action("do_climb", "climb");
   add_action("do_pick", "pick");
}

summon_g(){
  object mon;
    mon = clone_object("/d/Terel/mecien/valley/guild/spells/angserp");
    tell_room(EN(TO), QCNAME(mon) + " coils down from the boughs of the tree!\n");
     mon->move_living("M", EN(TO));
   set_alarm(20.0, -1.0, "return_t", mon);
}

return_t(object mon){
  tell_room(EN(mon), QCTNAME(mon) + " slithers back into the boughs of the tree.\n");
   mon->move_living("M", "/d/Terel/mecien/workroom");
  mon->remove_object();
}

mixed
do_pick(string str){
  if(!str) return 0;
  if(str == "nut"){
   write("You cannot reach them from here.\n");
  if(TP->query_alignment() < -100) set_alarm(5.0, -1.0, "summon_g");
   return 1;
   }
  if(str == "leaf"){
   write("You cannot reach them from here.\n");
  return 1;
  }
  return 0;
}

int
do_climb(string str)
{
   object mon;
   if (!strlen(str) || ((str != "tree") )) {
      NF("Climb what?\n");
      return 0;
   }
   
   if (!tree_room) {
      NF("That is not possible at the moment.\n");
      return 0;
   }
   
   if(TP->query_alignment() < -100){
  TP->catch_msg("The tree burns you.\n");
  set_alarm(4.0, -1.0, "summon_g");
 return 1;
   }

   if (!MEMBER(TP)) {
      NF("You cannot seem to grip the tree.\n");
      return 1;
   }
   
   TP->catch_msg("You climb up into the tree.\n");
  TP->add_prop("_tree_last_room", file_name(EN(TP)));
  tell_room(EN(TP), QCTNAME(TP) + " climbs up into the tree.\n", TP);
   TP->move_living("M", tree_room);
   tell_room(tree_room, QCTNAME(TP) + " climbs up from below.\n", TP);
   return 1;
}

create_object()
{
   set_name("tree");
   add_name("mystic_tree");
   set_adj(({"mystical", "silvery-white"}));
   set_long("@@long@@");
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,10000);
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_M_NO_GET,"You grasp at it in vain.\n");
   add_prop(MAGIC_AM_MAGIC,({150,"summoning"}));
   
   add_item("nuts", "They are silvery-white nuts that grow from the boughs of the tree.\n");
   add_item("boughs", "These sleak and elegant branches are filled with vibrant leaves and luminous nuts.\n");
   add_item("leaves", "They are vibrant silvery-white in colour, thick and plush and form a canopy over the great tree.\n");
   add_item("trunk", "It is silky smooth, of silvery-white colour.\n");
}

if_living(object me){
   if(interactive(me)){
   if(EN(me) == tree_room) return 1;
   }
}


long(){
   string desc, who;
  object *is;
   
   desc = "A beautiful silvery-white tree, its branches reaching high into " +
   "the air, full of vibrant leaves of the same colour. Small nuts grow " +
   "from its elegant boughs.";
   is = filter(all_inventory(tree_room), if_living);
   
   who = " There seems to be someone in the tree.";
  if(!sizeof(is)) return desc + "\n";
   else return desc + who + "\n";
}

set_duration(int d)
{
   set_alarm(itof(d), -1.0, "tree_depart");
}

set_tree_room(object room)
{
   tree_room = room;
}

tree_depart()
{
   int i;
   object *pl;
   
   add_prop(OBJ_I_LIGHT, 1);
   ETO->update_light(1);
   tell_room(ETO, BS("The "+short()+" starts fading away into a luminous glow.\n"));
   pl = all_inventory(tree_room);
   for (i = 0; i < sizeof(pl); i++) {
      if (interactive(pl[i])) {
         pl[i]->catch_msg("The sacred tree returns to the spirit world.\n");
         tell_room(pl[i]->query_prop("_tree_last_room"), QCTNAME(pl[i]) +
            " climbs down from the fading tree.\n");
         pl[i]->move_living("M", pl[i]->query_prop("_tree_last_room"));
        }
   }
   remove_object();
}


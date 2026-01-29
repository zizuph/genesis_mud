inherit "/d/Shire/room";
 
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include <macros.h>
 
#define TP this_player()
#define SHADOW MICH_DIR + "naked.c"

//    Prototypes
void give_naked(object player);
object ob,militia;
object shadow;
int fishes;    /* The current amount of the fishes in the pond */
 
create_room() {
   set_short("About the pond");
   set_long("The track goes close to a small pond with reeds \n" +
   "on its banks. You are feeling like it is a good place for \n" +
   "you to relax and have a break from adventuring. \n" +
"The air is hot and wet here. The fields spread all over the site.\n" +
   "The only exception is a gloomy forest to the west.\n");
   add_item("track","This is a common country side track used by " +
      "local peasants. \n" +
      "You wonder where it leads. \n");
   add_item("reed","These is a simple reed which often grows on the " +
      "banks of " +
      "small lakes, rivers and swamps. \n");
   add_item("pond","This is a little pond - forgotten and uncleaned.\n" +
      "You think you can swim here and even to taste the water.\n" +
      "After some years it becomes a real swamp. \n" +
      "Its only inhabitants are gnats, flies and some fishes. \n");
 
   add_exit(MICH_DIR +"fields1","northwest",0);
   add_exit(MICH_DIR +"fields5","northeast",0);
   add_exit(MICH_DIR +"wood2","west",0);
   reset_room();
 }
 
reset_room() {
   fishes = 2 + random(5);
   if(!ob) {
   ob = clone_object(MICH_DIR +"npc/gnat");
   ob->move(TO);
   ob = clone_object(MICH_DIR +"npc/gnat");
   ob->move(TO);
   ob = clone_object(MICH_DIR +"npc/gnat");
   ob->move(TO);
   }
   if (!militia) {
        militia = clone_object(MICH_DIR +"npc/militia");
        militia->move(TO);
   }
}
 init() {
    ::init();
    add_action("do_swim","swim",0);
    add_action("do_fish","fish",0);
    add_action("do_drink","taste",0);
   add_action("do_drink","drink",0);
    add_action("do_dive","dive",0);
    add_action("do_throw","throw",0);
 }
 
 do_swim() {
 /* Here i check if the player is skillful enough in swimming */
   if(TP->query_skill(103) > 10 + random(5))
 
 { write("You bravely jump into the pond and start swiming around. \n");
   say(QCTNAME(TP) + " starts swiming with great joy in the pond! \n");
   set_alarm(9.0,0.0,"get_rest");
   return 1;
 }
 else { write("But you don't know how to swim, my dear!\n");
     say(QCTNAME(TP) + " doesn't dare to swim here!.\n"); }
 }
 
 get_rest() {
 write("You came out of the water feeling very pleased and relaxed.\n");
 say(QCTNAME(TP) + " stops swimming and leaves the pond. \n");
 TP->add_fatigue(5);
 }
 
do_fish() {
/* I suppose the player to have some hunting skill for fishing */
if (TP->query_skill(105) > random(10))
 
{ write("You sit down fishing.\n");
  say(QCTNAME(TP) + " sit down and looks like fishing.\n");
  set_alarm(9.0,0.0,"get_chance");
  return 1;
}
else { write("Somehow you feel that you won't catch anything.\n");
    say(QCTNAME(TP) + " wants to fish but don't know how to do it!\n");
}    }
 
get_chance() {
object fish;
if (fishes > 0)
 
   /* The players DEX plus hunting skill makes the percentage of      */
   /* success                                                         */
 
   { if (TP->query_stat(1)+TP->query_skill(105) > random(200))
        { write("You catch a small fish with your bare hands!\n");
          say(QCTNAME(TP) + " got a fish from the pond!\n");
          fishes = fishes - 1;
 
        /* Here i give the fish to lucky player */
          fish = clone_object("/std/food");
          fish->set_name("carp");
          fish->set_pname("carps");
          fish->set_short("big tasty carp");
          fish->set_pshort("big tasty carps");
          fish->set_long("This is a big lake carp. It looks to be " +
          "caught not long time ago\n" +
          "as it looks fresh and nutricious. If you are hungry enough\n"+
          "you can try to eat it raw.\n");
          fish->set_adj(({"fresh","big","tasty","raw"}));
          fish->set_amount(195);
          fish->add_prop(OBJ_I_VOLUME,500);
          fish->add_prop(OBJ_I_WEIGHT,500);
          fish->move(TP);
        }
     else { write("Alas, you are too clumsy to catch a fish!\n"); }
   }
else { write("There are no fish left in the pond.\n"); }
}
 
do_drink(str) {
notify_fail(capitalize(query_verb()) + " what? \n");
if (str!="water")
return 0;
write("You drink some water from the pond.\n");
say(QCTNAME(TP) + " drinks some water from the pond. \n");
TP->drink_soft(1000);
write("It is warm and tastes good.\n");
return 1;
}
 
do_dive(str)
{ object ob;        /* an exact thing in the inventory */
  int i;            /* the counter of the inventory */
  object* inven;    /* the pointer on the inventory */
  int burden;
 
 burden=0;
 notify_fail(capitalize(query_verb()) + " where? \n");
   if(str != "in pond" && str != "into pond")
 return 0;
/* The diving requires higher swimming skill */
 if (TP->query_skill(103) > random(10))
 {
   write("You bravely dived into the pond...\n");
   say(QCTNAME(TP) + " have dived into the pond. \n");
/* Any attempt of diving is taking energy */
   TP->add_fatigue(-20);
/* The player cannt dive in too much loaded - more than 19% of max    */
   if (TP->query_encumberance_weight()>19)
    { notify_fail("You don't dare to dive in being so much burdened!\n");
      return 0;
    }
/* Making the player 'naked'   */
   TP->command("remove all");
   TP->catch_msg("You have to remove everything to dive properly.\n");
   say(QCTNAME(TP)+ " gets completely naked before diving into the pond.\n");
/* Dealing the player with naked shadow   */
   if (!TP->query_naked_shadow())
   { set_alarm(0.1,0.0,&give_naked(TP)); }
 
/* Teleporting the player to the bottom of the pond */
 
   TP->move_living("dives down", MICH_DIR + "bottom");
   return 1;
 }
/* If we find out low swimming skill we should swear a bit */
 else { notify_fail("You chicken out at the last moment.\n");
   say(QCTNAME(TP)+ " seems to think better of diving in.\n");
 return 0;         }
 }
 
do_throw(str)
{
object* inven;
int i;
FIXEUID;
 
inven = all_inventory(TP);
for (i=0; i<sizeof(inven); i++)
{
   if (inven[i]->id(str))
   { if (!inven[i]->query_prop(OBJ_M_NO_DROP))
   {  inven[i]->move(MICH_DIR + "bottom");
      write("You threw the " + str +" and it falls down in the pond.\n");
      say(QCTNAME(TP) + " throws the " + str + " in the pond. \n");
      return 1;
   }}
}
notify_fail("You don't have this " + str + " with you.\n");
}
void
give_naked(object ob)
{
   shadow = clone_object(SHADOW);
   shadow->shadow_me(ob);
   shadow->destruct_naked_shadow();
}

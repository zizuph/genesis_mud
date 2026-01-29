/*
**   ARGOS - Metro - Theros Inn
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
**   Can buy food here or rent the room to the south - a temp start loc
*/
inherit "/std/room";
inherit "/lib/pub";
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"
 
/* prototypes */
public object fix_drink(mixed data);
public object fix_food(mixed data);
 
object keeper;
 
void reset_room() {
    if (keeper) return;
    keeper=clone_object(NPC_DIR+"innkeeper");
    keeper->equip_me();
    keeper->move(THIS);
    tell_room(THIS, QCTNAME(keeper)+" walks in.\n");
}
 
void create_room() {
    set_short("Theros Inn");
    set_long(
        "You are standing in the front room of Theros Inn, where "+
        "visitors from many realms come for good food and a place to "+
        "stay. A railed wooden bar divides the front room, the dining "+
        "area on the west side with its sets of tables and chairs, "+
        "and the kitchen on the east with it hearth where pots of stew "+
        "simmer. A doorway leads into another part of the inn to the "+
        "south, while you can see the streets outside to the north "+
        "and west.\n");
 
    add_item("bar",
       "It is a beautifully carved wooden bar with a long brass rail "+
       "running its length at the foot. It separates the dining from "+
       "the kitchen area. There is a menu on it.\n");
    add_item(({"dining","dining area"}),
       "The dining area is on the west side of the room with three "+
       "sets of tables and chairs.\n");
    add_item("kitchen",
       "The kitchen is behind the bar, a large hearth with warming "+
       "fires simmering pots of stew inside.\n");
    add_item("menu",
       "It is hanging on the bar. There is writing on it.\n");
    add_cmd_item("menu", "read", "@@read");
    add_item(({"table","tables","chairs","chair"}),
       "Three sets of a small square table surrounded by four "+
       "chairs are lined along the western wall.\n");
    add_item("hearth",
       "Taking up most of the eastern wall, the hearth is made of "+
       "marble and houses cooking food over its fires.\n");
    add_item(({"stew","pots","food"}),
       "Large black iron pots are suspended over the fires of the hearth, "+
       "the smell of hearty stew steaming from each.\n");
    add_item(({"fire","fires"}),
       "The fires cook the food in the hearth.\n");
    add_item(({"street","streets"}),
       "The streets are outside to the north and west.\n");
 
    /* food:  cc = 5 + (grams*grams/600) */
    add_food("baklava","baklava","sweet",
             55,10,"baklava","pieces of baklava",
             "It is a sweet, crusty pastry, a favorite of Argosians.\n");
    add_food("gemista","gemista","baked",
             250,110,"gemista","gemistas",
             "It is a baked green pepper filled with sauce and rice.\n");
    add_food(({"bowl of goat stew","goat stew","stew"}),
             ({"bowl of goat stew","goat stew","stew"}),
             0, 350, 210, "bowl of goat stew","bowls of goat stew",
             "It is a thick stew made with vegetables and goat meat. " +
             "It looks wholesome.\n");
 
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
 
    add_exit(ROOM_DIR+"lroad11","north",0);
    add_exit(ROOM_DIR+"droad8","west",0);
    add_exit(ROOM_DIR+"inn2","south",0);
    reset_room();
}
 
 
int read(string str) {
    write("" +
        "-----------------------------------\n" +
        " Theros' Inn - Argosian Delicacies \n" +
        "-----------------------------------\n" +
        "   Baklava                    10 cc\n" +
        "   Gemista                   110 cc\n" +
        "   Goat Stew                 210 cc\n\n" +
        "   Room for rent               8 sc\n"+
        "   (Ask for more information)      \n"+
        "-----------------------------------\n");
    return 1;
}
 
int order(string args) {
  /* prevents buy command if keeper isn't present */
  int buyrc;
  if (keeper && present(keeper,this_object())) {
      buyrc=::order(args);
     if (buyrc)   /* transaction went OK */
        keeper->command("smile merrily");
     else
        keeper->command("say Hmmm, there seems to be a problem here.");
     return buyrc;
     }
  else {
     tell_object(this_player(),"But the inn keeper is not here!\n");
     return 1;
  }
}
 
int rent() {
   object Tp=this_player();
   object Tr=this_object();
 
   if (!(keeper && present(keeper,this_object()))) {
      write("But the inn keeper is not here!\n");
      return 1;
   }
 
   if (Tp->query_prop(RENTED_INN_ROOM)) {
      keeper->command("say I already have you on the books for tonight.");
      keeper->command("say No need to pay again.");
       return 1;
   }
 
   if (MONEY_ADD(Tp,96)) {
      Tp->catch_msg("You pay "+QTNAME(keeper)+" the rental fee.\n");
      tell_room(QCTNAME(Tp)+" pays "+QTNAME(keeper)+" some money.\n",Tp);
      Tp->add_prop(RENTED_INN_ROOM,1);
      keeper->command("emote writes something in a small book.");
      keeper->command("say OK, you are registered to stay here tonight.");
      keeper->command("say I think you'll find the bed comfortable.");
      keeper->command("smile greedily");
      return 1;
   }
 
   keeper->command("say You can't pay the price!");
   keeper->command("say The room is for paying customers only. "+
                      "I'm not running a shelter here!");
   keeper->command("smirk");
   return 1;
}
 
void init() {
   ::init();
   init_pub();
   add_action("rent","rent");
}
 
/* added these to make food unsellable */
public object fix_food(mixed data) {
    object ob;
    ob = ::fix_food(data);
    ob->add_prop(HEAP_I_UNIT_VALUE, 0);
    return ob;
}
public object fix_drink(mixed data) {
    object ob;
    ob = ::fix_drink(data);
    ob->add_prop(HEAP_I_UNIT_VALUE, 0);
    return ob;
}

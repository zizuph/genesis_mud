/*
** ARGOS - Metro - Pub
**
** History
** Date      Coder      Action
** -------- ----------- --------------------------
** 3/3/95   Zima        Created
**
*/
inherit "/std/room";
inherit "/lib/pub";
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"
object   bartender=0;
#define NUM 2

/* prototypes */
public object fix_food(mixed data);
public object fix_drink(mixed data);

object *guard=allocate(NUM);
 
void make_bartender() {
    if (bartender) return;
    bartender=clone_object(NPC_DIR+"bartender");
    bartender->equip_me();
    bartender->move(THIS);
    tell_room(THIS, QCNAME(bartender)+" pops up from behind the bar.\n");
}
 
void make_guard(int i) {
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"barpatron");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" walks in and orders an ouzo.\n");
}
 
void reset_room() {
   int i;
   make_bartender();
   for (i=0; i<NUM; i++)
      make_guard(i);
}
 
void create_room() {
   set_short("Ouzophilos Pub");
   set_long(
       "The smell of stale beer and wine soaked into the wooden tables "+
       "of this establishment recall nights of merriment gone by in "+
       "Ozouphilos pub. A long wooden bar sits along the western wall "+
       "of the pub, behind which are bottles of various local drinks. "+
       "There is a menu hanging on the bar, and you think you might "+
       "like to have one yourself.\n");
 
   add_item("bar", "A simple wooden bar paralleling the west wall.\n");
   add_item("menu","It is hanging on the bar. There is writing on it.\n");
   add_item("tables",
            "Several wooden tables, worn from the revelry of the past, "+
            "are scattered in a somewhat organized manner across "+
            "the floor of the room, three or four chairs sitting "+
            "around each.\n");
   add_item("chairs",
            "They are scattered about the room sitting around the "+
            "tables.\n");
   add_cmd_item("menu", "read", "@@read");
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
 
   /* drink - values taken from doc/examples/trade/inn.c */
   add_drink ("ouzo","ouzo","clear",100,5,12,"ouzo","ouzos",
              "It is a clear alcoholic drink found in Argos.\n");
   add_drink(({"retsina","wine","bottle of retsina"}),
             ({"bottle of retsina","retsina","wine"}), 0,
             200,25,72,
             "bottle of retsina","bottles of retsina",
             "It is a white wine of Argosian vintage. " +
             "It has an odd pine aroma.\n");
   add_drink(({"ouisku","whiskey","bottle of ouisku"}),
             ({"bottle of ouisku","ouisku","whiskey"}), 0,
             400,100,300,
             "bottle of ouisku","bottles of ouisku",
             "It is a strong dark alcoholic beverage poplular in "+
             "Argos, much like whiskey.\n");
 
    add_exit(ROOM_DIR+"lroad9","north",0);
    add_exit(ROOM_DIR+"droad8","east",0);
    reset_room();
}
 
void init() {
    ::init();
    init_pub(); /* initialize pub support */
}
 
int read(string str) {
    write("" +
        "---------------------------------------\n" +
        " Ouzophilos Pub - Fine Argosian Spirits\n" +
        "---------------------------------------\n" +
        "   Ouzo                       12 cc\n" +
        "   Retsina (Wine)             72 cc\n" +
        "   Ouisku  (Whiskey)         300 cc\n" +
        "\n");
    return 1;
}

int order(string args) {
  /* prevents buy command if bartender isn't present */
  int buyrc;
  if (bartender && present(bartender,this_object())) {
      buyrc=::order(args);
     if (buyrc)   /* transaction went OK */
        bartender->command("smile merrily");
     else
        bartender->command("say Hmmm, there seems to be a problem here.");
     return buyrc;
     }
  else {
     tell_object(this_player(),"But the bartender is not here!\n");
     return 1;
  }
}
 
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

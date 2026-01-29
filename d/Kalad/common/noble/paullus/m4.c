/* Sarr
 *
 * Modification log:
 * Fysix, Jan 1998: Fixed guards cloning, after a reset_room
 *                  the room forgot the guards were there.
 */

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

object ob,ob2,ob3;
object *guard = allocate(3);
int    guards_cloned;

void reset_room();
void call_guards(object enemy);

void
create_room()
{
    set_short("In the northern part of the Dining Room");
    set_long("You now stand in the north part of a very long "+
    "room. This appears to be the dining room. A very long "+
    "wooden table is placed here, stretching all the way down "+
    "to the south end of this room. Various nobles and their "+
    "guests sit at the table eating food. The walls in here are "+
    "lined with candles, and a large and intricate glass ball "+
    "is hanging overhead. To the southwest, you see the "+
    "main entrance hall.\n");
 
    add_item("candles","They burn giving light.\n");
    add_item(({"guests","nobles"}),"They chow down on food.\n");
    add_item("ball","A wonderful looking ball, it is made out of "+
    "different colored glass, resulting in a giant ball mirror that "+
    "reflects many different colored lights. It is beautiful.\n");
    add_item("table","A very beautiful and ornately decorated table. "+
    "An intricatly decorated table cloth covers it. Many fine "+
    "dishes and platters are scattered about, with warm steamy food "+
    "on it.\n");
    add_item("dishes","Fine china and crystal goblets.\n");
    add_item("platters","Silver platters with food on them.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m7),"north",0,-1,-1);
    add_exit(NOBLE(paullus/m1),"southwest",0,-1,-1);
    add_exit(NOBLE(paullus/m3),"south",0,-1,-1);
    reset_room();
}

// Clone, arm and move an npc
varargs object
clone_npc(string file_name, string how = "xxx")
{
object npc;
   
   npc = clone_object(file_name);
   npc->arm_me();
   npc->move_living(how, TO);

   return npc;
}

void
reset_room()
{
    if(!ob)
        ob = clone_npc(NOBLE(npc/yf_dinner_noble));
    if(!ob2)
        ob2 = clone_npc(NOBLE(npc/ym_dinner_noble));
    if(!ob3)
        ob3 = clone_npc(NOBLE(npc/ym_dinner_noble));

    guards_cloned = 0;
}

// Guards are summoned here
void
call_guards(object enemy)
{
int i, n_cloned;
   
   if (guards_cloned)
      return;
   
   i = sizeof(guard);
   n_cloned = 0;
   
   while (i--)
   {
      if (!guard[i])
      {
         guard[i] = clone_object(NOBLE(npc/house_guard));
         guard[i]->set_house_name("Paullus");
         guard[i]->set_color_name("red-gold");
         guard[i]->arm_me();
         guard[i]->move_living("M", TO);
         n_cloned++;
         guards_cloned = 1;
      }
   }

   if (n_cloned > 0)
      tell_room(TO, (n_cloned == 1 ?
         "A guard runs" : "Some guards run") + " in to the rescue!\n");
   
   i = sizeof(guard);
   while (i--)
   {
      guard[i]->command("shout Die trouble maker!");
      guard[i]->command("kill " + enemy->query_real_name());
   }
}

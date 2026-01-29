/* Sarr
 *
 * Modification log:
 * Fysix, Jan 1998: Fixed guards cloning, after a reset_room
 *                  the room forgot the guards were there.
 */

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

object ob;
object ob2;
object *guard = allocate(2);
int    guards_cloned;

void reset_room();
void call_guards(object ob);

void
create_room()
{
    set_short("In the Ball Room of the House of Paullus");
    set_long("You now find yourself in southeast corner of what "+
    "appears to be a giant ball room. The floor beneath you is "+
    "made of polished wood for dancing. There are nobles here "+
    "dancing and having a good time. The main entrance is off "+
    "to your east, while the ball room stretches out to your north "+
    "and west.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m6),"north",0,-1,-1);
    add_exit(NOBLE(paullus/m19),"northwest",0,-1,-1);
    add_exit(NOBLE(paullus/m20),"west",0,-1,-1);
    add_exit(NOBLE(paullus/m1),"east",0,-1,-1);

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
        ob = clone_npc(NOBLE(npc/ym_ball_noble));
    if(!ob2)
        ob2 = clone_npc(NOBLE(npc/yf_ball_noble));

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
         "A guard runs" : "A pair of guards run") + " in to the rescue!\n");
   
   i = sizeof(guard);
   while (i--)
   {
      if (i > 0)
         guard[0]->team_join(guard[i]);
      guard[i]->command("shout Die trouble maker!");
      guard[i]->command("kill " + enemy->query_real_name());
   }
}

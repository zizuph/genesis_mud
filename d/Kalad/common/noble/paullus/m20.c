/* Sarr
 *
 * Modification log:
 * Fysix, Jan 1998: Fixed guards cloning, after a reset_room
 *                  the room forgot the guards were there.
 */

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

object *guard = allocate(2);
int    guards_cloned;

void call_guards(object ob);

void
create_room()
{
    set_short("In the Ball Room of the House of Paullus");
    set_long("You now find yourself in southwest corner of what "+
    "appears to be a giant ball room. The floor beneath you is "+
    "made of polished wood for dancing. There are nobles here "+
    "dancing and having a good time. The ball room stretches out "+
    "to your north and east.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m2),"east",0,-1,-1);
    add_exit(NOBLE(paullus/m19),"north",0,-1,-1);
    add_exit(NOBLE(paullus/m6),"northeast",0,-1,-1);
    
    reset_room();
}

void
reset_room()
{
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
      guard[i]->command("shout Die trouble maker!");
      guard[i]->command("kill " + enemy->query_real_name());
   }
}


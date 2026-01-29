/* modified by Olorin, 5-jun-1993
 * inserted a check for no_of_rats in make_rat()
 */
inherit "/std/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/time.c"

#define MAX_RATS 5 /* max number of rats running around */
#define WEAPONS ({WEP_DIR+"knife",WEP_DIR+"stick",WEP_DIR+"fssword",\
                  WEP_DIR+"qstaff",WEP_DIR+"hatchet",EDORAS_DIR+"obj/fknife",})

object *rats;
int no_of_rats,
    mr_aid;

void add_stuff();
void make_rat();

create_room()
{
  set_short("A large warehouse in the Harlond");
  set_long(BS("You are in a large, dimly lit warehouse in the Harlond. "+
    "A few empty crates are stacked in a corner, and there's not "+
    "much else here, except the squeaking of rats. "+
    "The exit to the pier is south.\n"));
  add_item("crates","The empty crates are just that - empty.\n");
  add_item("rats","You are sure they are hiding somewhere in the walls.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_exit(MINAS_DIR+"harlond/pier4","south",0);
  rats = allocate(MAX_RATS);
  add_stuff();
}

add_stuff()
{
  object weapon;
  mr_aid = set_alarm(5.0, 0.0, make_rat);
  if(!present("_hidden_weapon",TO))
  {
    weapon = clone_object(WEAPONS[random(sizeof(WEAPONS))]);
    weapon->add_name("_hidden_weapon");
    weapon->add_prop(OBJ_I_HIDE,5+random(10));
    weapon->move(TO);
  }
}

reset_room()
{
  add_stuff();
}

make_rat()
{
  if (!sizeof(get_alarm(mr_aid)))
    mr_aid = 0;
  if(!rats[no_of_rats])
  {
    rats[no_of_rats] = clone_object(NPC_DIR+"rat");
    rats[no_of_rats]->move(TO);
    tell_room(TO,"A filthy rat comes running from between the crates.\n");
  }
  no_of_rats++;
  if(no_of_rats == MAX_RATS)
  {
    no_of_rats = 0;
    return;
  }
  if (!mr_aid)
    mr_aid = set_alarm(200.0 + rnd()*200.0, 0.0, make_rat);
}

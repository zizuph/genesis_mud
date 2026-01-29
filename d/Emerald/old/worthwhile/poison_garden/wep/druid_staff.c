/* druid_staff.c created by Shiva@Genesis
 * a druid staff is a very special weapon, enchanted with a number
 * of druid spells meant especially for the purpose.
 */

inherit "/std/weapon";

#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#define EYES    1
#define CARVING 2
#define VINES   4
#define LEAVES  8

static mapping looked_at_carving = ([ ]);
static object *ided_wood         = ({ });
static object *noticed_eyes      = ({ });

static object who_to_trap;

void create_weapon()
{
  set_name("staff");
  add_adj("wooden");
  set_long("A very solid and intricately carved wooden staff.\n");

  add_item(({ "carving", "carvings" }), "@@exa_carving@@");
  add_item("vines",  "@@exa_vines@@");
  add_item("leaves", "@@exa_leaves@@");
  add_item("wood",   "@@exa_wood@@");

  set_hit(40);
  set_pen(40);
  set_dt(W_BLUDGEON);
  set_wt(W_CLUB);
  set_wf(this_object());
  set_hands(W_BOTH);
  set_likely_break(1);
  set_likely_corr(2);

  add_prop(OBJ_I_VALUE, 2500);
  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 2000);
}

int looked_already(string name, int at_what)
{
  return (member_array(name, m_indices(looked_at_carving)) >= 0 && 
          looked_at_carving[name] & at_what);
}

void add_looked(string name, int at_what)
{
  if (member_array(name, m_indices(looked_at_carving)) >= 0)
  {
    looked_at_carving[name] |= at_what;
    return;
  }
  
  looked_at_carving[name] = at_what;
}

static string eyes_desc()
{
  string name = this_player()->query_real_name();

  if (member_array(this_player(), noticed_eyes) < 0 &&
      this_player()->resolve_task(TASK_ROUTINE + 100,
      ({ TS_INT, SS_AWARENESS })) > 0)
  {
    noticed_eyes += ({ this_player() });
    add_item("eyes", "@@exa_eyes@@");
    return "You notice what look like tiny eyes among the flora.\n";
  }

  return "";
}

string exa_carving()
{
  string str;
  string name = this_player()->query_real_name();

  if (looked_already(name, CARVING))
  {
    str = "Odd...the carvings seem to have changed since you " +
        "last looked.\n";
  }
  else
  {
    add_looked(name, CARVING);
    str = "The staff is covered with amazingly detailed carvings\n" +
        "of intertwined vines and myriad leaves.\n";
  }
      
  return str + eyes_desc();
}

string exa_vines()
{
  string str;
  string name = this_player()->query_real_name();

  if (looked_already(name, VINES))
  {
    str = "Odd...the vines seem to have grown and shifted since you " +
        "last looked.\n";
  }
  else
  {
    add_looked(name, VINES);
    str = "Twisted vines covered with wicked, jagged thorns.\n";
  }

  return str + eyes_desc();
}

string exa_leaves()
{
  string str;
  string name = this_player()->query_real_name();
  
  if (looked_already(name, LEAVES))
  {
    str = "Odd...the leaves seem to have shifted since you last looked.\n";
  }
  else
  {
    add_looked(name, LEAVES);
    str = "Tiny leaves of innumerable types delicately carved into the " +
        "surface of the staff.\n";
  }

  return str + eyes_desc();
}

string exa_wood()
{
  if (member_array(this_player(), ided_wood) < 0)
  {
    if (this_player()->resolve_task(TASK_DIFFICULT + 100, ({ TS_INT,
        SS_APPR_OBJ })) <= 0)
    {
      return "The wood seems to be quite sturdy; every centimeter " +
          "of its surface is covered with detailed carvings.\n";
    }

    ided_wood += ({ this_player() });
  }

  return "The staff seems to be fashioned from the wood of a silver " +
      "oak, valued above all other wood for its strength and rumoured " +
      "magical properties; every centimeter of its surface is covered " +
      "with amazingly detailed carvings, obviously created by a master.\n";
}

string exa_eyes()
{
  string name = this_player()->query_real_name();

  if (looked_already(name, EYES))
  {
    return "The eyes seem to have grown more numerous since you last " +
        "looked!\n";
  }  

  add_looked(name, EYES);
  return "Hundreds of pairs of sinister, frightening eyes, which seem " +
      "to be peering at you from inside the vines.\n";
}

void set_who_to_trap(object who)
{
  who_to_trap = who;
}

int wield()
{
  object room;

  if (this_player() == who_to_trap && 
      (room = clone_object("/std/room")))
  {
    room->set_name("vines");
    room->set_short("Tangled vines");
    room->set_long("You are trapped in a tangled mass of vines.\n");
    room->move(environment(this_player()));
    this_player()->move_living("M", room, 1, 1);
    return -1;
  }
  
  return 0;
}

void init()
{
  ::init();

  if (member_array(this_player(), noticed_eyes) >= 0)
  {
    if (!item_id("eyes"))
    {
      add_item("eyes", "@@exa_eyes@@");
    }
  }
  else
  {  
    remove_item("eyes");
  }
}


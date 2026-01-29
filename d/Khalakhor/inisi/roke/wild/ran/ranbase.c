/*
 * ranbase.c
 *
 * Base room for random forest.
 * By Glindor, Nov 2001.
 * Added a walkthrough for those who did the quest before - Tapakah, 07/2021
 */

#pragma save_binary
#pragma strict_types

#include "/d/Khalakhor/sys/paths.h"

inherit "/std/room";
inherit HERBSEARCH;

#include "/d/Khalakhor/sys/terrains.h"
#include "randefs.h"
#include <language.h>
#include <macros.h>
#include <std.h>

object *items, *owner;
int room_id;

void follow(object who, object tp, object *objs);

void
setup_forest_herbs()
{
  string * herbs;

  herbs = HERBMASTER->query_herbs(({TERRAIN_MIXEDWOOD}));
  set_up_herbs(({one_of_list(herbs), one_of_list(herbs),
                 one_of_list(herbs), one_of_list(herbs)}));
}

void
create_forroom()
{
}

void
set_room_id(int id)
{
  room_id = id;
}

static string
step(int dir)
{
  int dest;
  dest = MAPSERVER->query_dest(this_player()->query_real_name(), 
                               room_id, dir);
  switch(dest) {
  case 30: return SOUTHROOM;
  case 31: return EASTROOM;
  case 32: return OGIONROOM;
  default: return RANROOMBASE + dest;
  }
}

string step_north() { return step(NO);}
string step_east() { return step(EA);}
string step_west() { return step(WE);}
string step_south() { return step(SO);}

string
xlong ()
{
  string extra_long = QDONE(ROKEGROUP, OGIONMAZE) ?
    ("You feel like you've been through this path before, and if "+
     "you call your destination, you may get there at once.\n") :
    "Somehow you feel that you are lost.\n";

  return LONGDESCR + extra_long;
}

nomask void
create_room()
{
  set_short(SHORTDESCR);
  set_long(xlong);

  OUTSIDE;
  setup_forest_herbs();

  create_forroom();
    
  add_item(THIRDITEM, THIRDDESCR3);
  switch (room_id % 3) {
  case 1:
    add_item(THIRDITEM, THIRDDESCR1);
    break;
  case 2:
    add_item(THIRDITEM, THIRDDESCR2);
    break;
  }
  add_cmd_item(({"rose", "flower"}), "pick",
               "A small gnome smites your fingers with a ruler.\n");

  add_item(SECONDITEM, SECONDDESCR1);
  switch (((room_id - 1) / 3) % 3) {
  case 1:
    add_item(SECONDITEM, SECONDDESCR2);
    break;
  case 2:
    add_item(SECONDITEM, SECONDDESCR3);
    break;
  }
    
  add_item(FIRSTITEM, FIRSTDESCR1);
  switch (((room_id - 1) / 9) % 3) {
  case 1:
    add_item(FIRSTITEM, FIRSTDESCR2);
    break;
  case 2:
    add_item(FIRSTITEM, FIRSTDESCR3);
    break;
  }

  add_exit(VBFC_ME("step_north"), "north");
  add_exit(VBFC_ME("step_east") , "east");
  add_exit(VBFC_ME("step_south"), "south");
  add_exit(VBFC_ME("step_west") , "west");

  add_npc(ROKEDIR + "npc/ant", random(4));
  
}

// Handle people trying to drop stuff
void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if (room_id == 1 && interactive(ob))
    MAPSERVER->arrived(ob->query_real_name());
        
  if (!living(from))
    return;

  if (sizeof(items) == 0)
    {
      items = ({ob});
      owner = ({from});
    }
  else
    {
      items += ({ob});
      owner += ({from});
    }
}

void
leave_inv(object ob, object to)
{
  int d;
  object *objs;

  ::leave_inv(ob, to);

  objs = ({});

  if (living(ob))
    {
      while ((d = member_array(ob, owner)) != -1)
        {
          if (items[d])
            objs += ({items[d]});
          items = exclude_array(items, d, d);
          owner = exclude_array(owner, d, d);
        }
      if (sizeof(objs))
        set_alarm(1.0, 0.0, &follow(ob, to, objs));
    }
  else
    {
      if ((d = member_array(ob, items)) == -1)
        return;
      items = exclude_array(items, d, d);
      owner = exclude_array(owner, d, d);
    }
}

void
follow(object who, object to, object *objs)
{
  object gnome;
  int t;

  if (!who)
    return;

  seteuid(getuid());
  gnome = clone_object(ROKEDIR + "npc/gnome");
  gnome->move_living("M", TO);
  tell_room(TO, "A small gnome arrives.\n");
  for (t = 0; t < sizeof(objs); t++)
    {
      if (objs[t])
        {
          objs[t]->move(gnome);
          tell_room(TO, "The small gnome picks up " +
                    LANG_ASHORT(objs[t]) + ".\n");
        }
    }
  gnome->move_living("somewhere", ENV(who));
  gnome->command("say Hey, you dropped something.");
  for (t = 0; t < sizeof(objs); t++)
    {
      if (objs[t])
        {
          objs[t]->move(who);
          tell_room(to, "The small gnome gives " +
                    LANG_ASHORT(objs[t]) + " to " + QCTNAME(who) + ".\n", ({who}));
          who->catch_msg("The small gnome gives you " +
                         LANG_ASHORT(objs[t]) +
                         ".\n");
        }
    }
  gnome->command("say CU.");
  gnome->command("wave " + who->query_real_name());
  tell_room(to, "The small gnome disappears between some trees.\n");
  gnome->remove_object();
}

void
move_to_ogion ()
{
  if (TP->query_prop(OBJ_M_NO_TELEPORT)) {
    write("You feel a slight shudder through your body, but realize " +
          "something is interfering with your move.\n");
    return;
  }
    
  int result = TP->move_living("X", OGIONROOM, 1);
  
  if (! result)
    write("You recognize the place immediately.\n");
}

int
call_ogion (string str)
{
  if (!str)
    NF0("Call who?");
  if (str != "noigo" && str != "ogion" && str != "perfect human")
    NF0("Call who?");
  write("You feel the wind from the north rustling through the leaves.\n");
  set_alarm(1.0, 0.0, move_to_ogion);
  return 1;
}
/* Test functions */

void
init()
{
  ::init();

  if (QDONE(ROKEGROUP, OGIONMAZE))
    add_action(call_ogion, "call");
  if (!(SECURITY->query_wiz_level(this_player()->query_real_name())))
    return;
  add_action("morph", "morph");
  add_action("mappa", "mappa");
  add_action("syd", "syd");
}

int
morph(string str)
{
  return MAPSERVER->morph(str);
}

int
mappa(string str)
{
  return MAPSERVER->mappa(str);
}

int
syd(string str)
{
  return MAPSERVER->syd(str);
}

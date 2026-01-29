inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"

#define MANA_LIMIT      15 /* How much mana does it cost to look at mirror */
#define CAST_LIMIT      50 /* How wise and skilled must the caster be? */

object eye_object;
int mirror_is_polished=0;

void create_object()
{
   seteuid(getuid());

    set_name("mirror");
    set_pname("mirrors");
    set_adj("silver");
    set_long("@@long_mirror");

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE,350);

    set_alarm(5.0, 0.0, "make_eye");
}

void make_eye()
{
  if(objectp(eye_object)) return;

  eye_object = clone_object(OBJ_DIR+"eye");
  eye_object->add_prop("_mirror_to_this_eye", file_name(TO));
  eye_object->move(MISTY_DIR+"gcaves/d12");
  eye_object->add_prop(OBJ_I_HIDE, 50);
  return;
}

string long_mirror()
{
  object room, this_room, last_room;
  int player_has_light;

  if(TP->query_attack())
    return "Don't look at your possesions and fight you coward!!!\n";

  if(!mirror_is_polished)
   {
    write("This is nice small little bit dusty silver mirror.\n");
    if(TP->query_guild_name_occ()=="Vampyr guild")
      return "When you look in it you see only some strange mist there.\n";
    else
      return "When you look in it you see some ugly face "+
             "looking back at you.\n";
   }
  else
   {
    mirror_is_polished = 0;
    write("This is nice small silver mirror.\n");

    if (TP->query_mana() < MANA_LIMIT)
      return "You can't concentrate enough to focus on mirror.\n";

    TP->add_mana(-MANA_LIMIT);

    if (random(TP->query_stat(SS_WIS) +
	       TP->query_stat(SS_SPELLCRAFT)) < random(CAST_LIMIT))
      return "You tried to look on mirror but haven't managed to focus.\n";

    write("You concentrate hard and manage to focus on mirror. "+
          "You see following:\n");
    if(objectp(eye_object)){ room = eye_object; }
    else room = TO;
    while(!(room=environment(room))->query_prop(ROOM_I_IS));
    this_room = environment(TP);
    if(room->query_prop(ROOM_I_IS))
    {
      last_room = TP->query_prop(LIVE_O_LAST_ROOM);
      if(room != this_room)
         TO->add_prop(OBJ_I_LIGHT, -1*(TP->query_prop(OBJ_I_LIGHT)));
      TP->move_living("M",room, 1);
      TP->move_living("M",this_room, 1, 1);
      TP->add_prop(LIVE_O_LAST_ROOM, last_room);
      TO->add_prop(OBJ_I_LIGHT, 0);
    }
    else
    {
      write("This is a bug. Please mail Milan informations where the "+
            "eye was as clear as possible.");
    }
    return "";
   }
}

init()
{
    ::init();
    add_action("polish", "polish");
}

int polish(string mirror)
{
  if(mirror == "mirror")
  {
    write("You polish your silver mirror.\n");
    mirror_is_polished = 1;
    return 1;
  }
  NF("Polish what?\n");
  return 0;
}

string query_recover()
{ 
   object room; 
    room = eye_object;
   if (!room) return MASTER;
   while(environment(room)) room = environment(room);
   return MASTER + ":" + file_name(room);
} 

void init_recover(string arg)
{ 
  string room, foobar;

   eye_object = clone_object(OBJ_DIR+"eye");
   eye_object->add_prop("_mirror_to_this_eye", file_name(TO));
   eye_object->add_prop(OBJ_I_HIDE, 50);
   if (!eye_object->move(arg))
   {
      eye_object->remove_prop(OBJ_I_HIDE);
      eye_object->move(environment());
   }
} 

void remove_object()
{
 object room; 
  if(eye_object)
  {
    room = eye_object; 
    while(!(room=environment(room))->query_prop(ROOM_I_IS));
    eye_object->remove_object();
    tell_room(room, "Glass eye sudenly turns into dust.\n");
  }
  ::remove_object();
} 

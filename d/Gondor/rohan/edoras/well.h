 /*
  * This is for the well in Edoras
  *
  * The idea and the original coding is from Dust, 
  *  from the well in the mansion in Terel.
  *  /d/Terel/common/town/mansion/crt/Dive.h
  * There are some modifications done by Olorin:
  *  -> it takes much less time to drown (_breath_int = 2 instead of 7)
  *  -> I use heal_hp(-100000) instead of set_hp(0), since
  *     set_hp(0) doesn't seem to work always when called for the first time
  *  -> I take additional precaution to prevent multiple deaths
  *
  * I hope I mentioned all my modification, but I don't make any promises.
  * If it works, praise Dust.
  * If it ain't, complain to Olorin first!
  *
  *  Olorin, Feb 1993
  *
  * Changed by Gnandar 2 June 1998 to allow a fake "search" in the dark
  * (since cmd/live/thing.c now blocks it).  one problem is that this
  * is now an instant search -- no delay -- but i can live with that
  * for now.  better than an unsolvable quest.
  */

inherit "/d/Gondor/common/room";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

int check_things_alarm;
int level;
int fake_search(string arg);

int
calc_basic() 
{
  return ((3*TP->query_skill(SS_SWIM) + 
             TP->query_stat(SS_STR) + 
             TP->query_stat(SS_CON) + 
             TP->query_stat(SS_DEX)) /6) ;
}

string
short_desc(object thing)
{
    if (thing->query_prop(HEAP_I_IS))
        return CAP(thing->short());
    return CAP(LANG_ADDART(thing->short()));
}

sink_down(mixed *args)
{
    object thing;
    string room;

    thing = args[0];
    room = args[1];
    thing->move(room);
    tell_room(TO, short_desc(thing) +
	" sinks downwards....\n");
    tell_room(room, short_desc(thing) + 
	" arrives from above....\n");
}

float_up(mixed *args)
{
    object thing;
    string room;

    thing = args[0];
    room = args[1];
    thing->move(room);
    tell_room(TO, short_desc(thing) + 
	" floats upwards....\n");
    tell_room(room, short_desc(thing) + 
	" arrives from below....\n");
}

int
check_things()
{
  int i, interval;
  object *op, thing;
  int breath;

  op = all_inventory();
  for (i=0; i<sizeof(op); i++)
  {
    thing = op[i];
    if (interactive(thing))
    {
      breath = thing->query_prop("_breath_int") - 1;
      if (breath)
      {
        thing->add_prop("_breath_int",breath);
        continue;
      }
      interval = thing->query_prop("_breath_int_times");
      if (interval < 1) interval = 1;
      if (interval > 50) interval = 50;
      thing->add_prop("_breath_int", interval);
      breath = thing->query_prop("_breath");
      breath--;
      thing->add_prop("_breath",breath);
      if (!breath && !thing->query_ghost())
      {
        thing->add_prop("_breath_int",1);
        thing->heal_hp(-1 * thing->query_max_hp());
        thing->catch_tell("Why didn't you take a breath or leave " +
            "the well earlier? You run out of air " +
            "and drown...\n");
        thing->do_die(this_object());
        log_file("drown",thing->query_name()+
            " drowned in the well in Edoras, "+ctime(time())+".\n");
        continue;
      }
      switch (breath)
      {
        case 12: case 11: case 10: case 9: case 8: 
        case 7: tell_object(thing, "You feel very well.\n"); break;
        case 6: tell_object(thing, "You feel quite giddy.\n"); break;
        case 5: tell_object(thing, "You feel very sick - you need air!\n"); break;
        case 4: tell_object(thing, "You are really out of breath!\n"); break;
        case 3: tell_object(thing, "You are completely out of breath, " +
          "you'll drown soon!\n"); break;
        case 2: tell_object(thing, "You are near drowning, " +
          "actually about to die...\n"); break;
        case 1: tell_object(thing,
          "You are drowning and at deaths door....\n");
      }
      continue;
    }
#ifdef DOWN_ROOM
    if (thing->query_prop(OBJ_I_WEIGHT) > thing->query_prop(OBJ_I_VOLUME))
    set_alarm(2.0, 0.0, &sink_down(({thing, DOWN_ROOM})));
#endif
#ifdef UP_ROOM
    if (thing->query_prop(OBJ_I_WEIGHT) < thing->query_prop(OBJ_I_VOLUME))
    set_alarm(2.0, 0.0, &float_up(({thing, UP_ROOM})));
#endif
  }

  if (sizeof(op) && !get_alarm(check_things_alarm))
      check_things_alarm = set_alarm(4.0, 0.0, check_things);
}

int
try_up()
{
  object  tp = TP;
  int     fat;

  fat = calc_basic();
    fat = 150 * (tp->query_prop(OBJ_I_WEIGHT) - tp->query_prop(CONT_I_WEIGHT))
              / (tp->query_prop(OBJ_I_VOLUME) - tp->query_prop(CONT_I_VOLUME) + 1) / fat;
  if (fat < 1) fat = 1;
  if (fat > 40) fat = 40;
  if (tp->query_fatigue() < fat)
  {
    write("You feel too tired to swim up with all the stuff you carry.\n");
    return 1;
  }
  if (tp->query_fatigue() < 3*fat)
  {
    write(BS("You feel rather tired. You hardly manage to swim up with all the stuff you carry.\n"));
  }
  tp->add_fatigue(-fat);
  if(fat > 20)
  {
    write("Swimming upwards with all the stuff you carry exhausts you.\n");
    return 0;
  }
  if(fat > 10)
  {
    write("Swimming upwards with all the stuff you carry makes you feel more tired.\n");
    return 0;
  }
  write("You swim up and feel a bit more tired.\n");
  return 0;
}

int
try_down()
{
  int fat;

  fat = calc_basic();
  fat = 150 * TP->query_prop(OBJ_I_WEIGHT) / TP->query_prop(OBJ_I_VOLUME) / fat;
  if (fat < 0) fat = 0;
  if (fat > 40) fat = 40;
  if (TP->query_fatigue() < fat)
  {
    write("You feel too tired to swim downwards with all the stuff you carry.\n");
    return 1;
  }
  if (TP->query_fatigue() < 3*fat)
  {
    write(BS("You feel rather tired. You hardly manage to swim down with all the stuff you carry.\n"));
  }
  TP->add_fatigue(-fat);
  if(fat > 20)
  {
    write("Swimming downwards with all the stuff you carry exhausts you.\n");
    return 0;
  }
  if(fat > 10)
  {
    write("Swimming downwards with all the stuff you carry makes you feel more tired.\n");
    return 0;
  }
  write("You swim down and feel a bit more tired.\n");
  return 0;
}

int
end_dive()
{
  write(BS("You finally get out of the water and you're very glad you can "
    + "breathe again - you were afraid you'll drown! You feel quite relieved. \n")); 
  return 0;
}

create_room()
{
  string dummy;
  int    i;

  set_short("Under water inside a well");
  set_long(BS("You are in a well under water. In the murky water you can hardly see your hand before your eyes.\n"));
  add_prop(ROOM_I_TYPE,ROOM_UNDER_WATER);
  add_prop(OBJ_I_CONTAIN_WATER, -1);
  add_prop(ROOM_I_INSIDE,1);
  sscanf(MASTER,"%sin_well%d%s",dummy,i,dummy);
  add_prop(ROOM_I_LIGHT,1 - i);
  set_noshow_obvious(1);
  set_alarm(2.0, 0.0, check_things);
  level = i;
  CREATEADD
}


do_feel()
{
  write("You feel around with your hands in the dark.\n");
#ifdef DOWN_ROOM
  write("There seems to be an exit leading down.\n");
#endif
#ifdef UP_ROOM
  write("There seems to be an exit leading up.\n");
#endif
  return 1;
}  

init()
{
  add_action("do_feel","feel");
  add_action("do_feel","touch");
  add_action("no_light","light");
  add_action("no_talk","'",1);
  add_action("no_talk","say");
  add_action("no_talk","shout");
  add_action("no_talk","scream");
  add_action("no_talk","whisper");
  add_action("no_talk","rsay");
  add_action("no_talk","grsay");
  add_action("no_talk","laugh");
  add_action("no_talk","whistle");
  if (level == 6) add_action(fake_search, "search");
  ::init();
}

no_light()
{
  write("You cannot light anything under water!\n");
  return 1;
}

int
no_talk(string str)
{
  string vb, *word;

  vb = query_verb();
  if(vb == "say" || vb == "rsay" || vb == "grsay" ||
    explode(vb,"")[0] == "'")
    vb = "speak";
  write("Don't be silly, you cannot " + vb + " under water!\n");
  if(TP->query_wiz_level())
  {
    write("Unless you are a wizard, of course!\n");
    return 0;
  }
  return 1;
}

int
fake_search(string arg)
{
    if (arg == "mud" ||
	arg == "ground" ||
	arg == "bottom")
    {
	write(TO->do_search(TP, arg));
	return 1;
    }
    return 0;
}

void
enter_inv(object ob, object old)
{
    if (!get_alarm(check_things_alarm))
        check_things_alarm = set_alarm(4.0, 0.0, check_things);

    ::enter_inv(ob, old);
}


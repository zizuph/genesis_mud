/* ctower/obj/colum.c is cloned by ctower/done1.c */
inherit "/std/object";
inherit "/d/Emerald/ctower/ctower_bits"; 

#include "/d/Emerald/lib/bit.h" 
#include <stdproperties.h>
#include "/d/Emerald/defs.h"
#include "../ctower.h"

void reward_player(object ob);
void give_torque(object ob);
void give_reward(object ob, int step);
void start_speach(object ob);

void
create_object()
{
  set_name("column");
  add_name("phase_quest_colum");
  set_long("This crystal column contains every color in "+
      "the spectrum swirling inside; it has a small square depression "+
      "on top, each side being 6 cm.\n");
  add_adj("crystal");
  add_prop(OBJ_I_WEIGHT, 10000);
  add_prop(OBJ_I_VOLUME, 10000);
  remove_prop(OBJ_I_VALUE);
  add_prop(OBJ_I_NO_GET, 1);
}

void transform()
{
  add_name("fin_column");
  add_adj("glowing");

  set_long("The crystal column is glowing softly and "+
      "you notice a small protrusion on the top.\n");
  add_item(({"protrusion"}), "The protrusion looks like the top of a " +
      "small cube.\n");   
}

int
fuse(string str)
{
  object cube, colum, *items;
 
  notify_fail(capitalize(query_verb()) + " what?\n");
  if (!strlen(str))
  {
    return 0;
  }

  if (parse_command(str, ({ }), "[crystal] 'cube' 'on' / " +
      "'into' / 'in' [the] [depression] [of] / [on] " +
      "'column'"))
  {
    if (!(cube = present("ctower_cube", this_player())))
    {
      return 0;
    }

    items = filter(all_inventory(environment()), &->id("fin_pillar"));

    if (sizeof(items) != 4) 
    {
      write("The cube pops back out and falls to the floor.\n");
      say(QCTNAME(this_player()) + " does something to the crystal " +
          "column and a cube drops to the floor.\n");

      cube->move(environment(), 1);

      return 1;
    }
 
    cube->remove_object();

    transform();
    start_speach(this_player());

    write("The cube fuses into place on the column, which starts to glow.\n");
    say(QCTNAME(this_player()) + " does something to the crystal column " +
        "and it starts to glow.\n");

    remove_object();
    return 1;
  }
 
  return 0;
}

void
init()
{
  add_action(fuse, "put");
  add_action(fuse, "place");
  add_action(fuse, "insert");
}

void
start_speach(object ob)
{
  if (ob && present(ob, environment()))
  {
    set_alarm(4.0, 0.0, &give_reward(ob, 0));
  }
}
 
void
give_reward(object ob, int step)
{
  if (!ob || !present(ob, environment()))
  {
    return;
  }

  switch (++step) 
  {
    case 1:
      tell_room(environment(),"As soon as the cube fuses to "+
          "the column, each of the four pillars emit a radiant light "+
          "corresponding to its color.  This rainbow "+
          "of colors is captured and redirected by the pyramids "+
          "atop the pillars, focusing the lights onto the facets "+
          "of the cube.  The focused light lances out in a " +
          "scintilating cascade of colors blossoming from the top "+
          "of the cube.\n");
          break;
     case 2:
       ob->catch_msg("The dazzling display begins "+
           "to sparkle and you begin to make out a crystal circlet "+
           "amongst the prismatic display.\n");
            break;
     case 3:
       ob->catch_msg("A melodic voice, with just a hint "+
           "of mischievousness, whispers in your mind:  You have proven "+
           "yourself both resourceful...and persistant.  I hereby judge "+
           "you worthy of the crystal torque.  It will be your "+
           "symbol of success in the Crystal Tower.\n");
            break;
      case 4:
        give_torque(ob);
        ob->catch_msg("The torque floats over and "+
            "settles comfortably around your neck.\n");
        tell_room(environment(), "A torque floats over and settles "+
            "comfortably around " + QTNAME(ob) + "'s neck.\n", ob);
        break;
      case 5:
        ob->catch_msg("The voice continues:  Know that "+
            "when the time is right you will be able to pass through yon "+
            "portal to seek further knowledge and adventure.  Also, if you "+
            "sing at either of the chandeliers you shall be transported "+
            "to the other.  This is the only egress currently available "+
            "to you.  It is also an easier means of reaching the portal "+
            "should the need arise.\n");
        break;
      case 6:
        ob->catch_msg("The voice says:  Good luck and good travels!\n");
        break;
      case 7:
        ob->catch_msg("With that the voice fades away, giggling merrily.  "+
            "The lighting drops back to the softly "+
            "glowing pillars and column, leaving you with a profound sense "+
            "of accomplishment and a smile on your face.  Good travels " +
            "indeed!\n");
        tell_room(environment(), "The lighting drops back to the softly "+
            "glowing pillars and column.\n", ob);
        break;
      default:
        reward_player(ob);
        return;
  }

  set_alarm(4.0, 0.0, &give_reward(ob, step));
}
 
void
reward_player(object ob)
{
  if (!ob || !present(ob, environment())) 
  {
    return;
  }

  if ((get_ctower_bits(ob) & 7) == 7)
  {
    return;
  }

  seteuid(geteuid());
  WRITE_LOG(QUEST_FILE, ob, "completed part six (final) of the crystal " +
      "tower.");
  WRITE_LOG(TOWER_LOG, ob, "completed part six (final).");

  SET_CBIT(ob, 3);

  ob->add_exp(XP_CRYSTAL_QUEST_6, 0);
  ob->catch_msg("You feel more experienced.\n");
}
 
void
give_torque(object ob)
{
  if (!ob || !present(ob, environment()))
  {
    return;
  }  
  
  if (get_ctower_bits(ob) <= 4)
  {
    return;
  }

  if (!present("phase_torque", ob))
  {
    setuid();
    seteuid(getuid());
    clone_object(CTOWER_OBJ + "torque")->move(ob, 1);
  }
}

#pragma save_binary

inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <std.h>


static void create_board();
#define MORE_OBJ "/std/board/board_more"

void
create_shire_room()
{
    object board;

    set_short("The Equestrian Lounge");
    set_long("This is the Equestrian Lounge, for members only. Plush chairs " +
            "surround a large fireplace in the center of the room. Beside each " +
            "chair is a small table to place your drink or pipe. Padded foot stools " +
            "are placed in front of each chair. Paintings depicting horses and " +
            "equestrians hang from the walls. On the east wall is a large board with " +
            "notes posted on it.\n");

    add_item(({"fire","fireplace"}),"A great fire burns in the large iron fireplace "+
            "in the center of the room. Its warmth makes you want to sit down and " +
            "relax after a long ride. You may stoke the fire if you need a bit more warmth.\n");

    add_item(({"cloth", "white cloth", "tables","table","chairs","chair","stool","stools","foot stools","foot stool"}),
            "Throughout "+
            "the room, tables and chairs surround the large iron fireplace in the " +
            "center of the room. The chairs are fine oak, plush with all the padding " +
            "an equestrian could dream of after a hard day's ride. The tables "+
            "are covered with clean white lace cloth. The padded foot stools look " +
            "very inviting.\n");

    add_item(({"wall","walls","east wall"}),"The walls are dark mahogany rough-hewn beams. "+
            "pictures cover the walls. A board is on the east wall.\n");

    add_item(({"ceiling", "beam", "beams"}),"The ceiling and walls are made from dark mahogany " +
            "rough-hewn beams.\n");

    add_item(({"painting", "paintings"}),
            "Various paintings of horses and their riders hang from the walls.\n");

    add_item(({"floor", "ground"}),"The floor is made from polished oak. It is shiney and spotless.\n");
 
    
    add_exit("foyer", "north",0);


    reset_shire_room();
}


int do_stand(string str)
{
  if(!str)
  {
    NF("Stand where?");
  }

  if (str != "up") {
      NF(CAP(query_verb())+" what? Up?\n");
      return 0;
   }

  if(TP->query_prop("_sitting"))
  {
    write("You stand up and leave your chair behind, feeling much more relaxed.\n");
    say(QCTNAME(TP)+" suddenly stands up.\n",TP);
    TP->remove_prop("_sitting");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
  }

  if(!TP->query_prop("_sitting") && !TP->query_prop("_standing"))
  {
    write("You are already standing! Perhaps you'd like to sit down and rest for a bit?\n");
    return 1;
  }
}


int do_climb(string str)
{
  if(!str)
  {
    NF("Climb where?");
  }
  switch(str)
  {
    if(!TP->query_prop("_standing"))
    {
      write("You are already standing on the ground.\n");
      return 1;
    }
    case "down": case "off table": case "down off table":
    case "down off the table":
      write("You climb down off the table.\n");
      SAY(" climbs down from the table.");
      TP->remove_prop("_standing");
      TP->remove_prop(LIVE_S_EXTRA_SHORT);
      break;
    case "up": case "walls": case "wall": case "up the wall":
      write("You try to climb, but find no purchase to do so.\n");
      SAY(" paws uselessly at the air trying to climb impossible "+
         "things.");
      break;
    case "table": case "on table": case "up table": case "up on table":
    case "the table": case "up on the table":
      write("Perhaps you wish to stand on the table?\n");
      break;
    default:
      write("Perhaps you wish to stand on the table or climb down "+
        "from it?\n");
      break;
  }
  return 1;
}

void leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);

   if(!objectp(to) || !objectp(ob))
      return;
  if(TP->query_prop("_sitting"))
  {
    write("You rise from your chair before leaving.\n");
    say(QCTNAME(TP) + " moves from "+HIS_HER(TP)+" position.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("_sitting");
  }
  if(TP->query_prop("_standing"))
  {
    write("You climb down from the table before leaving.\n");
    say(QCTNAME(TP) + " climbs down from "+HIS_HER(TP)+" position.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("_standing");
  }

}


init()
{
   add_action("do_sit","sit");
   add_action("do_stoke","stoke");
   add_action("do_stand","stand");
   add_action("do_stand","rise");
   ::init();
}


int do_sit(string str)
{
   if (!str) { NF("Sit where?\n"); return 0; }
   if(TP->query_prop("_sitting"))
   {
      write("But you are already sitting somewhere!\n");
      return 1;
   }
  if(TP->query_prop("_leaning") || TP->query_prop("_standing"))
  {
    write("Perhaps you should stand up first?\n");
    return 1;
  }
   switch(str)
   {
    case "down": case "in chair": case "chair": case "in the chair":
    case "in a chair": case "on chair": case "on a chair":
      write("You sit down in one of the chairs and rest your feet on the foot stool.\n");
      SAY(" falls back into the plush chair and kicks " +HIS_HER(TP)+ " feet up on the foot stool.");
      TP->add_prop("_sitting",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a chair");
      break;
    case "by fire": case "by the fire": case "the fire":
      write("You pull up a chair and sit by the fire.\n");
      SAY(" pulls up a chair and sits by the fire.");
      TP->add_prop("_sitting",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting by the fire");
      break;
    default:
      write("Perhaps you'd like to sit in a chair, "+
        "or by the fire?\n");
      break;
   }
   return 1;
}


int do_stoke(string str)
{
  if(!str) { NF("What do you want to stoke?"); }

  write("You stoke the fire, sending embers flying as the fire burns "+
     "brighter.\n");
  SAY(" stokes the fire sending sparks flying as the fire erupts "+
     "briefly.");
  return 1;
}


void
reset_shire_room()
{
    ::reset_shire_room();
    if (!present("board", TO))
    create_board();
}

static void
create_board()
{
    object board;

    if ((board = clone_object("/std/board")))
    {
    board->set_board_name("/d/Shire/bree/rooms/town/stable/club/board");
    board->set_num_notes(50);
    board->set_silent(1);
    board->set_show_lvl(0);
    board->set_remove_rank(WIZ_NORMAL);
    board->set_remove_str("Sorry, mortals are not allowed to remove notes.\n");
    board->move(TO);
    }
    return 0;
}

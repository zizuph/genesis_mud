/*
* The Rich Men's Club
*
* Coded by Conan assisted by Valeria Jan -95
* 
*/

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>

static void create_board();

mixed *rdata;
public void
reset_room()
{
  if (!present("board", TO))
    create_board();
}

public void
create_room()
{
  set_short("First floor of The Rich Men's Club");
  set_long(break_string(
    "You're standing on the first floor of 'The Rich Men's Club'. "+
    "This room is very relaxing and the impressive paintings on the "+
    "walls are perfect for hours of meditation. A fire is burning "+
    "in the fireplace, making the atmosphere even more cozy. There "+
    "are some stairs leading up to the second floor and down to the "+
    "ground floor where new titles can be obtained. To the north is "+
    "an exit out of the tower and there is a sign "+
    "on one of the walls. There's a golden statue standing in one "+
    "corner. It looks really impressive, not to mention how "+
    "valuable it must be, being made of solid gold.\n",60));
  
  add_item("fireplace","The fireplace is made of dark stones neatly "+
    "put together.\n");
  add_item("fire","The fire is sparkling and sends waves of warmth through "+
    "the room.\n");
  add_item("paintings","The paintings are skillfully painted by the local "+
    "artists of Ci'u'bori.\n");
  add_item("stairs","They are made of the same type of stone as the "+
    "fireplace. They are leading up and down.\n");
  add_item("sign","There's some readable text on it.\n");
  add_item("statue","It is a golden statue made to honour "+
           capitalize((RICH_ROOM)->query_president())+", the President "+
           "of this distinguished club. The statue is made of solid gold "+
           "and must weigh several tonnes. Not that you thought of "+
           "stealing it and take it to the nearest shop and sell it, "+
           "of course.\n");
  add_cmd_item("statue","get","You should be ashamed of yourself, "+
               "being so dishonest that you want to steal the statue of "+
               "our President. Shame on you!\n");
  add_cmd_item("statue","take","Greedy, eh? You aren't strong enough to "+
               "lift that statue, not to mention carry it away. And what "+
               "do you think "+capitalize((RICH_ROOM)->query_president())+
               " would do if you ran off with this statue? No, better "+
               "earn your money by fair play.\n");
  add_cmd_item("statue","kick","You begin to aim a kick at the statue, "+
               "but suddenly you think of the pain you will recieve in "+
               "your foot and forget the whole idea.\n");
  add_cmd_item("statue","smile","You smile at the statue of your president, "+
               capitalize((RICH_ROOM)->query_president())+".\n");
  add_cmd_item("statue","steal","You move towards the statue, ready to "+
               "run away with it to the nearest shop...easy money. Then "+
               "you realize what "+
               capitalize((RICH_ROOM)->query_president())+" will do "+
               "with you once understanding that you've sold the "+
               "statue. Better not play with death and earn the money "+
               "in a more honest way, like stealing it from children.\n");
  add_cmd_item("statue","kiss","You kiss the golden statue of "+
               capitalize((RICH_ROOM)->query_president())+". You feel "+
               "the taste of metal, the golden metal...\n");
  /*add_cmd_item("statue","",".\n");*/
  
  add_exit(GOLD + "path1","north","@@stairway");
  add_exit(RICHCLUB+"richprivate2","up","@@check");
  add_exit(RICHCLUB+"richclub","down",0);
  
  INSIDE;
  add_prop(OBJ_I_HAS_FIRE,1);

  rdata = ({});
  
  restore_object(RICH_OBJ);

  reset_room();
}

void
init()
{
  ::init();
  
  add_action("sign","read");
}

static void
create_board()
{
  object board;

  if ((board = clone_object("/std/board")))
  {
    board->set_board_name(RICHCLUB+"richboard");
    board->set_num_notes(23);
    board->set_anonymous(0);
    board->set_silent(1);
    board->set_show_lvl(1);
    board->set_remove_lvl(15);
    board->set_remove_str("Sorry but that is for high-level wizards only !\n");
    board->set_err_log(RICHCLUB+"richboard/board_err");
    board->move(TO);
  }
  return 0;
}

int
check()
{
  int lv;
  
  FIXEUID;

  lv = (RICH_ROOM)->query_level(TP);
  if (lv >= 4 || TP->query_wiz_level()>0) return 0;

  write("You don't think you are dressed up enough to enter that floor.\n");
  return 1;
}

int
sign(string s)
{
  string str;
  int i,n,v;
  
  if (s == "sign")
  {
    restore_object(RICH_OBJ);

    str = "\n";
    n = 0;
    str += "+-------------------------------------------"+
           "--------------------+\n| $            "+
           "         BIG SHOT Members                      $ |\n"+
           "+-------------------------------------------"+
           "--------------------+\n| ";
    
    v = 0;
    for (i = 0; i<sizeof(rdata); i++)
    {
      if (RMC_PAID(i) == 16 && RMC_PURCHASE(i) >= 4000 && !RMC_SUSPEND(i))
      {
        str = str + CAP(RMC_MEMBER(i));
        n = n + 1;
        v++;

        if (v == 4)
        {
          RNAMETAB;
          str += "|\n| ";
          v = 0;
        }
        else
          RNAMETAB;
      }
    }
    for (i = v; i < 4; i++)
      str += "\t\t";

    str += "|\n";
    n = 0;
    str += "+-------------------------------------------"+
           "--------------------+\n| $            "+
           "       FILTHILY Rich Members                   $ |\n"+
           "+-------------------------------------------"+
           "--------------------+\n| ";
    
    v = 0;
    for (i = 0; i<sizeof(rdata); i++)
    {
      if (RMC_PAID(i) == 16 && RMC_PURCHASE(i) < 4000 &&
          RMC_PURCHASE(i) >= 2000 && !RMC_SUSPEND(i))
      {
        str = str + CAP(RMC_MEMBER(i));
        n = n + 1;
        v++;

        if (v == 4)
        {
          RNAMETAB;
          str += "|\n| ";
          v = 0;
        }
        else
          RNAMETAB;
      }
    }
    for (i = v; i < 4; i++)
      str += "\t\t";


    str += "|\n";
    n = 0;
    str += "+-------------------------------------------"+
           "--------------------+\n| $            "+
           "     OBSCENELY Wealthy Members                 $ |\n"+
           "+-------------------------------------------"+
           "--------------------+\n| ";
    
    v = 0;
    for (i = 0; i<sizeof(rdata); i++)
    {
      if (RMC_PAID(i) == 16 && RMC_PURCHASE(i) < 2000 && !RMC_SUSPEND(i))
      {
        str = str + CAP(RMC_MEMBER(i));
        n = n + 1;
        v++;

        if (v == 4)
        {
          RNAMETAB;
          str += "|\n| ";
          v = 0;
        }
        else
          RNAMETAB;
      }
    }
    for (i = v; i < 4; i++)
      str += "\t\t";

    str += "|\n+-------------------------------------------"+
           "--------------------+\n";

    n = 0;
    str += "| $            "+
           "     EXTREMELY Wealthy Members                 $ |\n"+
           "+-------------------------------------------"+
           "--------------------+\n| ";
    
    v = 0;
    for (i = 0; i<sizeof(rdata); i++)
    {
      if (RMC_PAID(i) == 8 && !RMC_SUSPEND(i))
      {
        str = str + CAP(RMC_MEMBER(i));
        n = n + 1;
        v++;

        if (v == 4)
        {
          RNAMETAB;
          str += "|\n| ";
          v = 0;
        }
        else
          RNAMETAB;
      }
    }
    for (i = v; i < 4; i++)
      str += "\t\t";

    str += "|\n+-------------------------------------------"+
           "--------------------+\n";

    n = 0;
    str += "| $            "+
           "          WEALTHY Members                      $ |\n"+
           "+-------------------------------------------"+
           "--------------------+\n| ";
    
    v = 0;
    for (i = 0; i<sizeof(rdata); i++)
    {
      if (RMC_PAID(i) == 4 && !RMC_SUSPEND(i))
      {
        str = str + CAP(RMC_MEMBER(i));
        n = n + 1;
        v++;

        if (v == 4)
        {
          RNAMETAB;
          str += "|\n| ";
          v = 0;
        }
        else
          RNAMETAB;
      }
    }
    for (i = v; i < 4; i++)
      str += "\t\t";

    str += "|\n+-------------------------------------------"+
           "--------------------+\n";

    n = 0;
    str += "| $            "+
           "          AVERAGE Members                      $ |\n"+
           "+-------------------------------------------"+
           "--------------------+\n| ";
    
    v = 0;
    for (i = 0; i<sizeof(rdata); i++)
    {
      if (RMC_PAID(i) == 2 && !RMC_SUSPEND(i))
      {
        str = str + CAP(RMC_MEMBER(i));
        n = n + 1;
        v++;

        if (v == 4)
        {
          RNAMETAB;
          str += "|\n| ";
          v = 0;
        }
        else
          RNAMETAB;
      }
    }
    for (i = v; i < 4; i++)
      str += "\t\t";

    str += "|\n+-------------------------------------------"+
           "--------------------+\n";

    n = 0;
    str += "| $            "+
           "           POOR Members                        $ |\n"+
           "+-------------------------------------------"+
           "--------------------+\n| ";
    
    v = 0;
    for (i = 0; i<sizeof(rdata); i++)
    {
      if (RMC_PAID(i) == 1 && !RMC_SUSPEND(i))
      {
        str = str + CAP(RMC_MEMBER(i));
        n = n + 1;
        v++;

        if (v == 4)
        {
          RNAMETAB;
          str += "|\n| ";
          v = 0;
        }
        else
          RNAMETAB;
      }
    }
    for (i = v; i < 4; i++)
      str += "\t\t";

    str += "|\n+-------------------------------------------"+
           "--------------------+\n";

    if (TP->query_wiz_level()>0)
    {
        n = 0;
        str += "[ $            "+
               "     WIZ-INFO: WIZARD MEMBERS                  $ ]\n"+
               "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
               "~~~~~~~~~~~~~~~~~~~~+\n[ ";
        
        v = 0;
        for (i = 0; i<sizeof(rdata); i++)
        {
          if (RMC_PAID(i) > 16)
          {
            str = str + CAP(RMC_MEMBER(i));
            n = n + 1;
            v++;
    
            if (v == 4)
            {
              RNAMETAB;
              str += "]\n[ ";
              v = 0;
            }
            else
              RNAMETAB;
          }
        }
        for (i = v; i < 4; i++)
          str += "\t\t";

        str += "]\n+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
               "~~~~~~~~~~~~~~~~~~~~+\n";
       
        n = 0;
        str += "[ $            "+
               "    WIZ-INFO: SUSPENDED MEMBERS                $ ]\n"+
               "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
               "~~~~~~~~~~~~~~~~~~~~+\n[ ";
        
        v = 0;
        for (i = 0; i<sizeof(rdata); i++)
        {
          if (RMC_SUSPEND(i))
          {
            str = str + CAP(RMC_MEMBER(i));
            n = n + 1;
            v++;
    
            if (v == 4)
            {
              RNAMETAB;
              str += "]\n[ ";
              v = 0;
            }
            else
              RNAMETAB;
          }
        }
        for (i = v; i < 4; i++)
          str += "\t\t";

        str += "]\n+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
               "~~~~~~~~~~~~~~~~~~~~+\n";
    }
    write(str + "\n");
    say(QCTNAME(TP)+" reads the sign on the wall.\n");
    return 1;
  }
  return 0;
}

int
stairway()
{
  if(TP->query_wiz_level())
    return 0;

  write("You can't enter the island yet, since some parts of it isn't ready "+
    "to open yet. You don't want to spend your vacation in a working zone, "+
    "do you?\n");
  return 1;
}









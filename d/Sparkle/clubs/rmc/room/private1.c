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

mapping members;

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
           capitalize((RMCMASTER)->query_president())+", the President "+
           "of this distinguished club. The statue is made of solid gold "+
           "and must weigh several tonnes. Not that you thought of "+
           "stealing it to take it to the nearest shop and sell it, "+
           "of course.\n");
  add_cmd_item("statue","get","You should be ashamed of yourself, "+
               "being so dishonest that you want to steal the statue of "+
               "our President. Shame on you!\n");
  add_cmd_item("statue","take","Greedy, eh? You aren't strong enough to "+
               "lift that statue, not to mention carry it away. And what "+
               "do you think "+capitalize((RMCMASTER)->query_president())+
               " would do if you ran off with this statue? No, better "+
               "earn your money by fair play.\n");
  add_cmd_item("statue","kick","You begin to aim a kick at the statue, "+
               "but suddenly you think of the pain you will receive in "+
               "your foot and forget the whole idea.\n");
  add_cmd_item("statue","smile","You smile at the statue of your president, "+
               capitalize((RMCMASTER)->query_president())+".\n");
  add_cmd_item("statue","steal","You move towards the statue, ready to "+
               "run away with it to the nearest shop... Easy money. Then "+
               "you realize what "+
               capitalize((RMCMASTER)->query_president())+" will do "+
               "with you once understanding that you've sold the "+
               "statue. Better not play with death and earn the money "+
               "in a more honest way, like stealing it from children.\n");
  add_cmd_item("statue","kiss","You kiss the golden statue of "+
               capitalize((RMCMASTER)->query_president())+". You feel "+
               "the taste of metal, the golden metal...\n");
  /*add_cmd_item("statue","",".\n");*/
  
  add_exit(RMCROOMS+ "path1","north","@@stairway");
  add_exit(RMCROOMS+"private2","up","@@check");
  add_exit(RMCROOMS+"joining","down",0);
  
  INSIDE;
  add_prop(OBJ_I_HAS_FIRE,1);

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
    board->set_board_name(RMCVAR+"board");
    board->set_num_notes(23);
    board->set_anonymous(0);
    board->set_silent(1);
    board->set_show_lvl(1);
    board->set_remove_lvl(15);
    board->set_remove_str("Sorry but that is for high-level wizards only !\n");
    board->set_err_log(RMCLOG+"board_err");
    board->move(TO);
  }
  return 0;
}

int
check()
{
    FIXEUID;

    if ((RMCMASTER)->query_level(TP->query_real_name()) >= 4 ||
	TP->query_wiz_level() > 0)
	return 0;
    
    write("You don't think you are dressed up enough to enter that floor.\n");
    return 1;
}


int
select1(int n, mixed *elem)
{
    if (RMC_PAID(elem) == n)
	return 1;
    return 0;
}

int
select2(int n, int min, int max, mixed *elem)
{
    if (RMC_PAID(elem) == n &&
	RMC_PURCHASE(elem) >= min &&
	RMC_PURCHASE(elem) <= max)
	return 1;
    return 0;
}

int
sign(string s)
{

    mapping selection;
    string *list, str;
    int i, j, end;
    mixed *params =
	({
	    ({ "BIG SHOT Members", &select2(16, 4000, 0x7fffffff) }),
	    ({ "FILTHILY Rich Members", &select2(16, 2000, 3999) }),
	    ({ "OBSCENELY Wealthy Members", &select2(16, 0, 1999) }),
	    ({ "EXTREMELY Wealthy Members", &select1(8) }),
	    ({ "WEALTHY Members", &select1(4) }),
	    ({ "AVERAGE Members", &select1(2) }),
	    ({ "POOR Members", &select1(1) })
	});
  
    if (s == "sign")
    {
	members = (RMCMASTER)->all_members();

	for (i = 0; i < sizeof(params); i++)
	{
	    write(
		"|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n" +
		sprintf("$ %|72s $\n", params[i][0]) +
		"|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");
	    selection = filter(members, params[i][1]);
	    list = map(sort_array(m_indexes(selection)), &capitalize());
	    end = sizeof(list);
	    for (j = 0; j < end; j += 4)
		write(sprintf("| %|18s%|18s%|18s%|18s |\n",
			      list[j],
			      (j + 1 >= end ? "" : list[j + 1]),
			      (j + 2 >= end ? "" : list[j + 2]),
			      (j + 3 >= end ? "" : list[j + 3])));
	}
	write("|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");

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

    write("You can't enter the island yet, since some parts of it aren't ready "+
	  "to open yet. You don't want to spend your vacation in a working zone, "+
	  "do you?\n");
    return 1;
}









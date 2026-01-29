/*
 * common functions for HH guildroom
 * TAPAKAH, 10/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"

int check_enter(int member_only);
int passage_granted(string player);
void load_board(string bpath);

mapping listed;

int
check_enter(int access_level)
{
  if(TP->query_wiz_level())
    return 0;

  if(access_level) {
    listed = restore_map(HH_LISTED);
    if(access_level == HH_ACCESS_MEMBER)
      if(passage_granted(TP->query_name()) ||
	 TP->query_prop(HH_MEMBER) >= HH_ACCESS_MEMBER)
	return 0;
      else {
	write("Only guildmembers or granted are allowed in that direction!\n");
	return 1;
      }  
    else
      if(TP->query_prop(HH_MEMBER) >= HH_ACCESS_COUNCIL)
	return 0;
      else {
	write("Only council members are allowed in that direction!\n");
	return 1;
      }
  }
  return 0;
}

int passage_granted(string player)
{
  return(IN_ARRAY(player,listed["granted"]));
}

int passage_banned(string player)
{
  return(IN_ARRAY(player,listed["banned"]));
}

void
load_board(string bpath)
{
  object bb;
  
  bb = clone_object("/std/board");                                           
  
  bb->set_board_name(bpath);
  bb->set_num_notes(30);
  bb->set_silent(1);  /* Keep the mud tidy RW */
  bb->set_show_lvl(1); /* Wizards may see levels, Mercade. */
  bb->set_keep_discarded(0);
  bb->move(TO,1);

}

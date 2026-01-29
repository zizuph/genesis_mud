/**********************************************************************
 * - entrance.c                                                     - *
 * - Courtyard in the temple of Oenghus.                            - *
 * - Created by Damaris@Genesis 03/2006                             - *
 **********************************************************************/
#pragma strict_types
#include "../guild.h"
inherit GUILD_ROOM;
inherit FRUIT_PICK;
#include "laying.c"
#include <macros.h>
#include <stdproperties.h>

#define LOG_SIZE      25000
#define WRITE_NAME(o)   sprintf("%-11s", capitalize((o)->query_real_name()))

string
query_sign()
{
 return("      @>-@>-@>-@>-@>-@>-@>-@>-@>-@>-@>-  -<@-<@-<@-<@-<@-<@-<@-<@-<@-<@-<@\n"+
"      @                                                                  @\n"+
"      %                        Temple  Of  Oenghus                       %\n"+
"      @                                                                  @\n"+
"      @>----------------------------------------------------------------<@\n"+
"      @                                                                  @\n"+
"      %  It  is  here that many lovely    To  learn  the teachings that  %\n"+
"      @  females   have   gathered  to    Deheune  is  willing to share  @\n"+
"      %  learn  the  teachings  of the    you  only  need  to  seek her  %\n"+
"      @  alluring  Deheune.  She is so    out and  speak  with  her. If  @\n"+
"      %  favored  by  Oenghus  that He    you  decided  you  no  longer  %\n"+
"      @  allows  her  this  temple  in    wish  to  be a  temptress you  @\n"+
"      %  the  Otherworld  so  she  can    may speak with her  again and  %\n"+
"      @  worship  Him. He  also allows    ask  to  leave.   Temptresses  @\n"+
"      %  her  the pleasure of teaching    are  given  a  set of bangles  %\n"+
"      @  other  females  the  fine art    to  wear  and  may   exchange  @\n"+
"      %  of love  and  temptress ways.    them here.                     %\n"+
"      @                                                                  @\n"+
"      @>-@>-@>-@>-@>-@>-@>-@>-@>-@>-@>-  -<@-<@-<@-<@-<@-<@-<@-<@-<@-<@-<@\n\n");
}

void
create_khalakhor_room()
{
	set_xlong(({
	"A sign that is made of intricately laced grape "+
	"vines is posted here denotes a transformation into the "+
	"Otherworld. The sacred temple of Oenghus encompasses all.",
	"A bright green sign that is made of intricately laced grape "+
	"vines is posted here signifies a transformation into the "+
	"Otherworld. The sacred temple of Oenghus encompasses all.",
	"A simple sign that is made of intricately laced grape vines "+
	"is posted here represents a transformation into the Otherworld. "+
	"The sacred temple of Oenghus encompasses all.",
	"A sign that is made of intricately laced grape vines "+
	"is posted here symbolizes a conversion into the Otherworld. "+
	"The sacred temple of Oenghus encompasses all.",
	"A sign that is made of intricately laced grape vines is "+
	"posted here designates an alteration into the Otherworld. The "+
	"sacred temple of Oenghus encompasses all.",}));
  
	config_room("solemn entrance");
	set_up_fruits(0, ({"grape", "raspberry", "blackberry"}));
	add_my_desc(lay_desc, this_object());	
	add_item(({"west", "southeast", "northeast", "northwest", "southwest",}),
	"There is intricately woven grape vines in that direction.\n");
	add_item(({"south", "north"}),
	"The courtyard continues in that direction.\n");
	add_item(({"east"}),
	"The garden continues in that direction.\n");
	
	add_item(({"sign"}), query_sign);
	add_npc(NPC + "deheune", 1);
	add_exit("court2", "north");
	add_exit("court6", "south");
	add_exit("garden", "east");
	add_exit("court1", "northwest");
	add_exit("court5", "southwest");	

	add_fail("auto", "Grape vines block your way.\n");

}
/**********************************************************************
 * - Function name: do_read                                         - *
 * - Description:   If a player wants to know what instructions can - *
 * -                be used.                                        - *
 * - Arguments:     str - string, hopefully "sign"                  - *
 * - Returns:       1/0                                             - *
 **********************************************************************/
int
do_read(string str)
{
	if (str != "sign")
	{
		notify_fail("Read what?\n");
		return 0;
	}
	write(query_sign());
	return 1;
}

void
hook_smelled(string str)
{
	if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
	{
		write("The air is filled with sweet berries and "+
		"succulent grapes.\n");
		return;
	}
   
} 
int
do_enter(string str)
{
	if (member_array(str, ({"samorgan", "village", "world"})) == -1)
	{
		notify_fail("Enter what? The village perhaps?\n");
		return 0;
	}
	write("You step forward and leave the Otherworld.\n");
	say(QCTNAME(this_player())+" vanishes.\n");
	this_player()->move_living("M", "/d/Khalakhor/sw_speir/samorgan/room/vil0510", 1, 0);
	say(QCTNAME(this_player())+" suddenly appears.\n");
	return 1;
}

public void
init()
{
	::init();
	init_fruit();
	init_lay();
	add_action("do_read",   "read");
	add_action("do_enter", "enter");
	add_action("do_enter", "return");
}

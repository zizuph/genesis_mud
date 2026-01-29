inherit "/std/object";

#include "defs.h"
#include <wa_types.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <living_desc.h>
#include <ss_types.h>
#include <adverbs.h>

#define DEPTH 1  /*  How many rooms away the shout will be heard.  */
 
/* **************************************************************************
 * Prototype
 */

void
create_object()
{
    	set_name("horn");
	set_adj("brass");
	add_adj("rusty");
	set_long("This horn looks quite rusty, and is rather large.\n"+
		"It is made of brass and is quite heavy. It is a plain\n"+
		"horn and it can most likely only make one tone. It is\n"+
		"inserted with some strange letters. It might be possible\n"+
		"to blow the horn and play a merry tune with it.\n");

	add_prop(OBJ_I_WEIGHT, 2000);
	add_prop(OBJ_I_VALUE, 250 + random(120));
	add_prop(OBJ_I_VOLUME, 800);

	add_item("letters",
		"There are some writings here which will come later.\n");

}

init()
{   /* 30 */
    ::init();
	add_action("do_blow", "blow");
}

do_blow(string str)
{
    string where;    
    object *rooms;
    object troom;
    int il;
	
    if(str!="horn")
	return notify_fail("Blow what? The Lumberjack?\n");
	
	if(!(sscanf(file_name(ENV(TP)),"/d/Shire/moria/%s", where)==1))
	{
		write("You blow the horn with all your cunning might.\n"
			+"Only a terrible sound can be heard from the\n" 
			+"horn, so you decide to stop the blowing.\n");
/* 50 */
		say(QCTNAME(TP)+" blow a horn with all "+HIS_HER(TP)+" cunning\n"
			+"might, but produces only a terrible sound. "+HE_SHE(TP)+" decide\n"
			+"to stop the blowing and put the horn down again.\n");
	return "";	
		
/* 70 */}
	else
	if(sscanf(file_name(ENV(TP)),"/d/Shire/moria/%s", where)==1)
	{	
	write("You grab a deep breath and start blowing the horn.\n"
		+"Shouting and screaming throughout the tunnels can\n"
		+"be heard, swords clinging against mail, clubs against\n"
		+"walls. All these noises are coming closer to your part\n"
		+"of the tunnel.\n");
	say(QCTNAME(TP)+" grabs a deep breath and starts blowing the horn.\n"
		+"Voices and shouting can be heard throughout the tunnels.\n"
		+"Swords clinging against mail, clubs against walls. The noise\n"
		+"are enclosing this place, with great speed.\n");
	return "";
	}
	if (!(troom = environment(this_player())))
	return 0;
	
	rooms = FIND_NEIGHBOURS(troom, DEPTH);
	
	for (il = 0; il < sizeof(rooms); il++)
	tell_room(rooms[il], "Someone " + file_name(this_object()) +
/* 92 */"sounds a horn which echo throughout the tunnels.\n", this_player());
	return 1;	
}

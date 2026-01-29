/**************************************************/
/*    Secret Room in Oak  Room of Icewall Castle  */
/*               Coded by Stevenson  */
/**************************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit ICEINROOM;

int star = 0, dome = 0;

void 
reset_icewall_room() 
{
    if (!dome) 
    {
	dome = 1;
	tell_room(TO,"There is a shimmer of an indigo haze "
		  + "over the surface of the stone as a "
		  + "crystalline dome appears.\n");
    }
    
    if (!star) 
    {
	star = 1;
	tell_room(TO,"There is a bright flash of intense light from "
		  + "underneath the dome.\n");
    }
}

void 
create_icewall_room()
{
    set_short("Secret Room");
    set_long("\nYou are standing in a secret room in the castle. In the"
	     + " middle of the room is a hexagonal stone that looks strangely"
	     + " magical. There are strange symbols carved into"
	     + " the rock walls which look very old. You get the feeling"
	     + " that this place is very powerful."
	     + "\n");
    
    add_item(({"wall","walls"}),"The rocky walls are adorned with "
	     + "ancient symbols.\n");
    add_item("dome","@@dome_desc");
    add_item("stone","@@stone_desc");
    add_item("symbols",
	     "You attempt to read the symbols but they are written in a "
	     + "language so ancient that even the most learned scholar "
	     + "wouldn't be able to translate them.\n");
    add_item("star","@@star_desc");
    
    
    add_exit(ICE_CAST1_R + "secret1.c", "west");
    
    reset_icewall_room();
}

void 
init()
{
    ::init();
    ADD("lift_dome", "lift");
    ADD("lift_dome", "remove");
    ADD("get_star",  "get");
    ADD("get_star",  "take");
}

int 
lift_dome(string str)
{
    NF("Lift what?\n");
    if (str != "dome" && !dome)
      return 0;
    write("You lift the dome off of the stone.\n"
	  + "As you set it down, it fades and then vanishes.\n");
    dome = 0;
    say(QCTNAME(TP)+" reaches towards the stone and is enveloped in a "
	+ "bluish haze.\n");
    TP->add_prop(LIVE_S_EXTRA_SHORT,
		 " glowing with a deep indigo light");
    write("You begin to glow with a deep indigo light.\n");
    set_alarm(120.0,0.0,"unlight",TP);
    return 1;
}

int 
get_star(string str)
{
    NF("Get what?\n");
    if (str != "star" || dome || !star)
      return 0;
    clone_object(ICE_CAST_O + "star.c")->move(this_player());
    write("You carefully lift the star from the stone.\nSuddenly the room "
	  + "begins to rumble.\n");
    say(QCTNAME(TP)+" reaches towards the stone.\nThe ground begins to "
	+ "rumble.\n");
    tell_room(ICE_CAST1_R+"oak_room","There is a rumbling sound to the east.\n");
    tell_room(ICE_CAST1_R+"secret1","There is a rumbling sound to the east.\n");
    star = 0;
    return 1;
}
string 
stone_desc()
{
    if (dome) 
    {
	write("Covering the stone is a crystalline dome. ");
	if (star)
	  write("There appears to be something underneath. ");
	return "\n";
    }
    if (star)
      return "Resting upon the stone is a star.\n";
    return "You see a hexagonal stone.\n";
}

string 
star_desc() 
{
    if (!dome && star)
      return "You see a beautiful crystalline star "
	+ "radiating its own inner light.\n";
    return "What star?\n";
}

void 
unlight(object who) 
{
    who->catch_msg("You aren't glowing anymore.\n");
    tell_room(E(who),QCTNAME(TP)+" is no longer glowing.\n",who);
    who->remove_prop(LIVE_S_EXTRA_SHORT);
}

string 
dome_desc() 
{
    if (dome)
      return "The dome seems to both capture and reflect light at the "
	+ "same time.\n";
    return "What dome?\n";
}

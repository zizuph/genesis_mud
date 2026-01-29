/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

int melted, lance;

/* prototype */
void reset_icewall_room();
int give_lance();

void
create_icewall_room() 
{
    set_short("Large Block of Ice");
    set_long("You stare in awe at the sight before you. An enormous block of "
	     + "ice is here. Its size takes up the enormity of the room. "
	     + "There is a single beam of sunlight streaking down from the "
	     + "ceiling of the room and resting upon the surface of the ice. "
	     + "The only way out is back from where you came."
	     + "\n");
    
    add_item(({"ice","block"}),"@@show_ice");
    add_item("dragon","It is a large Silver Dragon.  It appears to be "
	     + "quite frozen.\n");
    add_item(({"rider","knight"}), "@@show_rider");
    add_item("hand","@@show_hand");
    add_item(({"lance","dragonlance"}),"@@show_lance");
    add_item(({"beam","light","sun","sunlight"}),
	     "The beam of sunlight is resting on the ice directly above "
	     + "the knight's hand.\n");
    add_item(({"ceiling","crack","hole"}),
	     "The ceiling is high above you and coming through a small "
	     + "hole is a single beam of sunlight.\n");
    
    add_exit(QUEST+"to_drag_3","west");
    
    reset_icewall_room();
}

void
reset_icewall_room() 
{
    melted = 0;
    lance = 1;
    /* Someone already did the quest this timeframe */
    // We allow it to be solved  more than once per life time.
    //    if (QUERY_QUEST("dragonlance"))
    //  lance = 0;
}

void
init() 
{
    ADA("focus");
    ADA("melt");
    ADD("get", "get");
    ADD("get", "take");
    ::init();
}

int
focus(string str) 
{
    object lens = P("mag_lens",TP);
    if (objectp(lens) && !melted &&
	(str == "beam with lens" || str == "light with lens"))
    {
	write("You focus the beam of light with your magnifying lens. "
	      + "The tiny point of light begins to melt the ice above the "
	      + "knight's hand.\n");
	set_alarm(6.0, 0.0, "all_melted", lens);
	say(QCTNAME(TP) + " begins to melt the ice.\n");
	return 1;
    }
    if (str == "light" || str == "beam")
      NF("Focus " + str + " with what?\n")
    else if (!objectp(lens))
      NF("You don't seem to have anything to focus light with.\n")
    else
      NF("Focus what?\n");
    return 0;
}

int
melt(string str)
{
    NF("How exactly do you plan to do that?\n");
    return 0;
}

int
all_melted(object lens)
{
    if (lance)
      write("The ice is now melted away, uncovering the dragonlance.\n");
    else
      write("The ice is now melted away, revealing an empty hand.\n");
    melted = 1;
    lens->melt(TO, TP);
    return 1;
}

int
get(string str) 
{
    if ((str == "lance" || str == "dragonlance") && lance)
    {
	if (melted)
	  give_lance();
	else
	  write("You reach up and grasp the dragonlance.  As you "
		+ "try to retrieve it, you find it is firmly held in the "
		+ "Knight's grasp.\n");
	return 1;
    }
    return 0;
}

void
bring_knights(object player)
{
  object knight;
  object squire;
  knight = clone_object("/d/Krynn/common/warfare/npcs/knight/rose");
  squire = clone_object("/d/Krynn/common/warfare/npcs/knight/squire");
  knight->move(TO, 1);
  squire->move(TO, 1);
  tell_room(TO, "A group of knights arrive!\n");
  knight->command("shout By the Measure! Do not let "+HIM(player)+" escape! "+HE(player)+" has the lance!");
  player->catch_tell("The knights charge you!\n");
  tell_room(TO, "The knights charge "+QTNAME(player)+".\n", player);
  knight->attack_object(player);
  squire->attack_object(player);
}

int
give_lance() 
{
    object lan;
    if(TP->query_prop("_player_i_lance_quest"))
    {
	lance = 0;
	seteuid(getuid(TO));
	lan = clone_object(ICE_CAST_O + "lance");

	if (!lan->move(TP))
	{
	  if(TP->query_alignment() > 0)
	  {
	    write("Sensing your inherent goodness, the Knight relaxes his grip "
		  + "and you retrieve the dragonlance!\n");
	  }
	  else
	  {
	    write("You break off one of the Knight's fingers forcing his grip "+
                  "to loosen, and you manage to retrieve the dragonlance!\n");
	    bring_knights(TP);
	  }
	  say (QCTNAME(TP) + " fetches the dragonlance.\n");
	}
	else
	{
	    lan->move(TO, 1);
	    if(TP->query_alignment() > 0)
	    {
	      write("Sensing your inherent goodness, the Knight relaxes his grip "
		    + "but the dragonlance is too heavy and you drop it on the floor!\n");
	    }
	    else
	    {
	      write("You break off one of the Knight's fingers forcing his grip "+
		    "to loosen, it is too heavy for you though, and you drop it.\n");
	      bring_knights(TP);
	    }
	    say(QCTNAME(TP) + " fetches the dragonlance but drops it!\n");
	    set_alarm(15.0,0.0,"remove_lance",lan);
	}
	return 1;
    }
    say(QCTNAME(TP) + " attemps to retrieve the dragonlance and fails.\n");
    write("You try to retrieve the dragonlance but it just won't work. Most " +
	  "likely you missed something along the way.\n");
    return 0;
}

void
remove_lance(object lan)
{
    if (P(lan,TO))
    {
	tell_room(TO, "Suddenly, the lance vanishes completely!\n");
	lan->remove_object();
    }
}

string 
show_ice() 
{
    string ice = "You see a large block of ice. Frozen within it is a "
      + "dragon and its rider.";
    if (melted) ice = ice + " You can see a hand sticking out of the "
      + "ice.";
    say(QCTNAME(TP) + " studies the block of ice intently.\n");
    return ice + "\n";
}

string 
show_hand() 
{
    string hand;
    if (lance) 
      return "The knight's hand is holding a dragonlance.\n";
    return "The knight's hand is empty.\n";
}

string 
show_lance() 
{
    if (lance) 
      return "The dragonlance is quite a formidable weapon "
	+ "easily able to pierce the thickest of dragonhides.\n";
    return "What?\n";
}

string 
show_rider() 
{
    string rider = "The rider was apparently a mighty Solamnic Knight "
      + "before his unfortunate demise. ";
    if (lance) 
      rider = rider + "He is clutching something in his hand.";
    return rider + "\n";
}

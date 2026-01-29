/* Flotsam sidestreet by Gorr 8.12.96 */
/* Navarre December 14th 2009, changing to place talisman in player
 * instead of on the ground, since there is an annoyance of having it
 * destroyed by the fire or acid by the draconians.
 */



#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_OUT;
#define SEEN_VARIDIAN "_player_has_seen_varidian"

object drac1;
object d2, d3, d4, d5;
object lamp_object;
int lamp_is = 1;

void
reset_flotsam_room()
{
    if(!objectp(drac1))
    {
	drac1 = clone_object(FNPC + "gsivak_l.c");
	drac1->move(TO);
    }
    if(!objectp(d2))
    {
	d2 = clone_object(KNPC + "sivak");
	d2->set_color("green");
	if (!random(2))
	{
	  clone_object("/d/Ansalon/taman_busuk/sanction/obj/weapon/sabre")->move(d2, 1);
	  d2->command("unwield all");
	  d2->command("wield sabre");
	  d2->command("wield all");
	}
	d2->move(TO);
    }
    if(!objectp(d3))
    {
	d3 = clone_object(KNPC + "kapak");
	d3->set_color("green");
	d3->move(TO);
    }
    if(!objectp(d4))
    {
	d4 = clone_object(KNPC + "kapak");
	d4->set_color("green");
	d4->move(TO);
    }
    if(!objectp(d5))
    {
	d5 = clone_object(KNPC + "baaz");
	d5->set_color("green");
	d5->move(TO);
    }
}


create_flotsam_room()
{
    set_short("Small, hidden courtyard");
    set_long("@@long_descr");

    add_item(({"house","houses","buildings","deserted houses"}),
      "Tall, stone houses look lifeless and deserted. \n");
    add_item(({"windows","window","dark windows"}),
      "No sign of life could be seen in this dark windows. \n");
    add_item(({"wall","brick wall"}),
      "The brick wall is blocking the street to the north. " +
      "It is covered with dirt and moss but it still looks solid. \n");
    add_item(({"moss","dirt"}),"The wall is covered with slimy moss. " +
      "It could hinder your movement but the wall still looks climbable. \n");
    add_item("bricks","The bricks are hardly visible from under the moss. \n");
    add_item(({"piles","furniture","loot","things"}),
      "All around this place you can see heaps of looted " +
      "things, boxes and furniture. Unfortunately most of them look rather " +
      "useless. It seems the draconians have already sold all " +
      "valuable things. " +
      "Probably they treated it as a part-time job. \n");
    add_item(({"fire","campfire","fireplace"}),"The campfire is still lit. Someone was " +
      "using it recently to roast a piece of meat. \n");
    add_item(({"piece of meat","meat","piece","food"}),
      "It doesn't look fresh, nor tasty. \n");
    add_item("log","Within the fire, a log burns.\n");

    add_item(({"box","boxes"}),"@@boxsearch");

    add_cmd_item(({"wall","brickwall"}),({"climb","up"}),"@@climbwall");


    /* Added by Ashlar 19 May 98: Since the only way in seems to be climbing
    a wall, I disallow steeds. If I am wrong, the bug log will tell. :) */
    add_prop(ROOM_I_NO_ALLOW_STEED,1);

    set_tell_time(90);
    add_tell("Burning logs and furniture emit sparkling noises. \n");
    add_tell("You hear a woman cry from one of the houses. " +
        "Unfortunately you can't say from which one. \n");
    add_tell("The flames dance along the log. \n");
    add_tell("A big, fat rat looks from behind the boxes, sniffing " +
        "for food.\n");    
    add_tell("Something moves in one of the windows. Or maybe it is " +
        "just your imagination. \n");
    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + "You stand in the small courtyard. Tall, deserted " +
    "houses are blocking the view from all sides except north, where you " +
    "see a brick wall. This place seems to be used as storage for piles " +
    "of furniture and other things looted by a band of draconians. In the " +
    "middle there is a fireplace and some pieces of food are lying around. "
    + season_descr() + "\n";

}

string
climbwall()
{
    if(TP->query_skill(SS_CLIMB) < (20 + random(20)))
    {
	write("You try to climb the wall but your foot slips on the moss " +
	  "and you land hardly on the ground. \n");
	say(QCTNAME(TP) + " tries to climb the wall but slips on the moss " +
	  "and lands hardly next to your feet. \n");
	return "";
    }
    write("You successfully climb the brickwall and jump on the other side. \n");
    TP->move_living("up the brickwall",FROOM + "gstreet3",1,0);

    return "";
}

void
reset_lamp()
{
    lamp_is = 1;
}

string
boxsearch()
{
    if (!objectp(drac1))
    {
	say(QCTNAME(TP) + " rummages though the boxes.\n");
	/*
		if(lamp_is == 1 )
		{
		    lamp_object = clone_object(FOBJ + "lamp.c");
		    lamp_object->move(TO);
		    lamp_is = 0;
		    return"After a moment you find a strange lamp.\n";
		}
	*/
	if(TP->query_prop(SEEN_VARIDIAN) && lamp_is == 1)
	{
	    lamp_object = clone_object(FOBJ + "wyvern_talisman");
	    lamp_object->move(TP);
	    lamp_is = 0;
            set_alarm(6000.0, 0.0, "reset_lamp");
	    return"After a moment you find a feathered talisman and quickly pocket it!\n";
	}
	else
	    return"You search through the boxes but surprisingly found " +
	    "nothing. \n";
    }
    else
    {
	drac1->command("kill " + TP->query_real_name());
	d2->command("kill " + TP->query_real_name());
	d3->command("kill " + TP->query_real_name());
	d4->command("kill " + TP->query_real_name());
	d5->command("kill " + TP->query_real_name());
	return "The draconians prevent you from reaching the " +
	"boxes.\n";
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
        start_room_tells();
}

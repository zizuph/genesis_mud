/* 
 * Laethorian Spa and Body
 *
 * Sanitary piercings of ear and nose only.
 *
 * Mortis 01.2006
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <money.h>
#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <formulas.h>
#include <options.h>
#include "/d/Kalad/common/noble/arm/ring.h"

inherit NOBLE_ROOMBASE;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES)

object piercer;

string
query_to_jail()
{
  return "west";
}

void check_more(object ob);

void
reset_palan_room()
{
	if (!piercer)
	{
		piercer = clone_object(NOBLE + "living/piercer");
		piercer->arm_me();
		piercer->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("Piercery inside Laethorian Spa and Body");
    LONG("The piercery is bright and clean with tall, silver braziers "
	+ "burning in each of its four corners.  The small room is completely "
	+ "done in polished, translucent white marble with a curving marble "
	+ "and glass counter forming a semi-circle in the center.  A marble "
	+ "sign is propped upon the counter.\n");

	ITEM(({"brazier", "braziers", "silver brazier", "silver braziers", "fire",
		"fires"}), "Tall, silver braziers stand in the four corners of this "
	+ "foyer.  Small fires burn in each, their light reflecting off the "
	+ "polished marble of the ceiling and shedding even light across the "
	+ "floor and walls.\n");
	ITEM(({"corner", "corners"}), "Standing in each of the corners and "
	+ "providing light are tall, silver braziers.\n");
	ITEM(({"wall", "walls", "ceiling", "floor", "floors"}), "The floor, "
	+ "walls and ceiling are of translucent white marble polished to a "
	+ "gleaming shine.\n");
	ITEM(({"sign", "marble sign"}), "An etched marble sign sits propped "
	+ "upon the counter of marble and glass.  You may read it.\n");
	ITEM(({"counter", "marble counter", "glass counter", "semi-circle",
		"jewelry"}),
	  "The counter in the center of the room has a base and back of "
	+ "polished, translucent white marble with a glass front and top for "
	+ "displaying jewelry.  Behind it, the perforian provides service and "
	+ "sells jewelry.  You may peruse it.\n");

	EXIT(NOBLE + "spa", "west", 0, 0);
	
	CMD(({"case", "display", "counter", "glass", "jewelry"}), "peruse",
		"@@peruse_display");
	CMD("sign", "read", "@@read_sign");
	CMD("sign", "mread", "@@mread_sign");

	reset_palan_room();
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the marble sign upon the counter.\n");
	write("The sign reads...\n");
	cat(NOBLE + "obj/spapierce.txt", 1, 60);
	return 1;
}

public int
mread_sign()
{
	string file = NOBLE + "obj/spapierce.txt";

	say(QCTNAME(TP) + " studies the marble sign upon the counter.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));
	return 1;
}

int
peruse_display()
{
	write("The semi-circular display contains single rings, pairs of rings, "
	+ "single studs, and pairs of studs for piercings.  They come in "
	+ "copper, brass, bronze, steel, silver, white-silver, gold, platinum, "
	+ "and ironwood and can be fitted with alexandrite, amber, corundum, "
	+ "crystal, diamond, emerald, fire-opal, garnet, jacinth, jade, "
	+ "jasper, onyx, opal, pearl, ruby, sapphire, star-ruby, topaz, "
	+ "or turquoise.\n");
	say(QCTNAME(TP) + " peruses the jewelry in the semi-circular display "
	+ "counter.\n");
	return 1;
}

int
order(string str)
{
    object buy_ob;
    string for_c, get_c, change, *rorder, gem, metal;
    int *result, m_res, price, no_gem;
    int val;
    seteuid(getuid());
    write_file("/d/Krynn/solamn/palanthas/log/pierce_order_log",
		this_player()->query_real_name()+" -> Verb: "+query_verb()
		+" Arg: "+str+"\n");
    NF("Order what?\n");
    if(!str)
	return 0;
    rorder = explode(str," ");
    NF("Order what?\n");
    if(sizeof(rorder) > 4 || sizeof(rorder) < 2)
	return 0;
    NF("Order "+rorder[0]+" what?\n");
    if(rorder[1] != "ring" && rorder[1] != "rings" && rorder[1] != "stud" &&
      rorder[1] != "studs")
	return 0;
    if(sizeof(rorder) == 2)
	no_gem = 1;
    if(no_gem == 0)
    {
	NF("Order "+rorder[0]+" "+rorder[1]+" with what?\n");
	if(rorder[2] != "with")
	    return 0;
	if(rorder[3] == "")
	    return 0;
    }
    switch(rorder[0])
    {
    case "copper":
	val = 2;
	metal = "copper";
	break;
    case "brass":
	val = 6;
	metal = "brass";
	break;
    case "bronze":
	val = 12;
	metal = "bronze";
	break;
    case "steel":
	val = 16;
	metal = "steel";
	break;
    case "silver":
	val = 24;
	metal = "silver";
	break;
    case "white-silver":
	val = 36;
	metal = "white-silver";
	break;
    case "gold":
	val = 144;
	metal = "gold";
	break;
    case "platinum":
	val = 1728;
	metal = "platinum";
	break;
    case "ironwood":
	val = 2856;
	metal = "ironwood";
	break;
    default:
	NF("Sorry, we don't have the metal type '"+rorder[0]+"'.\n");
	return 0;
    }
    if(no_gem == 0)
    {
	switch(rorder[3])
	{
	case "turquoise":
	    val = val + 144;
	    gem = "turquoise";
	    break;
	case "jasper":
	    val = val + 288;
	    gem = "jasper";
	    break;
	case "amber":
	    val = val + 576;
	    gem = "amber";
	    break;
	case "garnet":
	    val = val + 1152;
	    gem = "garnet";
	    break;
	case "onyx":
	    val = val + 1728;
	    gem = "onyx";
	    break;
	case "jade":
	    val = val + 2304;
	    gem = "jade";
	    break;
	case "crystal":
		val = val + 2440;
		gem = "crystal";
		break;
	case "pearl":
	    val = val + 2880;
	    gem = "pearl";
	    break;
	case "topaz":
	    val = val + 3456;
	    gem = "topaz";
	    break;
	case "opal":
	    val = val + 4032;
	    gem = "opal";
	    break;
	case "emerald":
	    val = val + 4608;
	    gem = "emerald";
	    break;
	case "sapphire":
	    val = val + 5184;
	    gem = "sapphire";
	    break;
	case "ruby":
	    val = val + 5760;
	    gem = "ruby";
	    break;
	case "jacinth":
	    val = val + 6336;
	    gem = "jacinth";
	    break;
	case "corundum":
		val = val + 6772;
		gem = "purple corundum";
		break;
	case "fire opal":
		val = val + 6801;
		gem = "fire opal";
		break;
	case "diamond":
	    val = val + 6912;
	    gem = "diamond";
	    break;
	case "alexandrite":
		val = val + 7012;
		gem = "alexandrite";
		break;
	case "star-ruby":
		val = val + 10250;
		gem = "star-ruby";
		break;
	
	default:
	    NF("Sorry, we don't have a gem-type '"+rorder[3]+"'.\n");
	    return 0;
	}
    }
    if(rorder[1] == "ring")
	buy_ob = clone_object(NOBLE + "obj/single_ring");
    if(rorder[1] == "rings")
    {
		val = val * 2;
		buy_ob = clone_object(NOBLE + "obj/pair_rings");
    }
    if(rorder[1] == "stud")
	buy_ob = clone_object(NOBLE + "obj/single_stud");
    if(rorder[1] == "studs")
    {
		val = val * 2;
		buy_ob = clone_object(NOBLE + "obj/pair_studs");
    }
    buy_ob->set_ring_metal(metal);
    if(no_gem == 0)
	buy_ob->set_ring_metal(gem,1);
    price = val;
    buy_ob->set_ring_value(val);

/*    result = pay(price, this_player(), for_c, 0, 0, get_c);

    if (sizeof(result)==1)
	{
		buy_ob->remove_object();
		return 0;
    }
*/
	if (!MONEY_ADD(TP, -price))
	{
		piercer->command("say You do not have the coin to pay for that!");
		piercer->command("frown");
		buy_ob->remove_object();
		return 1;
	}
    TP->catch_msg("You pay the tailor " + price + " copper coins.\n");

    if (buy_ob->move(this_player()))
	{
		write("Too heavy for your load.\n");
		say(QCTNAME(TP) + " drops something.\n");
		buy_ob->move(environment(this_player()));
    }
    else
	{
		write("You get yourself a "+buy_ob->short()+".\n");
		say(QCTNAME(TP) + " orders a "+buy_ob->short()+".\n");
    }
    return 1;
}

int
unpierce(string s)
{
    object ob;
    switch(s)
    {
    case "left ear":
	NF("You don't have a pierced left ear.\n");
	if(!TP->query_prop(KALAD_RING_EAR_LEFT))
	    return 0;
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_EAR_LEFT) == 2)
	    return 0;
	NF("You don't have a pierced left ear.\n");
	ob = present("pierce1",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    case "right ear":
	NF("You don't have a pierced right ear.\n");
	if(!TP->query_prop(KALAD_RING_EAR_RIGHT))
	    return 0;
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_EAR_RIGHT) == 2)
	    return 0;
	NF("You don't have a pierced right ear.\n");
	ob = present("pierce2",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    case "both ears":
	NF("You don't have both ears pierced.\n");
	if(!TP->query_prop(KALAD_RING_EAR_BOTH))
	    return 0;
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_EAR_BOTH) == 2)
	    return 0;
	NF("You don't have have both ears pierced.\n");
	ob = present("pierce3",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    case "nose":
	NF("You don't have a pierced nose.\n");
	if(!TP->query_prop(KALAD_RING_NOSE))
	    return 0;
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_NOSE) == 2)
	    return 0;
	NF("You don't have a pierced nose.\n");
	ob = present("pierce4",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    case "left eyebrow":
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_EYEB_LEFT) == 2)
	    return 0;
	NF("You don't have a pierced left eyebrow.\n");
	if(!TP->query_prop(KALAD_RING_EYEB_LEFT))
	    return 0;
	ob = present("pierce5",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    case "right eyebrow":
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_EYEB_RIGHT) == 2)
	    return 0;
	NF("You don't have a pierced right eyebrow.\n");
	if(!TP->query_prop(KALAD_RING_EYEB_RIGHT))
	    return 0;
	ob = present("pierce6",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break; 
    case "both eyebrows":
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_EYEB_BOTH) == 2)
	    return 0;
	NF("You don't have both eyebrows pierced.\n");
	if(!TP->query_prop(KALAD_RING_EYEB_BOTH))
	    return 0;
	ob = present("pierce7",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    case "tongue":
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_TONGUE) == 2)
	    return 0;
	NF("You don't have a pierced tongue.\n");
	if(!TP->query_prop(KALAD_RING_TONGUE))
	    return 0;
	ob = present("pierce8",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    case "lip":
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_LIP) == 2)
	    return 0;
	NF("You don't have a pierced lip.\n");
	if(!TP->query_prop(KALAD_RING_LIP))
	    return 0;
	ob = present("pierce9",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    case "left nipple":
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_NIP_LEFT) == 2)
	    return 0;
	NF("You don't have a pierced left nipple.\n");
	if(!TP->query_prop(KALAD_RING_NIP_LEFT))
	    return 0;
	ob = present("pierce10",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    case "right nipple":
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_NIP_RIGHT) == 2)
	    return 0;
	NF("You don't have a pierced right nipple.\n");
	if(!TP->query_prop(KALAD_RING_NIP_RIGHT))
	    return 0;
	ob = present("pierce11",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;    
    case "both nipples":
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_NIP_BOTH) == 2)
	    return 0;
	NF("You don't have a both nipples pierced.\n");
	if(!TP->query_prop(KALAD_RING_NIP_BOTH))
	    return 0;
	ob = present("pierce12",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;    
    case "navel":   
	NF("Please remove all rings from body part.\n");
	if(TP->query_prop(KALAD_RING_NAVEL) == 2)
	    return 0;
	NF("You don't have a pierced navel.\n");
	if(!TP->query_prop(KALAD_RING_NAVEL))
	    return 0;
	ob = present("pierce13",TP);
	if(!ob)
	    return 0;
	ob->remove_object();
	check_more(TP);
	break;
    default:
	NF("There is no such body part "+s+".  You can have the following "
	+ "unpierced here:  left ear, right ear, both ears, nose, left eyebrow, "
	+ "right eyebrow, both eyebrows, tongue, lip, left nipple, right nipple, "
	+ "both nipples, or navel.\n");
	return 0;
    }
    write("You request an unpiercing from the Perforian.\n");
    write("He waves a short, white wand over your piercing and the hole "
	+ "closes miracuously!\n");
    say(QCTNAME(TP) + " requests an unpiercing from the Perforian.\n");
	say("The Perforian waves a short, white wand over " + QCTNAME(TP) + "'s "
	+ "piercing and the hole closes miracuously!\n");
    return 1;
}

void
init()
{
    ::init();
    ADA("unpierce");
    ADA("order");
}

void
check_more(object ob)
{
    int i;
    object *inv,temp;
    inv = all_inventory(ob);
    for(i=0;i<sizeof(inv);i++)
    {
	if(inv[i]->query_prop(KALAD_RING_HOLE))
	{
	    temp = clone_object(MASTER_OB(inv[i]));
	    inv[i]->remove_object();
	    temp->move(ob);
	    break;
	}
    }
}

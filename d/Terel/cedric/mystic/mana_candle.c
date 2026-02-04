#include "/d/Terel/common/terel_std_rec.h"
#include "/d/Terel/common/terel_std_rec.h"
inherit "/std/object.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define TP              this_player
#define TO              this_object
#define MYS_SKILL	130001

object			the_room;
int			amount_burned = 0;
int			lit_flag = 0;

void
init()
{
    ::init();
    add_action("do_light", "light");
    add_action("do_unlight", "extinguish", 1);
}

string
how_much()
{
    switch(amount_burned)
    {
	case 0: return "The candle has never been lit.";
	case 1: return "The candle is almost whole.";
	case 2: return "The candle has burned perhaps a fourth of the way down.";
	case 3: return "The candle is about half gone.";
	case 4: return "Most of the candle has burned away.";
	case 5: return "The candle is almost gone; only a stub remains.";
    }
}

string
is_lit()
{
    if (lit_flag) 
	return "The candle is burning; a wonderful odor fills this place.";
    else 
	return "The candle is not lit.";
}

string
short_is_lit()
{
    if (lit_flag)
	return " (burning)";
    else
	return "";
}

void
create_object()
{
    set_name("candle");
    add_name("mys_mana_candle");
    add_adj(({"healing", "blue", "thin"}));
    set_short("thin blue candle@@short_is_lit@@");
    set_long(BS("This delicate taper is a deep azure in color. "
    + "A strip of metallic foil, bearing a strange seal resembling an intricate "
    + "silver star, is wrapped around the bottom of the candle. The wax smells "
    + "somehow of mystery and knowledge, of ancient texts and mystic runes.\n"
    + "@@how_much@@\n@@is_lit@@\n"));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
}

void
burn_0()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		if (room_list[i]->query_skill(MYS_SKILL))
		{
		    room_list[i]->add_mana(10);
		    tell_object(room_list[i], BS("The pungent incense of the candle fills your "
		    + "senses and clears your mind.\n"));
		}
		else 
		{
		    tell_object(room_list[i], BS("The pleasant smell of the candle fills your "
		    + "senses, but there is something unsatifying about it. It is as if "
		    + "an insight, a certain clarity of mind, is hovering within your reach,"
		    + " but is not to be granted to you today.\n"));
		}
	    }
	call_out("burn_1", 30);
    }
}

void
burn_1()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		if (room_list[i]->query_skill(MYS_SKILL))
		{
		    room_list[i]->add_mana(10);
		    tell_object(room_list[i], BS("The pungent incense of the candle fills your "
		    + "senses and clears your mind.\n"));
		}
		else 
		{
		    tell_object(room_list[i], BS("The pleasant smell of the candle fills your "
		    + "senses, but there is something unsatifying about it. It is as if "
		    + "an insight, a certain clarity of mind, is hovering within your reach,"
		    + " but is not to be granted to you today.\n"));
		}
	    }
	call_out("burn_2", 30);
    }
}

void
burn_2()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		if (room_list[i]->query_skill(MYS_SKILL))
		{
		    room_list[i]->add_mana(10);
		    tell_object(room_list[i], BS("The pungent incense of the candle fills your "
		    + "senses and clears your mind.\n"));
		}
		else 
		{
		    tell_object(room_list[i], BS("The pleasant smell of the candle fills your "
		    + "senses, but there is something unsatifying about it. It is as if "
		    + "an insight, a certain clarity of mind, is hovering within your reach,"
		    + " but is not to be granted to you today.\n"));
		}
	    }
	call_out("burn_3", 30);
    }
}

void
burn_3()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		if (room_list[i]->query_skill(MYS_SKILL))
		{
		    room_list[i]->add_mana(10);
		    tell_object(room_list[i], BS("The pungent incense of the candle fills your "
		    + "senses and clears your mind.\n"));
		}
		else 
		{
		    tell_object(room_list[i], BS("The pleasant smell of the candle fills your "
		    + "senses, but there is something unsatifying about it. It is as if "
		    + "an insight, a certain clarity of mind, is hovering within your reach,"
		    + " but is not to be granted to you today.\n"));
		}
	    }
	call_out("burn_4", 30);
    }
}

void
burn_4()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		if (room_list[i]->query_skill(MYS_SKILL))
		{
		    room_list[i]->add_mana(10);
		tell_object(room_list[i], BS("The pungent incense of the candle fills your "
		    + "senses and clears your mind.\n"));
		}
		else 
		{
		    tell_object(room_list[i], BS("The pleasant smell of the candle fills your "
		    + "senses, but there is something unsatifying about it. It is as if "
		    + "an insight, a certain clarity of mind, is hovering within your reach,"
		    + " but is not to be granted to you today.\n"));
		}
	    }
	call_out("burn_5", 30);
    }
}

void
burn_5()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		if (room_list[i]->query_skill(MYS_SKILL))
		{
		    room_list[i]->add_mana(10);
		    tell_object(room_list[i], BS("The pungent incense of the candle fills your "
		    + "senses and clears your mind.\n"));
		}
		else 
		{
		    tell_object(room_list[i], BS("The pleasant smell of the candle fills your "
		    + "senses, but there is something unsatifying about it. It is as if "
		    + "an insight, a certain clarity of mind, is hovering within your reach,"
		    + " but is not to be granted to you today.\n"));
		}
	    }
	tell_room(environment(TO()), "The candle gutters and dies.\n"
	+ "The powerful odor soon disperses.\n");
	remove_object();
    }
}

int
do_light(string str)
{
    object  ob;

    notify_fail("Light what?\n");    
    if (!parse_command(str+" ", environment(TP()), "%o", ob))
	return 0;
    if (ob!=TO())
	return 0;
    if (lit_flag)
    {
	notify_fail("But the candle is already lit!\n");
	return 0;
    }
    if (living(environment(TO())))
    {
	notify_fail(BS("You sense somehow that the sacred candle's benefits are "
	+ "to be shared, and that it must not be lit in "
	+ "your hands alone.\n"));
	return 0;
    }
    lit_flag = 1;
    write(BS("You light the thin blue candle, and the air soon fills with a "
    + "powerful fragrance. Inhaling the deep, elusive aroma, you soon clear "
    + "your mind of distractions and focus your willpower.\n"));
    say(BS(QCTNAME(TP())+" lights the thin blue candle, and the air soon fills with a "
    + "wonderful fragrance. Inhaling the deep, elusive aroma, you soon clear "
    + "your mind of distractions and focus your willpower.\n"));
    amount_burned++;
    add_prop(OBJ_M_NO_GET, "The sacred flame is not to be moved while burning.\n");
    call_out("burn_"+amount_burned, 30);
    return 1;
}

int
do_unlight(string str)
{
    object  ob;

    notify_fail("Extinguish what?\n");    
    if (!parse_command(str+" ", environment(TP()), "%o", ob))
	return 0;
    if (ob!=TO())
	return 0;
    if (!lit_flag)
    {
	notify_fail("But the candle is not lit!\n");
	return 0;
    }
    lit_flag = 0;
    write(BS("Regretfully, you extinguish the candle, and the powerful odor soon "
    + "disperses.\n"));
    say(BS(QCTNAME(TP())+" extinguishes the candle, and the powerful odor soon "
    + "disperse.\n"));
    add_prop(OBJ_I_NO_GET, 0);
    return 1;
}

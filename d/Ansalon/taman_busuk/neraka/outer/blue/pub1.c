/* Ashlar, 7 May 97 - The Hanged Knight tavern */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

inherit OUTER_IN;
inherit "/d/Ansalon/lib/pub";

object ob, barkeeper = 0;

/* the Knight who is the current center of attention */
object knight = 0;
/* two draconians */
object d1 = 0, d2 = 0;
/* three mercenaries */
object m1 = 0, m2 = 0, m3 = 0;

void
reset_neraka_room()
{
	/* the draconians have been drinking and are rather brave */
    if (!d1)
    {
    	d1 = clone_npc(NNPC + "bozak","blue");
        if (!knight)
            d1->add_prop(LIVE_S_EXTRA_SHORT, " leaning against the wall");
        d1->clear_chat();
        d1->clear_act();
        d1->set_stat_extra(SS_DIS, 20);

    }
    if (!d2)
    {
    	d2 = clone_npc(NNPC + "kapak","blue");
        d2->add_prop(LIVE_S_EXTRA_SHORT, " sitting at a table");
        d2->clear_chat();
        d2->clear_act();
        d2->set_stat_extra(SS_DIS, 20);
    }
    if (!m1)
    	m1 = clone_npc(NNPC + "mercenary","blue");
    if (!m2)
    	m2 = clone_npc(NNPC + "mercenary","blue");
    if (!m3)
    	m3 = clone_npc(NNPC + "mercenary","blue");
    if (!barkeeper)
    {
        barkeeper = clone_npc(NNPC + "hk_barkeep");
	set_barkeeper(barkeeper);
    }
}

void
create_neraka_room()
{
    set_short("dirty tavern in the Blue Quarter");
    
    set_long("@@long_descr@@");
    add_item(({"sign","large sign"}),
        "The sign consists of a crudely drawn picture of " +
        "a man in Solamnian armour hanging upside down from a rope " +
        "tied to his feet. Below the picture are the words: 'The " +
        "Hanged Knight' and a pricelist:\n\n@@read_pricelist@@");
    add_cmd_item(({"sign","large sign","pricelist","menu"}),({"read"}),
        ({"The Hanged Knight\n\n@@read_pricelist@@"}));
    add_item(({"table","tables"}),"The tables are dirty and sticky " +
        "from spilled beer.\n");
    add_item(({"counter","long counter"}),"It is a long, heavily scratched " +
        "counter, from behind which the barkeeper serves the drinks.\n");
    add_item(({"patrons","patron"}),"The patrons of this place are mainly " +
        "dragonarmy soldiers and human workers.\n");
    add_item_inside();
    remove_item("walls");
    add_item("walls","The north wall holds a large sign.\n");
    remove_item("north wall");
    add_item("north wall","A large sign hangs on the north wall, above " +
        "the counter.\n");
    add_item("fire","The fire adds warmth and light to the room.\n");
    add_item(({"fireplace","large fireplace"}),"The fireplace is made " +
        "of stone, and there is a fire burning there.\n");
    add_prop(OBJ_I_HAS_FIRE, 1);

    add_exit(NOUTER+"blue/b12","out","@@try_to_leave");

    add_drink_object(({"squire","squires","bloody squire","bloody squires"}),
		     NOBJ + "drink/bsquire",
		     55);

    add_drink_object(({"vingaard","vingaards","vingaard under rocks","rocks"}),
		     NOBJ + "drink/ving",
		     110);

    add_drink_object(({"spirit","spirits","sword spirit","sword spirits"}),
		     NOBJ + "drink/spirit",
		     220);
		     
    reset_room();
}

int
try_to_leave()
{
    if ((knight == TP) && (d1))
    {
    	d1->command("say Oh no you don't!");
        tell_room(TO,"The " + d1->short() + " stops " + QCTNAME(knight) + 
            " from leaving.\n", knight);
        write("The " + d1->short() + " stops you from leaving.\n");
        return 1;
    }
    else
    {
    	write("You step out of the tavern and into the market square.\n");
        return 0;
    }
}

string
read_pricelist()
{
    return "+--------------------------------+\n" +
	   "| Bloody Squire           55 cc  |\n" +
	   "| Vingaard under rocks    110 cc |\n" + 
	   "| Sword Spirit            220 cc |\n" +
	   "+--------------------------------+\n";
}

string
long_descr()
{
    string str;

    str = "You are standing inside a small, dirty tavern in the Blue " +
        "Quarter of Neraka. There are some tables here, and a long " +
        "counter along the north wall. On the wall behind the counter " +
        "hangs a large sign. A fire is burning in a large fireplace. ";

    if (knight && (E(knight) == TO))
    {
    	str += "The room is dead quiet, and all the patrons are watching " +
            (knight == TP ? "you" : knight->query_the_name(TP)) + 
            " intently. ";
    }
    else
    {
    	str += "The air is filled with the loud noises of drunken " +
            "conversation, and the patrons seem to be enjoying " +
            "their drinks. ";
    }
    return str + "\n";
}

void
drac_knight_interact(int i)
{
    if (!d1 || !d2 || !knight || (E(knight) != TO))
        return;
    if ((d1->query_enemy() && (i<21))|| d2->query_enemy())
        return;

    switch(i)
    {
    	case 0:
            d1->command("emote straightens up.");
            d1->remove_prop(LIVE_S_EXTRA_SHORT);
            break;
        case 3:
            d1->command("emote sneers: What have we here? A Knight " +
                "in this place?");
            break;
        case 4:
            if (d2)
                d2->command("chuckle evil");
            break;
        case 7:
            d1->command("say to " + knight->query_real_name() + 
                " What's the matter? Didn't you see the sign?");
            break;
        case 9:
            if (d2)
                d2->command("shout Hey, we could put it up there instead " + 
                    "of the sign!");
            break;
        case 11:
            d1->command("grin");
            break;
        case 14:
            d1->command("say We'd have to Measure it, and put it on the " +
                "rack if it is too short.");
            break;
        case 16:
            if (d2)
                d2->command("laugh drunk");
            break;
        case 17:
            if (m2)
                m2->command("emote laughs so hard he chokes on his beer.");
            break;
        case 20:
            d1->command("shout Enough of this. Let's get it!");
            d1->command("kill " + knight->query_real_name());
            break;
        case 21:
            if (d2)
                d2->command("emote rises and draws its sword.");
            break;
        case 22:
            if (d2)
                d2->command("assist");
            break;    
        case 23:
            return;
    }
    set_alarm(2.5,0.0,&drac_knight_interact(i+1));
}

void
knight_enter(object obj)
{
    if (!obj || knight || (E(obj) != TO))
        return;

    obj->catch_msg("All conversation stop as you enter the room, and every " +
        "patron turn to watch you.\n");
    tell_room(TO,"All conversation stop as every patron turn to watch " +
        QTNAME(obj) + ".\n", obj);
    knight = obj;
    set_alarm(4.0,0.0,&drac_knight_interact(0));
}

void
enter_inv(object obj,object from)
{
    ::enter_inv(obj,from);
    if (!obj->query_npc() && (obj->query_guild_name_occ() ==
        "Solamnian Knights") && (!knight) && !obj->query_invis())
    {
    	set_alarm(1.0,0.0,&knight_enter(obj));
    }
}

void
knight_leave(object obj)
{
    if(knight)
    	tell_room(TO,"The coversation starts up again as the patrons return " +
		  "to their drinks.\n");
    if(d1)
        d1->add_prop(LIVE_S_EXTRA_SHORT, " leaning against the wall");
    knight = 0;
}

void
leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);
    if (obj == knight)
        set_alarm(1.0,0.0,&knight_leave(obj));
}

/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    init_pub();
}

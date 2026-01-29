/*  /d/Avenir/common/outpost/paint_shop.c
 *   Paints Sybarun Sigils on Armours. 
 *   By Lilith, March 2022
 *      Based on:
 *     /d/Gondor/minas/rooms/paintq.c
 *     Painting room for the painter in Minas Tirith.                   
 *     Coded by Gwyneth, August 27, 2000
 *  Updates:
 */

inherit "/d/Avenir/common/outpost/fort_base";

#include <cmdparse.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Avenir/common/outpost/paint_shop.h"

#define OBJ_M_NO_ALTER "_obj_m_no_alter"

public string read_sign();

object painter;

public string
read_sign()
{
    cat("/d/Avenir/common/outpost/help/paint.txt");
	return "";
}

public void
reset_fort_room()
{
    if (!objectp(painter))
    {
        painter = clone_object(PAINTER);
        painter->equip_me(0);
        painter->move(this_object(), 1);
    }
}

nomask void
create_fort_room()
{
	add_exit("forge_entry", "down");
	
    set_short("the Good As New shop");
    set_long("Very well-lighted with lots of lamps, this place of "+
	    "business is vibrant with colour. "+
        "There is a long table running down the center with "+
        "splotches and smears of paint staining the surface. "+ 
	    "Known as 'Good As New', this shop is where the dwarven "+
        "guards of the fortress come to get the paint on their weapons "+
        "and armours updated to keep them looking pristine. "+
        "While the proprietor appears to be quite busy, she might "+
        "have time to do a small job for you.\n"+
        "   There is a sign prominently posted on the wall.\n");
		
    add_prop(ROOM_M_NO_STEAL, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 50);  // so trade can happen
	
    add_cmd_item( ({"sign", "poster"}), "read", read_sign);
    add_item( ({"sign", "poster"}), read_sign);
    add_item(({"stone table", "sturdy table", "quartzite table",
        "table", "work table", "center table", "long table"}), 
		"The pale quartzite table shows paint stains " +
        "but few scratches or chips. The stone must be very hard "+
        "and strong.\n");
    add_item(({"stains", "paint stains", "splotches", "smears"}), 
	    "Red, geen, purple and grey paint is splattered all over "+
		"the surface of the work table.\n");
    add_item(({"several lamps", "lamps", "lamp", "light"}), "The " +
        "lamps have been placed in strategic spots to make best use " +
        "of their light.\n");
    add_item(({"wall", "walls", "lime plaster", "plaster"}), 
        "The stone walls have been painted with lime plaster, "+
        "giving them bright white colour that .\n");
    add_item(({"bucket", "buckets", "paint", "buckets of paint",
        "paint buckets"}), "The buckets contain 4 colours: "+
        "grey, green, red, and purple.\n");
    add_item(({"brushes", "brush"}), "These are fairly ordinary " +
        "looking brushes, made of bicorn hair instead of horse "+
        "hair like most painters brushes are.\n");
    add_item("chair", "The chair is made of stone, and padded " +
        "with a comfortable and cushion.\n");
    add_item(({"ceiling", "floor", "ground", "up", "down"}), 
        "It is stone. It is all stone. Splotches of color break "+
        "up the monotony of stone.\n");
		
	add_exit_views();
    add_fort_room();
		
    reset_fort_room();
}

public int
start_paint(string str)
{
    int mon, paint_index;
    string mess, *arr, paint;
    mixed *paint_me;

    if (!present(painter, this_object()))
    {
        notify_fail("There is nobody here to assist you.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Paint <what> <which> colour?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, all_inventory(this_player()),
      " %i %s ", paint_me, paint))
    {
        notify_fail("You don't seem to have that "+
        "item with you.\n");
        return 0;
    }

    paint_index = member_array(paint, COLOUR);
    if (paint_index == -1)
    {
        notify_fail("That colour is not an option at this time.\n");
        return 0;
    }

    paint_me = NORMAL_ACCESS(paint_me, 0, 0);

    if (sizeof(paint_me) > 1)
    {
        notify_fail("Only one item at a time may be painted.\n");
        return 0;
    }

    if (!sizeof(paint_me))
    {
        notify_fail("Paint <which> item <what> colour?\n");
        return 0;
    }

    if (mess = paint_me[0]->query_prop(OBJ_M_NO_GIVE))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("You can't give the " +
                LANG_THESHORT(paint_me[0]) +" away to be painted.\n");
        }

        return 0;
    }

    if (mess = paint_me[0]->query_prop(OBJ_M_NO_DROP))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("You can't seem to do that.\n");
        }

        return 0;
    }

    if (paint_me[0]->query_prop(HEAP_I_IS))
    {
        notify_fail(capitalize(LANG_THESHORT(paint_me[0])) +
            " cannot be painted over.\n");
        return 0;		
    }	
	
    if (paint_me[0]->query_lock())
    {
        notify_fail(capitalize(LANG_THESHORT(paint_me[0])) +
            " cannot be painted over.\n");
        return 0;
    }

    if (mess = paint_me[0]->query_prop(OBJ_M_NO_ALTER))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail(capitalize(LANG_THESHORT(paint_me[0])) +
            " cannot be painted over.\n");
        }

        return 0;
    }
/* Not bothering with the gem thing. Really inconvenient.--Lilith

    if (paint != "grey" && 
	!painter->allow_paint(this_player()->query_real_name(), paint))
    {
        painter->command("whisper to " + OB_NAME(this_player()) +
            " You haven't given me the right minerals for " +
            paint + " paint yet. Ask me ["+ paint +" paint] "+
            " to find out which ingredients I am missing. ");
        return 1;
    }
*/
    arr = paint_me[0]->query_prop(OBJ_S_PAINTED);
    if (sizeof(arr) > 0)
    {
        if (arr[2] == paint)
        {
            notify_fail(capitalize(LANG_THESHORT(paint_me[0])) +
                " is already painted " + COLOUR[paint_index] + ".\n");
            return 0;
        }
        else if (painter->query_marker())
        {
            painter->command("emote looks rather busy. It " +
                "appears that you must wait your turn.\n");
            return 1;
        }
        else
        {
            mon = ((paint_me[0]->query_prop(OBJ_I_VOLUME)) / 9);
			if (mon < 144) mon = 144;
            if (mon > 1728) mon = 1728;

            if (!MONEY_ADD(this_player(), -(mon)))
            {
                notify_fail("You can't afford to have " +
                    LANG_THESHORT(paint_me[0]) + " repainted.\n");
                return 0;
            }
            write("You pay " + mon + " copper to " +
                painter->query_the_name(this_player()) + ".\n");
            painter->add_paint(this_player(), paint_me[0], paint_index ,1);
            return 1;
        }
    }
    if (painter->query_marker())
    {
        painter->command("emote looks rather busy. It " +
            "appears that you must wait your turn.\n");
        return 1;
    }

    mon = ((paint_me[0]->query_prop(OBJ_I_VOLUME)) / 9);
    if (mon < 144) mon = 144;	
    if (mon > 1728) mon = 1728;
    if (!MONEY_ADD(this_player(), -(mon)))
    {
        notify_fail("You can't afford to have " +
            LANG_THESHORT(paint_me[0]) + " painted.\n");
        return 0;
    }

    write("You pay " + mon + " copper to " +
        painter->query_the_name(this_player()) + ".\n");

    painter->add_paint(this_player(), paint_me[0], paint_index, 0);
    return 1;    
}

public int
inquire(string str)
{
    int i, sz, mon;
    mixed *arm;
    string *arr, place;

    if (!strlen(str))
    {
        notify_fail("Inquire about which item?\n");
        return 0;
    }

    str = lower_case(str);
    if (!parse_command(str, this_player(), 
      "[about] [the] [price] [of] [the] [a] %i", arm))
    {
        notify_fail("You don't seem to have that piece of gear on you.\n");
        return 0;
    }

    arm = NORMAL_ACCESS(arm, 0, 0);

    sz = sizeof(arm);

    if (!sz)
    {
        notify_fail("Inquire about which item?\n");
        return 0;
    }

    if (!present(painter, this_object()))
    {
        notify_fail("There is nobody here to help you.\n");
        return 0;
    }

    i = -1;
    while(++i < sz)
    {
		/* She can paint lots of things, but not everything.
		 * No coins, herbs, guild obs, quest rewards, etc
		 */
        if (
		  arm[i]->query_prop(HEAP_I_IS) ||
          arm[i]->query_prop(OBJ_M_NO_DROP) ||
          arm[i]->query_prop(OBJ_M_NO_GIVE) ||
          arm[i]->query_lock())
        {
            painter->command("say I don't paint things like that " +
                arm[i]->short() + ".");
        }
        else
        {
            mon = ((arm[i]->query_prop(OBJ_I_VOLUME)) / 9);
            if (mon < 144) mon = 144;
            if (mon > 1728) mon = 1728;

            painter->command("say It would cost you " + (mon) +
                " copper to paint the " + arm[i]->short() + ".");
            if (sizeof(arm[i]->query_prop(OBJ_S_PAINTED)) > 0)
            {
                painter->command("say It would cost you " + (mon * 2) +
                    " copper to restore the " + arm[i]->short() + ".");
            }
        }
    }

    return 1;
}

public void
add_solv(object arm)
{
    string *adjs = arm->query_adjs();
    string *nadjs = arm->query_prop(OBJ_S_PAINT_INFO)[3];

    if (!painter->solv_tells(arm, this_player()))
    {
        return;
    }
 
    arm->move(painter, 1);
    write("You hand your " + arm->short() + " to " +
        painter->query_the_name(this_player()) + ".\n");
    say(QCTNAME(this_player()) + " hands " + this_player()->query_possessive() +
        " " + arm->short() + " to " + QTNAME(painter) + ".\n");
    write("You request to have your " + arm->short() +
        " restored to its previous unpainted state.\n");
    arm->set_long(arm->query_prop(OBJ_S_PAINT_INFO)[0]);
    arm->set_short(arm->query_prop(OBJ_S_PAINT_INFO)[1]);
    arm->set_pshort(arm->query_prop(OBJ_S_PAINT_INFO)[2]);
    arm->remove_adj(adjs);
    arm->add_adj(nadjs);
    arm->remove_name("_sybarus_painted");
    arm->remove_prop(OBJ_S_PAINTED);
    arm->remove_prop(OBJ_S_PAINT_INFO);
    arm->add_prop(OBJ_M_NO_ALTER, 1);
    return;
}

public int
start_solv(string str)
{
    int mon;
    string mess, *arr;
    mixed *paint_me;

    if (!present(painter, this_object()))
    {
        notify_fail("There is nobody here to assist you.\n");
        return 0;
    }

    if (painter->query_marker())
    {
        painter->command("say I am busy with another job now.");
        notify_fail("It appears you must wait your turn.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Restore which armour?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, all_inventory(this_player()),
      " %i ", paint_me))
    {
        notify_fail("You don't seem to have that item.\n");
        return 0;
    }

    paint_me = NORMAL_ACCESS(paint_me, 0, 0);

    if (sizeof(paint_me) > 1)
    {
        notify_fail("Only one item at a time may be restored.\n");
        return 0;
    }

    if (!sizeof(paint_me))
    {
        notify_fail("Restore which item?\n");
        return 0;
    }

    if (mess = paint_me[0]->query_prop(OBJ_M_NO_GIVE))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("You can't give the " +
                LANG_THESHORT(paint_me[0]) + " away to be restored.\n");
        }

        return 0;
    }

    if (mess = paint_me[0]->query_prop(OBJ_M_NO_DROP))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("Oddly enough, you can't seem to do that.\n");
        }

        return 0;
    }

    arr = paint_me[0]->query_prop(OBJ_S_PAINTED);
    if (!sizeof(arr))
    {
        notify_fail("That item can't be restored.\n");
        return 0;
    }
    mon = ((paint_me[0]->query_prop(OBJ_I_VOLUME)) / 9);
    if (mon < 144) mon = 144;
    if (mon > 1728) mon = 1728;
    if (!MONEY_ADD(this_player(), -(mon)))
    {
        notify_fail("You can't afford to have " +
            LANG_THESHORT(paint_me[0]) + " restored.\n");
        return 0;
    }

    write("You pay " + mon + " copper to " +
        painter->query_the_name(this_player()) + ".\n");

    add_solv(paint_me[0]);
    return 1;    

}

public void
init()
{
    ::init();

    add_action(start_paint, "paint");
    add_action(inquire, "inquire");
    add_action(start_solv, "restore");
}
 
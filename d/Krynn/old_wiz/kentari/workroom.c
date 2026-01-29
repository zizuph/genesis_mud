/*
   Krynn. Kentari's Workroom
   workroom.c
   -----

   Coded ........: November 1996
   By ...........: Kentari

   Latest update : February 1998
   By ...........: Kentari
   Reason .......: Adding Fireplace Code
*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Gondor/open/fireplace/fireplace";

#include "/d/Krynn/common/defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"
#include <money.h>
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#define MNSTR 		"/d/Krynn/kentari/mnstrs/"
#define LOG_FILE	"/d/Krynn/kentari/log/enter"

int alarm_id;
public string           fire_desc(string arg);  /* VBFC for fire */

string Owner = ("kentari");
object me = find_living(Owner);
object dragon;


void
create_room()
{
    set_short("Kentari's workroom");
    add_item(({"cushions","pillows","floor"}),
	"The soft feather-filled cushions look so inviting that you " +
	"have to fight the urge to just lie down and let the day's " +
	"weariness overtake you.\n");
    add_item(({"sword","blade"}),
	"The ancient sword of Kentari's ancestry is a well-oiled, " +
	"gleaming monster of a weapon, easily six feet long.  It " +
	"has a pattern of roses decorating the blade, with an elven " +
	"starjewel embedded in the hilt.\n");
    add_item(({"shield","crest"}),
	"This shield displays the crest of Kentari's line with " +
	"bold colors and a sharp image.\n");   
    add_item(({"fireplace","burnished fireplace","stone fireplace",
	"burnished stone fireplace"}), &fire_desc("fireplace"));
    add_item(({ "fire", "flame","flames" }), &fire_desc("fire"));
    add_item(({"wood","firewood","wood in fireplace","firewood in fireplace"}), 
	&fire_desc("wood"));
    add_item(({"ash","ashes","ash in fireplace","ashes in fireplace"}),
	&fire_desc("ashes"));

       /* set the pattern for parse_command() */
    set_parse_pattern("[the] [burnished] [stone] 'fireplace'");
    
    set_long(fire_desc);           /* use VBFC for room description */

    add_exit("/d/Krynn/solamn/vin/room/startroom","vkeep", "@@check");
    add_exit("/d/Krynn/wayreth/tower/conclave", "wohs", "@@check");
    add_exit("/d/Krynn/diamond/room/s1","diamond", "@@check");
    add_exit("/d/Krynn/kentari/vault","vault", 0);
    add_exit("/d/Krynn/kentari/ktest_room","down", 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    dragon = clone_object(MNSTR+"kenpet.c")->move(TO);
}  

/*
 * Function name: reset_workroom
 * Description  : Called to make the room reset from time to time. You
 *                should redefine this function if you want your workroom
 *                to reset.
 */
public void
reset_room()
{
	if(!dragon) 
      	  (dragon = clone_object(MNSTR +"kenpet.c"))->move_living(0,this_object());
	
	/* reset wood to default amount */
    set_wood(-1);

    /* if fire's gone out and there's someone here to rekindle it,
     * start it up again.
     */
    if ( query_fire_state() != FIRE_BURNING && ENV(dragon) == this_object() )
	{
	tell_room(this_object(),
            BSN("The dragon hatchling deftly puts more wood in the " +
		"fireplace with its tail and lights it with a small " +
		"breath of flame."));
	set_fire_state(FIRE_BURNING);
        }

}

void
init()
{
    ::init();
    init_fire();        /* add verbs for fire */

    if (TP->query_real_name() == Owner && !present("_reader_", TP))
	{
	setuid();
        seteuid(getuid());
	clone_object("/secure/mail_reader")->move(TP, 1);
	}
}

int
check()
{
    string name = this_player()->query_real_name();
    int level = this_player()->query_wiz_level();
 
    if(name != "kentari" && name != "kentarijr" && level < 15)
    {
	write("You do not have the immortal powers neccessary to travel " +
 		"the portal.\n");
	say(QCTNAME(this_player())+" tries to travel the portal, but "+
	"lacks the neccessary immortal powers.\n");
        return 1;
    }
    return 0;
}

int
who_enters()
{
    string name = this_player()->query_real_name();

    if(name != "kentari" && name != "kentarijr")
    {
	write_file(LOG_FILE, name+" entered at "+ctime(time())+"\n");
	return 1;
    }
    return 0;
}

static int
query_prevent_snoop()
{
   return 1;  
}

/*
 * Function name:       fire_desc 
 * Descripiton  :       VBFC for room and items that vary w fire
 * Arguments    :       string arg -- what we're looking at
 * Returns      :       string description
 */
public string
fire_desc(string arg)
{
    int fire_state = query_fire_state();

    switch ( arg )
    {

    case "fireplace":
        switch ( fire_state )
	{
        case FIRE_BURNING:
            return BSN("A burnished stone fireplace is set into the "+
		"wall. A fire burns softly in the fireplace, "+
                "casting a gentle glow over the room.");
        case FIRE_UNLIT_WOOD:
            return BSN("A burnished stone fireplace is set into the "+
		"wall. Firewood is stacked in the fireplace.");
	default:        /* FIRE_ASHES */
	    return BSN("A burnished stone fireplace is set into the "+
		"wall.");
        }

    case "fire":
        if ( fire_state == FIRE_BURNING )
            return BSN("A fire burns softly in the fireplace.");
	return BSN("You find no fire.");

    case "wood":
        switch ( fire_state )
        {
        case FIRE_BURNING:
	    return BSN("The wood in the fireplace softly burns, emiting "+
                "a pleasant warmth.");
        case FIRE_UNLIT_WOOD:
	    return BSN("Unlit wood is piled in the fireplace.");
	default:        /* FIRE_ASHES */
            return BSN("You find no firewood.");
        }

    case "ashes":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return BSN("Beneath the softly burning fire, "+
		"ashes cover the bottom of the fireplace.");
        case FIRE_UNLIT_WOOD:
	    return BSN("Beneath the wood, "+
                "ashes cover the bottom of the fireplace.");
	default:        /* FIRE_ASHES */
 	    return BSN("Ashes cover the bottom of the fireplace.");
	}

	default:    /* room long description */
            if ( fire_state == FIRE_BURNING )
              return BSN(
		"This is Kentari's workroom, where he learns the " +
    		"tricks of the trade and relaxes after a long day of work. " +
    		"A warming fire burns softly in the burnished stone fireplace, over " +
    		"which the sword of Kentari's line is mounted along with " +
    		"a Solamnic shield bearing his family crest. Soft cushions " +
    		"adorn the floor where you could all too easily imagine " +
		"curling up and drifting into peaceful slumber.\n");
	    return BSN(
                "This is Kentari's workroom, where he learns the " +
		"tricks of the trade and relaxes after a long day of work. " +
		"A chill draft emanates from the burnished stone fireplace, over " +
		"which the sword of Kentari's line is mounted along with " +
		"a Solamnic shield bearing his family crest. Soft cushions " +
		"adorn the floor where you could all too easily imagine " +
		"curling up and drifting into peaceful slumber.\n");
	}
    return "";  /* "cannot" happen */
} /* fire_desc */

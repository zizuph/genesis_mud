/* Mortis 12.2005 
 * Smells of what's below and guards above
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_ROOMBASE;

string
query_to_jail()
{
  return "down";
}

object guard1, guard2;

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "Wide, polished oak floorboards run flat against the "
	+ "curved, translucent white marble of this perfectly circular second "
	+ "floor of a Palanthas guard tower.  Grey, stone stairs curve along "
	+ "the wall leading down to the ground floor.  The ceiling is over a "
	+ "dozen feet high.  Cots line the walls, and there are several chairs "
	+ "around a table in the middle of the floor.  An iron runged ladder "
	+ "is bolted to the west wall and leads up to a trapdoor in the "
	+ "ceiling.  ";  /* ...continued in TIMEOFDAY description. */
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += road + "The first rays of dawn stream in through the east window "
	+ "lighting the room in  " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues.\n";
	break;

    case TOD_DAY:
	desc += road + "The translucent marble of the walls gleams as daylight "
	+ "streams in through the windows.\n";
	break;

    case TOD_TWILIGHT:
	desc += road + "The marble of the eastern wall seems to glow of its own "
	+ "accord as the last rays of the setting sun strike it.\n";
    break;

    case TOD_NIGHT:
	desc += road + "The glow from the lamplights outside sheds a soft glow "
	+ "through the windows.\n";
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{
	if (!guard1)
		guard1 = clone_object(LIV + "city_guard");
		guard1->move(TO);
	if (!guard2)
		guard2 = clone_object(LIV + "city_guard");
		guard2->move(TO);
}

void
create_palan_room()
{
	object trapdoor;

    SHORT("The second floor of a Palanthas guard tower");
    LONG("@@get_time_desc@@");

	ITEM(({"short tower", "short marble tower", "marble tower"}), "You're "
	+ "inside a tower of translucent, white marble rising at least forty "
	+ "feet into the air.  Why not have a <look> around?\n");
	ITEM(({"floor", "floorboard", "floorboards"}), "The floor must be "
	+ "heavily reinforced and the oak floorboards exceptionally sturdy for "
	+ "there is neither give nor creak when trod upon.  The floorboards are "
	+ "long, wide, and of smoothly polished oak.\n");	
	ITEM(({"wall", "walls"}), "Built entirely of large, translucent white "
	+ "marble blocks, the walls are at least two feet thick and polished to "
	+ "a reflective shine.  At the cardinal points of the tower are thin "
	+ "one pained windows like arrow slits looking out around the "
	+ "quarter.\n");
	ITEM(({"window", "windows"}), "Set into the walls at the cardinal "
	+ "points are thin, one pained windows like arrow slits looking out "
	+ "around the quarter  It's too difficult to see anything on the "
	+ "streets through them.  You'd have better luck up top.\n");
	ITEM("ceiling", "Thick, wide boards of polished oak reinforced with "
	+ "small, triangular wall supports form a high ceiling and the floor of "
	+ "the level above.  It is at around fourteen feet high, tall enough "
	+ "for most weapons to stand upright.  An iron chain suspends a large, "
	+ "oil lamp providing indoor light.\n");
	ITEM(({"large oil lamp", "ceiling lamp", "oil lamp", "large lamp"}),
	  "Hanging from a two foot, iron chain in the center of the ceiling is "
	+ "a large, oil lamp shedding steady light in the room.\n");
	ITEM("stairs", "Stairs of rough, grey, stone lead down to the ground "
	+ "floor.\n");
	ITEM("grey stone", "Neatly cut but left rough for traction, the grey "
	+ "stone of the stairs contrasts with the translucent white of the "
	+ "marble walls.\n");
	ITEM("ground floor", "The stairs leading down onto the ground floor "
	+ " curve out of sight along the wall below offering little view of "
	+ "what's below.\n");
	ITEM(({"chair", "chairs"}), "Half a dozen thin, wooden chairs ring a "
	+ "large, round table in the center of the room.\n");
	ITEM("table", "A large, round table with a thin, wooden top sits in the "
	+ "center of the room.  Its simple, round legs appear bolted into the "
	+ "bottom as if it could be dissassembled.\n");
	ITEM(({"cot", "cots"}), "Wide, padded cots with blankets line the walls "
	+ "particularly in the west of the room.  They are fairly clean and well "
	+ "kept after.\n");
	ITEM(({"ladder", "iron ladder", "iron runged ladder"}), "An iron runged "
	+ "ladder is bolted against the west wall and leads up to a trapdoor "
	+ "in the ceiling.\n");

	EXIT(MERCH + "merchant_tower1", "down", 0, 0);

	trapdoor = clone_object(MERCH + "doors/tower2_trapdoor");
	trapdoor->move(TO);

	reset_palan_room();
}

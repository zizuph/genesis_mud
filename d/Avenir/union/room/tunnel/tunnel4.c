#pragma strict_types

#include "defs.h"
inherit TBASE;

public int pieces = 2;

public void
reset_room(void)
{
    pieces++;
    if (pieces > 6)
	pieces = 6;
}

public void
tunnel_room(void)
{
    set_short("dark tunnel");
    set_long("A long, sinuous vein of glowing rock runs up "+
	"along the western wall, disrupting the otherwise "+
	"smooth surface of the tunnel. The vein bathes "+
	"everything in an eerie glow that casts no shadows. "+
	"The tunnel continues to descend to the @@get_north@@ "+
	"and ascends to the @@get_south@@.\n");

    add_item(({ "wall", "walls" }),
	"The walls a are smooth and undecorated. The west wall "+
	"is marred by a thick vein of glowing rock that runs from "+
	"the base of the wall to the ceiling.\n");
    add_item(({"vein", "wall", "rock"}), "@@piece_desc@@");

    add_cmd_item(({"music","wind"}), ({"listen","hear"}),
	"The musical sound of the wind fills you, inexplicably, "+
	"with joy.\n");

    add_prop(ROOM_I_LIGHT, 3);

    southern("tunnel3");
    northern("tunnel5");

    enable_reset(200);
}

public string
piece_desc(void)
{
    string str;

    switch(pieces)
    {
    case 0:
	str = "The vein seems to have many scars where "+
	    "bits have been broken or chiseled off.\n";
	break;
    case 1 .. 2:
	str = "The vein has many scars where pieces have "+
	    "been broken off, but it looks like there "+
	    "may be a couple left.\n";
	break;
    case 3 .. 4:
	str = "The vein has a few scratches on it where "+
	    "pieces have been broken off, but otherwise "+
	    "it is whole.\n";
	break;
    default:
	str = "The vein is whole, with only a couple of "+
	    "scratches where pieces have been broken off.\n";
	break;
    }

    return "This strange type of rock inexplicably produces "+
	"dazzling pulses of unearthly light. " + str;
}

public int
do_chisel(string str)
{
    object obj;
    object piece;
    string foo;
    object *inv;

    NF(CAP(query_verb()) + " what?");
    if (!strlen(str))
	return 0;

    inv = all_inventory();

    notify_fail(CAP(query_verb()) +" the vein with what?\n");
    if (!parse_command(str, inv, "[glowing] 'vein' %s", foo))
	return 0;

    if (!parse_command(str, inv, "[glowing] 'vein' 'with' %o", obj))
	return 0;

    if (!obj->query_wielded())
    {
	write("You aren't wielding the " + obj->short() +".\n");
	return 1;
    }

    switch(obj->weapon_type())
    {
    case "club":
    case "bow":
    case "item":
	write("The "+ obj->short() +" is not sharp "+
	    "enough to chisel anything with.\n");
	return 1;
    }

    if (!pieces)
    {
	write("The vein of glowing rock is exhausted.\n");
	return 1;
    }

    write("You chisel at the glowing vein with your "+ obj->short() +".\n");
    say(QCTNAME(TP) +" hits the glowing vein with "+ HIS(TP) +" "+
	QSHORT(obj) +".\n");

    TP->add_fatigue(-15);
    if (random(2))
	obj->set_dull(obj->query_dull() + 1);

    piece = clone_object(OUTPOST + "obj/lsource");
    piece->set_volume(random(14) + 1);
    piece->move(TO, 1);
    pieces--;

    tell_room(TO, "A "+ piece->short() +" breaks off from the "+
	"vein and falls to the ground.\n");

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(do_chisel, "chisel");
    add_action(do_chisel, "mine");
    add_action(do_chisel, "break");
    add_action(do_chisel, "chip");
}

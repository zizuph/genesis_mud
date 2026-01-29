#pragma strict_types
/*
 * ~/priv_10.c
 *
 * Private room in Melchior's Bath.
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Lilith, Apr 2002: ?
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../priv.h"
inherit BATH_PRIV;

static void
create_priv_bath(void)
{
    set_short("Southeast private bath");
    set_long(
      "This is by far the most pleasant place you have been in a "
      +"long time.\nHot spring-water trickles over a coarsely-hewn "
      +"baryta feldspar wall and falls, steaming, into a deep pool.  "
      +"Lamplight sparkles off of the silvery mineral, highlighting "
      +"a censer from which aromatic smoke rises.  Heat seems to "
      +"emanate from the very stones of the grotto, drawing beads "
      +"of sweat from your skin. The unpolished floor is riddled "
      +"with narrow channels designed to carry away excess water.  "
      +"Wisps of mist part to reveal steps "
      +"leading down into the inviting pool.\n"
      +"There is a sign on the door.\n");

    add_item(({"grotto", "stones" }),
	"The grotto is made of feldspar, a type of stone.\n");
    add_item(({"wall", "walls", "baryta", "feldspar", "baryta feldspar", 
	"mineral", "silvery mineral", "lamplight", "hollows"}),
	"The walls are of a feldspar whose silvery-white colour "+
	"is due to the presence of the rare metal baryta. "+
	"Small hollows have been carved into the walls and "+
	"filled with lamp oil, providing a diffuse and "+
	"glittering illumination.\n");
    add_item(({"mist", "smoke"}),
	"A thin white stream rises from the censer.\n");
    add_item(({"censer", "censor", "dish"}),
	"A circular-shaped brass dish with an ornate, vented cover. "+
	"Incense burns within, producing a white, aromatic smoke.\n");
    add_item(({"light", "illumination"}),
	"Pleasing to the eyes, a dim, flickering light shines "+
	"from the many hollows which have been carved into the "+
	"walls and filled with lamp oil.\n");
    add_item(({"floor", "channels", "channel", "narrow channel" }),
	"The unpolished floor is riddled with narrow channels designed "+
	"to carry away excess water.\n");

    add_cmd_item(({"censer","censor"}), ({"get","take"}),
	"The censer is too hot, you will burn yourself.\n");
    add_cmd_item(({"wall","walls"}), ({"touch","feel"}),
	"The walls feel rough and warm to the touch.\n");

    bath_door("ten", "arc_se", "nw");
}

public void
hook_smelled(string str)
{
    write("The misty air is pungent with the scent of oils and herbs.\n");
}

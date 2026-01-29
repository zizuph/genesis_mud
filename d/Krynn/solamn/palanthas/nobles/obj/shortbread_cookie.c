/* Mortis 12.2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "../../local.h"

string chess = one_of_list(({"pawn", "castle", "knight", "bishop", "queen",
							 "king"}));

mapping chess_to_emote = (["pawn":"cry out:  Defend the king!  Die to live!  "
	+ "Live to die!", "castle":"thunder around threateningly while "
	+ "remaining perfectly still and stone-like.", "knight":"announce, "
	+ "\"Stand to, steadfast foe.  I shall make this battle our last!\" as "
	+ "you hop around neighing and making clip-clop noises.",
	"bishop":"gesture a series of complex, holy signs and declare:  Death "
	+ "to the dying.  Victory to the victors.", "queen":"sneer powerfully "
	+ "as you say:  I shall teach you why you fear the night.  You shall "
	+ "all drown in lakes of blood.", "king":"just sit there and look "
	+ "around, occasionally scratch your butt, and nibble on your cookie."]);

mapping chess_to_emote2 = (["pawn":"cries out:  Defend the king!  Die to live!  "
	+ "Live to die!", "castle":"thunders around threateningly while "
	+ "remaining perfectly still and stone-like.", "knight":"announces, "
	+ "\"Stand to, steadfast foe.  I shall make this battle our last!\" while "
	+ "hopping around neighing and making clip-clop noises.",
	"bishop":"gestures a series of complex, holy signs and declares:  Death "
	+ "to the dying.  Victory to the victors.", "queen":"sneers powerfully "
	+ "and says:  I shall teach you why you fear the night.  You shall "
	+ "all drown in lakes of blood.", "king":"just sits there and looks "
	+ "around, occasionally performs a crude butt-scratch, and nibbles on "
	+ "the shortbread cookie."]);

public void
create_food()
{
    set_amount(55);
    set_name("cookie");
    set_pname("cookies");
	add_name(chess);
	add_pname(chess + "s");
    set_adj(({"shortbread", chess}));
	set_short("shortbread " + chess + " cookie");
    set_pshort("shortbread " + chess + " cookies");
    set_long("This rich, buttery, cookie is small by Mer-cantile measure, "
	+ "rectangular, lightly glazed on top, and stamped with the image of a "
	+ chess + " chess piece.\n");
}

void
init()
{
    ::init();
    ADA("smell");
}

int
smell(string str)
{
	if (!str || !parse_command(str, ({}), "[short] [bread] [shortbread] [chess] 'cookie' / 'cookies' "))
	return 0;

    TP->catch_msg("You smell the cookie getting a hint of its "
	+ "simple, buttery richness.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " shortbread "
	+ "to " + HIS(TP) + " nose sniffing it for a moment as "
	+ PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	string chess_emote = chess_to_emote[chess];
	string chess_emote2 = chess_to_emote2[chess];

	write("You crunch into your shortbread chess cookie getting a taste of "
	+ "its simple, buttery richness.\nYou feel the sudden urge to "
	+ chess_emote + "\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches into " + HIS(TP) + " shortbread "
	+ "chess cookie.\nSuddenly " + HE(TP) + " " + chess_emote2 + "\n",
		({TO, TP}));
}

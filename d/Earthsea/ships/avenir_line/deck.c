inherit "/d/Genesis/ship/deck";

#include "/sys/macros.h"
#include "defs.h"
#include "/sys/stdproperties.h"

void
create_deck()
{
    set_short("Deck of the barque");
    set_long(break_string("The deck is low and narrow and "+
	"appears to be made from planks of fragrant cedar. There "+
	"is a square-rigged black sail fitted with silver and "+
	"embroidered with silver stars. Toward "+
	"the prow you see an elegant low-cushioned divan. It is "+
	"remarkably peaceful and calm on the deck, as if the "+
	"waves beneath were stilled by magic for a peaceful ride. "+
	"You feel as though you are in a dream, as you gaze upon "+
	"the sea, the cool breezes stroking your brow.\n", 70));
    add_item((({"sail", "black sail", "square-rigged sail"})),
      "The barque is a low-riding vessel with a large square "+
      "sail fitted to the mainmast. It is embroidered with "+
      "silver stars like the night sky.\n");
    add_item((({"planks", "cedar", "fragrant cedar" })),
      "A lovely fragrance surrounds you from the cedar "+
      "deck.\n");
    add_item((({"divan", "cushioned divan"})),
      "The red silk divan looks sinfully luxurious.\n");
    add_item((({"deck", "cedar deck"})),
      "The deck exhales a fragrance from the cedar planks, "+
      "almost like a perfume.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_M_NO_ATTACK, 1);



    set_deck_sound("@@sounds");
    set_bump_sound("The barque glides easily to the pier.\n");
}

string
sounds()
{
    int i = random(5);

    switch(i)
    {
    case 0:
	return "The barque glides through the water as if on a "+
	"cushion of air.\n";
	break;

    case 1:
	return "You feel lulled into dreams by the gentle, "+
	"rocking motion of the barque.\n";
	break;

    case 2:
	return "Gentle sea breezes fill the starry sail, and "+
	"the silver fittings jingle like bells.\n";
	break;

    default:
	return "You seem to hear the soft singing of mermaids "+
	"as the barque glides forward.\n";
	break;
    }
    return "";
}

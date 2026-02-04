inherit "/std/object.c";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)    break_string(message, 70)
#define TP              this_player
#define TO              this_object

void
create_object()
{
    set_name("journal");
    add_adj(({"fragile", "leather-bound"}));
    set_long(BS("Written with a strong, but sloppy hand, this journal appears "
    + "to detail the travels of one Duncan Thane. Weather and time have left "
    + "their mark on the small book; only the last few pages seem legible.\n"));
    add_cmd_item(({"book", "journal"}), "read", 
      "You flip rapidly through the first pages, too stained and faded to be \n"
    + "legible. Though you cannot read the words, the handwriting gives you the \n"
    + "impression of a lifetime of searching, of a man being gradually drained \n"
    + "away by the demands of a ceaseless quest. Towards the end the writing seems \n"
    + "to gain a new strength:\n"
    + "     Let it be known that I, Duncan Thane, have after a lifetime of searching \n"
    + "found the key that will end my ageless quest and change the history of an \n"
    + "age long past...[here the writing fades for a few pages]...imagine my surprise!\n"
    + "The Word, the secret name that would unlock the ancient power and place it \n"
    + "in my very hands! And what was this Word but the very name that has plagued\n"
    + "my dreams for so many years! The Last Rider of the great battle! And where \n"
    + "was that portal to past, which shall soon carry me to the final confrontation,\n"
    + "but in the...[again the writing fades. Only the last words are legible]\n"
    + "     The cold gnaws at my bones and consumes me; the hunger is no better. \n"
    + "Conner has gone for aid, but I know that my hours are numbered. I only hope\n"
    + "that one day another will find this journal and finish this thing I have begun.\n"
    + "This boulder is no shelter. I lay down my pen for the last time. Adieu, \n"
    + "								  Duncan Thane\n");
}

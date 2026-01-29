/*      A guide book
        of the Calian Council  

    coder(s):   Maniac
    history:
                10.5.94              Created                  Maniac

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/scroll";
#include <stdproperties.h>
#include "defs.h"
#include COUNCIL_HEADER

void
read_it(string str)
{
    ::read_it("mread");
}

void
create_scroll()
{
    set_name("book");
    set_adj( ({ "guide", "council" }) );
    set_short("council guide book sitting on the reading desk");
    set_long("A thickish book with a brown leather cover." +
        "The title of the book is: 'Calian Council Guide'.\n");
    set_file(TEXT("council_guide"));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET,
	"The Council guide book is fixed here by the magic of Caliana.\n");
}
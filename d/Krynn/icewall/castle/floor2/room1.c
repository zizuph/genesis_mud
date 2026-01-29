/* War Room Created by Stevenson --
*  Icewall Militia conceived and spawned by Macker
*/

/* Created by Macker 11/2/94 */
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

inherit ICEINROOM;

object bozak, bozak2, kapak, kapak2, baaz, baaz2;

void
reset_icewall_room()
{
    if(!bozak)
    {
	bozak = clone_object(ICE_CAST_M + "bozak.c");
	bozak->set_color("white");
	bozak->move(TO);
    }
    if(!bozak2)
    {
	bozak2 = clone_object(ICE_CAST_M + "bozak.c");
	bozak2->set_color("white");
	bozak2->move(TO);
    }
    if(!kapak)
    {
	kapak = clone_object(ICE_CAST_M + "kapak.c");
	kapak->set_color("white");
	kapak->move(TO);
    }
    if(!kapak2)
    {
	kapak2 = clone_object(ICE_CAST_M + "kapak.c");
	kapak2->set_color("white");
	kapak2->move(TO);
    }
    if(!baaz)
    {
	baaz = clone_object(ICE_CAST_M + "baaz.c");
	baaz->set_color("white");
	baaz->move(TO);
    }
    if(!baaz2)
    {
	baaz2 = clone_object(ICE_CAST_M + "baaz.c");
	baaz2->set_color("white");
	baaz2->move(TO);
    }
    return;
}

void create_icewall_room() {
    set_short("Draconian Room");
    set_long("@@my_long@@");

    add_item("maps","The maps are of Solamnia, Solace, Qualinesti, and "
      + "Mt. Nevermind. It appears that they are battle maps.\n");
    add_item("charts","These charts seem to detail the "
      + "architectural flaws in Vingaard Keep.\n");
    add_item(({"painting","huma","Huma"}),"The sight of 'Huma' shocks "
      + "you for it has been grotesquely disfigured. The eyes "
      + "have been painted yellow, and one of his upper teeth was "
      + "painted in black. You also notice that where his "
      + "armour was is now crudely drawn a big flowery dress. "
      + "Under the painting you can see a placard.\n");
    add_item("placard","The placard is written in scribbles but you can "
      + "make out the text sure enough: 'The Mighty Huma--GirlyMan!'\n");

    add_exit(ICE_CAST2_R+"hall3_2","south");

    reset_icewall_room();
}

string
my_long()
{
    if((bozak)||(bozak2)||(kapak)||(kapak2)||(baaz)||(baaz2)) 
	return
	"This room is apparently the planning room of the "
	+ "Dragon Highlord. On the walls are charts and "
	+ "maps of Krynn. Most noticeably you see a "
	+ "painting of Huma on the east wall. "
	+ "\n\n"
	+ "It appears that you have found yourself in the "
	+ "middle of a heated discussion: one concerning "
	+ "the Destruction Of Vingaard! "
	+ "\n";
    else
	return("Oddly enough, this room is totally empty. " +
	  "There is nothing interesting here at all. No monsters, " +
	  "no furniture, no nothing.\n");
}


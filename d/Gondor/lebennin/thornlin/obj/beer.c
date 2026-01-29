/*
 * Stole the file from /d/Gondor/common/guild/obj/beer.c
 * By : someone, assuming it was Elessar
 * Boromir, 29 apr. 1995
 */
inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink() 
{
    set_name(({"beer", "brew", }));
    set_pname(({"beers"}));
    set_adj(({"home-brewed", "home", }));
    set_short("home brew");
    set_pshort("pints of home brew");
    set_long(break_string(
	"It is the the pride of Thornlin, next to its pork meals, "+
	"fine home brew, or at least as fine as it can get.\n",70));

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(568);      /* This is a pint */
    set_alco_amount(12);       /* 2% alcohol     */
    add_prop(OBJ_I_WEIGHT, 540);
    add_prop(OBJ_I_VOLUME, 540);
}

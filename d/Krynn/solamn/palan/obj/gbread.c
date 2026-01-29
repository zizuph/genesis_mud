/* File:          /d/Krynn/solamn/palan/obj/gbread.c
 * Creator:       Karath
 * Date:          November 9, 1997
 * Modifications:
 * Purpose:       Yummy food!
 */

#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>

public void
create_food()
{
    set_amount(175);
    set_name( ({"man", "gingerbread man"}) );
    set_pname( ({"men", "gingerbread men"}) );
    set_adj("gingerbread");
    set_short("gingerbread man");
    set_pshort("gingerbread men");
    set_long("A yummy gingerbread man with a smile and clothing "+
	"of icing. His nose is a tiny little chocolate-chip, and "+
	"his eyes are little marshmallows. He looks delicious.\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
	", chomping off the head first, then the arms, then legs, "+
	"finally eating his body in two big bites!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
	", chomping off the head first, then the arms, then legs, "+
	"finally eating his body in two big bites!\n");
}

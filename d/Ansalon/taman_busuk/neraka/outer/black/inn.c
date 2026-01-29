/* Ashlar, 4 Jun 97 - The Black Ship Inn
 *
 * Stralle @ Genesis 040226
 *  - Added a quest
 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

inherit OUTER_IN;
inherit "/d/Ansalon/lib/pub";

object ob, barkeeper = 0;
object d1,m1;
int out_of_dragonbrew = 0;

void set_out_of_dragonbrew();
int query_out_of_dragonbrew();

void
reset_neraka_room()
{
    if (!objectp(barkeeper))
    {
        barkeeper = clone_npc(NNPC + "bs_barkeep");
        barkeeper->add_prop(LIVE_S_EXTRA_SHORT," standing behind the counter");
        set_barkeeper(barkeeper);

        if (query_out_of_dragonbrew())
        {
            if (!barkeeper->query_need_ladle())
                barkeeper->set_need_ladle();

            set_out_of_dragonbrew();
        }
    }
    if (!objectp(d1))
        d1 = clone_npc(NNPC + "baaz","black");
    if (!objectp(m1))
        m1 = clone_npc(NNPC + "mercenary","black");
}

void
create_neraka_room()
{
    set_short("the Black Ship Inn");
	
    set_long("This is a modest inn in the Black Quarter, named the " +
        "Black Ship Inn. A few tables and benches are placed in " +
        "the spacious common room, and a counter stands in one end " +
        "of the room. The walls are decorated with nautical implements " +
        "of various kind. A few patrons sit at the tables, eating and " +
        "drinking. A fire is blazing away in the stone hearth " +
        "in a corner.\n");

    add_item("counter","An old and scratched counter, it has a " +
        "pricelist on top of it.\n");

    add_item(({"patrons","patron"}),"The patrons seem to be enjoying " +
        "their food and drink.\n");

    add_item(({"pricelist","menu"}),
        "It contains some words.\n");
    add_cmd_item(({"pricelist","menu"}),({"read"}),
        ({"@@read_pricelist@@"}));
    add_item(({"table","tables"}),"The tables are a bit dirty.\n");
    add_item(({"bench","benches"}),"The low wooden benches make for " +
        "somewhat uncomfortable seating at the tables.\n");
    add_item_inside();

    remove_item("walls");
    add_item("walls","The walls are decorated with nautical implements " +
        "of various kind.\n");
    add_item(({"implements","nautical implements"}),
        "There are lines and pieces of sail and amusingly shaped driftwood " +
        "and lots of other things.\n");
    add_item(({"lines","sail","driftwood"}),"It doesn't get interesting " +
        "even on closer examination.\n");
    add_item("fire","The fire adds warmth and light to the room.\n");
    add_item(({"hearth","stone hearth"}),"It is a simple stone hearth " +
        "without any ornaments. There is a fire burning in it.\n");

    add_prop(OBJ_I_HAS_FIRE, 1);

    add_exit(NOUTER+"black/yard","out");

    add_drink_object(({"ale","ales","mug","mugs"}),
        NOBJ + "drink/ale1", 21);
    add_drink_object(({"dragonbrew","black dragonbrew","dragonbrews","black dragonbrews"}),
        NOBJ + "drink/dragonbrew", 213);

    add_food_object(({"leg","chicken","legs","chickens","chicken leg","chicken legs"}),
        NOBJ + "food/chickenleg", 12);
    add_food_object(({"stew","stews"}),
        NOBJ + "food/stew", 57);

    reset_room();
}

string
read_pricelist()
{
	return "The menu reads:\n\n" +
        "Mug of ale             1 silver and 9 copper\n" +
        "Black Dragonbrew       17 silver and 9 copper\n" +
        "Chicken leg            1 silver piece only!\n" +
        "Stew                   4 silver and 9 copper\n";
}

/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    init_pub();
}

void
pub_hook_player_buys(object ob, int price)
{
    ::pub_hook_player_buys(ob, price);
    barkeeper->command("nudge parrot");
}

void
set_out_of_dragonbrew()
{
    out_of_dragonbrew = !out_of_dragonbrew;
}

int
query_out_of_dragonbrew()
{
    return out_of_dragonbrew;
}

object
fix_drink(mixed data)
{
    if (stringp(data[0]) && data[0] == NOBJ + "drink/dragonbrew" &&
        objectp(barkeeper))
    {
        if (query_out_of_dragonbrew() || barkeeper->query_need_ladle())
        {
            barkeeper->command("say Unfortunately I'm all out of that.");
            barkeeper->command("say Perhaps you could help me fetch some new?");

            return 0;
        }
#ifdef 0
        else if (!random(8))
            set_out_of_dragonbrew();
#endif
    }

    return ::fix_drink(data);
}    

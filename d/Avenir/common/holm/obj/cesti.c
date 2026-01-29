// -*-C++-*-
// file name: /d/Avenir/common/holm/obj/cesti.c
// creator(s):  Lilith, Jun 1997
// last update:
//            Lilith 2000.12.18 patched drop bug
//            Zizuph Oct 2022: Made an unarmed enhancer
//            Lilith Mar 2022: set the likely break and cond to neg values
//              per Arman AoB, see notes below.
// purpose:   A piece of armour improving unarmed attacks for humanoids
// note:      HEAVILY borrowed from ~Avenir/common/port/obj/knuckles.c
//            made by Boriska, Jun 1995


#pragma strict_types

inherit "/d/Avenir/inherit/unarmed_enhancer";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/std/combat/combat.h"

// unarmed wchit and wpen bonus
// Don't forget to update case statement picking a message for player
// if bonus range changes
#define F_BONUS(skill) (1+(skill)/10)

// saves unarmed attack bonus
private int bonus;

void
create_unarmed_enhancer()
{
    set_name ("cesti");
    set_pname(({"cesti", "armours", "gloves"}));
    set_short("pair of spiked leather cesti");
    set_pshort("pairs of spiked leather cesti");
    add_adj(({"spiked","leather"}));
    add_name(({"gloves", "armour"}));
    set_long("These gloves are made of two layers of thick "+
        "leather, the upper one having sharp spikes driven through "+
        "the top, along the backs of the hands. They look like "+
        "they could do some bloody damage in a fight.\n");

    set_default_enhancer(35, 
                         35, 
                         W_BLUDGEON | W_IMPALE, 
                         9, A_HANDS, ({0, 0, 0 }), this_object());

    set_af(this_object());

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 500); // yes, we're expensive

    add_item(({"spike", "spikes" }), "These spikes are half the "+
        "length of your smallest finger, and filed to sharp points "+
        "that could rip flesh to shreds.\n");

/*	
 *  Lilith, Feb 2022: Getting feedback from unarmed fighters that these
 *                    are wearing down very fast--because they are
 *                    both taking hits and enhancing hits.  I'm going to
 *                    try setting these to negatives to see how it goes.
 *         Arman gave ok to set values very very negative on 3/3/2022
 */
	set_likely_break(-1000); 
	set_likely_cond(-1000);

}

private string
message(int bonus)
{
    switch (bonus)
    {
        case 1..3:
            return "As you slip the "+ short() +" over your hands, "+
                   "you feel certain that your next brawl will be "+
                   "a bloody one.\n";
        case 4..6:
            return "As you slip the "+ short() +" over your hands, a "+
                   "grin of anticipation spreads across your face.\n"+
                   "It is time to slice and dice!\n";
        case 7..9:
            return "The "+ short() +" feels natural on your hands, as "+
                   "though they belong there. Your fingers flex and  "+
                   "ball, forming fists that will make rivers of blood "+
                   "run in your next fight!\n";
        default:
            return "You wear the "+ short() +".\n";
    }
}

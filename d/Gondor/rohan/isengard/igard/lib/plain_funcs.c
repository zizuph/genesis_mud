/*
 *  IGARD_LIB + "plain_funcs.c"
 *
 *  Various functions common to Isengard rooms.
 *
 *  Last modified by Alto, 23 September 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"
#include "/d/Gondor/std/tell.c"

/* PROTOTYPES */

public string         plain_tower_desc(int distance);
public void           add_plain_tells();
public void           isle_add_items();
public void           path_add_items();
public void           dome_add_items();

public string
plain_tower_desc(int distance)
{
    string tower_text = " A mighty tower ";

    switch (distance)
    {
    case 0:
		      tower_text += "lurks far down at the center of the "
            + "plain, dominating the environment even at this distance. "
            + "The ring wall, however, is a close rival towering nearby "
            + "and encircling the plain. ";
        break;
        
    case 1:
		      tower_text += "lurks far down at the center of the "
            + "plain. It is far enough away to seem somewhat hazy as "
            + "you look at it, perhaps due to all the steam "
            + "and vapours escaping from the vents on the plain. ";
        break;
    case 2:
		      tower_text += "can be seen at the center of the plain. From "
            + "here it seems to be enshrouded in a thin mist, possibly "
            + "due to the steams and vapours arising from the vents "
            + "scattered across the plain. The great ring wall looms "
            + "high somewhat closer in the other direction. ";
        break;
    case 3:
		      tower_text += "stands in the center of the plain, its great "
            + "gaping pinnacles open to the sky as if reaching up to "
            + "devour the sun and stars. It is further away from here "
            + "than the ring wall, which looms across the horizon in "
            + "other direction. ";
        break;
    case 4:
		      tower_text += "rests in the distance, at the center "
            + "of the plain. You appear to be halfway between the "
            + "tower and the massive ring wall that encircles and encloses "
            + "the fastness of Isengard. ";
        break;
    case 5:
		      tower_text += "spikes high into the air at the center of the "
            + "plain. Although you are some distance away, the tower "
            + "blots out a great portion of the sky. The ring wall enclosing "
            + "the plain looms large in the distance. ";
        break;
    case 6:
		      tower_text += "lurks at the center of the plain. From here "
            + "you can see many roads converging upon it, such that "
            + "it resembles a massive spider perched in a "
            + "web of tremendous proportions. The gaping horns of its "
            + "pinnacles do little to dispel this sinister effect. The "
            + "great ring wall can be seen in the distance, encircling "
            + "the plain of Isengard. ";
        break;
    case 7:
		      tower_text += "blocks out most of the sky. All streets lead "
            + "down to its base at the center of the plain, which "
            + "resembles an isle of black rock, gleaming and hard. Gulls "
            + "turn and wheel about its heights and pinnacles. The streets "
            + "lead away from the brooding tower and return to the great ring "
            + "wall in the distance. ";
        break;
    case 8:
		      tower_text += "has seized a vast circumference here at the center "
            + "of the plain. It stands atop a great isle of rock, which "
            + "the road appears to lead down to. The great ring wall "
            + "in the distance is obscured in mist, possibly "
            + "due to the steams and vapours escaping from vents "
            + "strewn across the plain. ";
        break;
    case 9:
		      tower_text += "dominates your surroundings, jutting up from a great "
            + "isle of black rock. The tower resembles a massive chisled "
            + "leviathan peering down upon the plain with rapacious greed. "
            + "High above, gulls wheel and cry among its gaping pinnacles. "
            + "Many streets lead up onto the isle of rock and also return to "
            + "the great ring wall a mile away. Gazing in the distance, you "
            + "discover that the wall has almost disappeared due to the vapours "
            + "and fumes rising from vents upon the plain. ";
        break;
    default:
        break;
    }

    return tower_text;
}


void
add_plain_tells()
{
    set_tell_time(120);

    add_tell("A wolf howls in the distance.\n");
    add_tell("An eagle cries far overhead.\n");
    add_tell("Someone shouts: 'Move it you lubbers, or you'll feel my whip!'\n");
    add_tell("Someone shouts: 'Orders came down to look for spies. It's our "
        + "hides if they aren't found!'\n");
    add_tell("Marching feet can be heard somewhere nearby.\n");
    add_tell("Steam hisses from one of the vents.\n");
    add_tell("The ground rumbles beneath your feet.\n");
    add_tell("The low rumbling of machinery can be heard from below ground.\n");
    add_tell("You hear the crack of a whip from somewhere behind.\n");
    add_tell("A slow breeze stirs the mist swirling about the plain.\n");
    add_tell("Phoom! Vapour shoots from one of the shafts.\n");
    add_tell("Deep voices grumble in the distance.\n");
    add_tell("Tortured machinery squeals and rattles from below.\n");
    add_tell("Someone shouts: 'Boss thinks there may be spies running loose "
        + "in here! Pick up the slack my lads, or you'll taste my whip.'\n");
    add_tell("Phoom! Vapour shoots from one of the shafts.\n");
    add_tell("Hissssss! Steam whistles from beneath one of the domes.\n");
    add_tell("Someone shouts: 'Find those spies and we'll feast on manflesh "
        + "at days end!'\n");
    add_tell("Someone shouts: 'I tell you, someone at the gates has slipped, "
        + "but as usual it is the Uruk Hai doing the cleaning up.'\n");
    add_tell("Someone shouts: 'Do you want to tell the Boss we can't find the "
        + "spies? Move it, you lazy hill orc!'\n");
    add_tell("An unwholesome voice cries out in pain.\n");
    add_tell("Crack! Somewhere nearby, a whip snaps across an unfortunate "
        + "back.\n");
    add_tell("Gulls scream as they circle and wheel about the pinnacles of "
        + "the tower.\n");
}


void
isle_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"foot", "base"}), "The foot of the mighty tower Orthanc is "
        + "an isle of chiselled black rock.\n");
    add_item(({"rock", "stone"}), "The rock upon which Orthanc stands is "
        + "black with many facets, gleaming as though it is wet.\n");
    add_item(({"face", "facet", "faces", "facets", "edge", "edges"}), "The "
        + "facets on the black rock are sharp and look as though "
        + "they are newly chiselled.\n");
    add_item(({"path", "small path"}), "There is a small path here which "
        + "runs around the isle of black rock.\n");
}


void
path_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"path", "gravel path", "small path"}), "The path beneath "
        + "your feet is made from crushed gravel. It crunches and "
        + "shifts as you walk across it.\n");
    add_item(({"gravel", "crushed gravel"}), "The gravel is made from "
        + "black stone, pulverized many times over in the mines to the "
        + "west, and further ground beneath the heels of many booted feet.\n");
    add_item(({"street", "streets", "road", "roads"}), "From here you can "
        + "see many roads leading from the ring wall down to the massive "
        + "tower in the center of the plain.\n");
}


void
dome_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"dome", "stone dome", "large stone dome"}), "This large "
        + "structure stands roughly ten feet high and has a circumference "
        + "of approximately forty feet. It is made of the same black stone "
        + "from which the mighty ring wall is constructed and appears "
        + "unbroken save for the great copper pipe rising from its top. "
        + "It might be possible to climb the dome to inspect the pipe more "
        + "closely.\n");
    add_item(({"pipe", "copper pipe", "great copper pipe"}), "The great "
        + "copper pipe rises from the center and top of the dome. It is "
        + "encased in blue deposits from long years of oxidation, but appears "
        + "to be sound. It protrudes several feet above the dome, but you "
        + "would need to climb the dome itself to get a better look inside. "
        + "Given the great gouts of steam and noxious vapours belching from "
        + "within the pipe, that could prove to be a dangerous venture.\n");
    add_item(({"steam", "gouts", "vapour", "vapours", "unwholesome vapours"}),
        "The steams and vapours belching from within the copper pipe above "
        + "the dome make your eyes water. The scent of sulfur is nearly "
        + "overwhelming, and you are finding it rather difficult to catch your "
        + "breath.\n");
    add_item(({"deposit", "deposits", "blue deposit", "blue deposits"}), 
        "Encasing the copper pipe is a blue deposit, formed by the oxidation "
        + "of copper over many years of exposure to heat and moisture.\n");
}



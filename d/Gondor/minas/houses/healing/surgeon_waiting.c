/*
 * /d/Gondor/minas/houses/healing/surgeon_waiting.c
 *
 * This is the waiting room of the surgeon. Here she will wait for
 * people who have scars that need to be removed.
 *
 * A nice feature in this room is the mirror on the wall. I initially
 * coded it to be an example (/doc/examples/obj/mirror.c), but that does
 * not mean that I cannot use the code myself elsewhere, or does it?
 *
 * The code for the surgeon, Haldira, may be found in #define SURGEON.
 *
 * /Mercade, 6 May 1994
 *
 * Revision history:
 */

inherit "/d/Gondor/common/room";

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define OPERATING_ROOM (HOH_DIR + "haldira_surgery")
#define OUT_ROOM       (HOH_DIR + "e_upcorr")
#define SURGEON        (NPC_DIR   + "surgeon_haldira")

#define SCAR_IN_FACE   ({ "forehead", "left cheek", "right cheek", "nose" })

static object surgeon;

void
create_room()
{
    set_short("the waiting room of the Houses of Healing surgeon");

    set_long(BSN("You are in the waiting room of the office of Haldira, " +
	"one of the surgeons of the Houses of Healing. She is specialized in " +
	"the surgery to remove scars from your body. There is a poster " +
	"with the details of her prices on the wall. A large carpet is " +
	"on the floor for waiting patients. There is a sturdy door on the " +
	"other side of the room."));

    add_item( ({ "carpet", "large carpet", "floor", "ground" }),
	BSN("A large carpet lies on the floor. It is made of wool and " +
	"has some shining colours."));
    add_item( ({ "poster" }),
	BSN("It has readable words on it."));
    add_item( ({ "wall", "walls" }),
	BSN("The walls are wainscotted with oak. On one of them you see " +
	"a poster with information and the prices of the surgeon. Also, " +
	"you see a certificate nailed to the wall. On the other wall, " +
	"there is a mirror."));
    add_item( ({ "certificate" }),
	BSN("The certificate is very interestingly looking and has a seal " +
	"on it."));
    add_item( ({ "seal", "wax", "red wax" }),
	BSN("In red wax you see the seal of the Lady Galadriel."));
    add_item( ({ "door", "sturdy door" }),
	BSN("On the other side of the room you see a door. It is a very " +
	"sturdy door, made of oak. Behind it is the surgery room."));
    add_item( ({ "mirror" }),
	"@@mirror_description");

    add_cmd_item( ({ "door", "sturdy door" }), ({ "open", "close" }),
	BSN("There is no reason to handle the door."));

    add_cmd_item( ({ "certificate" }), ({ "read" }),
	"CERTIFICATE\n\n" +
	BSN("By appointment of the Lady Galadriel, Haldira, surgeon based " +
	"in Minas Tirith, is licenced to perform recovering surgery on " +
	"victims of war. She has shown to be a highly qualified and skilled " +
	"surgeon, specialized in removing scars from the skin."));

    add_cmd_item( ({ "poster" }), ({ "read" }),
	"SCAR REMOVAL!\n\n" +
	BSN("Combat or accident may leave ugly scars on your body. Surgeon " +
	"Haldira, of the Houses of Healing, famous all over the world for her " +
	"skills, may help you recover from them. Be advised that after " +
	"surgery you have to recover for at least half an hour.") + "\n" +
	"Prices for the removal of one scar (approximately):\n" +
	"    from your head: 62 platinum coins\n" +
	"    from a leg    : 39 platinum coins\n" +
	"    from an arm   : 34 platinum coins\n" +
	"    from a hand   : 47 platinum coins\n\n" +
	BSN("The command to to get help is \"remove scar from <location>\". " +
	"After issueing the command you do not have to pay instantly, so " +
	"you can use the command to get information about surgery too."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_WIZINFO,
	BSN("In this room, Haldira, surgeon of Minas Tirith by appointment " +
	"of the Lady Galadriel, waits for people who want to have surgery " +
	"done on their scars. The price is rather fair and the rate of " +
	"success is rather high too. /Mercade!"));

    add_exit(OUT_ROOM,       "west");
    /* Command 'private' used by the surgeon. Don't change without reason. */
    add_exit(OPERATING_ROOM, "private", "@@enter_private");

    set_alarm(7.0, 0.0, "reset_room");
}

int
enter_private()
{
    if ((this_player()->query_wiz_level()) ||
	(objectp(surgeon) && (this_player() == surgeon)))
    {
	return 0;
    }

    if (!objectp(surgeon))
    {
	WRITE("You have no business in there.");
	return 1;
    }

    if (this_player() == surgeon->query_client())
    {
	return 0;
    }

    WRITE("You have no business in there.");
    return 1;
}

void
reset_room()
{
    if (!objectp(surgeon))
    {
	FIX_EUID;

	surgeon = clone_object(SURGEON);
	surgeon->arm_surgeon();
	surgeon->move_living("X", TO);
    }
}

/*
 * When someone examines this mirror, he gets an impression of him or
 * herself. This function gives the description.
 */
string
mirror_description()
{
    int     index;
    int     scar = this_player()->query_scar();
    object  armour;
    string *tmp = ({ });
    string  beauty;
    string  scars;
    string  health;
    string  wearing = "";

/*
 * This gives the string of what we think of our own beauty...
 * Or do we always think we look like the image of perfection?
 * It is a call_other to the object that normally handles beauty text.
 */
    beauty = call_other("/cmd/live/state", "beauty_text",
	(this_player()->my_opinion(this_player())),
	!this_player()->query_gender());

/*
 * Give a description of the armours worn on the head and on the neck.
 * Earrings are not in the set of default hitlocations :-)
 */
    if (objectp(armour = this_player()->query_armour(TS_NECK)))
    {
	tmp += ({ LANG_ADDART(armour->short(this_player())) +
	    " around your neck" });
    }
    if (objectp(armour = this_player()->query_armour(TS_HEAD)))
    {
	tmp += ({ LANG_ADDART(armour->short(this_player())) +
	    " on your head" });
    }
    if (sizeof(tmp))
    {
	wearing = ", wearing " + COMPOSITE_WORDS(tmp);
    }

/*
 * Give us an array of all scars the player has in his/her face and make
 * a nice string of them.
 */
    tmp = ({ });
    index = 0; /* intentional start at 1 with ++. */
    while(++index < F_MAX_SCAR)
    {
	if (scar & (1 << index))
	{
	   tmp += ({ F_SCAR_DESCS[index] });
	}
    }

    tmp &= SCAR_IN_FACE;
    if (sizeof(tmp))
    {
	scars = "You have " +
	    ((sizeof(tmp) == 1) ? "a scar" : "scars") +
	    " on your " + COMPOSITE_WORDS(tmp) +
	    " and you ";
    }
    else
    {
	scars = "You ";
    }

/*
 * Here we do a call_other to the object that normall generates the
 * descriptions if you examine someone. It returns how healthy you are.
 */
    health = call_other("/cmd/live/state", "show_subloc_health",
	this_player(), this_player());

/*
 * Finally we return the whole description with a remark about the mirror
 * itself.
 */
    return BSN("It is a mirror in a nicely carved wooden setting, hanging " +
	"on the wall. Looking into the mirror, you see yourself, " +
	LANG_ADDART(this_player()->query_nonmet_name()) + ". " +
	scars + "think that you look " + beauty + wearing +
	". You seem to be " + health + ".");
}

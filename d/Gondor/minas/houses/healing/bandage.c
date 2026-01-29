/*
 * /d/Gondor/common/obj/bandage.c
 *
 * This is the bandage that is used after the surgeon removed a scar from
 * you. This bandage will remove the scar at the end of the periode of
 * recovery.
 *
 * It is cloned from /d/Gondor/common/npc/surgeon_haldira.c
 *
 * /Mercade, 4 May 1994
 *
 * Revision history:
 */

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define HALF_HOUR   1800
#define FAIL_CHANCE   15 /* out of 100. */

static int creation_time = time();
static int scar          = -1;

void
create_object()
{
    set_name("bandage");
    set_pname("bandages");

    set_adj("white");

    set_short("white bandage");
    set_pshort("white bandages");

    set_long("@@long_description");

    add_prop(OBJ_I_VALUE,     0);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT,  400);

    add_prop(OBJ_M_NO_STEAL,    1);
    add_prop(OBJ_M_NO_TELEPORT, 1);

    add_prop(OBJ_S_WIZINFO,
	BSN("This object is put on the player after the player after " +
	"the surgeon removed a scar from him. If the player is not " +
	"careful with the bandage, it will mess up the process of " +
	"recovery. The scar is only removed if the player handles this " +
	"recovery and bandage correctly."));
}

/*
 * Function name: scar_to_part
 * Description  : Return a string description of the scar location the
 *                bandage is covering.
 * Returns      : string - the description.
 */
string
scar_to_part()
{
    switch(scar)
    {
    case   1:
    case   2:
	return "leg";
    case   4:
    case 128:
    case 256:
    case 512:
	return "head";
    case   8:
    case  16:
	return "arm";
    case  32:
    case  64:
	return "hand";
    default:
	return "body-part";
    }
}

string
long_description()
{
    if (scar == -1)
    {
	return BSN("It is a used bandage. On the inside is a stain of " +
	    "blood, not worth a second look.");
    }

    if (scar_to_part() == "head")
    {
	return BSN("You can only feel that the bandage is arround your " +
	    "head, but you cannot clearly see it. Be careful not to remove " +
	    "it too soon, though make sure you remove it manually when it " +
	    "is time to do so.");
    }

    return BSN("It is a bandage, put arround your " + scar_to_part() +
	" until it has recovered from surgery. Be careful not to remove " +
	"it too soon, though make sure you remove it manually when it is " +
	"time to do so.");
}

void
init()
{
    ::init();

    add_action("remove", "remove");
}

/*
 * Function name: used_bandage
 * Description  : When the bandage gets disrupted or removed, we change
 *                it to a used bandage and remove the NO_DROP property.
 */
void
used_bandage()
{
    remove_prop(OBJ_M_NO_DROP);
    remove_prop(OBJ_M_NO_GIVE);

    remove_adj("white");
    add_adj("used");
    add_adj("stained");

    set_short("used bandage");
    set_pshort("used bandages");

    add_item( ({ "blood", "stain", "blood stain", "stain of blood" }),
	BSN("On the inside of the bandage is a stain of blood."));

    environment()->remove_no_scar_bandage_shadow();
    scar = -1;
}

/*
 * Function name: disrupt_bandage
 * Description  : This function is called when the player disrupts the
 *                bandage by some action. It uses a little alarm to get
 *                the descriptions right.
 */
void
disrupt_bandage()
{
    set_alarm(0.5, 0.0, "used_bandage");
}

/*
 * Function name: unscar_client
 * Description  : When the player rightfully removes the bandage after
 *                the appropriate time, we unscar the player.
 */
void
unscar_client()
{
    int scars = environment()->query_scar();

    if (scar == -1)
    {
	return;
    }

    if (scars & scar)
    {
	scars ^= scar;
	environment()->set_scar(scars);
	environment()->save_me(1);
    }
}

int
remove(string str)
{
    if (!strlen(str) && !parse_command(str, ({ }),
	"[the] [white] [used] 'bandage'"))
    {
	NFN0("Remove what?");
    }

    if (scar == -1)
    {
	NFN0("The bandage is not used.");
    }

    if (time() < (creation_time + HALF_HOUR))
    {
        WRITE("You remove the bandage from your " + scar_to_part() +
	    ". However, you remove it too soon and your " + scar_to_part() +
	    " has not recovered completely yet. The scar will not " +
	    "disappear.");
	SAY(" removed the bandage from " + POSSESSIVE(TP) + " " +
	    scar_to_part() + ". However, removing it too soon, the scar " +
	    "remains.");

	used_bandage();

	return 1;
    }

    if (random(100) < FAIL_CHANCE)
    {
	SAY(" removes the bandage from " + POSSESSIVE(TP) + scar_to_part() +
	    ". However, it looks like the surgery has not been completely " +
	    "removed.");

	if (scar_to_part() == "head")
	{
	    WRITE("You remove the bandage from your head. You cannot see " +
		"the skin, but you feel that there still is a scar left. " +
		"The surgery has not been successful.");
	}
	else
	{
	    WRITE("You remove the bandage from your " + scar_to_part() +
		". The skin beneath it still has a scar on it. The surgery " +
		"has not been successful.");
	}

	used_bandage();
	return 1;
    }

    SAY(" removes the bandage from " + POSSESSIVE(TP) + " " +
	scar_to_part() + ". It looks like the skin beneath healed " +
	"completely The scar vanished.");

    if (scar_to_part() == "head")
    {
	WRITE("You remove the bandage from your head. You cannot see " +
	    "the skin, but you feel that it healed completely and that " +
	    "the scar vanished.");
    }
    else
    {
	WRITE("You remove the bandage from your " + scar_to_part() +
	    ". The skin beneath it looks completely recovered and the scar " +
	    "disappeared.");
    }

    unscar_client();
    used_bandage();
    return 1;
}

/*
 * Function name: set_scar
 * Description  : This function sets the scar location that this bandage
 *                protects.
 * Arguments    : int i - the scar location.
 */
void
set_scar(int i)
{
    scar = i;

    add_prop(OBJ_M_NO_DROP,
	"Impossible, it is around your " + scar_to_part() + ".\n");
    add_prop(OBJ_M_NO_GIVE,
	"Impossible, it is around your " + scar_to_part() + ".\n");
}

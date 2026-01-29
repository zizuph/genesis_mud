/*
 * /d/Gondor/common/quest/rotk/crown.c
 *
 * This is the White Crown, the crown of the King of Gondor!
 *
 * /Mercade, 3 October 1993
 *
 * Revision history:
 */

inherit "/std/armour";

#include "/d/Gondor/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

/*
 * Create the object
 */
void
create_armour()
{
    set_name("crown");
    set_adj("ancient");
    add_adj("pearl");
    add_adj("silver");
    add_adj("white");

    set_short("white crown");

    set_long(BSN("The crown is shaped like the helms of the Guards of the " +
        "Citadel, save that it is loftier, and it is all white, and the " +
        "wings at either side are wrought of pearl and silver in the " +
        "likeness of the wings of a sea-bird, for it is the emblem of the " +
        "kings who came over the Sea; and seven gems of adamant are set in " +
        "the circlet, upon its summit is set a single jewel the light of " +
        "which goes up like a flame."));

    set_ac(5);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    set_af(TO);

    add_prop(OBJ_I_VALUE,  50000);
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_S_WIZINFO, BSN("Is not the long description enough?"));
}

/*
 * This will allow you to (try to) crown someone.
 */
void
init()
{
    ::init();

    add_action("do_crown", "crown");
}

/*
 * The code for if you try to crown someone (or yourself)
 */
int
do_crown(string str)
{
    if (TP->query_real_name() == "olorin")
    {
        if (((str == "elessar") || (str == "aragorn")) &&
            (present("elessar", ENV(TP))))
        {
            NFN("The time to crown has not come yet.");
            return 0;
        }

        NFN("Find Aragorn son of Arathorn, chieftain of the Dunedain of " +
            "Arnor, Captain of the Host of the West, bearer of the Star of " +
            "the North, wielder of the Sword Reforged, victorious in " +
            "battle, whose hands bring healing, the Elfstone, Elessar of " +
            "the line of Valandil, Isildur's son, Elendil's son of Numenor, " +
            "before you try to set this crown on anyones head! Thou, " +
            "Mithrandir, shallt not behave like a fool!");
        return 0;
    }

    if (TP->query_real_name() == "elessar")
    {
        NFN("Thou shallt ask Mithrandir to set this crown on thy head.");
        return 0;
    }

    NFN("You do not have the right to crown anyone with this crown!");
    return 0;
}

/*
 * Redefine the wear function.. Most people are not worth it.
 */
int
wear()
{
    if (TP->query_real_name() == "elessar")
    {
        LSAY("As ", " wears the Crown, the jewel on top of it starts to " +
            "shine brightly.");
        write(BSN("As you wear the Crown, the jewel on top of it starts to " +
            "shine brightly."));
        add_prop(OBJ_I_LIGHT, 1);
        return 1;
    }

    if (TP->query_real_name() == "olorin")
    {
        write(BSN("You are only the Steward, not the King!"));
        return 0;
    }

    write(BSN("You do not have the right to wear the White Crown!"));
    return 0;
}

int
remove()
{
    if (query_prop(OBJ_I_LIGHT))
    {
        LSAY("As ", " removes the Crown, the jewel on top of it goes dark " +
            "again.");
        write(BSN("As you remove the Crown, the jewel on top of it goes " +
            "dark again."));
    }

    remove_prop(OBJ_I_LIGHT);
    return 1;
}

/*
 * Recovery code
 */
string
query_recover()
{
    return MASTER + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}

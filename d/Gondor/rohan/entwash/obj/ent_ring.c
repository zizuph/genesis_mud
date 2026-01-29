/*
 *  /d/Gondor/rohan/entwash/obj/ent_ring.c
 *
 *  This is one of the little surprises to be found in the Entwash
 *
 *  October 1995, by Gorboth
 */

inherit "/std/armour";
inherit "/d/Gondor/common/lib/friend_or_foe";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

//	Prototypes
varargs int set_clean(int i = 1);

//    global variables
int  clean,           // 1: clean ring, 0: dirty ring
     worn,            // 1: ring being worn, 0: ring not worn
     turned;          // 1: ring may not be turned, 0: ring turnable

void
create_armour()
{
    set_name("ring");
    set_short("metal ring");
    set_adj("metal");
    if (clean)
        add_adj("queer");
    else
        add_adj("dirty");
    set_long("@@exa_ring");
    set_at(A_ANY_FINGER);
    set_ac(1);
    set_af(TO);

    add_item(({"leaves on ring", "holly leaves on ring"}), BSN(
        "The leaves carved into the ring are splendid to behold. The"
      + " artist who crafted this metal spared no effort in his"
      + " mastery of shape and form."));

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 11);
    add_prop(OBJ_I_VALUE, 25);
    add_prop(MAGIC_AM_ID_INFO, ({
      "\n",1,
      "There seems to be something magical about this ring.\n",3,
      "This ring is contained of Elvish magic.\n",10,
      "This is one of the lesser Rings of Power, forged by elves ages ago.\n",25,
      "Turning this ring on your finger will bring an Elvish blessing upon you.\n",11 }));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, BSN("This is just a fun little secret that"
      + " can be found in a stream of the Entwash. It gives an emote,"
      + " nothing more."));
}

int
clean_ring(string str)
{
    if (!str)
    {
        return 0;
    }

    if (str == "ring" || str == "metal ring")
    {
        if (clean == 1)
        {
            NFN("As you are about to clean the ring, you notice that"
              + " it is not dirty!");
            return 0;
        }
        else
        {
            write(BSN("You carefully wipe the dirt and grime from the"
              + " metal ring. It looks quite different now!"));
            // I call this function to do the work.
            set_clean();
            return 1;
        }
    }

    return 0;
}

string
exa_ring()
{
    string desc;

    if (clean == 1)
    {
        desc = "This ring is most strange. It is a small circlet of"
          + " unknown metal, which has been cunningly formed to"
          + " resemble a growing vine. Holly leaves are carved into"
          + " the untarnished material.";
    }
    else
        desc = "This ring is very dirty. Earth and a film of some"
          + " sticky substance cover its surface. It looks as if"
          + " someone picked it up out of a mud puddle.";

    return BSN(desc);
}

int
wear(object obj)
{
    if (obj != TO)
    {
        return -1;
    }

    TP->wear_me();
    worn = 1;
    write(BSN("This ring feels exceedingly good on your finger."));

    return 1;
}

int
remove(object obj)
{
    write(BSN("As you remove the ring, your finger feels suddenly empty and cold."));
    worn = 0;

    return 1;
}

int
react_ring()
{
    if (TP->query_alignment() < 1)
    {
        write("You regain your self identity.\n");
        TP->command("ack");
        TP->command("spit");

        turned = 0;
        return 0;
    }

    write("You regain your self identity.\n");
    TP->command("peer laz");
    TP->command("sigh wist");

    turned = 0;
    return 0;
}

int
turn_ring(string str)
{
    object ring;
    
    if (!strlen(str))
    {
        return 0;
    }

    notify_fail("Turn the " + this_object()->short() + "?\n");

    if (!parse_command(str, ({ this_object() }), " %o ", ring))
	return 0;

    if (ring != this_object())
	return 0;

    if (turned)
    {
        write(BSN("You are swooning too heavily to turn the ring again."));
        return 1;
    }

    if (worn == 1)
    {
        if (clean == 1)
        {
            write(BSN("You turn the ring on your finger. Suddenly a"
              + " great longing wells up within you, a desire to gaze"
              + " at the stars, and to linger by the sea. You begin to"
              + " swoon as an ancient Elvish melody washes over your"
              + " senses."));
            say(QCTNAME(TP) + " pauses suddenly and stares into"
              + " the West with a look of great longing.\n", TP);
            turned = 1;
            set_alarm(5.0, 0.0, react_ring);

            return 1;
        }
        else
            write(BSN("You turn the ring on your finger, but all you"
              + " can feel is the dirt and grime rubbing between your flesh"
              + " and the metal."));

        return 1;
    }

    write("You are not wearing the ring!\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(clean_ring, "clean");
    add_action(turn_ring, "turn");
    add_action(turn_ring, "rotate");
}

varargs int
set_clean(int i = 1)
{
    if ((clean && i) || (!clean && !i))
    {
        // no change.
        return 0;
    }

    if (i) // make the ring clean
    {
        remove_adj("dirty");
        add_adj("queer");
        clean = 1;
    }
    else // make ring dirty
    {
        remove_adj("queer");
        add_adj("dirty");
        clean = 0;
    }

    return 1;
}


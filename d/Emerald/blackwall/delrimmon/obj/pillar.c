/*
 *  /d/Emerald/blackwall/delrimmon/obj/pillar.c
 *
 *  This pillar marks the place where the Torque Wearers were laid to
 *  rest after their deaths. It is yet a place of some enchantment, as
 *  the striving adventurer may discover.
 *
 *  Copyright (c) ?? 1997 by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/obelisk";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define MIN_SKILL       20
#define GOOD_SKILL      70

// Global Variables
public int     Mossy = 1; /* The pillar is covered with moss. */

//  Prototypes
string  exa_moss();
string  exa_runes();
string  get_pillar();
string  pillar_long();
int     clean_it(string str);
int     read_it(string str);
string  remove_moss();
public int     check_seen(object for_obj);

public void        set_mossy(int i) { Mossy = i; }

/*
 * Function name:        create_obelisk
 * Description  :        set up the obelisk
 */
public void
create_obelisk()
{
    set_name("pillar");
    add_name( ({"mound", "mound of vegetation", "vegetation"}) );

    add_adj( ({"thick", "mossy", "black", "stone",}) );

    set_short("black stone pillar");
    set_long(pillar_long);

    add_item( ({ "moss", "texture", "side", "sides", "stone",
                 "stone side", "stone sides", "side of the pillar",
                 "sides of the pillar", "moss on the pillar",
                 "pillars side", "pillars sides", "moss on pillar",
                 "black stone", "black stone sides", "surface",
                 "surface of the pillar", "pillar surface",
                 "black stone surface" }),
                 exa_moss);
    add_item( ({"rune", "runes", "letter", "letters",
                "carven letter", "carven letters",
                "marking", "markings", "character", "characters"}),
              exa_runes);

    add_cmd_item( ({"pillar", "stone pillar",
                    "ragged pillar",
                    "ragged stone pillar"}),
                  ({"clean"}), remove_moss);
    add_cmd_item( ({"pillar", "stone pillar",
                    "ragged pillar",
                    "ragged stone pillar",
                    "moss"}),
                  ({"search"}),
                 BSN("Inspecting the pillar thoroughly, you find"
                   + " that most of its surface has been covered"
                   + " by a thickly growing moss."));

    add_prop(OBJ_I_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 70000);

    add_prop(OBJ_M_NO_GET, get_pillar);
} /* create_obelisk */

string
exa_moss()
{
    if (Mossy)
    {
        return BSN("Thick moss covers nearly every inch of the"
                 + " pillar's surface. It grows thickly in"
                 + " clumps which obscure the texture of"
                 + " the stone beneath.");
    }

    return BSN("Most of the moss has been removed from the"
             + " surface, yet some bits and pieces remain,"
             + " rooted deeply in the recesses of runes"
             + " which have been carved in the black stone.");
}


string
get_pillar()
{
    return BSN("Tugging at the pillar reveals it to be quite"
             + " solidly embedded in the earth. There is no"
             + " use attempting to budge it.");
}

string
pillar_long()
{
    if (Mossy)
    {
        return BSN("Surrounded by brambles and trailers of thorn,"
                 + " this ancient pillar of stone has perhaps lain"
                 + " hidden beneath the undergrowth for centuries."
                 + " Its black stone surface is almost entirely"
                 + " overgrown with moss, obscuring the majority"
                 + " of its sides.");
    }

    return BSN("Surrounded by brambles and trailers of thorn,"
             + " this ancient pillar of stone has perhaps lain"
             + " hidden beneath the undergrowth for centuries."
             + " Its stone sides are completely black and smooth."
             + " It appears as if moss has been removed from most"
             + " of its surface, revealing what appear to be"
             + " carven letters in the stone.");
}

  
/*
 * Function name: read_it
 * Description:   Handle player attempts to read the runes.
 */
int
read_it(string str)
{
    int     ls,
            i,
            lack,
            seed;
    mixed   year;
    string  name,
            text,
           *t;

    FIX_EUID

    if (!strlen(str))
        NFN0("Read what?");

    if (str != "pillar" && str != "letter"
     && str != "letters" && str != "carven letters"
     && str != "runes" && str != "markings")
        NFN0("What do you wish to read?");

    say(QCTNAME(TP) + " crouches on bended knee to read the "
                    + QSHORT(TO) + ".\n");

    if (Mossy)
    {
        NFN0("You find no " + str + ".");
    }

    ls = TP->query_skill(SS_LANGUAGE);

    if (ls < MIN_SKILL)
    {
        write(BSN("The pillar is covered with strange characters."
                + " You recognize the letters to be some mode of"
                + " Elvish, the ancient writing of Telberin, yet"
                + " you lack the skill to read them."));

        return 1;
    }

    write(BSN("These letters appear to be written in a mode of ancient"
            + " Elvish, and have been marred by years of moisture and"
            + " corrosion. Yet, using your skill with languages you"
            + " make a guess at what they read:\n\n"));


    text = "\tHERE LIE THE TORQUE WEARERS\n\n"
         + "\tTRAGICALLY SLAIN IN THE\n"
         + "\tSERVICE OF THEIR CITY\n\n"
         + "\tTHEY NOW REMAIN HERE TO\n"
         + "\tWATCH OVER THE LAKE\n\n"
         + "\t     FORMANDIL\n"
         + "\t     ISLIN\n"
         + "\t     RANDIL\n"
         + "\t     LOCRAEL\n"
         + "\t     VIDMIN\n"
         + "\t     SELVIC\n";

    if (ls < GOOD_SKILL)
    {
        t = explode(text, "");
        seed = TP->query_name()[0];
        lack = ((ls - MIN_SKILL) / 3 + 2);
        for (i = 1; i < sizeof(t); i++)
            if (!random(lack, seed++) &&
                t[i] != " " && t[i] != "\n" && t[i] != "\t")
                t[i] = ".";
        text = implode(t, "");
    }
    write(text);

    return 1;
}

string
remove_moss()
{
    if (!Mossy)
    {
        return(BSN("The majority of the moss has been removed,"
                 + " but you toil some and get the stone"
                 + " surface slightly cleaner."));
    }
                 
    Mossy = 0;

    return(BSN("You carefully tear the moss from the stone to"
            + " reveal the black stone surface beneath."));
}

int
clean_it(string str)
{
    if (!strlen(str))
        NFN0("Remove what?");

    if (str != "moss" && str != "moss from pillar")
        NFN0("What do you wish to remove?");

    write(remove_moss());

    return 1;
}

string
exa_runes()
{
    string  tmpstr =  ENV()->query_exa_arg();

    if (Mossy)
    {
        if (strlen(tmpstr))
        {
            return("You find no " +tmpstr+ ".\n");
        }

        return("What?\n");
    }

    return BSN("The stone of this pillar is remarkably smooth and"
         + " black, and appears to have been completely resistant"
         + " to the ravages of time and weather. The letters in"
         + " surface are difficult to read, due entirely to the"
         + " dirt and remaining pieces of moss which cover them."
         + " You are able to make some of them out, however.");
}

void
init()
{
    ::init();

    add_action(read_it, "read");
    add_action(clean_it, "remove");
}


/*
 * Function name: check_seen
 * Description:   True if this object can be seen by a given object
 * Arguments:     for_obj: The object for which visibilty should be checked
 * Returns:       1 if this object can be seen.
 */
public int
check_seen(object for_obj)
{
    if (environment(this_object())->query_pillar())
    {
        return 1;
    }

    return 0;
} /* check_seen */

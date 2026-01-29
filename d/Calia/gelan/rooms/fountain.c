// ROOM:  fountain

    /* Calia Domain

    HISTORY

    Code containing the description of the most of the items in the fountain in
    Gelan. Originally coded by Snarf.

    Coin-related code (quest?) was not complete, so it was commented out by
    Maniac, 7.94
    Code to remove headaches when drinking / washing has been commented out for
    the time being, by Maniac 7.94
    Action for applicant task added Maniac 25/7/95
    Inherit from water room and made drinking have effect, Maniac, 2/8/96
    Added water vials to collect for Elemental Worshippers, Maniac, 6/11/96
    Made soaking more easy, Maniac, 17/12/96
    Stopped drinking if player is completely soaked, Maniac, 17/5/98
    Fixed typo, Maniac, 4/3/99

    [2001-04-04] Revised by Uhclem to prevent dragons from landing in the
    fountain and to deploy fountain_protection, an invisible object that
    provides protection against various evils.  The object is deployed to good,
    wise, and brave players who drink the water.  The entire file was
    restructured during this edit (headers added, spacing and line breaks
    changed, etc.) and stored on his computer as
    [C:\CALIA\GELAN\ROOMS\FOUNTAIN.DOC].
    */

// INCLUSIONS AND DEFINITIONS

#pragma save_binary

inherit "/d/Calia/std/water_room";

#include "snarfdefs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Calia/glykron/palace/specials/orange_task.h"

    /*
     *  The live_i_no_dragonfear property isn't in the standard collection as 
     *  of this writing, so it has to be defined explicitly.  We need to keep
     *  track of what we add to players and roving NPCs, so I created another
     *  property, calia_as_room_props, which keeps a list of the properties
     *  this room has added to each living.  When the player leaves this room,
     *  all properties in this list are removed.  The same properties modified
     *  by this room may also be modified by other Calian objects; if they are,
     *  they are deleted from calia_as_room_props so we'll know that the room
     *  is no longer responsible for managing them.    
     */

//protection-related objects:
#define FOUNTAIN_PROTECTION    "/d/Calia/gelan/specials/fountain_protection"

//protection-related properties:
#define LIVE_I_NO_DRAGONFEAR             "_live_i_no_dragonfear"
#define CALIA_AS_ROOM_PROPS              "_calia_as_room_props"
#define CALIA_I_FOUNTAIN_PROTECTION      "_calia_i_fountain_protection"
#define ROOM_M_DA_DRAGONSTEED_NO_LAND    "_room_m_da_dragonsteed_no_land"

#define TP this_player()

// GLOBAL VARIABLES

// FUNCTIONS

// Function:  statue(flag)

/*

Purpose:  provides description of statue.

Arguments:  string flag, specifies what part of the statue the player is
looking at.

Returns:  string containing description.

*/

string
statue(string flag)

{

    string text;
    text = "";

    if (flag == "2" || flag == "3")

    {

        text = text + "The dragon is a hideous creature and" +
            " seems to be writhing with pain and malice. It has" +
            " a slimy body covered with black and grey scales," +
            " more than the usual number of legs and heads" +
            " and long, sharp fangs. Like any respected" +
            " dragon, it belches dangerous, impressive" +
            " flames. The creature's leathery wings are" +
            " equipped with sharp talons. ";

    }

    if (flag == "1" || flag == "3")

    {

        text = text + "Caliana, the golden heroine, an" +
            " athletic figure, is holding a splendid, magic sword" +
            " in her right hand and a skilfully ornamented shield" +
            " in the left hand. She is wearing a golden helmet" +
            " on her shining long mane and her legs are" +
            " clad in golden leggings. On her athletic chest she" +
            " is carrying a golden platemail and over her" +
            " shoulders she is wearing a fluttering cape.";

    }

    return BS(text + "\n");

}

// Function:  shout(str)

/*

Purpose:  a special magical shout.

Arguments:  string str, contains words to be shouted; only "Praise Caliana"
invokes the magic.

Returns:  1/0.

*/

int
shout(string str)

{

    object tp = this_player();
    object ticket, coin;

    if ((str != "Praise Caliana") && (str != "praise Caliana") &&
        (str != "praise caliana") && (str != "Praise caliana"))

    {

        return 0;

    }

    tp->catch_msg("You shout out loudly: Praise Caliana!\n");

    tell_room(this_object(), QCTNAME(tp) + " shouts" +
        " out loudly: Praise Caliana!\n", tp);

    if (ticket = present(TICKET_NAME, tp))

    {

        tp->catch_msg("Your ticket turns into a crystalline coin!\n");
        ticket->remove_object();
        coin = clone_object(COIN);
        coin->move(tp);
        return 1;

    }

    else

    {

        tp->catch_msg("Nothing happens..\n");
        return 1;

    }

}

// Function:  drink(rest)

/*

Purpose:  drink water from the fountain.

Arguments:  string rest, expecting "water" and "fountain".

Returns:  1/0.

*/

int
drink(string rest)

{

    object tp = this_player();
    object protection;
    string x,y,z;
    int c;

    notify_fail("Drink what from what?\n");

    if (!rest)

    {

        return 0;

    }

    if ((sscanf(rest,"%sfrom %s",x,y)) != 2)

    {

        return 0;

    }

    if (!(x == "" || x == "water "))

    {

        return 0;

    }

    if (sscanf(y, "the %s", z))

    {

        y = z;

    }

    if (y != "fountain" && y != "pool")

    {

        return 0;

    }

    c = 0;

    while (tp->drink_soft(50, 0) && c < 15) c++;

    if (!c)

    {

        write("You have drunk all that you can.\n");
        return 1;

    }

    say(QCTNAME(tp) + " drinks some water" +
        " from the fountain.\n");

    write("You drink some water from the fountain.\n");

    /*
     *  Following section added by Uhclem to deploy the protection object. 
     *  There's some variation allowed in the player's discipline and wisdom,
     *  but alignment solidly in the good range is non-negotiable.    
     */

    if (tp->query_stat(SS_DIS) > (50 + random(50)) &&
        tp->query_stat(SS_WIS) > (50 + random(50)) &&
        tp->query_alignment() > (600 + random(600)) &&
        !tp->query_prop(CALIA_I_FOUNTAIN_PROTECTION))

    {

        protection = clone_object(FOUNTAIN_PROTECTION);
        protection->move(tp, 1);

    }

    return 1;

}

// Function:  wash(rest)

/*

Purpose:  wash in the fountain, hardly sanitary when other folks are drinking,
but reasonable in a medieval milieu.

Arguments:  string rest, expecting "self/face" and "fountain".

Returns:  1/0.

*/

int
wash(string rest)

{

    string  x,*pron,*pron1,*pron2;
    int     i,face;

    pron1 = ({"his face", "her face", "its face", "your face"});
    pron2 = ({"himself", "herself", "itself", "yourself"});

    if (!rest)

    {

        write("Wash what?\n");
        return 1;

    }

    if (sscanf(rest,"%sface%s",x,x))

    {

        pron = pron1;

    }

    else if (sscanf(rest,"%smyself%s",x,x))

    {

        pron = pron2;

    }

    else return 0;

    if ((sscanf(rest,"%swater%s",x,x) != 2) &&
        (sscanf(rest,"%sfountain%s",x,x) != 2) &&
        (sscanf(rest,"%spool%s",x,x) != 2 ))

    {

        return 0;

    }

    say((QCTNAME(TP) + " washes " + pron[(TP->query_gender())] +
        " in the fountain.\n"));

    write("You wash " + pron[3] + " in the fountain.\n");

    return 1;

}

// Function:  bath(rest)

/*

Purpose:  bathe in fountain; calls wash() function above.

Arguments:  string rest, " in fountain".

Returns:  1/0.

*/

int
bath(string rest)

{

    string x;

    if (!rest) return 0;

    if ((!(sscanf(rest, "%sfountain%s", x, x))) &&
        (!(sscanf(rest, "%swater%s", x, x))) &&
        (!(sscanf(rest, "%smyself%s", x, x))) &&
        (!(sscanf(rest, "%spool%s", x, x))))

    {

        return 0;

    }

    return wash("myself fountain");

}

// Function:  swim(foo)

/*

Purpose:  swim in fountain - not!.

Arguments:  string foo, really doesn't matter what it contains.

Returns:  1.

*/

int
swim(string foo)

{

    write("The fountain isn't deep enough for you to swim in.\n");
    return 1;

}

// Function:  collect(str)

/*

Purpose:  collect vials at bottom of fountain.

Arguments:  string str, expecting "vials".

Returns:  1/0.

*/

int
collect(string str)

{

    object vial;
    int num;

    if (str != "vials")

    {

        notify_fail("Collect vials?\n");
        return 0;

    }

    vial = clone_object("/d/Calia/worshippers/objects/water_vial");
    num = 3 + random(6);
    vial->set_heap_size(num);

    if (!vial->move(this_player()))

    {

        write("You collect " + num + " water vials from the fountain.\n");
        say(QCTNAME(TP) + " collects some water vials from the fountain.\n");
        return 1;

    }

    write("Hmm, you had trouble collecting the vials for some reason.\n");
    return 1;

}

// Function:  init()

/*

Purpose:  initialize local commands.

Arguments:  none.

Returns:  nothing.

*/

void
init()

{

    ::init();
    add_action(drink,"drink",0);
    add_action(wash,"wash",0);
    add_action(bath,"bath",0);
    add_action(swim,"swim",0);
    add_action(shout, "shout");
    add_action(collect, "collect");

}

// Function:  enter_inv(ob, where_from)

/*

Purpose:  detect when someone enters the room and apply appropriate magic
effects due to proxmity of statue and fountain.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object where_from)

{

    ::enter_inv(ob, where_from);

    /*
     *  There are no effects applied to nonliving objects, and wizards are 
     *  exempt from this process.    
     */

    if (!living(ob) || ob->query_wiz_level())

    {

        return;

    }

    /*
     *  Add the no_dragonfear property - and record it in the list - only if it 
     *  is not already present.    
     */

    if (!ob->query_prop(LIVE_I_NO_DRAGONFEAR))

    {

        ob->add_prop(LIVE_I_NO_DRAGONFEAR, 1);

        if (!ob->query_prop(CALIA_AS_ROOM_PROPS))

        {

            ob->add_prop(CALIA_AS_ROOM_PROPS, ({LIVE_I_NO_DRAGONFEAR}));

        }

        else

        {

            ob->add_prop(CALIA_AS_ROOM_PROPS,
                ob->query_prop(CALIA_AS_ROOM_PROPS) +
                ({LIVE_I_NO_DRAGONFEAR}));

        }

    }

}

// Function:  leave_inv(ob, where_to)

/*

Purpose:  remove all room-applied properties from the player as he leaves.

Arguments:  object leaving the room, object destination.

Returns:  nothing.

*/

void
leave_inv(object ob, object where_to)

{

    string *prop_list = ob->query_prop(CALIA_AS_ROOM_PROPS);

    ::leave_inv(ob, where_to);

    /*
     *  There are no effects applied to nonliving objects, wizards are exempt 
     *  from this process, and there's no need to do anything if no properties
     *  have been added.    
     */

    if (!living(ob) || ob->query_wiz_level() || !prop_list)

    {

        return;

    }

    while (sizeof(prop_list))

    {

        ob->remove_prop(prop_list[0]);
        prop_list -= ({prop_list[0]});

    }

    ob->remove_prop(CALIA_AS_ROOM_PROPS);

}

// ROOM DEFINITION

void
make_fountain()

{

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_S_MAP_FILE, "gelan_map.txt");

    add_prop(ROOM_M_DA_DRAGONSTEED_NO_LAND,
        "No dragon can land so close to the statue of Caliana" +
        " slaying one of their kind!\n");

    add_item(({"bottom", "bottom of the fountain", "bottom of fountain",
        "bottom of pool", "bottom of the pool"}),
        "The bottom of the fountain is made of some kind of" +
        " magical stone. You notice hundreds of tiny water" +
        " vials scattered down there. You could probably collect" +
        " them if you wanted.\n");

    add_item(({ "objects", "tiny objects", "tiny vials", "tiny water vials",
        "water vials", "vials"}),
        "There are hundreds of tiny water vials resting at the" +
        " bottom of the fountain.. or perhaps they are" +
        " just refractions of light on the stone? You" +
        " could always try collecting them.\n");

    add_item(({"Caliana", "caliana", "golden heroine", "heroine"}),
        BS("@@statue|1"));

    add_item(({"dragon", "black dragon"}), BS("@@statue|2"));

    add_item(({"statue", "mighty statue", "golden statue",
        "mighty golden statue"}), BS("@@statue|3"));

    add_item("fountain",
        "The fountain is a large round pool, filled with deep" +
        " blue water. There seem to be tiny objects" +
        " scattered on the bottom.\n");

    add_item(({"pool", "large pool", "round pool", "large round pool"}),
        "The pool is filled filled with deep blue water. There seem" +
        " to be tiny objects scattered on the bottom.\n");

    add_item(({"water", "blue water", "deep blue water"}),
        "The water has a deep blue color and feels very smooth.\n");

}

/*
 * /d/Gondor/ithilien/forest/orcrefuse.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"

#define LOST_RANGER_SEARCHER   "_ranger_i_searching_for_lost_ranger"
#define MIN_AWARE  20

object    Corpse, Corpse2, Vulture;
int    Pot_here;

public string   do_search(object searcher, string str);
public void     enter_inv(object ob, object from);
public void     add_vulture();
public int      do_smell(string arg);

public void
create_gondor()
{
    set_short("At the northwest edge of an orcish camp in Ithilien");
    set_long("There is a large pile of refuse at this edge "+
    "of the camp. The stench from the garbage is so strong that "+
    "it is difficult to breathe without gagging. "+
    "To the south is what looks like a palisade, and east is more of "+
    "the camp. The green woods of Ithilien continue north and west.\n");
    add_item( ({ "matter", "pile", "pile of refuse", "refuse",
    "garbage" }),
    "The pile contains rotten food and garbage, orc corpses "+
    "infested with worms, worn-out pieces of clothing and "+
    "equipment, and other matter so decayed as to be "+
    "unrecognizable.\n");
    add_item( ({ "worm", "worms", "maggot", "maggots"}), 
    "The corpses are infested with slick white worms.\n");
    add_item("food", 
    "The food is quite rotten, and probably was not very appetizing "+
    "even when fresh.\n");
    add_item( ({ "orc corpses", "corpses" }),
    "The dead orcs probably died from wounds or bad food.\n");
    add_item("palisade", 
    "A crude palisade has been erected to the south.\n");
    add_item("camp", 
    "Tents fill the clearing to the east.\n");
    add_item(({"palisade"}),
        "It is a barrier forming a strong defense to protect the camp. " +
        "It is made of of broken trees and other rubble.\n");
    add_item(({"tents", "tent"}),
        "The tents are made from canvas with many patches on them. They " +
        "look ratty and barely adequate to keep the elements out.\n");
    add_item(({"canvas"}),
        "It is ratty and heavy-duty. It's used to make the tents the camp.\n");
    

    add_exit(ITH_DIR+"forest/orcpost2","south",0);
    add_exit(ITH_DIR+"forest/orccamp2","east",0);

    add_prop(OBJ_S_SEARCH_FUN,"do_search");

    reset_room();
}

public void
reset_room()
{
    FIX_EUID;

    if ( !Corpse )
    (Corpse = clone_object(ITH_DIR+"forest/corpse"))->move(TO);
    set_alarm(5.0, 0.0, "add_vulture");
    if ( !Corpse2 )
    (Corpse2 = clone_object(ITH_DIR+"forest/rcorpse"))->move(TO);
    Pot_here = 1;
}


public void
init()
{
    ::init();
    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_smell, "inhale");
}

public string
do_search(object searcher, string str)
{
    object    pot;

    if ( str != "garbage" && str != "refuse" && str != "pile" &&
    str != "pile of garbage" && str != "pile of refuse" )
    return "";

    write("Searching through the pile of garbage makes you feel sick.\n");
    say("With horror you notice that " +
    QTNAME(searcher) +
    " searches through the stinking pile of garbage.\n");

    if ( !Pot_here ||
    searcher->query_skill(SS_AWARENESS) < (MIN_AWARE + random(MIN_AWARE)) )
    return BSN("Reluctantly you sift through the garbage pile, "+
           "but you don't find anything of interest.");

    FIX_EUID;
    pot = clone_object(OBJ_DIR + "pot");
    pot->set_dirty(1);
    Pot_here = 0;
    if ( pot->move(searcher) )
    pot->move(TO);
    SAY(" seems to have found something of interest among all that garbage.");
    return BSN("Among all the garbage you find an old battered pot. "+
    "It seems to be without holes, but it is very dirty.");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if ( ob->query_prop(LOST_RANGER_SEARCHER) == 1 )
    {
    if ( !objectp(Vulture) )
        add_vulture();
    clone_object(ITH_DIR+"forest/ring")->move(Vulture);
    ob->add_prop(LOST_RANGER_SEARCHER, 2);
    }
}

public void
add_vulture()
{
    if ( !objectp(Vulture) )
    {
    Vulture = clone_object(NPC_DIR+"vulture");
    Vulture->set_restrain_path(ITH_DIR+"forest/orcrefuse");
    tell_room(TO,
        "A vulture comes flying, and lands on the refuse pile.\n");
    Vulture->move(TO);
    }
}

/*
 * Function name:       do_smell
 * Description:         handle attempts to smell/sniff
 * Arguments:           string arg -- whatever the player typed
 * Returns:             1 if we understand arg, 0 if not
 */
public int
do_smell(string arg)
{
    if ( !arg || arg == "matter" || arg == "pile" ||
    arg == "pile of refuse" || arg == "refuse" || arg == "garbage" ||
    arg == "food" || arg == "orc corpses" || arg == "corpses" )
    {
        write(BSN("The stench of the refuse makes it difficult to "+
           "breathe without gagging."));
        return 1;
    }
    return 0;
}

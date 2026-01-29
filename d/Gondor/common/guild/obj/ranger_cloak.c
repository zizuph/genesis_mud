/*
 * /d/Gondor/common/guild/obj/ranger_cloak.c
 *
 * The cloaks of the rangers.
 *
 * Original version by Elessar.
 *
 * This version by Olorin, December 1996
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 */
#pragma save_binary
#pragma strict_types

inherit "/std/armour.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define HIS(x)  ((x)->query_possessive())

static  object  Shadow;
static  string  Shadow_File,
               *Hood_Adjs = ({ "green-cloaked", "hooded" });

/*
 * Function mame: set_shadow_file
 * Description:   set the Shadow_File
 * Argument:      string file: the path name to the shadow
 */
public void
set_shadow_file(string file)
{
    Shadow_File = file;
}

/*
 * Function name: set_hood_adjs
 * Description:   Set the adjectives used for hooded players.
 * Argument:      *adjs - the two adjectives
 * Returns:       1 / 0 - success / failure
 */
public int
set_hood_adjs(string *adjs)
{
    if (!pointerp(adjs) || (sizeof(adjs) != 2))
        return 0;

    Hood_Adjs = adjs;
    return 1;
}

/*
 * Function name: create_cloak
 * Description:   creator
 */
public void
create_cloak()
{
    add_adj(({"dark-green", "green", "spotted", }));
    set_short("dark-green spotted cloak");
    set_long("This is a hooded cloak made of heavy dark-green cloth. "
      + "To help the wearer to walk unseen through glades and "
      + "forests, the cloak is spotted in various hues of brown and "
      + "green.\n");
    set_hood_adjs( ({ "green-cloaked", "hooded" }) );
}

nomask void
create_armour()
{
    set_name("cloak");
    add_name(({ "armour" }));
    set_adj(({ "hooded", "ranger", "heavy", }));
    set_default_armour(3, A_ROBE, (({ 0, 0, 1})), TO);

    add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
    add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3) + random(20));

    set_shadow_file(RANGER_DIR + "obj/hood_shadow");

    create_cloak();
}

public mixed 
remove(object arm)
{
    if (TP->query_hooded())
        Shadow->remove_shadow();
    return 0;
}


public int
do_hood(string str)
{
    string  vb = query_verb(),
            pron;
 
    if (vb == "hood")
        pron = "whom";
    else
        pron = "what";
 
    NFN(CAP(vb)+" "+pron+"?");
    if (!strlen(str))
        return 0;
 
    if ((vb == "hood") && (str != "me" && (LOW(str) != ENV(TO)->query_real_name())))
        return 0;
 
    if ((vb == "wear") && (str != "hood"))
        return 0;
 
    if (ENV(TO) != TP)
    {
        NFN("You do not have the cloak!");
        return 0;
    }
 
    if (query_worn() != TP)
    {
        NFN("You do not wear your cloak!");
        return 0;
    }
 
    if (TP->query_hooded())
    {
        NFN("You are already wearing your hood!");
        return 0;
    }
 
    if (!IS_RANGER(TP))
    {
        NFN0("Only Rangers can do that.");
    }
    write("You draw the hood of your cloak over your head, hiding "
        + "your face within the cowl.\n");  
    say(QCTNAME(TP) + " draws the hood of " + HIS(TP) + " cloak over "
        + HIS(TP) + " head, hiding " + HIS(TP) + " face within the "
        + "cowl.\n"); 
 
    FIX_EUID
    Shadow = clone_object(Shadow_File);
    Shadow->set_hood_adjs(Hood_Adjs);
    Shadow->shadow_me(TP);
    return 1;
}
 
public int
do_reveal(string str, int silent = 0)
{
    string  vb = query_verb(),
            pron;
 
    switch (vb)
    {
        case "unhood":
            pron = "whom";
            break;
        case "mreveal":
            vb = "remove";
        case "remove":
            pron = "what";
            break;
    }
 
    NFN(CAP(vb)+ " "+pron+"?");
    if (!strlen(str))
        return 0;
 
    switch (vb)
    {
        case "unhood":
            if (str == "me")
                break;
            if (LOW(str) == ENV(TO)->query_real_name())
                break;
            NFN("You can only remove your own hood!");
            return 0;
            break;
        case "remove":
            if (str != "hood")
                return 0;
            break;
    }
 
    if (ENV(TO) != TP)
    {
        NFN("You do not have the cloak!");
        return 0;
    }
 
    if (!TP->query_hooded())
    {
        NFN("You are not wearing your hood!");
        return 0;
    }
 
    if (!silent)
    {
        write("You remove the hood and reveal your face again.\n");
        say(QCTNAME(TP)+" removes "+HIS(TP)+" hood.\n");
    }
 
    Shadow->remove_hood_shadow();
    return 1;
}
 
public void
init()
{
    ::init();
 
    add_action(do_hood, "hood");
    add_action(do_hood, "wear");
    add_action(do_reveal, "mreveal");
    add_action(do_reveal, "unhood");
    add_action(do_reveal, "remove");
}
 
public void
leave_env(object from, object to)
{
    if (from->query_hooded())
    {
        Shadow->remove_shadow();
    }
 
    ::leave_env(from, to);
}

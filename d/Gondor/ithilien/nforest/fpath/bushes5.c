/*
 *      /d/Gondor/ithilien/nforest/fpath/bushes5.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      1996, Olorin: Changed inheritance.
 *      May 5, 2004: Tweaked slightly by Tigerlily
 *          for ranger recode
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#ifndef NEW_RANGERS_OPEN
#define COUNCIL                  (RANGER_DIR + "council")
#define GUILD_NAME               "Gondorian Rangers Guild"
#endif
//else
#ifdef NEW_RANGERS_OPEN
#define GUILD_NAME               "Rangers of the Westlands"
#endif

#define RANGER_ITHILIEN_FOUND    "ranger_ithilien_found"
#define RANGER_ITHILIEN_VISITOR  "ranger_ithilien_visitor"
#define MIN_SKILL                (75 + random(26))
#define ENTRANCE  (RANGERS_ITH_DIR + "entrance")

public string  enter_bushes();
public string  exa_bushes();
public string  exa_forest();
public string  exa_ground();

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("stream");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress ");
    set_extraline("The noise of a rushing stream to the north subdues " +
        "the sound of singing birds here. You can hear the sound of a " +
        "waterfall to the northwest. The land descends rapidly to the " +
        "west, and you can see the lowlands and meadows in the Vale of " +
        "Anduin. The green forests grow denser to the south, ruling " +
        "out the bushes and thickets that grow in abundance here.");

    set_up_herbs( ({ HERB_DIR + "suranie", HERB_DIR + "attanar", 
        HERB_DIR + "tyelka",  HERB_DIR + "foxglove", }),
       ({ "bushes", "thickets", "ground"}), 3);

    add_item("stream", BSN("The stream is hidden behind the bushes " +
        "and the rock to the north. You hear the sound of a waterfall " +
        "further northwest."));
    add_cmd_item( ({ "water", "water from stream" }), "drink",
        BSN("The stream is hidden behind the bushes to the north. You " +
        "cannot reach it to drink from it."));
    add_item( ({"rock","cliff"}), BSN(
        "The giant rock to the north rises like a dark shadow out of the " +
        "forest to the north. The sheer cliff face is completely free of " +
        "vegetation and without any features that might make it possible " +
        "to climb it."));
    add_item("waterfall", BSN("You cannot see the waterfall, but you can " +
        "hear the water falling northwest of you. It sounds like it is quite " +
        "a fall."));
    add_item(({"forest", "wood", "woodlands", "herbs"}), &exa_forest());
    add_item(({"ground", "path", "tracks"}), &exa_ground());
    add_item(({"bushes", "thicket", "thickets"}), &exa_bushes());

    add_cmd_item( ({ "bushes", "thicket", }), "enter",
        &enter_bushes());
    add_exit(ITH_DIR + "nforest/fpath/bushes4",   "southeast", 0, 3);
    add_exit(ITH_DIR + "nforest/fpath/waterfall", "west",      0, 1);
}

private int 
query_allowed(object pl)
{
    if (pl->query_ranger_level() > 2)
        return 1;

    /* Uncomment if all rangers should be allowed */
#ifndef NEW_RANGERS_OPEN
    if (pl->query_guild_name_occ() == "Gondorian Rangers Guild") 
        return 1;
#endif

#ifdef NEW_RANGERS_OPEN
    if (!objectp(find_object(ENTRANCE)))
        ENTRANCE->teleledningsanka();
    if ((RANGERS_FULL_MEMBER(pl)) || 
        pl->query_prop(RANGER_ITHILIEN_VISITOR) ||
        ENTRANCE->query_allowed(pl->query_real_name()) ||
        MANAGER->query_voted_in(pl->query_real_name(), "ithilien"))
        return 1;
#endif
    if (IS_GONDOR_WIZARD(pl))
        return 1;
    if (pl->query_prop(RANGER_ITHILIEN_VISITOR)) 
        return 1;
    if (pl->query_prop(RANGER_ITHILIEN_FOUND) >= 6) 
        return 0;
    return 0;
}

private int 
enter_wrong(object pl)
{
    pl->move_living("into the bushes", ITH_DIR + "nforest/fpath/waterfall");
    return 1;
}

private int 
enter_passage(object pl)
{
#ifndef NEW_RANGERS_OPEN
    pl->move_living("into the bushes", 
        "/d/Gondor/common/guild/ithilien/entrance");
#endif
//else
#ifdef NEW_RANGERS_OPEN
    pl->move_living("into the bushes", RANGERS_ITH_DIR + "entrance");
#endif
    return 1;
}

public string
enter_bushes()
{
    object tp = this_player();
    tp->catch_msg("You enter the bushes.\n");
    if (query_allowed(tp)) 
        enter_passage(tp);
    else 
        enter_wrong(tp);
    return "";
}

private int 
check_track(object player)
{
    int     track  = player->query_skill(SS_TRACKING),
            aware  = player->query_skill(SS_AWARENESS);

#ifndef NEW_RANGERS_OPEN
    if (player->query_skill(SS_PUNISHMENT) == NOACCESS) 
        return 0;
#endif

  

#ifdef  NEW_RANGERS_OPEN 
    if ((ITHILIEN_MEMBER(player)) || 
        player->query_prop(RANGER_ITHILIEN_VISITOR) ||
        MANAGER->query_voted_in(player->query_real_name(), "ithilien") ||
        IS_GONDOR_WIZARD(player))

        return 4;
    if (RANGERS_MEMBER(player))
        return 3;
#endif

//else

#ifndef  NEW_RANGERS_OPEN 
//old ranger Ithilien designation
    if ((player->query_company() == "Ithilien") || 
        player->query_prop(RANGER_ITHILIEN_VISITOR) ||
        IS_GONDOR_WIZARD(player))
        return 4;
    if (player->query_company()) 
        return 3;
#endif


    if (player->query_prop(RANGER_ITHILIEN_FOUND) >= 6) 
        return 2;
    if ((track+aware)/2 >= MIN_SKILL) 
    {
        player->add_prop(RANGER_ITHILIEN_FOUND, 6);
        return 1;
    }
    return 0;
}

public string 
exa_bushes()
{
    int     ic;
    string  desc = "Bushes are growing all around you. The bushes are "
        + "green and fair, with a delicate fragrance.";
  
    switch (check_track(TP))
    {
    case 4: 
        desc += " You are certain that entering these bushes will take you " +
            "to the Henneth Annun, the secret hideout of the Rangers of Ithilien!";
        break;
    case 3:
    case 2: 
        desc += " You see a path behind these bushes. Enter the bushes to reach it.";
        break;
    case 1: 
        desc += " You discover a well hidden path behind the bushes! " +
            "Enter the bushes to reach it.";
            break;
    default:
        break;
    }
    return BSN(desc);
}

public string 
exa_forest()
{
    string  desc = "These are the woodlands of Ithilien, with tall green " +
        "trees, mostly rowans and cypresses, dominating most of the view " +
        "to the south and north. The forest is less dense along the stream " +
        "however, which can be heard from the north.";
    if (check_track(TP))
        desc += " Looking carefully, you can make out a few tracks on the ground.";
    desc += " Many herbs of different forms and scents fill the air with " +
        "sweet and pungent smells. ";
    
    return BSN(desc);
}

public string 
exa_ground()
{
    string desc;
    int ic;
    
    if (ic = check_track(TP))
    {
        desc = "Looking carefully, you can make out several tracks " +
            "among the dry leaves and twigs on the floor. Following " +
            "the tracks, you find that the hidden path continues " +
            "behind the bushes. Enter them to follow the path.";
        if (ic == 4)
            desc += " You know that this is the path to the Henneth " +
                "Annun, the secret hideout of the Rangers of Ithilien.";
    }
    else
        desc = "There are mostly dry leaves and moss on the forest " +
            "floor, and a few tracks leading east and southeast. ";
    
    return BSN(desc);
}

static mixed
parse_this(string str, string form)
{
    object *oblist,
           *tmplist = ({ });
    int     i;

    if (!CAN_SEE_IN_ROOM(TP))
        return tmplist;
  
    if (!strlen(str) || (!parse_command(LOW(str), ENV(TP),
         form, oblist)))
        return ({ });
  
    oblist = NORMAL_ACCESS(oblist, 0, 0);
  
    if (!sizeof(oblist))
        return ({ });
    for (i = 0; i < sizeof(oblist); i++)
    {
        if (objectp(oblist[i]) && living(oblist[i]) &&
            (this_player() != oblist[i]) &&
            CAN_SEE(this_player(), oblist[i]))
            tmplist = tmplist + ({ oblist[i] });
    }
    return tmplist;
}

public int 
do_welcome(string str)
{
    object *strangers;
    object tp = this_player();
    int     i = -1, 
            s;

#ifndef  NEW_RANGERS_OPEN 
    if (tp->query_guild_name_occ() != GUILD_NAME)
    {
        notify_fail("What ?\n");
        return 0;
    }
#endif

#ifdef NEW_RANGERS_OPEN
    if (!RANGERS_MEMBER(tp) && !tp->query_wiz_level())
    {
        notify_fail("What ?\n");
        return 0;
    }
#endif
    
    NFN("Welcome whom?");
    if(!strlen(str))
        return 0;

#ifndef  NEW_RANGERS_OPEN 
    /* Only the Captain can invite strangers into the Henneth Annun! */
    if ((COUNCIL->query_ithilien() != tp->query_name()) && !tp->query_wiz_level())
    {
        NFN("Only the Captain of the Rangers of Ithilien can invite " +
           "strangers into the Henneth Annun!"); 
        return 0;
    }
#endif

#ifdef  NEW_RANGERS_OPEN 
    if (!MANAGER->query_council(tp->query_real_name(), "ithilien") && 
         !tp->query_wiz_level())
        notify_fail("Only the Captain of the Rangers of Ithilien " +
            "can invite strangers into the Henneth Annun!\n"); 
        return 0;
#endif

    strangers = parse_this(str,"%l");

    NFN("Welcome whom?");
    if (!(s = sizeof(strangers)))
        return 0;
  
    while(++i < s)
    {
        if(strangers[i]->query_guild_name_occ() == GUILD_NAME)
        {
            TP->LCATCH_MSG("You do not need to invite ",".",strangers[i]);
            write("As a ranger, " + strangers[i]->query_pronoun() +
                " can enter the hideout without invitation!\n");
        }
        else
        {
            TP->LCATCH_MSG("You invite ", " to visit the secret " +
               "hideout of the Rangers of Ithilien! ",
                strangers[i]);
            strangers[i]->CATCH_MSG(" invites you to visit the " +
                "Henneth Annun, the Window on the West, " +
                "the secret hideout of the Rangers of Ithilien!", TP);
            say(QCTNAME(TP) + " whispers something to " + QTNAME(strangers[i]) + ".\n",
                ({TP, strangers[i]}) );
            strangers[i]->add_prop("ranger_ithilien_visitor",TP->query_name());
        }
    }
  
    return 1;
}

public void 
init()
{
    ::init();
    add_action(do_welcome,   "welcome");
}

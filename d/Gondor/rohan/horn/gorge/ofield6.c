/*
 * /d/Gondor/rohan/horn/burg/tow_enter.c
 *
 * Modification history:
 *
 * 21-Dec-97, Gnadnar: general cleanup 
 */

inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/rohan/horn/hd_defs.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
#include "/d/Gondor/common/lib/herb_list.h"

public int	give_player_xp(object player);
public string	find_tracks();
public int	enter_bush(string str);
public int	climb_tree(string str);
public int	get_rope(string str);
public int	kill_orc(string str);
public string	tree_desc(string arg);
public int	call_helmsdeep_guard(object blower);
public void	scene2();
public void	scene3();
public void	scene4();
public void	scene5();
public void	scene6();
public void	scene7();
public void	scene8();
public void	scene9();
public void	scene10();
public void	remove_corpse();

#define		EMPTY_TREE		0
#define		ROPE_IN_TREE		1
#define		ORC_IN_TREE		2
#define		CORPSE_IN_TREE		3
#define		USED_ROPE_IN_TREE	4

static object	*Guards = allocate(3), Erkenbrand;
static object	Orc, Quest_solver;
static int	State = EMPTY_TREE;

public int
give_player_xp(object player)
{
    if (player->test_bit("Gondor", GONDOR_GROUP, SPYING_ORC_BIT))
        return 0;
    player->set_bit(GONDOR_GROUP, SPYING_ORC_BIT);
    player->add_exp_quest(SPYING_ORC_EXP);
    LOG_QUEST(player, SPYING_ORC_EXP, "Spying Orc");
    player->catch_msg("You feel more experienced!\n"); 
    return 1;
}

public void
create_helmsdeep_room()
{
    int     i;
    string *herbs;

    set_short_desc("A grassy field");
    set_extra_long("A grassy field at the end of the Dike. The northern "+
	"cliff, its base obscured by bushes, rises high above the lush grass. "+
	"An oak tree grows quite close to the cliff, and the field "+
	"stretches away from the cliff to the southeast. ");

    set_track_dir2("southeast");

    add_item( ({ "branch", "branches", "oak tree", "oak", "tree"}),
	&tree_desc("tree") );
    add_item( ({ "bush", "bushes" }),
	BSN("The bushes are low and dense."));
    add_item( ({ "northern cliff", "northern cliffs", "cliff", "cliffs" }),
    	BSN("The northern cliff rises high and steep, impossible to climb."));
    add_item( ({ "wall", "tower", "keep", "hornburg"}),
	BSN("To the south, the Rock rises steeply. "+
	"High on the ridge, there's a wall, and behind that a tower."));
    add_item( ({ "ridge", "rock" }),
	BSN("Upon the Rock, the keep is built."));
    add_item( ({ "dike", "Dike" }),
	BSN("The Dike is the outer fortification of the fastness. The Dike ends "+
	"here at the northern cliff."));
    add_item( ({ "ground", "track", "tracks", "footprint", "footprints" }),
    	find_tracks);
    FIELD;
    GRASS;
    GORGE;
    MOUNTAINS;

    add_exit(ROH_DIR+"horn/gorge/ofield5","southeast",0);

    herbs = ({ HERBS[random(sizeof(HERBS))],
               HERBS[random(sizeof(HERBS))],
               HERBS[random(sizeof(HERBS))] });
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,8);

    set_search_places(({"gorge", "grass", "ground", "slope"}));
    for(i = 0; i < sizeof(herbs); i++)
        add_herb_file(herbs[i]);
}

public void
init()
{
    ::init();
    add_action(enter_bush, "enter");
    add_action(climb_tree, "climb");
    add_action(get_rope, "get");
    add_action(get_rope, "take");
    add_action(get_rope, "pick");
    add_action(kill_orc, "kill");
}

public string
long_desc()
{
    string desc;
    desc = ::long_desc();
    if ( State == ORC_IN_TREE )
	desc += BSN("From a rope looped round a branch of the oak tree, there "+
	    "dangles a terrified orc, kicking frantically and clawing at the "+
	    "noose encircling his neck.");
    else if ( State == CORPSE_IN_TREE )
	desc += BSN("From a rope looped round a branch of the oak tree, there "+
	    "dangles an orc corpse, slowly swaying in the wind.");

    /* probably wouldn't notice an empty rope until you actually
     * examined the tree
     */
    return desc;
}

public string
find_tracks()
{
    string track_desc;
    int skill;

    skill = TP->query_skill(SS_TRACKING);
    switch(skill)
    {
        case 0..TRACK_LOW : 
            track_desc = "You find nothing special. ";
            break;
        case TRACK_LOW + 1..TRACK_HIGH :
            if(TP->query_prop(FOUND_ORC))
                track_desc = "You follow the tracks but they disappear in "+
                "the rocky ground close to the cliff. ";
            else
                track_desc = "You find nothing special. ";
            break;
        case TRACK_HIGH + 1..100 :
            if(TP->query_prop(FOUND_ORC))
                track_desc = "You follow the tracks but they disappear in "+
                "the rocky ground close to the cliff. Very faintly can you "+
                "also see some orc "+
                "tracks leading to the "+ track_dir2 +". It looks as if an "+
                "attempt to cover the tracks leading to the burg "+
                "has been made. ";
            else
                track_desc = "Very faintly can you see some orc tracks "+
                "leading to the "+ track_dir2 +". It looks as if an "+
                "attempt to cover the tracks has been made. ";
            break;
        default :
            break;
    }
    return BSN(track_desc);
}

public int
enter_bush(string str)
{
    if (str == "bush" || str == "bushes")
    {
        write(BSN("You force your way into the dense bushes, but find "+
	    "nothing of interest. You emerge into the field again."));
        SAY(" enters the bushes, but soon emerges.");
        return 1;
    }
    NFN0("Enter what?");
}

public int
climb_tree(string str)
{
    if ( str != "tree" && str != "oak" && str != "oak tree" )
    {
        NFN0("Climb what?");
    }

    if ( TP->query_skill(SS_CLIMB) < 5 )
    {
            write(BSN("You attempt to climb the tree, but can't quite "+
		"manage it."));
            SAY(" makes some attempt to climb the tree, but fails.");
    }
    else if ( State == ROPE_IN_TREE || State == ORC_IN_TREE )
    {
	write("You approach the tree.\n");
	SAY(" approaches the tree.");
	Guards[0]->command("say Keep back there!");
	Guards[1]->command("say Can't you see we're busy here?");

    }
    else if ( State == CORPSE_IN_TREE )
    {
	write(BSN("As you start to hoist yourself up, the dangling corpse "+
	    "bumps you off the branch. You fall to the ground."));
	SAY(" starts to climb the tree, but bumbles into the corpse and falls.");
    }
    else if ( State == USED_ROPE_IN_TREE )
    {
	write(BSN("You start to hoist yourself into the tree, but become "+
	    "entangled with the rope and fall to the ground."));
	SAY(" starts to climb the tree, but becomes entangled "+
	    "with the rope and falls.");
    }
    else
    {
            write(BSN("You climb up to the lowest branch, but "+
            	"find nothing unusual. You return to the ground."));
            SAY(" climbs up into the tree, then quickly climbs down again.");
    }
    return 1;
}

public int
call_helmsdeep_guard(object blower)
{
    object	tower;
    FIX_EUID;
    if ( !blower->query_prop(FOUND_ORC) || !blower->query_prop(SHOWN_MAP) ||
    !blower->query_prop(MADE_REPORT) )
    {
        ::call_helmsdeep_guard(blower);
        return 0;
    }
    TOW_ROOM->short();
    tower = find_object(TOW_ROOM);
    tower->move_guards();
    Erkenbrand = tower->query_erkenbrand();
    Guards = tower->query_guards();
    Erkenbrand->command("emote looks around.");
    Erkenbrand->command("introduce me");
    Quest_solver = blower;
    set_alarm(3.0, 0.0, "scene2");
    return 1;
}

public void
scene2()
{
    Erkenbrand->command("say Spread out and search those bushes.");
    tell_room(TO, "The guards start prodding the bushes with their spears.\n");
    set_alarm(8.0, 0.0, "scene3");
}

public void
scene3()
{
    Orc = clone_object(ROH_DIR + "horn/npc/scared_orc");
    Orc->move(TO);
    tell_room(TO, "An orc appears!\n");
    Orc->command("emote makes a wild dash to escape.");
    Guards[0]->command("emote captures the orc when he tries to flee.");
    TO->add_prop(ROOM_M_NO_ATTACK,
	"Guard says: Hey! Hands off the prisoner!\n");
    TO->add_prop(ROOM_M_NO_MAGIC_ATTACK,
	"Guard says: Hey! Hands off the prisoner!\n");
    set_alarm(10.0, 0.0, "scene4");
}

public void
scene4()
{
    Guards[1]->command("emote produces a coil of rope.");
    Guards[1]->command("emote starts to tie a noose.");
    Guards[2]->command("say This tree looks good enough.");
    set_alarm(5.0, 0.0, "scene5");
}

public void
scene5()
{
    Guards[1]->command("emote puts the noose around the orc's neck.");
    Guards[2]->command("emote throws the rope around a high branch.");
    add_item("rope", &tree_desc("rope"));
    State = ROPE_IN_TREE;
    set_alarm(10.0, 0.0, "scene6");
}

public void
scene6()
{
    Orc->command("emote screams pitifully and thrashes wildly.");
    tell_room(TO, "The guard pulls the rope and ties it to a low branch.\n");
    add_item("orc", &tree_desc("orc"));
    State = ORC_IN_TREE;
    Orc->remove_object();
    TO->add_prop(ROOM_M_NO_ATTACK, 0);
    TO->add_prop(ROOM_M_NO_MAGIC_ATTACK, 0);
    set_alarm(10.0, 0.0, "scene7");
}

public void
scene7()
{
    tell_room(TO, "The scared male orc kicks violently.\n");
    set_alarm(6.0, 0.0, "scene8");
}

public void
scene8()
{
    tell_room(TO, "The scared male orc claws desperately at the rope.\n");
    set_alarm(9.0, 0.0, "scene9");
}

public void
scene9()
{
    object ob;

    tell_room(TO, "The scared male orc dies.\n");
    State = CORPSE_IN_TREE;
    remove_item("orc");
    add_item( ({ "orc corpse", "corpse" }), &tree_desc("corpse"));
    Guards[0]->command("say Now THAT will go good with a hearty breakfast.");
    Guards[1]->command("say Yes, I'm hungry too.");
    Erkenbrand->command("say Thank you for your help.");
    give_player_xp(Quest_solver);
    if (objectp(ob = present("_helmsdeep_horn", Quest_solver)))
    {
	Erkenbrand->command("say I have to take your horn; "+
	    "others might need it.");
	Erkenbrand->command("emote takes the horn.");
	ob->remove_object();
    }
    Quest_solver->remove_prop(FOUND_ORC);
    Quest_solver->remove_prop(FOUND_TRACK);
    Quest_solver->remove_prop(SHOWN_MAP);
    Quest_solver->remove_prop(MADE_REPORT);
    ob = find_object(HIDE_OUT);
    ob->brave_orc();
    set_alarm(10.0, 0.0, "scene10");
}

public void
scene10()
{
    object mail;

    Erkenbrand->command("say Take this gift and use it well.");
    mail = clone_object(ROH_DIR + "horn/obj/b_coat_mail");
    mail->move(Erkenbrand, 1);
    Erkenbrand->command("give mail to "+Quest_solver->query_real_name());
    if ( ENV(mail) == Erkenbrand )
	Erkenbrand->command("drop mail");
    Erkenbrand->command("say Fare thee well!");
    Erkenbrand->move_living("southeast", TOW_ROOM);
    Guards[0]->move_living("following Erkenbrand", TOW_ROOM);
    Guards[1]->move_living("following Erkenbrand", TOW_ROOM);
    Guards[2]->move_living("following Erkenbrand", TOW_ROOM);
    set_alarm(200.0, 0.0, "remove_corpse");
}

public void
remove_corpse()
{
    State = USED_ROPE_IN_TREE;
    remove_item( ({ "corpse", "orc corpse" }) );
    tell_room(TO, BSN("Some crows descend from the sky and pick the "+
	"bones of the orc corpse clean."));
    set_alarm(200.0, 0.0, "remove_rope");
}

public void
remove_rope()
{
    State = EMPTY_TREE;
    remove_item("rope");
    tell_room(TO, "A tall Rohirrim guard arrives.\n"+
	"The tall Rohirrim guard removes the rope from the oak tree.\n"+
	"The tall Rohirrim guard smiles grimly.\n"+
	"The tall Rohirrim guard leaves southeast.\n");
}
	

public void
reset_room()
{
    set_searched(0);
}

public string
tree_desc(string arg)
{
    string desc = "The oak is fairly tall, and its branches grow quite close "+
	"to the cliff.";

    if ( arg == "tree" )
	desc = "The oak is fairly tall, and its branches grow quite close "+
	    "to the cliff. ";
    else
	desc = "";

    if ( State == ORC_IN_TREE )
	desc += "From a rope looped round a high branch there dangles a "+
	    "terrified orc, kicking frantically and clawing at the noose "+
	    "encircling his neck.";
    else if ( State == CORPSE_IN_TREE )
	desc += "From a rope looped round a high branch there dangles "+
	    "an orc corpse, slowly swaying in the wind";
    else if ( State == ROPE_IN_TREE || State == USED_ROPE_IN_TREE )
	desc += "A rope is looped round a high branch of the tree.";

    return BSN(desc);
}

public int
get_rope(string str)
{
    int	want_corpse;

    if ( State == EMPTY_TREE )
	return 0;
    
    if ( str == "corpse from tree" || str == "corpse from oak tree" ||
    str == "corpse from oak" || str == "orc corpse from tree" ||
    str == "orc corpse from oak tree" || str == "orc corpse from oak" )
    {
	if ( State != CORPSE_IN_TREE )
	    return 0;
	want_corpse = 1;
    }
    else if ( str != "rope from tree" && str != "rope from oak tree" &&
    str != "rope from oak" )
	return 0;

    if ( want_corpse || TP->query_skill(SS_CLIMB) < 5 ||
    State != USED_ROPE_IN_TREE )
	return climb_tree("tree");

    write(BSN("You climb up to the lowest branch and untie the rope, "+
	"which falls to the ground. You climb back down again."));
    SAY(" climbs up into the tree and unties the rope, then quickly "+
	"climbs down again.");
    clone_object("/std/rope")->move(TO);
    remove_item("rope");
    State = EMPTY_TREE;
    return 1;
}

public int
kill_orc(string str)
{
    if ( State == ORC_IN_TREE && ( str == "orc" || str == "scared orc" ) )
    {
	write("Guard says: Hey! Hands off the prisoner!\n");
	return 1;
    }
    return 0;
}

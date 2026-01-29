/*
 *  /d/Gondor/guilds/rangers/north/ith_funcs.c
 *
 *  Various functions for Ithilien Hideout rooms
 *
 *  Coded by Alto, 18 July 2001
 *
 *
 *  Modification log:
 *     2006.08.30, Toby: Added a check in long_desc to remove
 *                       a 0 appearing in exa cave.
 */
inherit "/d/Gondor/std/room.c";

#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

/* Global variables */
string             *handle    =({});
string             *extradesc =({});
string             Exline, Vehicle;
object             actor;
static object      Tstand, Tstand2;

#define MOVING_THROUGH_VANTAGE       "_moving_through_vantage"

/* Prototypes */

public void        ith_add_items();
public int         daylight();
public void        ith_add_torch();
public string      vantage_extraline();
public int         vantage_add_cmds();
public int         crawl_tunnel(object actor);
public int         wind_passage(object actor);
public int         climb_recesses(object actor);
public int         swing_rope(object actor);
public int         exit_room();
public int         move_ranger(object who);


void
ith_add_items()
{
    add_item(({"floor", "stone floor", "ground"}), "The floor here "
        + "formed from the slow and ancient movement of water across "
        + "the bottom of the cave. In the middle of the floor runs a "
        + "shallow depression formed by the passage of many booted feet "
        + "over long years.\n");
    add_item(({"depression", "shallow depression"}), "The floor seems "
        + "a bit depressed in the areas where most traffic moves through. "
        + "It is a testament to the age of this place, and the many long "
        + "years the folk of Gondor have kept vigil here.\n");
    add_item(({"wall", "walls", "north wall", "south wall", "west wall",
        "east wall"}), 
        "The walls, like the floors, are "
        + "smooth and cool. Most of the walls in Henneth Annun are bare, "
        + "although here and there you notice an iron torch stand mounted "
        + "upon the wall of the cave.\n");
    add_item(({"ceiling"}), "The ceiling of the cave, much like the floor "
        + "and walls, is smooth and cool.\n");
    add_item(({"hideout", "henneth annun"}), "It is all around you. Because "
        + "it entirely housed within a network of caves, it cannot be "
        + "seen from the outside.\n");
    add_prop(ROOM_M_NO_SCRY, 1);
}

void
ith_add_torch()
{
    if (!present(Tstand))
    {
        Tstand = clone_object(OBJ_DIR + "torchstand");
        Tstand->set_time(1999);
        Tstand->set_lit(1);
        Tstand->set_replace_msg("A green-cloaked sentinel slips quietly into "
            + "the room and places a new torch in the iron stand. After "
            + "lighting the new torch, the sentinel slips away and "
            + "disappears around a corner.\n");
        Tstand->set_no_desc(1);
        Tstand->remove_prop(CONT_I_ATTACH, 1);
        Tstand->move(TO);

    }
}

void
ith_add_second_torch()
{
    if (!present(Tstand2))
    {
        Tstand2 = clone_object(OBJ_DIR + "torchstand");
        Tstand2->set_time(1777);
        Tstand2->set_lit(1);
        Tstand2->set_replace_msg("A green-cloaked sentinel slips quietly into "
            + "the room and places a new torch in the iron stand. After "
            + "lighting the new torch, the sentinel slips away and "
            + "disappears around a corner.\n");
        Tstand2->set_no_desc(1);
        Tstand2->remove_prop(CONT_I_ATTACH, 1);
        Tstand2->move(TO);

        add_item(({"sentinel", "green-cloaked sentinel"}), "You are too late, "
            + "as the busy sentinel has already left.\n");
    }
}

/*
 * Function name: daylight
 * Description  : return lightlevel of room
 * Returns      : 0 if evening/night, 1 otherwise
 */
public int
daylight()
{
    string timestr = tod();
    if (timestr == "night" || timestr == "evening")
        return 0;
    return 1;
}


string
vantage_extraline()
{
    int position;

    string *extradesc =
/*1*/   ({"The passage ahead narrows to a small tunnel, barely two feet across "
               + "and perhaps one foot high. It looks like you are going "
               + "to have to crawl through it.", 
/*2*/     "The passage here is filled with hundreds, if not thousands, "
               + "of stalactites and stalagmites. Many of them look almost "
               + "razor sharp, so you had best carefully wind through the "
               + "passage.", 
/*3*/     "The passage ends abruptly here, but twenty feet above "
               + "your head a small passage opens into the wall of the "
               + "cave. Someone has cut small recesses into the wall here, "
               + "which you might be able to climb.",
/*4*/     "A deep fissure opens in the floor here. Fortunately someone has "
               + "tied a rope here. Perhaps you can swing across the fissure "
               + "on the rope."});


    string *handle =
/*1*/     ({"tunnel", 
/*2*/       "passage", 
/*3*/       "recesses",
/*4*/       "rope"});


    Exline = ONE_OF_LIST(extradesc);

    position = member_array(Exline, extradesc);

    Vehicle = handle[position];

    return Vehicle;

}


/* Add commands for respective movement item */

int
vantage_add_cmds()
{
    switch (Vehicle)
    {
    case "tunnel":
        add_cmd_item(({"tunnel", "through tunnel", "through the tunnel"}), 
            "crawl", &exit_room());
        add_item(({"tunnel", "small tunnel"}), "The tunnel is so narrow "
            + "that you find yourself wishing you had not eaten that huge "
            + "dinner. It remains to be seen if you can manage to crawl "
            + "through it.\n");
        return 1;

    case "passage":
        add_cmd_item(({"passage", "through passage", "through the passage",
            "carefully through the passage"}), "wind", &exit_room());
        add_item(({"stalactite", "stalactites", "stalagmite", "stalagmites"}), 
            "Formed from ages of mineral-rich water dripping from the ceiling, "
            + "massive stalactites and stalagmites fill the passage. The "
            + "stalactites descending from the ceiling look like large "
            + "icicles that could skewer you if they fell, while the "
            + "stalagmites rising from the floor look sharp enough to impale "
            + "anyone who trips and falls.\n");
        return 1;

    case "recesses":
        add_cmd_item(({"recess", "recesses", "recesses on wall"}), "climb",
            &exit_room());
        add_item(({"recess", "recesses"}), "The small indentations in the "
            + "wall look as if they were made with a hammer and chisel.\n");
        return 1;

    case "rope":
        add_cmd_item(({"rope", "on rope", "on the rope", 
            "across fissure", "across the fissure"}),
            "swing", &exit_room());
        add_item(({"rope"}), "The rope looks sturdy enough. Good thing "
            + "someone thought to tie it here.\n");
        add_item(({"fissure"}), "You cannot see the bottom from here. "
            + "Darkness yawns at you from below.\n");
        return 1;

    default:
        write("The vantage point appears to be unreachable. Please file "
        + "a bug report.\n");
        return 1;
    }
}


/* Set long description of room with extraline from above */

string
long_desc()
{
    string extra;

    extra = Exline;

    if(!extra)
       extra = "";

    return "You are climbing through a small passage in the cave complex of "
        + "Henneth Annun. A small amount of light from far above provides "
        + "minimal illumination. The walls and floor are slick and damp beneath "
        + "your hands and feet. " + extra + "\n";
}


/* Additional items common to all vantage rooms */

void
vantage_add_items()
{
    add_item(({"wall", "walls"}), "The walls are slick and damp here.\n");
    add_item(({"floor", "ground"}), "The floor here is slippery with "
        + "cool condensation.\n");
    add_item(({"roof", "ceiling"}), "The ceiling of the passage is smooth "
        + "in some places, but filled with razor-sharp stalactites in "
        + "others.\n");
    add_item(({"stalactites", "stalactite"}), "You would probably be cut "
        + "to ribbons if one were to break loose and fall upon you.\n");
}


/* Functions for what player sees while moving to the next room */

int
finish_moving(object actor)
{
    actor->remove_prop(MOVING_THROUGH_VANTAGE);
    return 1;
}


int
crawl_tunnel(object actor)
{

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
    actor->catch_tell("You are already moving!\n");
    return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &actor->catch_tell("You bend "
        + "down on all fours and begin "
        + "to crawl through the narrow tunnel.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("Oof. "
        + "You are stuck! You should have "
        + "gone on that diet.\n\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("Straining and "
        + "sucking in your tummy, you manage to squeeze "
        + "through the small tunnel.\n\n"));

    tell_room(environment(actor), QCTNAME(actor) + " bends down on all "
        + "fours and begins to crawl through the small tunnel.\n", 
        actor);
    set_alarm(2.0, 0.0, &tell_room(environment(actor), "The tunnel looks " 
        + "too tight for " + QCTNAME(actor) + ", and " + PRONOUN(actor) 
        + " appears to be stuck!\n", actor));
    set_alarm(5.0, 0.0, &tell_room(environment(actor), QCTNAME(actor) 
        + " somehow manages to squirm through the small tunnel.\n", actor));

    set_alarm(5.0, 0.0, &finish_moving(actor));

    return 1;
}


int
wind_passage(object actor)
{

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
    actor->catch_tell("You are already moving!\n");
    return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &actor->catch_tell("You carefully enter the "
        + "forest of stalactites and stalagmites.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("Ouch! You scratch "
        + "yourself on one of the stalagmites rising up from " 
        + "the floor.\n\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("After ducking and " 
        + "weaving, you manage to get past most of the "
        + "stalactites and stalagmites with only "
        + "a few cuts and scrapes.\n\n"));
    tell_room(environment(actor), QCTNAME(actor) + " looks nervously at "
        + "the forest of stalactites and stalagmites as " + PRONOUN(actor) 
        + " begins to wind through them.\n", actor);
    set_alarm(2.0, 0.0, &tell_room(environment(actor), "Ouch! " 
        + QCTNAME(actor) + " bumps into one of the stalagmites!\n", actor));

    set_alarm(2.0, 0.0, &finish_moving(actor));

    return 1;
}


int
climb_recesses(object actor)
{

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
    actor->catch_tell("You are already moving!\n");
    return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &actor->catch_tell("You place your "
        + "hands and feet into the recesses and begin "
        + "climbing up the wall.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("Careful! You "
        + "almost slipped!\n\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("Your fingers "
        + "and toes start to ache "
        + "as you continue to climb.\n\n"));

    tell_room(environment(actor), QCTNAME(actor) + " places " 
        + actor->query_possessive() + " hands and feet into the recesses "
        + "and begins climbing up the wall.\n", actor);
    set_alarm(2.0, 0.0, &tell_room(environment(actor), "Eeks! " 
        + QCTNAME(actor) + " almost slipped!\n", actor));

    set_alarm(2.0, 0.0, &finish_moving(actor));

    return 1;
}


int
swing_rope(object actor)
{

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
    actor->catch_tell("You are already moving!\n");
    return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &actor->catch_tell("You grab the "
        + "rope and give it a good tug. It seems sturdy enough.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("Without a second "
        + "thought you leap into the darkness above the fissure!\n\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("Wind streams through "
        + "your hair as you swing through a long arc.\n\n"));

    tell_room(environment(actor), QCTNAME(actor) + " grabs the rope and "
        + "gives it a good tug.\n", actor);
    set_alarm(2.0, 0.0, &tell_room(environment(actor), "Suddenly, " 
        + QCTNAME(actor) + " leaps into the darkness above the fissure!\n", 
        actor));
    set_alarm(5.0, 0.0, &tell_room(environment(actor), QCTNAME(actor) 
        + " swings through a long smooth arc over the fissure.\n", actor));

    set_alarm(5.0, 0.0, &finish_moving(actor));

    return 1;
}


/* Move player to next room */

int
exit_room()
{
    object tp = this_player();
    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
    write("You are already moving!\n");
    return 1;
    }

    switch (Vehicle)
    {
    case "tunnel":
        crawl_tunnel(tp);
        set_alarm(6.0, 0.0, &move_ranger(tp));        
        return 1;

    case "passage":
        wind_passage(tp);
        set_alarm(6.0, 0.0, &move_ranger(tp));        
        return 1;

    case "recesses":
        climb_recesses(tp);
        set_alarm(6.0, 0.0, &move_ranger(tp));        
        return 1;

    case "rope":
        swing_rope(tp);
        set_alarm(6.0, 0.0, &move_ranger(tp));        
        return 1;

    default:
        write("The vantage point appears to be unreachable. Please make "
            + "a bug report.\n");
        return 1;
    }
}


/* Error check fuction - masked in room files */

int
move_ranger(object who)
{
    write("This should not happen. Please make a bug report.\n");
    return 0;
}

void
enter_inv(object ob, object from)
{
    string name;
    object entrance;

    ::enter_inv(ob, from);

    if (!living(ob) || !ob->query_wiz_level())
        return;

    name = ob->query_real_name();
/* 
//     Gondorian wizards, arches and Shire stewards/lieges not tracked.
    if (SECURITY->query_wiz_dom(name) == "Gondor" ||
      (SECURITY->query_wiz_dom(name) == "Shire" &&
       SECURITY->query_wiz_rank(name) >= WIZ_STEWARD) ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return;
*/
    (RANGERS_ITH_DIR + "entrance.c")->teleledningsanka();
    entrance = find_object(RANGERS_ITH_DIR + "entrance.c");
    if (entrance->query_allowed(name))
        return;

    clone_object(RANGERS_OBJ + "tracker")->move(ob, 1);
    return;
}

void
leave_inv(object ob, object to)
{
    string name;
    object tracker, entrance;

    ::leave_inv(ob, to);

    if (!living(ob) || !ob->query_wiz_level())
        return;

    name = ob->query_real_name();
/*
    if (SECURITY->query_wiz_dom(name) == "Gondor" ||
      (SECURITY->query_wiz_dom(name) == "Shire" &&
       SECURITY->query_wiz_rank(name) >= WIZ_STEWARD) ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return;
*/
    (RANGERS_ITH_DIR + "entrance.c")->teleledningsanka();
    entrance = find_object(RANGERS_ITH_DIR + "entrance.c");
    if (entrance->query_allowed(name))
        return;

    tracker = present("_ranger_tracker", ob);
    if (objectp(tracker))
        tracker->remove_object();
}

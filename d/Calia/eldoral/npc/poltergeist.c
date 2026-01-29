/*
 * poltergeist.c
 *
 * This is the 'ghost' of the lord of Castle Chimera. It's not an actual
 * npc, rather it's an object that manifests itself in various ways in
 * the object's environment, but as it possesses a consciousness, I
 * decided to put in the npc directory. This npc is part of the
 * "Seer and the Lord Quest".
 *
 * Coded by Khail, Jan 3/96
 */
#pragma strict_types

#include "defs.h"

inherit "/std/object";

int haunt,
    reacting_to_seer,
    reacting_to_dagger;

public void reset_quest();
public void create_object();
public void start_poltergeist();
public void next_manifest(int index);
public void react_dagger(object ob, object who);
public void react2_dagger(object ob, object who);
public void react_seer(object ob);
public void react_seer_2(object ob);
public void react_seer_3(object ob);
public void react_seer_4(object ob);
public void move_home(object ob);

public void
reset_quest()
{
    reacting_to_seer = 0;
    reacting_to_dagger = 0;
}

public void
create_object()
{
    set_name("lord");
    set_short("no short");
    set_long("no long");
    set_no_show();
    setuid();
    seteuid(getuid());
    SEER_BRAIN->add_poltergeist(TO);
}

public void
start_poltergeist()
{
    TO->move(RUIN + "throne_room");
    tell_room(environment(TO), "The air in the room grows strangely " +
        "cold.\n");
    haunt = set_alarm(5.0, 0.0, &next_manifest(0));
}

public void
next_manifest(int index)
{
    string str;
    switch(index)
    {
        case 0:
            str = "Suddenly a fire blazes up in the fireplace, " +
                "and dies down again.\n";
            break;
        case 1:
            str = "A horrible growl seems to emanate from the " +
                "air around you.\n";
            break;
        case 2:
            str = "The room becomes very warm, the air is almost " +
                "stifling.\n";
            break;
        case 3:
            str = "The torches on the walls suddenly flare into " +
                "life, the flicker out again.\n";
            break;
        case 4:
            str = "Strange whispers echo around the room.\n";
            break;
        case 5:
            str = "The dust on the floor begins to swirl, as if " +
                "something were walking past.\n";
            break;
        case 6:
            str = "A cold, sharp wind suddenly springs up, roaring " +
                "around you like a gale, but the wind dies away " +
                "again almost as suddenly as it arrived.\n";
            break;
        default:
            str = "You feel a tickle on your hand. Looking down " +
                "you see hundreds of little red spiders crawling " +
                "down your arm!\n";
    }

    tell_room(environment(TO), str);
    haunt = set_alarm(itof(20 + random(10)), 0.0, 
        &next_manifest(random(8)));
}

/*
 * Function name: react_dagger
 * Description  : What the poltergeist does when reacting to the dagger
 *                being placed on his throne for the first time.
 * Arguments    : ob - object pointer to the dagger.
 *                who - Object pointer to the player who dropped 'ob'.
 * Returns      : n/a
 */ 
public void
react_dagger(object ob, object who)
{
    if (reacting_to_dagger)
        return;

    if (get_alarm(haunt))
        remove_alarm(haunt);

    tell_room(environment(TO), "Suddenly, all grows extremely quiet. As " +
        "you watch, the " + ob->short() + " lifts off the " +
        "throne, hovering in " +
        "midair vertically, rotating slowly as if being closely " +
        "examined by unseen hands.\n");
    if (!ob->query_prop(OBJ_S_ORIG_SHORT))
        ob->add_prop(OBJ_S_ORIG_SHORT, ob->query_short());
    ob->set_short(ob->query_prop(OBJ_S_ORIG_SHORT) + 
        ", hovering in midair");
    ob->add_prop(OBJ_M_NO_GET, "Whatever is holding the " +
        ob->query_prop(OBJ_S_ORIG_SHORT) + " up in midair, " +
        "you aren't going to try " +
        "taking it from it.\n");
    set_alarm(10.0, 0.0, &react2_dagger(ob, who));
}

public void
react2_dagger(object ob, object who)
{
    if (get_alarm(haunt))
        remove_alarm(haunt);

    if (!ob->id(ELDORAL_DAGGER_NAME))
    {
        tell_room(environment(TO), "The " + ob->short() + 
            " suddenly drops back " +
            "onto the seat of the throne.\n");
    }
    else
    {
        tell_room(environment(TO), "You hear a rasping voice hiss from " +
            "the air: This tells me nothing.\nYou can feel the anger " +
            "starting the burn in the room, and the voice adds: The " +
            "seer knows...the seer knows!\nThe dagger suddenly drops " +
            "back onto the throne.\n");
        who->add_prop(LIVE_I_SEER_QUEST,
            who->query_prop(LIVE_I_SEER_QUEST) | SEQ_SPOKE_LORD);
        ob->add_prop(OBJ_I_LORD_SAW_ME, 1);
        reacting_to_dagger = 1;
    }
    if (!ob->query_prop(OBJ_S_ORIG_SHORT))
        ob->add_prop(OBJ_S_ORIG_SHORT, ob->query_short());
    ob->set_short(ob->query_prop(OBJ_S_ORIG_SHORT) + ", resting " +
        "upon the seat of the throne");
    ob->remove_prop(OBJ_M_NO_GET);
    next_manifest(random(8));
}

/*
 * Function name: react_seer
 * Description  : This function is called by the quest brain when the
 *                seer remembers that he was the one who killed the lord.
 *                The poltergeist arrives for revenge.
 * Arguments    : n/a
 * Description  : n/a
 */
public void
react_seer(object ob)
{
    TO->move(RUIN + "seer_tower");
    reacting_to_seer = 1;
    tell_room(environment(TO), "Suddenly, the room grows very cold.\n");
    set_alarm(5.0, 0.0, &ob->react_lord(TO));
}

public void
react_seer_2(object ob)
{
    if (!objectp(ob))
    {
        reacting_to_seer = 0;
        move_home(query_prop(LIVE_O_LAST_ROOM));
        return;
    }
        
    tell_room(environment(TO), "The room suddenly shifts temperature, " +
        "and becomes as hot as a furnace! Roars of rage seem to come " +
        "from nowhere.\n");
    set_alarm(8.0, 0.0, &ob->react_lord_2(TO));
}

public void
react_seer_3(object ob)
{
    if (!objectp(ob))
    {
        reacting_to_seer = 0;
        move_home(query_prop(LIVE_O_LAST_ROOM));
        return;
    }

    tell_room(environment(TO), "Suddenly flames spring up from the " +
        "empty fireplace, setting the center of the room alight into " +
        "a column of fire that reaches all the way up the ceiling " +
        "only to fade away again.\n");
    set_alarm(5.0, 0.0, &ob->react_lord_3(TO));
}

public void
react_seer_4(object ob)
{
    if (!objectp(ob))
    {
        reacting_to_seer = 0;
        move_home(query_prop(LIVE_O_LAST_ROOM));
        return;
    }

    tell_room(environment(TO), "A roaring voice utters: You're as " +
        "dead as I am, fool! Now pay the price of your betrayal!\n" +
        "Dark shadows start to creep down the walls from the " +
        "depths of the ceiling. As the seer, or apparently, the " +
        "ghost of the seer, stares in shock, the shadows seem to " +
        "swarm him under! With a wail of unspeakable horror and " +
        "anger, the shadows completely consume him. When they depart, " +
        "nothing but the faint odour of sulfur remains.\n");
    ob->finish_quest();
    set_alarm(0.0, 0.0, remove_object);
} 

public void
move_home(object ob)
{
    if (!reacting_to_seer && !reacting_to_dagger)
        TO->move(ob);
}
         

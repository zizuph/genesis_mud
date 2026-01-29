#pragma strict_types

inherit "/std/room";
inherit "/lib/skill_raise";

#include "../defs.h"

#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <config.h>
#include <filter_funs.h>
#include <cmdparse.h>

mapping pets    = ([]);

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
    
    foreach(string skill: m_indexes(SKILLS))
    {
        sk_add_train(SKILLS[skill][0], SKILLS[skill][1], 0, 0, SKILLS[skill][2]);
    }
}

public void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("Pet House");
    set_long("Where we keep pets, where they can eat and drink, " +
    "staying healthy.\n");

    add_prop("_room_i_allow_steed", 1);
    add_prop("_room_i_allow_horse", 1);
    
    set_up_skills();
    enable_reset(200);
    
    set_alarm(4.0, 0.0, &reset_room());
}

public object *
idle_pets()
{
    setuid();
    seteuid(getuid());

    object beast, *mounts = ({});
    
    if (objectp(beast = find_object(BEAST + "std/std_pet")) &&
        pointerp(object_clones(beast)))
        mounts = filter(object_clones(beast), &operator(>)(,1800) @
                        &->query_idle_pet());
    
    return mounts;
}

public int
breed_pets()
{
    setuid();
    seteuid(getuid());
    
    object  beast,
           *mounts;
    string *rooms,
            genus;
            
    if (objectp(beast = find_object(BEAST + "join_pet")) &&
        pointerp(object_clones(beast)))
        mounts = object_clones(beast);
        
    if (MAX_PET_SPAWNS <= sizeof(mounts))
        return 0;
    
    if (!pointerp(rooms))
        rooms = m_indexes(PET_LOCS);
    
    foreach(object mount: mounts)
    {
        rooms -= ({ file_name(environment(mount)) + ".c" });
    }
    
    if (!sizeof(rooms))
        return -1;
    
    object room = one_of_list(rooms);
    
    if (IN_ARRAY(PET_LOCS[room], m_indexes(BIOME_LIST)))
        genus = one_of_list(BIOME_LIST[PET_LOCS[room]]);
    
    if (!strlen(genus))
        return -2;
    
    if (!sizeof(GENUS->query_biome(genus, PET_LOCS[room])))
        return 0;
    
    beast = clone_object(BEAST + "join_pet");
    beast->set_genus(genus);
    beast->set_biome(PET_LOCS[room]);
    beast->update_description(genus);
    beast->move(room, 1);
    
    return 1;
}

/*
 * Function name: reset_room
 * Description  : Do the things we need to do when the room resets.
 */
public void
reset_room()
{
    object *pets, *m_pets;
    int     result;
    
    if (sizeof(pets = idle_pets()))
    {
        m_pets = filter(pets, &operator(!=)(, this_object()) @ &environment());
        
        if (sizeof(m_pets))
            m_pets->move_living("X", this_object(), 0, 0);
    }
    
    if ((result = breed_pets()) < 0)
        return; //ADD_LOGGER
}

int
query_pet_house()
{
    return 1;
}

void
pet_recovery(object pet, int when)
{
    int mod,
        add;
    
    if (!(mod = (time() - when) / 60))
        return;
    
    pet->heal_hp((pet->query_max_hp()*mod)/100);
    pet->add_mana((pet->query_max_mana()*mod)/100);
    pet->add_fatigue((pet->query_max_fatigue()*mod)/100);
    
    if (!pet->drink_soft((pet->query_prop(LIVE_I_MAX_DRINK)*mod)/100))
        pet->set_soaked(pet->query_prop(LIVE_I_MAX_DRINK));
    if (!pet->eat_food((pet->query_prop(LIVE_I_MAX_EAT)*mod)/100))
        pet->set_stuffed(pet->query_prop(LIVE_I_MAX_EAT));
}

public void
enter_inv(object ob, object from)
{
    if (stringp(ob->query_tamer()))
        pets += ([ ob->query_tamer_name() : time() ]);
    
    ::enter_inv(ob, from);
}

public void
leave_inv(object ob, object to)
{
    if (stringp(ob->query_tamer_name()))
        pet_recovery(ob, pets[ob->query_tamer_name()]);
    
    ::leave_inv(ob, to);
}

int
do_list(string str)
{
    object  beast,
           *mounts;
    
    notify_fail("What would you like to list, 'join pets' or 'player pets'?\n");
    if (!str)
        return 0;
    
    if (!IN_ARRAY(str, ({   "join", "join pet", "join pets", "player",
                            "player pet", "player pets"})))
        return 0;
    
    switch(str)
    {
        case "join":
        case "join pet":
        case "join pets":
        if (objectp(beast = find_object(BEAST + "join_pet")))
            mounts = object_clones(beast);
            break;
        
        case "player":
        case "players":
        case "player pet":
        case "player pets":
        if (objectp(beast = find_object(BEAST + "base/pet_base")))
            mounts = object_clones(beast);
            break;
        
        default:
            return 0;
    }
    
    if (!sizeof(mounts))
    {
        notify_fail("No mounts fitting the specified criteria were found in the realms.\n");
        return 0;
    }
    
    foreach(object mount: mounts)
    {
        object tamer = mount->query_tamer();
        string name  = mount->query_tamer_name();
        
        if (stringp(name))
            write("----------------------------------------" +
            "\nPlayer:    " + name +
            (objectp(tamer) ? "" + 
            "\nAverage:   " + tamer->query_average_stat() +
            "\nRace:      " + tamer->query_race() : "") +
            "\nPet:       " + MANAGER->query_pet_name(name) +
            "\nMaturity:  " + mount->query_maturity() +
            "\nGenus:     " + mount->query_genus() +
            "\nDesc:      " + mount->query_nonmet_name() +
            "\nLocation:  " + file_name(environment(mount)) +
            "\n");
        else
            write("Genus: " + mount->query_genus() +
            " - Location: " + file_name(environment(mount)) +
            "\n");
    }
    
    return 1;
}

void
init()
{
    ::init();
    add_action(do_list, "list");
    init_skill_raise();
}
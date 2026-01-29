#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "../defs.h"

#include <macros.h>
#include <stdproperties.h>

static mapping members  = ([]);
static mapping pets     = ([]);

public int query_join_time(mixed who);

public void
populate_existing_pets()
{
    object *new_pets;
    
    if (!sizeof(new_pets = object_clones(find_object(PET_BASE))))
        return;
    
    foreach(object pet: new_pets)
    {
        pets[lower_case(pet->query_name())] = pet;
    }
}

void
create()
{
    setuid();
    seteuid(getuid());
    
    populate_existing_pets();
}

public int
save_member(string who)
{
    mapping member_save;
   
    who = lower_case(who);
    
    if (!mappingp(member_save = members[who]))
        return 0;
  
    save_map(member_save, MEMBER_DIR(who));
    return 1;
}

public int
load_member(string who)
{
    if (file_size(MEMBER_DIR(who) + ".o") < 0)
        return 0;
    
    members[who] = restore_map(MEMBER_DIR(who));
    return 1;
}

public string
get_name(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!stringp(who))
        return "";
    
    return who;
}

mixed
get_map(mixed who, string map)
{
    string name;
    
    if (!strlen(name = get_name(who)) || !load_member(name) ||
        (member_array(map, m_indexes(members[name])) < 0))
        return 0;
  
    return members[name][map];
}

int
set_map(mixed who, string map, mixed set)
{
    if (!strlen(who = get_name(who)) || !load_member(who))
        return 0;
    
    members[who][map] = set;
    return save_member(who);
}

int
add_member(mixed who, string name, string genus, string race,
           int gender, mixed adjs)
{
    int     age,
            join_time;
    object  ob;
    string *achievements = ({});
  
    if (objectp(who))
    {
        age = who->query_age();
    	who = who->query_real_name();
    }
  
    if (!stringp(who))
        return 0;
    
    if (!age && (ob = find_player(who)))
        age = ob->query_age();
    
    if (!(join_time = query_join_time(who)))
        join_time = time();
    
    if (pointerp(get_map(who, "achievements")))
        achievements = members[who]["achievements"];
    
    members[who] = ([   "join_time"     : join_time,
                        "pet_name"      : name,
                        "pet_age"       : age,
                        "pet_genus"     : genus,
                        "pet_race"      : race,
                        "pet_gender"    : gender,
                        "pet_adjs"      : adjs,
                        "achievements"  : achievements
                    ]);
    
    return save_member(who);
}

public object
query_current_pet(mixed who)
{
    mixed pet;
    
    if (objectp(who))
        who = who->query_real_name();
    
    if (!stringp(who))
        return 0;
    
    if (!load_member(who))
        return 0;
    
    if (!stringp(pet = members[who]["pet_name"]))
        return 0;
    
    if (!objectp(pet = pets[pet]))
        return 0;
    
    return pet;
}

public void
set_current_pet(mixed who, object pet)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!stringp(who))
        return;
    
    if (!load_member(who))
        return;
    
    if (!objectp(pet))
        return;
    
    if (!stringp(who = members[who]["pet_name"]))
        return;
    
    pets += ([ who : pet ]);
}

public int
query_ability(mixed who, string ability)
{
    if (!stringp(ability))
        return 0;
    
    return get_map(who, ability);
}

public void
add_ability(mixed who, string ability)
{
    int executed = 1;
    
    if (!stringp(ability))
        return;
    
    executed += get_map(who, ability);
    
    set_map(who, ability, executed);
}

public int
query_ability_success(mixed who, string ability, int success)
{
    if (!stringp(ability))
        return 0;
    
    if (random(100) > success)
        return 0;
    
    return 1;
}

public void
set_skills(mixed who, mapping skills)
{
    if (!mappingp(skills))
        return;
    
    set_map(who, "pet_skills", skills);
}

public mapping
get_skills(mixed who)
{
    return get_map(who, "pet_skills");
}

public varargs string *
query_achievements(mixed who)
{
    return get_map(who, "achievements");
}

public void
add_achievement(mixed who, string achievement)
{
    if (!stringp(achievement))
        return;
    
    if (stringp(who))
        who = find_player(who);
    
    if (!objectp(who))
        return;
    
    if (IN_ARRAY(achievement, query_achievements(who)))
        return;
    
    switch(achievement)
    {
        case TSUMMON:
        who->catch_msg("You have learned the ability " +
        "'tsummon'. You can now 'help tamer tsummon' to " +
        "access what you've just learnt.\n");
            break;
        case TDISMISS:
        who->catch_msg("You have learned the ability " +
        "'tdismiss'.\n");
            break;
        case TMANEUVER:
        who->catch_msg("You have learned the ability " +
        "'tmaneuver'.\n");
            break;
        case TASSIST:
        who->catch_msg("You have learned the ability " +
        "'tassist'.\n");
            break;
        case TKILL:
        who->catch_msg("You have learned the ability " +
        "'tkill'.\n");
            break;
        case TCALM:
        who->catch_msg("You have learned the ability " +
        "'tcalm'.\n");
            break;
        case TSCOUT:
        who->catch_msg("You have learned the ability " +
        "'tscout'.\n");
            break;
        case ADD_TAMER_SKILL:
        case ADD_PET_SKILL:
        who->catch_msg("You have attained new knowledge " +
        "concerning pet training.\n");
            break;
        case FOOD_NO_VALUE:
        case FOOD_VALUE:
        case FOOD_VORARE:
        case FOOD_POISON:
        case FOOD_HERB:
        case FOOD_INN:
        who->catch_msg("You have attained new knowledge " +
        "concerning pet dietary restrictions.\n");
            break;
        case TAME_NEW_PET:
        who->catch_msg("You have attained new knowledge " +
        "concerning pet taming.\n");
            break;
        case CAN_MOUNT:
        case CANNOT_RIDE:
        case HAS_FALLEN_RIDING:
        case HAS_FALLEN_COMBAT:
        who->catch_msg("You have gained new knowledge " +
        "concerning pet mounted restrictions.\n");
            break;
        case PET_INJURY:
        who->catch_msg("You have gained new knowledge " +
        "about pet injuries.\n");
            break;
        case TITLE_ANI_HANDL:
        case TITLE_HUNTING:
        case TITLE_TRACKING:
        case TITLE_LOC_SENSE:
        case TITLE_SNEAK:
        who->catch_msg("You have gained new knowledge " +
        "about tamer masteries.\n");
            break;
        case GENUS_TITLES:
        who->catch_msg("You have gained new knowledge " +
        "about tamer affiliations.\n");
            break;
        case FIND_PET_ARMOUR:
        who->catch_msg("You have attained new knowledge "+
        "concerning pet armoury.\n");
            break;
        default:
            return;
    }
    
    string *achievements = ({});
    
    achievements = get_map(who, "achievements") + ({ achievement });
    
    set_map(who, "achievements", achievements);
}

public int
query_satisfaction(mixed who)
{
    return get_map(who, "satisfaction");
}

public int
add_satisfaction(mixed who, int value, mixed food)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!stringp(who))
        return 0;
    
    if ((value + query_satisfaction(who)) < 0)
        return 0;
    
    value += query_satisfaction(who);
    
    //if (objectp(food))
    //    LOGGER->add(who, food, value);
    
    set_map(who, "satisfaction", value);
    return 1;
}

public int
query_join_time(mixed who)
{
    return get_map(who, "join_time");
}

public void
set_pet_name(mixed who, string name)
{
    set_map(who, "pet_name", name);
}

public string
query_pet_name(mixed who)
{
    return get_map(who, "pet_name");
}

public void
set_pet_age(mixed who, int age)
{
    set_map(who, "pet_age", age);
}

public int
query_pet_age(mixed who)
{
    if (stringp(who))
        who = find_player(who);
    
    return (who->query_age() - get_map(who, "pet_age"));
}

public void
set_pet_genus(mixed who, string genus)
{
    set_map(who, "pet_genus", genus);
}

public string
query_pet_genus(mixed who)
{
    return get_map(who, "pet_genus");
}

public void
set_pet_race(mixed who, string race)
{
    set_map(who, "pet_race", race);
}

public string
query_pet_race(mixed who)
{
    return get_map(who, "pet_race");
}

public void
set_pet_adjs(mixed who, mixed adjs)
{
    set_map(who, "pet_adjs", adjs);
}

public varargs string *
query_pet_adjs(mixed who)
{
    return get_map(who, "pet_adjs");
}

public void
set_pet_injuries(mixed who, mapping injury)
{
    if (get_map(who, "pet_injuries"))
        injury += get_map(who, "pet_injuries");
    
    set_map(who, "pet_injuries", injury);
}

public mixed
query_pet_injuries(mixed who)
{
    return get_map(who, "pet_injuries");
}

public void
remove_pet_injury(mixed who, string injury)
{
    mapping injuries;
    
    injuries = get_map(who, "pet_injuries");
    
    set_map(who, "pet_injuries", m_delete(injuries, injury));
}

public int
set_title(mixed who, string title, int value)
{
    if (!strlen(title))
        return 0;
    
    return set_map(who, title + "_title", value);
}

public mixed
query_title(mixed who, string title)
{
    return get_map(who, title + "_title");
}

public int
add_pet_armour(mixed who, string *armour)
{
    return set_map(who, "pet_armour", armour);
}

public string *
query_pet_armour(mixed who)
{
    return get_map(who, "pet_armour");
}

public int
remove_pet_armour(mixed who)
{
    return set_map(who, "pet_armour", ({}));
}

public int
add_worn_armour(mixed who, int armour)
{
    return set_map(who, "worn_pet_armour", armour);
}

public int
query_worn_armour(mixed who)
{
    return get_map(who, "worn_pet_armour");
}

public int
remove_worn_armour(mixed who)
{
    return set_map(who, "worn_pet_armour", 0);
}

public int
set_armour_desc(mixed who, string desc)
{
    return set_map(who, "long_armour_desc", desc);
}

public string
query_armour_desc(mixed who)
{
    return get_map(who, "long_armour_desc");
}

public int
query_armour_quality(mixed who)
{
    return get_map(who, "armour_quality");
}

public int
set_armour_quality(mixed who, int quality)
{
    return set_map(who, "armour_quality", quality);
}

public string
query_pet_size(mixed who)
{
    return get_map(who, "pet_size");
}

public void
set_pet_size(mixed who, string size)
{
    set_map(who, "pet_size", size);
}

public int
query_pet_stay(mixed who)
{
    return get_map(who, "pet_stay");
}

public int
set_pet_stay(mixed who, int stay)
{
    return set_map(who, "pet_stay", stay);
}

public status
query_pet_rideable(mixed who, object pet)
{
    if (!objectp(who) && !objectp(who = find_player(who)))
        return 0;
    
    if ((pet->query_prop(CONT_I_HEIGHT) * 2) >= who->query_prop(CONT_I_HEIGHT))
    {
        MANAGER->add_achievement(who->query_real_name(), CAN_MOUNT);
        return 1;
    }
    
    return 0;
}
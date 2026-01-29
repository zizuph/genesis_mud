
/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

#pragma strict_types

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "../defs.h"

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <ss_types.h>
#include <options.h>
#include <cmdparse.h>
#include <wa_types.h> 
#include <files.h>

int     summon,
        assist,
        calm,
        maneuver;

string
get_soul_id() 
{
    return GUILD_NAME + " soul"; 
}

int 
query_cmd_soul() 
{
    return 1; 
}

public mapping
query_ability_map()
{
    return ([
                "tsummon"   : SPECIALS + "tsummon",
                "tdismiss"  : SPECIALS + "tdismiss",
                "tmaneuver" : SPECIALS + "tmaneuver",
                "tscout"    : SPECIALS + "tscout",
            ]);
}

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return ([
            /* Ability name : Ability function */
                "tsummon"   : "do_ability",
                "tdismiss"  : "do_ability",
                "tmaneuver" : "do_ability",
                "tscout"    : "do_ability",
            /* Command name : Function name */
                "help"      : "help",
                "tassist"   : "tassist",
                "tkill"     : "tkill",
                "tcalm"     : "tcalm",
                "tintro"    : "tintro",
                "tarmour"   : "tarmour",
                "tstay"     : "pet_stay",
                "tfollow"   : "pet_stay",
                "tsend"     : "tsend",
           ]);
}

int
help(string str)
{
    string  subject, filename,
           *achievements;
    
    achievements = MANAGER->query_achievements(this_player());
        
    if (!parse_command(str, ({ }), "[beast] 'tamer' / 'tamers' %s", subject) &&
        str)
        return 0;
            
    if (!strlen(subject))
        subject = "help";
    
    notify_fail("You are unable to recall ever having come across such "
    + "information.\n");
    
    filename = HELP + subject;
    if (file_size(filename) > 0)
    {
        setuid();
        seteuid(getuid());
        
        switch(lower_case(subject))
        {
            /* Abilities */
            case "tarmour":
            if (!IN_ARRAY(FIND_PET_ARMOUR, achievements))
                return 0;
            
            cat(filename);
                break;
            
            case "tassist":
            if (!IN_ARRAY(TASSIST, achievements))
                return 0;
                
            cat(filename);
                break;
            
            case "tcalm":
            if (!IN_ARRAY(TCALM, achievements))
                return 0;
            
            cat(filename);
                break;
            
            case "tdismiss":
            if (!IN_ARRAY(TDISMISS, achievements))
                return 0;
            
            cat(filename);
                break;
            
            case "tfollow":
            cat(filename);
                break;
            
            case "tintro":
            if (!sizeof(filter(ALL_TITLES, &operator(>)(,-1) @
                &member_array(, achievements))))
                return 0;
            
            cat(filename);
                break;
                
            case "tkill":
            if (!IN_ARRAY(TKILL, achievements))
                return 0;
            
            cat(filename);
                break;
            
            case "tmaneuver":
            if (!IN_ARRAY(TMANEUVER, achievements))
                break;
            
            cat(filename);
                break;
            
            case "tscout":
            if (!IN_ARRAY(CAN_MOUNT, achievements) ||
                GENUS->query_rideable(MANAGER->query_pet_genus(this_player()),
                MANAGER->query_pet_race(this_player())))
                return 0;
            
            cat(filename);
                break;
                
            case "tstay":
            cat(filename);
                break;
            
            case "tsummon":
            if (!IN_ARRAY(TSUMMON, achievements))
                return 0;
            
            cat(filename);
                break;
            
            case "abilities":
            cat(filename, 1, 10);
            
            /*      TARMOUR     */
            if (IN_ARRAY(FIND_PET_ARMOUR, achievements))
                cat(filename, 11, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TASSIST      */
            if (IN_ARRAY(TASSIST, achievements))
                cat(filename, 12, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TCALM      */
            if (IN_ARRAY(TCALM, achievements))
                cat(filename, 13, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TDISMISS      */
            if (IN_ARRAY(TDISMISS, achievements))
                cat(filename, 14, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TFOLLOW     */
            cat(filename, 15, 1);
            
            /*      TINTRO      */
            if (sizeof(filter(ALL_TITLES, &operator(>)(,-1) @
                &member_array(, achievements))))
                cat(filename, 16, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TKILL      */
            if (IN_ARRAY(TKILL, achievements))
                cat(filename, 17, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TMANEUVER   */
            if (IN_ARRAY(TMANEUVER, achievements))
                cat(filename, 18, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TSCOUT & TSEND  */
            if (IN_ARRAY(TSCOUT, achievements))
                cat(filename, 19, 2);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TSTAY       */
            cat(filename, 21, 1);
            
            /*      TSUMMON      */
            if (IN_ARRAY(TSUMMON, achievements))
                cat(filename, 22, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            cat(filename, 23, 3);
                    break;
                    
            case "skills":
            cat(filename, 1, 4);
            
            /*      ADD_TAMER_SKILL      */
            if (IN_ARRAY(ADD_TAMER_SKILL, achievements))
                cat(filename, 5, 8);
            else
                cat(HELP + "empty", 3, 1);
            
            /*      ADD_PET_SKILL      */
            if (IN_ARRAY(ADD_PET_SKILL, achievements))
                cat(filename, 13, 5);
            else
                cat(HELP + "empty", 3, 1);
            
            /*      HAS_SKILL_BOOST      */
            if (IN_ARRAY(HAS_SKILL_BOOST, achievements))
                cat(filename, 18, 4);
            else
                cat(HELP + "empty", 3, 1);
            
            cat(filename, 21, 3);
                    break;
                    
            case "food":
            cat(filename, 1, 4);
            
            /*      FOOD_NO_VALUE      */
            if (IN_ARRAY(FOOD_NO_VALUE, achievements))
                cat(filename, 5, 4);
            else
                cat(HELP + "empty", 3, 1);
            
            /*      FOOD_VORARE      */
            if (IN_ARRAY(FOOD_VORARE, achievements))
                cat(filename, 9, 5);
            else
                cat(HELP + "empty", 3, 1);
            
            /*      FOOD_POISON      */
            if (IN_ARRAY(FOOD_POISON, achievements))
                cat(filename, 14, 4);
            else
                cat(HELP + "empty", 3, 1);
            
            /*      FOOD_VALUE      */
            if (IN_ARRAY(FOOD_VALUE, achievements))
                cat(filename, 18, 5);
            else
                cat(HELP + "empty", 3, 1);
            
            /*      FOOD_HERB      */
            if (IN_ARRAY(FOOD_HERB, achievements))
                cat(filename, 23, 4);
            else
                cat(HELP + "empty", 3, 1);
            
            cat(filename, 26, 3);
                break;
            
            case "armour":
            cat(filename, 1, 4);
            if (IN_ARRAY(FIND_PET_ARMOUR, achievements))
                cat(filename, 5, 2);
            else
                cat(HELP + "empty", 3, 1);
            cat(filename, 7, 4);
                break;
            
            case "tame":
            cat(filename, 1, 4);
            
            if (IN_ARRAY(TAME_NEW_PET, achievements))
                cat(filename, 5, 7);
            else
                cat(HELP + "empty", 3, 1);
            
            cat(filename, 12, 3);
                break;
            
            case "riding":
            cat(filename, 1, 4);
            
            /*      CAN_MOUNT      */
            if (IN_ARRAY(CAN_MOUNT, achievements))
                cat(filename, 5, (GENUS->query_rideable(
                MANAGER->query_pet_genus(this_player()),
                MANAGER->query_pet_race(this_player())) ? 5 : 9));
            else
                cat(HELP + "empty", 3, 1);
            
            /*      CANNOT_RIDE      */
            if (IN_ARRAY(CANNOT_RIDE, achievements))
                cat(filename, 14, 4);
            else
                cat(HELP + "empty", 3, 1);
            
            /*      HAS_FALLEN_RIDING      */
            if (IN_ARRAY(HAS_FALLEN_RIDING, achievements))
                cat(filename, 18, 4);
            else
                cat(HELP + "empty", 3, 1);
            
            /*      HAS_FALLEN_COMBAT     */
            if (IN_ARRAY(HAS_FALLEN_COMBAT, achievements))
                cat(filename, 22, 4);
            else
                cat(HELP + "empty", 3, 1);
            
            cat(filename, 26, 2);
                break;
                
            case "injury":
            cat(filename, 1, 4);
            
            if (IN_ARRAY(PET_INJURY, achievements))
                cat(filename, 5, 3);
            else
                cat(HELP + "empty", 3, 1);
            
            cat(filename, 8, 3);
                break;
                
            case "titles":
            cat(filename, 1, 4);
            
            if (sizeof(filter(ALL_TITLES, &operator(>)(,-1) @
                &member_array(, achievements))))
                cat(filename, 5, 3);
            else
                cat(HELP + "empty", 3, 1);
            
            cat(filename, 8, 3);
                break;
            
            case "leaving":
            cat(filename);
                break;
            
            case "help":
            cat(filename, 1, 4);
            
            /*      ABILITIES      */
            if (sizeof(filter(ALL_ABILITIES,
                &operator(>)(,-1) @ &member_array(, achievements))))
                cat(filename, 5, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      ARMOUR      */
            if (IN_ARRAY(FIND_PET_ARMOUR, achievements))
                cat(filename, 6, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      FOOD      */
            if (sizeof(filter(ALL_FOOD,
                &operator(>)(,-1) @ &member_array(, achievements))))
                cat(filename, 7, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      INJURY      */
            if (IN_ARRAY(PET_INJURY, achievements))
                cat(filename, 8, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      LEAVING      */
            cat(filename, 9, 1);
            
            /*      RIDING      */
            if (sizeof(filter(ALL_MOUNT,
                &operator(>)(,-1) @ &member_array(, achievements))))
                cat(filename, 10, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      SKILLS      */
            if (sizeof(filter(ALL_SKILLS,
                &operator(>)(,-1) @ &member_array(, achievements))))
                cat(filename, 11, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TAME      */
            if (IN_ARRAY(TAME_NEW_PET, achievements))
                cat(filename, 12, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            /*      TITLES      */
            if (sizeof(filter(ALL_TITLES,
                &operator(>)(,-1) @ &member_array(, achievements))))
                cat(filename, 13, 1);
            else
                cat(HELP + "empty", 1, 1);
            
            cat(filename, 14, 3);
                    break;
        }
        return 1;
    }
    
    return 0;
}

mixed
query_pet_present(object player)
{
    object *pet = filter(all_inventory(environment(player)),
           &operator(==)(player->query_real_name()) @ &->query_tamer_name());
           
    if (sizeof(pet))
        return pet[0];
    
    return 0;
}

mixed
query_enemies(object target)
{
    return filter(all_inventory(environment(target)),
           &operator(==)(target) @ &->query_attack());
}

public int
tassist(int tkill)
{
    string  name;
    object  attack,
            pet;
    int     success;
    
    name    = MANAGER->query_pet_name(this_player()->query_real_name());
    pet     = query_pet_present(this_player());
    attack  = this_player()->query_attack();
    
    if (!IN_ARRAY(TASSIST, MANAGER->query_achievements(this_player())))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (pet->query_unconscious())
    {
        notify_fail("The " + pet->query_nonmet_name() + "is unconscious.\n");
        return 0;
    }
    
    if (!objectp(pet) ||
        !MANAGER->load_member(this_player()->query_real_name()) ||
        !strlen(name))
    {
        notify_fail("Your pet is not around to assist you.\n");
        return 0;
    }

    if (!objectp(attack))
    {
        notify_fail("You are not attacking anyone.\n");
        return 0;
    }
    
    if (attack == pet->query_attack())
    {
        notify_fail(capitalize(name) + " is already assisting.\n");
        return 0;
    }
    
    notify_fail(capitalize(name) + " is unable to assist.\n");
    if (attack->query_prop(OBJ_M_NO_ATTACK))
        return 0;
    
    if (attack == pet)
        return pet->express_emotion("betrayal", 0);
    
    if (!F_DARE_ATTACK(pet, attack))
        return pet->express_emotion("fear", attack);
    
    if (!CAN_SEE_IN_ROOM(pet))
        return pet->express_emotion("confusion", 0);
    
    if (environment(this_player())->query_prop(ROOM_M_NO_ATTACK)) 
    {
        notify_fail("A divine protection prevents you from hostile actions.\n");
        return 0;
    }
    
    if (pet->query_attack())
    {
        if ((time() - assist) < 5)
        {
            notify_fail(capitalize(name) + " is too focused on " +
            pet->query_possessive() + " prey to heed your command.\n");
            return 0;
        }
        
        success = (this_player()->query_skill(SS_ANI_HANDL) +
                  ((pet->query_maturity() * 5) * pet->query_hp()) /
                  pet->query_max_hp());
                  
        if (!MANAGER->query_ability_success(this_player(), TASSIST, success))
        {
            assist = time();
            
            notify_fail("You were unable to direct "+ capitalize(name) + 
            " away from "+pet->query_possessive()+ " prey.\n");
            return 0;
        }
        
        pet->tell_watcher(QCTNAME(pet) + " acts on command and turns to " +
        "attack " + QTNAME(attack) + ".\n", ({ attack, pet }));
        
        attack->catch_msg(QCTNAME(pet) + " acts on command and turns to " +
        "attack you.\n");
        
        MANAGER->add_ability(this_player(), TASSIST);
    }
    else if (!tkill)
    {
        tell_room(environment(this_player()), QCTNAME(pet)+
        " acts on command and attacks "+QTNAME(attack)+
        ".\n", attack, pet);
        
        attack->catch_msg(QCTNAME(pet)+ " acts on command and "+
        "attacks you.\n");
    }
    
    pet->attack_object(attack);
    return 1;
}

varargs int
tkill(string str)
{
    object victim, pet;
    mixed  tmp, *oblist;
    int pkill = (query_verb() == "kill!");
    
    pet = query_pet_present(this_player());
    if (!IN_ARRAY(TKILL, MANAGER->query_achievements(this_player())))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (pet->query_unconscious())
    {
        notify_fail("The " + pet->query_nonmet_name() + "is unconscious.\n");
        return 0;
    }
    
    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        notify_fail("You can't see anything here.\n");
        return 0;
    }

    if (this_player()->query_ghost())
    {
        notify_fail("Umm yes, killed. That's what you are.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Kill what?\n", 0);
        return 0;
    }

    /* Require an exaclamation for attacking players. */
    if (str[-1..] == "!")
    {
        pkill = 1;
        str = str[..-2];
    }

    str = lower_case(str);
    if (!parse_command(str, all_inventory(environment(this_player())),
       "[the] %i", oblist) || !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        notify_fail("You find no such living creature.\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Be specific, you cannot kill " +
            COMPOSITE_ALL_LIVE(oblist) + " at the same time.\n");
        return 0;
    }

    victim = oblist[0];
    if (!living(victim))
    {
       write(capitalize(LANG_THESHORT(victim)) + " isn't alive!\n");
       return 1;
    }
 
    if (victim->query_ghost())
    {
        write(victim->query_The_name(this_player()) + " is already dead!\n");
        return 1;
    }

    if (victim == this_player())
    {
        write("What? Attack yourself?\n");
        return 1;
    }

    if (this_player()->query_attack() == victim)
    {
        write("Yes, yes.\n");
        return 1;
    }

    if (tmp = environment(this_player())->query_prop(ROOM_M_NO_ATTACK))
    {
        if (stringp(tmp))
            write(tmp);
        else
            write("You sense a divine force preventing your attack.\n");
        return 1;
    }

    if (tmp = victim->query_prop(OBJ_M_NO_ATTACK))
    {
        if (stringp(tmp))
        {
            write(tmp);
        }
        else
        {
            write("You feel a divine force protecting " +
                victim->query_the_name(this_player()) + ", your attack fails.\n");
        }

        return 1;
    }

    if (member_array(victim, this_player()->query_team_others()) != -1)
    {
        write("You cannot attack " + victim->query_the_name(this_player()) +
            " as " + victim->query_pronoun() + " is in your team.\n");
        return 1;
    }

    /* Require an exclamation mark for attacking another player. */
    if (!this_player()->query_npc() && !victim->query_npc() && !pkill)
    {
        write("Attack " + victim->query_the_name(this_player()) + "?!? That " +
            "requires an exclamation mark at the end of the command.\n");
        return 1;
    }

    this_player()->reveal_me(1);

    /* Check if we dare! */
    if (!F_DARE_ATTACK(this_player(), victim))
    {
        write("Umm... no. You do not have enough self-discipline to dare!\n");
        say(QCTNAME(this_player()) + " considers attacking " + QTNAME(victim) +
            ", though does not dare to do so.\n", ({ victim, this_player() }) );
        tell_object(victim, this_player()->query_The_name(victim) +
            " looks at you as if ready to attack, though you see fear in " +
            this_player()->query_possessive() + " eyes.\n");
        return 1;
    }
    
    this_player()->attack_object(victim);
    this_player()->add_prop(LIVE_O_LAST_KILL, victim);
    
    string str;
    
    if (this_player()->query_steed() == query_pet_present(this_player()))
        str = " "+this_player()->query_pronoun()+" is riding on.\n";
    else
        str = ".\n";

    if(tassist(1))
    {
        say(QCTNAME(this_player()) + " attacks " + QTNAME(victim) + " with the "
        + "assistance of the " + pet->query_nonmet_name() + str,
        ({ this_player(), victim }) );
        
        tell_object(victim, this_player()->query_The_name(victim) + " attacks "
        + "you with the assistance of the " + pet->query_nonmet_name() + str);
    
        if (this_player()->query_steed() == query_pet_present(this_player()))
            str = " you are riding on.\n";
        
        this_player()->catch_msg("You attack " + QTNAME(victim) + " with the "
        + "assistance of the " + pet->query_nonmet_name() + str);
    
        MANAGER->add_ability(this_player(), TKILL);
    }
    else
    {
        say(QCTNAME(this_player()) + " attacks " + QTNAME(victim) + ".\n",
        ({ this_player(), victim }) );
        
        tell_object(victim, this_player()->query_The_name(victim) + " attacks "+
        "you!\n");
    
        this_player()->catch_msg("You attack "+QTNAME(victim)+".\n");
    }
    return 1;
}

int
tcalm(string str)
{
    int     skill;
    string  name;
    object  pet;
    
    skill   = this_player()->query_skill(SS_ANI_HANDL);
    name    = MANAGER->query_pet_name(this_player()->query_real_name());
    pet     = query_pet_present(this_player());
    
    if (!IN_ARRAY(TCALM, MANAGER->query_achievements(this_player())))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (pet->query_unconscious())
    {
        notify_fail("The " + pet->query_nonmet_name() + "is unconscious.\n");
        return 0;
    }
    
    if (!objectp(pet) ||
        !MANAGER->load_member(this_player()->query_real_name()) ||
        !strlen(name))
    {
        notify_fail("Your pet is not in the vicinity.\n");
        return 0;
    }
    
    if (!str || str != name)
    {
        notify_fail("Calm " + capitalize(name) + "?\n");
        return 0;
    }
    
    if(!sizeof(query_enemies(pet)))
    {
        notify_fail(capitalize(name)+" is not showing any signs of "
        + "hostility.\n");
        return 0;
    }
    
    if ((time() - calm) < 10)
    {
        notify_fail(capitalize(name) + " is already calming down.\n");
        return 0;
    }
    
    calm = time();
    
    MANAGER->add_ability(this_player(), TCALM);
    pet->cease_hostility(1);
    return 1;
}

int
tintro(string str)
{
    int     gender, title_value, i = 0;
    string *titles = ({}), *achievements, genus;
    
    achievements = MANAGER->query_achievements(this_player());
    
    if (!sizeof(filter(ALL_TITLES, &operator(>)(,-1) @
        &member_array(, achievements))))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if ((gender = this_player()->query_gender()) > 1)
        gender = 0;
    
    str = capitalize(str);
    
    foreach(int skill, string *g_titles : HIGH_TITLES)
    {
        if (member_array(ALL_TITLES[i], achievements) > -1)
            titles += ({ g_titles[gender] });
    
        if (str == g_titles[gender])
            title_value = skill;
        
        i++;
    }
    
    switch(str)
    {
        case "Genus":
        if (strlen(genus = MANAGER->query_pet_genus(this_player())))
        {
            MANAGER->set_title(this_player(), genus, 
            MANAGER->query_title(this_player(), genus) ? 0 : 1);
            
            this_player()->catch_msg("You have chosen " +
            (MANAGER->query_title(this_player(), genus) ? "" : "not ") +
            "to display your affiliations with the " +
            GENUS->query_family(genus) + " family, presenting yourself as: " +
            this_player()->query_guild_title_lay() + "\n");
        }
        return 1;
        
        case "Incognito":
        case "Incog":
        title_value = -1;
            break;
            
        case "Tamer":
        title_value = 0;
            break;
            
        default:
        if (!title_value)
        {
            this_player()->catch_msg(""
            + (strlen(this_player()->query_guild_title_lay()) ? "Your current "
            + "title is: " + this_player()->query_guild_title_lay() + "\n" : ""
            + "You have chosen not to display your title.\n")
            + "You may hide your title with 'incognito' and display your "
            + "normal titles with 'tamer'"
            + (member_array(GENUS_TITLES, achievements) > -1 ? ", choose to "
            + "display your 'genus' title" : "")
            + (sizeof(titles) ? " or choose from one of the following:\n"
            + COMPOSITE_WORDS(titles) + "\n": ".\n"));
            return -1;
        }
            break;
    }
    
    MANAGER->set_title(this_player(), "high", title_value);
    
    if (!strlen(this_player()->query_guild_title_lay()))
        this_player()->catch_msg("You decide hide all your animal " +
        "affiliations.\n");
    else
        this_player()->catch_msg("You have chosen to present yourself as: " +
        this_player()->query_guild_title_lay() + "\n");
    
    return 1;
}

public int
tarmour(string str)
{
    object  pet, *armours;
    int     success;
    
    if (!IN_ARRAY(FIND_PET_ARMOUR, MANAGER->query_achievements(this_player())))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (!strlen(str))
        str = "all";
    
    pet = query_pet_present(this_player());
    
    if (!sizeof(armours = pet->query_armour(-1)))
    {
        if (!sizeof(armours = filter(deep_inventory(this_player()),
            &->query_tamer_pet_armour())))
        {
            notify_fail("You have no armour with which to equip " + QTNAME(pet)
            + ".\n");
            return 0;
        }
    
        if (!sizeof(armours = FIND_STR_IN_ARR(str, armours)))
        {
            notify_fail("None of your companion armours fit that description.\n");
            return 0;
        }
    
        armours[0]->move(pet, 1);
        
        this_player()->catch_msg("You equip the " + pet->query_nonmet_name()
        + " with an armour.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
        + " equips the " + pet->query_nonmet_name() + " with an armour.\n",
        ({ this_player() }), this_player());
        pet->command("$wear " + OB_NAME(armours[0]));
        return 1;
    }
    
    this_player()->catch_msg("You remove the armour from the "
    + pet->query_nonmet_name() + ".\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + " removes "
    + "the armour from the " + pet->query_nonmet_name() + ".\n",
    ({ this_player() }), this_player());
    pet->command("$remove all");
    armours->move(this_player(), 1);
    return 1;
}

public int
pet_stay()
{
    object  pet;
    int     stay, success;

    stay = member_array(query_verb(), ({"tfollow", "tstay"}));
    pet  = MANAGER->query_current_pet(this_player());
    
    if (!objectp(pet) || environment(pet) != environment(this_player()))
    {
        this_player()->catch_msg("Your pet needs to be present for you to "
        + "command it.\n");
        return 1;
    }
    
    if (MANAGER->query_pet_stay(this_player()) == stay)
    {
        this_player()->catch_msg("Your pet is already " +
        (stay ? "staying put" : "following your lead") + ".\n");
        return 1;
    }
    
    if (success = MANAGER->set_pet_stay(this_player(), stay))
    {
        this_player()->catch_msg("You command "
        + capitalize(pet->query_real_name()) + " to "
        + (stay ? "stay" : "follow") + ".\n");
        this_player()->tell_watcher(QCTNAME(this_player()) + " commands "
        + QTNAME(pet) + " to " + (stay ? "stay" : "follow") + "\n");
    }
    
    return success;
}

public int
edit_message(string message, string name)
{
    object  mount, message_ob;
    
    if (!strlen(message))
    {
        write("You set down your quill, deciding not to write that message "
        + "after all.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());
    
    mount = MANAGER->query_current_pet(this_player());
    
    message_ob = clone_object(SPECIALS + "objects/message");

    message_ob->set_message(message);
    message_ob->set_sender(this_player()->query_real_name());
    message_ob->set_who(name);
    message_ob->move(PET_HOUSE, 1);
    mount->add_prop("_tamer_message_ob", message_ob);
    
    (SPECIALS + "tsend")->do_ability(name);
    
    return 1;
}

public int
tsend(string str)
{
    object mount = MANAGER->query_current_pet(this_player());
    string name;
    
    if (!objectp(mount) || 
        !IN_ARRAY(TSCOUT, MANAGER->query_achievements(this_player())))
        return 0;
    
    if (GENUS->query_genus_rideable(mount))
    {
        notify_fail("Your pet does not know how to perform such a feat, it is "
        + "more suitable as a mount than a messenger.\n");
        return 0;
    }
    
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " a message to whom?\n");
        return 0;
    }
    
    if (!parse_command(str, ({}), "[a] 'message' [to] %s", name))
    {
        notify_fail(capitalize(query_verb()) + " a message to whom?\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    
    clone_object(EDITOR_OBJECT)->edit(&edit_message(, name));
    return 1;
}
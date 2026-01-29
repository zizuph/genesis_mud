/*
 *  Created by Carnak, February 2016
 */
#pragma save_binary

inherit "std/object.c";

#include "../defs.h"

#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>

#define RACE        1
#define GENDER      2
#define SIZE        3
#define ADJ1        4
#define ADJ2        5
#define NAME        6

void get_phase(int i);

int     phase,
        taming,
        gender;

object  mount;
        
string  adj1, adj2,
        race, genus,
        name, biome,
       *guild, racial,
        physique;
        
public void 
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("_pet_creation_object_");
    set_short("pet creation");
    set_long("an object for pet creation.\n");
    
    set_no_show();
}

void
process_input(string str)
{   
    str = lower_case(str);
    
    if (IN_ARRAY(str, ({ "q", "quit", "ignore" }) ))
    {
        this_player()->catch_msg("The "+mount->query_short()+" senses "+
        "your hesitation and runs away with haste.\n");
        
        if (this_player()->query_guild_member(GUILD_NAME) &&
            !MANAGER->load_member(this_player()->query_real_name()))
        {
            this_player()->remove_lay_member();
        }
        
        mount->remove_object();
        remove_object();
        return;
    }
    
    if (IN_ARRAY(str, ({ "back", "previous", "reassess" }) ))
    {
        if (phase > 1)
        {
            this_player()->catch_msg("You appear to have been mistaken "+
            "on your previous assessment.\n");
        
            phase -= 1;
        }
        get_phase(phase);
        return;
    }
    
    if (!strlen(str))
    {
        get_phase(phase);
        return;
    }
    
    switch(phase)
    {
        case 0:
        return;
            
        case RACE:
        if (IN_ARRAY(str, GENUS->query_biome(genus, biome) + 
                          GENUS->query_guild_pets(guild, genus) +
                          GENUS->query_racial_pets(racial, genus)))
        {
            if (IN_ARRAY(str, GENUS->query_restrictions(guild, genus)) ||
                IN_ARRAY(str, GENUS->query_restrictions(({ racial }), genus)))
            {
                write("Your knowledge on genus is lacking, you decide "+
                "to reassess the animal.\n");
                break;
            }
            else
            {
                race = str;
                phase++;
                break;
            }
        }
        else 
        {
            write("Your knowledge on genus is lacking, you decide "+
            "to reassess the animal.\n");
            break;
        }
            
        case GENDER:
        if (IN_ARRAY(str, GENDERS))
        {
            switch(str)
            {
                case "male":
                gender = G_MALE;
                    break;
                case "female":
                gender = G_FEMALE;
                    break;
            }
            phase++;
        } else
        {
            write("You hesitate to approach the " + race + " at " +
            "such close proximity.\n");
        }
            break;
        
        case SIZE:
        if (IN_ARRAY(str, GENUS->query_genus_sizes()))
        {
            physique = str;

            mixed   *size_val;
            if (sizeof(size_val = GENUS->query_genus_sizes(str)))
            {
                // Check if the height of the player is enough to mount this pet
                int height = GENUS->query_height(genus, race);
                if (this_player()->query_prop(CONT_I_HEIGHT) >
                    (2 * ((height * size_val[0]) / 100)))
                    write("If your assessment on the physique is correct, this "
                    + "companion will never mature into a size big enough for "
                    + "you to ride on it.\n");
            }
            phase++;
        }
        else 
        {
            write("You further study the " + race + "'s physique " +
            "to determine how big it might grow.\n");
        }
            break;
        
        case ADJ1:
        case ADJ2:
        string *adjs = ({});
        foreach(mixed *adj: GENUS->query_adjectives(genus, race))
        {
            adjs += adj;
        }
        
        if (strlen(physique))
            adjs += ({ physique });
        
        if (IN_ARRAY(str, adjs))
        {
            if (phase == ADJ1)
                adj1 = str;
            else
                adj2 = str;
            
            phase++;
        } else
        {
            write("You find difficulties determining the most "+
            "prominent features.\n");
        }
            break;
        
        case NAME:
        if (strlen(str) > 1 && strlen(str) < 11 && !LANG_IS_OFFENSIVE(str))
        {
            name = str;
            write("You decide that "+capitalize(name)+" would be a "+
            "fitting name for the "+ adj1 +" "+ adj2 +" "+ race +".\n");
            phase++;
        } else
        {
            if (LANG_IS_OFFENSIVE(str))
                write("This is not an acceptable name, please choose something "
                + "else.\n");
            else
                write("That is quite a mouthful, you decide to reconsider the "
                + "name.\n");
        }
            break;
    }
    
    get_phase(phase);
}

void
get_phase(int i)
{
    string *adjs = ({}), *races;
    mixed previous;
    int j;
    
    phase = i;
    
    if (phase < 0)
        phase = 0;
    
    switch(phase)
    {
        case 0:
        write("You study the " +  mount->query_short() + " with great care, "+
        "in an attempt to determine your compatibility with it. In the "+
        "unlikely event that you would falsely assume any specifics of "+
        "the animal, you may 'reassess' it. Should it not be to your "+
        "liking, you could just 'ignore' it and proceed with your "+
        "travels.\n\n");
        phase++;
        get_phase(phase);
        return;
        
        case RACE:
        races   =   GENUS->query_guild_pets(guild, genus) + 
                    GENUS->query_biome(genus, biome) +
                    GENUS->query_racial_pets(racial, genus);
        
        for (j = 0; j < sizeof(races); j++)
        {
            if (IN_ARRAY(races[j], GENUS->query_restrictions(guild, genus)) ||
                IN_ARRAY(races[j], GENUS->query_restrictions(({ racial }),
                genus)))
            {
                races = exclude_array(races, j, j);
                j--;
            }
        }
        
        if (!sizeof(races))
        {
            write("Something went horribly wrong.\n");
            mount->remove_object();
            remove_object();
            return;
        }
        
        write("The animal appears to be the young offspring of the following "
        + "race:\n" +
        implode(sort_array(races), ", ") + "\n");
            break;
            
        case GENDER:
        write("You identify the gender of the " + race + " as:\n"+
        implode(GENDERS,", ") + "\n");
            break;
            
        case SIZE:
/*
        if (!GENUS->query_rideable(genus, race))
        {
            phase++;
            get_phase(phase);
            return;
        }*/
        write("You study the physique of the " + race + " and determine its " +
        "potential for growth to be:\n" +
        implode(sort_array(GENUS->query_genus_sizes()), ", ") + "\n");
            break;
            
        case ADJ1:
        foreach(mixed *adj: GENUS->query_adjectives(genus, race))
        {
            adjs += adj;
        }
        
        if (strlen(physique))
            adjs += ({ physique });
        
        write("The most prominent feature of the " + race + " is that it is:\n"+
        implode(sort_array(adjs), ", ") + "\n");
        
            break;
        case ADJ2:
        foreach(mixed *adj: GENUS->query_adjectives(genus, race))
        {
            if (!IN_ARRAY(adj1, adj))
                adjs += adj;
        }
        
        if (strlen(physique) && adj1 != physique)
            adjs += ({ physique });
        
        write("The " + adj1 + " " + race + " is also prominently:\n" +
        implode(sort_array(adjs), ", ") + "\n");
            break;
            
        case NAME:
        write("You should probably name the " + adj1 + " " + adj2 + " " + race +
        " something if you wish to tame it.\n");
            break;
            
        default:
        if (MANAGER->load_member(this_player()->query_real_name()))
        {       
            if (objectp(MANAGER->query_current_pet(this_player())))
            {
                previous = MANAGER->query_current_pet(this_player());
            }
            else if (stringp(MANAGER->query_current_pet(this_player())))
            {
                previous = filter(all_inventory(environment(this_player())),
                &operator(==)(, MANAGER->query_current_pet(this_player()) @
                &->query_name()));
                
                if (sizeof(previous) && pointerp(previous))
                    previous = previous[0];
            }
            
            if (!MANAGER->add_member(this_player(), name, genus,
                                     race, gender, ({adj1, adj2})))
            {
                write("The " + mount->query_short() + " runs away in fear.\n");
                mount->remove_object();
                remove_object();
                return;
            }
               
            if (objectp(previous))
            {
                write("You set your pet free to once again roam the wilds. " +
                "You gaze out until it disappears from your view entirely.\n");
                previous->remove_object();
            }
            
            write("The " + mount->query_short() + " runs around playfully, " +
            "darting off into the distance. You could 'tsummon' " +
            mount->query_objective() + " should you feel the urge.\n");
            MANAGER->set_pet_size(this_player(), physique);
            mount->remove_object();
            remove_object();
            return;
        }
        
        if (!MANAGER->add_member(this_player(), name, genus,
                                 race, gender, ({adj1, adj2})))
        {
            write("Something spooked the "+mount->query_short()+", sending "+
            "it running off into the distance.\n");
            
            if (this_player()->query_guild_member(GUILD_NAME))
                this_player()->remove_lay_member();
            
            mount->remove_object();
            remove_object();
            return;
        }
        
        write("The "+mount->query_short()+" runs around playfully, darting " +
        "off into the distance. You realize that "+mount->query_pronoun() +
        " is still just a " + GENUS->query_cub(genus) + ", you feel an " +
        "urge to call for "+ mount->query_objective() + ".\n");
        tell_room(environment(mount), QCTNAME(mount) + " darts off into the "
        + "distance.\n", ({ this_player() }), mount);
        MANAGER->add_achievement(this_player(), TSUMMON);
        MANAGER->set_pet_size(this_player(), physique);
        mount->remove_object();
        remove_object();
        return;
    }
    
    input_to(process_input, 1);
}

void
process_taming(string str)
{
    if (time() - taming < 9)
    {
        write("You are in the process of taming the "+mount->query_short()+".\n");
        input_to(process_taming, 1);
        return;
    }
    
    input_to(process_input, 1);
    process_input(str);
}

void
taming_descs(int stage)
{
    switch(stage)
    {
        case 1:
        write("You carefully approach the " + mount->query_short() +
        " in a non-threatening manner.\n");
            break;
        case 2:
        write("The " + mount->query_short() + " attempts to appear bigger " +
        "as you begin to advance, threatening to assault.\n");
            break;
        case 3:
        write("The " + mount->query_short() + " lashes out at you, but " +
        "its attack barely even breaks your skin.\n");
            break;
        case 4:
        write("A whimpering sound escapes from the " + mount->query_short() +
        ", reacting to your towering presence.\n");
            break;
        case 5:
        write("The " + mount->query_short() + " moves forward, pressing " +
        "itself against your hand. It appears to have accepted you.\n");
            break;
    }
}

void
start_taming()
{
    taming = time();
    
    set_alarm(0.0, 0.0, &taming_descs(1));
    set_alarm(2.0, 0.0, &taming_descs(2));
    set_alarm(5.0, 0.0, &taming_descs(3));
    set_alarm(7.0, 0.0, &taming_descs(4));
    set_alarm(9.0, 0.0, &taming_descs(5));
    set_alarm(9.0, 0.0, &get_phase(0));
    
    input_to(process_taming, 1);
}

void
start(object ob)
{
    mount   = ob;
    genus   = mount->query_genus();
    biome   = mount->query_biome();
    racial  = this_player()->query_race();
    guild   = ({
        this_player()->query_guild_name_occ(),
        this_player()->query_guild_name_lay(),
        this_player()->query_guild_name_race(),
        this_player()->query_guild_name_craft()
    });
    start_taming();
}
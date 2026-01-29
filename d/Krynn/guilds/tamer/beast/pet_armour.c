/*
 *  Created by Carnak, December 2016
 */
#pragma save_binary

inherit "std/object.c";

#include "../defs.h"

#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include <money.h>

#define ARMOUR_COST 1728
#define START       10
#define MAT         9
#define CRAFT       8
#define STYLE       7
#define COND        6
#define DYE         5
#define COLOR       4
#define COLOR_ADJ   3
#define RACE        2
#define ADJ2        1
#define ADJ1        0
#define CONF       -1


void    get_phase(int i);

object  player, mount;
string  mat, crft, stle, cnd, col, col_a, genus, race,
       *adjectives = ({"", ""});
int     phase;


string *material = ({ "leather", "metal" }),
       *craft    = ({ "poorly crafted", "roughly crafted", "savagely crafted", "well crafted", "expertly crafted" });
mapping style    = ([
            "leather":({"soft", "boiled", "studded", "spiked"}),
            "metal":({"banded", "scaled", "plated"}),
        ]),
        color    = ([
            "leather":({"black", "grey", "blue", "green", "purple", "red", "yellow", "orange", "white"}),
            "metal":({"bronze", "iron", "steel"})
        ]),
        col_adj  = ([
            "leather":({"pale", "vivid", "brilliant"}),
            "metal":({"silver-plated", "gold-plated", "platinum-plated"})
        ]),
        cond     = ([
            "leather":({"sleek", "smooth", "ripped", "torn", "worn"}),
            "metal":({"polished", "corroded", "battered", "dented", "solid"})
        ]),
        descs    = ([
            "leather":({"@@query_condition@@ @@query_style@@-leather armour, "
            + "@@query_craft@@", }),
            "metal":({"@@query_condition@@ @@query_style@@ @@query_color@@ "
            + "armour, @@query_craft@@"})
        ]);

string
query_condition()
{
    return cnd;
}

string
query_style()
{
    return stle;
}

string
query_craft()
{
    return crft;
}

string
query_color()
{
    return col;
}

string
query_race()
{
    return race;
}

public void 
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("_pet_armour_object_");
    set_short("pet armour");
    set_long("an object for creating pet armour.\n");
    
    set_no_show();
}

void
process_input(string str)
{
    string *adjs = ({});

    str = lower_case(str);
    
    if (IN_ARRAY(str, ({ "q", "quit", "ignore" }) ))
    {
        this_player()->catch_msg("You have cancelled your order for pet " +
        "armour.\n");
        
        remove_object();
        return;
    }
    
    if (IN_ARRAY(str, ({ "back", "previous", "reassess" }) ))
    {
        if (phase < RACE)
        {
            this_player()->catch_msg("You change your mind concerning your " +
            "previous design choices.\n");
        
            phase++;
        }
        get_phase(phase);
        return;
    }
    
    switch(phase)
    {
        case START:
        return;
        
        case MAT:
        if (IN_ARRAY(str, material))
        {
            mat = str;
            phase--;
            break;
        }
        else 
        {
            write("You may only choose from metal and leather.\n");
            break;
        }
        
        case CRAFT:
        if (IN_ARRAY(str, craft))
        {
            crft = str;
            phase--;
            break;
        }
        else 
        {
            write("The available conditions are: " +
            COMPOSITE_WORDS(craft) + ".\n");
            break;
        }
        
        case STYLE:
        if (IN_ARRAY(str, style[mat]))
        {
            stle = str;
            phase--;
            break;
        }
        else 
        {
            write("The available styles are: " + COMPOSITE_WORDS(style[mat]) +
            ".\n");
            break;
        }
        case COND:
        if (IN_ARRAY(str, cond[mat]))
        {
            cnd = str;
            phase--;
            break;
        }
        else 
        {
            write("The available conditions are: " +
            COMPOSITE_WORDS(cond[cnd]) + ".\n");
            break;
        }
        
        case DYE:
        if (IN_ARRAY(str, ({"No", "no", "N", "n"})))
        {
            col_a = "none";
            if (mat == "metal")
                phase--;
            else
                phase = RACE;
        }
        else if (IN_ARRAY(str, ({"Yes", "yes", "Y", "y"})))
        {
            phase--;
        }
            break;
        case COLOR:
        if (IN_ARRAY(str, color[mat]))
        {
            col = str;
            phase--;
            break;
        }
        else 
        {
            write("The available colors are: " +
            COMPOSITE_WORDS(color[mat]) + ".\n");
            break;
        }
        case COLOR_ADJ:
        if (IN_ARRAY(str, col_adj[mat]))
        {
            if (stle == "plated")
            {
                stle = str;
                col_a = "none";

            } else
                col_a = str;
            
            phase--;
            break;
        }
        else 
        {
            write("The available adjectives are: " +
            COMPOSITE_WORDS(col_adj[mat]) + ".\n");
            break;
        }
        case RACE:
        if (IN_ARRAY(str, ({ MANAGER->query_pet_race(player) }) + 
                             GENUS->query_armour(genus) ))
        {
            race = str;
            phase--;
            break;
        }
        else 
        {
            write("You were unable to select an armour design and decide to " +
            "look through them again.\n");
            break;
        }
        
        case ADJ1:
        case ADJ2:
        adjs = GENUS->query_armour() + MANAGER->query_pet_adjs(player);
        if (IN_ARRAY(str, adjs) && !IN_ARRAY(str, adjectives))
            adjectives[phase] = str;
        
        if (strlen(adjectives[phase]))
        {
            phase--;
            break;
        } else
        {
            write("You take another look at the varying armour features.\n");
            break;
        }
        
        case CONF:
        if (!IN_ARRAY(str, ({"Yes", "yes", "Y", "y"})))
        {
            if (IN_ARRAY(str, ({"No", "no", "N", "n"})))
            {
                write("You decide to start over with your custom order.\n");
                phase = RACE;
            } else
                write("Does the " + adjectives[1] + " " + adjectives[0] +
                " " + race + " match your custom order? [Y]es or [N]o, " +
                "please confirm.\n");
        } else
            phase--;
        
        break;
    }
    
    get_phase(phase);
}

void
get_phase(int i)
{
    string *adjs = ({}), *races, new_d;
    mixed previous;
    int j, money;
    
    phase = i;
    
    if (phase > START)
        phase = START;
    
    switch(phase)
    {
        case START:
        write("You discuss the various armour types you could custom " +
        "order with the resident smith.\n\n");
        phase--;
        
        if (phase == START)
            break;
        
        get_phase(phase);
        return;
        
        case MAT:
        write("You may choose from two materials, leather or metal. The " +
        "leather armours cost roughly half as much as the metal ones, the " +
        "determining factor is the quality of the craft.\nDo you want metal " +
        "or leather?\n");
            break;
            
        case CRAFT:
        write("You may select the quality of the armour, the price ranges " +
        "from " + (40 / (2 - member_array(mat, material))) + " to " +
        (100 / (2 - member_array(mat, material))) + " platinum coins.\n" +
        "Please select one of the following qualities: " +
        COMPOSITE_WORDS(craft) + ".\n");
            break;
        case STYLE:
        write("The " + mat + " armours come in the following styles: " + 
        COMPOSITE_WORDS(style[mat]) + ".\n");
            break;
        case COND:
        write("The artisan crafter is able to mimic deteriorated conditions, " +
        "without harming the actual armour. Which condition would you like " +
        "the armour to be in?\n" + COMPOSITE_WORDS(cond[mat]) + ".\n");
            break;
        case DYE:
        write("Would you like for the armour to be "
        + (mat != "leather" ? "plated" : "dyed") + ", [Y]es or [N]o.\n");
            break;
            
        case COLOR:
        write("The available colors are: " + COMPOSITE_WORDS(color[mat]) +
        "\n");
            break;
        case COLOR_ADJ:
        if (col_a == "none")
        {
            get_phase(RACE);
            return;
        }
        write("The available options are: " + COMPOSITE_WORDS(col_adj[mat]) +
        "\n");
            break;
        case RACE:
        races   = ({ MANAGER->query_pet_race(player) }) + 
                     GENUS->query_armour(genus);
        
        write("The armour types would make your pet appear as:\n" +
        implode(races, ", ") + "\n");
            break;
            
        case ADJ2:
        adjs = MANAGER->query_pet_adjs(player);
        write("You want the most prominent feature of your " + race +
        " to be:\n" + implode(adjs, ", ") + "\n");
        
            break;
        case ADJ1:
        adjs = GENUS->query_armour() + ({ MANAGER->query_pet_adjs(player)[1] });
        adjs = filter(adjs, &operator(<)(,0) @ &member_array(, adjectives));
        write("The " + adjectives[1] + " " + race + " should also be " +
        "prominently:\n" + implode(adjs, ", ") + "\n");
            break;
        
        case CONF:
        write("Does the " + adjectives[1] + " " + adjectives[0] + " " + race +
        " match your custom order? [Y]es or [N]o, please confirm.\n");
            break;
            
        default:
        money = ((40 + (15 * member_array(crft, craft))) /
                (2 - member_array(mat, material))) * ARMOUR_COST;
        
        if (!money)
        {
            write("Something went wrong with your purchase.\n");
            return;
        }
        
        if (!MONEY_ADD(this_player(), -money))
        {
            write("The cost to custom forge your specific armour for your pet "
            + "is " + MONEY_TEXT_SPLIT(money) + ". You are lacking the "
            + "sufficient funds to proceed with the transaction.\n");
            remove_object();
            return;
        }
        
        if (MANAGER->load_member(player->query_real_name()))
        {
            new_d = one_of_list(descs[mat]) + " and " + (col_a != "none" ?
            (mat != "metal" ? "dyed " + LANG_ADDART(col_a) + " " +
            col + "." : col_a + ".") : (mat != "metal" ?
            "is a natural brown colour." : "has a polished sheen."));
            
            object arm = clone_object("/d/Krynn/guilds/tamer/beast/obj/armour_obj");
            arm->move(player, 1);
            arm->set_pet_armour_vars(([
                "material" : mat,
                "craft" : crft,
                "style" : stle,
                "condition" : cnd,
                "color" : col,
                "color_adj" : col_a,
                "genus" : genus,
                "race" : race,
                "height" : mount->query_prop(CONT_I_HEIGHT),
                "pet_desc" : process_string(new_d),
            ]));
            
            //MANAGER->set_armour_desc(player, process_string(new_d));
            MANAGER->add_pet_armour(player, ({  adjectives[1],
                                                adjectives[0], race }));
            //MANAGER->set_armour_quality(player, member_array(crft, craft) + 1);
            /*
            if (MANAGER->query_worn_armour(player))
            {
                write("You purchase a new armour for your pet and replace " +
                "it with the old one.\n");
                player->tell_watcher(QCTNAME(player) + " purchases a new " +
                "set of armours and replaces the ones currently worn by " +
                player->query_possessive() + " pet.\n");
                
                remove_object();
                return;
            }*/
            
            write("An armour has been created for your " + race + ". You may "
            + "wear and remove the armour at any time by 'tarmour'.\n");
            player->tell_watcher(QCTNAME(player) + " orders an armour for " +
            player->query_possessive() + " " + race + ".\n");
            
            remove_object();
            return;
        }
        
        write("Something went wrong.\n");
        remove_object();
        return;
    }
    
    input_to(process_input, 1);
}

void
start_armour(object tamer, object beast)
{
    player  = tamer;
    mount   = beast;
    genus   = beast->query_genus();
    
    get_phase(START);
    input_to(process_input, 1);
}
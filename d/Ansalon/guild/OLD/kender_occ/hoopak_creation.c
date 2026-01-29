#pragma save_binary

inherit "std/object.c";

#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>

#include "guild.h"

#define PRESET_KENDER_HOOPAK_COLORS "_preset_kender_hoopak_colors"
#define PRESET_KENDER_HOOPAK_PAINTS "_preset_kender_hoopak_paints"

#define START       3
#define ADJ3        2
#define ADJ2        1
#define ADJ1        0
#define CONF       -1

void    get_phase(int i);

object  player, hoopak;
string *adjectives = ({"", "", ""}),
        weapon, ornament_str;
int     phase;

string *all_col     =   ({  "alabaster", "almond", "amber", "amethyst", "apricot",
                            "aquamarine", "azure", "beige", "bisque", "black",
                            "blue", "brown", "cherry", "cobalt", "cream", "cyan",
                            "emerald", "ginger", "gold", "green", "indigo", "ivory",
                            "jade", "lavender", "lilac", "lime", "magenta",
                            "maroon", "orange", "peach", "pearl", "peridot", "pink",
                            "purple", "red", "ruby", "sapphire", "scarlet",
                            "silver", "teal", "topaz", "turquoise", "vermillion",
                            "violet", "viridian", "white", "yellow"
                        });

mapping ornament    =   ([  "beads":"bead-adorned", "feathers":"feather-trimmed",
                            "strings":"brightly-tassled", "leaves":"leaf-entwined", 
                            "flowers":"flower-braided", "ribbons":"vividly-ribboned"
                        ]);
mapping ornamented  =   ([  "beads":"beaded", "feathers":"feathered",
                            "strings":"stringed", "leaves":"leafed",
                            "flowers":"flowered", "ribbons":"ribboned"
                        ]);
string *paints      =   ({});
string *colors      =   ({});

string *
get_random_colors(int j)
{
    int i, k;
    string one_of, *random_set = ({});
    
    for (i = 0; i < j; i++)
    {
        if (k > j)
            return random_set;
        
        if (stringp(one_of = one_of_list(all_col)) &&
            member_array(one_of, random_set) < 0)
            random_set += ({ one_of });
        else
            k++, i--;
    }
    
    return random_set;
}
         
public void 
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("_hoopak_creator");
    set_short("hoopak creator");
    set_long("an object for creating hoopaks.\n");
    
    set_no_show();
}

void
process_input(string str)
{   
    str = lower_case(str);
    
    if (player != this_player())
        player = this_player();
    
    if (IN_ARRAY(str, ({ "q", "quit", "ignore" }) ))
    {
        player->catch_msg("You have stopped altering the " +
        weapon + " and restored it to its proper state.\n");
        
        remove_object();
        return;
    }
    
    if (IN_ARRAY(str, ({ "back", "previous", "reassess" }) ))
    {
        if (phase < ADJ3)
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
        
        case ADJ1:
        case ADJ2:
        case ADJ3:
        if (IN_ARRAY(str, (phase != ADJ2 ? (phase != ADJ3 ? colors : paints)
            : m_indexes(ornament))))
        {
            if (phase != 1)
                adjectives[phase] = str;
            else if (IN_ARRAY(str, m_indexes(ornament)))
            {
                ornament_str = str;
                adjectives[phase] = ornament[str];
            }
        }
        
        if (strlen(adjectives[phase]))
        {
            phase--;
            break;
        } else
        {
            write("You rethink the design and imagine all the possible " +
            "features.\n");
            break;
        }
        
        case CONF:
        if (!IN_ARRAY(str, ({"Yes", "yes", "Y", "y"})))
        {
            if (IN_ARRAY(str, ({"No", "no", "N", "n"})))
            {
                write("You change your mind and decide to start over.\n");
                phase = ADJ3;
            } else
                write("Does the " + adjectives[1] + " " + adjectives[2] +
                " hoopak suit your tastes? [Y]es or [N]o, please confirm.\n");
        } else
            phase--;
        
        break;
    }
    
    get_phase(phase);
}

void
get_phase(int i)
{
    mixed   previous;
    object  shadow,
            sling;
    int j;
    
    phase = i;
    
    if (!sizeof(paints = player->query_prop(PRESET_KENDER_HOOPAK_PAINTS)))
    {
        paints = get_random_colors(8 + random(8));
        player->add_prop(PRESET_KENDER_HOOPAK_PAINTS, paints);
    }
    
    if (!sizeof(colors = player->query_prop(PRESET_KENDER_HOOPAK_COLORS)))
    {
        colors = get_random_colors(8 + random(8));
        player->add_prop(PRESET_KENDER_HOOPAK_COLORS, colors);
    }
    
    if (phase > START)
        phase = START;
    
    switch(phase)
    {
        case START:
        weapon = hoopak->short();
        write("You sit down to work on the " + weapon + ".\n");
        say(QCTNAME(this_player()) + " sits down to work on the " + weapon +
        ".\n");
        phase--;
        
        if (phase == START)
            break;
        
        get_phase(phase);
        return;
        
        case ADJ3:
        write("You look through your pouches and find some paints to use " +
        "on your hoopak:\n" +
        implode(paints, ", ") + "\n");
            break;
            
        case ADJ2:
        write("You also find various ornaments with which you could adorn " +
        "your hoopak:\n" + implode(m_indexes(ornament), ", ") + "\n");
        
            break;
        case ADJ1:        
        write("You find " + ornament_str + " of numerous colors in your " +
        "pouches:\n" +
        implode(colors, ", ") + "\n");
            break;
        
        case CONF:
        write("Does the " + adjectives[1] + " " + adjectives[2] + " hoopak " +
        "suit your tastes? [Y]es or [N]o, please confirm.\n");
            break;
            
        default:
        
        weapon = hoopak->short();
        shadow = clone_object(HOOPAK_SHADOW);
        
        if (shadow->shadow_me(hoopak))
        {
            shadow->set_hoopak("names", ({"weapon", "hoopak", "staff"}));
            shadow->set_hoopak("short", adjectives[1] + " " +
                                        adjectives[2] + " hoopak");
            shadow->set_hoopak("p_short", adjectives[1] + " " +
                                          adjectives[2] + " hoopaks");
            shadow->set_hoopak("long", "This is a staff, that is for sure, " +
            "but quite an unusual one. It is made from a " + weapon + " " +
            "that has been modified with a forked top and steel-clad bottom " +
            "end that comes to a sharp point. The forked top has been " +
            "adjusted to be used as a catapult and has a leather sling tied " +
            "across it. The shaft has been painted in " + adjectives[2] + " " +
            "finish and adorned at the top with " + adjectives[0] + " " +
            ornament_str + ".\n");
            shadow->set_hoopak("adjs", ({adjectives[2], adjectives[1],
            adjectives[0] + "-" + ornamented[ornament_str],
            ornamented[ornament_str]}));
            shadow->init_hoopak_shadow(player);
            write("You successfully alter the " + weapon + " into a hoopak " +
            "of your own design.\n");
            say(QCTNAME(this_player()) + " successfully altered the " + weapon +
            " into a hoopak.\n");
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
init_hoopak(object weapon, object actor)
{
    hoopak = weapon;
    player = actor;
    
    get_phase(START);
    input_to(process_input, 1);
}
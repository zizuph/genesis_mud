
/* 
    Ring for Gelan Cadets who graduate, a token 
    of recognition from the guild. Graduates can 
    vary the attributes of the ring (potentially 
    permanently) if they visit the cadet training 
    room. The gem surface desc info is from 
    /d/Genesis/gems/obj/. 

    Coded by Maniac@Genesis, September 1997 

    History: 
     25/12/02          nade configure_properties() public    Maniac 
     4-6/01            now configurable with various 
                       images, colours and patterns, 
                       and cgimage command added             Maniac 
     7/4/01            inherits general stuff                Maniac 
        /99            Description updates                   Maniac 
        /98            Description updates                   Maniac 
       9/97            Created                               Maniac 
 */ 

#pragma strict_types

inherit "/std/object"; 
#include "cadet.h" 
inherit GC_GR_SUPPORT; 

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <std.h>


/* 
 * Prototypes. 
 */ 
varargs private void configure_ring(string arg); 
private void configure_short(); 
private void configure_properties(); 
private void configure_lettering(); 
string graduation_ring_long(); 
string graduation_ring_short(); 

string query_centre_colour(); 
string query_centre_figure(); 
string query_inner_stone(); 
string query_letter_type(); 
string query_marble_colour(); 
string query_ray_type(); 
string query_setting_material(); 
string query_light_travel_type(mixed ix); 
string query_inner_stone_desc(mixed ix); 


/* 
 * Whether description initialised on cloning the ring. 
 */ 
private int init_ring = 0; 


/* 
 * Configurable attributes. 
 */ 
static string *attributes = 
       ({ "centre colour", 
          "centre figure", 
          "inner stone", 
          "letter type", 
          "marble colour", 
          "ray type", 
          "setting material" }); 

/* 
 * Choices for attributes. 
 */ 
static string *centre_colours = 
       ({ "golden", "crystal", "silver" }); 
static string *centre_figures = 
       ({ "falcon", "hawk", "kestrel" }); 
static string *inner_stones = 
       ({ "lapis lazuli", "quartz", "onyx" }); 
static string *letter_types = 
       ({ "golden", "silver", "crystal" }); 
static string *marble_colours = 
       ({ "white", "faded green", "faded red" }); 
static string *ray_types = 
       ({ "golden", "silver", "crystal" }); 
static string *setting_materials = 
       ({ "gold", "bronze", "crystal", 
          "iron", "silver", "steel" }); 

/* 
 * Extended attribute descriptions .. 
 */ 
// .. for ray types (corresponding indexes) 
static string *light_travel_types = 
       ({ "radiate from", "emanate from", "refract from" }); 
// .. for inner stones (corresponding indexes) 
static string *inner_stone_descs = 
       ({ "vivid blue", "soft grey", "lustrous black" }); 


/* 
 * Dynamic global variables. 
 */ 
int centre_figure = 0, 
    centre_colour = 0, 
    inner_stone = 0, 
    marble_colour = 0, 
    setting_material = 0, 
    ray_type = 0, 
    letter_type = 0; 


/* 
 ****************************** 
 * Function code starts here! * 
 ****************************** 
 */ 

void 
create_object() 
{ 
    set_name("ring"); 
    add_name(GC_RING_ID); 
    if (!init_ring) 
        configure_ring(); 

    config_wearable_item(A_ANY_FINGER, 1, 6); 
    add_prop(OBJ_I_VALUE, 0); 
    add_prop(OBJ_I_WEIGHT, 50); 
    add_prop(OBJ_I_VOLUME, 50); 
} 


string
graduation_ring_lettering()
{
    string rn; 

    rn = environment(this_object())->query_real_name(); 

    return (

    sprintf("%|80s", 
            "Congratulations " + capitalize(rn) + ".") + 
            "\n\n" + 
    sprintf("%|80s", 
            "You have graduated from the Cadets of Gelan.") + 
            "\n\n" + 
    sprintf("%|80s","May the " + query_ray_type() + 
            " star bring you strength on your travels.") + 
            "\n\n" + 
    sprintf("%|80s", 
            "And may your cast iron stomach serve you well!") + 
            "\n\n" + 
    sprintf("%|80s", 
            "See \"help graduate\" for more information.") + 
            "\n"); 
} 


/* 
 * Function:      configure_ring 
 * Description:   Sets up the various configurable parts of 
 *                the ring description based on the main 
 *                design and the values of the attributes. 
 * Arguments:     string arg - the autoload string 
 */ 
varargs private void 
configure_ring(string arg) 
{ 
    string tmp; 

    if (stringp(arg) && strlen(arg)) 
    { 
        if (sscanf(arg, "%s#i1#%d#i2#%d#i3#%d#i4#%d#i5#%d#i6#%d#i7%d#", 
                   tmp, 
                   centre_figure, centre_colour, inner_stone, 
                   marble_colour, setting_material, ray_type, 
                   letter_type) == 8) 
        { 
            init_ring = 1; 
        } 
    } 
    configure_short(); 
    set_long(graduation_ring_long()); 
    configure_lettering(); 
    configure_properties(); 
} 


/* 
 * Function:      configure_properties 
 * Description:   Configure's the descriptions in the 
 *                properties of the ring based on the ray 
 *                colour attribute. 
 */ 
public void 
configure_properties() 
{ 
    add_prop(OBJ_M_NO_SELL, 
             "If you want to rid yourself of " + 
             LANG_THESHORT(this_object()) + 
             " you may <lose> it.\n"); 
    add_prop(OBJ_M_NO_DROP, 
             "If you want to rid yourself of " + 
             LANG_THESHORT(this_object()) + 
             " you may <lose> it.\n"); 
} 


/* 
 * Function:      configure_short 
 * Description:   Configure's the short description and 
 *                adjectives of the ring based on the 
 *                ray type attribute. 
 */ 
private void 
configure_short() 
{ 
    set_adj(({query_ray_type(), "star"})); 
    set_short(graduation_ring_short()); 
} 


/* 
 * Function:     configure_lettering 
 * Description:  Configures the items describing the lettering 
 *               on the ring based on the letter type attribute. 
 */ 
private void 
configure_lettering() 
{ 
    remove_cmd_item("lettering"); 
    add_cmd_item(({"lettering", query_letter_type() + " lettering"}), 
        "read", graduation_ring_lettering); 
    remove_item("lettering"); 
    add_item(({"lettering", query_letter_type() + " lettering"}), 
        "You can read it.\n"); 
} 


/* 
 * Function:   graduatin_ring_long 
 * Returns:    string - the long description of the ring. 
 */ 
string 
graduation_ring_long() 
{ 
    return 
       ("The " + query_ray_type() + " star ring, " + 
        "a memento of graduating from the Cadets of Gelan, " + 
        "has a hexagonal " + query_setting_material() + 
        " setting displaying a circular " + query_marble_colour() + 
        " marble stone, which is set in turn with a hexagonal " + 
        query_inner_stone() +  " stone, its " + 
        query_inner_stone_desc(inner_stone) + 
        " surface decorated with the image of " + 
        LANG_ADDART(query_centre_colour()) + " " + 
        query_centre_figure() + 
        ". Six fine " + query_ray_type() + " lines " + 
        query_light_travel_type(ray_type) + " the " + 
        "points of the " + query_inner_stone() + " to those of the " + 
        query_setting_material() + " setting, forming a barely " + 
        "perceptible star. " + capitalize(query_letter_type()) + 
        " lettering traces a path around the edge of the " + 
        query_marble_colour() + " marble and engravings of a " + 
        "sword, spear, axe, dagger, mace and gauntlet decorate " + 
        "the " + query_setting_material() + " setting. The ring " + 
        "is a token of recognition from and by the Cadets of Gelan " + 
        "guild only. The command <cglist> will list the graduates " + 
        "currently in the game. If you ever wish to <lose> the ring " + 
        "you may do so.\n"); 
} 


/* 
 * Function:     graduation_ring_short 
 * Description:  string - the short description of the ring. 
 */ 
string 
graduation_ring_short() 
{ 
    return query_ray_type() + " star ring"; 
} 


/* 
 * Function:     query_choices 
 * Description:  Given a cinfigurable attribute of the ring, 
 *               return the choices for its value. 
 * Arguments:    string attribute - the attribute 
 * Returns:      string *         - the choices 
 */ 
string * 
query_choices(string attribute) 
{ 
    switch (attribute) 
    { 
        case "centre colour" : 
            return centre_colours; 
            break; 
        case "centre figure" : 
            return centre_figures; 
            break; 
        case "inner stone" : 
            return inner_stones; 
            break; 
        case "letter type" : 
            return letter_types; 
            break; 
        case "marble colour" : 
            return marble_colours; 
            break; 
        case "ray type" : 
            return ray_types; 
            break; 
        case "setting material" : 
            return setting_materials; 
            break; 
    } 
    return 0; 
} 


/* 
 * Function:      changed_attribute 
 * Description:   Sets a new long description, and if 
 *                describes the change of an attribute in 
 *                the ring to this_player() if required. 
 * Arguments:     string attribute  - the attribute 
 *                string val        - the value 
 *                int written       - message written only if this is 1 
 */ 
varargs private void 
changed_attribute(string attribute, string val, int written) 
{ 
    if (written) 
        write("The local jeweller alters your ring so that " + 
              "the " + attribute + " is " + val + ".\n"); 
    set_long(graduation_ring_long()); 
} 


/* 
 * Function:      set_index_of_attribute 
 * Description:   Set the value of a ring attribute. 
 * Arguments:     string attribute  - name of a configurable attribute 
 *                string val        - the new value of the attribute 
 *                int written       - messages written only if this is 1 
 * Returns:       int               - whether successful 
 */ 
varargs int 
set_value_of_attribute(string attribute, string val, int written) 
{ 
    int ix; 

    switch (attribute) 
    { 
        case "centre colour" : 
            if ((ix = member_array(val, centre_colours)) != -1) 
            { 
                centre_colour = ix; 
                changed_attribute("centre colour", val, written); 
                return 1; 
            } 
            break; 
        case "centre figure" : 
            if ((ix = member_array(val, centre_figures)) != -1) 
            { 
                centre_figure = ix; 
                changed_attribute("centre figure", LANG_ADDART(val), 
                                  written);  
                return 1; 
            } 
            break; 
        case "inner stone" : 
            if ((ix = member_array(val, inner_stones)) != -1)  
            { 
                inner_stone = ix; 
                changed_attribute("inner stone", LANG_ADDART(val), 
                                  written); 
                return 1; 
            } 
            break; 
        case "letter type" : 
            if ((ix = member_array(val, letter_types)) != -1) 
            { 
                letter_type = ix; 
                changed_attribute("letter type", val, written); 
                configure_lettering(); 
                return 1; 
            } 
            break; 
        case "marble colour" : 
            if ((ix = member_array(val, marble_colours)) != -1) 
            { 
                marble_colour = ix; 
                changed_attribute("marble colour", val, written); 
                return 1; 
            } 
            break; 
        case "ray type" : 
            if ((ix = member_array(val, ray_types)) != -1) 
            { 
                ray_type = ix; 
                changed_attribute("ray type", val, written); 
                configure_short(); 
                configure_properties(); 
                return 1; 
            } 
            break; 
        case "setting material" : 
            if ((ix = member_array(val, setting_materials)) != -1) 
            { 
                setting_material = ix; 
                changed_attribute("setting material", val, written); 
                return 1; 
            } 
            break; 
        default : 
            notify_fail(capitalize(attribute) + " is an " + 
                        "unknown attribute.\n"); 
            return 0; 
            break; 
    } 
    notify_fail(capitalize(attribute) + " cannot be changed to " + 
                val + ". The possible choices are " + 
                COMPOSITE_WORDS(query_choices(attribute)) + ".\n"); 
    return 0; 
} 


/* 
 * Function:     query_light_travel_type 
 * Description:  Should return the light travel type description 
 *               for a ray type by its index or name. 
 * Returns:      string - the light type 
 */ 
string 
query_light_travel_type(mixed ix) 
{ 
    int tmp; 

    if (stringp(ix) && 
        ((tmp = member_array(ix, ray_types)) != -1)) 
        return light_travel_types[tmp]; 

    if (intp(ix) && (ix < sizeof(ray_types))) 
        return light_travel_types[ix]; 

    return 0; 
} 


/* 
 * Function:     query_inner_stone_desc 
 * Description:  Should return the stone surface description of 
 *               for an inner stone by its index or name. 
 * Returns:      string - the stone description 
 */ 
string 
query_inner_stone_desc(mixed ix) 
{ 
    int tmp; 

    if (stringp(ix) && 
        ((tmp = member_array(ix, inner_stones)) != -1)) 
        return inner_stone_descs[tmp]; 

    if (intp(ix) && (ix < sizeof(inner_stones))) 
        return inner_stone_descs[ix]; 

    return 0; 
} 


/* 
 * Function:     query_centre_figure 
 * Returns:      string - text for the centre figure of the ring. 
 */ 
string 
query_centre_figure() 
{ 
    return centre_figures[centre_figure]; 
} 


/* 
 * Function:     query_centre_colour 
 * Returns:      string - text for the centre colour of the ring. 
 */ 
string 
query_centre_colour() 
{ 
    return centre_colours[centre_colour]; 
} 


/* 
 * Function:      query_inner_stone 
 * Returns:       string - text for the inner stone of the ring. 
 * 
 */
string 
query_inner_stone() 
{ 
    return inner_stones[inner_stone]; 
} 


/* 
 * Function:     query_marble_colour 
 * Returns:      string - text for the marble colour of the ring. 
 */ 
string 
query_marble_colour() 
{ 
    return marble_colours[marble_colour]; 
} 


/* 
 * Function:     query_marble_colour 
 * Returns:      string - text for the letter type of the ring. 
 */ 
string 
query_letter_type() 
{ 
    return letter_types[letter_type]; 
} 


/* 
 * Function:     query_ray_type 
 * Returns:      string - text for the ray type of the ring. 
 */ 
string 
query_ray_type() 
{ 
    return ray_types[ray_type]; 
} 


/* 
 * Function:     query_setting_material 
 * Returns:      string - text for the setting material of the ring. 
 */ 
string 
query_setting_material() 
{ 
    return setting_materials[setting_material]; 
} 


/* 
 * Function:     init_arg 
 * Description:  Called on autoloading to initialise from the 
 *               autoload string. 
 */ 
void 
init_arg(string arg) 
{ 
    ::init_arg(arg); 
    configure_ring(arg); 
} 


string 
query_auto_load() 
{ 
    return (::query_auto_load() + 
            "#i1#" + centre_figure + 
            "#i2#" + centre_colour + 
            "#i3#" + inner_stone + 
            "#i4#" + marble_colour + 
            "#i5#" + setting_material + 
            "#i6#" + ray_type + 
            "#i7#" + letter_type + "#"); 
} 


/* 
 * Function:     cgimage 
 * Description:  Action function to allow modification of the 
 *               ring's attributes at the cadet training room, 
 *               and provide information about the command. 
 * Returns:      int - success 
 */ 
int 
cgimage(string str) 
{ 
    string attribute, val, *choices; 

    if (stringp(str) && strlen(str)) 
    { 
        if (!this_player()->query_wiz_level() && 
            file_name(environment(this_player())) != GC_TRAINROOM) 
        { 
            notify_fail("You'll have to visit the cadet training " + 
                "room if you want to try that.\n"); 
            return 0; 
        } 

        if (str == "list attributes") 
        { 
            write("The ring attributes that you can " + 
                "choose values for are: " + COMPOSITE_WORDS(attributes) + 
                ".\n"); 
            return 1; 
        } 
        else if (sscanf(str, "list values of %s", attribute) == 1) 
        { 
            if (sizeof(choices = query_choices(attribute))) 
            { 
                write("The following choices are available for " + 
                    attribute + ": " + COMPOSITE_WORDS(choices) + ".\n"); 
                return 1; 
            } 
            notify_fail("There is not an attribute called " + 
                attribute + " on the ring that you can choose a " + 
                "value for.\n"); 
            return 0; 
        } 
        else if (sscanf(str, "choose %s for %s", val, attribute) == 2) 
        { 
            return set_value_of_attribute(attribute, val, 1); 
        } 
    } 

    this_player()->more("In the cadet training room " + 
        "you can choose to vary the attributes of your " + 
        "graduation ring within general limits in the " + 
        "design.\n" + 
        "The following commands are possible:\n\n" + 
        "cgimage list attributes.\n" + 
        "    (to list all the ring attributes).\n" + 
        "cgimage list values of <attribute>.\n" + 
        "    (e.g. \"cgimage list values of centre figure\").\n" + 
        "cgimage choose <value> for <attribute>.\n" + 
        "    (e.g. \"cgimage choose hawk for centre figure\").\n\n" + 
        "After a successful choice, your ring will " + 
        "be different. There are many attributes " + 
        "available to choose values for, making a " + 
        "fair number of variations in the ring possible.\n"); 
    return 1; 
} 


void 
init() 
{ 
    ::init(); 
    if (pardon_time <= time()) 
       add_action(cgimage, "cgimage"); 
} 

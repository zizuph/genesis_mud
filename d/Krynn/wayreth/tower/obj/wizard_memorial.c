inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>

#include "/d/Krynn/common/warfare/warfare.h"

// Whether the gem cavity is filled (1) or empty (0)
int crystal_one, crystal_two, crystal_three, crystal_four;

// Set the shape of the gem cavities
string crystal_shape_one = "ellipse";
string crystal_shape_two = "tear";
string crystal_shape_three = "triangular";
string crystal_shape_four = "oval";

// Set the description of the gems filling the cavities
string crystal_desc_one = "";
string crystal_desc_two = "";
string crystal_desc_three = "";
string crystal_desc_four = "";

// Number of gem cavities filled
int cavities_no = 0;

// Queries whether the crystal slot if used or not.
public int
query_crystal_slot_one()
{
    return crystal_one;
}

public int
query_crystal_slot_two()
{
    return crystal_two;
}

public int
query_crystal_slot_three()
{
    return crystal_three;
}

public int
query_crystal_slot_four()
{
    return crystal_four;
}

// Queries the shape of the crystal cavities
public string
query_crystal_shape_one()
{
    return crystal_shape_one;
}

public string
query_crystal_shape_two()
{
    return crystal_shape_two;
}

public string
query_crystal_shape_three()
{
    return crystal_shape_three;
}

public string
query_crystal_shape_four()
{
    return crystal_shape_four;
}

// Queries whether there are any free slots available
public int
query_free_gem_slot(string shape)
{
    if(!query_crystal_slot_one() && (query_crystal_shape_one() == shape))
        return 1;

    if(!query_crystal_slot_two() && (query_crystal_shape_two() == shape))
        return 2;

    if(!query_crystal_slot_three() && (query_crystal_shape_three() == shape))
        return 3;

    if(!query_crystal_slot_four() && (query_crystal_shape_four() == shape))
        return 4;

    return 0;
}

public void
set_gem_slots(string shape, string gem_desc)
{
    if(shape == "ellipse")
    {
        crystal_one = 1;
        crystal_desc_one = gem_desc;
    }
    if(shape == "tear")
    {
        crystal_two = 1;
        crystal_desc_two = gem_desc;
    }
    if(shape == "triangular")
    {
        crystal_three = 1;
        crystal_desc_three = gem_desc;
    }
    if(shape == "oval")
    {
        crystal_four = 1;
        crystal_desc_four = gem_desc;
    }
}

public void
reset_gem_slots()
{
    crystal_one = 0;
    crystal_two = 0;
    crystal_three = 0;
    crystal_four = 0;
    cavities_no = 0;

    crystal_desc_one = "";
    crystal_desc_two = "";
    crystal_desc_three = "";
    crystal_desc_four = "";
}

void
create_container()
{
    set_name("memorial");
    set_adj("moss");
    add_adj("moss-covered");
    set_short("@@short_descr");
    set_long("@@long_descr");
    set_key(7111999);  // There is no key for this strongbox

    set_pick(100);

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 900000);
    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(OBJ_I_VALUE,12000);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP,0);
    add_prop(CONT_I_WEIGHT, 95500);
    add_prop(CONT_I_VOLUME,7500);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);

    add_prop(MAGIC_AM_ID_INFO, ({ "This memorial is a magical " +
        "receptacle that can be opened through the insertion of " +
        "four different shaped Augmentation Crystals.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
}

void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the memorial.\n");
	return;
    }
    ::enter_inv(obj,from);
}

void
leave_inv(object obj, object to)
{
    ::leave_inv(obj,to);
}

string
short_descr()
{
    return "moss-covered memorial";
}

string
memorial_base()
{
    string str_desc = "You notice the base of the memorial has ";

    if(!cavities_no)
        return "Within the base of the memorial you notice four " +
            "dark cavities - one shaped like a tear, one shaped " +
            "like an oval, one triangular-shaped, and one " +
            "ellipse-shaped.";

    if(crystal_one)
        str_desc += LANG_ADDART(crystal_desc_one)+ " embedded on the " +
            "side facing north, ";
    else
        str_desc += "an empty ellipse-shaped cavity, ";        

    if(crystal_two)
        str_desc += LANG_ADDART(crystal_desc_two)+ " embedded on the " +
            "side facing south, ";
    else
        str_desc += "an empty tear-shaped cavity, ";

    if(crystal_three)
        str_desc += LANG_ADDART(crystal_desc_three)+ " embedded on the " +
            "side facing east, and ";
    else
        str_desc += "an empty triangular-shaped cavity, and "; 

    if(crystal_four)
        str_desc += LANG_ADDART(crystal_desc_four)+ " embedded on the " +
            "side facing west.";
    else
        str_desc += "an empty oval-shaped cavity.";

    return str_desc;  

}

string
long_descr()
{
    return "This moss-covered statue of a robed human wizard " +
        "is a memorial to one of the greatest practitioners " +
        "of the Magical Arts the world of Krynn has ever seen " +
        "- Vincil Da Jevra, the Highmage slain at the beginning " +
        "of the Lost Battles that ended the golden age of magic. " +
        memorial_base();
}

/*
 * Function name: short
 * Description  : Add the status of the container to it.
 * Arguments    : for_obj - who wants to know the short
 * Returns      : The short description.
 */
public varargs string
short(object for_obj)
{
    return short_descr();
}

/*
 * Function name: long
 * Description  : A the status of the container to it.
 * Arguments    : string str - the psuedo-item the person wants to see.
 *                object for_obj - who wants to know the long
 * Returns      : string - The long description.
 */
public varargs string
long(string str, object for_obj)
{
    string desc;
    desc = long_descr();
    if (!strlen(str))
    {
        desc += ((query_prop(CONT_I_CLOSED)) ?
            "\n" : " A panel at the base of the memorial lies open, ");
    }
    return desc;
}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell("containing " + COMPOSITE_DEAD(obarr) + ".\n");
    }
    else
    {
        for_obj->catch_tell("with whatever contents it once held " +
            "now gone.\n");
    }
}

void
unlock_memorial()
{
    TO->remove_prop(CONT_I_LOCK);
    TO->remove_prop(CONT_I_CLOSED);

    tell_room(environment(TO), "A panel at the base of the " +
        short()+ " opens!\n", ({ }), TO);
}


int
insert_gem(string str)
{
    string gem, monument;
    mixed  *oblist,
           *monuments;
    object * item;
    object player = this_player();
    string cavity_desc = "cavity";

    if (!str)
    {
        notify_fail("Insert what?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[the] %s 'into' [the] %s", gem, monument))
    {
        notify_fail("Insert <what> into <what>?\n");
        return 0;
    }

    if (!sizeof(oblist = FIND_STR_IN_ARR(gem, all_inventory(player))))
    {
        notify_fail("You possess no " + gem + ".\n");
        return 0;
    }

    if (!sizeof(monuments = FIND_STR_IN_ARR(monument, 
        all_inventory(environment(this_object())))))
    {
        notify_fail("You see no " + monument + ".\n");
        return 0;
    }

    if (!IN_ARRAY(this_object(), monuments))
    {
        notify_fail("You see no " + monument + "!\n");
        return 0; 
    }


    if(crystal_one && crystal_two && crystal_three && crystal_four)
    {
        notify_fail("There are already four augmentation stones inserted " +
            "in to the " +short()+ ". You cannot put any more in!\n");
        return 0;
    }

    string *gem_array = filter(m_indexes(MASTERWORK_GEM_PROPS), 
        &call_other(oblist[0], "id",));

    if(!sizeof(gem_array))
    {
        notify_fail("The " +oblist[0]->query_short()+ " is the wrong " +
            "shape to insert into your " +short()+ ".\n");
        return 0;
    }

    string gem_id = gem_array[0];
    string gem_shape = MASTERWORK_GEM_PROPS[gem_id][0];
    string benefit_type = MASTERWORK_GEM_PROPS[gem_id][1];
    int benefit_bonus = MASTERWORK_GEM_PROPS[gem_id][2]; 
    string gem_desc = oblist[0]->query_name();  

    if (cavities_no > 3)
    {
        player->catch_tell("There are no free cavities in the " +short()+ 
            " to insert your " +oblist[0]->query_short()+ " into.\n");
        return 1;
    }

    if (!query_free_gem_slot(gem_shape))
    {
        player->catch_tell("The " +oblist[0]->query_short()+ " is the " +
            "wrong shape to insert into the " +((cavities_no == 3) ? 
            "remaining cavity" : "cavities") + " of the " +short()+ ".\n");
        return 1;
    }

    int gem_slot = query_free_gem_slot(gem_shape);

    player->catch_tell("You insert " +oblist[0]->short()+ " into "+
        "the " +gem_shape+ "-shaped " +cavity_desc+ " of the " +
        short()+ ". The stone robes of the statue briefly glow with red " +
        "runes as the " + oblist[0]->query_short()+ " locks in to place.\n");

    tell_room(environment(player), QCTNAME(player)+ " inserts " + 
        oblist[0]->short()+ " into the " +short_descr()+ ".\n", 
        ({ player }), player);

    oblist[0]->reduce_heap_size();
    set_gem_slots(gem_shape, gem_desc);
    cavities_no += 1;

    if(cavities_no == 4)
        unlock_memorial();
    
    return 1;
}

void
init()
{
    ::init();
    add_action(insert_gem, "insert");
    add_action(insert_gem, "affix");
}


/*
 *  /d/Sparkle/guilds/new_merc/obj/weapon_rack.c
 *
 *  This is the standard weapon rack used in the Tutorial Guild in Sparkle.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Genesis/specials/guilds/objs/weapon_rack";


#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>


/* Prototypes */
public void        create_rack();


/*
 * Function name:        create_rack
 * Description  :        the object constructor
 */
public void
create_rack()
{
    set_name("rack");
    add_adj( ({ "large", "weapon", "weapons" }) );
    set_short("large weapon rack");
    set_long("\nThe entire length of the west wall is filled with"
      + " many fixtures, cabinets, and pegs which"
      + " facilitate the organized storage and display of all types"
      + " of weapons.\n\n"); 

    add_item( ({ "fixture", "fixtures" }),
        "The fixtures that comprise the rack are meant to provide"
      + " easy access and display of the weapons.\n");
    add_item( ({ "cabinet", "cabinets" }),
        "The cabinets that are part of the weapon rack have glass"
      + " doors so that the contents are easily viewed.\n");
    add_item( ({ "glass", "glassy" }),
        "You know ... see-through stuff.\n");
    add_item( ({ "see-through stuff", "see through stuff" }),
        "Wow ... you can see through it. Sweet!\n");
    add_item( ({ "glass door", "glass doors", "door", "doors",
                 "cabinet door", "cabinet doors" }),
        "The cabinet doors have glass fronts.\n");
    add_item( ({ "glass fronts", "fronts" }),
        "Ooo ... glassy.\n");
    add_item( ({ "peg", "pegs" }),
        "The pegs mostly come in two's, placed a few inches apart"
      + " so that the hilt of a blade, the head of a mallet, or the"
      + " crescents of an axe can rest atop while the thinner main"
      + " length of the weapon can hang down between.\n");
    add_item( ({ "west wall", "west", "western wall",
                 "wall to the west", "entire length",
                 "length of the west wall",
                 "entire length of the west wall" }),
        "The west wall has been configured to serve as a complete weapon"
      + " rack.\n");
    add_item( ({ "contents" }),
        "You can just <exa rack> to see them.\n");
} /* create_rack */


/*
 * Function:    format_list_item_row
 * Description: Given the item information, it prints out a formatted
 *              row including whatever information it needs for the
 *              columns. It should match the number of columns that are
 *              printed in format_header_and_footer.
 *              The last argument "obj" can be used to glean more info
 *              to be printed.
 */
public string
format_list_item_row(string short_desc, int count, int recoverable, object obj)
{
    string row_content, prepend_text, weapon_type;
    
    if (recoverable == 1)
    {
        prepend_text = "+ ";
    }
    else
    {
        prepend_text = "  ";
    }
    
    switch (obj->query_wt())
    {
    case W_SWORD:
        weapon_type = "sword";
        break;
    case W_POLEARM:
        weapon_type = "polearm";
        break;
    case W_AXE:
        weapon_type = "axe";
        break;
    case W_KNIFE:
        weapon_type = "knife";
        break;
    case W_CLUB:
        weapon_type = "club";
        break;
    case W_MISSILE:
        weapon_type = "missile";
        break;
    case W_JAVELIN:
        weapon_type = "javelin";
        break;
    default:        
        weapon_type = "unknown";
    }
    
    return sprintf("|  %-50s | %|10s | %5d  |\n", 
                            prepend_text + short_desc, 
                            weapon_type, count);
}

/*
 * Function:    format_header_and_footer
 * Description: This prints the header and the footer that surrounds
 *              the item rows. It should match the number of columns that
 *              are printed in format_list_item_row.
 */
public string
format_header_and_footer(string contents)
{
    return  "\nYou take some time to assess which weapons are currently"
             + " stocked:\n\n"
             + sprintf("%54s-%12s-%8s\n"
               ," .----------------------------------------------------."
               ,"-----------."
               ,"------. ")
             + sprintf("|   %-49s | %|10s | %5s  |\n", 
                       "Description", "Type", "Qty") 
             + sprintf("%-54s-%12s-%6s\n"
               ," >----------------------------------------------------+"
               ,"-----------+"
               ,"------< ") + contents
             + sprintf("%54s-%12s-%8s\n"
               ," `----------------------------------------------------^"
               ,"-----------^"
               ,"------' ")
             + "\n + Indicates a lasting item\n";               
} /* format_header_and_footer */


/*
 * Function:    hook_prepend_describe_contents
 * Description: Allows one to customize the text that goes above the
 *              listing of the contents in the rack object.
 */
public void
hook_prepend_describe_contents(object for_obj, object * obarr)
{
    string name = query_name();
    if (sizeof(obarr))
    {
        for_obj->catch_tell(
            "==========================================================="
          + "=====================\n"
          + " ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~  Current Contents  ~*~*~*~*~"
          + "*~*~*~*~*~*~*~*~*~*~ \n"
          + "==========================================================="
          + "=====================\n");
    }
} /* hook_prepend_describe_contents */


/*
 * Function:    hook_append_describe_contents
 * Description: Allows one to customize the text that goes after the
 *              listing of the contents in the rack object.
 */
public void
hook_append_describe_contents(object for_obj, object * obarr)
{
    string name = query_name();
    if (sizeof(obarr))
    {
        for_obj->catch_tell(
            "==========================================================="
          + "=====================\n"
          + " ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
          + "*~*~*~*~*~*~*~*~*~*~* \n"
          + "==========================================================="
          + "=====================\n\n"
          + "                         ----> [Commands for Use] <----\n\n"
          + "   <list rack>         - An organized display of the curre"
          + "ntly stocked items\n"
          + "   <list [weapontype]> - Displays only items of the specifi"
          + "d type in stock\n"
          + "   <kick rack>         - Send all non-lasting items tumbling"
          + " to the floor\n");
    }
} /* hook_append_describe_contents */


/*
 * Function:    do_kick
 * Description: Function that separates out the non-saving items from the
 *              rack. This is useful for during armageddon.
 */
public int
do_kick(string arg)
{
    mixed matches;
    object * nonglowing;
    object rack;
    
    if (parse_command(arg, all_inventory(environment(this_player())),
                      "[the] %i", matches))
    {
        if (matches[0] == 1 && matches[1] == this_object())
        {
            rack = this_object();
        }
    }

    if (!objectp(rack))
    {
        notify_fail(capitalize(query_verb()) + " what? The " + short() 
            + "? <" + query_verb() + " " + short() + ">\n");
        return 0;
    }
    
    nonglowing = filter(all_inventory(), &operator(==)(0) @ &->check_recoverable());
    if (!sizeof(nonglowing))
    {
        write("You " + query_verb() + " the west wall with all of"
          + " your might, but nothing falls.\n");
        return 1;
    }
    
    nonglowing->move(environment());

    write("You " + query_verb() + " the west wall with all of your"
      + " might! "
        + capitalize(COMPOSITE_ALL_DEAD(nonglowing)) + " tumble to"
        + " the floor.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
        + " " + query_verb() + "s the west wall with all of "
        + this_player()->query_possessive() + " might! "
        + capitalize(COMPOSITE_ALL_DEAD(nonglowing)) + " tumble to"
        + " the floor.\n", this_player());
    return 1;
} /* do_kick */
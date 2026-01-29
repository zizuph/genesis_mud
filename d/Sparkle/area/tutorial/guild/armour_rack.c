/*
 *  /d/Sparkle/area/tutorial/guild/armour_rack.c
 *
 *  This is the standard armour rack used in the Tutorial Guild in Sparkle.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Genesis/specials/guilds/objs/armour_rack";


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
    remove_name("rack");
    set_name("stand");
    add_adj( ({ "armour", "armor" }) );
    set_short("armour stand");
    set_long("\nThe armour stand in this room looks big enough to suit"
      + " the needs of the entire guild.\n\n");
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
    string row_content, prepend_text;
    
    if (recoverable == 1)
    {
        prepend_text = "+ ";
    }
    else
    {
        prepend_text = "  ";
    }
    
    return "\t" + sprintf("|  %-50s | %5d  |\n", prepend_text + short_desc, 
                        count);

} /* format_list_item_row */


/*
 * Function:    format_header_and_footer
 * Description: This prints the header and the footer that surrounds
 *              the item rows. It should match the number of columns that
 *              are printed in format_list_item_row.
 */
public string
format_header_and_footer(string contents)
{
    return  "\nYou take a moment to assess which armours are currently"
             + " stocked: \n\n"
             + "\t" + sprintf("%-54s-%8s\n"
               ," .----------------------------------------------------."
               ,"------. ")
             + "\t" + sprintf("|   %-49s | %5s  |\n", "Description", "Qty") 
             + "\t" + sprintf("%-54s-%6s\n"
               ," >----------------------------------------------------+"
               ,"------< ") + contents
             + "\t" + sprintf("%-54s-%8s\n"
               ," `----------------------------------------------------^"
               ,"------' ")
             + "\n\t + Indicates a lasting item\n";               
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
          + "       <list stand> - An organized display of the curre"
          + "ntly stocked items\n"
          + "       <kick stand> - Send all non-lasting items tumbling"
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
        write("You " + query_verb() + " the armour stand with all of"
          + " your might, but nothing falls.\n");
        return 1;
    }
    
    nonglowing->move(environment());

    write("You " + query_verb() + " the armour stand with all of your"
      + " might! "
        + capitalize(COMPOSITE_ALL_DEAD(nonglowing)) + " tumble to"
        + " the floor.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
        + " " + query_verb() + "s the armour stand with all of "
        + this_player()->query_possessive() + " might! "
        + capitalize(COMPOSITE_ALL_DEAD(nonglowing)) + " tumble to"
        + " the floor.\n", this_player());
    return 1;
} /* do_kick */
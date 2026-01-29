/*
 * /w/aeg/gnome/obj/chronometer.c
 *
 * A *brilliant* gnomish chronometer to show the local time.
 *
 * Created March 2008, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#define TP  this_player()


/*prototypes*/
public void             create_object();
public int              read_time(string thetime);
public int              wind_watch(string watch);
public string           add_item_long(string item);
public string           get_default_desc(string item);
public string           get_gnome_desc(string item);

/*
 * Function name:       create_object
 * Description  :       creates the object.
 */
public void
create_object()
{
    set_name("chronometer");
    add_name("watch");
    set_adj( ({"small", "gnomish"}) );
    set_long(&add_item_long("long_desc"));
    
} /* create_object */


/* Function name:       init
 * Description  :       adds the action
 */
public void
init()
{
    ::init();
    
    add_action("read_time", "read");
    add_action("wind_watch", "wind");
    
} /* init */


/*
 * Function name:       read_time()
 * Description  :       allows the player to read the time.
 */
public int
read_time(string thetime)
{
    if (thetime == "time")
    {
        write("The chronometer reads: " + ctime(time()) + ".\n");
        say("" + QTNAME(TP) + " inspects " + TP->query_possessive() 
            + " small gnomish chronometer.\n");
        return 1;
    }
    
    return 0;
} /* read_time */


/*
 * Function name:       wind_watch()
 * Description  :       allows the player to wind the watch.
 */
public int
wind_watch(string watch)
{
    if (watch == "dial")
    {
        write("You turn the dial on the chronometer, which gives it "
            + "continued life.\n");
        say("" + QTNAME(TP) + " winds the dial on " + TP->query_possessive() 
            + " small gnomish chronometer.\n");
        return 1;
    }
    
    notify_fail("Wind what?\n");
    return 0;
           
} /* wind_watch */

/*
 * Function name:       add_item_long()
 * Description  :       queries the race name of this_player and routes
 *                      the long description appropriately. 
 */
public string
add_item_long(string item)
{
    string race;
    string description;
    
    race = this_player()->query_race_name();
    switch (race)
    {
    case "gnome":
        description = get_gnome_desc(item);
        break;

    default:
        description = get_default_desc(item);
    }
    
    return description;
} /* add_item_long */


/*
 * Function name:       get_gnome_desc()
 * Decription   :       sets and shows the description of the watch
 *                      for gnomes.
 */
public string
get_gnome_desc(string item)
{
    string description;
    
    description = 
        "This device immensely useful! You could <read "
      + "time> at any moment to determine the time! You must wind the dial "
      + "on the chronometer to keep it running. How brilliant of an "
      + "invention! Why didn't someone think of this sooner? The world "
      + "will now work in sync! Everything will happen on time! "
      + "You will never be late! Gnomes are the most brilliant race!\n";
               
    return description;
} /* get_gnome_desc */


/*
 * Function name:       get_default_desc()
 * Decription   :       sets and shows the description of the watch
 *                      for non-gnomes.
 */
public string
get_default_desc(string item)
{
    string description;
    
    description =
        "This gnomish device is a chronometer. It appears to show the "
      + "local time. One might be able to <read time>. It might be helpful "
      + "to keep the chronometer working, by winding the dial.\n";
            
    return description;
    
} /* get_default_desc */


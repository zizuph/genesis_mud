/*
 * riel room object - removes the room benefit after a set      
 * period of time.
 *
 * Arman Kharas, Feb2018
 */

#include <files.h>
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "../../herald.h"

inherit "/std/object";

int destruct;

// This function needs to add remove_herb_file once the 

public void
remove_riel(string herb_file)
{
    setuid();
    seteuid(getuid());

    object room = environment(this_object());
    string * herbs_in_room = room->query_herb_files();

    tell_room(room, "You feel the area around you seems to lose a " +
        "bit of vitality and lustre.\n");

    if (IN_ARRAY(herb_file, herbs_in_room))
    {
        room->remove_herb_file(herb_file);
    }

    remove_object();
}

public int
query_remove_riel()
{
    return destruct;
}

public void
set_remove_riel(int herb_value, object herb)
{
    // one day is 86400 'beats'. Default removal is 10 days
    // for a herb with a value of 10 copper.
    //
    // A herb of 1 platinum value would be removed within
    // 84 minutes.

    if(herb_value < 10)
        herb_value = 10;

    destruct = 8640000 / herb_value;
    string herb_file = MASTER_OB(herb);

    set_alarm(itof(destruct), 0.0, &remove_riel(herb_file));
}

/* 
 * Function:    create_object
 * Description: Standard object creation function. Set to nomask, but
 *              can override defaults using create_spell_object
 */
public nomask void
create_object()
{
    set_name("_riel_base_spell_obj");
    add_name( ({"riel_base_spell_obj" }) );
    set_short("hidden riel base spell object");    
    set_long("A basic spell object. One should not be able to see it "
           + "in their inventory.\n");
    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);                          
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GET, 1); 
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    
    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    setuid();
    seteuid(getuid());

}
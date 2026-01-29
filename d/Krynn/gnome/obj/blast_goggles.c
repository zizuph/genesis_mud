/*
 * /d/Krynn/gnome/obj/blast_goggles.c
 * 
 * These blast goggles are needed for gnomes to protect their
 * eyes from the explosions that seem to happen in their presence.
 * 
 *  Aeg 2008: created
 *  Aeg 2021: updated with new features
 */

#pragma strict_types
 
inherit "/std/armour";
 
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

/* prototypes */
public void             create_armour();
public int              do_read(string str);
public int              adjust(string str);

/*
 * Function name:       create_armour
 * Description  :       Creates the armour.
 */
public void
create_armour()
{
    set_name("goggles");
    add_name( ({"blast_goggles"}) );
    set_short("pair of gnomish blast goggles");
    set_adj( ({"gnomish", "blast"}) );
    add_item("label", "@@read");
    set_long("This set of goggles, much like other goggles, is made "
        + "to be worn over the eyes. Gnomes use these goggles for "
        + "protection from projectiles and large blasts of light. They "
        + "also use these goggles to minimize the necessary "
        + "blinks per minute of the wearer. No sane gnome would tolerate "
        + "falling victim to a rogue speck of airborne dust and miss that "
        + "vital bit of knowledge from experiments. " 
        + "They are circular and have rubber pads on the inside to "
        + "form a seal on the face. The lenses are transpartent with a rich "
        + "orange tint.  They are caked with soot, but it "
        + "looks as if someone has wiped them clean enough to be "
        + "functional. A small label has been attached to the strap.\n");
    set_ac(0);
    set_at(A_EYES);
    set_layers(0);
    set_looseness(5);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 5);
    
    seteuid(getuid());
    
} /* create armour */ 

/* Function name:       init
 * Description  :       adds the action
 */
public void
init()
{
    ::init();
    add_action("do_read", "read");
    add_action("adjust", "adjust");
    add_action("do_wipe", "wipe");
}

public int
do_wipe(string str)
{
    if (str == "goggles" || str == "glasses")
    {
        if (!query_worn())
        {
            write("You must wear the goggles to do this.\n");
            return 1;
        }
        write("You wipe some grime from the lenses of your "
            + "blast goggles.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " wipes some grime off of the lenses of " 
          + this_player()->query_possessive() + " blast goggles.\n",
          this_player());
        return 1;
        }
    
    notify_fail("Wipe what?\n");
    return 0;
}

public int
adjust(string str)
{
    if (str == "goggles" || str == "glasses")
    {
        if (!query_worn())
        {
            write("You must wear the goggles to do this.\n");
            return 1;
        }
        write("You adjust your blast goggles. Ah! That's better.\n");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " adjusts " 
          + this_player()->query_possessive() + " blast goggles.\n",
          this_player());
        return 1;
        }
    
    notify_fail("Adjust what?\n");
    return 0;
}


public int 
do_read(string str)
{
    if (str == "label" || str == "label on goggles")
    {
        write("The label reads: Product of Gnomish Industries.\n" 
        +  "Users may <adjust> and <wipe> these goggles.\n");
    return 1;      
    }
    notify_fail("Read what?\n");
    return 0;    
}

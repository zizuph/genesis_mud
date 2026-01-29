/*
 * This wand teleports the wielder somewhere. It is the base wand
 * functionality that can be used by inheriting it.
 * 
 * Made into Base Wand by Petros, March 2009
 */
 
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

#define CROOM "/d/Ansalon/balifor/flotsam_forest/coastline/"

// Global Variables
public int charge = 0;

public string
query_teleport_destination()
{
    return CROOM + "road15";
}

public void
reset_short_desc()
{
    if (query_adjs())
    {
        remove_adj(query_adjs());
    }
    
    set_short(0);
    if (charge == 0)
    {
        add_adj("shiny");
    }
    else
    {
        add_adj("dull");
    }
}

public void
create_wand()
{
    // Mask this function to customize the wand.
}

public nomask void
create_object()
{
    set_name("wand");
    reset_short_desc();
    set_long("This " + short() + " is made of " +
      "some sort of blue wood. Along its shaft there is some " +
      "writing.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 3500);
    add_prop(MAGIC_AM_MAGIC,({25,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({ "This is a wand of teleportation. This particular type "
       + "generally has a preset destination.\n", 10,
         "This type of wand usually has only one charge.\n", 20,
         "The wand also provides the holder with some enhancement " +
         "to their magical spellpower.\n", 30,
         "With the right knowledge and magical ability, it may "
       + "be recharged.\n", 40,
         "One can recharge the wand by researching the Manual of "
       + "the Magi in the Palanthas Library.\n", 60,
         "The way to recharge the wand is by chanting "
       + "'raficulsander'.\n", 95 }));

    add_item( ({ "writing", "shaft" }), 
        "It looks like you can read the writing on the shaft of the wand.\n");
        
    set_slots(W_ANYH);
    set_magic_spellpower(30);

    add_cmd_item("wand","wave","@@wave_wand");
    add_cmd_item(({"wand","shaft","writing"}),"read",
      "@@read_writing");
    add_cmd_item("raficulsander","chant","@@recharge");

    //Enable default item expiration
    set_item_expiration();
    
    // Call the create_wand function for customization purposes
    create_wand();
}

string
wave_wand()
{
    if(!TO->query_held())
    {
        write("You have to be holding the wand to wave it.\n");
        return "";
    }
  
    // added by Torqual so players cannot run away using wand
    if (TP->query_attack() || !TP->query_relaxed_from_combat())
    {
        write("You wave the wand around, but nothing happens.\n");
        return "";
    }

	
	// Added so the wand don't work in areas locked for teleporting.
	if ((environment(TP)->query_prop(ROOM_I_NO_TELEPORT)) || 
		(environment(TP)->query_prop(ROOM_M_NO_TELEPORT)) ||
		(environment(TP)->query_prop(ROOM_M_NO_TELEPORT_FROM)))
	{
		write("You wave the wand around, but nothing special happens.\n");
		return "";
	}
    
    if(charge == 1)
    {
        write("You wave the " + short() + " around, but nothing happens.\n");
        say(QCTNAME(TP) + " waves the " + short() + " around and " +
          "makes some silly gestures. Not surprisingly, nothing " +
          "happens.\n");
        return "";
    }
    else
    {
        if (MASTER_OB(environment(TP)) == query_teleport_destination())
        {
            write("You wave the " + short() + " around, but nothing "
                + "happens.\n");
            say(QCTNAME(TP) + " waves the " + short() + " around and " +
              "makes some silly gestures. Not surprisingly, nothing " +
              "happens.\n");
        }
        else
        {            
            write("You wave the " + short() + ", and suddenly you find " +
              "yourself somewhere else!\n");
            say(QCTNAME(TP) + " waves the " + short() + " and suddenly " +
              "disappears in a blinding flash of light!\n");
            tell_room(query_teleport_destination(), QCTNAME(TP) +
              " suddenly appears in a blinding flash of light!\n");
            TP->move_living("X", query_teleport_destination(), 1, 0);
        }
        charge = 1;
        reset_short_desc();
        return "";
    }
}

string
read_writing()
{
    return "This is a wand of teleportation. Wave it, " +
    "and you will be taken to a preset destination. " +
    "Warning! Use it with caution, as it is a one way " +
    "trip. Further information on such magical travelling " +
    "devices can be found in 'Manual of the Magi. Volume " +
    "436ii'.\n";
}

string
recharge()
{
    if(!TO->query_held())
    {
    write("You can only recharge it if you are holding it.\n");
    return "";
    }

    if(TP->query_skill(SS_SPELLCRAFT) < 40)
    {
    write("You do not have the magical skill or knowledge " +
      "to be able to recharge this wand.\n");
    return "";
    }
    if(charge == 0)
    {
    write("You raise the wand above your head and chant the " +
      "mystical words 'Rafi cul san der'!\nNothing seems " +
      "to happen.\n");
    say(QCTNAME(TP) + " raises a wand above " + POSSESSIVE(TP) +
      " head and begins " +
      "chanting the spidery words of magic.\n");
    return "";
    }
    else
    {
    write("You raise the wand above your head and chant " +
      "the mystical words 'Rafi cul san der'!\nThe wand pulses " +
      "briefly with a blue light as you feel your own energies " +
      "being drawn into the wand.\nYou feel somewhat drained.\n");

    say(QCTNAME(TP) + " raises a wand above " + POSSESSIVE(TP) +
      " head and begins chanting the spidery words of magic.\n" +
      "The wand pulses briefly with a blue light.\n");

    charge = 0;
    reset_short_desc();
    TP->add_mana(-random(50) - 100);
    return "";
    }
}

void
set_charge(int number)
{
    charge = number;
    reset_short_desc();
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}
 
void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    ::init_keep_recover(arg);
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
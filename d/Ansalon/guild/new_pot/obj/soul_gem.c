/*
 * Ashlar, 6 Sep 97
 *
 * A gem that allows a priest to capture the soul of a dying enemy
 * and store it to use in spells as a mana-reducing component.
 *
 * Updated 13 May 98 - The new holdable item thingy fits this like
 *                     the proverbial glove, so lets make it a such.
 *
 * Changed max charges to 75.
 *
 * Dec 2022 - increased rate of soul absorption, due to slower kill rate
 *            due to global decrease in damage. Zizuph
 *
 */

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "../guild.h"

#define ONE_CHARGE 100

string *adj = ({ "dull", "flickering", "glimmering", "glittering", "shining", 
                 "gleaming", "glowing", "dazzling", "brilliant", "blazing" });

string colour;
string pot_name;
int charge, maxcharge, owner_level, soul_num;
object pot_owner;

public void
set_priest_level(object caster, int level)
{
   pot_owner = caster;
   pot_name = caster->query_real_name();
   owner_level = level;
   maxcharge = ((ONE_CHARGE * owner_level) +
                max(0, pot_owner->query_skill(PS_STANDING)) * 5);

   // level 11 spell, maxcharge between 1100-1500 (level) + 6000 (standing)
   // DEBUG("soul_gem set_priest_level set: " +level+ ", maxcharge: " +maxcharge+ 
   //       "priest name: " +pot_name+ ".");
}  

void
set_up_gem()
{
    int i;
    remove_adj(adj);
    if (charge == 0)
    {
        add_adj("inert");

        set_short("inert " + (stringp(colour) ? colour + " " : "") +
        "soul gem");
        soul_num = 0;
        return;
    }
    if (maxcharge < 0)
        maxcharge = 0;
    i = (sizeof(adj) * charge) / (maxcharge + 1);
    if (i > 9)
        i = 9;
    add_adj(adj[i]);
    set_short(adj[i] + " " + (stringp(colour) ? colour + " " : "") +
    "soul gem");
}

string
query_priest_name()
{
    return pot_name;
}

void
set_priest_name(string name)
{
    pot_name = name;
}

string
query_colour()
{
    return colour;
}

void
set_colour(string c)
{
    if (stringp(colour))
        remove_adj(colour);
    colour = c;
    add_adj(colour);
    set_up_gem();
}

int
query_souls()
{
    return soul_num;
}

void
set_souls(int i)
{
   soul_num = i;
}

void
create_object()
{
    set_name("gem");
    add_name("soulgem");
    add_name("_ansalon_soul_gem");
    set_adj("soul");

    set_long("It is a small gem, finely cut. The inside is strangely " +
    "opaque. You recognize this as a soul gem, used to trap the souls " +
    "of unsuspecting victims. @@soul_desc@@\n");

    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This is a soul gem, used in some dark arts to capture the " +
        "souls of enemies.\n", 10,
        "In order to use this properly, the gem must be held in either " +
        "hand when killing the target.\n", 20 }));

    add_prop(OBJ_S_WIZINFO,
        "This object is used by the Priests of Takhisis to capture " +
        "souls of enemies and use them in their magic.\n");

    charge = 0;

    set_slots(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_I_VALUE, 1500);

    set_colour("chromatic");
    set_up_gem();

    set_keep(1);
}

string
soul_desc()
{
   string str;

   switch(soul_num)
   {
     case 0:
       str = "The gem looks like it is currently empty of souls.";
       break;
     case 1:
       str = "The gem looks like it contains a single soul.";
       break;
     case 2..11:
       str = "The gem looks like it contains a few souls.";
       break;
     case 12..15:
       str = "The gem looks like it contains a score of souls.";
       break;
     case 16..50:
       str = "The gem looks like it contains many souls.";
       break;
     case 51..99:
       str = "The gem looks crowded with many souls.";
       break;
     case 100..999:
       str = "The gem contains hundreds of tormented souls.";
       break;
     case 1000..9990:
       str = "The gem contains thousands of tormented souls!";
       break;
     case 10000..99900:
       str = "The gem contains tens of thousands of tormented souls!";
       break;
     default:
       str = "";
     break;
    }

    return str;
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    /* This needs to be called from leave_env() so that items are
     * released when they are dropped.
     */
    holdable_item_leave_env(env, to);
}

int
query_charge()
{
    return charge;
}

int
query_max_charge()
{
    return maxcharge;
}

int
add_charge(int c)
{
    charge += c;
    if (charge > maxcharge)
    {
        charge = maxcharge;
        
        if (objectp(query_holder()))
            query_holder()->catch_msg("The " + short() + " is bursting with " +
            "energy, unable to contain any more souls.\n");
        return 0;
    }
    if (charge < 0)
        charge = 0;

    if ((c < 0) && (charge < ONE_CHARGE))
    {
        maxcharge -= 5;
    }

    if (c < 0)
        soul_num = max(0, soul_num - 1);
        // DEBUG("soul_gem new soul number: " +soul_num+ ".");        
    set_up_gem();
    return 1;
}

int
trap_soul(object victim)
{
    if (victim->query_prop(LIVE_I_UNDEAD))
        return 0;

    soul_num = soul_num + 1; 
       // DEBUG("soul_gem new soul number: " +soul_num+ ".");       
    if (add_charge(victim->query_average_stat() * 6))
        return 1;
    
    return 0;
}

string
query_recover()
{
    return MASTER + ":" + colour + "&&" +
    charge + "," + maxcharge + "," +soul_num+ "," + pot_name;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");

    colour = a[0];
    add_adj(colour);
    sscanf(a[1],"%d,%d,%d,%s",charge,maxcharge,soul_num,pot_name);
    set_up_gem();
}

/*
 * Function name: appraise_object
 * Description:   This is called when someone appraises this item.
 *                We want to mask it to add a message telling the
 *                appraiser that the item can be held.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    write(holdable_item_usage_desc());
}



varargs public int
move(mixed dest, mixed subloc)
{
    if (MASTER_OB(dest) == "/d/Sparkle/clubs/rmc/obj/player_purse")
        return 7;
    
    return ::move(dest, subloc);
}
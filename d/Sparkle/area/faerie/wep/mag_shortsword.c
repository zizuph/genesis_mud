/*
 * Based on the Elfblade by Morinir from the Shire in 1996
 * By Finwe, April 2005
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#include "../defs.h"

string long_func();

#define HIT 20
#define PEN 35

#define DEBUG_WHO find_player("igneous")

#undef DEBUG_WHO
#ifdef DEBUG_WHO
#define DEBUG(s)  DEBUG_WHO->catch_msg(s + "\n")
#else
#define DEBUG(s)
#endif


void
create_weapon()
{
    set_name("sword");
    add_name(({"shortsword"}));
    add_adj("glowing");
    add_adj("mithral");
    set_short("glowing mithral shortsword");
    set_long("@@long_func@@");

    set_hit(HIT);
    set_pen(PEN);
    set_likely_dull(4);
    set_likely_corr(1);
    set_likely_break(1);

    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,400);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN)+random(200));
    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_ID_INFO,({"This shortsword appears magical.",1,
	"The sword feels warm in your grasp.",20,
	"The sword is an ancient heirloom of the elves of Faerie",40,
	"The sword will glow when enemies are close by.",50}));

    add_prop(OBJ_S_WIZINFO,"The "+short()+" will gleam faintly if player is " +
      " 1 room from an orc or goblin and shine brightly if the player"+
      " is in the same room as a goblin or an orc.\n"+
      "Besides this the sword will only act as a 10/10 weapon in the"+
      " hands of any player > adventure. It will.\n"); 
    
    add_item(({"runes","elven runes"}),"The runes seem to mark some sort"+
      " of enchantment laid upon the blade.\n");

    set_wf(TO);
    set_keep();
}

mixed
wield(object wep)
{
//    if(this_player()->query_average_stat() > NEWBIE_MAX) 
    {
	    TO->set_hit(10);
	    TO->set_pen(10);
	    write("The sword feels heavy in your hand");
    }
//    else 
    {
	    TO->set_hit(HIT);
	    TO->set_pen(PEN);
	    write("You wield the "+short()+".\n");
    }

    tell_room(ENV(TP),QCTNAME(TP)+" wields the "+short()+".\n",TP);

    return 1;
}

mixed
unwield(object wep)
{
//    if (IS_NEWBIE)  
    {
	    TO->set_hit(HIT);
	    TO->set_pen(PEN);
	
    }
//    else 
    {
	    write("You unwield the "+short()+".\n");
    }   

    tell_room(ENV(TP),QCTNAME(TP)+" unwields the "+short()+".\n",TP);

    return 1;
}


int
find_bad_races(mixed where)
{
    object *livings = ({}), *baddies = ({}), room;

    setuid(); seteuid(getuid());
    if (stringp(where))
    {
	    room = find_object(where);
	    if (!objectp(room))
	        catch(call_other(where, "??"));
	    if (!objectp(room = find_object(where)))
	        return 0;
    }

    if (objectp(where))
	    room = where;
    if (!objectp(room) || !room->query_prop(ROOM_I_IS))
	    return 0;

    DEBUG("Searching "+file_name(room));
    // Now we Search :)
    livings = FILTER_LIVE(all_inventory(room));
    if (!sizeof(livings))
	    return 0;

    DEBUG("Filtering "+COMPOSITE_LIVE(livings));
    baddies += FILTER_RACE(livings, "orc");
    baddies += FILTER_RACE(livings, "goblin");
    baddies += FILTER_RACE(livings, "uruk");

    DEBUG("Returning "+(sizeof(baddies) ? COMPOSITE_LIVE(baddies) : "nothing"));
    if (!sizeof(baddies))
	    return 0;

    return 1;    
}

string
long_func()
{
    string desc;
    object player = query_wielded();

    if (!objectp(player))
	    player = TP;

    desc="This short sword is marvelously light. The extremely sharp blade is made from some sort of brightly polished metal, but it seems lighter than an ordinary steel shortsword. Flowing elven runes are etched into the blade.\n";
    if (!living(player))
        return desc;

    if (find_bad_races(ENV(player)) || 
      sizeof(filter(ENV(player)->query_exit_rooms(), find_bad_races)))
	desc += "The edges of the "+short()+" are shining brightly.\n";

    return desc;
}

/*
 * Longsword used by Tom Bombadill
 * Based on the longsword used by Elrond in Rivendell
 * By Finwe, January 2002
 */
inherit "/std/weapon";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <filter_funs.h>
#include <composite.h>
#include <options.h>


string long_func();

#define DEBUG_WHO find_player("finwe")

#undef DEBUG_WHO
#ifdef DEBUG_WHO
#define DEBUG(s)  DEBUG_WHO->catch_msg(s + "\n")
#else
#define DEBUG(s)
#endif


/*prototype*/

void
create_weapon()
{
    set_name(({"sword", "shortsword","short sword"}));
    set_pname(({"swords", "shortswords", "short swords"}));
    set_adj(({"ancient", "runed"}));
    set_short("ancient runed short sword");
    set_long("@@long_func@@");

    add_item(({"engravings", "flowing engravings"}),
        "The flowing engravings  run the length of the blade. " +
        "They are flowing, like waves of an ocean. Within the " +
        "etchings are runes.\n");
    add_item(({"runes", "ancient runes",  "intricate runes"}),
        "The runes are ancient characters used by people in ages " +
        "long past. They are etched in the engravings on the blade.\n");

    set_default_weapon(45,40, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    set_wf(TO);

    add_prop(OBJ_S_WIZINFO,
      "This sword is used Tom Bombadill. " +
      "It has no magical properties other than the ability " +
      "to sense alignment of npcs and increased hit/pen " +
      "abilities. Additionally, if a evil aligned player " +
      "tries to wield it, they will be severely injured and " +
      "forced to drop the sword.\n");

    add_prop(MAGIC_AM_ID_INFO,
      ({"This sword shines with power", 20,
	"A strong power has been imbued into the weapon, " +
	"enhancing the wielder's senses", 40,
	"This sword was forged by men in ages past. " +
	"It enables the wielder to sense when evil things " +
	"are nearby.", 60}));

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,40)); /* magic sword */ 

}

// mixed
// check_align(object what)
mixed 
wield(object weapon)
{

    /*
     * Checks alignment. if evil, player cant wield blade
     */
    if (TP->query_alignment() > -150 && 
      TP->query_race_name() !="goblin")
    {
	write("You wield the "+short()+" and prepare " +
	  "to defend yourself.\n");
	TP->say(QCTNAME(TP) + " wields an "+short()+".\n");
	return 1;
    }
    tell_room(ENV(TP),QCTNAME(TP)+" screams in pain and drops " +
        "an "+short()+". The sword clatters as it hits " +
        "the ground!\n", ({TP}));
    // Move the weapon to the wielders environment
    move(ENV(TP), 1);
    return "You scream in pain as a searing flash of pain " +
        "runs up your arm. You drop the "+short()+"!\n";
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
    desc="This "+short()+" is marvelously light. The extremely sharp " +
        "blade is made of ancient steel but it seems lighter than " +
        "an ordinary steel short sword. Flowing engravings are etched " +
        "onto the blade.\n";

    if (find_bad_races(ENV(player)) || 
      sizeof(filter(ENV(player)->query_exit_rooms(), find_bad_races)))
	desc += "The edges of the "+short()+" are shining brightly.\n";

    return desc;
}

mixed
unwield(object what)
{
    return 0;
}

public mixed 
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object wielder = query_wielded();
 
    switch(phurt)
    {
    case -1:
    case -2:
//        if (!wielder->query_option(OPT_GAG_MISSES))
            wielder->catch_msg("You lunge for "+QTNAME(enemy)+
            " but miss.\n");
//        if (!enemy->query_option(OPT_GAG_MISSES))
        enemy->catch_msg(QCTNAME(wielder)+" lunges for "+
            "you with " +HIS_HER(wielder)+" "+ short()+
            " but misses.\n");
        wielder->say(QCTNAME(wielder)+" lunges for "+
        QTNAME(enemy)+" but misses.\n",enemy);
        break;
    case 0:
        if (!wielder->query_option(OPT_GAG_MISSES))
            wielder->catch_msg("You barely miss "+QTNAME(enemy)+
              " with your "+short()+".\n");
        if (!enemy->query_option(OPT_GAG_MISSES))
            enemy->catch_msg(QCTNAME(wielder)+" barely misses you "+ 
              "with the "+short()+".\n");
        wielder->say(QCTNAME(wielder)+" swings the "+short()+
          " at "+QTNAME(enemy)+" and barely misses.\n",enemy);
        break;
    case 1..5:
        wielder->catch_msg("You rip open a shallow wound into the "+
          hdesc+" of the "+enemy->query_race_name()+" with "+
          "the "+short()+".\n");
        enemy->catch_msg("You feel a fresh wound open on your "+hdesc+
          " as the "+short()+" tears into you.\n");
        wielder->say(QCTNAME(wielder)+" rips open a "+
          "shallow wound into the "+hdesc+" of "+QTNAME(enemy)+ 
          " with the "+short()+".\n",enemy);
        break;
    case 6..10:
        wielder->catch_msg("You hack chunks of flesh out "+
          "of the "+hdesc+" of the "+enemy->query_race_name()+
          " with the "+short()+".\n");
        enemy->catch_msg("You lose small chunks of flesh as the "+short()+
          " hacks into your "+hdesc+".\n");
        wielder->say(QCTNAME(wielder)+" hacks small chunks of "+
          "flesh out of the "+hdesc+" of "+QTNAME(enemy)+" with the "+
          short()+".\n",enemy);
        break;
    case 11..20:
        wielder->catch_msg("Your "+short()+" rips into the "+hdesc+
          " of "+QTNAME(enemy)+", shredding flesh as it goes.\n");
        enemy->catch_msg("The flesh of your "+hdesc+" is shredded as the "+
          short()+" rips into it.\n");
        wielder->say(QCTNAME(wielder)+" shreds the flesh on "+
          "the "+hdesc+" of "+QTNAME(enemy)+" with "+
          HIS_HER(wielder)+" "+short()+".\n",enemy);
        break;
    case 21..40:
        wielder->catch_msg("Your "+short()+" tears a deep wound "+
          "into the "+hdesc+" of the "+enemy->query_race_name()+".\n");
        enemy->catch_msg(QCTNAME(wielder)+" tears a deep "+
          "wound into your "+hdesc+" with "+HIS_HER(wielder)+
          " "+short()+".\n");
        wielder->say(QCTNAME(wielder)+" tears a deep wound into "+
          "the "+hdesc+" of "+QTNAME(enemy)+" with the "+short()+
          ".\n",enemy);
        break;
    case 41..60:
        wielder->catch_msg("Your "+short()+" shreds large "+
          "chunks of flesh from the "+hdesc+" of the "+
          enemy->query_race_name()+".\n");
        enemy->catch_msg(QCTNAME(wielder)+" shreds large chunks of "+
          "flesh from your "+hdesc+" with "+HIS_HER(wielder)+
          " "+short()+".\n");
        wielder->say(QCTNAME(wielder)+" shreds large chunks of "+
          "flesh from the "+hdesc+" of "+QTNAME(enemy)+" with the "+
          short()+".\n",enemy);
        break;
    case 61..80:
        wielder->catch_msg("You plunge your "+short()+" into "+
          "the "+hdesc+" of the "+enemy->query_race_name()+". " +
          "Blood sprays all over you.\n");
        enemy->catch_msg(QCTNAME(wielder)+" plunges "+HIS_HER(wielder)+
            short()+"into your "+hdesc+". "+HE_SHE(wielder)+" pulls out "+
            HIS_HER(wielder)+short()+ " and gets sprayed by blood.\n");
        wielder->say(QCTNAME(wielder)+" plunges "+
            HIS_HER(wielder)+short()+"into into the "+hdesc+" of the"+ 
            enemy->query_race_name()+". "+HE_SHE(wielder)+" pulls out "+
            HIS_HER(wielder)+short()+ " and gets sprayed by blood.\n");
        break;
    case 81..90:
        wielder->catch_msg("Your "+short()+" almost severs the "+
            hdesc+" of the "+enemy->query_race_name()+". Blood " +
            "sprays everywhere.\n");
        enemy->catch_msg("The "+short()+" almost severs your "+hdesc+
            ". Your blood sprays everywhere.\n");
        wielder->say(QTNAME(wielder)+"'s "+short()+
            " almost severed "+QTNAME(enemy)+"'s "+hdesc+". " +
            "Blood sprays all over from the wound.\n");
        break;

    default:
        wielder->catch_msg("You dive for the "+hdesc+" of the "+
            enemy->query_race_name()+ " but miss, barely scratching "+
            HIM_HER(enemy)+".\n");
        enemy->catch_msg(QCTNAME(wielder)+" dives for your "+hdesc+
            " but misses, barely scratching you.\n");
        wielder->say(QTNAME(wielder)+" dives for the "+hdesc+" of the "+enemy->query_race_name()+" but misses, barely  scratching "+
        HIM_HER(enemy)+".\n");
        break;

    }
    return 1;
}


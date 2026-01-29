 // file name:    ~Avenir/common/port/obj/uw_amulet.c
 // creator(s):    Glinda june -95
 // last update:   Lucius, Aug 2007: We use clone_unique to control the
 //                amulets distribution, the melding is no longer needed.
 //                Lilith, Feb 2001: updated the Invoke function to
 //                charge mana even if there are no undead around. Also
 //                added check for MAGIC_I_RES_LIFE which will cause the
 //                invocation to fail if the resolve_task is lower than 
 //                the target's resistance.
 //                Lilith, Jan 1998: changed symbolism from Aclolthayr to
 //                Sachluph, as she would convey protection from poison;
 //                Fixed the magic identify prop; updated indentation.
 //                Cirion, Feb 1996, fixed the resistances thanks to
 //                ~olorin/open/resistance guide.
 // purpose:       One of the treasures that can be found in the wreck
 // note:          Gives a resistance to poison of 30 (additive)
 //                Makes undead flee when invoked.
 //                Lucius, Sep 2008: Invoke ability commented out as
 //                  AoB has allowed the new vamp guild practical immunity
 //                  from the run_away() call for whatever special reason.
 //                Zizuph, June 2021: Reenable invoke ability.  There are
 //                  more undead in the game than the old vampire guild.
 //                  Add room magic/attack checks, let the DIS of the
 //                  opponent make the task more difficult.  Ensure
 //                  life magic immunity is respected.  Add a 300 sec
 //                  cooldown to prevent the ability from repeatedly
 //                  targeting (griefing) a single undead.
 // bug(s):
 // to-do:

inherit "/std/armour";
inherit "/lib/keep";
inherit "/d/Genesis/specials/examples/std_magic_lib";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/deities.h"
#include "/sys/tasks.h"                        /* defines for the TASK system */
#include <wa_types.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <stdproperties.h>

string my_long();
string staff_desc();

int invoke_cooldown;

void 
create_armour()
{
    set_short("ensorcelled black amulet");
    set_name("amulet");
    add_name(({"amulet of sachluph", "timboreallin"}));
    set_adj(({"black", "snake", "staff", "ensorcelled"}));
    set_long (my_long);
    add_item(({"staff","sprouts","sprouting staff","leaves"}), staff_desc);
    add_item(({"snake","snakes","serpent","serpents","relief","center"}), 
         "Two snakes intertwine along "
        +"the edge of the amulet, then loop around the staff at the "
        +"centre. Their bodies are made of real silver, and each of "
        +"their eyes is a tiny sparkling emerald.\n");

    set_ac(1);
    set_af(TO);
    set_am(({ 0, 0, 0}));
    set_at (A_NECK);
    set_likely_break(20);

    add_prop(SACHLUPH_OFFERING, 1);
    add_prop(MAGIC_AM_MAGIC , ({ 60, "life" }) );
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO ,
           ({ "   With the power of Life does Sachluph\n", 11,
              "   Cause the staff to sprout new growth,\n", 22,
              "   And the body to resist all that would\n", 33,
              "   Taint its purity with deadly poisons.\n", 44,
              "   Invoke Sachluph to make the Undead turn\n"+
              "   And flee far, far away from thee.\n", 55,
              "   Undead should wear me not, upon pain of death!\n", 
              66 }) );
    add_prop(OBJ_S_WIZINFO, "Adds poison resistance of 30 (additive).\n");
//             "It is possible to turn undead using the 'invoke' command.\n");
    add_prop(OBJ_I_VALUE, 1900);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);
    
    add_magic_obj_spell("'sachluph' / 'Sachluph'",
       ({ "invoke" }), "/d/Aveni/common/port/obj/uw_amulet_effect.c");

    set_magic_obj_effect(({"_turn_undead_eff_"}));
}

string
my_long()
{
    string str;

    if (TP->query_prop(LIVE_I_UNDEAD))
        str = " Something about the amulet infuses you with a sense of "+
              "dread.";
    else
        str = " Something about the amulet infuses you with a sense of "+
              "well-being, as though it somehow protects you.";

    if ( (IS_SYBARITE(TP)) || 
            (TP->query_skill(SS_LANGUAGE) > 29 + random(30)) )
        str += " You aren't certain, but you think that this amulet "+
               "harnesses the power of Sachluph, the Sybarite Goddess "+
               "of the Eleventh Hour, who governs all plants, and thus "+
               "both healing and poisoning.";

    return  "This "+ short() +" has been crafted from some strange black "+
            "metal. In the centre is the relief of a sprouting staff "+
            "entwined with serpents." + str + "\n"; 
}

string 
staff_desc()
{
    string desc = "";

    if ( (IS_SYBARITE(TP)) &&
            (TP->query_skill(SS_LANGUAGE) > 29 + random(30)) )
        desc += "The wooden staff is miraculously sprouting "
             +"new growth.";

    if (query_worn())
        desc += " The leaves, made from the gemstone jade, "
             +"seem to be rippling as though in a soft breeze. They "
             +"glow with a faint greenish light.";
    else
        desc += " The leaves growing from the staff are very "
             +"realistic.";

    return desc +"\n";
}

mixed 
query_magic_protection(string prop, object what)
{
    if (what == query_worn() && prop == MAGIC_I_RES_POISON)
    {
        query_worn()->catch_msg("The snakes and leaves on " +
            LANG_THESHORT(TO) + " shift in sudden, sinuous "+
            "movement, and a wave of greenish light washes "+
            "over you.\n");
        tell_room(ENV(query_worn()), QCTPNAME(query_worn())+
            " "+ QSHORT(TO)+" throbs with a strange glow.\n",
            query_worn());
        return ({ 30, 1 });
    }
 
    return ::query_magic_protection(prop, what);
}
 
public mixed 
wear(object ob)
{
    int damage;

    if (ob != TO || TP != ENV(TO))
        return -1;
    if (damage = TP->query_magic_res(MAGIC_I_RES_LIFE))
    {
        write("As you try to wear the amulet around your neck, "
             +"you find you cannot breathe. A horrible feeling "
             +"of paralysis runs up your spine, reminiscent of "
             +"the effects of snake venom.\n");
        say(QCTNAME(TP)+" seems to be overcome momentarily by a "
             +"pain that leaves "+ TP->query_objective() +" gasping "
             +"for breath.\n");
        TP->heal_hp(-damage);
        return -1;
    }

    if (damage = TP->query_prop(LIVE_I_UNDEAD))   
    {
        write("You find the life-force of the amulet repellant as "
             +"you attempt to place it around your neck. Your throat "
             +"closes and a greenish light washes over you, burning "
             +"your skin!\n");
        say(QCTNAME(TP)+" seems to be overcome momentarily with pain "
             +"and a greenish light washes over "+ TP->query_objective() 
             +".\n");
        TP->heal_hp(-damage);
        return -1;
    }

    TP->add_magic_effect(TO);
    add_magic_obj_effects(TP); 
    
    // Only hint to the player that it is magical if he/she has
    // a high enough awareness.
    if (TP->query_skill(SS_AWARENESS) < 40)
       return 0;

    write("As you wear the "+short()+" around your neck, you "
         +"feel your blood start to flow strongly through your "
         +"veins, as though fortified by some unseen force.\n");
    say(QCTNAME(TP)+" wears "+LANG_ASHORT(TO)+" around "+POSSESS(TP)
         +" neck.\n");
    return 1;
}
 
public mixed
remove(object ob)
{
    object owner = query_worn();
 
    if ((owner))
    { 
        owner->remove_magic_effect(TO); 
        remove_magic_obj_effects(wearer);
        
        if (owner->query_skill(SS_AWARENESS) > 40)
        {
            write("As you remove the "+short()+" from around your neck, "
                +"you feel the blood in your veins slow down slightly.\n");
            say(QCTNAME(owner)+" removes "+LANG_ASHORT(TO)+".\n");

	    return 1;
        }
    }

    return 0;   
}

void reset_cooldown()
{
    invoke_cooldown = 0;
    if (query_worn())
    {
        query_worn()->catch_tell("The " + short() + " shudders momentarily, "+
        "a brief heart beat paired with your own.\n");
    }
}

object
find_undead()
{
    object *oblist;
    int    i;

    oblist = filter(all_inventory(environment(query_worn())), living);
    if (!sizeof(oblist))
        return 0;
    for(i=0; i<sizeof(oblist); i++)
    {
        if (oblist[i]->query_prop(LIVE_I_UNDEAD))
            return oblist[i];
    }
    return 0;
}

public int
do_invoke(string str)
{
    mixed  amulets;
    object target;
    string vb;
    int i, mana, fat, res;
        
    vb = query_verb(); 
    if (!str)
    {
        notify_fail(capitalize(vb) +" what?\n");
        return 0;
    }
    if ((str != "sachluph") && (str != "Sachluph"))
    {
        notify_fail(capitalize(vb) +" what?\n");
        return 0;
    }
    if (query_worn() != this_player())
    {
        notify_fail(capitalize(vb) +" what? Perhaps you should be "+
        "wearing the "+ short() +".\n");
	return 0;
    }
    if (invoke_cooldown)
    {
       query_worn()->catch_tell("You invoke the Goddess Sachluph.\nThe "+
           short() +" flickers and fades, as if its connection to her "+
           "has been throttled.\n");
       return 1;
    }

    target = find_undead();
    object room = environment(this_player());
    mixed message;
    if (message = room->query_prop(ROOM_M_NO_ATTACK))
    {
        if (stringp(message))
        {
            query_worn()->catch_tell(message);
        }
        else
        {
            query_worn()->catch_tell("The Goddess Sachluph cannot heed your "+
               "call here.\n");
        }
        return 1;
    }
    if (message = room->query_prop(ROOM_M_NO_MAGIC))
    {
        if (stringp(message))
        {
            query_worn()->catch_tell(message);
        }
        else
        {
            query_worn()->catch_tell("The Goddess Sachluph cannot heed your "+
               "call here.\n");
        }
        return 1;
    }
    if (room->query_prop(ROOM_I_NO_ATTACK) || room->query_prop(ROOM_I_NO_MAGIC))
    {
        query_worn()->catch_tell("The Goddess Sachluph cannot heed your "+
           "call here.\n");
        return 1;
    }
    target = find_undead();
    if (target && (ONATTACK(target) || ONMAGIC(target)))
    {
        query_worn()->catch_tell("The Goddess Sachluph cannot heed your "+
           "call on your target.\n");
        return 1;
    }

    if (!target)
    {
        /* mana penelty for invoking even if there is no target */
        mana = query_worn()->query_max_mana() / 20;
        query_worn()->catch_tell("You invoke the Goddess Sachluph.\nThe "+
            short() +" glows with a faint greenish light, then subsides,"+
           "leaving you feeling both mentally and physically tired.\n"+
           "There are no undead in your vicinity.\n");

        tell_room(environment(query_worn()), QCTPNAME(query_worn()) +" "+
            short() +" glows with a faint greenish light, then subsides.\n",
            query_worn());
        return 1;
    }
    /* We've got targets, now lets do mana and fatigue checks */
    mana = query_worn()->query_max_mana() / 10;
    if (query_worn()->query_mana() < mana)
    {
        query_worn->catch_tell("Your mind is too scattered to concentrate "+
            "upon the invocation.\n");
        return 1;
    }
    fat = query_worn()->query_max_fatigue() / 10;
    if (query_worn()->query_fatigue() < fat)
    {
        query_worn()->catch_tell("You are too tired to perform the "+
            "invocation.\n");
        return 1;
    }

    /* I now invoke the amulet */
    query_worn()->add_mana(-mana);
    query_worn()->add_fatigue(-fat);
    query_worn()->catch_tell("You invoke the Goddess Sachluph.\nThe "+
        short() +" glows with a fierce and blinding greenish light, "+
        "then subsides, leaving you feeling both mentally and "+
        "physically tired.\n");
    tell_room(environment(query_worn()), QCTPNAME(query_worn()) +" "+
        short() +" glows with a fierce and blinding greenish light, "+
        "then subsides.\n", query_worn());
    invoke_cooldown = 1;
    set_alarm(300.0, 0.0, reset_cooldown);
    /* Do I have the ability to overcome any RES_LIFE the target may have?
     *  (This was added per request of Shiva and Boron)
     */
    res = target->query_prop(MAGIC_I_RES_LIFE);
    i = min(this_player()->resolve_task(TASK_ROUTINE, ({ TS_DIS }),
        target, ({ TS_DIS })), 100);
    if (i <= res)
    {
        query_worn()->catch_tell("The undead is unaffected "+
            "by your invocation of Sachluph.  "+ 
            capitalize(target->query_pronoun()) +" is protected "+
            "against Her power.\n");
        target->catch_tell("You are unaffected by the light.\n");
        return  1;
    }   

    /* NOW lets make the undead turn and run away */
    target->catch_tell("The greenish light causes terror to rise "+
            "from the depths of your being.  You feel the need to "+
            "flee.\n");
    target->add_panic(300);
    target->run_away();
    target->run_away();
    target->run_away();
    return 1;
}

void
init()
{
    ::init();
    /* required to use spell_commands from the std_magic_lib */
    init_spell_commands();
}


/*
 * Function:    cmd_parse_spell_action
 * Description: Parses actions for spell commands and targets to trigger
 *              spells added to the item.
 * Argument:    string arg - the argument which is parsed
 */
public int
cmd_parse_spell_action(string arg)
{
    int result = ::cmd_parse_spell_action(arg);
    
    if (!result)
        notify_fail("Press what together? The bracers of the umber " +
            "hulk?\n");
                                                                           
    
    return result;

/*
 * Function name: enter_env
 * Description:   The container enters a new environment
 * Arguments:     dest - The destination
 *                old  - From what object
 *
 * No longer needed, cloned with clone_unique, which spreads
 * out the cloning.
 *
void
enter_env(object dest, object old)
{
    object *obs;
    int i;

    ::enter_env(dest, old);

    obs = all_inventory(dest);
    for (i = 0; i < sizeof(obs); i++)
    {
        if (obs[i]->id("timboreallin") && obs[i] != this_object())
        {
            obs[i]->remove_object();
            dest->catch_tell("The "+ short() +"s shimmer in your "+
                "hands, then merge and become one.\n");
        }
    }
}
 */

/*
 * /d/Shire/elves/weps/aeglos.c
 * Purpose    : This is the ancient spear called, 'Aeglos'; was the weapon of the
                last High King of the Ñoldor Gil-galad, and it was used during
             	the War of the Last Alliance. It was greatly feared by the enemies,
             	but its fate after Gil-galad's death on SA 3431 is unknown. Until now.
             	The spear had been safely stored within Rivendell.
 * Located    :
 * Created By : Tomas
 */


#include "/d/Shire/sys/defs.h"
#include <cmdparse.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>
#include <filter_funs.h>
#include <tasks.h>

inherit "/std/weapon";
inherit "/lib/keep";

#define MIN_WIELD 75
#define I_WIELD_AEGLOS "_live_i_wield_aeglos_"

// Global Vars
int     given_away;
string  dropped_by_wiz,
        cloned_by_wiz;

void
create_weapon()
{
    set_name("spear");
    add_name("lance");
    set_pname(({"spear", "spears"}));
    set_adj("ancient");
    set_adj("broad-bladed");
    set_short("ancient spear");

    set_short("ancient broad-bladed spear");
    set_long("@@long_desc@@\n");

	add_cmd_item(({"inscription"}),({"read", "examine"}), "@@exa_inscription@@");


   /* eglos, or aiglos, means "Snowthorn" or "icicle" in Sindarin
    (from aeg, "point" and loss, "snow")

    'Snow-point' is the literal interpretation of the spear's name, but some sources
    go further and suggest the broader meaning 'icicle'. This might easily be correct,
    but to complicate matters there's an alternative in the name of a plant that grew
    in Beleriand, known as aeglos (a name interpreted as 'Snowthorn'). It's possible,
    then, that the point of Gil-galad's spear represented a thorn of this plant, rather
    than an icicle.

    'I was at the Battle of Dagorlad before the Black Gate of Mordor, where we had the
    mastery: for the Spear of Gil-galad and the Sword of Elendil, Aeglos 1 and Narsil,
    none could withstand.'

    Against Aeglos the spear of Gil-galad none could stand....

    His sword was long, his lance was keen,
    his shining helm afar was seen....

   */

    set_wf(TO);
    set_default_weapon((45 + random(5)), (45 + random(5)),W_POLEARM,
    W_IMPALE|W_SLASH, W_BOTH, 0);

    set_wf(TO);
    set_likely_dull(1);
    set_likely_break(1);

    add_prop(OBJ_I_LIGHT,2);

    add_prop(OBJ_I_WEIGHT,10000); /* These used to be set by mudlib if no value *
                                   * was provided according to hit/pen          */
    add_prop(OBJ_I_VOLUME,8200);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(42,40));

    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"You sense that this magic has been blessed "+
    "by ancient elven mystical powers. Since it is of elven magic, orcs  "+
    "will not be able to wield this weapon\n",25,"You sense that this "+
    "spear is called, Aeglos and was once wielded by the fallen king Gil-galad "+
    "of Noldor. It was rumored that the spear could inflict terror, " +
    "within its enemies. Since the weapon was forged by elven magic, " +
    "Orcs may not wield this weapon. Elves may find inner meaning by wielding "+
    "this weapon. ",50}));
    add_prop(OBJ_S_WIZINFO,"Orc's can't wield it. Elves can see the history in " +
    "inscription. Causes panic in its enemies.\n");
    
    
}


mixed
exa_inscription()
{
    if (TP->query_race_name() == "elf")
    {
	    write("You stare at the shimmering words, they are written in Sindarin, " +
        "but you just make them out, recalling something deep within the " +
        "recesses of your mind...SUDDENLY! As if the words could speak " +
        "you understand their meaning:\n\n " +
		"I was at the Battle of Dagorlad before the Black Gate of Mordor, " +
		"where we had the mastery: for the Spear of Gil-galad and the " +
		"Sword of Elendil, Aeglos and Narsil, none could withstand.\n" +
        "       Against Aeglos the spear of Gil-galad none could stand...\n\n " +
        "             His sword was long, his lance was keen,\n\n" +
        "                his shining helm afar was seen...\n");
        return 1;
    }
}


string
long_desc()
{
    if (TP->query_race_name() == "elf" )
	return "Standing almost 9 feet long, 'Aeglos' consists of a two foot " +
	"blade, etched in a filigree of a brass crown interleaved with thorn berry vines. " +
    "The long pole is a dark hardwood, with small diamond-like " +
    "carvings, which are designed to assist in handling The narrow end of the blade is " +
    "connected via heavy brass socketed ring fused it to the pole. Its curved tip " +
    "is designed to focus energy from its small tip, widening the deeper it goes. " +
    "A glowing inscription can be seen etched into the blade.\n"; 
	else
	return "Standing almost 9 feet long, " +short()+ " consists of a two foot " +
	"blade, etched in a filigree of a brass crown interleaved with thorn berry vines." +
    "The long pole is a dark hardwood, with small diamond-like carvings, which are "+
    "designed to assist in handling. The narrow end of the blade is connected via " +
    "heavy brass socketed ring fused it to the pole. Its curved tip is designed to " +
    "focus energy from its small tip, widening the deeper it goes.\n";
}


mixed
wield(object what)
{
    int success;
    /* Broken */
    if (query_prop(OBJ_I_BROKEN))
        return "It is of no use, the blade is too far gone.\n";
    /* Stat checks */
    success = TP->query_stat(SS_WIS) / 3;
    success += TP->query_skill(SS_WEP_POLEARM) / 3;
/*    if (success < MIN_WIELD && TP->query_race() != "orc")
        return "The spear resists your attempt at wielding it.\n";
    return 0;
    */
    if (IS_NOLDOR(TP))
    {
        write("You wrap you hands around Aeglos, the " + short() + 
        " and and cry to Tulkas to protect you.\n");
        say(QCTNAME(TP) + " wraps " + HIS_HER(TP) + " hands around the " +short() + 
        " and shouts a battlecry in an ancient tongue!\n");
        return 1;
    }
    else if(TP->query_race_name() == "elf")
    {
        write("You wrap your hands around the spear and admire its exceptional " +
        "workmanship.\n");
        say(" wraps " + HIS_HER(TP) + " hands around the " + short + 
        " and grins dangerously.\n");
        return 1;
    }
    else
    {
       write("You wrap your hands around the " + short() + " and prepare for battle.\n");
        say(QCTNAME(TP) + " wraps " + HIS_HER(TP) + " hands around the " + short() + 
        " and prepares for battle.\n");
        return 1;
    }
}


int
unwield()
{
    set_this_player(query_wielded());
    if(TP->query_race_name() == "elf"){
   	 write("As you release your grip on the ancient spear, you hear soft spoken " +
   	 "elvish words, \n\n" +
   	 "          'Guren níniatha n'i lû n'i a-govenitham'\n " +
   	 "       (My heart shall weep until I see you again...)\n\n");
   	 return 0;
   	}
    return 0;
}


static void
tell_watcher(string str, object enemy)
{
   object mee,*ob;
   int i;
   mee = query_wielded();
   ob = FILTER_LIVE(all_inventory(environment(mee))) - ({ mee });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (!ob[i]->query_option(OPT_BLOOD))
      ob[i]->catch_msg(str);
}

public int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
           int phit, int dam)
{
    string how;
    string what;
    string owhat;
    string with;
    string where;
    int i_see_combat = 1;
    object me = query_wielded();

    if ((!objectp(enemy)) || (!objectp(me)))
    {
        return 1;
    }
    // The sword resists its power against an elven opponent
    if(enemy->TP->query_race() != "elf" && !random(6))
    {
        enemy->catch_msg(QCTNAME(query_wielded())+" thrusts deeply "+
        "into your "+hdesc+" with "+HIS_HER(query_wielded())+" "+short()+ ".\n");
        query_wielded()->catch_msg("You slash deeply into "+QTNAME(enemy)+
        "'s "+hdesc+" with your "+short()+".\n");
        tell_room(E(query_wielded()),QCTNAME(query_wielded())+" thrusts deeply "+
        "into "+QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(query_wielded())+
        " "+short()+".\n",({query_wielded(),enemy}));
        enemy->heal_hp(-dam);
        if(enemy->query_hp() <= 0)
            enemy->do_die(query_wielded());
    }

    if (phurt == -1)
    {
        TP->add_panic(1);
        if (i_see_combat)
        {
            me->catch_msg("You cut a massive swath in the air near "+
            QTNAME(enemy)+"'s "+hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" cuts a massive swath in the "+
            "air near your "+hdesc+" with "+HIS_HER(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" cuts a massive swath in the air near "+
        QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+" "+short()+".\n",enemy);
        return 1;
    }
    enemy->add_panic(-3 - (phurt / 5));
    if(phurt > -1 && phurt < 5)
    {
        if (i_see_combat)
        {
            me->catch_msg("You strike a glancing blow on "+QTNAME(enemy)+
            "'s "+hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" strikes a glancing blow on "+
            "your "+hdesc+" with "+HIS_HER(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" strikes a glancing blow on "+QTNAME(enemy)+
        "'s "+hdesc+" with "+HIS_HER(me)+" "+short()+".\n",enemy);
        return 1;
    }

    if(phurt > 4 && phurt < 10)
    {
        if (i_see_combat)
        {
            me->catch_msg("You slash your "+short()+" across "+
            QTNAME(enemy)+"'s "+hdesc+", inflicting painful cuts.\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" slashes "+HIS_HER(me)+" "+short()+
            " across your "+hdesc+", inflicting much pain.\n");
        }
        tell_watcher(QCTNAME(me)+" slashes "+HIS_HER(me)+" "+short()+
        " across "+QTNAME(enemy)+"'s "+hdesc+", inflicting painful cuts.\n",enemy);
        return 1;
    }

    if(phurt > 9 && phurt < 20)
    {
        if (i_see_combat)
        {
            me->catch_msg("You lunge forward and stab "+QTNAME(enemy)+"'s "+
            hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" lunges forward and stabs your "+
            hdesc+" with "+HIS_HER(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" lunges forward and stabs "+
        QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+" "+short()+".\n",enemy);
        return 1;
    }

    if(phurt > 19 && phurt < 30)
    {
        if (i_see_combat)
        {
            me->catch_msg("Swinging wide, you feign to the right, then stab deeply "+
            "into "+QTNAME(enemy)+"'s "+hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" feigns to the right, then "+
            "stabs deeply into your "+hdesc+" with "+HIS_HER(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" feigns to the right, then stabs deeply "+
        "into "+QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+" "+short()+
        ".\n",enemy);
        return 1;

    }


    if(phurt > 29 && phurt < 50)
    {
        if (i_see_combat)
        {
            me->catch_msg("Stepping backwards, you rotate the "+short()+" in a " +
            "figure eight pattern, then in one fluid motion spin it around your " +
            "waist, "+QTNAME(enemy)+ " foolishly advances, just as you bring up " +
            "the broad blade across "+QTNAME(enemy)+"'s "+hdesc+ ".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" appears to stagger backward, while " +
            "attempting some flashy figure eight move with this " +short()+ 
            ". But as you move forward to attack, " +QCTNAME(me)+ "quickly " +
            "spins "+HIS_HER(me)+ " " +short()+ " around " +HIS_HER(me)+ " waist, " +
            "tearing your "+hdesc+" with its broad blade!\n");
        }
        tell_watcher(QCTNAME(me)+" steps back, while spinning "+HIS_HER(me)+ 
        " " +short()+ " in front of " +HIM_HER(me)+ ". "+QTNAME(enemy)+" foolishly " +
        "moves forward to attack, just as " +QCTNAME(me)+ "switches form, by " +
        "spinning "+HIS_HER(me)+ " " +short()+ "around "+HIS_HER(me)+ " waist " +
        "tearing into the " +hdesc+ " of " +QTNAME(enemy)+  ".\n",enemy);
        return 1;
    }

    if(phurt > 49 && phurt < 70)
    {
        if (i_see_combat)
        {
            me->catch_msg("You faint with a forward thrust, then step back quickly " +
            "bringing your " +short()+ " in front of you, then, quickly spin the haft " +
            "around your neck, catching  "+QTNAME(enemy)+" off guard, you shred " +
            HIS_HER(enemy)+ " "+hdesc+ " .\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" lunges forward, then bringing " +HIS_HER(me)+
            " " +short()+ " in front of " +HIM_HER(me)+ " " +HE_SHE(me)+ " quickly " +
            "spins  "+HIS_HER(me)+ " " +short()+ "around " +HIS_HER(me)+ " neck, " +
            "shreds apart your "+hdesc+" with "+HIS_HER(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" shreds apart "+QTNAME(enemy)+"'s "+
        hdesc+" with "+HIS_HER(me)+" "+short()+".\n",enemy);
        return 1;
    }
    if(phurt > 69 && phurt < 90)
    {
        if (i_see_combat)
        {
            me->catch_msg("You rip large chunks of flesh off "+
            QTNAME(enemy)+"'s "+hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" rips large chunks of flesh "+
            "off your "+hdesc+" with "+HIS_HER(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" rips large chunks of flesh off "+
        QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+" "+short()+
        ".\n",enemy);
        return 1;
    }
    if(phurt > 90)
    {
        if (i_see_combat)
        {
            me->catch_msg("You slash "+QTNAME(enemy)+"'s "+hdesc+
            " cleanly in half with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" slashes your "+hdesc+
            " cleanly in half with "+HIS_HER(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" slashes "+QTNAME(enemy)+"'s "+hdesc+
        " cleanly in half with "+HIS_HER(me)+" "+short()+".\n",enemy);
        return 1;
    }

}

int
set_dull(int i)
{
    return 0;
}

int
set_corroded(int i)
{
    return 0;
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}

void
enter_env(object to, object from)
{
  ::enter_env(to, from);
  seteuid(getuid(this_object()));
  if (!from && TP->query_wiz_level()) {
    cloned_by_wiz = CAP(TP->query_real_name());
    if (!living(to)) write_file("/d/Shire/log/items",TP->query_name()+
    " cloned the Aeglos into "+file_name(ENV(TO))+". "+ctime(time())+".\n");
    else write_file("/d/Shire/log/items",TP->query_name()+" cloned the Aeglos."+
    ctime(time())+".\n");
    }
  else if (given_away && from->query_wiz_level())
  {
    write_file("/d/Shire/log/items",from->query_name()+" gave the Aeglos to "+
    to->query_name()+". "+ctime(time())+".\n");
  given_away = 0;
  }
  if (!living(from) && strlen(dropped_by_wiz)) {
    write_file("/d/Shire/log/items",TP->query_name()+
    " picked up the Aeglos dropped by "+dropped_by_wiz+" in "+file_name(ENV(TP))+". "+
    ctime(time())+".\n");
    }
  else if (!living(from) && strlen(cloned_by_wiz)) {
    write_file("/d/Shire/log/items",TP->query_name()+
    " picked up the Aeglos cloned by "+cloned_by_wiz+" in "+file_name(ENV(TP))+". "+
    ctime(time())+".\n");
  }
}

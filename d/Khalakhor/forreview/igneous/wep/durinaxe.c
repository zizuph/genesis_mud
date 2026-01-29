#include "/d/Shire/sys/defs.h"
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>

inherit "/std/weapon";

#define DURINAXE_SHADOW             "/d/Khalakhor/igneous/wep/durinaxe_shadow"

#define AXE_SPECIAL_ID              "_Shire_durin_waraxe_"
#define AXE_NO_GET_PROP             "_Shire_i_no_get_durin_axe"
#define LIVE_I_CAN_WIELD_DURINS_AXE "_live_i_can_wield_durins_axe"

#define BALROG_SLAY   60
#define DRAGON_SLAY   30
#define EVIL_SLAY     10
#define ORC_SLAY      35
#define UNDEAD_SLAY   20

#define GOBLINOID_RACES   ({"goblin", "orc", "uruk", "troll", "hobgoblin", \
			      "half_troll", "peredhil", "yrch"})

// Prototypes
void drop_axe(object who);
void dwarf_shout(object who);

int gAxeskill_extra;
int silent = 0;

void
create_weapon()
{
    set_name("waraxe");
    add_name("axe");
    add_name(AXE_SPECIAL_ID);
    set_short("Durin's Waraxe");
    set_long("Blah, blah\n");


    set_hit(49);
    set_pen(58);
    set_wt(W_AXE);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    set_wf(TO);

    add_prop(MAGIC_AM_MAGIC,
      ({
	90, "enchantment",
	UNDEAD_SLAY, "undead-slaying",
	EVIL_SLAY, "evil-slaying",
	ORC_SLAY,  "goblinoid-slaying",
	DRAGON_SLAY, "dragon_slaying",
	BALROG_SLAY, "balrog-slaying"
      }));
    add_prop(MAGIC_AM_ID_INFO,
      ({ LANG_THESHORT(TO)+" seems to be very well crafted.\n", 1,
	"It is shining and seems to be magical.\n", 12,
	"It is made of mithril, so it is very powerful and even "+
	"light.\n", 25,
	"It hates orcs and it's kin and slays verses them.\n", 35,
	"It is of slaying versus evil.\n", 47,
	"It is also of slaying versus Balrogs and Dragons.\n", 67,
	"It is intelligent and connected with the land, so it "+
	"will travel back to it's origin in the Mines of Moria "+
	"if it is outside Middle-Earth.\n", 83,
      }));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_M_NO_GET, "@@axe_no_get@@");
}

mixed
wield(object to)
{
    wielder = ENV(TO);

    if (wielder->query_prop(LIVE_I_UNDEAD))
    {
	wielder->heal_hp(-(wielder->query_max_hp() / 5));
	wielder->add_prop(AXE_NO_GET_PROP,1);
	set_alarm(0.2,0.0,&drop_axe(wielder));
	if (wielder->query_hp() <= 0)
	    wielder->do_die(TO);
	tell_room(ENV(wielder), QCTNAME(wielder)+" is bathed in a crimson "+
	  "light as "+HE_SHE(wielder)+" screams in pain!\n",
	  ({wielder}));
	return "A thunderous voice eminates within your head: 'You are "+
	"not worthy!!!  You will pay for this insult you living corpse!'"+
	"\nA crimson light suddenly engulfs you, causing you to "+
	"scream out in pain!\n";
    }
    if (member_array(wielder->query_race_name(),GOBLINOID_RACES) != -1)
    {
	wielder->heal_hp(-(wielder->query_max_hp() / 4));
	wielder->catch_tell("A booming voice enters your mind:  Filthy "+
	  wielder->query_race_name()+", how dare you even attempt to wield "+
	  "me!!!\n");
	wielder->command("$scream");
	wielder->add_prop(AXE_NO_GET_PROP, 1);
	set_alarm(0.2,0.0, &drop_axe(wielder));
	if (wielder->query_hp() <= 0)
	    wielder->do_die(TO);
	return "Your hands feel as if they were on fire, burning your flesh.\n";
    }
    if (wielder->query_alignment() <= 0)
    {
	set_alarm(0.2,0.0,&drop_axe(wielder));
	wielder->add_prop(AXE_NO_GET_PROP,1);
	return "A thundering voice laughs:  'Servant of Evil how dare "+
	"attempt to wield me!! Release me now or suffer my wraith!!\n";
    }
    if (wielder->query_race() != "dwarf" && 
      !wielder->query_prop(LIVE_I_CAN_WIELD_DURINS_AXE))
    {
	return "A rumbling voice chuckles:  'You are not worthy! "+
	"Dare not attempt to wield me again unless you prove "+
	"yourself worthy of possessing me!\n";
    }
    if (wielder->query_race_name() == "dwarf")
    {      
	set_alarm(1.5,0.0,&dwarf_shout(wielder));
    }
    tell_room(ENV(wielder), QCTNAME(wielder)+" grasps "+LANG_THESHORT(TO)+
      " firmly in both hands.\n",({wielder}));
    wielder->catch_msg("You gasp "+LANG_THESHORT(TO)+" firmly in both your "+
      "hands, you realize the awesome power which lies within the waraxe.\n"+
      "A pleased voice says:  'Greetings worthy one!'\n");
    return 1;
}

void
unwield(object to)
{
    object who = query_wielded();

    if (gAxeskill_extra)
    {
	ADD_SKILL(who, SS_WEP_AXE, -gAxeskill_extra);
	gAxeskill_extra = 0;
    }
}

void
drop_axe(object who)
{
    if (ENV(TO) == who)
	who->command("drop "+AXE_SPECIAL_ID);
}

void
dwarf_shout(object who)
{
    string praise_str = "'All Hail Durin!!  Greatest of Mahal's Children... "+
    "May your sprit guide and protect me.'\n";
    int highest_skill;

    if (query_wielded() != who)
	return;
    tell_room(ENV(who),QCTNAME(who)+" raises "+LANG_THESHORT(TO)+
      " above "+HIS_HER(who)+" head and shouts: "+praise_str,({who}));
    who->catch_msg("You raise "+LANG_THESHORT(TO)+" above yout head and "+
      "shout out:  "+praise_str);

    highest_skill = MAX(who->query_skill(SS_WEP_SWORD) ,
      who->query_skill(SS_WEP_KNIFE));
    highest_skill = MAX(who->query_skill(SS_WEP_CLUB), highest_skill);
    highest_skill = MAX(who->query_skill(SS_WEP_POLEARM), highest_skill);

    if (who->query_skill(SS_WEP_AXE) < highest_skill)
    {
	gAxeskill_extra = highest_skill - who->query_skill(SS_WEP_AXE);
	ADD_SKILL(who, SS_WEP_AXE, gAxeskill_extra);
	// Need to update the weapon now that the persons skill has changed.
	who->update_weapon(TO);
    }
}

string
axe_no_get()
{
    if (TP->query_prop(AXE_NO_GET_PROP))
    {
	if (!silent)
	{
	    tell_room(ENV(TO),CAP(LANG_THESHORT(TO))+" starts to glow a hot "+
	      "crimson red as "+QTNAME(TP)+" brings "+HIS_HER(TP)+
	      " hand close to it.\n",({TP}));
	    silent = 1;
	}
	else
	    silent = 0;
	return CAP(LANG_THESHORT(TO))+" starts to glow a hot crimson red "+
	"in warning.  You decide it would be safer not to try and "+
	"pick it up.\n";
    }
    else
	return 0;
}

void
left_middle_earth()
{
    if (query_wielded() || living(ENV(TO)))
    {
	write("An outraged voice thunders: 'How dare you take me away "+
	  "from my homeland..  I will not stand for this treatment!!\n");
	drop_axe(ENV(TO));
    }
    tell_room(ENV(TO),CAP(short())+" melts down in a puddle of some "+
      "strange liquid and seemingly seems to evaporate from "+
      "existance!\n");
    remove_object();
}


/* This weapon will NEVER recover. */ 
public string 
query_recover() 
{
    return 0;
}

/* Durins axe refuses to be placed within containers that aren't
 * Living or are not a room. 
 */
varargs public int
move(mixed dest, mixed subloc)
{
    object old;

    if (!dest)
	return 5;
    old = ENV(TO);
    if (stringp(dest))
    {
	call_other(dest,"??");
	dest = find_object(dest);
    }
    if (!objectp(dest))
	dest = old;

    if (!living(dest) && !dest->query_prop(ROOM_I_IS))
    {
	write("A booming voice shouts in anger:  How dare you try place me "+
	  "within "+LANG_ASHORT(dest)+"!\n");
	return 5;
    }
    else
	return ::move(dest,subloc);
}


void
enter_env(object dest, object old)
{
    object shadow;
    ::enter_env(dest, old);

    if (living(dest))
    {
	FIXEUID
	shadow = clone_object(DURINAXE_SHADOW);
	shadow->shadow_me(dest);
	shadow->set_durinaxe(TO);
    }
    if (living(old))
    {
	if (old->query_durinaxe_shadow())
	    old->remove_durinaxe_shadow();
    }
}

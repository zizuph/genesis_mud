/* 
 * The Sword of Thanar
 *
 * Cleaned up by Cotillion on 2007-10-02. 
 * Removed do_die() call upon wield. Killing newbies is bad.
 *   (Gorboth - July 2010)
 * 2022-02-06: Ckrik
 *    This sword was made into a spell enhancer of power 50, death, fire and earth.
 */ 

#include "../default.h"
inherit (STD + "weapon");
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <ss_types.h>
#include <wa_types.h>

int uses = 5, alarm;
object invis;   /* Current invisible player */

int sword(object player);
int fortify(object player);
int powerword(string s);


void
create_weapon()
{
    ::create_weapon();

    set_name("sword");
    add_name("sword of thanar");
    set_pname("swords");
    set_adj("foul");
    add_adj("stygion-black");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    set_short("foul stygion-black sword");
    set_pshort("foul stygion-black swords");
    set_long("@@my_long");
    set_hit(50);
    set_pen(50);
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(50);
    set_spellpower_elements(({
        SS_ELEMENT_DEATH, SS_ELEMENT_FIRE, SS_ELEMENT_EARTH
    }));
    set_hands(W_BOTH);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_wf(TO);

    add_prop(OBJ_I_VALUE,4000);
    add_prop(OBJ_I_WEIGHT,30000);
    add_prop(OBJ_I_VOLUME,30000);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(OBJ_S_WIZINFO,"This is the sword used by the avatar of "+
      "Thanar (/d/Kalad/common/caravan/npc/avatar_thanar), which can only "+
      "be wielded by someone with a sword skill of 90, spellcraft of 20, "+
      "as well as str,dex,con,int,wis and dis of at least 100. The sword "+
      "also grants the ability of temporary invisibility to its "+
      "wielder. The sword can only do this a limited amount of times.\n");
    add_prop(MAGIC_AM_ID_INFO,({"The sword is magically enchanted. " +
    "Those versed in magic may find the sword useful in channeling arcane energy.\n",5,
	"The sword possess a great power enabling its wielder to survive the fiercest of attacks.\n",25,
	"The sword can only be wielded by one of great might. All others "+
	"will fail at the task.\n",55}));
    add_prop(MAGIC_AM_MAGIC, ({ 90, "enchantment" }));
}

string
my_long()
{
    string empty_desc;
    if(uses < 1)
	empty_desc = "A faint glimmering of darkness enshrouds the blade.";
    else
	empty_desc = "A terrible darkness enfolds the blade.";
    return("A sword that seems to be fashioned out of darkness itself. " + empty_desc + "\n");
}

mixed
wield(object what)
{
    if ((TP->query_skill(SS_WEP_SWORD) > 89) &&
	(TP->query_skill(SS_SPELLCRAFT) > 19) &&
	(TP->query_base_stat(SS_STR) > 99) &&
	(TP->query_base_stat(SS_DEX) > 99) &&
	(TP->query_base_stat(SS_CON) > 99) &&
	(TP->query_base_stat(SS_INT) > 99) &&
	(TP->query_base_stat(SS_WIS) > 99) &&
	(TP->query_base_stat(SS_DIS) > 99))
    {
	write("With great satisfaction, you lay your hands upon the hilt.\n");
	say(QCTNAME(TP) + " with great satisfaction, grasps the foul stygion-black sword.\n");
	alarm = set_alarm(10.0,0.0, &sword(TP));
	return 0;
    }

    write("You attempt to wield the blade, but instead are engulfed in an "+
	  "energy-draining black globe!\n");
    write("Your very soul seems to drain away...\n");
    say(QCTNAME(TP) + " foolishly attempted to wield the foul stygion-black sword and as a "+
	"result, is engulfed in an enery-draining black globe!\n");
    say(QCTNAME(TP) + "'s very soul seems to drain away...\n");
    
    TP->heal_hp(-1250);
    if (TP->query_hp() <= 0)
/* Lets not do this. It tends to kill newbies, which is not what we do any
   more. (Gorboth)
	TP->do_die(TO);
 */
    uses = uses + 1;
    return "A portion of your soul was drained away!\n";
}

int
sword(object player)
{
    if (!objectp(player) || player != query_wielded())
        return 1; 

    write("An urge to slay all within your reach seems about to overwhelm "+
      "you, but thankfully the urge subsides.\n");
    say(QCTNAME(TP) + " begins to look frantically about, as if "+
      "searching for someone to slay...\n");
    TP->command("$shout The world is mine to conquer!");
    TP->command("$cackle");
    alarm = set_alarm(10.0,0.0, &fortify(player));
    return 1;
}

void
init()
{
    ::init();
    add_action(powerword, "command");
}

int
fortify(object player)
{
    if (!objectp(player))
       return 1;

    if (!query_wielded())
    {
	player->catch_tell("The foul stygion-black sword urges you to wield it.\n");
	return 1;
    }

    player->catch_tell("You feel power flow from within the foul stygion-black sword "+
      "to empower you against anything.\n");
    say(QCTNAME(player) + " looks completely invincible.\n");
    player->command("$smile dem");
    return 1;
}

void
visibility(object player)
{
    if (!objectp(player) || invis != player)
	return;

    player->add_prop(OBJ_I_INVIS, player->query_prop(OBJ_I_INVIS) - 1);
    player->catch_msg("You slowly reappear...\n");
    say(QCTNAME(player) + " slowly reappears...\n");
    invis = 0;
}

void
invisibility(object player)
{
    player->add_prop(OBJ_I_INVIS, player->query_prop(OBJ_I_INVIS) + 1);
    alarm = set_alarm(60.0, 0.0, &visibility(player));
    invis = player;
}

int
unwield(object obj)
{
    if (query_wielded() == invis)
	visibility(invis);

    if (alarm && get_alarm(alarm))
	remove_alarm(alarm);

    return 0;
}

int
powerword(string s)
{
    if (!query_wielded())
    {
	write("You must wield the foul stygion-black sword first.\n");
	return 1;
    }

    if (!stringp(s) || s != "dilvardyn")
    {
	NF(capitalize(query_verb()) + " what?\n");
	return 0;
    }
    NF("You call upon the power of the foul stygion-black sword, but nothing happens.\n");
    if (uses < 1 || invis == TP)
	return 0;

    write("You call upon the power of the stygion black sword.\n");
    write("In response, power flows into you and you fade from sight!\n");
    say(QCTNAME(TP) + " concentrates deeply.\n");
    say(QCTNAME(TP) + " vanishes from sight!\n");
    uses = uses - 1;
    invisibility(TP);
    return 1;
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}

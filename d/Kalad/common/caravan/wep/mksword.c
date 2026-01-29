#include "../default.h"
inherit (STD + "weapon");

#include <ss_types.h>
#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("sword");
    set_adj("two-handed");
    add_adj("thanar");
    set_wf(TO);
    set_long("A massive sword made of the finest steel. Engraved upon the "+
      "pommel is an image of a dark sun. Engraved around the image are "+
      "several encryptic runes.\n");
    set_hit(41);
    set_pen(41);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VALUE,1560);
    add_prop(OBJ_I_WEIGHT,15000);
    add_prop(OBJ_I_VOLUME,15000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(OBJ_S_WIZINFO,"This magical blade, which belongs to the master knight "+
      "(/d/Kalad/common/caravan/npc/mknight) is a magical sword that has "+
      "been enchanted to become a more powerful weapon, however only those "+
      "individuals with a dis over 100 can wield it, since it can only be "+
      "wielded by someone of strong commitments. If they try to wield the "+
      "sword and fail, they are drained of mana. In addition, a minimum "+
      "sword skill of 40 is required to wield it. This is cumulative with "+
      "the 101 minimum dis requirement. Also the user must have an "+
      "alignment less than 500.\n");
    add_prop(MAGIC_AM_ID_INFO,({"This sword has been enchanted\n", 5,
	"The enchantment on the sword has made it more powerful than "+
	"conventional weapons.\n", 25,
	"This enchanted sword, more powerful than normal ones, can only be "+
	"wielded by individuals of strong convictions, those that try and fail "+
	"lose some mana as a result. Also, the sword has a few unique "+
	"abilities available to its wielder.\n", 51}));
}

mixed
wield(object what)
{
    if(TP->query_base_stat(SS_DIS) > 99)
	if(TP->query_alignment() < 500)
	    if(TP->query_skill(SS_WEP_SWORD) > 39)
	    {
		write("As you grip the handle of the blade, you feel a presence "+
		  "diligently appraising your dedication and convictions. Then with "+
		  "a start, the presence withdraws and allows you to wield the sword.\n");
		say(QCTNAME(TP) + " seems to be involved in some internal struggle "+
		  "with the two-handed thanar sword...\n");
		return 0;
	    }
    this_player()->add_mana(-random(50)-10);
    return "As you grip the blade's handle, a fierce presence assaults you "+
    "and commands you to release the sword. You do as you are told.\n";
}

void
init()
{
    ::init();
    add_action("swing","swing");
    add_action("death","thanaraidme");
}

int
swing()
{
    if(!query_wielded())
    {
	write("You must wield the sword first.\n");
	return 1;
    }
    write("You raise the two-handed thanar sword above your head and "+
      "rapidly swing it in a circle above you.\n");
    say(QCTNAME(TP) + " raises the two-handed thanar sword above " + TP->query_possessive() + " head and rapidly swings it around in a circle.\n");
    set_alarm(3.0,0.0,"swing_effect");
    return 1;
}

void
swing_effect()
{
    write("A gust of wind swirls around you.\n");
    say("A gust of wind swirls around " + QCTNAME(TP) + ".\n");
}

int
death()
{
    if(!query_wielded())
    {
	write("You must wield the sword first.\n");
	return 1;
    }
    write("You clasp the sword to your chest and call upon the glory of "+
      "Thanar.\n");
    say(QCTNAME(TP) + " clasps the sword to " + TP->query_possessive() + " chest and calls upon the glory of Thanar.\n");
    set_alarm(3.0,0.0,"death_effect");
    return 1;
}

void
death_effect()
{
    say("A gathering of darkness enshrouds " + QTNAME(TP) + ", and " + TP->query_pronoun() + " now looks fortified against " + TP->query_possessive() + " enemies.\n");
}

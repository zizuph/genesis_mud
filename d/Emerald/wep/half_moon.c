/* 
 * Karath 10/6/96
 * Magical half-moon polearm for the gatekeeper of Emerald.
 */

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include <ss_types.h>
#define TP	this_player()
#define	TO	this_object()
#define QW	query_wielded()
#define QPOS(QW)	QW->query_possessive()

#define MANADAMAGE ((TP->query_max_mana()/3) - (TP->query_max_mana()/2))

public string emeralds_extra();

void
create_weapon()
{
    set_name("polearm");
    add_name("half-moon");
	add_name("half moon");
    set_short("ornate jeweled half-moon polearm");
    add_adj( ({"ornate", "jeweled", "half", "moon", "half-moon"}) );
    set_long("This magnificant polearm consists of a long, oaken shaft "+
	"plated with steel, with a wicked looking half-moon crescent set on "+
	"top. The steel sleeve that joins the half-moon to the shaft is inset "+
	"with four large diamond-shaped emeralds. The half-moon is set with "+
	"the curve pointing down, and the outside edge is razor-sharp. "+
	"The top of the half-moon dips down forming a "+
	"shape of a pointed half-doughnut."+
	"\n\n");
    set_hit(37);
    set_pen(48);
    set_wt(W_POLEARM);
    set_dt(W_SLASH|W_IMPALE);
    set_hands(W_BOTH);

	add_item( ({"emerald on polearm", "emerald on half-moon",
		"emeralds on polearm", "emeralds on half-moon"}),
		"The emeralds on the shaft of the half-moon look to be " +
		"worth more gold than you can carry. @@emeralds_extra");

	add_prop(OBJ_M_NO_BUY, 1);
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
	add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
	add_prop(MAGIC_AM_ID_INFO, ({
		"The half-moon polearm reeks of magic.\n", 0,
		"The half-moon polearm is magical and seems to only be "+
			"usable by elves.\n", 20,
		"The half-moon polearm is a magical relic of Emerald and "+
			"may only be wielded by elves with high wisdom and "+
			"a good knowledge of polearms.\n", 50 }));
	add_prop(OBJ_S_WIZINFO, "This is the legendary polearm of the "+
		"elven city of Telberin. The gatekeeper of Emerald wields "+
		"this magical weapon. The polearm is wielded only by elves "+
		"with polearm skill of at least superior journeyman and "+
		"wisdom of at least 90 - 110.\n");

	set_wf(TO);
}

public int
wield(object wep)
{
	tell_room("wield fun started\n");
	if (TP->query_race_name() != "elf")
		{
			write("You try to wield the half-moon polearm, but " +
				"the it doesn't seem to be built for use by a " +
				TP->query_race_name() + ".\n" +
				"You feel mentally drained from the effort.\n");
			TP->add_mana(MANADAMAGE);
			tell_room(QCTNAME(TP) + " tries to wield " +
			TP->query_possessive() + " half-moon " +
			"polearm but for some reason fails.\n" + TP->query_pronoun() +
			" appears drained from the effort.\n");
			return -1;
		}
	if (TP->query_skill(SS_WEP_POLEARM) < 50)
		{
			write("You try to wield the half-moon polearm, but " +
				"your skill with this type of weapon is lacking.\n" +
				"You feel mentally drained from the effort.\n");
			TP->add_mana(MANADAMAGE);
			tell_room(QCTNAME(TP) + " tries to wield " +
			TP->query_possessive() + " half-moon polearm " +
			"but for some reason fails.\n" + TP->query_pronoun() +
			" appears drained from the effort.\n");
			return -1;
		}
	if ((TP->query_stat(SS_WIS) + random(20)) < 110)
		{
			write("You try to wield the half-moon polearm, but " +
				"as it is a very unique weapon with many unusual " +
				"methods of use, you just don't feel that you are " +
				"wise enough to use it properly.\n" +
				"You feel mentally drained from the effort.\n");
			TP->add_mana(MANADAMAGE);
			tell_room(QCTNAME(TP) + " tries to wield " +
			TP->query_possessive() + " half-moon polearm " +
			"but for some reason fails.\n" + TP->query_pronoun() +
			" appears drained from the effort.\n");
			return -1;
		}
	write("You take a deep breath and prepare to wield the half-moon " +
		"polearm.\n");
	tell_room(QCTNAME(TP) + " takes a deep breath and prepares " +
		"to wield " + TP->query_possessive() + " half-moon " +
		"polearm\n");
	return 0;
}

public string
emeralds_extra()
{
	int z;
	z = random(5);
	switch (z)
	{
		case 0:
			return "The emeralds flicker mysteriously.\n";
		case 1:
			return "The emeralds glow with a faint, barely perceptable "+
				"light.\n";
		case 2:
			return "The emeralds pulsate faintly.\n";
		case 3:
			return "The emeralds seem to be humming softly.\n";
		case 4:
			return "The emeralds throb and vibrate.\n";
	}
}

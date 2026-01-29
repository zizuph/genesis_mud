/* Wandering Cleric of Morgion's Amulet of Morgion
 * by Teth and Aridor, Feb 21, 1997
 * The npc that wears this: /d/Krynn/common/npcs/wand_cl_morgion.c
 */

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <language.h>
#include "/d/Krynn/std/room/cmd_parse.c"

/* prototype */
void do_magic();

public void
create_armour()
{
    set_name("amulet");
    set_pname("amulets");
    add_name(({"necklace","armour"}));
    add_pname(({"necklaces","armours"}));
    set_adj(({"bronze","etched"}));
    add_adj(({"metal","tarnished","ruddy"}));
    set_short("etched bronze amulet");
    set_pshort("etched bronze amulets");

    set_ac(5);
    set_af(TO);
    set_at(A_NECK);

    set_long("This amulet is made of tarnished bronze, so it has a ruddy " +
	     "colour to it. The metal face of the amulet is etched with a " +
	     "symbol.\n");
    add_item(({"face","metal face","symbol","etched symbol","etching"}),
	     "The symbol on the amulet is of a black hood, with two glowing " +
	     "red eyes shining from within it.\n");
    add_item(({"glowing red eyes","red eyes","eyes","glowing eyes"}),
	     "The bright eyes stare at you, with malice.\n");
    add_cmd_parse("[at] [into] [the] [glowing] [red] 'eyes'",
		  "stare","@@do_magic");
    add_item(({"hood","black hood"}),"The black hood on the amulet " +
	     "seems to be enamelled on.\n");
    
    set_keep(1);
    
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, 400 + (random(400)));
    add_prop(OBJ_I_ALIGN, -900);
    add_prop(OBJ_S_WIZINFO, "This is an Amulet of Morgion, the talisman " +
	     "of any cleric who worships this god of decay and disease. " +
	     "It is worn by a wandering cleric, wand_cl_morgion.c, from Krynn's " +
	     "common/npcs directory. " +
	     "It is mildly enchanted, and does the following effects. If worn " +
	     "by a Knight of Solamnia, it reduces their prestige. This is " +
	     "additive and intended. If worn by a player of align > 400, " +
	     "the amulet halves the players dex and con stats for an amount " +
	     "of time. It also has a special magic effect, of being able " +
	     "to detect how many livings in the room are infected with " +
	     "sickness.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
	     ({"This amulet is the talisman of an evil " +
	       "god.\n", 5, "Wearing it will have detrimental effects on people " +
	       "who follow holy and righteous paths.\n", 11,
	       "It can also detect its own in its vicinity.\n", 25,
	       "The ill wrought on those who are holy that wear it affects " +
	       "their quickness and health.\n", 51, }));
    
}

mixed
wear(object what)
{
    int stat1, stat2;

    stat1 = (TP->query_base_stat(1) / 2);
    stat2 = (TP->query_base_stat(2) / 2);
    if (TP->query_guild_member("Solamnian Knights"))
    {
        write("The amulet burns against your neck. You feel distanced " +
	      "from your faith.\n");
        say(QCTNAME(TP) + "'s neck is burned as " + HE(TP) + " places " +
	    "the etched bronze amulet against " +HIS(TP)+" skin.\n");
        TP->change_prestige(-3);
    }
    if (((TP->query_alignment()) >= 400) &&
      ((TP->query_stat(2)) >= (TP->query_base_stat(2))) &&
      ((TP->query_stat(1)) >= (TP->query_base_stat(1))))
    {
        write("The amulet flares hot against your skin. You " +
	      "feel feverish as you wear the amulet.\n");
        say(QCTNAME(TP) + " looks shaken as " +HE(TP)+" wears the " +
	    "etched bronze amulet.\n");
        TP->add_tmp_stat(1, -(stat1), 60);
        TP->add_tmp_stat(2, -(stat2), 60);
        return 1;
    }
    if (TP->query_alignment() < 400)
    {
        write("The amulet feels warm against your skin as you wear " +
	      "it, although it is not a pleasant warmth.\n");
        say(QCTNAME(TP) + " appears a little feverish as " +HE(TP)+
	    " wears the etched bronze amulet.\n");
        return 1;
    }
    return 0;
}

object *
query_sickness(object *objs)
{
    object *sick = ({});
    int i;

    for(i=0;i<sizeof(objs);i++)
      if (living(objs[i]) && present("nasty_sickness",objs[i]))
	sick += ({ objs[i] });
	
    return sick;
}

string
do_magic()
{
    object *ob;
    int num;
    ob = all_inventory(E(TP));
    ob = query_sickness(ob);
    num = (ob && sizeof(ob) ? sizeof(ob - ({ 0 })) : 0);
    if (num == 0)
    {
        write("You stare deeply into the glowing red eyes and the eyes just stare " +
	      "right back at you without blinking.\n");
        say(QCTNAME(TP) + " takes " + (query_worn() ? "the amulet from " + HIS(TP) +
				       " neck" : "an amulet") +
	    " and holds it closely before " + HIS(TP) + " eyes.\n");
        return "";
    }
    write("You stare deeply into the glowing red eyes and suddenly " +
	  LANG_WNUM(num) + " bright dot" + (num == 1 ? " appears" : "s appear") +
	  ", which you feel in your direct vicinity. You feel " +
      (num == 1 ? "this dot is" : "these dots are") + " possessed by " +
	  "the same evil might as this amulet.\n");
    say(QCTNAME(TP) + " takes " + (query_worn() ? "the amulet from " + HIS(TP) +
				   " neck" : "an amulet") +
	" and holds it closely before " + HIS(TP) + " eyes.\n");
    return "";
}

void
init()
{
    ::init();
    init_cmdparse();
}

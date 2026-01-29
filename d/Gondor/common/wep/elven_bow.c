#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>

#define UNWORTHY_DRAIN   100
#define COMBAT_DRAIN     10
#define TP               this_player()
#define ENV(x)           environment(x)

inherit "/std/bow";

public string rune_desc();
public int worthy(object player);
public void shock_reaction(object player);

int worthy_wielder = 0;

public void
create_bow()
{
    set_adj(({"sleek", "elven"}));
    set_short("sleek elven bow");
    add_item("runes", &rune_desc());
    set_long("The bow is very sleek and very light, still you feel " + 
	     "that it would require considerable strength to draw it. " +
	     "It is made from some kind of white wood that has been " +
	     "decorated with thin elven runes that seem to twine with " +
	     "the fibers of the wood.\n");

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 3250);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(42, 58) + 120);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_M_NO_BUY, 1);    
    add_prop(MAGIC_AM_MAGIC,({ 33, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({ "The elven bow seems to be magical.\n",1,
      "It seems to aid restore those that are worthy and pacify others.\n",25,
      "Touching its runes will fill the air with the song and joy " +
      "of elves. Its magic music will restore those worthy and enthrall " +
      "lesser beings with its beauty.\n",70 }));


    set_hit(42);
    set_pen(58);
}


public mixed
wield(object wep)
{
    worthy_wielder = worthy(TP);
    
    if (worthy_wielder)
    {
	write("The bow trembles as if alive when you wield it.\n");

	tell_room(ENV(TP), QCTNAME(TP) + " wields the " + wep->short() + ".\n",
		  ({ TP }));
    }
    else
    {
	if (TP->query_panic() > 200)
	{
	    return "No way you are going to touch that bow!\n";
	}
	
	write("The bow seem to tremble when you touch it. The tremors quickly grows stronger " +
              "until the air is filled with a shrill and very unnerving shriek from the bow.\n");

	tell_room(ENV(TP), "When " + QTNAME(TP) + " wields the " + wep->short() +
		  " it seems to whine with a high pitched sound. The whine quickly " +
		  "picks up to a very unnerving and shrill shriek.\n", ({ TP }));

	if (TP->resolve_task(TASK_DIFFICULT + 100, ({ TS_DIS })) > 0)
	{
	    write("You hold the bow with a firm grip and after a moment " +
		  "the shriek subsides to a pitiful wailing sound.\n");
	    tell_room(ENV(TP), QCTNAME(TP) + " holds the bow in a firm grip and after a moment " +
		      "the shriek subsides to a pitiful wailing sound.\n", ({ TP }));
	}
	else
	{
	    tell_room(ENV(TP),
		      QCTNAME(TP) + " quickly releases the " + wep->short() + ".\n",
		      ({ TP }));
	    set_alarm(0.0, 0.0, &shock_reaction(TP));
	 
	    return "The shriek sears through your mind in a white flash of pain.\n" +
		"You can not bear to hold this.. this Elf-bow!\n";
	}
    }

    return 1;
}

public mixed
unwield(object wep)
{
    return 0;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,	int dt, int phit, int dam)
{
    int shoot = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    if (shoot && worthy_wielder)
    {
	if (phurt > 5 && random(5))
	{
	    // Transfer fatigue...
	    enemy->add_fatigue(-COMBAT_DRAIN);
	    query_wielded()->add_fatigue(COMBAT_DRAIN);
	    write("The bow rings like a clarion.\n");
	}
    }

    return shoot;
}


public int
worthy(object player)
{
    if (TP->query_race() == "goblin")
    {
	return 0;
    }
    
    if (TP->query_race() == "elf" || 
	TP->query_alignment() > 400)
    {
	return 1;
    }
    
    return 0;
}


public string
rune_desc()
{
    int bonus = 0;
    int skill = 0;
    
    if (TP->query_race() == "elf")
    {
	bonus = 20;
    }
    
    skill = TP->query_skill(SS_LANGUAGE) + bonus;
    
    if (skill > 60)
    {
	return "The runes are in Quenya, reading: 'Eldi-Lindalë' " +
	    "- Star Music, or Music of the Stars.\n";
    }
    else if (skill > 40)
    {
	return "The runes are in Quenya, reading: 'Eldi-Lindalë' " +
	    "You can not quite remember what it means... " +
	    "Star-something?\n";
    }
    else
    {
	return "You haven't the faintest idea what the runes could mean, " +
	    "perhaps they are just pretty patterns made by some over " +
	    "ambitious elf?\n";
    }
}

public void 
shock_reaction(object player)
{
    player->add_panic(UNWORTHY_DRAIN);
    player->add_mana(-UNWORTHY_DRAIN);
    
    if (random(2))
    {
	player->command("$wail");
    }
    else
    {
	player->command("$wince");
    }
    
    return;    
}

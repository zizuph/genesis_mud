/*
 * The spellbook for the Wizards of High Sorcery
 */
#include "../local.h"

inherit "/std/book";
inherit "/d/Krynn/wayreth/std/spellcasting-karath";

#include <stdproperties.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include "../guild/local.h"
#include "spellbook.h"

mixed gPages = ({});
int gPrev_level = -1;

public void setup_spells(int level);

public void
create_book()
{
    set_name("book");
    add_name(SPELL_BOOK);
    set_long("This is a red book with golden bindings. It contains " +
	     "the spells a wizard from the High Sorcery is able to cast.\n");
    set_short("book");
    set_adj("red");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    maxm_page = sizeof(gPages) * 2 + 2;
    enable_reset();
}

public void
reset_scroll()
{
    setup_spells(E(TO)->query_wohs_level());    
}

/*
 * Book functions
 */
/*
 * Function name: turn_me
 * Description:   Turn the book to another page
 */
public void
turn_me()
{
    int appr_num;

    gPage = previous_object()->query_gPage();

    if (book_is_closed) 
    {
        write("But the " + short(TP) + " is closed.\n");
        return;
    }

    appr_num = LANG_NUMW(gPage);
    if (appr_num > 0 && appr_num < maxm_page + 1)
    {
        what_page = appr_num;

        write("You turn the " + short(TP) + " to page " + gPage + ".\n");
        return;
    }

    if (gPage == "forward" || gPage == "") 
    {
        int old_page = what_page;

        what_page += (what_page % 2 ? 2 : 1);

        if (maxm_page < what_page) 
        {
            write("You have reached the last page of the " + 
		  short(TP) + ".\n");    
	    what_page = old_page;
            return;
        }
	
        if ((maxm_page == what_page) || (maxm_page == what_page + 1))
            write("You turn the " + short(TP) + " to the last page.\n");
        else
            write("You turn the " + short(TP) +
                  " to page " + LANG_WNUM(what_page) + ".\n");
        return;
    }
    else 
        if (gPage == "backward" || gPage == "back")
	{
	    if ((what_page == 1) || (what_page == 2))
	    {
                write("You cannot turn the " + short(TP) +
		      " below the first page.\n");
		return;
	    }

	    what_page -= (what_page % 2 ? 1 : 2);

	    write("You turn the " + short(TP) +
		  " to page " + LANG_WNUM(what_page) + ".\n");

	    return;
	}
	else
	{
	    write("Do you want to turn the page 'forward' or 'backward', " +
		  "or maybe even turn the page to '<num>'.\n");
	    return;
	}
}

static string *
proc_string(string str)
{
    string tmp, *t;

    t = explode(break_string(str, 15), "\n");

    if (sizeof(t) > 1)
    {
        tmp = implode(t[1..], " ");
	t = ({ t[0] }) + explode(break_string(tmp, 26), "\n");
    }

    return t;
}

public int
query_number_ipages()
{
    int size = sizeof(gPages);

    return (size > 19 ? ((size - 19) / 22) + 1 : 1) * 2; 
}

/*
 * Function name: generate_index
 * Description:   It will generate the index pages.
 * Arguments:     nr - The page number
 */
static void
generate_index(int nr)
{
     string *page_l, *page_r = ({});
     int page = 1, low, high_l, high_r, i;

     write(HEADER);

     if (nr == 1)
     {
         page_l = ({ sprintf(" | /| %|28s ", "I N D E X") });
	 page_l += ({ BLANK_L });

	 page_l += ({ sprintf(" ||:| %-'.'25s %02d ", "Index pages", page) });

	 page += query_number_ipages();
	 low = 0;
	 high_l = 8;
	 high_r = 19;
     }
     else
         {
	     low = (nr == 3 ? 19 : 41) + 1;
	     page = (nr == 3 ? 43 : 87);
	     high_l = low + 10;
	     high_r = high_l + 11;

	     page_l = ({ sprintf(" | /| %-'.'25s %02d ", gPages[low-1], 
				 page) });
	     page += 2;
	 }

     i = low;

     while (i < high_l)
     {
         if (i < sizeof(gPages))
             page_l += ({ sprintf(" ||:| %-'.'25s %02d ", gPages[i], page) });
	 else
	     page_l += ({ BLANK_L });

	 page += 2;
	 i++;
     }
     
     while (i < high_r)
     {
         if (i < sizeof(gPages))
             if (i == high_l)
	         page_r = ({ sprintf("|: %-'.'25s %02d |\\ |\n", gPages[i],
				     page) });
	     else
	         page_r += ({ sprintf("|: %-'.'25s %02d |:||\n", gPages[i],
				      page) });
	 else
	     page_r += ({ BLANK_R });

	 page += 2;
	 i++;
     }

     for (i = 0; i < 11; i++)
         write(page_l[i] + page_r[i]);

     write(BLANK);

     write(sprintf(" ||:|             -%02d-             |:             -%02d-             |:||\n", nr, nr + 1));
     
     write(BOTTOM);
}

/*
 * Function name: read_book_at_page
 * Description:   Should be redefined in your book. is called from read_it
 * Arguments:     which - Read the book at which page
 *                verb  - If the player wanted to read it, or mread it.
 *                        To mread something, you can look how the scroll.c 
 *                        does it in read_it() if needed.
 */
public varargs void
read_book_at_page(int which, string verb)
{ 
    string name, header, *page_l, *page_r, *ingrs, *prep, *desc;
    mapping text;
    int i;

    seteuid(getuid());

    which -= (which % 2 ? 0 : 1);

    if (which < query_number_ipages())
    {
        generate_index(which);
	return;
    }

    name = gPages[(which - query_number_ipages()) / 2];

    text = restore_map(WBOOKPAGES + lower_case(name));

    header = HEADER + sprintf(" | /| %|28s |: %|28s |\\ |\n", name,
			      text["name"]);

//    write(header + SUB_HEADER);
    write(header + BLANK);

//    page_l = ({ sprintf(" ||:| Usage: %-21s ", text["cmd"]) });

    ingrs = proc_string(text["ingr"]);

    page_l = ({ sprintf(" ||:| Ingredients: %-15s ", ingrs[0]) });

    for (i = 1; i < sizeof(ingrs); i++)
        page_l += ({ sprintf(" ||:|   %-26s ", ingrs[i]) });
      
    prep = proc_string(text["prep"]);

    page_l += ({ sprintf(" ||:| Preparation: %-15s ", prep[0]) });

    for (i = 1; i < sizeof(prep); i++)
        page_l += ({ sprintf(" ||:|   %-26s ", prep[i]) });    

    for (i = sizeof(page_l); i < 10; i++)
        page_l += ({ BLANK_L });

    desc = explode(break_string(text["desc"], 27), "\n");

    page_r = ({ "|:  Description:                |:||\n" });
    page_r += ({ BLANK_R });

    for (i = 0; i < sizeof(desc); i++)
        page_r += ({ sprintf("|:  %-27s |:||\n", desc[i]) });

    for (; i < 8; i++)
        page_r += ({ BLANK_R });

    for (i = 0; i < 10; i++)
        write(page_l[i] + page_r[i]);


    write(sprintf(" ||:|             -%02d-             |:             -%02d-             |:||\n", which, which + 1));

    write(BOTTOM);

    return;
}

/*
 * A few check functions
 */
public int
check_combat()
{
    object caster = query_caster();

    if (!caster->query_npc() && objectp(caster->query_attack()))
    {
        caster->catch_msg("You are not able to summon the " +
			  "magic while in combat.\n");
	if (caster->query_wohs_hooded())
	    tell_room(E(caster), QCTNAME(caster) + " shakes " +
		      POSSESSIVE(caster) + " head in confusion.\n",
		      caster);
	else
	  tell_room(E(caster), QCTNAME(caster) + " gets " +
		    "a puzzled look on " + POSSESSIVE(caster) + " face.\n",
		    caster);
        return 1;
    }
    return 0;
}

public int
check_gagged()
{
    object caster = query_caster();

    if (caster->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        if (!caster->query_wiz_level())
	{
	    caster->catch_msg("You are not able pronounce the words " +
			      "right.\n");
	    return 1;
	}
	    caster->catch_msg("You cannot speak, but as a wizard, you "+
		"bypass that silly detail.\n");
    }

    return 0;
}

/*
 * Overridden functions in spellcasting
 */
public int
check_skills()
{
    return 1;
}

/*
 * Special magic function
 */
public int
kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == query_caster())
        return 0;
    return 1;
}

public object *
find_one_living_friendly(string str)
{

    object who, *whos, caster;

    caster = query_caster();

    if (!str || !strlen(str))
      {
	return ({ caster });
      }

    whos = PARSE_THIS(str,"[the] %l");
    if(sizeof(whos))
        who = whos[0];
    if(who && present(who,E(caster)) )
    {
        return ({who});
    }   

    write("You must cast this spell on a present being.\n");
    return 0;
}

public object *
find_one_living_target(string str)
{
    object target, *targets;


    if (!str || !strlen(str))
    {
        target = query_caster()->query_attack();
        if (target)
	    return ({ target });

        write("You are not fighting anyone!\n");
	return 0;
    }

    targets = PARSE_THIS(str, "[the] %l");
    if(sizeof(targets))
	target = targets[0];
    if(target && present(target,E(query_caster()) ) );
    {
        return ({ target });
    }

    write("No such target here.\n");
    return 0;
}

public mixed *
find_all_living_targets(string str)
{
    object *targets, caster, *temptargets;
    int i, maximum;
    caster = query_caster();
    maximum = (caster->query_wohs_level()/5 + random(3));

    /* Get the union of my saved enemies and everything I can see */
    /* in my environment */
    targets = FILTER_CAN_SEE(all_inventory(E(caster)) &
	caster->query_enemy(-1), caster);

    /* Nobody to target, no spell */
    if(!sizeof(targets))
      {
	write("No enemies to target!\n");
	return 0;
      }

    /* Make sure we aren't targetting more than our maximum */
    while(sizeof(targets) > maximum)
	targets -= ({ targets[random(sizeof(targets))] });

    return targets;
}

public mixed *
find_team_living_targets(string str)
{
    object *targets = ({ }), *teammates, caster;
    int i, maximum;
    caster = query_caster();
    maximum = (caster->query_wohs_level()/8 + random(3));

    /* Get our present team members plus ourselves */
    teammates = all_inventory(E(caster)) & caster->query_team();
    teammates += ({ caster, });

    /* put all the enemies into one big array */
    for(i=0; i < sizeof(teammates); i++)
	targets |= teammates[i]->query_enemy(-1);

    /* Sanity check to be sure we aren't attacking our team */
    targets -= teammates;

    /* Make sure our potential targets are in the same room */
    targets &= all_inventory(E(caster));

    /* Make sure we can see everyone we are about to target */
    targets = FILTER_CAN_SEE(targets, caster);

    /* Nobody to target, no spell */
    if(!sizeof(targets))
      {
	write("No team enemies to target!\n");
	return 0;
      }

    /* Make sure we aren't targetting more than our maximum */
    while(sizeof(targets) > maximum)
	targets -= ({ targets[random(sizeof(targets))] });

    find_player("karath")->catch_msg("Got targets\n");

    return targets;
}

public object *
find_caster(string str)
{
    return ({ query_caster() });
}

/* Function name: find_distant_living
 * Returns:       An array of objects, if object is:
 *                0 - Target was a wizard or invis.
 *                1 - The environment or the target is protected by magic
 */
public object *
find_distant_living(string str)
{
    object who = find_living(str);


    if (!objectp(who) || who->query_wiz_level())
    {
        query_caster()->catch_msg("You can't locate " + C(str) + ".\n");
        return 0;
    }

    return ({ who });
}

public object *
find_dead_object(string str)
{
    object *targets;

    targets = FIND_STR_IN_OBJECT(str, query_caster()) +
              FIND_STR_IN_OBJECT(str, E(query_caster()));

    targets = targets - filter(targets, living);

    if (!sizeof(targets))
    {
        write("You can't seem to locate " + str + " here.\n");
	return 0;
    }
    return ({ targets[0] });
}

public object *
find_environment(string str)
{
    return ({ environment(query_caster()) });
}

public object *
find_teledom_destination(string str)
{
    string file = ADMIN->query_wohs_destination(query_caster(), str);
    string *from = explode(file_name(E(query_caster())), "/") - ({""}),
           *to;

    object room;

    if (!strlen(file))
    {
        query_caster()->catch_msg("You don't have that destination " +
				  "memorised.\n");
	return 0;
    }

    to = explode(file, "/") - ({ "" });

    room = find_object(file);

    if ((sizeof(from) > 1) && (sizeof(to) > 1) && (from[1] != to[1]))
    {
	if (!objectp(room))
	{
	    if (catch(file->teleledningsanka()))
	    {
	        query_caster()->catch_msg("That destination can't be " +
					  "reached.\n");
		return 0;
	    }
	    
	    room = find_object(file);
	}

	return ({ room });
    }

    write("You didn't need the extended powers of this spell, but you "+
	"cast anway.\n");
    return ({ room });
}

public object *
find_tele_destination(string str)
{
    string file = ADMIN->query_wohs_destination(query_caster(), str);
    string *from = explode(file_name(E(query_caster())), "/") - ({""}),
           *to;

    if (!strlen(file))
    {
        query_caster()->catch_msg("You don't have that destination " +
				  "memorised.\n");
	return 0;
    }

    to = explode(file, "/") - ({ "" });

    if ((sizeof(from) > 1) && (sizeof(to) > 1) && (from[1] == to[1]))
    {
        object room = find_object(file);
        
	if (!objectp(room))
	{
	    if (catch(file->teleledningsanka()))
	    {
	        query_caster()->catch_msg("That destination can't be " +
					  "reached.\n");
		return 0;
	    }
	    
	    room = find_object(file);
	}

	return ({ room });
    }

    write("You can't cross domains with this teleport spell.\n");
    return 0;
}

public void
general(string str, object *oblist)
{
    int size;
    oblist = FILTER_PLAYERS(oblist);

    oblist->catch_msg(str + "\n");
}

public void
generalbb(string str, object *oblist)
{
    oblist = FILTER_CAN_SEE_IN_ROOM(oblist);

    general(str, oblist);
}

public int
query_spell_mess(string verb, string arg)
{
    switch (verb)
    {
        case "acidrain":
	    write("You start to mumble arcane words.\n");
	    say(QCTNAME(this_player()) + " starts to mumble arcane words.\n");
	    return 1;
	    break;

	case "unvalleddac":
	    write("You start to move your fingers in a prescribed pattern.\n");
	    say(QCTNAME(this_player()) + " starts to move " +
		POSSESSIVE(this_player()) + " fingers in a prescribed " +
		"pattern.\n");
	    return 1;
	    break;
    }
    return 0;
}

public 
list_spells()
{
    write("You should read the book to gain knowledge about the spells.\n");
}

public string
spell_wohs_fail()
{
    switch(random(2))
    {
        case 0:
	    return "You fail to concentrate enough upon the spell.\n";
	    break;

        case 1:
	    return "You fail to pronounce one of the spidery words right.\n";
	    break;
    }
}

#include "spells/cerebekvok.c"
#include "spells/merak.c"
#include "spells/unvalleddac.c"
#include "spells/leddacomata.c"
#include "spells/ustilo.c"
#include "spells/ohmstena.c"
#include "spells/baraki.c"
#include "spells/actenni.c"
#include "spells/melberentis.c"
#include "spells/nocturnus.c"
#include "spells/vattik.c"
#include "spells/kentik.c"
#include "spells/takadek.c"
#include "spells/kwerrik.c"
#include "spells/karrat.c"
#include "spells/karratala.c"
#include "spells/wrancheka.c"

/*
#include ACIDRAIN
#include ACIDARROW
#include ANIMATE
#include ANTIMAGIC
#include BURNBLOOD
#include WINVITE
*/

static void
add_book_spell(string verb, function f, string name, string book_name)
{
    add_spell(verb, f, name);
    gPages += ({ book_name });
}

static void
setup_white_spells(int level)
{
    remove_spell("kwerrik");
    remove_spell("actenni");
    remove_spell("wrancheka");
    remove_spell("ustilo");
//    remove_spell("okkaledd");
    remove_spell("karratala");

    if (level >= 2)
        add_book_spell("ustilo", do_ustilo, "Burning Hands",
                       "Ustilo");

    if (level >= 6)
	add_book_spell("actenni", do_actenni, "Haste", "Actenni");

    if (level >= 12)
        add_book_spell("kwerrik", do_kwerrik, "Locate", "Kwerrik");

    if (level >= 14)
        add_book_spell("wrancheka", do_wrancheka, "Mass Confusion", "Wrancheka");

//    if (level >= 15)
//        add_book_spell("okkaledd", do_okkaledd, "Wizard Eye", "OkkaLedd");

    if (level >= 16)
        add_book_spell("karrat", do_karrat, "Teleport", "Karrat");

    if (level >= 19)
        add_book_spell("karratala", do_karratala, "Wide Teleport", "Karratala");
}

static void
setup_red_spells(int level)
{
    remove_spell("kwerrik");
    remove_spell("actenni");
    remove_spell("melberentis");
    remove_spell("wrancheka");
//    remove_spell("okkaledd");
    remove_spell("ustilo");
    remove_spell("karrat");
    remove_spell("nocturnus");
    remove_spell("karratala");
    if (level >= 2)
        add_book_spell("ustilo", do_ustilo, "Burning Hands",
                       "Ustilo");

    if (level >= 4)
        add_book_spell("nocturnus", do_nocturnus, "Globe of Darkness",
		     "Nocturnus");

    if (level >= 6)
	add_book_spell("melberentis", do_melberentis, "Slow", "Melberentis");

    if (level >= 7)
	add_book_spell("actenni", do_actenni, "Haste", "Actenni");

    if (level >= 12)
        add_book_spell("kwerrik", do_kwerrik, "Locate", "Kwerrik");

//    if (level >= 16)
//        add_book_spell("okkaledd", do_okkaledd, "Wizard Eye", "OkkaLedd");

    if (level >= 16)
        add_book_spell("karrat", do_karrat, "Teleport", "Karrat");

    if (level >= 18)
        add_book_spell("karratala", do_karratala, "Wide Teleport", "Karratala");
}

public void
setup_black_spells(int level)
{
    remove_spell("kwerrik");
//    remove_spell("okkaledd");
    remove_spell("karrat");
    remove_spell("karratala");
    remove_spell("wrancheka");
    remove_spell("nocturnus");
    remove_spell("ohmstena");
    remove_spell("melberentis");
    if (level >= 2)
        add_book_spell("ohmstena", do_ohmstena, "Shocking Grasp",
                       "Ohmstena");


    if (level >= 4)
        add_book_spell("nocturnus", do_nocturnus, "Globe of Darkness",
		     "Nocturnus");

    if (level >= 6)
	add_book_spell("melberentis", do_melberentis, "Slow", "Melberentis");

    if (level >= 12)
        add_book_spell("kwerrik", do_kwerrik, "Locate", "Kwerrik");

    if (level >= 14)
        add_book_spell("wrancheka", do_wrancheka, "Mass Confusion", "Wrancheka");

//    if (level >= 16)
//        add_book_spell("okkaledd", do_okkaledd, "Wizard Eye", "OkkaLedd");

    if (level >= 16)
        add_book_spell("karrat", do_karrat, "Teleport", "Karrat");

    if (level >= 19)
        add_book_spell("karratala", do_karratala, "Wide Teleport", "Karratala");
}


public void
setup_spells(int level)
{
    if (!living(E(TO)))
        return;

    if (level != gPrev_level)
    {
        gPrev_level = level;
	gPages = ({});

	remove_spell("cerebekvok");
	remove_spell("merak");
	remove_spell("unvalleddac");
	remove_spell("leddacomata");
	remove_spell("baraki");
	remove_spell("vattik");
	remove_spell("kentik");
	remove_spell("takadek");

        if (level >= 0)
            add_book_spell("cerebekvok", do_cerebekvok, "Mind Whisper",
                           "CereBekvok");
        if (level >= 1)
            add_book_spell("merak", do_merak, "Halo", "Merak");

        if (level >= 2)
            add_book_spell("unvalleddac", do_unvalleddac, "Detect Magic",
			     "UnvalLeddac");
        if (level >= 4)
            add_book_spell("leddacomata", do_leddacomata, "Magic Missile",
                           "LeddacOmata");

        if (level >= 5)
	    add_book_spell("baraki", do_baraki, "Shield", "Baraki");

        if (level >= 8)
	    add_book_spell("vattik", do_vattik, "Lightning Bolt", "Vattik");

        if (level >= 10)
	    add_book_spell("kentik", do_kentik, "Identify", "Kentik");

        if (level >= 13)
	    add_book_spell("takadek", do_takadek, "Mundane Weapon Immunity", "Takadek");

	switch (ADMIN->query_member_order(E(TO)->query_real_name()))
	{
	    case "white":
	        setup_white_spells(level);
	        break;
	    case "red":
	        setup_red_spells(level);
		break;
	    case "black":
	        setup_black_spells(level);
		break;
	}

        maxm_page = sizeof(gPages) * 2 + 2;
    }
}

public void
set_book_status(int *book_status)
{
    what_page = book_status[0];
    book_is_closed = book_status[1];
}

public int *
query_book_status()
{
  return ({ what_page, book_is_closed });
}




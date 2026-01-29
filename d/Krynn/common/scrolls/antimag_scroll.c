/* A magic scroll! By Teth, Feb 1997 */

inherit "/std/scroll";
inherit "/lib/keep";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>

#define SCROLLFILE KRSCROLL + "antimag.txt"
#define SCROLL_I_FURLED "_scroll_i_furled"
#define NO_MAGIC_OBJ KRSCROLL + "antimagic_obj"

// I was first going to reduce it from permanent to 7 hours.
// But to give it some randomness, and more dangerous to rely on, I changed it to 5-10 hours.
#define NO_MAGIC_DURATION 18000 + random(18000) 

void
create_scroll()
{
    set_name("parchment");
    add_name("scroll");
    add_name("_anti_magic_scroll_");
    set_pname("parchments");
    add_pname("scrolls");
    set_adj("crinkled");
    add_adj("magic");
    set_short("furled crinkled parchment");
    add_adj("furled");
    set_pshort("crinkled parchments");
    set_long("This crinkled parchment is currently furled.\n");
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, 1000 + (random(440)));
    add_prop(SCROLL_I_FURLED, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 35, "abjuration" }));
    add_prop(MAGIC_AM_ID_INFO, ({"This scroll bears magical " +
        "enchantment.\n", 5, "Reading it without skill in language " +
        "and a measure of intelligence may cause mental pain.\n", 10,
        "It is used more easily by clerics and magic-users, " +
        "as well as people who are rangers as their main " +
        "profession.\n", 15,
        "It removes the ability of any casting of magic " +
        "in the room in which the scroll is read.\n", 35}));
    add_prop(OBJ_S_WIZINFO, "This is a scroll of abjuration. " +
      "It adds the ROOM_M_NO_MAGIC prop to the room in which " +
      "it is read. The scroll must be " +
      "unfurled to be read. Chances of reading the scroll " +
      "are done with resolve_task. Routine resolve_task for " +
      "clerics and magic-users, and occ rangers, difficult " +
      "for everyone else.\n");
    
    will_not_recover = (random(100) < PERCENTAGE_OF_RECOVERY_LOST);

    set_file(SCROLLFILE);
}

init()
{
    ADA("furl");
    ADA("unfurl");
    ::init();
}

int furl(string str)
{
    if((str=="parchment")||(str=="crinkled parchment")||
       (str=="scroll")   ||(str=="crinkled scroll"))
    {
        if (TO->query_prop(SCROLL_I_FURLED))
        {
            write("The " + query_short() + " is already furled!\n");
            return 1;
        }
        write("You furl the " + query_short() + ".\n");
        say(QCTNAME(TP) + " furls the " + QSHORT(TO) + ".\n");
        TO->add_prop(SCROLL_I_FURLED, 1);
        TO->remove_adj("unfurled");
        TO->set_short("furled tattered parchment");
        TO->add_adj("furled");
        TO->remove_item("symbols");
        TO->remove_item("black symbols");
        TO->remove_item("runes");
        TO->remove_item("black runes");
        TO->set_long("This tattered parchment is currently furled.\n");
        return 1;
    }
    NF("Furl what?\n");
    return 0;
}

int unfurl(string str)
{
    if((str=="parchment")||(str=="crinkled parchment")||
       (str=="scroll")||(str=="crinkled scroll"))
    {
        if (!(TO->query_prop(SCROLL_I_FURLED)))
        {
            write("The " + query_short() + " is already unfurled!\n");
            return 1;
        }
        write("You unfurl the " + query_short() + ".\n");
        say(QCTNAME(TP) + " unfurls the " + QSHORT(TO) + ".\n");
        TO->remove_prop(SCROLL_I_FURLED);
        TO->remove_adj("furled");
        TO->set_short("unfurled crinkled parchment");
        TO->add_adj("unfurled");
        TO->set_long("This unfurled parchment is covered with black " +
		     "runes and symbols.\n");
        TO->add_item(({"black runes","runes","symbols","black symbols"}),
		     "You'd have to read the scroll to discern the meaning.\n");
        return 1;
    }
    NF("Unfurl what?\n");
    return 0;
}

public int
read_access(object ob)
{
    if (E(ob) != TP)
    {
      NF("You must be holding the scroll to read it properly!\n");
      return 0;
    }
    if (ob->query_prop(SCROLL_I_FURLED))
    {
        NF("You can only read unfurled scrolls!\n");
        return 0;
    }
    if ((E(TP))->query_prop(ROOM_M_NO_MAGIC))
    {
        NF("The text on the scroll shimmers and waves, but does " +
	   "not allow you to read it here.\n");
        return 0;
    }
    return (function_exists("create_object", ob) == SCROLL_OBJECT);
}

/*
 * Function name: read_it
 * Description  : Perform the actual read. This function prints the text
 *                to the player and displays a message to the people in
 *                the room.
 * Arguments    : string - the command the player executed, only 'read'
 */
void
read_it(string str)
{
    int taskcheck;
    object no_magic_obj;
    
    seteuid(getuid(TO));

    if (!scroll_file)
    {
        write("There was nothing to read on the " + QSHORT(TO) + ".\n");
        return;
    }

    if ((str == "read") &&
        (file_size(scroll_file) < 4000))
    {
        if ((TP->query_guild_style_occ() == "magic") ||
            (TP->query_guild_style_occ() == "cleric") ||
            (TP->query_guild_style_occ() == "ranger") ||
            (TP->query_guild_style_lay() == "magic") ||
            (TP->query_guild_style_lay() == "cleric") ||
            (TP->query_wiz_level()))
        {
            taskcheck = TP->resolve_task(TASK_ROUTINE,
              ({TS_INT, SS_LANGUAGE}));
        }
        else taskcheck = TP->resolve_task(TASK_DIFFICULT,
              ({TS_INT, SS_LANGUAGE}));
        if (taskcheck < 75)
        {
            write("The runes and symbols of the scroll writhe before your " +
		  "eyes, then erupt from the page and invade your mind!\n");
            say(QCTNAME(TP) + " attempts to read the " + QSHORT(TO) + 
		", but fails!\n");
            TP->command("$shout My head!");
            TP->command("$scream");
            TP->set_mana(0);
            TP->command("$groan");
            TP->command("$wince");
            TP->heal_hp(-200);
            if (TP->query_hp() <= 0)
                TP->do_die(TO);
            write("The " + query_short() + " bursts into flames and disappears!\n");
            say("The "+QSHORT(TO)+" bursts into flames and disappears!\n");
            remove_object();
            return;
        }
        if (taskcheck >= 75)
        {
            write("You read the " + query_short() + ".\n");
            say(QCTNAME(TP) + " reads the " + QSHORT(TO) + ".\n");
            cat(scroll_file);
            TP->command("$say Cigama rost tuline! Lostu creallu!");
            write("The " + query_short() + " bursts into flames and disappears!\n");
            say("The "+QSHORT(TO)+" bursts into flames and disappears!\n");
            setuid();
            seteuid(getuid());
            no_magic_obj = clone_object(NO_MAGIC_OBJ);
            no_magic_obj->move(E(TP));
            no_magic_obj->apply_no_magic(NO_MAGIC_DURATION);

            write("The magic of the scroll is somehow absorbed and " +
              "dispelled by the room.\n");
            say("The magic of the scroll seems to be absorbed and " +
              "dispelled by the room.\n");
            remove_object();
        }
    }
    else
    {
        if (file_size(scroll_file) >= 50000)
        {
            write("The scroll is too large to be read.\n");
            return;
        }
    }
    if (str=="mread")
    {
      write("Due to the nature of scrolls, they must be read.\n");
    }
    return;
}

public string
query_recover()
{
  return MASTER;
}

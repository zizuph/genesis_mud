/* A magic scroll! By Teth, Feb 1997 */

inherit "/std/scroll";
inherit "/lib/keep";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>
#include <tasks.h>
#include <ss_types.h>

#define SCROLLFILE KRSCROLL + "fireres.txt"
#define SCROLL_I_FURLED "_scroll_i_furled"
#define STRENGTH 5 + (random(35))
#define TIME 60 + (random(180))
#define RES_TYPE "fire"

void
create_scroll()
{
    set_name("parchment");
    add_name("scroll");
    set_pname("parchments");
    add_pname("scrolls");
    set_adj("tattered");
    add_adj("magic");
    set_short("furled tattered parchment");
    add_adj("furled");
    set_pshort("tattered parchments");
    set_long("This tattered parchment is currently furled.\n");
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, ((STRENGTH * TIME) / 5));
    add_prop(SCROLL_I_FURLED, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 25, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({"This scroll bears magical " +
        "enchantment.\n", 5, "Reading it without skill in language " +
        "and a measure of intelligence may cause mental pain.\n", 10,
        "It is used more easily by clerics and magic-users, " +
        "as well as people who are rangers as their main " +
        "profession.\n", 15,
        "It adds " + RES_TYPE + " resistance to the reader " +
        "for some amount of time.\n", 20}));
    add_prop(OBJ_S_WIZINFO, "This is a scroll of " + RES_TYPE +
      " resistance, that gives a small amount of resistance " +
      "for a limited amount of time. The scroll must be " +
      "unfurled to be read. Chances of reading the scroll " +
      "are done with resolve_task. Routine resolve_task for " +
      "clerics and magic-users, and occ rangers, difficult " +
      "for everyone else.\n");

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
    if((str=="parchment")||(str=="tattered parchment")||
      (str=="scroll")||(str=="tattered scroll"))
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
        TO->remove_item("blue symbols");
        TO->remove_item("runes");
        TO->remove_item("blue runes");
        TO->set_long("This tattered parchment is currently furled.\n");
        return 1;
    }
    NF("Furl what?\n");
    return 0;
}

int unfurl(string str)
{
    if((str=="parchment")||(str=="tattered parchment")||
      (str=="scroll")||(str=="tattered scroll"))
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
        TO->set_short("unfurled tattered parchment");
        TO->add_adj("unfurled");
        TO->set_long("This unfurled parchment is covered with blue " +
          "runes and symbols.\n");
        TO->add_item(({"blue runes","runes","symbols","blue symbols"}),
          "You'd have to read the scroll to discern the meaning.\n");
        return 1;
    }
    NF("Unfurl what?\n");
    return 0;
}

public int
read_access(object ob)
{
    if (ob->query_prop(SCROLL_I_FURLED))
    {
        NF("You can only read unfurled scrolls!\n");
        return 0;
    }
    NF("You must be holding the scroll to read it properly!\n");
    return ((E(ob) == TP) &&
      (function_exists("create_object", ob) == SCROLL_OBJECT));
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
    object resobj;
    int taskcheck;
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
          (TP->query_guild_style_lay() == "cleric"))
        {
            taskcheck = TP->resolve_task(TASK_ROUTINE,
              ({TS_INT, SS_LANGUAGE}));
        }
        else taskcheck = TP->resolve_task(TASK_DIFFICULT,
              ({TS_INT, SS_LANGUAGE}));
        if (taskcheck < 50)
        {
            write("The runes and symbols of the scroll writhe before your " +
              "eyes, then erupt from the page and invade your mind!\n");
            say(QCTNAME(TP) + " attempts to read the " + QSHORT(TO) + 
              ", but fails!\n");
            TP->command("$scream");
            TP->set_mana(0);
            TP->command("$puke");
            TP->command("$wince");
            write("The " + query_short() + " bursts into flames and disappears!\n");
            say("The "+QSHORT(TO)+" bursts into flames and disappears!\n");
            remove_object();
            return;
        }
        if ((taskcheck = 50) || (taskcheck > 50))
        {
            write("You read the " + query_short() + ".\n");
            say(QCTNAME(TP) + " reads the " + QSHORT(TO) + ".\n");
            cat(scroll_file);
            TP->command("$say Nastok kreechok flam! Vidiffi!");
            write("The " + query_short() + " bursts into flames and disappears!\n");
            say("The "+QSHORT(TO)+" bursts into flames and disappears!\n");
            resobj = clone_object("/std/resistance");
            resobj->set_strength(STRENGTH);
            resobj->set_time(TIME);
            resobj->set_res_type(RES_TYPE);
            resobj->move(TP);
            write("You feel more resistant.\n");
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
        write("Due to the nature of scrolls, they must be read.\n");
    return;
}

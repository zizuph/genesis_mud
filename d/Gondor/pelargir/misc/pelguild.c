/*   
 *   Pelargir Adventurers Guild - modified by Cinder, from:
 *   Minas Tirith adv. guild coded by Elessar
 *
 *   NOTE.
 *
 *         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 *
 *         /Styles.
 *
 *  - Olorin, 5 February 1997: Updated skills according to new
 *                             adventurers' guild skill levels
 *                             according to 'man skills'.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/guild_support.c";
inherit "/lib/skill_raise.c";
inherit "/d/Shire/lib/training";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/* 1 = closed,   0 = open.  */
#define CLOSED          0

/* 
 *	Prototypes:
 */
private void    set_up_skills();

/*
 *	Global variables:
 */
static  int     Closed = CLOSED;

public void
create_gondor()
{
    set_short("Pelargir Adventurers' Guild");
    set_long(BSN("This is the Adventurers' Guild in Pelargir. Travelers "
      + "visiting the city and citizens alike gather here to "
      + "<meditate> and set "
      + "their personal values or to <learn> and <improve> new skills. "
      + "There is a sign hanging on the wall."));
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE,1);
    add_exit(PELAR_DIR + "streets/belfalas10", "north", 0);
    create_guild_support();
    create_skill_raise();
    set_up_skills();

    add_item("sign", "Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

}

string
wizinfo()
{
   return ("If there should be due cause to close down the guild, do so by\n"+
           "typing:  Call here close_guild\n"+
           "This will temporarily prevent mortals from entering. After a\n"+
           "reboot, the guild will be open by default.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob) || !Closed)
        return;

    if (ob->query_wiz_level())
        write("\n\nWARNING!\nYou shouldn't be here. "+
              "I'm doing some work on the guild.\n");
    else
    {
        write("The guild is closed. Come back later.\n");
        ob->move_living("north", PELAR_DIR + "street/sroad4");
    }
}


public void
init()
{
    init_skill_raise();
    init_guild_support();

    ::init();
}


public string
close_guild()
{
    Closed = !Closed;

    if (Closed)
	return "  **The guild is now closed**";
    return "  **The guild is now open**";
}

public int query_closed() { return Closed; }

private void
set_up_skills() {

    string me;

    me = "use a polearm";
    sk_add_train(SS_WEP_POLEARM,  ({ me, me, }),  0, 0, 30);
    me = "appraise the quality of objects";
    sk_add_train(SS_APPR_OBJ,     ({ me, me, }),  0, 0, 30);
    me = "appraise the value of objects";
    sk_add_train(SS_APPR_VAL,     ({ me, me, }),  0, 0, 30);
    me = "swim";
    sk_add_train(SS_SWIM,         ({ me, me, }),  0, 0, 30);
    me = "be aware of surroundings";
    sk_add_train(SS_AWARENESS,    ({ me, me, }),  0, 0, 30);
    me = "trade and make deals";
    sk_add_train(SS_TRADING,      ({ me, me, }),  0, 0, 20);
}

void
gs_hook_start_meditate()
{
    write(BSN("Carefully you sit against the wall and let the "+
      "busy din of the real world fade into the background. "+
      "With your mind focussed inward you find you are able to "+
      "<estimate> your own abilities and <set> your preference "+
      "for each. To break your meditation, just <rise> from the floor."));
}

void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface\n"+
          "of your consciousness. You exhale and feel very relaxed as\n"+
         "you get up.\n");
}


string read_sign()
{
   return "\n\n" +

"+-------------------------------------------------------------------+\n" +
"|                                                                   |\n" +
"|        P E L A G I R   A D V E N T U R E R S '   G U I L D        |\n" +
"|                                                                   |\n" +
"|  These are the available skills that can be learned here.         |\n" +
"|                                                                   |\n" +
"|  Trading. . . . . . . . . . . . Superior Amateur                  |\n" +
"|  Awareness. . . . . . . . . . . Superior Layman                   |\n" +
"|  Swim . . . . . . . . . . . . . Superior Layman                   |\n" +
"|  Appraise Value . . . . . . . . Superior Layman                   |\n" +
"|  Appraise Object. . . . . . . . Superior Layman                   |\n" +
"|  Polearms . . . . . . . . . . . Superior Layman                   |\n" +
"|                                                                   |\n" +
"+-------------------------------------------------------------------+\n\n";

}


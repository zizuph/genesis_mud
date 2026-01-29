/*
 * Dol Guldur Adventurer Guild - /d/Gondor/rhovanion/dolguldur/adv.c
 * Modified from Whitfurrows Adventurers guild
 *
 * Varian - November 2020
 *
 *   This is a modification of Styles adv_guild.c    
 *   Styles   Wed Jan 22 1992
 *   NOTE.
 *   The player can't advance more than one level at the time.
 *   This is intentional and not a bug. The players should
 *   experience the effort of gaining each level. Thus they
 *   will receive each new rank that comes along with the level.
 *
 *   If the guild is closed you can toggle this by doing,
 *   > Call here close_guild
 *   This is a quick way to close/open it if needed
 *
 *   /Styles.
 *
 *   History:
 *      reformatted text, and fixed minor typos, Sept 7, 1998
 *       -- Finwe
 */
 
#include "/d/Gondor/rhovanion/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"

inherit RHOVANION_DIR + "dolguldur/std/base";
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";
 
#define NUM sizeof(query_money_types(-1))
#define CLOSED 0/* 1 = closed,   0 = open.  */
 
void set_up_skills();
 
int closed;
object meditate;
static object bogazh;

void
create_dg_room()
{
    set_items_city();

    closed = CLOSED; 
   
    set_short("Dol Guldur Training Grounds");
    set_long("You have entered a clearing in the rubble of Dol Guldur, " +
        "an open space which the locals have used as training grounds. " +
        "The tall tower which stands in the middle of Dol Guldur is " +
        "visible to the northeast, while the rest of this clearing is " +
        "surrounded by a wall of rubble. A small sign stands at the " +
        "edge of the clearing, and there is just enough room between " +
        "the rubble to make your way out to the main road east of " +
        "here.\n");

    add_item( ({"clearing", "open space", "circle", "training grounds"}),
        "A lot of rubble has been pushed to the edges of the clearing, " +
        "allowing for plenty of open room where people can train.\n");
    add_item( ({"wall", "rubble wall", "wall of rubble"}),
        "It looks like someone just picked up all of the broken bits " +
        "of stone and wood and just dropped it in a pile around the " +
        "edge of the clearing. As a result, the only way out of here " +
        "is through the opening on the east side.\n");
    add_item( ({"sign", "small sign"}),
        "A small sign stands right at the edge of the clearing. You " +
        "can read it for more information.\n");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
    add_exit(DG_DIR + "main2", "east");

    set_no_exit_msg( ({"north", "northeast", "southeast", "south", 
            "southwest", "west", "northwest"}),
        "The piles of rubble are simply too high and unstable, " +
        "you will have to use the opening to the east.\n");
   
    create_skill_raise();
    create_guild_support();
    set_up_skills();
    reset_room();

    add_cmd_item("sign", "read", "@@read_sign@@");

}
 
void
reset_room()
{
    if (!bogazh)
        bogazh = clone_object(DG_DIR + "npc/bogazh");
    if (!present(bogazh))
        bogazh->move(this_object());
}
 
wizinfo() 
{
    return ("If there should be due cause to close down the " +
        "guild, do so by typing:  Call here close_guild\n" +
        "This will temporarily prevent mortals from entering. " +
        "After a reboot, the guild will be open by default. " +
        "Please send us some mail if there is anything that " +
        "needs to be fixed.\n\n   Gondor Wizards.\n");
}

 
enter_inv(ob, from) {
    ::enter_inv(ob, from);
   
    stop_room_tells();

    if (!query_ip_number(ob) || !closed)
        return;
   
    if (ob->query_wiz_level()) 
        write("\n\nWARNING!\nYou shouldn't be here. I'm doing " +
        "some work on the guild.\n");
    else 
    {
        write("The guild is closed. Come back later.\n");
        ob->move(DG_DIR + "main2");
    }
}
 
 
init() 
{
    ::init();
    init_skill_raise();
    init_guild_support();
}
 
close_guild() 
{
    if (closed) 
    {
        closed = 0;
       return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
}
 
query_closed() 
{ 
    return closed; 
}
 
void
set_up_skills() 
{
    string me;
    /* 
     * Add skill that can be trained. Do not add all skills, 
     * and vary a bit 
     */

    me = "use an axe";
    sk_add_train(SS_WEP_AXE,         ({ me, me }),   0,0,30 );
    me = "know where you are";
    sk_add_train(SS_LOC_SENSE,       ({ me, me }),   0,0,30 );
    me = "find and identify herbs";
    sk_add_train(SS_HERBALISM,       ({ me, me }),   0,0,20 );
    me = "handle animals";
    sk_add_train(SS_ANI_HANDL,       ({ me, me }),   0,0,30 );
    me = "track something in the wild";
    sk_add_train(SS_TRACKING,        ({ me, me }),   0,0,30 );
    me = "hunt for a living";
    sk_add_train(SS_HUNTING,         ({ me, me }),   0,0,30 );
    me = "be aware of your surroundings";
    sk_add_train(SS_AWARENESS,       ({ me, me }),   0,0,30 );
}
 
gs_meditate(str) 
{
    return ::gs_meditate(str);
}
 
sk_improve(str) 
{
    if (!bogazh || !present(bogazh))
    {
        notify_fail("There is no one here to teach you " +
        "anything! Bogazh must be somewhere else right now.\n");
        return 0;
    }
   
    return ::sk_improve(str);
}

string read_sign()
{
   return "\n\n" +
"+-------------------------------------------------------------------+\n" +
"|                                                                   |\n" +
"|                    Dol Guldur Training Academy                    |\n" +
"|                                                                   |\n" +
"|  If you have the time and the dedication, these are the skills    |\n" +
"|  Bogazh will teach you:                                           |\n" +
"|                                                                   |\n" +
"|  Axe. . . . . . . . . . . . . . Superior Layman                   |\n" +
"|  Location Sense . . . . . . . . Superior Layman                   |\n" +
"|  Herbalism. . . . . . . . . . . Superior Amateur                  |\n" +
"|  Animal Handling. . . . . . . . Superior Layman                   |\n" +
"|  Tracking . . . . . . . . . . . Superior Layman                   |\n" +
"|  Hunting. . . . . . . . . . . . Superior Layman                   |\n" +
"|  Awareness. . . . . . . . . . . Superior Layman                   |\n" +
"|                                                                   |\n" +
"+-------------------------------------------------------------------+\n\n";

}
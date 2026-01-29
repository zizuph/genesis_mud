/*   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   NOTE.
 *      The player can't advance more than one level at the time.
 *      This is intentional and not a bug. The players should
 *      experience the effort of gaining each level. Thus they
 *      will receive each new rank that comes along with the level.
 *
 *      If the guild is closed you can toggle this by doing,
 *      > Call here close_guild
 *
 *      This is a quick way to close/open it if needed
 * 
 *      /Styles.
 *       
 *      Updated January 1997 by Finwe. New room descriptions were 
 *      added as well as the ability for players to list their 
 *      guilds and taxes.
 */
 
 
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/room";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "default.h"
#include "/d/Emerald/defs.h"
 
#define NUM             sizeof(query_money_types(-1))
#define CLOSED          0       /* 1 = closed,   0 = open.  */
 
int closed;
object meditate;
 
/*
* Prototypes
*/
void set_up_skills();
 
void
create_room()
{ 
 
    set_short("Adventurers Guild of Telberin");
    set_long("   You stand on a brown carpet in the middle " +
        "of the Adventurer's Guild. It is appropriately named " +
        "because elves come here to learn and train new skills " +
        "that will help them in their many journies. The room is " +
        "decorated with trophies that many elves have donated " +
        "from their many travels. An expert instructor who " +
        "works here can help you <learn> and <improve> skills " +
        "here. You may also <meditate> here on the rug to " +
        "change your personal priorities.\n");
 
    add_item(({"trophies", "decorations", "souveniers", 
            "wall", "walls"}),
        "You see magnificent weapons, plaques, awards, armours, " +
        "and other decorations on the wall. They are proudly " +
        "displayed to show the strength and power of the elves.\n");
    add_item(({"rug", "carpet", "down", "floor"}),
        "A large brown carpet fills the room. Gold medallions " +
        "have been embroidered into the carpet. It is on these " +
        "medallions that elves sit to change their preferences.\n");
    add_item(({"medallion", "medallions"}),
        "These magical, circular designs are embroidered into " +
        "the carpet. They are made from gold threads and are " +
        "about 10 feet in diameter.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling has a large skylight in it that lights the room\n");
    add_item("skylight",
        "The skylight fills the ceiling and is made from panes " +
        "of glass.\n");
 
    add_exit( THIS_DIR + "adv_foyer", "south");
 
    closed = CLOSED; 
   
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
   
    create_guild_support();
    create_skill_raise();
    set_up_skills();
 
}
 
string
wizinfo()
{
    return ("If there should be due cause to close down the guild, " +
        "do so by typing:\n  Call here close_guild\n" +
        "This will temporarily prevent mortals from entering. " +
        "After a reboot, the guild will be open by default. Please " +
        "send me some mail if there is anything that needs to be " +
        "fixed.\n\n" +
        "   Finwe\n");
}
 
void
enter_inv(object ob, mixed from) 
{
    ::enter_inv(ob, from);
   
    if (!query_ip_number(ob) || !closed)
        return;
   
    if (ob->query_wiz_level()) 
        write("\n\nWARNING!\nYou shouldn't be here.\n " +
            "Some remodeling is being done to the guild.\n");
    else
    {
        write("The guild is closed. Come back later.\n");
        ob->move("/d/Emerald/room/keep/c10");
    }
}
 
void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
   
}
 
 
void
init()
{
    ::init();
    init_skill_raise();
    init_guild_support();
}
 
string
close_guild()
{
    if (closed)
    {
        closed = 0;
        return "  ** The guild is now opened **";
    }
    closed = 1;
    return "  ** The guild has been closed **";
}
 
query_closed() { return closed; }
 
void
set_up_skills()
{
    string me, ot;
   
    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }),     0, 0, 27 );
 
    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE,  ({ me, ot }),     0, 0, 30 );
 
    me = "use a club"; ot = me;
    sk_add_train(SS_WEP_CLUB,   ({ me, ot }),    0, 0, 27 );
 
    me = "use spellcraft"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({ me, ot }),    0, 0, 20 );
 
    me = "appraise the quality of different objects"; ot = me;
    sk_add_train(SS_APPR_OBJ,   ({ me, ot }),      0, 0, 20 );
 
    me = "appraise the value of different objects"; ot = me;
    sk_add_train(SS_APPR_VAL,   ({ me, ot }), 0, 0, 45 );
 
    me = "swim"; ot = me;
    sk_add_train(SS_SWIM,       ({ me, ot }), 0, 0, 50 );
 
    me = "climb"; ot = me;
    sk_add_train(SS_CLIMB,      ({ me, ot }), 0, 0, 40 );
 
    me = "hunt wild game"; ot = me;
    sk_add_train(SS_HUNTING,    ({ me, ot }), 0, 0, 50 );
 
    me = "be aware of your surroundings"; ot = "his awareness";
    sk_add_train(SS_AWARENESS, ({ me, ot }),     0, 0, 45 );
 
    me = "trade and make deals"; ot = me;
    sk_add_train(SS_TRADING,    ({ me, ot }),       0, 0, 30 );
}
 
void
gs_hook_start_meditate()
{
    write("You step onto a medallion that has been sewn " +
        "into the carpet and sit down on it. The cares of your " +
        "life drift away as a feeling of peace and serenity " +
        "descends. You block your senses and concentrate upon " +
        "your mind. You find yourself able to <estimate> your " +
        "different preferences and <set> them at your own desire. " +
        "Just <rise> when you are done meditating.\n"); }


void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the " +
        "surface of your consciousness. You exhale and feel very " +
        "relaxed as you stand up, walk off the medallion and back " +
        "onto the carpet.\n");
    say(QCTNAME(this_player()) + " rises from a golden medallion.\n");
}
 
int
gs_hook_already_meditate()
{
    write("You can't do that. The power of the medallion prevents " +
        "it. If you wish to finish your meditation you can do so " +
        "by typing 'rise'.\n");
    return 1;
}
 


/*
list()
{
    string str;
 
    str = this_player()->list_mayor_guilds();
    if (str)
        write("You are member of following guilds.\n" + str);
    else
        write("You are not member of any guilds.\n");
 
    return 1;
}
*/

/*   This is a modification of Styles adv_guild.c    
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
 
/*
 *  Whitfurrows Adventurer's Guild - all players can improve here.
 */
 
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/training";
 
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
 
#define NUM sizeof(query_money_types(-1))
#define CLOSED 0/* 1 = closed,   0 = open.  */
 
void set_up_skills();
 
int closed;
object meditate;
static object adebras;
 
void
create_shire_room()
{
    closed = CLOSED; 
   
    set_short("Whitfurrows Training Academy");
    set_long("@@my_long");
   
    add_item(({"rack","racks"}),
        "These racks are full of weapons and adventuring " +
        "equipment that Captain Adebras uses for instructional " +
        "purposes.\n");
    add_item(({"weapon","weapons"}),
        "All of the weapons in this room are training weapons, " +
        "and would be useless in a real fight.\n");
    add_item(({"equipment","adventuring equipment"}),
        "The adventuring gear in this room is purely for " +
        "instructional purposes, and wouldn't be of any use " +
        "outside this room.\n");
   
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
    add_exit("/d/Shire/eastroad/village/whit/whitlane5","out",0,1);
   
    create_skill_raise();
    create_guild_support();
    set_up_skills();
    reset_shire_room();

    add_item("sign", "Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

}
 
void
reset_shire_room()
{
    if (!adebras)
        adebras = clone_object("/d/Shire/eastroad/village/whit/npc/adebras");
    if (!present(adebras))
        adebras->move(this_object());
}
 
wizinfo() 
{
    return ("If there should be due cause to close down the " +
        "guild, do so by typing:  Call here close_guild\n" +
        "This will temporarily prevent mortals from entering. " +
        "After a reboot, the guild will be open by default. " +
        "Please send me some mail if there is anything that " +
        "needs to be fixed.\n\n   Shire Wizards.\n");
}
 
my_long() 
{
    return ("You have entered a large smial, that has been " +
        "burrowed deep into the hill.  The only place that is " +
        "open to the public is the training academy of Captain " +
        "Adebras, where you now stand.  Racks of weapons and " +
        "equipment line the walls, as well as a quiet, secluded " +
        "spot where you can meditate.  When the Captain is " +
        "here, he can teach you new skills, and help you " +
        "improve old skills. There is a sign hanging on the wall.\n");
   
}
 
enter_inv(ob, from) {
    ::enter_inv(ob, from);
   
    if (!interactive(ob) || !closed)
        return;
   
    if (ob->query_wiz_level()) 
        write("\n\nWARNING!\nYou shouldn't be here. I'm doing " +
        "some work on the guild.\n");
    else 
    {
        write("The guild is closed. Come back later.\n");
        ob->move("/d/Shire/eastroad/village/whit/whitlane5");
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

    me = "size up opponents";
    sk_add_train(SS_APPR_MON,  ({ me, me }),   0,0,20 );
    me = "hide inside rooms";
    sk_add_train(SS_HIDE,      ({ me, me }),   0,0,20 );
    me = "use a club";
    sk_add_train(SS_WEP_CLUB,  ({ me, me }),   0,0,30 );
    me = "move quietly";
    sk_add_train(SS_SNEAK,     ({ me, me }),   0,0,20 );
    me = "be aware of surroundings";
    sk_add_train(SS_AWARENESS, ({ me, me }),   0,0,30 );
    me = "use missiles";
    sk_add_train(SS_WEP_MISSILE, ({ me, me }),   0,0,30 );
    me = "use a dagger";
    sk_add_train(SS_WEP_KNIFE, ({ me, me }),   0,0,30 );
}
 
gs_meditate(str) 
{
    return ::gs_meditate(str);
}
 
sk_improve(str) 
{
    if (!adebras || !present(adebras))
    {
        notify_fail("There is no one here to teach you " +
        "anything!. Captain Adebras must have been murdered!\n");
        return 0;
    }
   
    return ::sk_improve(str);
}

string read_sign()
{
   return "\n\n" +
"+-------------------------------------------------------------------+\n" +
"|                                                                   |\n" +
"|      W H I T F U R R O W S   T R A I N I N G   A C A D E M Y      |\n" +
"|                                                                   |\n" +
"|  If you have the time and the dedication, these are the skills    |\n" +
"|  Captain Adebras will teach you:                                  |\n" +
"|                                                                   |\n" +
"|  Appraise Monsters. . . . . . . Superior Amateur                  |\n" +
"|  Awareness. . . . . . . . . . . Superior Layman                   |\n" +
"|  Bows and Arrows. . . . . . . . Superior Layman                   |\n" +
"|  Clubs. . . . . . . . . . . . . Superior Layman                   |\n" +
"|  Hide . . . . . . . . . . . . . Superior Amateur                  |\n" +
"|  Knives . . . . . . . . . . . . Superior Layman                   |\n" +
"|  Sneak. . . . . . . . . . . . . Superior Amateur                  |\n" +
"|                                                                   |\n" +
"+-------------------------------------------------------------------+\n\n";

}

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
 *  Modified from Whitfurrows Adventurers guild
 *  Varian - 2015
 */
 
 
#include "../defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit MIRKWOOD_OLDROAD_DIR + "base";
inherit MIRKWOOD_STD_DIR + "room";
inherit "/d/Shire/lib/training";
 
#define NUM sizeof(query_money_types(-1))
#define CLOSED 0/* 1 = closed,   0 = open.  */
 
void set_up_skills();
 
int closed;
object meditate;
static object gruk;
 
void create_room()
{
    closed = CLOSED; 
   
    set_short("Hargnak hall of warriors");
    set_long("You are standing inside a long wooden building located on " +
        "the western edge of the goblin village of Hargnak in Mirkwood. " +
        "A large banner on the northern wall proclaims this to be the " +
        "Hargnak hall of warriors. It seems obvious that the young " +
        "goblins, and perhaps even some of the older goblins too, come " +
        "here to train their skills in combat. Several racks of arms " +
        "and armours have been lined up along the south wall where " +
        "trainees use them frequently in their training. An open doorway " +
        "in the east wall leads back out into the village of Hargnak.\n");
   
    add_item_light(({"rack","racks"}),
        "These racks are made from a dark wood, and are filled with a " +
        "wide assortment of weapons and armours for the purpose of " +
        "combat training. You might even be able to learn a thing or two " +
        "here yourself!\n", LIGHT_ALL);
    add_item_light(({"north wall","northern wall"}),
        "The north wall of this hall is empty save for a massive red " +
        "banner which announces this place as the Hargnak hall of " +
        "warriors.\n", LIGHT_ALL);
    add_item_light(({"banner","red banner"}),
        "This is a huge red banner which stretches across much of the " +
        "northern wall. Jagged black letters clearly read 'The Hargnak " +
        "Hall of Warriors'.\n", LIGHT_ALL);
    add_item_light(({"south wall","southern wall"}),
        "There are several wooden racks of weapons and armours lined " +
        "up along the southern wall of this hall.\n", LIGHT_ALL);
    add_item_light(({"east wall","eastern wall", "doorway", "open doorway"}),
        "An open doorway in the east wall leads back out into the middle " +
        "of the goblin village of Hargnak.\n", LIGHT_ALL);
    add_item_light(({"west wall","western wall"}),
        "The western wall of this hall is made of wood, like the rest " +
        "of the building, and has been left unadorned.\n", LIGHT_ALL);
    add_item_light(({"floor","down", "plank", "planks"}),
        "Wide wooden planks stretch across the floor of the hall. Heavily " +
        "scratched and worn, these planks seem to have several lips " +
        "that might trip you if you are not careful.\n", LIGHT_ALL);    
    add_item_light(({"ceiling","up", "beam", "beams", "roof"}),
        "The ceiling of the hall has long wooden beams stretching across " +
        "to connect the north and south walls, supporting the roof above.\n", LIGHT_ALL);
    add_item_light(({"hargnak","village"}),
        "The goblin village of Hargnak awaits you on the other side " +
        "of the doorway.\n", LIGHT_ALL);
    add_item_light(({"wall","walls"}),
        "This building has four walls, did you want to look at one of " +
        "them in particular?\n", LIGHT_ALL);


    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
    add_exit("hargnak2", "east");
   
    create_skill_raise();
    create_guild_support();
    set_up_skills();
    reset_room();

    add_item("sign", "You can read this sign if you want\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

}
 
void
reset_room()
{
    if (!gruk)
        gruk = clone_object(GOBLINS_DIR + "npc/gruk");
    if (!present(gruk))
        gruk->move(this_object());
}
 
wizinfo() 
{
    return ("If there should be due cause to close down the " +
        "guild, do so by typing:  Call here close_guild\n" +
        "This will temporarily prevent mortals from entering. " +
        "After a reboot, the guild will be open by default. " +
        "Please send me some mail if there is anything that " +
        "needs to be fixed.\n\n   Gondor Wizards.\n");
}

 
enter_inv(ob, from) {
    ::enter_inv(ob, from);
   
    if (!query_ip_number(ob) || !closed)
        return;
   
    if (ob->query_wiz_level()) 
        write("\n\nWARNING!\nYou shouldn't be here. I'm doing " +
        "some work on the guild.\n");
    else 
    {
        write("The guild is closed. Come back later.\n");
        ob->move(GOBLINS_DIR + "hargnak2");
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

    me = "use a sword";
    sk_add_train(SS_WEP_SWORD,      ({ me, me }),   0,0,30 );
    me = "throw a javelin";
    sk_add_train(SS_WEP_JAVELIN,    ({ me, me }),   0,0,30 );
    me = "use a club";
    sk_add_train(SS_WEP_CLUB,       ({ me, me }),   0,0,30 );
    me = "use a polearm";
    sk_add_train(SS_WEP_POLEARM,    ({ me, me }),   0,0,30 );
    me = "use an axe";
    sk_add_train(SS_WEP_AXE,        ({ me, me }),   0,0,30 );
    me = "use missiles";
    sk_add_train(SS_WEP_MISSILE,    ({ me, me }),   0,0,30 );
    me = "use a dagger";
    sk_add_train(SS_WEP_KNIFE,      ({ me, me }),   0,0,30 );
}
 
gs_meditate(str) 
{
    return ::gs_meditate(str);
}
 
sk_improve(str) 
{
    if (!gruk || !present(gruk))
    {
        notify_fail("There is no one here to teach you " +
        "anything!. Gruk must be somewhere else right now.\n");
        return 0;
    }
   
    return ::sk_improve(str);
}

string read_sign()
{
   return "\n\n" +
"+-------------------------------------------------------------------+\n" +
"|                                                                   |\n" +
"|       H A R G N A K     H A L L     O F     W A R R I O R S       |\n" +
"|                                                                   |\n" +
"|  If you have the time and the dedication, these are the skills    |\n" +
"|  Gruk will teach you:                                             |\n" +
"|                                                                   |\n" +
"|  Sword. . . . . . . . . . . . . Superior Layman                   |\n" +
"|  Javelin. . . . . . . . . . . . Superior Layman                   |\n" +
"|  Bows and Arrows. . . . . . . . Superior Layman                   |\n" +
"|  Clubs. . . . . . . . . . . . . Superior Layman                   |\n" +
"|  Axe. . . . . . . . . . . . . . Superior Layman                   |\n" +
"|  Knives . . . . . . . . . . . . Superior Layman                   |\n" +
"|  Polearm. . . . . . . . . . . . Superior Layman                   |\n" +
"|                                                                   |\n" +
"+-------------------------------------------------------------------+\n\n";

}
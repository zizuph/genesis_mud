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
static object laone;
 
void create_room()
{
    closed = CLOSED; 
   
    set_short("Gairent training academy");
    set_long("This small tent looks a little bigger on the inside than " +
        "it appears from the outside, but perhaps that is mainly because " +
        "the tent is sparsely furnished. Aside from a table which sits " +
        "opposite from the opening you entered from, the rest of the " +
        "tent is empty and rather spacious. It appears that most of " +
        "the empty space here is used for training sessions.\n");
   
    add_item_light(({"tent","here"}),
        "This small tent looks a little bigger on the inside than " +
        "it appears from the outside, but perhaps that is mainly because " +
        "the tent is sparsely furnished. Aside from a table which sits " +
        "opposite from the opening you entered from, the rest of the " +
        "tent is empty and rather spacious. It appears that most of " +
        "the empty space here is used for training sessions.\n", LIGHT_ALL);
    add_item_light(({"wall","walls"}),
        "The walls of this tent are made of a rough, yet sturdy fabric. " +
        "They seem to be in very good condition, but otherwise rather " +
        "unremarkable.\n", LIGHT_ALL);
    add_item_light(({"opening","flap"}),
        "The flap of this tent has been tied up, making the narrow " +
        "opening easier to navigate. You can see the village of Gairent " +
        "when you peer through the opening.\n", LIGHT_ALL);
    add_item_light(({"village","gairent"}),
        "Peeking through the open flap of the tent, you can see the " +
        "small woodman village of Gairent.\n", LIGHT_ALL);
    add_item_light(({"table", "desk"}),
        "This small table seems to be used as a desk. There are a variety " +
        "of jars and papers organized neatly on top of it and a box beneath " +
        "the table appears to be in use as a makeshift chair.\n", LIGHT_ALL);
    add_item_light(({"box", "chair"}),
        "This is a rather plain wooden box which apparently serves as a " +
        "chair for the person who owns this tent.\n", LIGHT_ALL);
    add_item_light(({"floor", "ground", "dirt"}),
        "The floor of this tent is simply hard packed dirt. There are " +
        "many footprints all around.\n", LIGHT_ALL);    
    add_item_light(({"ceiling","up"}),
        "You look up to see the ceiling of the tent, it is made from the " +
        "same rough fabric as the walls.\n", LIGHT_ALL);
    add_item_light(({"fabric","material"}),
        "This rough fabric appears to be quite sturdy and apparently rather " +
        "effective at keeping the interior of this tent both warm and " +
        "dry.\n", LIGHT_ALL);
    add_item_light(({"jar","jars","herbs"}),
        "There are some jars on top of the small table here which appear " +
        "to contain a small variety of basic herbs.\n", LIGHT_ALL);
    add_item_light(({"paper", "papers"}),
        "Stacked neatly atop the small table are several papers. A closer " +
        "examination suggests that they are nothing more than personal " +
        "notes and records.\n", LIGHT_ALL);
    add_item_light(({"footprint","footprints"}),
        "There are dozens of sets of different footprints visible in " +
        "the hard packed dirt which is the floor inside this tent. This " +
        "appears to be a busy place!\n", LIGHT_ALL);


    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
    add_exit("gairent2", "out");
   
    create_skill_raise();
    create_guild_support();
    set_up_skills();
    reset_room();

    add_item_light("sign", "You can read this sign if you want\n", LIGHT_ALL);
    add_cmd_item("sign", "read", "@@read_sign@@");

}
 
void
reset_room()
{
    if (!laone)
        laone = clone_object(WOODSMEN_DIR + "npc/laone");
    if (!present(laone))
        laone->move(this_object());
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
        ob->move(WOODSMEN_DIR + "gairent2");
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
    sk_add_train(SS_WEP_AXE,      ({ me, me }),   0,0,30 );
    me = "know where you are";
    sk_add_train(SS_LOC_SENSE,    ({ me, me }),   0,0,30 );
    me = "find and identify herbs";
    sk_add_train(SS_HERBALISM,       ({ me, me }),   0,0,20 );
    me = "handle animals";
    sk_add_train(SS_ANI_HANDL,    ({ me, me }),   0,0,30 );
    me = "track something in the wild";
    sk_add_train(SS_TRACKING,        ({ me, me }),   0,0,30 );
    me = "hunt for a living";
    sk_add_train(SS_HUNTING,    ({ me, me }),   0,0,30 );
    me = "be aware of your surroundings";
    sk_add_train(SS_AWARENESS,      ({ me, me }),   0,0,30 );
}
 
gs_meditate(str) 
{
    return ::gs_meditate(str);
}
 
sk_improve(str) 
{
    if (!laone || !present(laone))
    {
        notify_fail("There is no one here to teach you " +
        "anything!. Laone must be somewhere else right now.\n");
        return 0;
    }
   
    return ::sk_improve(str);
}

string read_sign()
{
   return "\n\n" +
"+-------------------------------------------------------------------+\n" +
"|                                                                   |\n" +
"|                    Gairent Training Academy                       |\n" +
"|                                                                   |\n" +
"|  If you have the time and the dedication, these are the skills    |\n" +
"|  Laone will teach you:                                            |\n" +
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
//-*-C++-*-
// Adventurer's guild (/d/Avenir/common/bazaar/extr/guild)
// creator(s): Ilyian, April 30, 1995
// last update: Lilith, 14 Oct 97, updated, added unarmed skill.
//              Boriska Sep 30, 1995 Moved board dir to more logical place.
// purpose:
// note: Copied from Styles' guild.c, see below for available skills
// bug(s):
// to-do:

/* ADV GUILD: These are the skills that can be trained, max 250
*     Skill:        Level:
*  Animal handling   30
*  Awareness         30
*  Blindfighting     20
*  Climb             30
*  Defense           20
*  Herbalism         30
*  Swim              30
*  Trading           30
*  Unarmed combat    30
*                   ----
*                   250
*/


inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/std/room";

#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include <std.h>
#include "/d/Avenir/common/common.h"

#define NUM             sizeof(query_money_types(-1))
#define CLOSED          0       /* 1 = closed,   0 = open.  */

int closed;
object meditate;

void
set_up_skills() {
    string me;
    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    me = "handle animals effectively";
    sk_add_train(SS_ANI_HANDL,    ({ me, me }),  0,0,30 );
    me = "be aware of surroundings";
    sk_add_train(SS_AWARENESS,    ({ me, me }),  0,0,30 );
    me = "fight while blind";
    sk_add_train(SS_BLIND_COMBAT, ({ me, me }),  0,0,20 );
    me = "climb up surfaces";
    sk_add_train(SS_CLIMB,        ({ me, me }),  0,0,30 );
    me = "defend yourself";
    sk_add_train(SS_DEFENSE,      ({ me, me }),  0,0,20 );
    me = "find and identify herbs";
    sk_add_train(SS_HERBALISM,    ({ me, me }),  0,0,20 );
    me = "swim in water";
    sk_add_train(SS_SWIM,         ({ me, me }),  0,0,30 );
    me = "make effective deals";
    sk_add_train(SS_TRADING,      ({ me, me }),  0,0,30 );
    me = "fight unarmed";
    sk_add_train(SS_UNARM_COMBAT, ({ me, me }),  0,0,30 );
}

void
create_room() {
    object board, box;

    closed = CLOSED;

    set_short("Survival Training Center");
    set_long("You stand in a large room with a soft carpet "+
         "stretching from wall to wall. Various experts in their "+
         "trades wander about here, waiting for someone to buy their "+
         "services. Here, you can improve your skills, meditate, or "+
         "list guilds. A "+
         "beautifully carved circular staircase leads upwards, and from "+
         "the east you can hear the noise of the marketplace.\n");
    
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    IN_IN /* No source flux messages*/
    add_exit(BAZAAR + "extr/str17","east",0,1);
    add_exit(BAZAAR + "intr/common","up",0,1);

    board = clone_object("/std/board");
    board->set_board_name(BAZAAR + "intr/guild_board");
    board->set_num_notes(25);         /* Number of notes         */
    board->set_anonymous(1);          /* You may write anonymous */
    board->set_silent(0);             /* Make noise when reading */
    board->set_show_lvl(0);           /* Full wizards or higher  */
    board->set_remove_rank(WIZ_NORMAL);   
    board->set_remove_str("You somehow failed.");
    board->set_use_gedit(0);       
    board->move(this_object());

    create_skill_raise();
    create_guild_support();
    set_up_skills();
}

void
enter_inv(object ob, object from) {
    ::enter_inv(ob, from);

    if (!interactive(ob) || !closed)
        return;

    if (ob->query_wiz_level())
        write("\n\nWARNING!\nYou shouldn't be here. "+
              "I'm doing some work on the guild.\n");
    else {
        write("The guild is closed. Come back later.\n");
        ob->move(BAZAAR + "extr/str17");
    }
}

void
init() {
    ::init();
    init_skill_raise();
    init_guild_support();
}

close_guild() 
{
    if (closed) {
        closed = 0;
        return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
}

query_closed() { return closed; }


gs_meditate(str) {
    return ::gs_meditate(str);
}

sk_improve(str) {
    return ::sk_improve(str);
}

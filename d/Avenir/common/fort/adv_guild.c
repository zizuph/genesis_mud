//-*-C++-*-
// Adventurer's guild (/d/Avenir/common/outpost/adv_guild)
// creator(s): Lilith, May 2022
// purpose: Example of what the dwarven defenders would be 
//     expected to be proficient in while stationed here.
// revisions:

/* ADV GUILD: These are the skills that can be trained, max 250
*     Skill:        Level:
*  Tracking          30
*  Location Sense    30
*  Awareness         30
*  Blindfighting     20
*  Club              30
*  Axe               30
*  Acrobat           20
*  Defense           20
*  Unarmed combat    30
*                   ----
*                   240
*/

#include "outpost.h"
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit OUTPOST +"fort_base";
inherit "/d/Avenir/inherit/sair_wall";

#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include <std.h>

#define NUM             sizeof(query_money_types(-1))
#define CLOSED          0       /* 1 = closed,   0 = open.  */

int closed;
object meditate;

/* Its not open yet */
int
check_up()
{
    write("A dwarven guard blocks you from going that way.\n");
    return 1;	
}	

void
set_up_skills() {
    string me;
    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    me = "track where others have gone";
    sk_add_train(SS_TRACKING,     ({ me, me }),  0,0,30 );

    me = "avoid getting lost";
    sk_add_train(SS_LOC_SENSE,    ({ me, me }),  0,0,30 );
	
    me = "be aware of surroundings";
    sk_add_train(SS_AWARENESS,    ({ me, me }),  0,0,30 );

    me = "fight while blind";
    sk_add_train(SS_BLIND_COMBAT, ({ me, me }),  0,0,20 );
	
    me = "move acrobatically out of harm's way";
    sk_add_train(SS_ACROBAT,      ({ me, me }),  0,0,20 );
	
    me = "defend yourself";
    sk_add_train(SS_DEFENSE,      ({ me, me }),  0,0,20 );
	
    me = "use clubs";
    sk_add_train(SS_WEP_CLUB,     ({ me, me }),  0,0,30 );
	
    me = "use axes";
    sk_add_train(SS_WEP_AXE,      ({ me, me }),  0,0,30 );
	
    me = "fight unarmed";
    sk_add_train(SS_UNARM_COMBAT, ({ me, me }),  0,0,30 );
}


void
load_board()
{
    object bb;

    seteuid(getuid(this_object()));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());
}

void
create_fort_room() 
{
    object box;

    closed = CLOSED;

    set_short("a training and meditation room");
    set_long("This is a training room where the defenders of Fort "+
        "Sybarus brush up on their skills before heading out to the "+
        "courtyard to practice their moves. "+
        "This being the ground floor of the north tower, the walls "+
        "are very thick and impervious to external noise. "+
        "The room is well-lighted by many crystal and copper lamps "+
        "installed on the walls. "+
		"In the corner is a simple mat for meditating on, with a "+
        "small sign nearby."+
        "\n");

    add_exit("gaol_main","down");
    add_exit("fort1", "east");
    add_exit("ntower1","up", check_up);

    add_npc(MON + "dw_guard", 1);
	
    create_skill_raise();
    create_guild_support();
    set_up_skills();
    load_board();	
    add_exit_views();
    add_fort_room();
	add_sair_wall();
    set_sair_dest(({OUTPOST+"tower_middle2", OUTPOST+"cave1", 
	    PORT +"port2"}));
		
	add_item(({"sign", "small sign"}), "You can <learn> or <improve> "+
        "your skills, <meditate>, or <list guilds>.\n");
	add_cmd_item(({"sign", "small sign"}), "read", 
        "You can <learn> or <improve> "+
        "your skills, <meditate>, or <list guilds>.\n");
    add_item(({"mat", "simple mat", "sea grass mat"}),
        "It is a simple mat woven of sea grass harvested from the "+
        "Sea of Sybarus nearby.\n");		
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
        write("The training guild is closed. Come back later.\n");
        ob->move(OUTPOST +"fort1");
    }
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

public void
init()
{
    ::init();
    sair_init();  
    init_skill_raise();
    init_guild_support();	
}
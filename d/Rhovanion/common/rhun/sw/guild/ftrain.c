
/*
 * Written by Quis for the Goblin Start Area 920516
 * Adapted for Spellweavers' Guild in Rhovanion 940309
 * by Farlong
 */

inherit "/d/Rhovanion/lib/room";

inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"
int closed;
#define OPEN		0	/* 1 = closed,   0 = open.  */

create_room()
{
  ::create_room();
  change_prop(ROOM_I_LIGHT,1);
  change_prop(ROOM_I_INSIDE,1);

  set_short("Mundane-skills training room");

  set_long(break_string("This is the room where Spellweavers"
	+" may improve the mundane abilities they require for"
	+" interracting with mortals of other paths.  The room"
	+" is dimly lit, and you feel a dark presense seem"
	+" to flow all around you.\n",75));

  AE(SWG+"t_hallway","west",0);

  closed = OPEN; 
  add_prop(OBJ_S_WIZINFO, "@@wizinfo");
  set_up_skills();

}


#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>

#define NUM		sizeof(query_money_types(-1))
#define CLOSED		0	/* 1 = closed,   0 = open.  */


/*
 * Prototypes
 */
void set_up_skills();


/* Note: I'm not sure what this wizinfo/close/open stuff does, but
   I'd rather not mess with it.--- Farlong 
*/

string
wizinfo()
{
   return ("If there should be due cause to close down the guild, do so by\n" +
	   "typing:  Call here close_guild\n" +
	   "This will temporarily prevent mortals from entering. After a\n" +
	   "reboot, the guild will be open by default. Please send me some\n" +
	   "mail if there is anything that needs to be fixed.\n\n   /Styles.\n"
	   );
}

void
init()
{
    ::init();
    init_guild_support();
    init_skill_raise();
}

string
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

query_closed() { return closed; }

void
set_up_skills()
{
    sk_add_train(SS_WEP_KNIFE,"use a knife in combat",0,0,50);
    sk_add_train(SS_DEFENCE,"defend against enemies in combat",0,0,50);
    sk_add_train(SS_HIDE,"hide",0,0,25);
    sk_add_train(SS_SNEAK,"sneak",0,0,25);
}




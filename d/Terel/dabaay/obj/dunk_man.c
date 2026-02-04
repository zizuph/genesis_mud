/*
 * * Lucius May 2009: /d/Terel/dark/ is gone, moved to Avenir.
 * 	Updated clone locations.
 */
#include "/d/Terel/include/Terel.h"
inherit "/std/object";
#define DUNKER_LOG  DABAAY_DIR + "log/dunker.loc"
#define DAB_NPC "/d/Terel/dabaay/npc/"

string gLocation = "";
string *gLocales = ({"/d/Terel/mountains/pool",
                     "/d/Terel/mountains/dcave",
                     "/d/Terel/common/road/cornerstone",
                     "/d/Terel/dabaay/harbor/bwalk_7"});

object dunker;

int summon_dunker();


void
create_object()
{
    FIX_EUID;
    set_name("dunk_man");
}

int
summon_dunker()
{
    if(!dunker)
    {
       gLocation = gLocales[random(sizeof(gLocales))];
       dunker = clone_object(DAB_NPC + "rogre");
       dunker->move(gLocation);
       write_file (DUNKER_LOG, gLocation + "(" +ctime(time()) +")\n");
       return 1;
    }
    return 0;
}

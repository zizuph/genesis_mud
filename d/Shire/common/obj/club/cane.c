// The guild object of the Old Fogey's Club...Dunstable 12/94

#pragma save_binary;

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/common/defs.h"
#include <formulas.h>
#define FOGEY_SOUL OBJ_DIR+"club/fogey_soul"
#define RACE this_player()->query_race()


void
create_object()
{
    set_name("cane");
    add_name("_fogey_cane_");
    add_adj(({"old","gnarled"}));
    set_short("old gnarled cane");
    set_long("This old gnarled cane is made of the sternest of oak, "+
      "which withstands the test of time very well.  The epitaph "+
      "'fhelp' has been etched into the side.\n");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,"The cane grips your hand and will not "+
      "let go.\n");
}

void
enter_env(object inv,object from)
{
    ::enter_inv(inv,from);

    if (!interactive(inv))
	return;
    if (inv->query_ghost())
	return;
    // Below code makes sure the m_in and m_out msgs aren't hardcoded.
    if (!inv->query_fogey_limp_shadow())
    {
	if (inv->query_m_out() == "leaves limping")
	    inv->set_m_out(F_ALIVE_MSGOUT);
	if (inv->query_m_in() == "arrives limping")
	    inv->set_m_in(F_ALIVE_MSGIN);
    }
    set_alarm(3.0, 0.0, "get_me_soul", inv);
}

string
query_auto_load() { return MASTER + ":"; }

public string
query_recover() { return 0; }

void
get_me_soul(object ob)
{
    if (ob->query_gender() != 0 && ob->query_wiz_level() || 
      (ob->query_race() != "human" && ob->query_race() != "hobbit" &&
	ob->query_race() != "dwarf"))
    {
	ob->catch_msg("Hey, your not an old fogey anymore!!\n");
	ob->remove_fogey_limp_shadow();
	remove_object();
	return;
    }
    setuid(); seteuid(getuid());
    ob->add_cmdsoul(FOGEY_SOUL);
    ob->update_hooks();
}

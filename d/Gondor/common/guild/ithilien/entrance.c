#pragma save_binary

inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

object ranger;

public int check_ranger();

create_room()
{
  set_short("Under the bushes");
  set_long(BS("You are standing at the top of a steep set of steps, your "+
    "head just bowed under a green roof of leaves. A little light "+
    "gets through from the outside, but enough for you to see the stairs "+
    "descending into a gloomy passage with stone walls. You can step "+
    "out of the bushes here. The sound of a rushing stream comes from the "+
    "north of here. \n")); 
  add_item("bushes","The bushes growing here are covering this hidden stair\n"+
    "from unwanted visitors. You may step out from them to the riverbank.\n");
  add_item("roof","The green leaf-roof is made up of bushes growing here.\n");
  add_item(({"stairs","steps"}),BS("The stone steps are carved into the hill, "+
    "leading down to a hidden path The steps themselves are smooth, but "+
    "hidden from view by all the bushes around.\n"));
  add_item("passage","The passage leads west into darkness.\n");
  add_exit(RANGER_ITH_DIR+"passage6","down","@@stop_stealth");
  add_exit("/d/Gondor/ithilien/nforest/fpath/bushes5","out","@@start_stealth");
}

int
start_stealth()
{
    if (TP->query_prop("_ranger_was_stealthy"))
    {
        TP->remove_prop("_ranger_was_stealthy");
        if (TP->query_autosneak() || sizeof(TP->query_team()))
            return 0;
        TP->set_autosneak(1);
        TP->catch_msg("You prepare to move stealthily again "
          + "as you were when you entered Henneth Annun.\n");
    }
    return 0;
}

int
stop_stealth()
{
    if (check_ranger())
    {
	return 1;
    }
    if (TP->query_autosneak())
    {
        TP->set_autosneak(0);
        TP->catch_msg("You stop being stealthy as you enter "
          + "the passage to Henneth Annun.\n");
        TP->add_prop("_ranger_was_stealthy", 1);
    }
    return 0;
}



public int
check_ranger()
{
    if (TP->query_wiz_level()) 
        return 0;
    if (TP->query_skill(SS_PUNISHMENT) == NOACCESS) 
    {
        write(BSN("You are stopped on the steps, since the Council of Rangers"+
	      " has punished you with limited access to the guildhouses."));
	return 1;
    }
    if (!present("ranger_guild_object", TP))
    {
	write("You are stopped on the steps, as you have no "+
	      "membership-token to show.\n");
        return 1;
    }
    return 0;
}
